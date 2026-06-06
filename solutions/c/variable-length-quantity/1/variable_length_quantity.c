#include "variable_length_quantity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int encode(const uint32_t *integers, size_t integers_len, uint8_t *output) {
  uint32_t n = 0;
  uint8_t *encoder = calloc(5, sizeof(uint8_t));
  uint8_t encoder_size = 0;
  uint8_t *ptr_encoder = encoder;
  uint8_t *ptr_output = output;

  for (uint32_t i = 0; i < integers_len; i++) {
    n = integers[i];

    encoder[0] = (n >> 28) | 0x80;
    encoder[1] = ((n >> 21) & 0x7f) | 0x80;
    encoder[2] = ((n >> 14) & 0x7f) | 0x80;
    encoder[3] = ((n >> 7) & 0x7f) | 0x80;
    encoder[4] = n & 0x7f;

    while (*ptr_encoder == 0x80) {
      ptr_encoder++;
    }

    encoder_size = 5 - (ptr_encoder - encoder);
    memcpy(ptr_output, ptr_encoder, encoder_size * sizeof(uint8_t));
    ptr_output += encoder_size;
    ptr_encoder = encoder;
  }

  return ptr_output - output;
}

int decode(const uint8_t *bytes, size_t buffer_len, uint32_t *output) {
  uint8_t b = 0;
  uint32_t n = 0;
  uint32_t *ptr_output = output;
  bool complete = false;

  for (uint32_t i = 0; i < buffer_len; i++) {
    complete = false;
    b = bytes[i];

    n <<= 7;
    n |= (b & 0x7f);

    if ((b & 0x80) != 0) {
      continue;
    }

    complete = true;
    *ptr_output++ = n;
    n = 0;
  }

  return complete ? ptr_output - output : -1;
}
