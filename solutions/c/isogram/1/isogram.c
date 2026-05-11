#include "isogram.h"
#include <stdlib.h>

bool is_isogram(const char phrase[]) {
  bool letters[26] = {false};
  char c = '\0';
  int i = 0;
  const char *ptr_phrase = phrase;

  if (phrase == NULL) {
    return false;
  }

  while ((c = *ptr_phrase++) != '\0') {
    if (c >= 65 && c <= 90) {
      c += 32;
    }

    if (c < 97 || c > 122) {
      continue;
    }

    i = c - 97;
    if (letters[i]) {
      return false;
    } else {
      letters[i] = true;
    }
  }
  return true;
}
