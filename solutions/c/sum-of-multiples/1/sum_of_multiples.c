#include "sum_of_multiples.h"
#include <stdlib.h>

static int comp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

static unsigned int dedup(unsigned int *multiples, size_t size) {
  if (size == 0) {
    return 0;
  }

  unsigned int i = 0;
  for (unsigned int j = 1; j < size; j++) {
    if (multiples[i] != multiples[j]) {
      multiples[++i] = multiples[j];
    }
  }

  return i + 1;
}

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit) {
  // We allocate bigger than what we need, but we know it cannot be bigger than
  // this
  unsigned int *multiples = calloc(limit * number_of_factors, sizeof(int));
  unsigned int multiples_size = 0;

  // Get all factors smaller than limit
  unsigned int multiple = 0;
  for (unsigned int i = 0; i < number_of_factors; i++) {
    multiple = factors[i];

    // Skip 0s
    if (multiple == 0) {
      continue;
    }

    while (multiple < limit) {
      multiples[multiples_size++] = multiple;
      multiple += factors[i];
    }
  }

  // Free the space we don't use
  multiples = realloc(multiples, multiples_size * sizeof(int));

  // Sort the array
  qsort(multiples, multiples_size, sizeof(int), comp);

  // Remove duplicate
  multiples_size = dedup(multiples, multiples_size);
  multiples = realloc(multiples, multiples_size * sizeof(int));

  // Add results
  unsigned int sum = 0;
  for (unsigned int i = 0; i < multiples_size; i++) {
    sum += multiples[i];
  }

  free(multiples);
  return sum;
}
