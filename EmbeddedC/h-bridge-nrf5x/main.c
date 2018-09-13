// Global C libraries
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

// Nordic libraries
#include "nordic_common.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_adc.h"
#include "app_button.h"
#include "app_gpiote.h"
#include "app_timer.h"
#include "app_util_platform.h"
#include "softdevice_handler.h"
#include "app_pwm.h"

// nrf5x-base libraries
#include "simple_timer.h"
#include "device_info_service.h"

// Local libraries
#include "lib/scratch_ble.h"
#include "lib/lsm6ds3.h"

#define TILT_THRESHOLD 30 // in degrees

// I/O pin definitions
#define LED0 17
#define LED1 8
#define LED2 29
#define LED3 22
#define TEST1 8
#define TEST2 9
#define BTN1 9
#define BTN2 21
#define IMU_INT1 30

#define ADC_BUFFER_SIZE 4
#define ADC_TIMER_PRESCALER 0
#define ADC_TIMER_OP_QUEUE_SIZE 4
#define ADC_TIMER_RATE APP_TIMER_TICKS(1, ADC_TIMER_PRESCALER)



static nrf_adc_value_t adc_buffer[ADC_BUFFER_SIZE];
static nrf_drv_adc_channel_t pot_adc_config = NRF_DRV_ADC_DEFAULT_CHANNEL(NRF_ADC_CONFIG_INPUT_3);
static nrf_drv_adc_channel_t dist_adcl_config = NRF_DRV_ADC_DEFAULT_CHANNEL(NRF_ADC_CONFIG_INPUT_2);

#define BUTTON_DEBOUNCE_DELAY 50
#define APP_GPIOTE_MAX_USERS 1

APP_TIMER_DEF(adc_timer_id);
APP_TIMER_DEF(sensor_timer_id);
APP_TIMER_DEF(poweroff_timer_id);
APP_TIMER_DEF(led_timer_id);

APP_PWM_INSTANCE(PWM1,1);

uint8_t connection_status = 0;

const uint8_t CMD_MOTORCW = 0x01;
const uint8_t CMD_MOTORCCW = 0x02;
const uint8_t CMD_BRAKE = 0x03;
const uint8_t CMD_PWR = 0x04;
const uint8_t CMD_TURN = 0x05;

uint16_t sensor_buffer[2] = {0, 0};
int16_t imu_buffer[2] = {0, 0};
uint8_t btn_states[1] = {0};
uint8_t shake_detected = 0;

uint8_t a_in1 = 5;
uint8_t a_in2 = 6;
uint8_t b_in1 = 3;
uint8_t b_in2 = 4;
uint8_t pwm_a = 7;
uint8_t pwm_b = 1;
uint8_t stby = 4;


uint8_t led_pins[4] = {LED0, LED1, LED2, LED3};
uint8_t led_state[4] = {1, 1, 1, 1};
uint8_t selected_led = 0;
uint8_t led_toggle_count = 0;



void gpio_cfg_led(uint32_t pin_number)
{
  nrf_gpio_cfg(
    pin_number,
    NRF_GPIO_PIN_DIR_OUTPUT,
    NRF_GPIO_PIN_INPUT_DISCONNECT,
    NRF_GPIO_PIN_PULLUP,
    NRF_GPIO_PIN_S0H1,
    NRF_GPIO_PIN_NOSENSE);
}

void gpio_cfg_high(uint32_t pin_number) {
    nrf_gpio_cfg(
      pin_number,
      NRF_GPIO_PIN_DIR_OUTPUT,
      NRF_GPIO_PIN_INPUT_DISCONNECT,
      NRF_GPIO_PIN_PULLUP,
      NRF_GPIO_PIN_S0H1,
      NRF_GPIO_PIN_NOSENSE);
}

void pwm_callback(uint8_t pwm_id){

}

/*static void adc_event_handler(nrf_drv_adc_evt_t const* p_event)
{
  if (p_event->type == NRF_DRV_ADC_EVT_DONE) {
    uint32_t i;
    for (i=0; i<p_event->data.done.size; i++) {
      sensor_buffer[i%2] = p_event->data.done.p_buffer[i];
      imu_read();
      imu_buffer[0] = (int16_t) comp_x;
      imu_buffer[1] = (int16_t) comp_y;
    }
  }
}

static void adc_timer_handler(void* p_context)
{
  nrf_drv_adc_buffer_convert(adc_buffer, ADC_BUFFER_SIZE);
  uint32_t i;
  for (i=0; i<ADC_BUFFER_SIZE; i++) {
    nrf_drv_adc_sample();
  }
}*/
void clear_motors(void)
{
    nrf_gpio_pin_clear(5);
    nrf_gpio_pin_clear(6);
}

