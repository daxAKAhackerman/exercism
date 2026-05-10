#include "resistor_color_trio.h"
#include <math.h>
#include <stdint.h>

resistor_value_t color_code(resistor_band_t bands[]) {
  uint16_t prefix = OHMS;

  uint64_t total_value = ((bands[0] * 10) + bands[1]) * pow(10, bands[2]);

  while (total_value / 1000 >= 1) {
    total_value /= 1000;
    ++prefix;
  }

  return (resistor_value_t){.value = total_value, .unit = prefix};
}
