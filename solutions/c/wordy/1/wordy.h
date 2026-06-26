#ifndef WORDY_H
#define WORDY_H

#include <stdbool.h>

#define TOKEN_BUF_LEN 64

typedef enum { UNDEFINED = -1, PLUS, MINUS, MULT, DIV, UNKNOWN } op_t;

typedef enum {
  NUMBER,
  OPERATION,
} expected_t;

bool answer(const char *question, int *result);

#endif