/*static void poweroff_handler(void * p_context)
{
  clear_leds();
  imu_poweroff();
  APP_ERROR_CHECK(sd_power_system_off());
}

static void ble_update_handler(void* p_context)
{
  // Build the BLE packets
  memset(tmp_buff, 0, sizeof(tmp_buff));
  tmp_buff[0] |= btn_states[0] << 7;              // Frame 1, Bit 8
  tmp_buff[0] |= shake_detected << 6;             // Frame 1, Bit 7
  tmp_buff[0] |= (sensor_buffer[0] >> 4) & 0x3F;  // Frame 1, Bits 1 - 6, Pot bits 5 - 10
  tmp_buff[1] |= (sensor_buffer[0] & 0xF) << 4;   // Frame 2, Bits 5 - 8, Pot bits 1 - 4
  tmp_buff[1] |= (sensor_buffer[1] >> 6) & 0xF;   // Frame 2, Bits 1 - 4, LDR bits 6 - 10
  tmp_buff[2] |= (sensor_buffer[1] & 0x3F) << 2;  // Frame 3, Bits 3 - 8, LDR bits 1 - 5
  tmp_buff[2] |= (imu_buffer[0] < 0) << 1;        // Frame 3, Bit 2, IMU X angle sign
  tmp_buff[2] |= (imu_buffer[1] < 0);             // Frame 3, Bit 1, IMU Y angle sign
  tmp_buff[3] = (uint8_t) abs(imu_buffer[0]);     // Frame 4, Bits 1 - 8, IMU X angle (abs)
  tmp_buff[4] = (uint8_t) abs(imu_buffer[1]);     // Frame 5, Bits 1 - 8, IMU Y angle (abs)

  // Reset shake detection flag
  if (shake_detected) shake_detected = 0;

  ble_write_data(tmp_buff, BLE_TX_LEN);
}

static void led_timer_handler(void* p_context)
{
  uint8_t i;
  if (connection_status == 0) {
    for (i=0; i<4; i++) {
      if (led_state[i]) {
        nrf_gpio_pin_set(led_pins[i]);
        led_state[i] = 0;
      } else {
        nrf_gpio_pin_clear(led_pins[i]);
        led_state[i] = 1;
      }
    }
    //Every cycle
    if (led_toggle_count++ >= 3) {
      app_timer_start(led_timer_id, APP_TIMER_TICKS(2000, APP_TIMER_PRESCALER), NULL);
      led_toggle_count = 0;
    } else {
      app_timer_start(led_timer_id, APP_TIMER_TICKS(250, APP_TIMER_PRESCALER), NULL);
    }
  } else if (connection_status == 2) {
    nrf_gpio_pin_clear(led_pins[selected_led]);
    if (selected_led == 0) {
      selected_led = 3;
    } else {
      selected_led--;
    }
    nrf_gpio_pin_set(led_pins[selected_led]);
    if (++led_toggle_count >= 16) {
      memset(led_state, 0, sizeof(led_state));
      connection_status = 1;
    }
    app_timer_start(led_timer_id, APP_TIMER_TICKS(250, APP_TIMER_PRESCALER), NULL);
  } else {
    if (comp_x > TILT_THRESHOLD) {
      led_state[0] = 0;
      led_state[2] = 1;
    } else if (comp_x < -TILT_THRESHOLD) {
      led_state[0] = 1;
      led_state[2] = 0;
    } else {
      led_state[0] = 0;
      led_state[2] = 0;
    }
    if (comp_y > TILT_THRESHOLD) {
      led_state[1] = 0;
      led_state[3] = 1;
    } else if (comp_y < -TILT_THRESHOLD) {
      led_state[1] = 1;
      led_state[3] = 0;
    } else {
      led_state[1] = 0;
      led_state[3] = 0;
    }
    for (i=0; i<4; i++) {
      if (led_state[i]) {
        nrf_gpio_pin_set(led_pins[i]);
      } else {
        nrf_gpio_pin_clear(led_pins[i]);
      }
    }
    app_timer_start(led_timer_id, APP_TIMER_TICKS(250, APP_TIMER_PRESCALER), NULL);
  }
}

static void adc_config(void)
{
  nrf_drv_adc_config_t config = NRF_DRV_ADC_DEFAULT_CONFIG;
  nrf_drv_adc_init(&config, adc_event_handler);

  pot_adc_config.config.config.input = NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD;
  pot_adc_config.config.config.reference = NRF_ADC_CONFIG_REF_SUPPLY_ONE_THIRD;

  dist_adcl_config.config.config.input = NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD;
  dist_adcl_config.config.config.reference = NRF_ADC_CONFIG_REF_SUPPLY_ONE_THIRD;

  nrf_drv_adc_channel_enable(&pot_adc_config);
  nrf_drv_adc_channel_enable(&dist_adcl_config);
}

static void timer_init(void)
{
  APP_TIMER_INIT(ADC_TIMER_PRESCALER,
                 ADC_TIMER_OP_QUEUE_SIZE,
                 false);

  app_timer_create(&adc_timer_id, APP_TIMER_MODE_REPEATED, adc_timer_handler);
  app_timer_create(&sensor_timer_id, APP_TIMER_MODE_REPEATED, ble_update_handler);
  app_timer_create(&poweroff_timer_id, APP_TIMER_MODE_SINGLE_SHOT, poweroff_handler);
  app_timer_create(&led_timer_id, APP_TIMER_MODE_SINGLE_SHOT, led_timer_handler);
}

static void start_poweroff_timer(void)
{
  app_timer_start(poweroff_timer_id, APP_TIMER_TICKS(15000, APP_TIMER_PRESCALER), NULL);
}

static void stop_poweroff_timer(void)
{
  app_timer_stop(poweroff_timer_id);
}

static void timer_start(void)
{
  app_timer_start(adc_timer_id, ADC_TIMER_RATE, NULL);
  app_timer_start(sensor_timer_id, APP_TIMER_TICKS(50, APP_TIMER_PRESCALER), NULL);
  app_timer_start(led_timer_id, APP_TIMER_TICKS(1000, APP_TIMER_PRESCALER), NULL);
  start_poweroff_timer();
}

static void button_event_handler(uint8_t pin, uint8_t action)
{
  if (pin == BTN1) {

    // If the button is pressed while not connected, reset the poweroff timer
    if (connection_status == 0) {
      stop_poweroff_timer();
      start_poweroff_timer();
    }

    if (action == APP_BUTTON_PUSH)
      btn_states[0] = 1;
    else if (action == APP_BUTTON_RELEASE)
      btn_states[0] = 0;

  }
}

static void buttons_init(void)
{
  static app_button_cfg_t p_button[] = {
    {BTN1, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_NOPULL, button_event_handler},
    {BTN2, APP_BUTTON_ACTIVE_LOW, NRF_GPIO_PIN_NOPULL, button_event_handler}
  };
  app_button_init(p_button, sizeof(p_button) / sizeof(p_button[0]), BUTTON_DEBOUNCE_DELAY);
  app_button_enable();
}

void imu_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  shake_detected = 1;
}

void ble_evt_connected(ble_evt_t* p_ble_evt)
{
  ble_stop_advertising();
  stop_poweroff_timer();
  connection_status = 2;
  clear_leds();
  led_toggle_count = 0;
  selected_led = 0;
}

void ble_evt_disconnected(ble_evt_t* p_ble_evt)
{
  app_timer_start(led_timer_id, APP_TIMER_TICKS(1000, APP_TIMER_PRESCALER), NULL);
  start_poweroff_timer();
  connection_status = 0;
  memset(led_state, 0, sizeof(led_state));
}*/

