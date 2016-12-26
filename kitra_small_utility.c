#include "kitra_small_utility.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void k_get_checksum(char* packet, uint32_t len, char* chks) {
  char n_chks = 0;
  int c;
  for (c = 0; c < len; c++) {
    n_chks = (char)(n_chks ^ packet[c]);
  }
  sprintf(chks, "%02X", n_chks);
}
