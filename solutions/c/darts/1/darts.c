#include "darts.h"
#include <stdint.h>

uint8_t score(coordinate_t c) {
  float coord_squared = (c.x * c.x) + (c.y * c.y);

  if (coord_squared <= 1.0f) {
    return 10;
  } else if (coord_squared <= 25.0f) {
    return 5;
  } else if (coord_squared <= 100.0f) {
    return 1;
  }

  return 0;
}
