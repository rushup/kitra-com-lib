#ifndef KITRA_INPUT_H
#define KITRA_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "kitra_packet_generator.h"

#define CHECKSUM_ENABLED 1

typedef enum{
  PARSE_OK,
  PARSE_BAD_CHECKSUM,
  PARSE_BAD_SIZE,
  PARSE_UNDEFINED_CMD,
  PARSE_ERROR
}eparse_result;

typedef enum{
  K_INPUT_CHANGE_BAUD_RATE = 511,
  K_INPUT_GET_FIRMWARE_VERSION = 512,
  K_INPUT_START_FW_UPDATE = 513,
  K_INPUT_GET_KITRA_STATUS = 515,
  K_INPUT_KITRA_RESET = 516,
  K_INPUT_KITRA_SLEEP = 517,
  K_INPUT_DI_ENABLE_DISABLE = 521,
  K_INPUT_DI_READ_STATE = 522,
  K_INPUT_DI_CONFIGURE_ACTIVATION = 523,
  K_INPUT_ADC_ENABLE_DISABLE = 531,
  K_INPUT_ADC_CHANGE_MODE = 532,
  K_INPUT_ADC_CHANGE_CONFIGURATION = 533,
  K_INPUT_ADC_READ_LAST_SAMPLE = 534,
  K_INPUT_ADC_SET_NOTIFICATION = 535,
  K_INPUT_DO_ENABLE_DISABLE = 541,
  K_INPUT_DO_CHANGE_STATE = 542,
  K_INPUT_DO_INIT_PWM = 543,
  K_INPUT_DO_CHANGE_MODE_PWM = 544,
  K_INPUT_CAP_ENABLE_DISABLE = 551,
  K_INPUT_CAP_READ_STATE = 552,
  K_INPUT_CAP_CONFIGURE_NOTIFICATIONS = 553,
  K_INPUT_CAP_CONFIGURE = 554,
  K_INPUT_HAPTIC_ENABLE_DISABLE = 561,
  K_INPUT_HAPTIC_CONFIGURATION = 562,
  K_INPUT_HAPTIC_CHANGE_MODE = 563,
  K_INPUT_LUX_ENABLE_DISABLE = 571,
  K_INPUT_LUX_READ_LUX = 572,
  K_INPUT_LUX_READ_PROX = 573,
  K_INPUT_LUX_SENSOR_CONFIGURATION = 574,
  K_INPUT_LUX_SENSOR_NOTIFICATIONS = 575,
  K_INPUT_LUX_SENSOR_MANAGED_NOTIFICATIONS = 576,
  K_INPUT_LDRGB_ENABLE_DISABLE = 581,
  K_INPUT_LDRGB_SET = 582,
  K_INPUT_LDRGB_SET_MANAGED = 583,
  K_INPUT_LDRGB_CHANGE_MODE = 584,
  K_INPUT_POS_ENABLE_DISABLE = 591,
  K_INPUT_POS_READ_RAW = 592,
  K_INPUT_POS_READ_EULER_ANGLES = 593,
  K_INPUT_POS_CONFIGURATION = 594,
  K_INPUT_POS_READ_CALIBRATION_STATE = 595,
  K_INPUT_POS_READ_STEP_COUNTER = 596,
  K_INPUT_ENV_ENABLE_DISABLE = 5101,
  K_INPUT_ENV_READ_VALUE = 5102,
  K_INPUT_ENV_ENABLE_NOTIFICATION = 5103,
  K_INPUT_MIC_ENABLE_DISABLE = 5111,
  K_INPUT_MIC_GET_LOCALIZATION_ANGLE = 5112,
  K_INPUT_BUZZ_ENABLE_DISABLE = 5141,
  K_INPUT_BUZZ_CHANGE_STATE = 5142,
  K_INPUT_I2C_READ = 5151,
  K_INPUT_I2C_WRITE = 5152
}einput_cmd;

//SYSTEM
typedef struct{
  uint32_t id;
  uint32_t baud_rate;
}k_input_change_baud_rate;
#define K_INPUT_CHANGE_BAUD_RATE_N_PARAMS 2
static const char* K_INPUT_CHANGE_BAUD_RATE_PARAMS= "%d,%d";

typedef struct{
  uint32_t id;
}k_input_get_firmware_version;
#define K_INPUT_GET_FIRMWARE_VERSION_N_PARAMS 1
static const char* K_INPUT_GET_FIRMWARE_VERSION_PARAMS = "%d";

typedef struct{
  uint32_t id;
}k_input_get_kitra_status;
#define K_INPUT_GET_KITRA_STATUS_N_PARAMS 1
static const char* K_INPUT_GET_KITRA_STATUS_PARAMS = "%d";

