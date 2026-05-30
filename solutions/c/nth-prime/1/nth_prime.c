#include "nth_prime.h"
#include <stdint.h>
#include <stdlib.h>

uint32_t nth(uint32_t n) {
  if (n == 0) {
    return 0;
  }

  uint32_t *primes = calloc(n + 1, sizeof(uint32_t));
  uint32_t *ptr_prime = primes;
  uint32_t candidate = 2;

  while (primes[n - 1] == 0) {
    for (uint32_t i = 0; i < n; i++) {
      if (primes[i] == 0) {
        *ptr_prime++ = candidate++;
        break;
      } else {
        if (candidate % primes[i] == 0) {
          candidate++;
          break;
        }
      }
    }
  }

  return primes[n - 1];
}
