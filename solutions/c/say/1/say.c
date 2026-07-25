#include "say.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void get_word_for_number(char *buf, unsigned int n) {
  switch (n) {
  case 0:
    strcat(buf, "zero");
    break;
  case 1:
    strcat(buf, "one");
    break;
  case 2:
    strcat(buf, "two");
    break;
  case 3:
    strcat(buf, "three");
    break;
  case 4:
    strcat(buf, "four");
    break;
  case 5:
    strcat(buf, "five");
    break;
  case 6:
    strcat(buf, "six");
    break;
  case 7:
    strcat(buf, "seven");
    break;
  case 8:
    strcat(buf, "eight");
    break;
  case 9:
    strcat(buf, "nine");
    break;
  case 10:
    strcat(buf, "ten");
    break;
  case 11:
    strcat(buf, "eleven");
    break;
  case 12:
    strcat(buf, "twelve");
    break;
  case 13:
    strcat(buf, "thirteen");
    break;
  case 14:
    strcat(buf, "fourteen");
    break;
  case 15:
    strcat(buf, "fifteen");
    break;
  case 16:
    strcat(buf, "sixteen");
    break;
  case 17:
    strcat(buf, "seventeen");
    break;
  case 18:
    strcat(buf, "eighteen");
    break;
  case 20:
    strcat(buf, "twenty");
    break;
  case 30:
    strcat(buf, "thirty");
    break;
  case 40:
    strcat(buf, "forty");
    break;
  case 50:
    strcat(buf, "fifty");
    break;
  case 60:
    strcat(buf, "sixty");
    break;
  case 70:
    strcat(buf, "seventy");
    break;
  case 80:
    strcat(buf, "eighty");
    break;
  case 90:
    strcat(buf, "ninety");
    break;
  default:
    fprintf(stderr, "Can't convert %d", n);
    break;
  }
}

static void handle_1_to_99(char *buf, unsigned int n) {
  if (n < 20)
    get_word_for_number(buf, n);
  else {
    get_word_for_number(buf, n - (n % 10));
    if (n % 10 != 0) {
      strcat(buf, "-");
      get_word_for_number(buf, n % 10);
    }
  }
}

static void handle_1_to_999(char *buf, unsigned int n) {
  if (n < 100) {
    handle_1_to_99(buf, n);
  } else {
    get_word_for_number(buf, n / 100);
    strcat(buf, " hundred");
    if (n % 100 != 0) {
      strcat(buf, " ");
      handle_1_to_99(buf, n % 100);
    }
  }
}

int say(int64_t input, char **ans) {
  if (input < 0 || input > 999999999999)
    return -1;

  char *buf = calloc(INITIAL_BUFFER_SIZE, sizeof(char));

  if (input == 0)
    get_word_for_number(buf, 0);

  while (input > 0) {
    if (strlen(buf) > 0)
      strcat(buf, " ");
    if (input >= 1000000000) {
      handle_1_to_999(buf, input / 1000000000);
      strcat(buf, " billion");
      input %= 1000000000;
    } else if (input >= 1000000) {
      handle_1_to_999(buf, input / 1000000);
      strcat(buf, " million");
      input %= 1000000;
    } else if (input >= 1000) {
      handle_1_to_999(buf, input / 1000);
      strcat(buf, " thousand");
      input %= 1000;
    } else if (input > 0) {
      handle_1_to_999(buf, input);
      input = 0;
    }
  }

  buf = realloc(buf, (strlen(buf) + 1) * sizeof(char));
  *ans = buf;
  return 0;
}