void motorLogic(uint8_t m_buffer[2])
{
  if (motor_buff[0] == CMD_MOTORCW) {
    drive_motorcw(m_buffer[1]);
  }
  else if(motor_buff[0] == CMD_MOTORCCW){
    drive_motorccw(m_buffer[1]);
  }
  else if (motor_buff[0]  == CMD_BRAKE){
    brake();
  }
  else if (motor_buff[0]  == CMD_PWR){
    set_pwr(m_buffer[1]);
  }
  else if (motor_buff[0]  == CMD_TURN){
    turn(m_buffer[1]);
  }
}


void ble_evt_write(ble_evt_t* p_ble_evt)
{
  if (simple_ble_is_char_event(p_ble_evt, &tx_char)) {
      // user wrote to tx characteristic
  }
  if (simple_ble_is_char_event(p_ble_evt,&motor_char)){
    motorLogic(motor_buff);
    /*if (motor_buff[0] == CMD_MOTOR){
        nrf_gpio_pin_set(8);
    }
    else{
        nrf_gpio_pin_clear(8);
    }*/
  }

}



void drive_motorcw(uint8_t state) {
  if(state){
    nrf_gpio_pin_set(a_in1);
    nrf_gpio_pin_clear(a_in2);
  }
  else{
    clear_motors();
  }
}

