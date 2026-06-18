#include "run_length_encoding.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void flush(unsigned int run_count, char **r_ptr, char run_char) {
  if (run_count > 1) {
    sprintf(*r_ptr, "%d%c", run_count, run_char);
    *r_ptr += strlen(*r_ptr);
  } else {
    *(*r_ptr)++ = run_char;
  }
}

char *encode(const char *text) {
  char c = '\0';
  char run_char = text[0];
  unsigned int run_count = 0;

  char *r = calloc(strlen(text) + 1, sizeof(char));
  char *r_ptr = r;

  while ((c = *text++) != '\0') {
    if (c != run_char) {
      flush(run_count, &r_ptr, run_char);
      run_char = c;
      run_count = 1;
    } else {
      run_count++;
    }
  }

  flush(run_count, &r_ptr, run_char);

  r = realloc(r, strlen(r) + 1);

  return r;
}

char *decode(const char *data) {
  char c = '\0';
  char *data_ptr = (char *)data;
  char *buf = calloc(READ_BUFF_LEN, sizeof(char));
  char *buf_ptr = buf;
  char *r = calloc(1, sizeof(char));
  char *r_ptr = r;
  unsigned int count = 0;

  while ((c = *data_ptr++) != '\0') {
    if (isalpha(c) || c == ' ') {
      count = strtol(buf, NULL, 10);
      buf_ptr = buf;
      memset(buf, 0, READ_BUFF_LEN);
      r = realloc(r,
                  ((r_ptr - r) + (count == 0 ? 1 : count) + 1) * sizeof(char));
      r_ptr = r + strlen(r);
      for (unsigned int i = 0; i < (count == 0 ? 1 : count); i++) {
        *r_ptr++ = c;
      }
      *r_ptr = '\0';
      count = 0;
    } else if (isdigit(c)) {
      *buf_ptr++ = c;
    }
  }

  free(buf);

  return r;
}
