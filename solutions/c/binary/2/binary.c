#include "binary.h"
#include <string.h>

int convert(const char *input) {
  int len = (int)strlen(input);
  int mul = 0;
  int sum = 0;

  for (; len > 0; --len) {
    if (input[len - 1] == '1') {
      sum += 1 << mul;
    } else if (input[len - 1] != '0') {
      return -1;
    }
    ++mul;
  }

  return sum;
}
