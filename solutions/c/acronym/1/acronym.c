#include "acronym.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *abbreviate(const char *phrase) {
  // If we received a null ptr, return a null ptr
  if (phrase == NULL) {
    return NULL;
  }

  bool use_next_letter = true;
  char c = '\0';
  char *result = calloc(strlen(phrase) + 1, sizeof(char));
  char *ptr_result = result;

  while ((c = *phrase++) != '\0') {
    // If the char is alpha
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      if (use_next_letter) {
        // Use ternary to uppercase
        *ptr_result++ = (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
        use_next_letter = false;
      }
    } else if (c == ' ' || c == '-') {
      // If it's a space or hyphen
      use_next_letter = true;
    }
  }

  // If the acronym is empty, return null ptr
  if (strlen(result) == 0) {
    free(result);
    result = NULL;
  }

  return result;
}
