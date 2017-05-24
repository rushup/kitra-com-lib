#define KITRA_INPUT_C

#include <string.h>
#include "kitra_input.h"
#include "kitra_output.h"
#include "kitra_packet_generator.h"
#include "kitra_small_utility.h"

char buffer_rx[MAX_BUFFER_SIZE];

eparse_result k_parse_packet_safe(const char* _packet,void* k_obj, uint32_t* packet_size, uint32_t* optional_mask)
{
    eparse_result ris;
    char* packet;
    packet = malloc(strlen(_packet) + 1);
    strcpy(packet,_packet);
    ris = k_parse_packet(packet,k_obj, packet_size, optional_mask);
    free(packet);
    return ris;
}

//return true success, false failure
eparse_result k_parse_packet(char* packet,void* k_obj, uint32_t* packet_size, uint32_t* optional_mask)
{
  char cks[3];
  char format[80];
  uint32_t len = strlen(packet);
  uint32_t id;
  bool generate_ris = false;
  if(len >= MAX_BUFFER_SIZE || len < 13)
    return PARSE_BAD_SIZE;
  
  k_get_checksum(packet + 1, len - 6, cks);
#if CHECKSUM_ENABLED == 1
  if(cks[0] != packet[len - 4] || cks[1] != packet[len - 3]) //bad checksum?
    return PARSE_BAD_CHECKSUM;
#endif
  
  memset(format,0,80);
  sscanf(packet,"%*6[^,],%u",&id);
  strcat(format,"%*s,");
  
  switch(id)
  {
#ifdef KITRA_SERVER
  //SYSTEM
  case K_INPUT_CHANGE_BAUD_RATE:
    strcat(format,K_INPUT_CHANGE_BAUD_RATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_change_baud_rate*) k_obj)->id,
           &((k_input_change_baud_rate*) k_obj)->baud_rate
    );
    *packet_size = sizeof(k_input_change_baud_rate);
    break;
  case K_INPUT_GET_FIRMWARE_VERSION:
    strcat(format,K_INPUT_GET_FIRMWARE_VERSION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_change_baud_rate*) k_obj)->id
    );
    *packet_size = sizeof(k_input_get_firmware_version);
    break;
    
  case K_INPUT_START_FW_UPDATE:
    strcat(format,K_INPUT_START_FW_UPDATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_start_fw_update*) k_obj)->id
    );
    *packet_size = sizeof(k_input_start_fw_update);
    break;
    
  case K_INPUT_GET_KITRA_STATUS:
    strcat(format,K_INPUT_GET_KITRA_STATUS_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_get_kitra_status*) k_obj)->id
    );
    *packet_size = sizeof(k_input_get_kitra_status);
    break;
  case K_INPUT_KITRA_RESET:
    strcat(format,K_INPUT_KITRA_RESET_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_kitra_reset*) k_obj)->id,
           &((k_input_kitra_reset*) k_obj)->option
    );
    *packet_size = sizeof(k_input_kitra_reset);
    break;
  case K_INPUT_KITRA_SLEEP:
    strcat(format,K_INPUT_KITRA_SLEEP_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_kitra_sleep*) k_obj)->id,
           &((k_input_kitra_reset*) k_obj)->option
    );
    *packet_size = sizeof(k_input_kitra_sleep);
    break;
  //DIGITAL INPUT
  case K_INPUT_DI_ENABLE_DISABLE:
    strcat(format,K_INPUT_DI_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_di_enable_disable*) k_obj)->id,
           &((k_input_di_enable_disable*) k_obj)->pin,
           &((k_input_di_enable_disable*) k_obj)->enabled,
           &((k_input_di_enable_disable*) k_obj)->pull
    );
    *packet_size = sizeof(k_input_di_enable_disable);
    break;
  case K_INPUT_DI_READ_STATE:
    strcat(format,K_INPUT_DI_READ_STATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_di_read_state*) k_obj)->id,
           &((k_input_di_read_state*) k_obj)->pin
    );
    *packet_size = sizeof(k_input_di_read_state);
    break;
  case K_INPUT_DI_CONFIGURE_ACTIVATION:
    strcat(format,K_INPUT_DI_CONFIGURE_ACTIVATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_di_configure_activation*) k_obj)->id,
           &((k_input_di_configure_activation*) k_obj)->pin,
           &((k_input_di_configure_activation*) k_obj)->enabled,
           &((k_input_di_configure_activation*) k_obj)->active_state,
           &((k_input_di_configure_activation*) k_obj)->sampling_time,
           &((k_input_di_configure_activation*) k_obj)->filter_activation
    );
    *packet_size = sizeof(k_input_di_configure_activation);
    break;
  //ADC
  case K_INPUT_ADC_ENABLE_DISABLE:
    strcat(format,K_INPUT_ADC_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_adc_enable_disable*) k_obj)->id,
           &((k_input_adc_enable_disable*) k_obj)->pin,
           &((k_input_adc_enable_disable*) k_obj)->enabled
    );
    *packet_size = sizeof(k_input_adc_enable_disable);
    break;
  case K_INPUT_ADC_CHANGE_MODE:
    strcat(format,K_INPUT_ADC_CHANGE_MODE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_change_mode*) k_obj)->id,
           &((k_input_change_mode*) k_obj)->pin,
           &((k_input_change_mode*) k_obj)->mode
    );
    *packet_size = sizeof(k_input_change_mode);
    break;
  case K_INPUT_ADC_CHANGE_CONFIGURATION:
    strcat(format,K_INPUT_ADC_CHANGE_CONFIGURATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_change_configuration*) k_obj)->id,
           &((k_input_change_configuration*) k_obj)->pin,
           &((k_input_change_configuration*) k_obj)->sampling_time,
           &((k_input_change_configuration*) k_obj)->average
    );
    *packet_size = sizeof(k_input_change_configuration);
    break;
  case K_INPUT_ADC_READ_LAST_SAMPLE:
    strcat(format,K_INPUT_ADC_READ_LAST_SAMPLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_adc_read_last_sample*) k_obj)->id,
           &((k_input_adc_read_last_sample*) k_obj)->pin
    );
    *packet_size = sizeof(k_input_adc_read_last_sample);
    break;
  case K_INPUT_ADC_SET_NOTIFICATION:
    strcat(format,K_INPUT_ADC_SET_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_adc_set_notification*) k_obj)->id,
           &((k_input_adc_set_notification*) k_obj)->pin,
           &((k_input_adc_set_notification*) k_obj)->notification_enabled,
           &((k_input_adc_set_notification*) k_obj)->thresdhold_level,
           &((k_input_adc_set_notification*) k_obj)->threshold_notification_enabled
    );
    *packet_size = sizeof(k_input_adc_set_notification);
    break;
  //DIGITAL OUTPUT/PWM
  case K_INPUT_DO_ENABLE_DISABLE:
    strcat(format,K_INPUT_DO_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_do_enable_disable*) k_obj)->id,
           &((k_input_do_enable_disable*) k_obj)->pin,
           &((k_input_do_enable_disable*) k_obj)->enabled,
           &((k_input_do_enable_disable*) k_obj)->mode
    );
    *packet_size = sizeof(k_input_do_enable_disable);
    break;
  case K_INPUT_DO_CHANGE_STATE:
    strcat(format,K_INPUT_DO_CHANGE_STATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_do_change_state*) k_obj)->id,
           &((k_input_do_change_state*) k_obj)->pin,
           &((k_input_do_change_state*) k_obj)->state
    );
    *packet_size = sizeof(k_input_do_change_state);
    break;
  case K_INPUT_DO_INIT_PWM:
    strcat(format,K_INPUT_DO_INIT_PWM_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_do_init_pwm*) k_obj)->id,
           &((k_input_do_init_pwm*) k_obj)->pin,
           &((k_input_do_init_pwm*) k_obj)->frequency,
           &((k_input_do_init_pwm*) k_obj)->percentage,
           &((k_input_do_init_pwm*) k_obj)->autostart
    );
    *packet_size = sizeof(k_input_do_init_pwm);
    break;
  case K_INPUT_DO_CHANGE_MODE_PWM:
    strcat(format,K_INPUT_DO_CHANGE_MODE_PWM_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_do_change_mode_pwm*) k_obj)->id,
           &((k_input_do_change_mode_pwm*) k_obj)->pin,
           &((k_input_do_change_mode_pwm*) k_obj)->mode
    );
    *packet_size = sizeof(k_input_do_change_mode_pwm);
    break;
  //CAPACTIVE
  case K_INPUT_CAP_ENABLE_DISABLE:
    strcat(format,K_INPUT_CAP_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_cap_enable_disable*) k_obj)->id,
           &((k_input_cap_enable_disable*) k_obj)->pin,
           &((k_input_cap_enable_disable*) k_obj)->enabled,
           &((k_input_cap_enable_disable*) k_obj)->sensitivity
    );
    *packet_size = sizeof(k_input_cap_enable_disable);
    break;
  case K_INPUT_CAP_READ_STATE:
    strcat(format,K_INPUT_CAP_READ_STATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_cap_read_state*) k_obj)->id,
           &((k_input_cap_read_state*) k_obj)->pin
    );
    *packet_size = sizeof(k_input_cap_read_state);
    break;
  case K_INPUT_CAP_CONFIGURE_NOTIFICATIONS:
    strcat(format,K_INPUT_CAP_CONFIGURE_NOTIFICATIONS_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_cap_configure_notifications*) k_obj)->id,
           &((k_input_cap_configure_notifications*) k_obj)->pin,
           &((k_input_cap_configure_notifications*) k_obj)->notification_touch_enabled,
           &((k_input_cap_configure_notifications*) k_obj)->notification_press_enabled,
           &((k_input_cap_configure_notifications*) k_obj)->notification_release_enabled,
           &((k_input_cap_configure_notifications*) k_obj)->threshold_level_press
    );
    *packet_size = sizeof(k_input_cap_configure_notifications);
    break;
  case K_INPUT_CAP_CONFIGURE:
    strcat(format,K_INPUT_CAP_CONFIGURE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_cap_configure*) k_obj)->id,
           &((k_input_cap_configure*) k_obj)->frequency
    );
    *packet_size = sizeof(k_input_cap_configure);
    break;
  //HAPTIC
  case K_INPUT_HAPTIC_ENABLE_DISABLE:
    strcat(format,K_INPUT_HAPTIC_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_haptic_enable_disable*) k_obj)->id,
           &((k_input_haptic_enable_disable*) k_obj)->pin,
           &((k_input_haptic_enable_disable*) k_obj)->enabled
    );
    *packet_size = sizeof(k_input_cap_read_state);
    break;
  case K_INPUT_HAPTIC_CONFIGURATION:
    strcat(format,K_INPUT_HAPTIC_CONFIGURATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_haptic_configuration*) k_obj)->id,
           &((k_input_haptic_configuration*) k_obj)->pin,
           &((k_input_haptic_configuration*) k_obj)->managed,
           &((k_input_haptic_configuration*) k_obj)->percentage,
           &((k_input_haptic_configuration*) k_obj)->effect,
           &((k_input_haptic_configuration*) k_obj)->autostart
    );
    *packet_size = sizeof(k_input_haptic_configuration);
    break;
  case K_INPUT_HAPTIC_CHANGE_MODE:
    strcat(format,K_INPUT_HAPTIC_CHANGE_MODE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_haptic_change_mode*) k_obj)->id,
           &((k_input_haptic_change_mode*) k_obj)->pin,
           &((k_input_haptic_change_mode*) k_obj)->mode
    );
    *packet_size = sizeof(k_input_haptic_change_mode);
    break;
  //PROXIMITY & LUX
  case K_INPUT_LUX_ENABLE_DISABLE:
    strcat(format,K_INPUT_LUX_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_lux_enable_disable*) k_obj)->id,
           &((k_input_lux_enable_disable*) k_obj)->pin,
           &((k_input_lux_enable_disable*) k_obj)->enabled
    );
    *packet_size = sizeof(k_input_lux_enable_disable);
    break;
  case K_INPUT_LUX_READ_LUX:
    strcat(format,K_INPUT_LUX_READ_LUX_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_lux_read_lux*) k_obj)->id,
           &((k_input_lux_read_lux*) k_obj)->pin
    );
    *packet_size = sizeof(k_input_lux_read_lux);
    break;
  case K_INPUT_LUX_READ_PROX:
    strcat(format,K_INPUT_LUX_READ_PROX_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_lux_read_prox*) k_obj)->id,
           &((k_input_lux_read_prox*) k_obj)->pin
    );
    *packet_size = sizeof(k_input_lux_read_prox);
    break;
  case K_INPUT_LUX_SENSOR_CONFIGURATION:
    strcat(format,K_INPUT_LUX_SENSOR_CONFIGURATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_lux_sensor_configuration*) k_obj)->id,
           &((k_input_lux_sensor_configuration*) k_obj)->pin,
           &((k_input_lux_sensor_configuration*) k_obj)->disable_lux,
           &((k_input_lux_sensor_configuration*) k_obj)->disable_prox,
           &((k_input_lux_sensor_configuration*) k_obj)->extended_range
    );
    *packet_size = sizeof(k_input_lux_read_prox);
    break;
  case K_INPUT_LUX_SENSOR_NOTIFICATIONS:
    strcat(format,K_INPUT_LUX_SENSOR_NOTIFICATIONS_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_lux_sensor_notifications*) k_obj)->id,
           &((k_input_lux_sensor_notifications*) k_obj)->pin,
           &((k_input_lux_sensor_notifications*) k_obj)->sample_notification_enabled,
           &((k_input_lux_sensor_notifications*) k_obj)->notification_rate,
           &((k_input_lux_sensor_notifications*) k_obj)->threshold_level_prox,
           &((k_input_lux_sensor_notifications*) k_obj)->threshold_level_lux,
           &((k_input_lux_sensor_notifications*) k_obj)->threshold_notification_prox_enabled,
           &((k_input_lux_sensor_notifications*) k_obj)->threshold_notification_lux_enabled
    );
    *packet_size = sizeof(k_input_lux_read_prox);
    break;
  case K_INPUT_LUX_SENSOR_MANAGED_NOTIFICATIONS:
    strcat(format,K_INPUT_LUX_SENSOR_MANAGED_NOTIFICATIONS_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_lux_sensor_managed_notifications*) k_obj)->id,
           &((k_input_lux_sensor_managed_notifications*) k_obj)->enabled
    );
    *packet_size = sizeof(k_input_lux_read_prox);
    break;
  //LED RGB
  case K_INPUT_LDRGB_ENABLE_DISABLE:
    strcat(format,K_INPUT_LDRGB_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_ldrgb_enable_disable*) k_obj)->id,
           &((k_input_ldrgb_enable_disable*) k_obj)->pin,
           &((k_input_ldrgb_enable_disable*) k_obj)->enabled
    );
    *packet_size = sizeof(k_input_ldrgb_enable_disable);
    break;
  case K_INPUT_LDRGB_SET:
    strcat(format,K_INPUT_LDRGB_SET_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_ldrgb_set*) k_obj)->id,
           &((k_input_ldrgb_set*) k_obj)->pin,
           &((k_input_ldrgb_set*) k_obj)->color,
           &((k_input_ldrgb_set*) k_obj)->intensity,
           &((k_input_ldrgb_set*) k_obj)->autostart
    );
    *packet_size = sizeof(k_input_ldrgb_set);
    break;
  case K_INPUT_LDRGB_SET_MANAGED:
    strcat(format, K_INPUT_LDRGB_SET_MANAGED_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &(( k_input_ldrgb_set_managed*) k_obj)->id,
           &(( k_input_ldrgb_set_managed*) k_obj)->pin,
           &(( k_input_ldrgb_set_managed*) k_obj)->effect,
           &(( k_input_ldrgb_set_managed*) k_obj)->color_override,
           &(( k_input_ldrgb_set_managed*) k_obj)->intensity_override,
           &(( k_input_ldrgb_set_managed*) k_obj)->duration,
           &(( k_input_ldrgb_set_managed*) k_obj)->loop,
           &(( k_input_ldrgb_set_managed*) k_obj)->loop_delay,
           &(( k_input_ldrgb_set_managed*) k_obj)->autostart
    );
    *packet_size = sizeof( k_input_ldrgb_set_managed);
    break;
  case K_INPUT_LDRGB_CHANGE_MODE:
    strcat(format, K_INPUT_LDRGB_CHANGE_MODE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &(( k_input_ldrgb_change_mode*) k_obj)->id,
           &(( k_input_ldrgb_change_mode*) k_obj)->pin,
           &(( k_input_ldrgb_change_mode*) k_obj)->mode
    );
    *packet_size = sizeof( k_input_ldrgb_change_mode);
    break;
  //POSITION SENSOR (ACCELLEROMETER ETC...)
  case K_INPUT_POS_ENABLE_DISABLE:
    strcat(format, K_INPUT_POS_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_pos_enable_disable*) k_obj)->id,
           &((k_input_pos_enable_disable*) k_obj)->enabled
    );
    *packet_size = sizeof(k_input_pos_enable_disable);
    break;
  case K_INPUT_POS_READ_RAW:
    strcat(format, K_INPUT_POS_READ_RAW_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_pos_read_raw*) k_obj)->id,
           &((k_input_pos_read_raw*) k_obj)->filter_mask
    );
    *packet_size = sizeof(k_input_pos_read_raw);
    break;
  case K_INPUT_POS_READ_EULER_ANGLES:
    strcat(format, K_INPUT_POS_READ_EULER_ANGLES_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_pos_read_euler_angles*) k_obj)->id
    );
    *packet_size = sizeof(k_input_pos_read_euler_angles);
    break;
  case K_INPUT_POS_CONFIGURATION:
    strcat(format, K_INPUT_POS_CONFIGURATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_pos_configuration*) k_obj)->id,
           &((k_input_pos_configuration*) k_obj)->enable_raw_notification,
           &((k_input_pos_configuration*) k_obj)->filter_mask_raw,
           &((k_input_pos_configuration*) k_obj)->enable_euler_notification,
           &((k_input_pos_configuration*) k_obj)->sampling_frequency,
           &((k_input_pos_configuration*) k_obj)->notification_mask,
           &((k_input_pos_configuration*) k_obj)->full_scale
    );
    *packet_size = sizeof(k_input_pos_configuration);
    break;
  case K_INPUT_POS_READ_CALIBRATION_STATE:
    strcat(format, K_INPUT_POS_READ_CALIBRATION_STATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_pos_read_calibration_state*) k_obj)->id
    );
    *packet_size = sizeof(k_input_pos_read_calibration_state);
    break;
  case K_INPUT_POS_READ_STEP_COUNTER:
    strcat(format,K_INPUT_POS_READ_STEP_COUNTER_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_pos_read_step_counter*) k_obj)->id
    );
    *packet_size = sizeof(k_input_pos_read_step_counter);
    break;
  //ENV SENSORS
  case K_INPUT_ENV_ENABLE_DISABLE:
    strcat(format, K_INPUT_ENV_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_env_enable_disable*) k_obj)->id,
           &((k_input_env_enable_disable*) k_obj)->enabled,
           &((k_input_env_enable_disable*) k_obj)->filter_mask
    );
    *packet_size = sizeof(k_input_env_enable_disable);
    break;
  case K_INPUT_ENV_READ_VALUE:
    strcat(format, K_INPUT_ENV_READ_VALUE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_env_read_value*) k_obj)->id,
           &((k_input_env_read_value*) k_obj)->filter_mask
    );
    *packet_size = sizeof(k_input_env_read_value);
    break;
  case K_INPUT_ENV_ENABLE_NOTIFICATION:
    strcat(format, K_INPUT_ENV_ENABLE_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_env_enable_notification*) k_obj)->id,
           &((k_input_env_enable_notification*) k_obj)->enabled,
           &((k_input_env_enable_notification*) k_obj)->sensor,
           &((k_input_env_enable_notification*) k_obj)->threshold_up_enabled,
           &((k_input_env_enable_notification*) k_obj)->threshold_down_enabled,
           &((k_input_env_enable_notification*) k_obj)->threshold_value,
           &((k_input_env_enable_notification*) k_obj)->notification_freq
    );
    *packet_size = sizeof(k_input_env_enable_notification);
    break;
  //MIC
  case K_INPUT_MIC_ENABLE_DISABLE:
    strcat(format, K_INPUT_MIC_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_mic_enable_disable*) k_obj)->id,
           &((k_input_mic_enable_disable*) k_obj)->mode,
           &((k_input_mic_enable_disable*) k_obj)->mic_out_sel_1_2,
           &((k_input_mic_enable_disable*) k_obj)->notification_enabled,
           &((k_input_mic_enable_disable*) k_obj)->notification_freq,
           &((k_input_mic_enable_disable*) k_obj)->bf_alg_type,
           &((k_input_mic_enable_disable*) k_obj)->bf_gain
    );
    *packet_size = sizeof(k_input_mic_enable_disable);
    break;
  case K_INPUT_MIC_GET_LOCALIZATION_ANGLE:
    strcat(format, K_INPUT_MIC_GET_LOCALIZATION_ANGLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_mic_get_localization_angle*) k_obj)->id
    );
    *packet_size = sizeof(k_input_mic_get_localization_angle);
    break;
  //LED NEOPIXEl
  case K_INPUT_LED_NEOPIXEL_ENABLE_DISABLE:
    strcat(format, K_INPUT_LED_NEOPIXEL_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_led_neopixel_enable_disable*) k_obj)->id,
           &((k_input_led_neopixel_enable_disable*) k_obj)->enabled,
           &((k_input_led_neopixel_enable_disable*) k_obj)->nleds
    );
    *packet_size = sizeof(k_input_led_neopixel_enable_disable);
    break;
  case K_INPUT_LED_NEOPIXEL_SET:
    strcat(format, K_INPUT_LED_NEOPIXEL_SET_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_led_neopixel_set*) k_obj)->id,
           &((k_input_led_neopixel_set*) k_obj)->pin,
           &((k_input_led_neopixel_set*) k_obj)->color,
           &((k_input_led_neopixel_set*) k_obj)->intensity,
           &((k_input_led_neopixel_set*) k_obj)->autostart
    );
    *packet_size = sizeof(k_input_led_neopixel_set);
    break;
  case K_INPUT_LED_NEOPIXEL_CHANGE_MODE:
    strcat(format, K_INPUT_LED_NEOPIXEL_CHANGE_MODE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_led_neopixel_change_mode*) k_obj)->id,
           &((k_input_led_neopixel_change_mode*) k_obj)->mode
    );
    *packet_size = sizeof(k_input_led_neopixel_change_mode);
    break;
  //BUZZER
  case K_INPUT_BUZZ_ENABLE_DISABLE:
    strcat(format, K_INPUT_BUZZ_ENABLE_DISABLE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_buzz_enable_disable*) k_obj)->id,
           &((k_input_buzz_enable_disable*) k_obj)->enabled
    );
    *packet_size = sizeof(k_input_buzz_enable_disable);
    break;
  case K_INPUT_BUZZ_CHANGE_STATE:
    strcat(format, K_INPUT_BUZZ_CHANGE_STATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_buzz_change_state*) k_obj)->id,
           &((k_input_buzz_change_state*) k_obj)->frequency,
           &((k_input_buzz_change_state*) k_obj)->duty_cycle,
           &((k_input_buzz_change_state*) k_obj)->toggle_ms
    );
    *packet_size = sizeof(k_input_buzz_change_state);
    break;
  //I2C
  case K_INPUT_I2C_READ:
    strcat(format, K_INPUT_I2C_READ_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_read_i2c*) k_obj)->id,
           &((k_input_read_i2c*) k_obj)->device_address,
           &((k_input_read_i2c*) k_obj)->data_address_low,
           &((k_input_read_i2c*) k_obj)->data_address_high,
           &((k_input_read_i2c*) k_obj)->size
    );
    *packet_size = sizeof(k_input_read_i2c);
    break;
  case K_INPUT_I2C_WRITE:
    strcat(format, K_INPUT_I2C_WRITE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
           &((k_input_write_i2c*) k_obj)->id,
           &((k_input_write_i2c*) k_obj)->device_address,
           &((k_input_write_i2c*) k_obj)->data_address_low,
           &((k_input_write_i2c*) k_obj)->data_address_high,
           &((k_input_write_i2c*) k_obj)->data[0],
           &((k_input_write_i2c*) k_obj)->data[1],
           &((k_input_write_i2c*) k_obj)->data[2],
           &((k_input_write_i2c*) k_obj)->data[3]
    );
    *packet_size = sizeof(k_input_write_i2c);
    break;
