#include "spiral_matrix.h"
#include <stdint.h>
#include <stdlib.h>

spiral_matrix_t *spiral_matrix_create(unsigned int size) {
  direction_t direction = RIGHT;
  unsigned int x = 0;
  unsigned int y = 0;

  unsigned int step_count_seed = size * 2;
  unsigned int step_count = step_count_seed / 2;

  spiral_matrix_t *matrix_struct = calloc(1, sizeof(spiral_matrix_t));
  matrix_struct->size = size;

  if (size <= 0) {
    matrix_struct->matrix = NULL;
    return matrix_struct;
  }

  int **matrix = calloc(size, sizeof(int *));
  for (unsigned int i = 0; i < size; i++) {
    matrix[i] = calloc(size, sizeof(int));
  }

  matrix_struct->matrix = matrix;

  for (unsigned int i = 1; i <= size * size; i++) {
    matrix[y][x] = i;

    step_count--;

    if (step_count <= 0) {
      step_count_seed--;
      step_count = step_count_seed / 2;

      direction = direction == UP ? RIGHT : direction + 1;
    }

    switch (direction) {
    case RIGHT:
      x++;
      break;
    case DOWN:
      y++;
      break;
    case LEFT:
      x--;
      break;
    case UP:
      y--;
      break;
    }
  }

  return matrix_struct;
}

void spiral_matrix_destroy(spiral_matrix_t *spiral_matrix) {
  if (spiral_matrix->matrix != NULL) {
    for (int i = 0; i < spiral_matrix->size; i++) {
      free(spiral_matrix->matrix[i]);
    }

    free(spiral_matrix->matrix);
  }
  free(spiral_matrix);
}
