#include "rotational_cipher.h"
#include <stdlib.h>
#include <string.h>

char *rotate(const char *text, int shift_key) {
  char c = '\0';

  char *rotated_text = calloc(strlen(text) + 1, sizeof(char));
  char *ptr_rotated_text = rotated_text;

  while ((c = *text++) != '\0') {
    if (c < 'A' || c > 'z' || (c > 'Z' && c < 'a')) {
      *ptr_rotated_text++ = c;
      continue;
    }

    if (c <= 'Z') {
      c -= 'A';
      c += shift_key;
      c %= 26;
      c += 'A';
    } else {
      c -= 'a';
      c += shift_key;
      c %= 26;
      c += 'a';
    }

    *ptr_rotated_text++ = c;
  }

  return rotated_text;
}
