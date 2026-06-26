#include "wordy.h"
#include <stdlib.h>
#include <string.h>

static op_t get_op(char *s) {
  if (strncmp(s, "plus", 4) == 0) {
    return PLUS;
  } else if (strncmp(s, "minus", 5) == 0) {
    return MINUS;
  } else if (strncmp(s, "multiplied", 10) == 0) {
    return MULT;
  } else if (strncmp(s, "divided", 7) == 0) {
    return DIV;
  } else {
    return UNKNOWN;
  }
}

bool answer(const char *question, int *result) {
  char token[TOKEN_BUF_LEN] = {'\0'};
  char *token_ptr = token;

  expected_t expected = NUMBER;

  int number = 0;
  op_t operation = UNDEFINED;

  // Initialize the result
  *result = 0;

  // If question doesn't start with "What is ", return false
  if (question != strstr(question, "What is ")) {
    return false;
  } else {
    // Else, advance the pointer past the prefix
    question += strlen("What is ");
  }

  while ((*token_ptr = *question++) != '\0') {
    // If we reach a space or ?, parse the token
    if (*token_ptr == ' ' || *token_ptr == '?') {
      if (expected == NUMBER) {
        number = strtol(token, NULL, 10);
        switch (operation) {
        case MINUS:
          *result -= number;
          break;
        case MULT:
          *result *= number;
          break;
        case DIV:
          *result /= number;
          break;
        case PLUS:
        case UNDEFINED:
          // UNDEFINED is to handle the first number encountered, which we
          // simply want to add to the result (currently 0)
          *result += number;
          break;
        default:
          // If we get here, just abort
          return false;
        }
        // After a number, we expect an operation
        expected = OPERATION;
        // Reset the token
        token_ptr = token;
        memset(token, 0, 64 * sizeof(char));
      } else if (expected == OPERATION) {
        operation = get_op(token);

        // If unknown operation, just abort
        if (operation == UNKNOWN) {
          return false;
        }

        // * and / are followed by "by", so advance the pointer by 3 (two
        // letters plus a space)
        if (operation == MULT || operation == DIV) {
          question += 3;
        }
        // After an operation, we expect a number
        expected = NUMBER;
        // Reset the token
        token_ptr = token;
        memset(token, 0, 64 * sizeof(char));
      }
    } else {
      token_ptr++;
    }
  }

  // If after parsing everything we are still expecting a number, it's because
  // we are missing something, abort
  if (expected == NUMBER) {
    return false;
  }

  return true;
}
