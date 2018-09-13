#include "simple_adv.h"
#include "simple_ble.h"

#define BLE_TX_LEN 8
#define BLE_RX_LEN 5

#define DEVICE_NAME "MINE"

#define ADV_INTERVAL 200
#define CONN_MIN_INTERVAL 10
#define CONN_MAX_INTERVAL 50

// service and characteristic handles
simple_ble_service_t scratch_service = {
    .uuid128 = {{0x9C, 0xCD, 0x5A, 0x86, 0xDC, 0xDB, 0xE8, 0xAF,
                 0x8C, 0x7B, 0xDB, 0xDC, 0x5A, 0x86, 0xCD, 0x9C}}

};
//New characterstics
simple_ble_char_t tx_char = {.uuid16 = 0x8701};
simple_ble_char_t rx_char = {.uuid16 = 0x8702};
simple_ble_char_t debug_char = {.uuid16 = 0x8703};
simple_ble_char_t motor_char = {.uuid16 = 0x8704};

uint8_t tx_buff[BLE_TX_LEN];
uint8_t rx_buff[BLE_RX_LEN];
uint8_t motor_buff[2];
uint32_t debug_buff;

void (*mFunc)();

// Intervals for advertising and connections
simple_ble_config_t ble_config = {
    .platform_id       = 0x00,              // used as 4th octect in device BLE address
    .device_id         = DEVICE_ID_DEFAULT,
    .adv_name          = DEVICE_NAME,       // used in advertisements if there is room
    .adv_interval      = MSEC_TO_UNITS(ADV_INTERVAL, UNIT_0_625_MS),
    .min_conn_interval = MSEC_TO_UNITS(CONN_MIN_INTERVAL, UNIT_1_25_MS),
    .max_conn_interval = MSEC_TO_UNITS(CONN_MAX_INTERVAL, UNIT_1_25_MS)
};

void __attribute__((weak)) drive_motor();

void ble_init(void)
{
  simple_ble_init(&ble_config);
}

void ble_start_advertising(void)
{
  simple_adv_service(&scratch_service.uuid_handle);
}

void ble_stop_advertising(void)
{
  advertising_stop();
}

void set_callback(void(*m)()){
  mFunc = m;
  //mFunc();
}

void ble_write_data(uint8_t* data, uint8_t len)
{
  uint8_t i;
  for (i=0; i<len && i<BLE_RX_LEN; i++)
  {
    rx_buff[i] = *(data+i);
  }
  simple_ble_notify_char(&rx_char);
}

// called automatically by simple_ble_init
void services_init(void)
{
  // add led service
  simple_ble_add_service(&scratch_service);

  // add led_off characteristic
  simple_ble_add_characteristic(0, 1, 0, 0, // read, write, notify, vlen
          BLE_TX_LEN, (uint8_t*) tx_buff,
          &scratch_service, &tx_char);

  // add rx characteristic
  simple_ble_add_characteristic(1, 0, 1, 0, // read, write, notify, vlen
          BLE_RX_LEN, (uint8_t*) rx_buff,
          &scratch_service, &rx_char);

  // add debug characteristic
  simple_ble_add_characteristic(1, 0, 1, 0, // read, write, notify, vlen
          1, (uint8_t*) &debug_buff,
          &scratch_service, &debug_char);
  simple_ble_add_characteristic(1, 1, 1, 0,
          2, (uint8_t*) &motor_buff,
          &scratch_service, &motor_char);
}
