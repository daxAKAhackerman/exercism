#include "linked_list.h"
#include <stdlib.h>

struct list_node {
  struct list_node *prev, *next;
  ll_data_t data;
};

struct list {
  struct list_node *first, *last;
};

struct list *list_create(void) {
  struct list *c = calloc(1, sizeof(struct list));
  return c;
}

ll_data_t list_pop(struct list *list) {
  struct list_node *last_node = list->last;
  ll_data_t data = last_node->data;
  if (last_node == list->first) {
    list->first = NULL;
    list->last = NULL;
  } else {
    list->last = last_node->prev;
    list->last->next = NULL;
  }
  free(last_node);

  return data;
}

ll_data_t list_shift(struct list *list) {
  struct list_node *first_node = list->first;
  ll_data_t data = first_node->data;
  if (first_node == list->last) {
    list->first = NULL;
    list->last = NULL;
  } else {
    list->first = first_node->next;
    list->first->prev = NULL;
  }
  free(first_node);

  return data;
}

void list_push(struct list *list, ll_data_t item_data) {
  struct list_node *node = calloc(1, sizeof(struct list_node));

  node->data = item_data;
  node->prev = list->last;

  if (list->first == NULL) {
    list->first = node;
  } else {
    list->last->next = node;
  }

  list->last = node;
}

void list_unshift(struct list *list, ll_data_t item_data) {
  struct list_node *node = calloc(1, sizeof(struct list_node));

  node->data = item_data;
  node->next = list->first;

  if (list->first == NULL) {
    list->last = node;
  } else {
    list->first->prev = node;
  }

  list->first = node;
}

size_t list_count(const struct list *list) {
  unsigned int count = 0;
  struct list_node *node = list->first;
  while (node != NULL) {
    count++;
    node = node->next;
  }
  return count;
}

void list_delete(struct list *list, ll_data_t data) {
  struct list_node *node = list->first;
  while (node != NULL) {
    if (node->data == data) {
      if (node == list->first) {
        list_shift(list);
        return;
      } else if (node == list->last) {
        list_pop(list);
        return;
      } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node);
        return;
      }
    }

    node = node->next;
  }
}

void list_destroy(struct list *list) {
  while (list->first != NULL) {
    list_pop(list);
  }
  free(list);
}
