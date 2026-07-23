#include "two_bucket.h"
#include <stdbool.h>

bucket_result_t measure(bucket_liters_t bucket_1_size,
                        bucket_liters_t bucket_2_size,
                        bucket_liters_t goal_volume, bucket_id_t start_bucket) {

  unsigned int num_of_actions = 0;

  bucket_t bucket_a = {.cap = start_bucket == BUCKET_ID_1 ? bucket_1_size
                                                          : bucket_2_size};
  bucket_t bucket_b = {.cap = start_bucket == BUCKET_ID_1 ? bucket_2_size
                                                          : bucket_1_size};

  // Solve
  fill_bucket(&bucket_a, &num_of_actions);

  // Edge case
  // If the goal is the same as the capacity of bucket_b, just fill that bucket
  if (bucket_b.cap == goal_volume)
    fill_bucket(&bucket_b, &num_of_actions);

  while (bucket_a.con != goal_volume && bucket_b.con != goal_volume) {
    if (bucket_b.con == bucket_b.cap)
      empty_bucket(&bucket_b, &num_of_actions);
    else if (bucket_a.con == 0)
      fill_bucket(&bucket_a, &num_of_actions);
    else
      pour_bucket(&bucket_b, &bucket_a, &num_of_actions);

    if (bucket_a.con == bucket_a.cap && bucket_b.con == 0)
      return (bucket_result_t){.possible = false};
  }

  return (bucket_result_t){
      .possible = true,
      .goal_bucket =
          bucket_a.con == goal_volume ? start_bucket : start_bucket ^ 1,
      .other_bucket_liters =
          bucket_a.con == goal_volume ? bucket_b.con : bucket_a.con,
      .move_count = num_of_actions};
}
