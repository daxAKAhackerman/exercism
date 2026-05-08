#include "hamming.h"
#include <stddef.h>
#include <string.h>

int compute(const char *lhs, const char *rhs) {
  size_t len = strlen(lhs);
  int distance = 0;

  if (len != strlen(rhs)) {
    return -1;
  }

  for (int i = 0; i < (int)len; i++) {
    if (*lhs++ != *rhs++) {
      distance++;
    }
  }

  return distance;
}
