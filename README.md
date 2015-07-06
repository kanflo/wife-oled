**Wife OLED**
==========

I wanted a display showing the current outside temperature alongside with the forecasted temperature in 8 hours. The I2C OLED driver has been modified to support the 128x32 pixel display I got from eBay. There is support for drawing BMPs, partial BMPs and the characters -.0123456789° in two different font sizes (see font.h).

The device subscribes to the topics `home/temperature/outside` and `home/temperature/forecast` displaying them in the left and right part of the display respectively. For readability I use a large font, [Ubuntu Condensed](http://font.ubuntu.com/#charset-condensed) in sizes 32px and 28px.

This is a copy of (rather than a clone of) Tuan PM's MQTT example for the ESP8266.
