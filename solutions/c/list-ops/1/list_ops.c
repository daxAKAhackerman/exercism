#include "list_ops.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

list_t *new_list(size_t length, list_element_t elements[]) {
  list_t *list = malloc(sizeof(list_t) + length * sizeof(list_element_t));
  list->length = length;
  memcpy(list->elements, elements, length * sizeof(list_element_t));

  return list;
}

list_t *append_list(list_t *list1, list_t *list2) {
  list_t *list =
      malloc(sizeof(list_t) + list1->length * sizeof(list_element_t) +
             list2->length * sizeof(list_element_t));
  list->length = list1->length + list2->length;
  memcpy(list->elements, list1->elements,
         list1->length * sizeof(list_element_t));
  memcpy(&list->elements[list1->length], list2->elements,
         list2->length * sizeof(list_element_t));

  return list;
}

void delete_list(list_t *list) { free(list); }

list_t *filter_list(list_t *list, bool (*filter)(list_element_t)) {
  list_t *filtered_list = new_list(list->length, list->elements);
  filtered_list->length = 0;
  list_element_t *ptr_element = filtered_list->elements;

  for (unsigned int i = 0; i < list->length; i++) {
    if (filter(list->elements[i])) {
      *ptr_element++ = list->elements[i];
      filtered_list->length++;
    }
  }

  filtered_list =
      realloc(filtered_list,
              sizeof(list_t) + filtered_list->length * sizeof(list_element_t));

  return filtered_list;
}

size_t length_list(list_t *list) { return list->length; }

list_t *map_list(list_t *list, list_element_t (*map)(list_element_t)) {
  list_t *mapped_list = new_list(list->length, list->elements);
  for (unsigned int i = 0; i < list->length; i++) {
    mapped_list->elements[i] = map(list->elements[i]);
  }

  return mapped_list;
}

list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t)) {
  for (unsigned int i = 0; i < list->length; i++) {
    initial = foldl(initial, list->elements[i]);
  }

  return initial;
}

list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t)) {
  for (unsigned int i = list->length; i > 0; i--) {
    initial = foldr(list->elements[i - 1], initial);
  }

  return initial;
}

list_t *reverse_list(list_t *list) {
  list_t *reversed_list = new_list(list->length, list->elements);
  list_element_t *ptr_elements = reversed_list->elements;
  for (unsigned int i = list->length; i > 0; i--) {
    *ptr_elements++ = list->elements[i - 1];
  }

  return reversed_list;
}
