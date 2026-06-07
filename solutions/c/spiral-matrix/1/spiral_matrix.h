#ifndef SPIRAL_MATRIX_H
#define SPIRAL_MATRIX_H

typedef enum { RIGHT, DOWN, LEFT, UP } direction_t;

typedef struct {
  int size;
  int **matrix;
} spiral_matrix_t;

spiral_matrix_t *spiral_matrix_create(unsigned int size);

void spiral_matrix_destroy(spiral_matrix_t *spiral_matrix);

#endif
