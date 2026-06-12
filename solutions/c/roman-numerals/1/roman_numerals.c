#include "roman_numerals.h"
#include <stdlib.h>
#include <string.h>

char *to_roman_numeral(unsigned int number) {
  char *result = calloc(BUFFER_SIZE, sizeof(char));
  char *result_ptr = result;

  roman_numeral roman_numerals[NUM_OF_NUMERALS] = {
      {.numeral = "M", .value = 1000}, {.numeral = "CM", .value = 900},
      {.numeral = "D", .value = 500},  {.numeral = "CD", .value = 400},
      {.numeral = "C", .value = 100},  {.numeral = "XC", .value = 90},
      {.numeral = "L", .value = 50},   {.numeral = "XL", .value = 40},
      {.numeral = "X", .value = 10},   {.numeral = "IX", .value = 9},
      {.numeral = "V", .value = 5},    {.numeral = "IV", .value = 4},
      {.numeral = "I", .value = 1},
  };

  unsigned int division_result = 0;
  for (unsigned int i = 0; i < NUM_OF_NUMERALS; i++) {
    division_result = number / roman_numerals[i].value;
    if (division_result > 0) {
      for (unsigned int j = 0; j < division_result; j++) {
        strncpy(result_ptr, roman_numerals[i].numeral, 2);
        result_ptr++;
        // If the value at ptr is not 0, we copied not 1, but 2 chars, so
        // increment the ptr again
        if (*result_ptr != '\0') {
          result_ptr++;
        }
      }
      number %= roman_numerals[i].value;
    }
  }

  result = realloc(result, sizeof(char) * (strlen(result) + 1));
  return result;
}
