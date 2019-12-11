#ifndef __MQTT_CONFIG_H__
#define __MQTT_CONFIG_H__

#define MQTT_HOST "172.16.3.100"
#define MQTT_PORT 1883
#define MQTT_USER NULL
#define MQTT_PASS NULL

/** Topic to receive outside temperature */
#define OUTSIDE_TEMP_TOPIC          "home/temperature/outside"
/** Topic to receive forecasted outside temperature */
#define OUTSIDE_TEMP_FORECAST_TOPIC "home/temperature/forecast"
/** Topic to reboot device */
#define REBOOT_TOPIC                "oledthermometer/reboot"
/** A topic for managing display on, off and display fading */
/** Valid messages are 'fadein', 'fadeout', 'off' and 'on' */
#define DISPLAY_TOPIC               "oledthermometer/display"

/** Heartbeats from the display are published on this topic every
 *  HEARTBEAT_TIME_MS */
#define HEARTBEAT_TOPIC             "oledthermometer/heartbeat"
#define HEARTBEAT_TIME_MS           (60000)

#endif // __MQTT_CONFIG_H__
