#include "flower_field.h"
#include <stdlib.h>

char **annotate(const char **garden, const size_t rows) {
  if (rows == 0) {
    return NULL;
  }

  char *garden_row = NULL;
  unsigned int count = 0;
  unsigned int row_len = 0;

  garden_row = (char *)garden[0];
  while (*garden_row++ != '\0') {
    row_len++;
  }

  char **annotation = calloc(rows + 1, sizeof(char *));

  for (unsigned int i = 0; i < rows; i++) {
    annotation[i] = calloc(row_len + 1, sizeof(char));
    for (unsigned int j = 0; j < row_len; j++) {
      if (garden[i][j] == '*') {
        annotation[i][j] = '*';
        continue;
      }

      count = 0;
      if (i > 0) {
        if (j > 0 && garden[i - 1][j - 1] == '*') {
          count++;
        }
        if (garden[i - 1][j] == '*') {
          count++;
        }
        if (j < row_len && garden[i - 1][j + 1] == '*') {
          count++;
        }
      }

      if (j > 0 && garden[i][j - 1] == '*') {
        count++;
      }
      if (j < row_len && garden[i][j + 1] == '*') {
        count++;
      }

      if (i < rows - 1) {
        if (j > 0 && garden[i + 1][j - 1] == '*') {
          count++;
        }
        if (garden[i + 1][j] == '*') {
          count++;
        }
        if (j < row_len && garden[i + 1][j + 1] == '*') {
          count++;
        }
      }

      annotation[i][j] = count > 0 ? count + '0' : ' ';
    }
  }

  return annotation;
}

void free_annotation(char **annotation) {
  char **annotation_ptr = annotation;
  while (*annotation_ptr != NULL) {
    free(*annotation_ptr++);
  }
  free(annotation);
}
