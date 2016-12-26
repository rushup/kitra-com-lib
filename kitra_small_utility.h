#ifndef KITRA_SMALL_UTLITY_H
#define KITRA_SMALL_UTLITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#define K_SET_BIT(var,pos) ((var) |= (1<<(pos)))

#define K_CLEAR_BIT(var,pos) ((var) &= ~(1<<(pos)))

#define K_SET_BIT_VAL(var,pos,val) val==0?K_CLEAR_BIT(var,pos):K_SET_BIT(var,pos)

void k_get_checksum(char* packet, uint32_t len, char* chks);

#ifdef __cplusplus
}
#endif

#endif