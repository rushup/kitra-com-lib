#ifndef KITRA_PACKET_GENERATOR_H
#define KITRA_PACKET_GENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define MAX_BUFFER_SIZE 2048

bool kitra_generate(char* packet,char* format,uint32_t* filter_mask, ...);
bool kitra_generate_packet(char* buffer, uint32_t buffer_size,char* format, uint32_t filter_mask, ...);

#ifdef __cplusplus
}
#endif

#endif