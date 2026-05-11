#include "armstrong_numbers.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool is_armstrong_number(int candidate) {
  char candidate_as_str[MAX_BUFFER_LEN] = {'\0'};
  int len = 0;
  int total = 0;

  snprintf(candidate_as_str, MAX_BUFFER_LEN, "%d", candidate);

  len = strlen(candidate_as_str);

  for (int i = 0; i < len; i++) {
    total += pow(candidate_as_str[i] - 48, len);
  }

  return total == candidate ? true : false;
}
