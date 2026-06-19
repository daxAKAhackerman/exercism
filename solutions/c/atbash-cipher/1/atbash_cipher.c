#include "atbash_cipher.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char apply_atbash(char c) {
  c = tolower(c);
  c -= 'a';
  c = 25 - c;
  c += 'a';
  return c;
}

char *atbash_encode(const char *input) {
  size_t len = strlen(input);
  char *r = calloc(len + len / 5 + 1, sizeof(char));
  char *r_ptr = r;
  char c = '\0';
  unsigned int counter = 0;

  while ((c = *input++) != '\0') {
    if (isalnum(c)) {
      if (isalpha(c)) {
        c = apply_atbash(c);
      }
      *r_ptr++ = c;
      counter++;
      if (counter % 5 == 0) {
        *r_ptr++ = ' ';
      }
    }
  }

  if (r_ptr > r && *(r_ptr - 1) == ' ') {
    *--r_ptr = '\0';
  }

  r = realloc(r, (r_ptr - r + 1) * sizeof(char));

  return r;
}

char *atbash_decode(const char *input) {
  char *r = calloc(strlen(input) + 1, sizeof(char));
  char *r_ptr = r;
  char c = '\0';

  while ((c = *input++) != '\0') {
    if (isalnum(c)) {
      if (isalpha(c)) {
        c = apply_atbash(c);
      }
      *r_ptr++ = c;
    }
  }

  r = realloc(r, (r_ptr - r + 1) * sizeof(char));

  return r;
}
