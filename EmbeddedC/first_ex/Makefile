PROJECT_NAME = $(shell basename "$(realpath ./)")

APPLICATION_SRCS = $(notdir $(wildcard ./*.c))
APPLICATION_SRCS += softdevice_handler.c
APPLICATION_SRCS += ble_advdata.c
APPLICATION_SRCS += ble_conn_params.c
APPLICATION_SRCS += app_button.c
APPLICATION_SRCS += app_timer.c
APPLICATION_SRCS += app_error.c
APPLICATION_SRCS += app_util_platform.c
APPLICATION_SRCS += nrf_drv_common.c
APPLICATION_SRCS += nrf_drv_gpiote.c
APPLICATION_SRCS += nrf_drv_adc.c
APPLICATION_SRCS += app_gpiote.c
APPLICATION_SRCS += nrf_drv_clock.c
APPLICATION_SRCS += ble_srv_common.c
APPLICATION_SRCS += nrf_drv_spi.c

APPLICATION_SRCS += led.c

APPLICATION_SRCS += simple_ble.c
APPLICATION_SRCS += simple_adv.c
APPLICATION_SRCS += simple_timer.c
#New Local Library added
APPLICATION_SRCS += scratch_ble.c
APPLICATION_SRCS += lsm6ds3.c

SOFTDEVICE_MODEL = s130
SDK_VERSION = 12

RAM_KB = 32
FLASH_KB = 256

# Arbitrary values for testing
#HW_REVISION = 2.0.1
#FW_REVISION = 3.4.5

#ENABLE_WIRELESS_DFU = 1

TOOLCHAIN_PATH = /usr/local/gcc-arm-none-eabi-6-2017-q1-update/bin/

NRF_BASE_PATH ?= nrf5x-base
LIBRARY_PATHS += . lib $(NRF_BASE_PATH)/include
SOURCE_PATHS += lib

include $(NRF_BASE_PATH)/make/Makefile
