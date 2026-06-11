#include "pascals_triangle.h"
#include <stdint.h>
#include <stdlib.h>

uint8_t **create_triangle(size_t rows) {
  uint8_t **triangle = calloc(rows == 0 ? 1 : rows, sizeof(uint8_t *));

  if (rows == 0) {
    triangle[0] = calloc(1, sizeof(uint8_t));
    return triangle;
  }

  for (unsigned int i = 0; i < rows; i++) {
    triangle[i] = calloc(rows, sizeof(uint8_t));
    for (unsigned int j = 0; j <= i; j++) {
      if (j == 0 || j == i) {
        triangle[i][j] = 1;
      } else {
        triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
      }
    }
  }

  return triangle;
}

void free_triangle(uint8_t **triangle, size_t rows) {
  for (unsigned int i = 0; i < rows; i++) {
    free(triangle[i]);
  }
  free(triangle);
}
