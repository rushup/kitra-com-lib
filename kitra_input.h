#ifndef KITRA_INPUT_H
#define KITRA_INPUT_H

#include <stdint.h>
#include <stdbool.h>

#define CHECKSUM_ENABLED 1

typedef enum{
  PARSE_OK,
  PARSE_BAD_CHECKSUM,
  PARSE_BAD_SIZE,
  PARSE_UNDEFINED_CMD,
  PARSE_ERROR
}eparse_result;

typedef enum{
  K_OUTPUT_POWER_UP = 611,
  K_OUTPUT_ACK = 612,
  K_OUTPUT_NACK = 613,
  K_OUTPUT_FIRMWARE_VERSION = 614,
  K_OUTPUT_GET_KITRA_STATUS_RESPONSE = 615,
  K_OUTPUT_DI_READ_STATE = 621,
  K_OUTPUT_DI_STATE_NOTIFICATION = 622,
  K_OUTPUT_ADC_READ_SAMPLE_RESPONSE = 631,
  K_OUTPUT_ADC_SAMPLE_NOTIFICATION = 632,
  K_OUTPUT_ADC_THRESHOLD_NOTIFICATION = 633,
  K_OUTPUT_CAP_READ_STATE_RESPONSE = 641,
  K_OUTPUT_CAP_NOTIFICATION = 642,
  K_OUTPUT_LUX_READ_LUX_RESPONSE = 651,
  K_OUTPUT_LUX_READ_PROX_RESPONSE = 652,
  K_OUTPUT_LUX_NOTIFICATION = 653,
  K_OUTPUT_LUX_MANAGED_NOTIFICATION = 654,
  K_OUTPUT_POS_READ_RAW_RESPONSE = 661,
  K_OUTPUT_POS_READ_EULER_RESPONSE = 662,
  K_OUTPUT_POS_NOTIFICATION_RAW = 663,
  K_OUTPUT_POS_NOTIFICATION_EULER = 664,
  K_OUTPUT_POS_MANAGED_NOTIFICATION = 665,
  K_OUTPUT_POS_READ_CALIBRATION_STATE_RESPONSE = 666,
  K_OUTPUT_POS_READ_STEP_COUNTER_RESPONSE = 667,
  K_OUTPUT_ENV_READ_VALUE_RESPONSE = 671,
  K_OUTPUT_ENV_NOTIFICATION = 672,
  K_OUTPUT_ENV_THRESHOLD_NOTIFICATION = 673,
  K_OUTPUT_MIC_GET_LOCALIZATION_RESPONSE = 681,
  K_OUTPUT_MIC_LOCALIZATION_NOTIFICATION = 682,
  K_OUTPUT_I2C_READ_RESPONSE = 691

}eoutput_cmd;

//SYSTEM
typedef struct{
  uint32_t id;
}k_output_power_up;
#define K_OUTPUT_POWER_UP_N_PARAMS 1
static char* K_OUTPUT_POWER_UP_PARAMS = "%d";

typedef struct{
  uint32_t id;
  uint32_t ref_id;
}k_output_ack;
#define K_OUTPUT_ACK_N_PARAMS 2
static char* K_OUTPUT_ACK_PARAMS = "%d,%d";

typedef struct{
  uint32_t id;
  uint32_t error_code;
  uint32_t ref_id;
}k_output_nack;
#define K_OUTPUT_NACK_N_PARAMS 3
static char* K_OUTPUT_NACK_PARAMS = "%d,%d,%d";


typedef struct{
  uint32_t id;
  uint32_t battery_mv;
  uint8_t battery_usb_plugged;
}k_output_get_kitra_status_response;
#define K_OUTPUT_GET_KITRA_STATUS_RESPONSE_N_PARAMS 3
static char* K_OUTPUT_GET_KITRA_STATUS_RESPONSE_PARAMS = "%d,%d,%hhd";


//INPUT
typedef struct{
  uint32_t id;
  uint16_t hw_version;
  uint16_t fw_version;
  uint16_t extra;
}k_output_firmware_version;
#define K_OUTPUT_FIRMWARE_VERSION_N_PARAMS 4
static char* K_OUTPUT_FIRMWARE_VERSION_PARAMS = "%d,%hd,%hd,%hd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t state;
}k_output_di_read_state;
#define K_OUTPUT_DI_READ_STATE_N_PARAMS 3
static char* K_OUTPUT_DI_READ_STATE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t state;
}k_output_di_state_notification;
#define K_OUTPUT_DI_STATE_NOTIFICATION_N_PARAMS 3
static char* K_OUTPUT_DI_STATE_NOTIFICATION_PARAMS = "%d,%hhd,%hhd";

