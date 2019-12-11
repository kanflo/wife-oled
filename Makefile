PROGRAM = oled_thermometer
EXTRA_COMPONENTS = extras/paho_mqtt_c extras/i2c extras/ssd1306 extras/fonts extras/rboot-ota extras/mbedtls

# The baudrate used for serial communications, defaults to 115200
BAUDRATE ?= 115200

# Modify to your likings
IDIOTA_SERVER ?= 172.16.3.106
IDIOTA_PORT ?= 27532
IDIOTA_CHECK_INTERVAL ?= 1
NODE_ID ?= NULL
NODE_TYPE ?= wifeoled
HW_REV ?= NULL


PROGRAM_INC_DIR = . idiota
PROGRAM_SRC_DIR = . idiota
# This must be set if touching PROGRAM_CFLAGS, lest there will be dragons
PROGRAM_CFLAGS = -Wall -Wl,-EL -nostdlib  -ffunction-sections -fdata-sections -g -O2 -std=gnu99
PROGRAM_CFLAGS += -DCONFIG_BAUDRATE=$(BAUDRATE)
PROGRAM_CFLAGS += -DCONFIG_IDIOTA_SERVER=\"$(IDIOTA_SERVER)\" -DCONFIG_IDIOTA_PORT=\"$(IDIOTA_PORT)\" -DCONFIG_IDIOTA_CHECK_INTERVAL=$(IDIOTA_CHECK_INTERVAL) -DCONFIG_NODE_ID=\"$(NODE_ID)\" -DCONFIG_NODE_TYPE=\"$(NODE_TYPE)\" -DCONFIG_HW_REVISION=\"$(HW_REV)\"

FONTS_ROBOTO_10PT = 1

include esp-open-rtos/common.mk
