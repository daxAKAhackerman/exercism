#include "secret_handshake.h"
#include <stdlib.h>

static void reverse(char **r) {
  char *temp = r[3];
  r[3] = r[0];
  r[0] = temp;
  temp = r[2];
  r[2] = r[1];
  r[1] = temp;
}

static int compact(const void *a, const void *b) {
  if ((*(char **)a == NULL && *(char **)b == NULL) ||
      (*(char **)a != NULL && *(char **)b != NULL)) {
    return 0;
  } else if (*(char **)a == NULL) {
    return 1;
  } else {
    return -1;
  }
}

const char **commands(size_t number) {
  char **r = calloc(4, sizeof(char **));

  if (number & 0x01) {
    r[0] = "wink";
  }
  if ((number >> 1) & 0x01) {
    r[1] = "double blink";
  }
  if ((number >> 2) & 0x01) {
    r[2] = "close your eyes";
  }
  if ((number >> 3) & 0x01) {
    r[3] = "jump";
  }

  if ((number >> 4) & 0x01) {
    reverse(r);
  }

  qsort(r, 4, sizeof(char *), compact);

  return (const char **)r;
}