typedef struct{
  uint32_t id;
  uint8_t option;
}k_input_kitra_reset;
#define K_INPUT_KITRA_RESET_N_PARAMS 2
static const char* K_INPUT_KITRA_RESET_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t option;
}k_input_kitra_sleep;
#define K_INPUT_KITRA_SLEEP_N_PARAMS 2
static const char* K_INPUT_KITRA_SLEEP_PARAMS = "%d,%hhd";

//INPUT
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
  uint8_t pull;
}k_input_di_enable_disable;
#define K_INPUT_DI_ENABLE_DISABLE_N_PARAMS 4
static const char* K_INPUT_DI_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
}k_input_di_read_state;
#define K_INPUT_DI_READ_STATE_N_PARAMS 2
static const char* K_INPUT_DI_READ_STATE_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
  uint8_t active_state;
  uint32_t sampling_time;
  uint16_t filter_activation;
}k_input_di_configure_activation;
#define K_INPUT_DI_CONFIGURE_ACTIVATION_N_PARAMS 6
static const char* K_INPUT_DI_CONFIGURE_ACTIVATION_PARAMS = "%d,%hhd,%hhd,%hhd,%d,%hd";

//ADC
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
}k_input_adc_enable_disable;
#define K_INPUT_ADC_ENABLE_DISABLE_N_PARAMS 3
static const char* K_INPUT_ADC_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t mode;
}k_input_change_mode;
#define K_INPUT_ADC_CHANGE_MODE_N_PARAMS 3
static const char* K_INPUT_ADC_CHANGE_MODE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint32_t sampling_time;
  uint16_t average;
}k_input_change_configuration;
#define K_INPUT_ADC_CHANGE_CONFIGURATION_N_PARAMS 5
static const char* K_INPUT_ADC_CHANGE_CONFIGURATION_PARAMS = "%d,%hhd,%d,%hd,%hd";

typedef struct{
  uint32_t id;
  uint8_t pin;
}k_input_adc_read_last_sample;
#define K_INPUT_ADC_READ_LAST_SAMPLE_N_PARAMS 2
static const char* K_INPUT_ADC_READ_LAST_SAMPLE_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t notification_enabled;
  uint16_t thresdhold_level;
  uint8_t threshold_notification_enabled;
}k_input_adc_set_notification;
#define K_INPUT_ADC_SET_NOTIFICATION_N_PARAMS 5
static const char* K_INPUT_ADC_SET_NOTIFICATION_PARAMS = "%d,%hhd,%hhd,%hd,%hhd";


//OUTPUT/PWM
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
  uint8_t mode;
}k_input_do_enable_disable;
#define K_INPUT_DO_ENABLE_DISABLE_N_PARAMS 4
static const char* K_INPUT_DO_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t state;
}k_input_do_change_state;
#define K_INPUT_DO_CHANGE_STATE_N_PARAMS 3
static const char* K_INPUT_DO_CHANGE_STATE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint32_t frequency;
  uint8_t percentage;
  uint8_t autostart;
}k_input_do_init_pwm;
#define K_INPUT_DO_INIT_PWM_N_PARAMS 5
static const char* K_INPUT_DO_INIT_PWM_PARAMS = "%d,%hhd,%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t mode;
}k_input_do_change_mode_pwm;
#define K_INPUT_DO_CHANGE_MODE_PWM_N_PARAMS 3
static const char* K_INPUT_DO_CHANGE_MODE_PWM_PARAMS = "%d,%hhd,%hhd";

//CAPACITIVE TOUCH
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
  uint8_t sensitivity;
}k_input_cap_enable_disable;
#define K_INPUT_CAP_ENABLE_DISABLE_N_PARAMS 4
static const char* K_INPUT_CAP_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
}k_input_cap_read_state;
#define K_INPUT_CAP_READ_STATE_N_PARAMS 2
static const char* K_INPUT_CAP_READ_STATE_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t notification_touch_enabled;
  uint8_t notification_press_enabled;
  uint8_t notification_release_enabled;
  uint16_t threshold_level_press;
}k_input_cap_configure_notifications;
#define K_INPUT_CAP_CONFIGURE_NOTIFICATIONS_N_PARAMS 6
static const char* K_INPUT_CAP_CONFIGURE_NOTIFICATIONS_PARAMS = "%d,%hhd,%hhd,%hhd,%hhd,%hd";

typedef struct{
  uint32_t id;
  uint32_t frequency;
}k_input_cap_configure;
#define K_INPUT_CAP_CONFIGURE_N_PARAMS 2
static const char* K_INPUT_CAP_CONFIGURE_PARAMS = "%d,%d";

