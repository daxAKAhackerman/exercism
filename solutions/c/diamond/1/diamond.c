#include "diamond.h"
#include <stdlib.h>

char **make_diamond(const char letter) {
  unsigned int width = (letter - 'A' + 1) * 2 - 1;
  unsigned int heigth = width;
  int step = 1;
  char c = 'A';
  unsigned int pos = width / 2;

  char **diamond = calloc(heigth + 1, sizeof(char *));

  for (unsigned int i = 0; i < heigth; i++) {
    diamond[i] = calloc(width + 1, sizeof(char));

    for (unsigned int j = 0; j < width; j++) {
      if (j == pos || j == ((width - 1) - pos)) {
        diamond[i][j] = c;
      } else {
        diamond[i][j] = ' ';
      }
    }
    if (pos == width - 1) {
      step *= -1;
    }
    pos += step;
    c += step;
  }

  return diamond;
}

void free_diamond(char **diamond) {
  char **diamond_ptr = diamond;
  while (*diamond_ptr != NULL) {
    free(*diamond_ptr++);
  }
  free(diamond);
}
