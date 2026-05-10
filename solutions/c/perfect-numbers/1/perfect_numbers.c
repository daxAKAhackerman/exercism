#include "perfect_numbers.h"

kind classify_number(int num) {
  int aliquot_sum = 0;

  if (num <= 0) {
    return ERROR;
  }

  for (int i = num / 2; i > 0; i--) {
    if (num % i == 0) {
      aliquot_sum += i;
    }
  }

  if (aliquot_sum == num) {
    return PERFECT_NUMBER;
  } else if (aliquot_sum > num) {
    return ABUNDANT_NUMBER;
  } else {
    return DEFICIENT_NUMBER;
  }
}
