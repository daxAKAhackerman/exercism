#include "largest_series_product.h"
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int64_t largest_series_product(char *digits, size_t span) {
  size_t len = strlen(digits);

  if (len < span) {
    return ERROR;
  }

  int64_t max = 0;
  int64_t buf = 1;

  for (unsigned int i = 0; i <= len - span; i++) {
    for (unsigned int j = 0; j < span; j++) {
      if (!isdigit(digits[i + j])) {
        return ERROR;
      }
      buf *= digits[i + j] - '0';
    }

    if (buf > max) {
      max = buf;
    }

    buf = 1;
  }

  return max;
}
