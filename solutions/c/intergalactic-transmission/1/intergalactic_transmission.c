#include "intergalactic_transmission.h"
#include <stdint.h>

int transmit_sequence(uint8_t *buffer, const uint8_t *message,
                      int message_length) {
  int bits_before_flush = 7;
  uint8_t int_buffer = 0;
  int transmission_len = 0;

  for (int i = 0; i < message_length; i++) {
    for (int j = 0; j < 8; j++) {
      int_buffer <<= 1;
      int_buffer |= (message[i] >> (7 - j)) & 0x1;
      bits_before_flush--;

      if (bits_before_flush == 0) {
        int_buffer <<= 1;
        if (__builtin_popcount(int_buffer) % 2 != 0)
          int_buffer |= 0x1;

        *buffer++ = int_buffer;
        transmission_len++;
        bits_before_flush = 7;
        int_buffer = 0;
      }
    }
  }

  if (bits_before_flush != 0 && bits_before_flush != 7) {
    int_buffer <<= bits_before_flush + 1;
    if (__builtin_popcount(int_buffer) % 2 != 0)
      int_buffer |= 0x1;
    *buffer = int_buffer;
    transmission_len++;
  }

  return transmission_len;
}

int decode_message(uint8_t *buffer, const uint8_t *message,
                   int message_length) {
  int bits_before_flush = 8;
  uint8_t int_buffer = 0;
  int transmission_len = 0;

  for (int i = 0; i < message_length; i++) {
    if (__builtin_popcount(message[i]) % 2 != 0) {
      return WRONG_PARITY;
    }

    for (int j = 0; j < 7; j++) {
      int_buffer <<= 1;
      int_buffer |= (message[i] >> (7 - j)) & 0x1;
      bits_before_flush--;
      if (bits_before_flush == 0) {
        *buffer++ = int_buffer;
        transmission_len++;
        bits_before_flush = 8;
        int_buffer = 0;
      }
    }
  }

  return transmission_len;
}
