/*

    Copyright (c) 2019 Johan Kanflo (github.com/kanflo)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "espressif/esp_common.h"
#include "esp/uart.h"
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <ssid_config.h>
#include <espressif/esp_sta.h>
#include <espressif/esp_wifi.h>
#include <paho_mqtt_c/MQTTESP8266.h>
#include <paho_mqtt_c/MQTTClient.h>
#include <i2c/i2c.h>
#include <ssd1306/ssd1306.h>
#include <fonts/fonts.h>
#include "font_bits.h"
#include "icon_bits.h"
#include "font.h"
#include "ssd1306_utils.h"
#include "mqtt_config.h"


/** I2C configuration */
#define I2C_BUS 0
#define SCL_PIN 0
#define SDA_PIN 2

#define GPIO_BUTTON 0
//#define GPIO_BUTTON 5
/** Pressing the button lights up the display if dimmed or off, go back to
 *  previous setting after this time
 */
#define BUTTON_ACTION_TIME_MS  (5000)
#define BUTTON_DEBOUNCE_TIME_MS  (150)

/** Size of display */
#define DISPLAY_WIDTH  (128)
#define DISPLAY_HEIGHT (32)

/** If we have not connected within this time, something might be up with the
  *  wifi driver and we reboot as a feeble attempt to fix that
  */
#define WIFI_RESTART_TIME_MS  (60000)

static const ssd1306_t dev = {
    .protocol     = SSD1306_PROTO_I2C,
    .screen       = SSD1306_SCREEN,
    .i2c_dev.bus  = I2C_BUS,
    .i2c_dev.addr = SSD1306_I2C_ADDR_0,
    .width        = DISPLAY_WIDTH,
    .height       = DISPLAY_HEIGHT
};

/* Local frame buffer */
static uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

#define DEFAULT_FONT FONT_FACE_ROBOTO_10PT

/** Convenience macros. Cannot understant the FreeRTOS tick addiction... */
#define delay_ms(t) vTaskDelay((t) / portTICK_PERIOD_MS)
#define get_time_ms() (xTaskGetTickCount() / configTICK_RATE_HZ)

/** Mutes for display updates */
SemaphoreHandle_t display_sem;
/** A semaphose that incicates wifi connection */
SemaphoreHandle_t wifi_connected;
/** MQTT publish queue */
QueueHandle_t publish_queue;
/** Button press queue */
QueueHandle_t button_queue;

#define PUB_MSG_LEN 32

/** Shall we draw stuff on the display of should it be considered off? */
bool display_on = true;
/** Is the display dimmed? */
bool display_dimmed = false;
/** Latest received temperature */
char temperature[PUB_MSG_LEN] = {0};
/** Latest received forecasted temperature */
char forecast[PUB_MSG_LEN] = {0};
/** Kerning between the temperature characters */
uint32_t kerning = 1;

/** Should be found lurking in a header file someehere... */
#ifndef MIN
 #define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif // MIN

/** Forward declarations to keep the compiler happy */
void gpio_irq_handler(uint8_t gpio_num);
static void display_message(char *msg, bool is_error);
static const char* get_wifi_macaddr(void);

/**
 * @brief      Button IRQ handler
 *
 * @param[in]  gpio_num  The gpio number
 */
void gpio_irq_handler(uint8_t gpio_num)
{
    uint32_t now_ms = xTaskGetTickCountFromISR() * portTICK_PERIOD_MS;
    (void) xQueueSendToBackFromISR(button_queue, &now_ms, NULL);
}

/**
 * @brief      Restart the system
 */
static void restart(void)
{
    display_message("Restarting", true);
    /** In case we hang in the restart */
    ssd1306_fade_out(&dev);
    sdk_system_restart();
    display_message("Restart failed", true);
    while(1);
}

/**
 * @brief      Lazy function for clearing the display
 */
static void clear_display(void)
{
    ssd1306_fill_rectangle(&dev, buffer, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, OLED_COLOR_BLACK);
}

/**
 * @brief      Lazy function for refreshing the display
 */
static void refresh_display(void)
{
    ssd1306_load_frame_buffer(&dev, buffer);
}

/**
 * @brief      Draw latest temperatures
 */
static void update_temperatures(void)
{
    xSemaphoreTake(display_sem, portMAX_DELAY);
    clear_display();
    if (display_on) {
        if (temperature[0]) {
           font_draw(&dev, buffer, (char*) temperature, FONT_LARGE, kerning, 0, 0);
        }
        if (forecast[0]) {
            uint32_t width = font_string_width(forecast, FONT_SMALL, kerning);
            font_draw(&dev, buffer, (char*) forecast, FONT_SMALL, kerning, DISPLAY_WIDTH-width, DISPLAY_HEIGHT/2 - small_digits_height/2);
        }
    }
    refresh_display();
    xSemaphoreGive(display_sem);
}

