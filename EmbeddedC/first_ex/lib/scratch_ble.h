#ifndef SCRATCH_BLE_H__
#define SCRATCH_BLE_H__

#include "ble_advdata.h"
#include "simple_ble.h"
#include "simple_adv.h"

#define BLE_TX_LEN 8
#define BLE_RX_LEN 5

simple_ble_service_t scratch_service;

simple_ble_char_t tx_char;
simple_ble_char_t rx_char;
simple_ble_char_t debug_char;
simple_ble_char_t motor_char;

uint8_t tx_buff[BLE_TX_LEN];
uint8_t rx_buff[BLE_RX_LEN];
uint8_t tmp_buff[BLE_RX_LEN];
uint8_t motor_buff[2];
uint32_t debug_buff;

simple_ble_config_t ble_config;

void ble_init(void);

void ble_write_data(uint8_t* data, uint8_t len);

void ble_start_advertising(void);

void ble_stop_advertising(void);

void services_init(void);

void ble_evt_write(ble_evt_t* p_ble_evt);

void set_callback(void(*m)());


#endif
