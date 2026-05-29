#include "prime_factors.h"
#include <stddef.h>
#include <stdint.h>

size_t find_factors(uint64_t n, uint64_t factors[MAXFACTORS]) {
  uint64_t i = 2;
  size_t count = 0;

  while (n > 1) {
    if (n % i == 0) {
      *factors++ = i;
      n /= i;
      ++count;
    } else {
      ++i;
    }
  }

  return count;
}
