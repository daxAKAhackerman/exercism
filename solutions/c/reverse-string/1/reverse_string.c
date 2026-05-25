#include "reverse_string.h"
#include <stdlib.h>
#include <string.h>

char *reverse(const char *value) {
  size_t len = strlen(value);

  char *reversed_value = calloc(len + 1, sizeof(char));
  char *ptr_reversed_value = reversed_value + (len - 1);

  while (*value != '\0') {
    *ptr_reversed_value-- = *value++;
  }

  return reversed_value;
}