//LRA HAPTIC
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
}k_input_haptic_enable_disable;
#define K_INPUT_HAPTIC_ENABLE_DISABLE_N_PARAMS 3
static const char* K_INPUT_HAPTIC_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t managed;
  uint8_t percentage;
  uint8_t effect;
  uint8_t autostart;
}k_input_haptic_configuration;
#define K_INPUT_HAPTIC_CONFIGURATION_N_PARAMS 6
static const char* K_INPUT_HAPTIC_CONFIGURATION_PARAMS = "%d,%hhd,%hhd,%hhd,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t mode;
}k_input_haptic_change_mode;
#define K_INPUT_HAPTIC_CHANGE_MODE_N_PARAMS 3
static const char* K_INPUT_HAPTIC_CHANGE_MODE_PARAMS = "%d,%hhd,%hhd";

//PROXIMITY & LUX
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
}k_input_lux_enable_disable;
#define K_INPUT_LUX_ENABLE_DISABLE_N_PARAMS 3
static const char* K_INPUT_LUX_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
}k_input_lux_read_lux;
#define K_INPUT_LUX_READ_LUX_N_PARAMS 2
static const char* K_INPUT_LUX_READ_LUX_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
}k_input_lux_read_prox;
#define K_INPUT_LUX_READ_PROX_N_PARAMS 2
static const char* K_INPUT_LUX_READ_PROX_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t disable_lux;
  uint8_t disable_prox;
  uint8_t extended_range;
}k_input_lux_sensor_configuration;
#define K_INPUT_LUX_SENSOR_CONFIGURATION_N_PARAMS 5
static const char* K_INPUT_LUX_SENSOR_CONFIGURATION_PARAMS = "%d,%hhd,%hhd,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t sample_notification_enabled;
  uint32_t notification_rate;
  uint32_t threshold_level_prox;
  float threshold_level_lux;
  uint8_t threshold_notification_prox_enabled;
  uint8_t threshold_notification_lux_enabled;
}k_input_lux_sensor_notifications;
#define K_INPUT_LUX_SENSOR_NOTIFICATIONS_N_PARAMS 8
static const char* K_INPUT_LUX_SENSOR_NOTIFICATIONS_PARAMS = "%d,%hhd,%hhd,%d,%d,%f,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t enabled;
}k_input_lux_sensor_managed_notifications;
#define K_INPUT_LUX_SENSOR_MANAGED_NOTIFICATIONS_N_PARAMS 2
static const char* K_INPUT_LUX_SENSOR_MANAGED_NOTIFICATIONS_PARAMS = "%d,%hhd";

//LED RGB
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t enabled;
}k_input_ldrgb_enable_disable;
#define K_INPUT_LDRGB_ENABLE_DISABLE_N_PARAMS 3
static const char* K_INPUT_LDRGB_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint32_t color;
  uint8_t intensity;
  uint8_t autostart;
}k_input_ldrgb_set;
#define K_INPUT_LDRGB_SET_N_PARAMS 5
static const char* K_INPUT_LDRGB_SET_PARAMS = "%d,%hhd,%X,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t effect;
  uint32_t color_override;
  uint8_t intensity_override;
  uint32_t duration;
  uint8_t loop;
  uint32_t loop_delay;
  uint8_t autostart;
}k_input_ldrgb_set_managed;
#define K_INPUT_LDRGB_SET_MANAGED_N_PARAMS 9
static const char* K_INPUT_LDRGB_SET_MANAGED_PARAMS = "%d,%hhd,%hhd,%X,%hhd,%d,%hhd,%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t mode;
}k_input_ldrgb_change_mode;
#define K_INPUT_LDRGB_CHANGE_MODE_N_PARAMS 3
static const char* K_INPUT_LDRGB_CHANGE_MODE_PARAMS = "%d,%hhd,%hhd";

//POSITION SENSOR (ACCELLEROMETER/GYRO/MAGNET)
typedef struct{
  uint32_t id;
  uint8_t enabled;
}k_input_pos_enable_disable;
#define K_INPUT_POS_ENABLE_DISABLE_N_PARAMS 2
static const char* K_INPUT_POS_ENABLE_DISABLE_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint16_t filter_mask;
}k_input_pos_read_raw;
#define K_INPUT_POS_READ_RAW_N_PARAMS 2
static const char* K_INPUT_POS_READ_RAW_PARAMS = "%d,%hX";

typedef struct{
  uint32_t id;
}k_input_pos_read_euler_angles;
#define K_INPUT_POS_READ_EULER_ANGLES_N_PARAMS 1
static const char* K_INPUT_POS_READ_EULER_ANGLES_PARAMS = "%d";

typedef struct{
  uint32_t id;
  uint8_t enable_raw_notification;
  uint16_t filter_mask_raw;
  uint8_t enable_euler_notification;
  uint32_t sampling_frequency;
  uint16_t notification_mask;
  uint16_t full_scale;
}k_input_pos_configuration;
#define K_INPUT_POS_CONFIGURATION_N_PARAMS 7
static const char* K_INPUT_POS_CONFIGURATION_PARAMS = "%d,%hhd,%hX,%hhd,%d,%hd,%hd";

