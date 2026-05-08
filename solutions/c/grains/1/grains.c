#include "grains.h"

uint64_t square(uint8_t index) {
  uint64_t grain = 1;

  if (index < 1 || index > 64) {
    return 0;
  }

  return grain << (index - 1);
}

uint64_t total(void) {
  uint64_t total = 0;
  int i;

  for (i = 0; i < 64; i++) {
    total += square(i + 1);
  }

  return total;
}
