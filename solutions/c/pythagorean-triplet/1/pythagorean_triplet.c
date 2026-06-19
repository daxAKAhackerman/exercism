#include "pythagorean_triplet.h"
#include <math.h>
#include <stdlib.h>

triplets_t *triplets_with_sum(unsigned int sum) {
  unsigned int max = sum - 3;
  double c = 0.0;
  unsigned int c_s = 0;
  triplets_t *triplets = calloc(1, sizeof(triplet_t));

  for (unsigned int a = 1; a < max; a++) {
    for (unsigned int b = a + 1; b < max; b++) {
      c_s = a * a + b * b;
      c = sqrt(c_s);
      if ((int)c != c) {
        continue;
      }

      if (a + b + c != sum) {
        continue;
      }

      triplets =
          realloc(triplets, sizeof(triplets_t) +
                                sizeof(triplet_t) * (triplets->count + 1));
      triplets->triplets[triplets->count] = (triplet_t){a, b, c};
      triplets->count++;
    }
  }

  return triplets;
}

void free_triplets(triplets_t *triplets) { free(triplets); }
