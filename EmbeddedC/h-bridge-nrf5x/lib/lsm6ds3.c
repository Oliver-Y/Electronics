#include <math.h>

#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "app_timer.h"

#define SPI_SS_PIN 6
#define SPI_MISO_PIN 3
#define SPI_MOSI_PIN 4
#define SPI_SCK_PIN 5

#define RAD_TO_DEG 57.2957795
#define ACCEL_SCALE 2 / 32768.0 // 2G Range
#define ACCEL_ALPHA 0.4

#define APP_TIMER_PRESCALER 0

int16_t accel_x, accel_y, accel_z;
int16_t gyro_x, gyro_y, gyro_z;
double comp_x, comp_y;
uint32_t last_imu_read;

uint32_t current_time;

#define SPI_INSTANCE 0
const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);
volatile bool spi_xfer_done;

uint8_t spi_tx_buff[1];
uint8_t spi_rx_buff[1];

uint32_t spi_write_reg(uint8_t reg, uint8_t data)
{
  uint32_t ret_code;
  nrf_gpio_pin_clear(SPI_SS_PIN);
  spi_tx_buff[0] = reg;
  nrf_drv_spi_transfer(&spi, spi_tx_buff, sizeof(spi_tx_buff), NULL, 0);
  spi_tx_buff[0] = data;
  ret_code = nrf_drv_spi_transfer(&spi, spi_tx_buff, sizeof(spi_tx_buff), NULL, 0);
  nrf_gpio_pin_set(SPI_SS_PIN);
  return ret_code;
}

uint8_t spi_read_reg(uint8_t reg)
{
  nrf_gpio_pin_clear(SPI_SS_PIN);
  spi_tx_buff[0] = reg | 0x80;
  nrf_drv_spi_transfer(&spi, spi_tx_buff, sizeof(spi_tx_buff), NULL, 0);
  nrf_drv_spi_transfer(&spi, NULL, 0, spi_rx_buff, sizeof(spi_rx_buff));
  nrf_gpio_pin_set(SPI_SS_PIN);
  return spi_rx_buff[0];
}

int16_t spi_read16_reg(uint8_t reg)
{
  int16_t output;
  nrf_gpio_pin_clear(SPI_SS_PIN);
  spi_tx_buff[0] = reg | 0x80;
  nrf_drv_spi_transfer(&spi, spi_tx_buff, sizeof(spi_tx_buff), NULL, 0);
  nrf_drv_spi_transfer(&spi, NULL, 0, spi_rx_buff, sizeof(spi_rx_buff));
  output = (int16_t) spi_rx_buff[0];
  nrf_drv_spi_transfer(&spi, NULL, 0, spi_rx_buff, sizeof(spi_rx_buff));
  output |= (int16_t) (spi_rx_buff[0] << 8);
  nrf_gpio_pin_set(SPI_SS_PIN);
  return output;
}

double convertRawAccel(int16_t raw)
{
  return (double) raw * 2 / 32768.0;
}

double convertRawGyro(int16_t raw)
{
  return (double) raw * 4.375 * 2 / 1000;
}

void spi_init(void)
{
  uint32_t err_code;
  nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
  //spi_config.ss_pin = SPI_SS_PIN;
  spi_config.miso_pin = SPI_MISO_PIN;
  spi_config.mosi_pin = SPI_MOSI_PIN;
  spi_config.sck_pin = SPI_SCK_PIN;

  nrf_gpio_cfg_output(SPI_SS_PIN);
  //err_code = nrf_drv_spi_init(&spi, &spi_config, spi_event_handler);
  err_code = nrf_drv_spi_init(&spi, &spi_config, NULL);
  APP_ERROR_CHECK(err_code);
}

void imu_read(void)
{
  double pitch, roll, delta_time;
  uint32_t time_diff;
  accel_x = spi_read16_reg(0x2A) * ACCEL_ALPHA + (accel_x * (1.0 - ACCEL_ALPHA));
  accel_y = spi_read16_reg(0x28) * ACCEL_ALPHA + (accel_y * (1.0 - ACCEL_ALPHA));
  accel_z = spi_read16_reg(0x2C) * ACCEL_ALPHA + (accel_z * (1.0 - ACCEL_ALPHA));
  gyro_x = spi_read16_reg(0x24);
  gyro_y = spi_read16_reg(0x22);
  gyro_z = spi_read16_reg(0x26);

  pitch = atan2(convertRawAccel(accel_x), convertRawAccel(-accel_z)) * RAD_TO_DEG;
  roll = atan2(convertRawAccel(accel_y), convertRawAccel(-accel_z)) * RAD_TO_DEG;

  current_time = app_timer_cnt_get();
  app_timer_cnt_diff_compute(current_time, last_imu_read, &time_diff);
  delta_time = time_diff * (APP_TIMER_PRESCALER + 1) / APP_TIMER_CLOCK_FREQ;

  comp_x = 0.93 * (comp_x + convertRawGyro(gyro_x) * delta_time) + 0.07 * pitch;
  comp_y = 0.93 * (comp_y + convertRawGyro(gyro_y) * delta_time) + 0.07 * roll;

  last_imu_read = app_timer_cnt_get();
}

void imu_init()
{
  //TODO: Check if SPI is already initialized or decouple spi and imu inits
  spi_init();

  spi_read_reg(0x0F);
  // TODO: Check if response == 0x69
  //debug_buff = res;
  //simple_ble_notify_char(&debug_char);

  spi_write_reg(0x10, 0x40);
  spi_write_reg(0x13, 0x80);
  spi_write_reg(0x11, 0x40);

  //Tap detection
  spi_write_reg(0x58, 0x0E);
  spi_write_reg(0x59, 0x09);
  spi_write_reg(0x5A, 0x06);
  spi_write_reg(0x5E, 0x40);
}

void imu_poweroff(void)
{
  spi_write_reg(0x10, 0x00);
  spi_write_reg(0x11, 0x00);
}
