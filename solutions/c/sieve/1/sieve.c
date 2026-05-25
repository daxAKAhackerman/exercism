#include "sieve.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes) {
  uint32_t prime_count = 0;
  bool *numbers = calloc(limit - 2, sizeof(uint32_t));

  for (uint32_t i = 2; i <= limit; i++) {
    if (numbers[i - 2]) {
      continue;
    }
    if (prime_count >= max_primes) {
      return prime_count;
    }
    *primes++ = i;
    ++prime_count;
    for (uint32_t j = i + i; j <= limit; j += i) {
      numbers[j - 2] = true;
    }
  }

  return prime_count;
}
