#!/usr/bin/python
#
# Pull current weather forecast for given lat/lon from the
# Swedish Meteorological and Hydrological Institute (SMHI)
# Will only work for places in Sweden.
#

import os, time
import requests
import sys
import json
import datetime
import random
import socket
from dateutil import tz
from dateutil.parser import parse
import paho.mqtt.client as mosquitto
from optparse import OptionParser


def getSMHIWeather(lat, lon):
    data = None
    if 0:
        with open("w.json") as f:
            data = f.read()
    else:
        url = "http://opendata-download-metfcst.smhi.se/api/category/pmp1.5g/version/1/geopoint/lat/%s/lon/%s/data.json" % (lat, lon)
        headers = {
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.75.14 (KHTML, like Gecko) Version/7.0.3 Safari/7046A194A'
        }
        r = requests.get(url, headers = headers)
        if r.status_code == 200:
            data = r.text
            with open("w.json", "r+") as f:
                f.write(data)
        else:
            sys.stderr.write("HTTP get failed with %d\n" % (r.status_code))
    if data:
        w = json.loads(data)
        return w["timeseries"]
    else:
        return None

def mqttOnConnect(mosq, obj, rc):
    print "[%s] MQTT Connected" % (datetime.datetime.now(tz.tzlocal()))
#    mosq.subscribe("adsb/proximity/json", 0)

def mqttOnDisconnect(mosq, obj, rc):
    print "[%s] MQTT Disconnected" % (datetime.datetime.now(tz.tzlocal()))

def mqttOnMessage(mosq, obj, msg):
    print "[%s] MQTT Message" % (datetime.datetime.now(tz.tzlocal()))

def mqttOnPublish(mosq, obj, mid):
#    print "[%s] MQTT Published" % (datetime.datetime.now(tz.tzlocal()))
    pass

def mqttOnSubscribe(mosq, obj, mid, granted_qos):
    print "[%s] MQTT Subscribed" % (datetime.datetime.now(tz.tzlocal()))

def main():
    # Find the temperature in futureHourOffset hours
    futureHourOffset = 8

    parser = OptionParser()
    parser.add_option('-m', '--mqtt-host', dest='mqtt_host', help="MQTT broker hostname", default='127.0.0.1')
    parser.add_option('-p', '--mqtt-port', dest='mqtt_port', type="int", help="MQTT broker port number", default=1883)
#    parser.add_option('-u', '--mqtt-user', dest='mqtt_user', help="MQTT broker connect user", default='')
#    parser.add_option('-a', '--mqtt-password', dest='mqtt_password', help="MQTT broker connect password", default='')

    parser.add_option('-v', '--verbose', dest='verbose',  action="store_true", help="Verbose output")
    parser.add_option('-T', '--tz', dest='timezone',  help="Your current timezone", default="Europe/Copenhagen")
    parser.add_option('-l', '--lat', dest='lat', type="float", help="Your latitude", default=0)
    parser.add_option('-L', '--lon', dest='lon', type="float", help="Your longitude", default=0)
    parser.add_option('-t', '--topic', dest='topic', help="The topic to publish the temperature to", default="home/temperature/outside%dhrs" % (futureHourOffset))

    (options, args) = parser.parse_args()

    os.environ["TZ"] = options.timezone
    time.tzset()

    mqttc = mosquitto.Mosquitto("weather-%d" % (random.randint(0, 65535)))
    mqttc.on_message = mqttOnMessage
    mqttc.on_connect = mqttOnConnect
    mqttc.on_disconnect = mqttOnDisconnect
    mqttc.on_publish = mqttOnPublish
    mqttc.on_subscribe = mqttOnSubscribe

    if options.lat == 0 and options.lon == 0:
        sys.stderr.write("I have no ide of where you are, use -l LAT -L LON to override (only works for Sweden though).\n")
        sys.exit(0);

    try:
        mqttc.connect(options.mqtt_host, options.mqtt_port, 60)
    except socket.error as e:
        sys.stderr.write("Could not connect to MQTT broker at %s, use -m HOST to override.\n" % options.mqtt_host)
        sys.exit(0);

    try:
        mqttc.loop_start()
        while True:
            # Get current time with time zone
            now = datetime.datetime.now(tz.tzlocal())
            if 0:
                # Testing: simulate time in the future
                now += datetime.timedelta(hours=14)
            future = now + datetime.timedelta(hours=futureHourOffset)
            if now.hour >= 0 and now.hour < 6:
                tod = "night"
            elif now.hour >= 6 and now.hour < 12:
                tod = "morning"
            elif now.hour >= 12 and now.hour < 18:
                tod = "day"
            elif now.hour >= 18 and now.hour <= 23:
                tod = "evening"

            series = getSMHIWeather(options.lat, options.lon)
            if not series:
                sys.stderr.write("Weather loading failed\n")
            else:
                for w in series:
                    utc = parse(w["validTime"])
                    utc = utc.replace(tzinfo=tz.tzutc())
                    # Convert time zone
                    local = utc.astimezone(tz.tzlocal())
                    if local < future and local + datetime.timedelta(hours=1) >= future:
                        temp = float(w["t"])
                        if temp > -5 and temp < 5:
                            temp = "%.1f" % temp
                        else:
                            temp = "%d" % temp

                        print "[%s] It's %s time, in %d hours the temperature will be %s degrees celcius" % (now, tod, futureHourOffset, temp)

                        mqttc.publish(options.topic, temp, retain=True)
                        mqttc.publish("home/temperature/forecast", temp, retain=True) # Temporary

            time.sleep(30*60)
    except Exception as e:
        sys.stderr.write("Got exception: %s" % (e))
        print traceback.format_exc()


# Ye ol main
main()
