#ifndef RAIL_FENCE_CIPHER_H
#define RAIL_FENCE_CIPHER_H

#include <stddef.h>

typedef enum {
  K,
  K_P,
} k_state_t;

typedef enum {
  UP = -1,
  DOWN = 1,
} direction_t;

char *encode(char *text, size_t rails);

char *decode(char *ciphertext, size_t rails);

#endif
