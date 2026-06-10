#include "saddle_points.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static bool is_saddle_point(uint8_t rows, uint8_t columns,
                            uint8_t matrix[rows][columns],
                            saddle_point_t candidate) {
  for (unsigned int j = 0; j < columns; j++) {
    if (matrix[candidate.row][candidate.column] < matrix[candidate.row][j]) {
      // Point is not the biggest in its row
      return false;
    }
  }

  for (unsigned int i = 0; i < rows; i++) {
    if (matrix[candidate.row][candidate.column] > matrix[i][candidate.column]) {
      // Point is not the smallest in its column
      return false;
    }
  }

  return true;
}

saddle_points_t *saddle_points(uint8_t rows, uint8_t columns,
                               uint8_t matrix[rows][columns]) {
  saddle_points_t *saddle_points = malloc(sizeof(saddle_points_t));
  saddle_points->count = 0;

  for (unsigned int i = 0; i < rows; i++) {
    for (unsigned int j = 0; j < columns; j++) {
      if (is_saddle_point(rows, columns, matrix,
                          (saddle_point_t){.row = i, .column = j})) {
        saddle_points =
            realloc(saddle_points,
                    sizeof(saddle_points_t) +
                        sizeof(saddle_point_t) * saddle_points->count + 1);
        // Return value expects positions to be index + 1
        saddle_points->points[saddle_points->count] =
            (saddle_point_t){.row = i + 1, .column = j + 1};
        saddle_points->count++;
      }
    }
  }
  return saddle_points;
}

void free_saddle_points(saddle_points_t *saddle_points) { free(saddle_points); }
