#include "all_your_base.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t rebase(int8_t digits[DIGITS_ARRAY_SIZE], int16_t input_base,
              int16_t output_base, size_t input_length) {
  int32_t value = 0;
  int8_t d = 0;

  // Invalid base
  if (output_base <= 1 || input_base <= 1) {
    memset(digits, 0, DIGITS_ARRAY_SIZE * sizeof(int8_t));
    return 0;
  }

  for (unsigned int i = 0; i < input_length; i++) {
    d = digits[input_length - 1 - i];

    // Digit is negative or bigger than what base allows
    if (d < 0 || d >= input_base) {
      memset(digits, 0, DIGITS_ARRAY_SIZE * sizeof(int8_t));
      return 0;
    }
    value += d * pow(input_base, i);
  }

  // Now that we have the base 10 value, wipe the array
  memset(digits, 0, DIGITS_ARRAY_SIZE * sizeof(int8_t));

  int8_t *reversed_digits_out = calloc(DIGITS_ARRAY_SIZE, sizeof(int8_t));
  int8_t *ptr_reversed_digits_out = reversed_digits_out;

  // This will give the digits in reverse order
  size_t count = 0;
  while (value != 0) {
    *ptr_reversed_digits_out++ = value % output_base;
    value /= output_base;
    ++count;
  }

  // Handle an edge case where the input value was 0, but not the length
  // In this case, we want to return a length of 1, not 0
  if (count == 0 && input_length > 0) {
    count++;
  }

  // Put back the digits in the correct order
  for (unsigned int i = 0; i < count; i++) {
    digits[i] = reversed_digits_out[count - i - 1];
  }

  free(reversed_digits_out);
  return count;
}