typedef struct{
  uint32_t id;
}k_input_pos_read_calibration_state;
#define K_INPUT_POS_READ_CALIBRATION_STATE_N_PARAMS 1
static const char* K_INPUT_POS_READ_CALIBRATION_STATE_PARAMS = "%d";

typedef struct{
  uint32_t id;
}k_input_pos_read_step_counter;
#define K_INPUT_POS_READ_STEP_COUNTER_N_PARAMS 1
static const char* K_INPUT_POS_READ_STEP_COUNTER_PARAMS = "%d";

//ENVIROMENT SENSORS
typedef struct{
  uint32_t id;
  uint8_t enabled;
  uint8_t filter_mask;
}k_input_env_enable_disable;
#define K_INPUT_ENV_ENABLE_DISABLE_N_PARAMS 3
static const char* K_INPUT_ENV_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhX";

typedef struct{
  uint32_t id;
  uint8_t filter_mask;
}k_input_env_read_value;
#define K_INPUT_ENV_READ_VALUE_N_PARAMS 2
static const char* K_INPUT_ENV_READ_VALUE_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint8_t enabled;
  uint8_t sensor;
  uint8_t threshold_up_enabled;
  uint8_t threshold_down_enabled;
  float threshold_value;
}k_input_env_enable_notification;
#define K_INPUT_ENV_ENABLE_NOTIFICATION_N_PARAMS 2
static const char* K_INPUT_ENV_ENABLE_NOTIFICATION_PARAMS = "%d,%hhd,%hhd,%hhd,%hhd,%f";

//MIC
typedef struct{
  uint32_t id;
  uint8_t mode;
  uint8_t filter_mask;
  uint8_t notification_enabled;
  uint32_t notification_freq;
}k_input_mic_enable_disable;
#define K_INPUT_MIC_ENABLE_DISABLE_N_PARAMS 5
static const char* K_INPUT_MIC_ENABLE_DISABLE_PARAMS = "%d,%hhd,%hhX,%hhd,%d";

typedef struct{
  uint32_t id;
}k_input_mic_get_localization_angle;
#define K_INPUT_MIC_GET_LOCALIZATION_ANGLE_N_PARAMS 1
static const char* K_INPUT_MIC_GET_LOCALIZATION_ANGLE_PARAMS = "%d";

//BUZZER
typedef struct{
  uint32_t id;
  uint8_t enabled;
}k_input_buzz_enable_disable;
#define K_INPUT_BUZZ_ENABLE_DISABLE_N_PARAMS 2
static const char* K_INPUT_BUZZ_ENABLE_DISABLE_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint32_t frequency;
  uint8_t duty_cycle;
  uint32_t toggle_ms;
}k_input_buzz_change_state;
#define K_INPUT_BUZZ_CHANGE_STATE_N_PARAMS 4
static const char* K_INPUT_BUZZ_CHANGE_STATE_PARAMS = "%d,%d,%hhd,%d"; 

typedef struct{
  uint32_t id;
}k_input_start_fw_update;
#define K_INPUT_START_FW_UPDATE_N_PARAMS 1
static const char* K_INPUT_START_FW_UPDATE_PARAMS = "%d";

typedef struct{
  uint32_t id;
  uint8_t device_address;
  uint8_t data_address_low;
  uint8_t data_address_high;
  uint8_t size;
}k_input_read_i2c;
#define K_INPUT_I2C_READ_N_PARAMS 5
static const char* K_INPUT_I2C_READ_PARAMS = "%d,%hhX,%hhX,%hhX,%hhd";

typedef struct{
  uint32_t id;
  uint8_t device_address;
  uint8_t data_address_low;
  uint8_t data_address_high;
  uint8_t data[4];
}k_input_write_i2c;
#define K_INPUT_I2C_WRITE_N_PARAMS 8
static const char* K_INPUT_I2C_WRITE_PARAMS = "%d,%hhX,%hhX,%hhX,%hhX,%hhX,%hhX,%hhX";

#if ADD_MARZIO_CODE == 1
typedef struct{
  uint32_t id;
}k_input_pos_peak_detector;
#define K_INPUT_POS_PEAK_DETECTOR_N_PARAMS 1
static const char* K_INPUT_POS_PEAK_DETECTOR_PARAMS = "%d";
#endif


eparse_result k_parse_packet(char* packet,void* k_obj, uint32_t* packet_size, uint32_t* optional_mask);
eparse_result k_parse_packet_safe(const char* _packet,void* k_obj, uint32_t* packet_size, uint32_t* optional_mask);

#ifdef __cplusplus
}
#endif

#endif
