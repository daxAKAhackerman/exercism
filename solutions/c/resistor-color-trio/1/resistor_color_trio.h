#ifndef RESISTOR_COLOR_TRIO_H
#define RESISTOR_COLOR_TRIO_H

#include <stdint.h>

typedef struct {
  uint16_t value;
  int unit;
} resistor_value_t;

typedef enum {
  BLACK,
  BROWN,
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  VIOLET,
  GREY,
  WHITE
} resistor_band_t;

typedef enum { OHMS, KILOOHMS, MEGAOHMS, GIGAOHMS } metric_prefix_t;

resistor_value_t color_code(resistor_band_t bands[]);

#endif
