#define KITRA_OUTPUT_C

#include "kitra_output.h"
#include <string.h>
#include "kitra_packet_generator.h"
#include "kitra_small_utility.h"

#define MAX_BUFFER_SIZE 4096

static char buffer_tx[MAX_BUFFER_SIZE];

/*
* @param k_obj
* @param optional_mask  bit as 1 means that must not be transmitted
*/
bool k_send_packet(void* k_obj, uint32_t optional_mask)
{
  char format[40];
  char cks[3];
  uint32_t len;
  uint32_t id = ((k_input_get_firmware_version*) k_obj)->id; //take just id
  
  memset(buffer_tx,0,sizeof(char)*MAX_BUFFER_SIZE);
  strcpy(buffer_tx,"$KITRA,");
  switch(id)
  {
  //SYSTEM
  case K_INPUT_CHANGE_BAUD_RATE:
    strcpy(format,K_INPUT_CHANGE_BAUD_RATE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_change_baud_rate*) k_obj)->id,
           ((k_input_change_baud_rate*) k_obj)->baud_rate
    );
    //sizeof(k_input_change_baud_rate);
    break;
  case K_INPUT_GET_FIRMWARE_VERSION:
    strcpy(format,K_INPUT_GET_FIRMWARE_VERSION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_change_baud_rate*) k_obj)->id
    );
    //sizeof(k_input_get_firmware_version);
    break;
    
  case K_INPUT_START_FW_UPDATE:
    strcpy(format,K_INPUT_START_FW_UPDATE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_start_fw_update*) k_obj)->id
    );
    //sizeof(k_input_start_fw_update);
    break;
    
  case K_INPUT_GET_KITRA_STATUS:
    strcpy(format,K_INPUT_GET_KITRA_STATUS_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_get_kitra_status*) k_obj)->id
    );
    //sizeof(k_input_get_kitra_status);
    break;
  case K_INPUT_KITRA_RESET:
    strcpy(format,K_INPUT_KITRA_RESET_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_kitra_reset*) k_obj)->id,
           ((k_input_kitra_reset*) k_obj)->option
    );
    //sizeof(k_input_kitra_reset);
    break;
  case K_INPUT_KITRA_SLEEP:
    strcpy(format,K_INPUT_KITRA_SLEEP_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_kitra_sleep*) k_obj)->id,
           ((k_input_kitra_reset*) k_obj)->option
    );
    //sizeof(k_input_kitra_sleep);
    break;
  //DIGITAL INPUT
  case K_INPUT_DI_ENABLE_DISABLE:
    strcpy(format,K_INPUT_DI_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_di_enable_disable*) k_obj)->id,
           ((k_input_di_enable_disable*) k_obj)->pin,
           ((k_input_di_enable_disable*) k_obj)->enabled,
           ((k_input_di_enable_disable*) k_obj)->pull
    );
    //sizeof(k_input_di_enable_disable);
    break;
  case K_INPUT_DI_READ_STATE:
    strcpy(format,K_INPUT_DI_READ_STATE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_di_read_state*) k_obj)->id,
           ((k_input_di_read_state*) k_obj)->pin
    );
    //sizeof(k_input_di_read_state);
    break;
  case K_INPUT_DI_CONFIGURE_ACTIVATION:
    strcpy(format,K_INPUT_DI_CONFIGURE_ACTIVATION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_di_configure_activation*) k_obj)->id,
           ((k_input_di_configure_activation*) k_obj)->pin,
           ((k_input_di_configure_activation*) k_obj)->enabled,
           ((k_input_di_configure_activation*) k_obj)->active_state,
           ((k_input_di_configure_activation*) k_obj)->sampling_time,
           ((k_input_di_configure_activation*) k_obj)->filter_activation
    );
    //sizeof(k_input_di_configure_activation);
    break;
  //ADC
  case K_INPUT_ADC_ENABLE_DISABLE:
    strcpy(format,K_INPUT_ADC_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_adc_enable_disable*) k_obj)->id,
           ((k_input_adc_enable_disable*) k_obj)->pin,
           ((k_input_adc_enable_disable*) k_obj)->enabled
    );
    //sizeof(k_input_adc_enable_disable);
    break;
  case K_INPUT_ADC_CHANGE_MODE:
    strcpy(format,K_INPUT_ADC_CHANGE_MODE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_change_mode*) k_obj)->id,
           ((k_input_change_mode*) k_obj)->pin,
           ((k_input_change_mode*) k_obj)->mode
    );
    //sizeof(k_input_change_mode);
    break;
  case K_INPUT_ADC_CHANGE_CONFIGURATION:
    strcpy(format,K_INPUT_ADC_CHANGE_CONFIGURATION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_change_configuration*) k_obj)->id,
           ((k_input_change_configuration*) k_obj)->pin,
           ((k_input_change_configuration*) k_obj)->sampling_time,
           ((k_input_change_configuration*) k_obj)->average
    );
    //sizeof(k_input_change_configuration);
    break;
  case K_INPUT_ADC_READ_LAST_SAMPLE:
    strcpy(format,K_INPUT_ADC_READ_LAST_SAMPLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_adc_read_last_sample*) k_obj)->id,
           ((k_input_adc_read_last_sample*) k_obj)->pin
    );
    //sizeof(k_input_adc_read_last_sample);
    break;
  case K_INPUT_ADC_SET_NOTIFICATION:
    strcpy(format,K_INPUT_ADC_SET_NOTIFICATION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_adc_set_notification*) k_obj)->id,
           ((k_input_adc_set_notification*) k_obj)->pin,
           ((k_input_adc_set_notification*) k_obj)->notification_enabled,
           ((k_input_adc_set_notification*) k_obj)->thresdhold_level,
           ((k_input_adc_set_notification*) k_obj)->threshold_notification_enabled
    );
    //sizeof(k_input_adc_set_notification);
    break;
  //DIGITAL OUTPUT/PWM
  case K_INPUT_DO_ENABLE_DISABLE:
    strcpy(format,K_INPUT_DO_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_do_enable_disable*) k_obj)->id,
           ((k_input_do_enable_disable*) k_obj)->pin,
           ((k_input_do_enable_disable*) k_obj)->enabled,
           ((k_input_do_enable_disable*) k_obj)->mode
    );
    //sizeof(k_input_do_enable_disable);
    break;
  case K_INPUT_DO_CHANGE_STATE:
    strcpy(format,K_INPUT_DO_CHANGE_STATE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_do_change_state*) k_obj)->id,
           ((k_input_do_change_state*) k_obj)->pin,
           ((k_input_do_change_state*) k_obj)->state
    );
    //sizeof(k_input_do_change_state);
    break;
  case K_INPUT_DO_INIT_PWM:
    strcpy(format,K_INPUT_DO_INIT_PWM_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_do_init_pwm*) k_obj)->id,
           ((k_input_do_init_pwm*) k_obj)->pin,
           ((k_input_do_init_pwm*) k_obj)->frequency,
           ((k_input_do_init_pwm*) k_obj)->percentage,
           ((k_input_do_init_pwm*) k_obj)->autostart
    );
    //sizeof(k_input_do_init_pwm);
    break;
  case K_INPUT_DO_CHANGE_MODE_PWM:
    strcpy(format,K_INPUT_DO_CHANGE_MODE_PWM_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_do_change_mode_pwm*) k_obj)->id,
           ((k_input_do_change_mode_pwm*) k_obj)->pin,
           ((k_input_do_change_mode_pwm*) k_obj)->mode
    );
    //sizeof(k_input_do_change_mode_pwm);
    break;
  //CAPACTIVE
  case K_INPUT_CAP_ENABLE_DISABLE:
    strcpy(format,K_INPUT_CAP_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_cap_enable_disable*) k_obj)->id,
           ((k_input_cap_enable_disable*) k_obj)->pin,
           ((k_input_cap_enable_disable*) k_obj)->enabled,
           ((k_input_cap_enable_disable*) k_obj)->sensitivity
    );
    //sizeof(k_input_cap_enable_disable);
    break;
  case K_INPUT_CAP_READ_STATE:
    strcpy(format,K_INPUT_CAP_READ_STATE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_cap_read_state*) k_obj)->id,
           ((k_input_cap_read_state*) k_obj)->pin
    );
    //sizeof(k_input_cap_read_state);
    break;
  case K_INPUT_CAP_CONFIGURE_NOTIFICATIONS:
    strcpy(format,K_INPUT_CAP_CONFIGURE_NOTIFICATIONS_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_cap_configure_notifications*) k_obj)->id,
           ((k_input_cap_configure_notifications*) k_obj)->pin,
           ((k_input_cap_configure_notifications*) k_obj)->notification_touch_enabled,
           ((k_input_cap_configure_notifications*) k_obj)->notification_press_enabled,
           ((k_input_cap_configure_notifications*) k_obj)->notification_release_enabled,
           ((k_input_cap_configure_notifications*) k_obj)->threshold_level_press
    );
    //sizeof(k_input_cap_configure_notifications);
    break;
  case K_INPUT_CAP_CONFIGURE:
    strcpy(format,K_INPUT_CAP_CONFIGURE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_cap_configure*) k_obj)->id,
           ((k_input_cap_configure*) k_obj)->frequency
    );
    //sizeof(k_input_cap_configure);
    break;
  //HAPTIC
  case K_INPUT_HAPTIC_ENABLE_DISABLE:
    strcpy(format,K_INPUT_HAPTIC_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_haptic_enable_disable*) k_obj)->id,
           ((k_input_haptic_enable_disable*) k_obj)->pin,
           ((k_input_haptic_enable_disable*) k_obj)->enabled
    );
    //sizeof(k_input_cap_read_state);
    break;
  case K_INPUT_HAPTIC_CONFIGURATION:
    strcpy(format,K_INPUT_HAPTIC_CONFIGURATION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_haptic_configuration*) k_obj)->id,
           ((k_input_haptic_configuration*) k_obj)->pin,
           ((k_input_haptic_configuration*) k_obj)->managed,
           ((k_input_haptic_configuration*) k_obj)->percentage,
           ((k_input_haptic_configuration*) k_obj)->effect,
           ((k_input_haptic_configuration*) k_obj)->autostart
    );
    //sizeof(k_input_haptic_configuration);
    break;
  case K_INPUT_HAPTIC_CHANGE_MODE:
    strcpy(format,K_INPUT_HAPTIC_CHANGE_MODE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_haptic_change_mode*) k_obj)->id,
           ((k_input_haptic_change_mode*) k_obj)->pin,
           ((k_input_haptic_change_mode*) k_obj)->mode
    );
    //sizeof(k_input_haptic_change_mode);
    break;
  //PROXIMITY & LUX
  case K_INPUT_LUX_ENABLE_DISABLE:
    strcpy(format,K_INPUT_LUX_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_lux_enable_disable*) k_obj)->id,
           ((k_input_lux_enable_disable*) k_obj)->pin,
           ((k_input_lux_enable_disable*) k_obj)->enabled
    );
    //sizeof(k_input_lux_enable_disable);
    break;
  case K_INPUT_LUX_READ_LUX:
    strcpy(format,K_INPUT_LUX_READ_LUX_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_lux_read_lux*) k_obj)->id,
           ((k_input_lux_read_lux*) k_obj)->pin
    );
    //sizeof(k_input_lux_read_lux);
    break;
  case K_INPUT_LUX_READ_PROX:
    strcpy(format,K_INPUT_LUX_READ_PROX_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_lux_read_prox*) k_obj)->id,
           ((k_input_lux_read_prox*) k_obj)->pin
    );
    //sizeof(k_input_lux_read_prox);
    break;
  case K_INPUT_LUX_SENSOR_CONFIGURATION:
    strcpy(format,K_INPUT_LUX_SENSOR_CONFIGURATION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_lux_sensor_configuration*) k_obj)->id,
           ((k_input_lux_sensor_configuration*) k_obj)->pin,
           ((k_input_lux_sensor_configuration*) k_obj)->disable_lux,
           ((k_input_lux_sensor_configuration*) k_obj)->disable_prox,
           ((k_input_lux_sensor_configuration*) k_obj)->extended_range
    );
    //sizeof(k_input_lux_read_prox);
    break;
  case K_INPUT_LUX_SENSOR_NOTIFICATIONS:
    strcpy(format,K_INPUT_LUX_SENSOR_NOTIFICATIONS_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_lux_sensor_notifications*) k_obj)->id,
           ((k_input_lux_sensor_notifications*) k_obj)->pin,
           ((k_input_lux_sensor_notifications*) k_obj)->sample_notification_enabled,
           ((k_input_lux_sensor_notifications*) k_obj)->notification_rate,
           ((k_input_lux_sensor_notifications*) k_obj)->threshold_level_prox,
           ((k_input_lux_sensor_notifications*) k_obj)->threshold_level_lux,
           ((k_input_lux_sensor_notifications*) k_obj)->threshold_notification_prox_enabled,
           ((k_input_lux_sensor_notifications*) k_obj)->threshold_notification_lux_enabled
    );
    //sizeof(k_input_lux_read_prox);
    break;
  case K_INPUT_LUX_SENSOR_MANAGED_NOTIFICATIONS:
    strcpy(format,K_INPUT_LUX_SENSOR_MANAGED_NOTIFICATIONS_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_lux_sensor_managed_notifications*) k_obj)->id,
           ((k_input_lux_sensor_managed_notifications*) k_obj)->enabled
    );
    //sizeof(k_input_lux_read_prox);
    break;
  //LED RGB
  case K_INPUT_LDRGB_ENABLE_DISABLE:
    strcpy(format,K_INPUT_LDRGB_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_ldrgb_enable_disable*) k_obj)->id,
           ((k_input_ldrgb_enable_disable*) k_obj)->pin,
           ((k_input_ldrgb_enable_disable*) k_obj)->enabled
    );
    //sizeof(k_input_ldrgb_enable_disable);
    break;
  case K_INPUT_LDRGB_SET:
    strcpy(format,K_INPUT_LDRGB_SET_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_ldrgb_set*) k_obj)->id,
           ((k_input_ldrgb_set*) k_obj)->pin,
           ((k_input_ldrgb_set*) k_obj)->color,
           ((k_input_ldrgb_set*) k_obj)->intensity,
           ((k_input_ldrgb_set*) k_obj)->autostart
    );
    //sizeof(k_input_ldrgb_set);
    break;
  case K_INPUT_LDRGB_SET_MANAGED:
    strcat(format, K_INPUT_LDRGB_SET_MANAGED_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           &(( k_input_ldrgb_set_managed*) k_obj)->id,
           &(( k_input_ldrgb_set_managed*) k_obj)->effect,
           &(( k_input_ldrgb_set_managed*) k_obj)->color_override,
           &(( k_input_ldrgb_set_managed*) k_obj)->intensity_override,
           &(( k_input_ldrgb_set_managed*) k_obj)->autostart
    );
    //sizeof( k_input_ldrgb_set_managed);
    break;
  case K_INPUT_LDRGB_CHANGE_MODE:
    strcat(format, K_INPUT_LDRGB_CHANGE_MODE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           &(( k_input_ldrgb_change_mode*) k_obj)->id,
           &(( k_input_ldrgb_change_mode*) k_obj)->pin,
           &(( k_input_ldrgb_change_mode*) k_obj)->mode
    );
    //sizeof( k_input_ldrgb_change_mode);
    break;
  //POSITION SENSOR (ACCELLEROMETER ETC...)
  case K_INPUT_POS_ENABLE_DISABLE:
    strcat(format, K_INPUT_POS_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_pos_enable_disable*) k_obj)->id,
           ((k_input_pos_enable_disable*) k_obj)->enabled
    );
    //sizeof(k_input_pos_enable_disable);
    break;
  case K_INPUT_POS_READ_RAW:
    strcat(format, K_INPUT_POS_READ_RAW_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_pos_read_raw*) k_obj)->id,
           ((k_input_pos_read_raw*) k_obj)->filter_mask
    );
    //sizeof(k_input_pos_read_raw);
    break;
  case K_INPUT_POS_READ_EULER_ANGLES:
    strcat(format, K_INPUT_POS_READ_EULER_ANGLES_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_pos_read_euler_angles*) k_obj)->id
    );
    //sizeof(k_input_pos_read_euler_angles);
    break;
  case K_INPUT_POS_CONFIGURATION:
    strcat(format, K_INPUT_POS_CONFIGURATION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_pos_configuration*) k_obj)->id,
           ((k_input_pos_configuration*) k_obj)->enable_raw_notification,
           ((k_input_pos_configuration*) k_obj)->filter_mask_raw,
           ((k_input_pos_configuration*) k_obj)->enable_euler_notification,
           ((k_input_pos_configuration*) k_obj)->sampling_frequency,
           ((k_input_pos_configuration*) k_obj)->notification_mask,
           ((k_input_pos_configuration*) k_obj)->full_scale
    );
    //sizeof(k_input_pos_configuration);
    break;
  case K_INPUT_POS_READ_CALIBRATION_STATE:
    strcat(format, K_INPUT_POS_READ_CALIBRATION_STATE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_pos_read_calibration_state*) k_obj)->id
    );
    //sizeof(k_input_pos_read_calibration_state);
    break;
  case K_INPUT_POS_READ_STEP_COUNTER:
    strcpy(format,K_INPUT_POS_READ_STEP_COUNTER_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_pos_read_step_counter*) k_obj)->id
    );
    //sizeof(k_input_pos_read_step_counter);
    break;
  //ENV SENSORS
  case K_INPUT_ENV_ENABLE_DISABLE:
    strcat(format, K_INPUT_ENV_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_env_enable_disable*) k_obj)->id,
           ((k_input_env_enable_disable*) k_obj)->enabled,
           ((k_input_env_enable_disable*) k_obj)->filter_mask
    );
    //sizeof(k_input_env_enable_disable);
    break;
  case K_INPUT_ENV_READ_VALUE:
    strcat(format, K_INPUT_ENV_READ_VALUE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_env_read_value*) k_obj)->id,
           ((k_input_env_read_value*) k_obj)->filter_mask
    );
    //sizeof(k_input_env_read_value);
    break;
  case K_INPUT_ENV_ENABLE_NOTIFICATION:
    strcat(format, K_INPUT_ENV_ENABLE_NOTIFICATION_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_env_enable_notification*) k_obj)->id,
           ((k_input_env_enable_notification*) k_obj)->enabled,
           ((k_input_env_enable_notification*) k_obj)->sensor,
           ((k_input_env_enable_notification*) k_obj)->threshold_up_enabled,
           ((k_input_env_enable_notification*) k_obj)->threshold_down_enabled,
           ((k_input_env_enable_notification*) k_obj)->threshold_value
    );
    //sizeof(k_input_env_enable_notification);
    break;
  //MIC
  case K_INPUT_MIC_ENABLE_DISABLE:
    strcat(format, K_INPUT_MIC_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_mic_enable_disable*) k_obj)->id,
           ((k_input_mic_enable_disable*) k_obj)->mode,
           ((k_input_mic_enable_disable*) k_obj)->filter_mask,
           ((k_input_mic_enable_disable*) k_obj)->notification_enabled,
           ((k_input_mic_enable_disable*) k_obj)->notification_freq
    );
    //sizeof(k_input_mic_enable_disable);
    break;
  case K_INPUT_MIC_GET_LOCALIZATION_ANGLE:
    strcat(format, K_INPUT_MIC_GET_LOCALIZATION_ANGLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_mic_get_localization_angle*) k_obj)->id
    );
    //sizeof(k_input_mic_get_localization_angle);
    break;
  //BUZZER
  case K_INPUT_BUZZ_ENABLE_DISABLE:
    strcat(format, K_INPUT_BUZZ_ENABLE_DISABLE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_buzz_enable_disable*) k_obj)->id,
           ((k_input_buzz_enable_disable*) k_obj)->enabled
    );
    //sizeof(k_input_buzz_enable_disable);
    break;
  case K_INPUT_BUZZ_CHANGE_STATE:
    strcat(format, K_INPUT_BUZZ_CHANGE_STATE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_buzz_change_state*) k_obj)->id,
           ((k_input_buzz_change_state*) k_obj)->frequency,
           ((k_input_buzz_change_state*) k_obj)->duty_cycle,
           ((k_input_buzz_change_state*) k_obj)->toggle_ms
    );
    //sizeof(k_input_buzz_change_state);
    break;
  //I2C
  case K_INPUT_I2C_READ:
    strcat(format, K_INPUT_I2C_READ_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_read_i2c*) k_obj)->id,
           ((k_input_read_i2c*) k_obj)->device_address,
           ((k_input_read_i2c*) k_obj)->data_address_low,
           ((k_input_read_i2c*) k_obj)->data_address_high,
           ((k_input_read_i2c*) k_obj)->size
    );
    //sizeof(k_input_read_i2c);
    break;
  case K_INPUT_I2C_WRITE:
    strcat(format, K_INPUT_I2C_WRITE_PARAMS);
    kitra_generate_packet(buffer_tx,MAX_BUFFER_SIZE,format,optional_mask,
           ((k_input_write_i2c*) k_obj)->id,
           ((k_input_write_i2c*) k_obj)->device_address,
           ((k_input_write_i2c*) k_obj)->data_address_low,
           ((k_input_write_i2c*) k_obj)->data_address_high,
           ((k_input_write_i2c*) k_obj)->data[0],
           ((k_input_write_i2c*) k_obj)->data[1],
           ((k_input_write_i2c*) k_obj)->data[2],
           ((k_input_write_i2c*) k_obj)->data[3]
    );
    //sizeof(k_input_write_i2c);
    break;
  default:
    return false;
  }
  len = strlen(buffer_tx);
  
  if(len < (MAX_BUFFER_SIZE - 6))
  {
    //add checksum and send
    k_get_checksum(buffer_tx + 1,strlen(buffer_tx),cks);
    buffer_tx[len] = '*';
    memcpy(buffer_tx + len + 1, cks, 2 );
    memcpy(buffer_tx + len + 3, "\r\n" , 2 );
    buffer_tx[len + 5] = 0;

    kitra_platform_send(buffer_tx,strlen(buffer_tx));
    
    return true;
  }
  
  return false;
  
}

#undef KITRA_OUTPUT_C
