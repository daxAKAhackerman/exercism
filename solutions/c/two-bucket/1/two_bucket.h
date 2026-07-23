#ifndef TWO_BUCKET_H
#define TWO_BUCKET_H

#include <stdbool.h>

#define min(a, b) (((a) <= (b)) ? (a) : (b))

typedef enum { BUCKET_ID_1, BUCKET_ID_2 } bucket_id_t;

typedef unsigned int bucket_liters_t;

typedef struct {
  bool possible;
  int move_count;
  bucket_id_t goal_bucket;
  bucket_liters_t other_bucket_liters;
} bucket_result_t;

typedef struct {
  unsigned int cap;
  unsigned int con;
} bucket_t;

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket);

static inline void fill_bucket(bucket_t *bucket, unsigned int *steps) {
  bucket->con = bucket->cap;
  (*steps)++;
}

static inline void empty_bucket(bucket_t *bucket, unsigned int *steps) {
  bucket->con = 0;
  (*steps)++;
}

static inline void pour_bucket(bucket_t *d, bucket_t *s, unsigned int *steps) {
  unsigned int amt_to_pour = min((d->cap - d->con), s->con);

  d->con += amt_to_pour;
  s->con -= amt_to_pour;

  (*steps)++;
}

#endif