//ADC
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint16_t sample;
}k_output_adc_read_sample_response;
#define K_OUTPUT_ADC_READ_SAMPLE_RESPONSE_N_PARAMS 3
static char* K_OUTPUT_ADC_READ_SAMPLE_RESPONSE_PARAMS = "%d,%hhd,%hd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint16_t sample;
}k_output_adc_read_sample_notification;
#define K_OUTPUT_ADC_SAMPLE_NOTIFICATION_N_PARAMS 3
static char* K_OUTPUT_ADC_SAMPLE_NOTIFICATION_PARAMS = "%d,%hhd,%hd";

typedef struct{
  uint32_t id;
  uint8_t pin;
}k_output_adc_threshold_notification;
#define K_OUTPUT_ADC_THRESHOLD_NOTIFICATION_N_PARAMS 2
static char* K_OUTPUT_ADC_THRESHOLD_NOTIFICATION_PARAMS = "%d,%hhd";


//CAPACITIVE
typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t state;
}k_output_cap_read_state_response;
#define K_OUTPUT_CAP_READ_STATE_RESPONSE_N_PARAMS 3
static char* K_OUTPUT_CAP_READ_STATE_RESPONSE_PARAMS = "%d,%hhd,%hhd";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t type;
}k_output_cap_notification;
#define K_OUTPUT_CAP_NOTIFICATION_N_PARAMS 3
static char* K_OUTPUT_CAP_NOTIFICATION_PARAMS = "%d,%hhd,%hhd";

//LUX
typedef struct{
  uint32_t id;
  uint8_t pin;
  float lux;
}k_output_lux_read_lux_response;
#define K_OUTPUT_LUX_READ_LUX_RESPONSE_N_PARAMS 3
static char* K_OUTPUT_LUX_READ_LUX_RESPONSE_PARAMS = "%d,%hhd,%.6g";

typedef struct{
  uint32_t id;
  uint8_t pin;
  int32_t prox;
}k_output_lux_read_prox_response;
#define K_OUTPUT_LUX_READ_PROX_RESPONSE_N_PARAMS 3
static char* K_OUTPUT_LUX_READ_PROX_RESPONSE_PARAMS = "%d,%hhd,%d";

typedef struct{
  uint32_t id;
  uint8_t pin;
  uint8_t threshold_prox;
  uint8_t threshold_lux;
  int32_t prox;
  float lux;
}k_output_lux_notification;
#define K_OUTPUT_LUX_NOTIFICATION_N_PARAMS 6
static char* K_OUTPUT_LUX_NOTIFICATION_PARAMS = "%d,%hhd,%hhd,%hhd,%d,%.6g";

typedef struct{
  uint32_t id;
  uint8_t type;
  uint8_t pin_mask;
}k_output_lux_managed_notification;
#define K_OUTPUT_LUX_MANAGED_NOTIFICATION_N_PARAMS 3
static char* K_OUTPUT_LUX_MANAGED_NOTIFICATION_PARAMS = "%d,%hhd,%hhX";

//POSITION (ACCELLEROMETER/GYRO/MAGNET)
typedef struct{
  uint32_t id;
  uint16_t acc_x;
  uint16_t acc_y;
  uint16_t acc_z;
  uint16_t angle_x;
  uint16_t angle_y;
  uint16_t angle_z;
  uint16_t magnet_x;
  uint16_t magnet_y;
  uint16_t magnet_z;
}k_output_pos_read_raw_response;
#define K_OUTPUT_POS_READ_RAW_RESPONSE_N_PARAMS 10
static char* K_OUTPUT_POS_READ_RAW_RESPONSE_PARAMS = "%d,%hd,%hd,%hd,%hd,%hd,%hd,%hd,%hd,%hd";

typedef struct{
  uint32_t id;
  uint16_t roll;
  uint16_t pitch;
  uint16_t yaw;
}k_output_pos_read_euler_response;
#define K_OUTPUT_POS_READ_EULER_RESPONSE_N_PARAMS 4
static char* K_OUTPUT_POS_READ_EULER_RESPONSE_PARAMS = "%d,%hd,%hd,%hd";

