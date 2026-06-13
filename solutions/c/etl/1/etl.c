#include "etl.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int convert(const legacy_map *input, const size_t input_len, new_map **output) {
  *output = calloc(26, sizeof(new_map));
  new_map *output_ptr = *output;

  for (char letter = 'A'; letter <= 'Z'; letter++) {
    for (unsigned int i = 0; i < input_len; i++) {
      if (strchr(input[i].keys, letter)) {
        *output_ptr++ =
            (new_map){.key = tolower(letter), .value = input[i].value};
        break;
      }
    }
  }

  size_t len = output_ptr - *output;
  *output = realloc(*output, len * sizeof(new_map));

  return len;
}
