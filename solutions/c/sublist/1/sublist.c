#include "sublist.h"
#include <stdbool.h>
#include <stddef.h>

static bool contains(int *big, int *small, size_t big_len, size_t small_len) {
  for (unsigned int i = 0; i < big_len; i++) {
    if (*small == big[i]) {
      int *ptr_small = small;
      for (unsigned int j = i; j < small_len; j++) {
        if (*ptr_small++ != big[j]) {
          return false;
        }
      }
      return true;
    }
  }

  return false;
}

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count) {
  if (!list_to_compare_element_count && !base_list_element_count) {
    return EQUAL;
  } else if (!base_list_element_count) {
    return SUPERLIST;
  } else if (!list_to_compare_element_count) {
    return SUBLIST;
  }

  if (base_list_element_count > list_to_compare_element_count &&
      contains(base_list, list_to_compare, base_list_element_count,
               list_to_compare_element_count)) {
    return SUBLIST;
  } else if (list_to_compare_element_count > base_list_element_count &&
             contains(list_to_compare, base_list, list_to_compare_element_count,
                      base_list_element_count)) {
    return SUPERLIST;
  }

  for (unsigned int i = 0; i < base_list_element_count; i++) {
    if (base_list[i] != list_to_compare[i]) {
      return UNEQUAL;
    }
  }

  return EQUAL;
}
