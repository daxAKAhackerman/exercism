#include "high_scores.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int comp(const void *a, const void *b) {
  return *(int32_t *)b - *(int32_t *)a;
}

int32_t latest(const int32_t *scores, size_t scores_len) {
  return scores[scores_len - 1];
}

int32_t personal_best(const int32_t *scores, size_t scores_len) {
  int32_t highest = 0;

  for (int i = 0; i < (int32_t)scores_len; i++) {
    if (scores[i] > highest) {
      highest = scores[i];
    }
  }

  return highest;
}

size_t personal_top_three(const int32_t *scores, size_t scores_len,
                          int32_t *output) {
  int num_of_elements_to_return = min(scores_len, 3);
  size_t array_size = sizeof(int32_t) * scores_len;

  int32_t *sorted_scores = malloc(array_size);
  memcpy(sorted_scores, scores, array_size);

  qsort(sorted_scores, scores_len, sizeof(int32_t), comp);

  memcpy(output, sorted_scores, sizeof(int32_t) * num_of_elements_to_return);

  free(sorted_scores);

  return num_of_elements_to_return;
}
