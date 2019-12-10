**Wife OLED**
==========

I wanted a display showing the current outside temperature alongside with the forecasted temperature in 8 hours.

The device subscribes to the topics `home/temperature/outside` and `home/temperature/forecast` displaying them in the left and right part of the display respectively. For readability I use a large font, [Ubuntu Condensed](http://font.ubuntu.com/#charset-condensed) in sizes 32px and 28px.

**Building**

Clone this repo:

```
git clone https://github.com/kanflo/wife-oled.git
cd wife-oled
git submodule init && git submodule update

```

Set the SSID configuration of EOR by adding the following to the file ```esp-open-rtos/include/private_ssid_config.h```:

```
#define WIFI_SSID "my ssid"
#define WIFI_PASS "my password"
```

Configure the MQTT stuff in ```mqtt_config.h```

Now ```make``` and ```make flash```