#else
  case K_OUTPUT_POWER_UP:
    //+1 leave room for $
    strcat(format,K_OUTPUT_POWER_UP_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_power_up*) k_obj)->id
    );
    break;
  case K_OUTPUT_ACK:
    strcat(format,K_OUTPUT_ACK_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_ack*) k_obj)->id,
             &((k_output_ack*) k_obj)->ref_id
    );
    break;
  case K_OUTPUT_NACK:
    strcat(format,K_OUTPUT_NACK_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_nack*) k_obj)->id,
             &((k_output_nack*) k_obj)->error_code,
             &((k_output_nack*) k_obj)->ref_id
    );
    break;
  case K_OUTPUT_FIRMWARE_VERSION:
    strcat(format,K_OUTPUT_FIRMWARE_VERSION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_firmware_version*) k_obj)->id,
             &((k_output_firmware_version*) k_obj)->hw_version,
             &((k_output_firmware_version*) k_obj)->fw_version,
             &((k_output_firmware_version*) k_obj)->extra
    );
    break;
  case K_OUTPUT_GET_KITRA_STATUS_RESPONSE:
    strcat(format,K_OUTPUT_GET_KITRA_STATUS_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_get_kitra_status_response*) k_obj)->id,
             &((k_output_get_kitra_status_response*) k_obj)->battery_mv,
             &((k_output_get_kitra_status_response*) k_obj)->battery_usb_plugged
    );
    break;
 //DI
  case K_OUTPUT_DI_READ_STATE:
    strcat(format,K_OUTPUT_DI_READ_STATE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_di_read_state*) k_obj)->id,
             &((k_output_di_read_state*) k_obj)->pin,
             &((k_output_di_read_state*) k_obj)->state
    );
    break;
  case K_OUTPUT_DI_STATE_NOTIFICATION:
    strcat(format,K_OUTPUT_DI_STATE_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_di_state_notification*) k_obj)->id,
             &((k_output_di_state_notification*) k_obj)->pin,
             &((k_output_di_state_notification*) k_obj)->state
    );
    break;
  //ADC
  case K_OUTPUT_ADC_READ_SAMPLE_RESPONSE:
    strcat(format,K_OUTPUT_ADC_READ_SAMPLE_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_adc_read_sample_response*) k_obj)->id,
             &((k_output_adc_read_sample_response*) k_obj)->pin,
             &((k_output_adc_read_sample_response*) k_obj)->sample
    );
    break;
  case K_OUTPUT_ADC_SAMPLE_NOTIFICATION:
    strcat(format,K_OUTPUT_ADC_SAMPLE_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_adc_read_sample_notification*) k_obj)->id,
             &((k_output_adc_read_sample_notification*) k_obj)->pin,
             &((k_output_adc_read_sample_notification*) k_obj)->sample
    );
    break;
  case K_OUTPUT_ADC_THRESHOLD_NOTIFICATION:
    strcat(format,K_OUTPUT_ADC_THRESHOLD_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_adc_threshold_notification*) k_obj)->id,
             &((k_output_adc_threshold_notification*) k_obj)->pin
    );
    break;
  //CAP
  case K_OUTPUT_CAP_READ_STATE_RESPONSE:
    strcat(format,K_OUTPUT_CAP_READ_STATE_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_cap_read_state_response*) k_obj)->id,
             &((k_output_cap_read_state_response*) k_obj)->pin,
             &((k_output_cap_read_state_response*) k_obj)->state
    );
    break;
  case K_OUTPUT_CAP_NOTIFICATION:
    strcat(format,K_OUTPUT_CAP_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_cap_notification*) k_obj)->id,
             &((k_output_cap_notification*) k_obj)->pin,
             &((k_output_cap_notification*) k_obj)->type
    );
    break;
  //BABYBEAR
  case K_OUTPUT_LUX_READ_LUX_RESPONSE:
    strcat(format,K_OUTPUT_LUX_READ_LUX_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_lux_read_lux_response*) k_obj)->id,
             &((k_output_lux_read_lux_response*) k_obj)->pin,
             &((k_output_lux_read_lux_response*) k_obj)->lux
    );
    break;
  case K_OUTPUT_LUX_READ_PROX_RESPONSE:
    strcat(format,K_OUTPUT_LUX_READ_PROX_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_lux_read_prox_response*) k_obj)->id,
             &((k_output_lux_read_prox_response*) k_obj)->pin,
             &((k_output_lux_read_prox_response*) k_obj)->prox
    );
    break;
  case K_OUTPUT_LUX_NOTIFICATION:
    strcat(format,K_OUTPUT_LUX_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_lux_notification*) k_obj)->id,
             &((k_output_lux_notification*) k_obj)->pin,
             &((k_output_lux_notification*) k_obj)->threshold_prox,
             &((k_output_lux_notification*) k_obj)->threshold_lux,
             &((k_output_lux_notification*) k_obj)->prox,
             &((k_output_lux_notification*) k_obj)->lux
    );
    break;
  case K_OUTPUT_LUX_MANAGED_NOTIFICATION:
    strcat(format,K_OUTPUT_LUX_MANAGED_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_lux_managed_notification*) k_obj)->id,
             &((k_output_lux_managed_notification*) k_obj)->type,
             &((k_output_lux_managed_notification*) k_obj)->pin_mask
    );
    break;
  //INEMO
  case K_OUTPUT_POS_READ_RAW_RESPONSE:
    strcat(format,K_OUTPUT_POS_READ_RAW_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_pos_read_raw_response*) k_obj)->id,
             &((k_output_pos_read_raw_response*) k_obj)->acc_x,
             &((k_output_pos_read_raw_response*) k_obj)->acc_y,
             &((k_output_pos_read_raw_response*) k_obj)->acc_z,
             &((k_output_pos_read_raw_response*) k_obj)->angle_x,
             &((k_output_pos_read_raw_response*) k_obj)->angle_y,
             &((k_output_pos_read_raw_response*) k_obj)->angle_z,
             &((k_output_pos_read_raw_response*) k_obj)->magnet_x,
             &((k_output_pos_read_raw_response*) k_obj)->magnet_y,
             &((k_output_pos_read_raw_response*) k_obj)->magnet_x
    );
    break;
  case K_OUTPUT_POS_READ_EULER_RESPONSE:
    strcat(format,K_OUTPUT_POS_READ_RAW_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_pos_read_euler_response*) k_obj)->id,
             &((k_output_pos_read_euler_response*) k_obj)->pitch,
             &((k_output_pos_read_euler_response*) k_obj)->roll,
             &((k_output_pos_read_euler_response*) k_obj)->yaw
    );
    break;
  case K_OUTPUT_POS_NOTIFICATION_RAW:
    strcat(format,K_OUTPUT_POS_NOTIFICATION_RAW_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_pos_read_raw_response*) k_obj)->id,
             &((k_output_pos_read_raw_response*) k_obj)->acc_x,
             &((k_output_pos_read_raw_response*) k_obj)->acc_y,
             &((k_output_pos_read_raw_response*) k_obj)->acc_z,
             &((k_output_pos_read_raw_response*) k_obj)->angle_x,
             &((k_output_pos_read_raw_response*) k_obj)->angle_y,
             &((k_output_pos_read_raw_response*) k_obj)->angle_z,
             &((k_output_pos_read_raw_response*) k_obj)->magnet_x,
             &((k_output_pos_read_raw_response*) k_obj)->magnet_y,
             &((k_output_pos_read_raw_response*) k_obj)->magnet_z
    );
    break;
  case K_OUTPUT_POS_NOTIFICATION_EULER:
    strcat(format,K_OUTPUT_POS_NOTIFICATION_EULER_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_pos_notification_euler*) k_obj)->id,
             &((k_output_pos_notification_euler*) k_obj)->pitch,
             &((k_output_pos_notification_euler*) k_obj)->roll,
             &((k_output_pos_notification_euler*) k_obj)->yaw
    );
    break;
  case K_OUTPUT_POS_MANAGED_NOTIFICATION:
    strcat(format,K_OUTPUT_POS_MANAGED_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_pos_managed_notification*) k_obj)->id,
             &((k_output_pos_managed_notification*) k_obj)->notification_mask,
             &((k_output_pos_managed_notification*) k_obj)->extra
    );
    break;
  case K_OUTPUT_POS_READ_CALIBRATION_STATE_RESPONSE:
    strcat(format,K_OUTPUT_POS_READ_CALIBRATION_STATE_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_pos_read_calibration_state_response*) k_obj)->id,
             &((k_output_pos_read_calibration_state_response*) k_obj)->calibrated
    );
    break;
    
  case K_OUTPUT_POS_READ_STEP_COUNTER_RESPONSE:
    strcat(format,K_OUTPUT_POS_READ_STEP_COUNTER_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_pos_read_step_counter_response*) k_obj)->id,
             &((k_output_pos_read_step_counter_response*) k_obj)->step_counter
    );
    break;
   //ENV SENSOR
  case K_OUTPUT_ENV_READ_VALUE_RESPONSE:
    strcat(format,K_OUTPUT_ENV_READ_VALUE_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_env_read_value_response*) k_obj)->id,
             &((k_output_env_read_value_response*) k_obj)->pressure,
             &((k_output_env_read_value_response*) k_obj)->temperature,
             &((k_output_env_read_value_response*) k_obj)->humidity,
             &((k_output_env_read_value_response*) k_obj)->lux
    );
    break;
  case K_OUTPUT_ENV_NOTIFICATION:
    strcat(format,K_OUTPUT_ENV_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_env_notification*) k_obj)->id,
             &((k_output_env_notification*) k_obj)->pressure,
             &((k_output_env_notification*) k_obj)->temperature,
             &((k_output_env_notification*) k_obj)->humidity,
             &((k_output_env_notification*) k_obj)->lux
    );
    break;
  //MIC
  case K_OUTPUT_MIC_GET_LOCALIZATION_RESPONSE:
    strcat(format,K_OUTPUT_MIC_GET_LOCALIZATION_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_mic_get_localization_response*) k_obj)->id,
             &((k_output_mic_get_localization_response*) k_obj)->angle
    );
    break;
  case K_OUTPUT_MIC_LOCALIZATION_NOTIFICATION:
    strcat(format,K_OUTPUT_MIC_GET_LOCALIZATION_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_mic_get_localization_notification*) k_obj)->id,
             &((k_output_mic_get_localization_notification*) k_obj)->angle
    );
    break;
  //I2C
  case K_OUTPUT_ENV_THRESHOLD_NOTIFICATION:
    strcat(format,K_OUTPUT_ENV_THRESHOLD_NOTIFICATION_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_env_threshold_notification*) k_obj)->id,
             &((k_output_env_threshold_notification*) k_obj)->sensor,
             &((k_output_env_threshold_notification*) k_obj)->up_down
    );
    break;
  case K_OUTPUT_I2C_READ_RESPONSE:
    strcat(format,K_OUTPUT_I2C_READ_RESPONSE_PARAMS);
    generate_ris = kitra_generate(packet,format,optional_mask,
             &((k_output_read_response_i2c*) k_obj)->id,
             &((k_output_read_response_i2c*) k_obj)->device_address,
             &((k_output_read_response_i2c*) k_obj)->data_address_low,
             &((k_output_read_response_i2c*) k_obj)->data_address_high,
             &((k_output_read_response_i2c*) k_obj)->data[0],
             &((k_output_read_response_i2c*) k_obj)->data[1],
             &((k_output_read_response_i2c*) k_obj)->data[2],
             &((k_output_read_response_i2c*) k_obj)->data[3]
    );
    break;
#endif
  default:
    return PARSE_UNDEFINED_CMD;
  }
  
  return (generate_ris == false?PARSE_ERROR:PARSE_OK);
}



#undef KITRA_INPUT_C
