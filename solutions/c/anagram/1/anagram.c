#include "anagram.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static bool strncaseicmp(const char *s1, const char *s2, size_t len) {
  for (unsigned int i = 0; i < len; i++) {
    if (tolower(s1[i]) != tolower(s2[i])) {
      return false;
    }
  }

  return true;
}

static void set_stats(uint8_t *subject_stats, const char *subject) {
  char c = '\0';

  while ((c = *subject++) != '\0') {
    if (c >= 'a') {
      c -= 'a' - 'A';
    }

    subject_stats[c - 'A']++;
  }
}

void find_anagrams(const char *subject, struct candidates *candidates) {
  uint8_t subject_stats[NUM_OF_LETTERS] = {0};
  set_stats(subject_stats, subject);

  for (unsigned int i = 0; i < candidates->count; i++) {
    // If different length, not an anagram
    if (strlen(subject) != strlen(candidates->candidate[i].word)) {
      candidates->candidate[i].is_anagram = NOT_ANAGRAM;
      continue;
    }

    // If same word, not an anagram
    if (strncaseicmp(subject, candidates->candidate[i].word, strlen(subject))) {
      candidates->candidate[i].is_anagram = NOT_ANAGRAM;
      continue;
    }

    candidates->candidate[i].is_anagram = IS_ANAGRAM;
    uint8_t candidate_stats[NUM_OF_LETTERS] = {0};
    set_stats(candidate_stats, candidates->candidate[i].word);

    for (unsigned int j = 0; j < NUM_OF_LETTERS; j++) {
      if (subject_stats[j] != candidate_stats[j]) {
        candidates->candidate[i].is_anagram = NOT_ANAGRAM;
        break;
      }
    }
  }
}
