#ifndef LSM6DS3_H_
#define LSM6DS3_H_

#include "nrf_drv_spi.h"

int16_t accel_x, accel_y, accel_z;
int16_t gyro_x, gyro_y, gyro_z;
double comp_x, comp_y;
uint32_t last_imu_read;

const nrf_drv_spi_t spi;
volatile bool spi_xfer_done;

uint8_t spi_rx_buff[1];
uint8_t spi_tx_buff[1];

uint32_t spi_write_reg(uint8_t reg, uint8_t data);

uint8_t spi_read_reg(uint8_t reg);

int16_t spi_read16_reg(uint8_t reg);

double convertRawAccel(int16_t raw);

double convertRawGyro(int16_t raw);

void imu_read(void);

void imu_init(void);

void imu_poweroff(void);

void spi_init(void);

#endif
