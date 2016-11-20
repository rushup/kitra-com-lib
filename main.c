#include <stdio.h>
#include "kitra_input.h"
#include "kitra_output.h"
#include "kitra_packet_generator.h"
#include "kitra_small_utility.h"

void kitra_platform_send(char* buffer, uint32_t length)
{
  /*Print through serial*/
}


int main() {
	
  k_input_ldrgb_enable_disable msg = {
	.id = K_INPUT_LDRGB_ENABLE_DISABLE,
	.pin = 0,
	.enabled = 1
  };
   printf("Hello, Lib working %d! \n",msg.enabled);
   
   return 0;
}