#include "scrabble_score.h"

unsigned int score(const char *word) {
  unsigned int total = 0;
  char c = '\0';

  while ((c = *word++) != '\0') {
    // Uppercase
    if (c >= 'a' && c <= 'z') {
      c -= 'a' - 'A';
    }

    // Skip bad letters
    if (c < 'A' || c > 'Z') {
      continue;
    }

    switch (c) {
    case 'F':
    case 'H':
    case 'V':
    case 'W':
    case 'Y':
      total += 4;
      break;
    case 'B':
    case 'C':
    case 'M':
    case 'P':
      total += 3;
      break;
    case 'D':
    case 'G':
      total += 2;
      break;
    case 'J':
    case 'X':
      total += 8;
      break;
    case 'Q':
    case 'Z':
      total += 10;
      break;
    case 'K':
      total += 5;
      break;
    default:
      ++total;
    }
  }

  return total;
}
