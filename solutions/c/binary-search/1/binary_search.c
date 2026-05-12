#include "binary_search.h"
#include <stdbool.h>

const int *binary_search(int value, const int *arr, size_t length) {
  int high_bound = length - 1;
  int low_bound = 0;
  int i = 0;

  while (true) {
    if (high_bound - low_bound < 0) {
      return NULL;
    }

    i = (high_bound + low_bound) / 2;
    if (arr[i] == value) {
      return &arr[i];
    } else if (arr[i] < value) {
      low_bound = i + 1;
    } else {
      high_bound = i - 1;
    }
  }
}
