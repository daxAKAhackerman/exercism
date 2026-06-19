#ifndef PYTHAGOREAN_TRIPLET_H
#define PYTHAGOREAN_TRIPLET_H

typedef struct {
  unsigned int a;
  unsigned int b;
  unsigned int c;
} triplet_t;

typedef struct {
  unsigned int count;
  triplet_t triplets[];
} triplets_t;

triplets_t *triplets_with_sum(unsigned int sum);

void free_triplets(triplets_t *triplets);

#endif
