#include "palindrome_products.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *n_as_str = NULL;

static bool is_palindrome(int n) {
  memset(n_as_str, 0, sizeof(char) * MAX_PALINDROME_SIZE);
  snprintf(n_as_str, MAX_PALINDROME_SIZE - 1, "%d", n);

  char *bg_ptr = n_as_str;
  char *end_ptr = n_as_str + (strlen(n_as_str) - 1);

  while (*bg_ptr != '\0') {
    if (*bg_ptr != *end_ptr) {
      return false;
    }
    bg_ptr++;
    end_ptr--;
  }

  return true;
}

static void add_factor(factor_t **f, int fa, int fb) {
  factor_t *last_f = *f;
  while (last_f->next != NULL)
    last_f = last_f->next;
  last_f->next = calloc(1, sizeof(factor_t));
  last_f->next->factor_a = fa;
  last_f->next->factor_b = fb;
}

static void free_factors(factor_t **f) {
  if (*f != NULL) {
    if ((*f)->next != NULL)
      free_factors(&(*f)->next);
    free(*f);
    *f = NULL;
  }
}

static void set_factor(factor_t **f, int fa, int fb) {
  if ((*f)->next != NULL) {
    free_factors(&(*f)->next);
  } else {
    (*f)->factor_a = fa;
    (*f)->factor_b = fb;
  }
}

product_t *get_palindrome_product(int from, int to) {
  product_t *r = calloc(1, sizeof(product_t));
  r->factors_lg = calloc(1, sizeof(factor_t));
  r->factors_sm = calloc(1, sizeof(factor_t));

  if (to < from) {
    sprintf(r->error, "invalid input: min is %d and max is %d", from, to);
    return r;
  }

  int prod = 0;
  n_as_str = calloc(MAX_PALINDROME_SIZE, sizeof(char));

  for (int i = from; i <= to; i++) {
    for (int j = i; j <= to; j++) {

      prod = i * j;
      if (prod % 10 == 0)
        continue;

      if (is_palindrome(prod)) {
        if (prod > r->largest) {
          r->largest = prod;
          set_factor(&r->factors_lg, i, j);
        } else if (prod == r->largest) {
          add_factor(&r->factors_lg, i, j);
        }

        if (prod < r->smallest || r->smallest == 0) {
          r->smallest = prod;
          set_factor(&r->factors_sm, i, j);
        } else if (prod == r->smallest) {
          add_factor(&r->factors_sm, i, j);
        }
      }
    }
  }

  if (r->largest == 0) {
    sprintf(r->error, "no palindrome with factors in the range %d to %d", from,
            to);
  }
  free(n_as_str);

  return r;
}

void free_product(product_t *p) {
  free_factors(&p->factors_lg);
  free_factors(&p->factors_sm);
  free(p);
}
