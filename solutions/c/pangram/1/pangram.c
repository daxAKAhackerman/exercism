#include "pangram.h"
#include <stdio.h>

bool is_pangram(const char *sentence) {
  char c = '\0';
  int letter_counter = 26;
  bool letters[26] = {false};

  if (sentence == NULL) {
    return false;
  }

  while ((c = *sentence++) != '\0') {
    // convert to lower case
    if (c >= 65 && c <= 90) {
      c += 32;
    }

    // non alpha
    if (c < 97 || c > 122) {
      continue;
    }

    if (letters[c - 97] == false) {
      letters[c - 97] = true;
      letter_counter--;
    }

    if (letter_counter == 0) {
      return true;
    }
  }

  return false;
}
