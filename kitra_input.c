#define KITRA_INPUT_C

#include "kitra_input.h"
#include <string.h>
#include "kitra_packet_generator.h"
#include "kitra_small_utility.h"

#define MAX_BUFFER_SIZE 1024
static char buffer_rx[MAX_BUFFER_SIZE];
static uint32_t tmp_cmd_index = 0;
bool tmp_processing = false;

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
  
sscanf(packet,"%*6[^,],%d",&id);
strcat(format,"%*s,"); //for parsing $KITRA

switch(id)
  {
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
             &((k_input_read_response_i2c*) k_obj)->id,
             &((k_input_read_response_i2c*) k_obj)->device_address,
             &((k_input_read_response_i2c*) k_obj)->data_address_low,
             &((k_input_read_response_i2c*) k_obj)->data_address_high,
             &((k_input_read_response_i2c*) k_obj)->data[0],
             &((k_input_read_response_i2c*) k_obj)->data[1],
             &((k_input_read_response_i2c*) k_obj)->data[2],
             &((k_input_read_response_i2c*) k_obj)->data[3]
    );
    break;
  default:
    return PARSE_UNDEFINED_CMD;
  }

  return (generate_ris == false?PARSE_ERROR:PARSE_OK);
}


#undef KITRA_INPUT_C