typedef struct{
  uint32_t id;
  uint16_t acc_x;
  uint16_t acc_y;
  uint16_t acc_z;
  uint16_t angle_x;
  uint16_t angle_y;
  uint16_t angle_z;
  uint16_t magnet_x;
  uint16_t magnet_y;
  uint16_t magnet_z;
}k_output_pos_notification_raw;
#define K_OUTPUT_POS_NOTIFICATION_RAW_N_PARAMS 10
static char* K_OUTPUT_POS_NOTIFICATION_RAW_PARAMS = "%d,%hd,%hd,%hd,%hd,%hd,%hd,%hd,%hd,%hd";

typedef struct{
  uint32_t id;
  uint16_t roll;
  uint16_t pitch;
  uint16_t yaw;
}k_output_pos_notification_euler;
#define K_OUTPUT_POS_NOTIFICATION_EULER_N_PARAMS 4
static char* K_OUTPUT_POS_NOTIFICATION_EULER_PARAMS = "%d,%hd,%hd,%hd";

typedef struct{
  uint32_t id;
  uint16_t notification_mask;
  uint16_t extra;
}k_output_pos_managed_notification;
#define K_OUTPUT_POS_MANAGED_NOTIFICATION_N_PARAMS 3
static char* K_OUTPUT_POS_MANAGED_NOTIFICATION_PARAMS = "%d,%hX,%hd";

typedef struct{
  uint32_t id;
  uint8_t calibrated;
}k_output_pos_read_calibration_state_response;
#define K_OUTPUT_POS_READ_CALIBRATION_STATE_RESPONSE_N_PARAMS 2
static char* K_OUTPUT_POS_READ_CALIBRATION_STATE_RESPONSE_PARAMS = "%d,%hhd";

typedef struct{
  uint32_t id;
  uint16_t step_counter;
}k_output_pos_read_step_counter_response;
#define K_OUTPUT_POS_READ_STEP_COUNTER_RESPONSE_N_PARAMS 2
static char* K_OUTPUT_POS_READ_STEP_COUNTER_RESPONSE_PARAMS = "%d,%hd";


//ENVIROMENT SENSOR

typedef struct{
  uint32_t id;
  float pressure;
  float temperature;
  float humidity;
  float lux;
}k_output_env_read_value_response;
#define K_OUTPUT_ENV_READ_VALUE_RESPONSE_N_PARAMS 5
static char* K_OUTPUT_ENV_READ_VALUE_RESPONSE_PARAMS = "%d,%.6g,%.6g,%.6g,%.6g";

typedef struct{
  uint32_t id;
  float pressure;
  float temperature;
  float humidity;
  float lux;
}k_output_env_notification;
#define K_OUTPUT_ENV_NOTIFICATION_N_PARAMS 5
static char* K_OUTPUT_ENV_NOTIFICATION_PARAMS = "%d,%.6g,%.6g,%.6g,%.6g";

typedef struct{
  uint32_t id;
  uint8_t sensor;
  uint8_t up_down;
}k_output_env_threshold_notification;
#define K_OUTPUT_ENV_THRESHOLD_NOTIFICATION_N_PARAMS 3
static char* K_OUTPUT_ENV_THRESHOLD_NOTIFICATION_PARAMS = "%d,%hhd,%hhd";

//MIC


typedef struct{
  uint32_t id;
  uint16_t angle;
}k_output_mic_get_localization_response;
#define K_OUTPUT_MIC_GET_LOCALIZATION_RESPONSE_N_PARAMS 2
static char* K_OUTPUT_MIC_GET_LOCALIZATION_RESPONSE_PARAMS = "%d,%hd";

typedef struct{
  uint32_t id;
  uint16_t angle;
}k_output_mic_get_localization_notification;
#define K_OUTPUT_MIC_LOCALIZATION_NOTIFICATION_N_PARAMS 2
static char*  K_OUTPUT_MIC_LOCALIZATION_NOTIFICATION_PARAMS = "%d,%hd";
//I2C


typedef struct{
  uint32_t id;
  uint8_t device_address;
  uint8_t data_address_low;
  uint8_t data_address_high;
  uint8_t data[4];
}k_input_read_response_i2c;
#define K_OUTPUT_I2C_READ_RESPONSE_N_PARAMS 8
static char* K_OUTPUT_I2C_READ_RESPONSE_PARAMS = "%d,%hhX,%hhX,%hhX,%hhX,%hhX,%hhX,%hhX";

#endif
