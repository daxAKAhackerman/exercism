#include "crypto_square.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

static char *normalize_text(const char *s) {
  char c = '\0';
  char *r = calloc(strlen(s) + 1, sizeof(char));
  char *r_ptr = r;

  while ((c = *s++) != '\0') {
    if (isalnum(c)) {
      *r_ptr++ = tolower(c);
    }
  }

  r = realloc(r, (strlen(r) + 1) * sizeof(char));
  return r;
}

char *ciphertext(const char *input) {
  // Allocate twice the input size, which should be plenty (plus a null byte)
  char *r = calloc(strlen(input) * 2 + 1, sizeof(char));
  char *r_ptr = r;

  char *normalized_input = normalize_text(input);
  size_t len = strlen(normalized_input);

  // To find the closest rectangle size, finding the square root works
  // If result is not an integer, ceil the columns and floor the rows
  unsigned int cols = (int)ceil(sqrt(len));
  unsigned int rows = (int)floor(sqrt(len));

  // If this isn't enough space, increment the rows
  // e.g. for len 8, sqrt gives 2 and 3, which is too small, so go to 3 by 3
  // instead.
  if (cols * rows < len) {
    rows++;
  }

  unsigned int index = 0;
  for (unsigned int i = 0; i < cols; i++) {
    for (unsigned int j = 0; j < rows; j++) {
      // Get the index like if it was in a matrix
      index = j * cols + i;
      if (index > len - 1) {
        // If there is no characters left in the column, add a space instead
        *r_ptr++ = ' ';
      } else {
        *r_ptr++ = normalized_input[index];
      }
    }
    // If we are not on the last word, add a space after the word
    if (i != cols - 1) {
      *r_ptr++ = ' ';
    }
  }

  free(normalized_input);

  return r;
}