void drive_motorccw(uint8_t state) {
  if(state){
    nrf_gpio_pin_set(a_in2);
    nrf_gpio_pin_clear(a_in1);
  }
  else{
    clear_motors();
  }
}

void brake(){
  nrf_gpio_pin_set(5);
  nrf_gpio_pin_set(6);
}

void turn(uint8_t angle){

}

void set_pwr(uint8_t power){
  app_pwm_channel_duty_set(&PWM1, 0, power);
}



/*void trial_code()
{
  // GPIOTE user identifier for the example module.
static app_gpiote_user_id_t   m_example_user_id;
// GPIOTE event handler.
static void example_gpiote_event_handler(uint32_t event_pins_low_to_high, uint32_t event_pins_high_to_low);

uint32_t  low_to_high_bitmask = 0x00000000; // Bitmask to be notified of transition from low to high for GPIO 0-3
uint32_t  high_to_low_bitmask = 0x00000000; // Bitmask to be notified of transition from high to low for GPIO 0-2
uint32_t retval;
retval = app_gpiote_user_register(&m_example_user_id,
                                  low_to_high_bitmask,
                                  high_to_low_bitmask,
                                  example_gpiote_event_handler);
if (retval != NRF_SUCCESS)
{ // Failed to register with user with GPIO module!}
retval = app_gpiote_user_enable(m_example_user_id);
if (retval != NRF_SUCCESS) {}
}*/

int main(void)
{
  //gpio_cfg_led(LED0);
  gpio_cfg_led(LED1);
//  gpio_cfg_led(LED2);
//  gpio_cfg_led(LED3);
//  drive_motor();
//  gpio_cfg_led(8);
  clear_leds();
  //set_callback(&drive_motor);

  ble_init();
  //adc_config();
  //imu_init();
  //buttons_init();
  //timer_init();
  //Tilt was in the timer_start below
  //timer_start();

  //StandBy pulled high
  gpio_cfg_high(4);
  nrf_gpio_pin_set(4);




  // Initialize GPIOTE driver
  if (!nrf_drv_gpiote_is_init()) {
    nrf_drv_gpiote_init();
  }
  //Initialize PWM
  app_pwm_config_t pwm1_cfg = APP_PWM_DEFAULT_CONFIG_2CH(5000L,1,7);
  //PWM ARE ACGIVE HIGH
  pwm1_cfg.pin_polarity[0] = APP_PWM_POLARITY_ACTIVE_HIGH;
  pwm1_cfg.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;
  app_pwm_init(&PWM1,&pwm1_cfg,pwm_callback);
  app_pwm_enable(&PWM1);
  app_pwm_channel_duty_set(&PWM1, 0, );

  // Setup interrupt handler for lsm6ds3 INT1
  //nrf_drv_gpiote_in_config_t input_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
  //nrf_drv_gpiote_in_init(IMU_INT1, &input_config, imu_event_handler);
  //nrf_drv_gpiote_in_event_enable(IMU_INT1, true);

  // Ram retention on power off
  NRF_POWER->RAMON = POWER_RAMON_ONRAM0_RAM0On   << POWER_RAMON_ONRAM0_Pos
                   | POWER_RAMON_ONRAM1_RAM1On   << POWER_RAMON_ONRAM1_Pos
                   | POWER_RAMON_OFFRAM0_RAM0Off << POWER_RAMON_OFFRAM0_Pos
                   | POWER_RAMON_OFFRAM1_RAM1Off << POWER_RAMON_OFFRAM1_Pos;

  // Begin advertising BLE peripheral
  ble_start_advertising();

  while (1) {
      power_manage();

  }
}
