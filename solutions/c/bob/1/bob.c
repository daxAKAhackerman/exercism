#include "bob.h"
#include <stdbool.h>
#include <string.h>

static char *strip_leading_whitespaces(const char *s) {
  while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') {
    s++;
  }
  return (char *)s;
}

static size_t strlen_without_whitespaces(char *s) {
  for (unsigned int i = strlen(s); i > 0; i--) {
    if (s[i - 1] != ' ' && s[i - 1] != '\t' && s[i - 1] != '\r' &&
        s[i - 1] != '\n') {
      return i;
    }
  }

  return 0;
}

char *hey_bob(char *greeting) {
  char *s = strip_leading_whitespaces(greeting);
  size_t len = strlen_without_whitespaces(s);

  if (len == 0) {
    return "Fine. Be that way!";
  }

  bool question = s[len - 1] == '?' ? true : false;

  bool has_at_least_one_lower_case = false;
  bool has_at_least_one_upper_case = false;

  char c = '\0';
  while ((c = *greeting++) != '\0') {
    if (c >= 'a' && c <= 'z') {
      has_at_least_one_lower_case = true;
    } else if (c >= 'A' && c <= 'Z') {
      has_at_least_one_upper_case = true;
    }
  }

  bool all_upper_case =
      !has_at_least_one_lower_case && has_at_least_one_upper_case;

  if (all_upper_case && question) {
    return "Calm down, I know what I'm doing!";
  } else if (question) {
    return "Sure.";
  } else if (all_upper_case) {
    return "Whoa, chill out!";
  }

  return "Whatever.";
}