/**
 * @brief      Display status message and happy/sad Mac icon
 *
 * @param      msg    The message
 * @param[in]  is_error  True: display sad Mac, false: display happy Mac
 */
static void display_message(char *msg, bool is_error)
{
    xSemaphoreTake(display_sem, portMAX_DELAY);
    if (msg) {
        printf("%sDisplaying message '%s'\n", is_error ? "Error: " : "", msg);
    }
    clear_display();
    if (display_on) {
        uint8_t char_height = 8;
        if (msg) {
            ssd1306_draw_string(&dev, buffer, font_builtin_fonts[0], sad_mac_width + 2, DISPLAY_HEIGHT/2-char_height/2, msg, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
        }
        ssd1306_sillydraw_bmp(&dev, buffer, is_error ? 0 : DISPLAY_WIDTH/2-happy_mac_width/2 , 0, is_error ? sad_mac_width : happy_mac_width, is_error ? sad_mac_height : happy_mac_height, is_error ? sad_mac_bits : happy_mac_bits);
    }
    refresh_display();
    xSemaphoreGive(display_sem);
}

/**
 * @brief      A task that periodically publishes a heart beat
 *
 * @param      pvParameters  not used
 */
static void heartbeat_task(void *pvParameters)
{
    (void) pvParameters;
    char msg[PUB_MSG_LEN];
    uint32_t count = 0;
    while (1) {
        delay_ms(HEARTBEAT_TIME_MS);
        snprintf((char*) msg, sizeof(msg)-1, "%s-%d", get_wifi_macaddr(), count++);
        if (xQueueSend(publish_queue, (void *)msg, 0) == pdFALSE) {
            /** Usually indicates something is up with the wifi connection,
             *  restart in an attempt to fix it.
             */
            restart();
        }
    }
}

/**
 * @brief      Called when the outside temperature has been received
 *
 * @param      md    MQTT message data
 */
static void handle_temperature_topic(mqtt_message_data_t *md)
{
    mqtt_message_t *message = md->message;
    memset((void*) temperature, 0, sizeof(temperature));
    strncpy(temperature, message->payload, MIN(sizeof(temperature)-1, message->payloadlen));
    update_temperatures();
    printf("Temperature: %s\n", temperature);
}

/**
 * @brief      Called when the 8 hour forecast has been received
 *
 * @param      md    MQTT message data
 */
static void handle_reboot_topic(mqtt_message_data_t *md)
{
    (void) md;
    restart();
}

/**
 * @brief      Called when the 8 hour forecast has been received
 *
 * @param      md    MQTT message data
 */
static void handle_forecast_topic(mqtt_message_data_t *md)
{
    mqtt_message_t *message = md->message;
    memset((void*) forecast, 0, sizeof(forecast));
    strncpy(forecast, message->payload, MIN(sizeof(forecast)-1, message->payloadlen));
    update_temperatures();
    printf("Forecast:    %s\n", forecast);
}

/**
 * @brief      Handle display MQTT topic
 *
 * @param      md    MQTT message data
 */
static void handle_display_topic(mqtt_message_data_t *md)
{
    char payload[32];
    mqtt_message_t *message = md->message;
    memset((void*) payload, 0, sizeof(payload));
    strncpy(payload, message->payload, MIN(sizeof(payload)-1, message->payloadlen));

    if (strcmp(payload, "fadein") == 0) {
        display_dimmed = false;
        ssd1306_fade_in(&dev);
    } else if (strcmp(payload, "fadeout") == 0) {
        display_dimmed = true;
        ssd1306_fade_out(&dev);
    } else if (strcmp(payload, "on") == 0) {
        display_on = true;
        update_temperatures();
    } else if (strcmp(payload, "off") == 0) {
        display_on = false;
        xSemaphoreTake(display_sem, portMAX_DELAY);
        clear_display();
        refresh_display();
        xSemaphoreGive(display_sem);
    }
}

/**
 * @brief      Return MAC address
 *
 * @return     MAC address.
 */
static const char* get_wifi_macaddr(void)
{
    // Use MAC address for Station as unique ID
    static char macaddr[13];
    static bool done = false;
    int8_t i;
    uint8_t x;
    if (done)
        return macaddr;
    if (!sdk_wifi_get_macaddr(STATION_IF, (uint8_t *)macaddr)) {
        return NULL;
    }
    for (i = 5; i >= 0; --i) {
        x = macaddr[i] & 0x0F;
        if (x > 9) x += 7;
        macaddr[i * 2 + 1] = x + '0';
        x = macaddr[i] >> 4;
        if (x > 9) x += 7;
        macaddr[i * 2] = x + '0';
    }
    macaddr[12] = '\0';
    done = true;
    return macaddr;
}

/**
 * @brief      The button handler task. If turned off the display will be
 *             momentarily turned on and then turned off after a slight
 *             delay. The same goes if the display was dimmed.
 *
 * @param      pvParameters  not used
 */
static void button_task(void *pvParameters)
{
    (void) pvParameters;
    uint32_t last = 0;
    /** Take a nap while we connect to wifi */
    delay_ms(5000);
    while(1) {
        uint32_t button_ts;
        xQueueReceive(button_queue, &button_ts, portMAX_DELAY);
        if (last < button_ts - BUTTON_DEBOUNCE_TIME_MS) {
            printf("Button pressed at %dms\r\n", button_ts);
            last = button_ts;
            if (!display_on) {
                printf("  Turning display on\n");
                display_on = true;
                update_temperatures();
                delay_ms(BUTTON_ACTION_TIME_MS);
                /** Might have changed while we took a nap */
                if (!display_on) {
                    printf("  Turning display off\n");
                    display_on = false;
                    update_temperatures();
                }
            } else if (display_dimmed) {
                printf("  Fading in display\n");
                ssd1306_fade_in(&dev);
                update_temperatures();
                delay_ms(BUTTON_ACTION_TIME_MS);
                /** Might have changed while we took a nap */
                if (display_dimmed) {
                    printf("  Fading out display\n");
                    ssd1306_fade_out(&dev);
                    update_temperatures();
                }
            } else {
                printf("  No action taken\n");
            }
        }
    }
}

/**
 * @brief      The MQTT pub/sub main task
 *
 * @param      pvParameters  not used
 */
static void mqtt_task(void *pvParameters)
{
    (void) pvParameters;
    int ret = 0;
    struct mqtt_network network;
    mqtt_client_t client = mqtt_client_default;
    char mqtt_client_id[20];
    uint8_t mqtt_buf[100];
    uint8_t mqtt_readbuf[100];
    mqtt_packet_connect_data_t data = mqtt_packet_connect_data_initializer;

    mqtt_network_new(&network);
    memset(mqtt_client_id, 0, sizeof(mqtt_client_id));
    strcpy(mqtt_client_id, "ESP-");
    strcat(mqtt_client_id, get_wifi_macaddr());

    while(1) {
        xSemaphoreTake(wifi_connected, portMAX_DELAY);
        printf("Connecting to MQTT broker %s\n", MQTT_HOST);
        ret = mqtt_network_connect(&network, MQTT_HOST, MQTT_PORT);
        if (ret) {
            printf("Error: failed to connect to broker (%d)\n", ret);
            /** Occasionally the wifi semaphore will not get locked so we end up in
             *  an infinite loop here spewing error prints until wifi is
             *  reconnected.
             */
            delay_ms(5000);
            taskYIELD();
            continue;
        }
        mqtt_client_new(&client, &network, 5000, mqtt_buf, 100, mqtt_readbuf, 100);

        data.willFlag       = 0;
        data.MQTTVersion    = 3;
        data.clientID.cstring   = mqtt_client_id;
        data.username.cstring   = MQTT_USER;
        data.password.cstring   = MQTT_PASS;
        data.keepAliveInterval  = 10;
        data.cleansession   = 0;
        printf("Connecting to broker\n");
        ret = mqtt_connect(&client, &data);
        if (ret) {
            printf("Error: failed to connect to broker (%d)\n", ret);
            mqtt_network_disconnect(&network);
            taskYIELD();
            continue;
        }
        printf("Connected to broker\n");
        mqtt_subscribe(&client, OUTSIDE_TEMP_TOPIC, MQTT_QOS1, handle_temperature_topic);
        mqtt_subscribe(&client, OUTSIDE_TEMP_FORECAST_TOPIC, MQTT_QOS1, handle_forecast_topic);
        mqtt_subscribe(&client, REBOOT_TOPIC, MQTT_QOS1, handle_reboot_topic);
        mqtt_subscribe(&client, DISPLAY_TOPIC, MQTT_QOS1, handle_display_topic);
        xQueueReset(publish_queue);

        while(1) {
            uint8_t msg[PUB_MSG_LEN];
            memset((void*) msg, 0, PUB_MSG_LEN);
            while(xQueueReceive(publish_queue, (void*)msg, 0) == pdTRUE) {
                printf("Publishing message '%s' on topic '%s'\n", msg, HEARTBEAT_TOPIC);
                mqtt_message_t message;
                message.payload = msg;
                message.payloadlen = PUB_MSG_LEN;
                message.dup = 0;
                message.qos = MQTT_QOS1;
                message.retained = 0;
                ret = mqtt_publish(&client, HEARTBEAT_TOPIC, &message);
                if (ret != MQTT_SUCCESS) {
                    printf("Error: failed to publish message (%d)\n", ret);
                    break;
                }
            }

            ret = mqtt_yield(&client, 1000);
            if (ret == MQTT_DISCONNECTED)
                break;
        }
        printf("Broker connection dropped, request restart\n");
        mqtt_network_disconnect(&network);
        taskYIELD();
    }
}

/**
 * @brief      A task to check wifi connection
 *
 * @param      pvParameters  not used
 */
static void wifi_task(void *pvParameters)
{
    (void) pvParameters;
    uint8_t status  = 0;
    uint8_t retries = 30;
    uint32_t last_connect = 0;
    struct sdk_station_config config = {
        .ssid = WIFI_SSID,
        .password = WIFI_PASS,
    };

    printf("Wifi: connecting\n");
    display_message(NULL, false);

    sdk_wifi_set_opmode(STATION_MODE);
    sdk_wifi_station_set_config(&config);

    while(1) {
        while ((status != STATION_GOT_IP) && (retries)) {
            status = sdk_wifi_station_get_connect_status();
            switch(status) {
                case STATION_IDLE:
                    printf("Wifi: idle\n");
                    break;
                case STATION_CONNECTING:
                    printf("Wifi: connecting\n");
                    break;
                case STATION_WRONG_PASSWORD:
                    display_message("Wrong password", true);
                    break;
                case STATION_NO_AP_FOUND:
                    display_message("AP not found", true);
                    break;
                case STATION_CONNECT_FAIL:
                    display_message("Connect failed", true);
                    break;
                case STATION_GOT_IP:
                    printf("Wifi: got IP\n");
                    display_message(NULL, false);
                    last_connect = get_time_ms();
                    xSemaphoreGive(wifi_connected);
                    taskYIELD();
                    break;
            }
            delay_ms(1000);
            retries--;
        }

        while ((status = sdk_wifi_station_get_connect_status()) == STATION_GOT_IP) {
            xSemaphoreGive(wifi_connected);
            taskYIELD();
        }
        display_message("Wifi disconnected", true);
        if (get_time_ms() - last_connect > WIFI_RESTART_TIME_MS) {
            printf("No wifi connection within %ds, restarting...\n", WIFI_RESTART_TIME_MS/1000);
            restart();
        }
        sdk_wifi_station_disconnect();
        retries = 30;
        delay_ms(1000);
        /** @todo: added this as a feeble attempt to reconnect to wifi as it
         *  sometimes fails */
        sdk_wifi_set_opmode(STATION_MODE);
        sdk_wifi_station_set_config(&config);
    }
}

/**
 * @brief      Initialize the button IRQ
 */
static void button_init(void)
{
    gpio_set_pullup(GPIO_BUTTON, true, false);
    gpio_set_interrupt(GPIO_BUTTON, GPIO_INTTYPE_EDGE_NEG, gpio_irq_handler);
}

/**
 * @brief      Initialize the OLED driver
 */
static void oled_init(void)
{
    i2c_init(I2C_BUS, SCL_PIN, SDA_PIN, I2C_FREQ_400K);
    do {
        if (ssd1306_init(&dev)) {
            printf("Error: ssd1306_init failed\n");
            // An error occured, while performing SSD1306 init (E.g device not found etc.)
            break;
        }
        ssd1306_fill_rectangle(&dev, buffer, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, OLED_COLOR_BLACK);
        ssd1306_load_frame_buffer(&dev, buffer);
        ssd1306_set_whole_display_lighting(&dev, false);
    } while(0);
}

/**
 * @brief      Good old user init code
 */
void user_init(void)
{
    uart_set_baud(0, 115200);
    printf("SDK version:%s\n", sdk_system_get_sdk_version());
    oled_init();
    button_init();
    vSemaphoreCreateBinary(wifi_connected);
    vSemaphoreCreateBinary(display_sem);
    publish_queue = xQueueCreate(3, PUB_MSG_LEN);
    button_queue = xQueueCreate(1, sizeof(uint32_t));
    xTaskCreate(&wifi_task, "wifi_task",  256, NULL, 2, NULL);
    xTaskCreate(&heartbeat_task, "heartbeat_task", 256, NULL, 3, NULL);
    xTaskCreate(&mqtt_task, "mqtt_task", 1024, NULL, 4, NULL);
    xTaskCreate(&button_task, "button_task", 1024, NULL, 4, NULL);
}
