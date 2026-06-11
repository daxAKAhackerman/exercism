#include "phone_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void set_error_result(char *result) {
  memset(result, 0, PHONE_NUMBER_BUFFER_LEN);
  sprintf(result, "0000000000");
}

char *phone_number_clean(const char *input) {
  char c = '\0';
  char *result = calloc(PHONE_NUMBER_BUFFER_LEN, sizeof(char));
  char *ptr_result = result;

  // Strip non-numeric characters
  while ((c = *input++) != '\0') {
    if (c >= '0' && c <= '9') {
      *ptr_result++ = c;
    }
  }

  // Handle length of 11
  if (strlen(result) == 11) {
    if (result[0] != '1') {
      // If doesn't start with 1, error
      set_error_result(result);
    } else {
      // Else just strip the leading 1
      memcpy(result, result + 1, 10 * sizeof(char));
      result[10] = '\0';
    }
  }

  // All other length except 10 are errors
  if (strlen(result) != 10) {
    set_error_result(result);
  }

  // Digits 0 and 3 can't be 0 or 1
  if ((result[0] == '0' || result[0] == '1') ||
      (result[3] == '0' || result[3] == '1')) {
    set_error_result(result);
  }

  return result;
}
