/* main.c -- MQTT client example
*
* Copyright (c) 2014-2015, Tuan PM <tuanpm at live dot com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * Neither the name of Redis nor the names of its contributors may be used
* to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "mqtt.h"
#include "wifi.h"
#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "mem.h"
#include "i2c.h"
#include "i2c_oled.h"
#include "graphics.h"
#include "font.h"

MQTT_Client mqttClient;

#define OUTSIDE_TEMP_TOPIC          "home/temperature/outside"
#define OUTSIDE_TEMP_FORECAST_TOPIC "home/temperature/forecast"
#define SCREEN_FILL_TOPIC           "displays/screenfill"
#define DEBUG_TOPIC                 "displays/wifeoled"

#define ALIVE_TOPIC                 "displays/alive"

#define KERNING   (3)

static char outside_temp[16];
static char outside_temp_forecast[16];


static void ICACHE_FLASH_ATTR sadMac(void)
{
	OLED_ClearBuffer();
	OLED_SillyDrawBMP((128-sad_mac_width)/2, (32-sad_mac_height)/2, sad_mac_width, sad_mac_height, sad_mac_bits);
	OLED_Display();
}

static void ICACHE_FLASH_ATTR displayTemperatures(void)
{
	unsigned int smallWidth = measureString(outside_temp_forecast, FONT_SMALL, KERNING);
	OLED_ClearBuffer();
	drawString(outside_temp, FONT_LARGE, KERNING, 0, 0);
	drawString(outside_temp_forecast, FONT_SMALL, KERNING, 128-smallWidth, 4);
	OLED_Display();
}


void wifiConnectCb(uint8_t status)
{
	if(status == STATION_GOT_IP) {
		MQTT_Connect(&mqttClient);
	} else {
		MQTT_Disconnect(&mqttClient);
	}
}
void mqttConnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Connected\r\n");
	MQTT_Subscribe(client, OUTSIDE_TEMP_TOPIC, 0);
	MQTT_Subscribe(client, OUTSIDE_TEMP_FORECAST_TOPIC, 0);
	MQTT_Subscribe(client, SCREEN_FILL_TOPIC, 1);
	MQTT_Subscribe(client, DEBUG_TOPIC, 1);

    uint8 bssid[6];
    char mac[32];
    wifi_get_macaddr(STATION_IF, bssid);
    os_sprintf(mac, MACSTR, MAC2STR(bssid));
	MQTT_Publish(client, ALIVE_TOPIC, mac, strlen(mac), 0, 0);
}

void mqttDisconnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Disconnected\r\n");
}

void mqttPublishedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Published\r\n");
}

void mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len)
{
	char *topicBuf = (char*)os_zalloc(topic_len+1),
			*dataBuf = (char*)os_zalloc(data_len+1);

	MQTT_Client* client = (MQTT_Client*)args;

	os_memcpy(topicBuf, topic, topic_len);
	topicBuf[topic_len] = 0;

	os_memcpy(dataBuf, data, data_len);
	dataBuf[data_len] = 0;

	INFO("Receive topic: %s, data: %s \r\n", topicBuf, dataBuf);
	if (os_strcmp(topicBuf, OUTSIDE_TEMP_TOPIC) == 0) {
		os_strncpy(outside_temp, dataBuf, sizeof(outside_temp));
		if (os_strcmp(outside_temp, "") == 0) {
			os_strcpy(outside_temp, "-");
		}
		if (os_strcmp(outside_temp, "-") != 0) {
			os_strcat(outside_temp, "/");
		}
		INFO("Outside '%s'\r\n", outside_temp);
		displayTemperatures();
	} else if (os_strcmp(topicBuf, OUTSIDE_TEMP_FORECAST_TOPIC) == 0) {
		os_strncpy(outside_temp_forecast, dataBuf, sizeof(outside_temp));
		if (os_strcmp(outside_temp_forecast, "") == 0) {
			os_strcpy(outside_temp_forecast, "-");
		}
		if (os_strcmp(outside_temp_forecast, "-") != 0) {
			os_strcat(outside_temp_forecast, "/");
		}
		INFO("Forecast '%s'\r\n", outside_temp_forecast);
		displayTemperatures();
	} else if (strcmp(topicBuf, SCREEN_FILL_TOPIC) == 0) {
		// TODO
	} else if (strcmp(topicBuf, DEBUG_TOPIC) == 0) {
		// TODO
	}

	os_free(topicBuf);
	os_free(dataBuf);
}


void user_init(void)
{
	uart_init(BIT_RATE_115200, BIT_RATE_115200);
	os_delay_us(1000000);

	INFO("Hello!\r\n");

  	i2c_init();
  	if (!OLED_Init()) {
	  	INFO("OLED init failed\r\n");
	} else {
		OLED_ClearBuffer();
		OLED_SillyDrawBMP((128-happy_mac_width)/2, (32-happy_mac_height)/2, happy_mac_width, happy_mac_height, happy_mac_bits);
		OLED_Display();

		INFO("Loading config\r\n");
		CFG_Load();

		MQTT_InitConnection(&mqttClient, sysCfg.mqtt_host, sysCfg.mqtt_port, sysCfg.security);
		//MQTT_InitConnection(&mqttClient, "192.168.11.122", 1880, 0);

		MQTT_InitClient(&mqttClient, sysCfg.device_id, sysCfg.mqtt_user, sysCfg.mqtt_pass, sysCfg.mqtt_keepalive, 1);
		//MQTT_InitClient(&mqttClient, "client_id", "user", "pass", 120, 1);

		MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);
		MQTT_OnConnected(&mqttClient, mqttConnectedCb);
		MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
		MQTT_OnPublished(&mqttClient, mqttPublishedCb);
		MQTT_OnData(&mqttClient, mqttDataCb);

		WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);

		INFO("\r\nSystem started ...\r\n");
	}
}
