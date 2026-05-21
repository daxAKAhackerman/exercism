#include "luhn.h"
#include <string.h>

bool luhn(const char *num) {
  int i = strlen(num) - 1;
  int real_length = 0;
  const char *ptr_num = num;
  int luhn_sum = 0;
  char c = '\0';
  bool double_num = true;

  // Check length without whitespaces
  while (*ptr_num != '\0') {
    if (*ptr_num++ != ' ') {
      real_length++;
    }
  }

  // Length 1 or less is bad
  if (real_length <= 1) {
    return false;
  }

  for (; i >= 0; i--) {
    // Skip whitespaces
    if (num[i] == ' ') {
      continue;
    }

    // Non numerals is bad
    if (num[i] < '0' || num[i] > '9') {
      return false;
    }

    // If we are not on a doubling number, just add the number value to the sum
    if ((double_num ^= 0x01) == false) {
      luhn_sum += num[i] - '0';
      continue;
    }

    // Else, double the digit, sub 9 if greater than 9
    c = (num[i] - '0') * 2;
    if (c > 9) {
      c -= 9;
    }
    luhn_sum += c;
  }

  // If divisible by 10, then good
  if (luhn_sum % 10 == 0) {
    return true;
  }

  // Else bad
  return false;
}
