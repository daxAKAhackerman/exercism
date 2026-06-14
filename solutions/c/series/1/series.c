#include "series.h"
#include <stdlib.h>
#include <string.h>

slices_t slices(char *input_text, unsigned int substring_length) {
  slices_t r = {0};
  size_t len = strlen(input_text);

  if (substring_length > len || substring_length <= 0) {
    return r;
  }

  r.substring = calloc(len, sizeof(char *));
  char **substring_ptr = r.substring;

  for (unsigned int i = 0; i < len - substring_length + 1; i++) {
    *substring_ptr = calloc(substring_length + 1, sizeof(char));
    strncpy(*substring_ptr, &input_text[i], substring_length);
    r.substring_count++;
    substring_ptr++;
  }

  return r;
}
