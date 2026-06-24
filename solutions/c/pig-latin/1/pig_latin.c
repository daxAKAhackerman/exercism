#include "pig_latin.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool is_vowel(char c) {
  // y is apparently not a vowel
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
    return true;
  } else {
    return false;
  }
}

static bool is_xr_or_yt(const char *s) {
  if (strlen(s) < 2) {
    return false;
  } else if (strncmp(s, "xr", 2) == 0 || strncmp(s, "yt", 2) == 0) {
    return true;
  } else {
    return false;
  }
}

static unsigned int count_consonants(const char *s) {
  unsigned int count = 0;
  char c = '\0';
  while ((c = *s++) != '\0') {
    if (is_vowel(c)) {
      break;
    } else if (c == 'y') {
      // y is treated like a consonant, but stop the counts
      count++;
      break;
    } else {
      count++;
    }
  }

  return count;
}

static bool is_consonants_followed_by_qu(const char *s,
                                         unsigned int consonants_count) {
  if (strlen(s) < consonants_count + 1) {
    return false;
  } else if (s[consonants_count - 1] == 'q' && s[consonants_count] == 'u') {
    return true;
  } else {
    return false;
  }
}

static bool is_consonants_ending_with_y(const char *s,
                                        unsigned int consonants_count) {
  if (s[consonants_count - 1] == 'y') {
    return true;
  } else {
    return false;
  }
}

static char *translate_word(const char *word) {
  size_t len = strlen(word);
  // Allocated space is the word length, plus 'ay', plus a null byte
  char *r = calloc(len + 3, sizeof(char));

  // Apply translation rules
  if (is_vowel(word[0]) || is_xr_or_yt(word)) {
    strncpy(r, word, len);
  } else {
    unsigned int consonants_count = count_consonants(word);
    if (is_consonants_followed_by_qu(word, consonants_count)) {
      strncpy(r, &word[consonants_count + 1], len - (consonants_count + 1));
      strncpy(&r[len - (consonants_count + 1)], word, consonants_count + 1);
    } else if (is_consonants_ending_with_y(word, consonants_count) &&
               consonants_count > 1) {
      strncpy(r, &word[consonants_count - 1], len - (consonants_count - 1));
      strncpy(&r[len - (consonants_count - 1)], word, consonants_count - 1);
    } else {
      strncpy(r, &word[consonants_count], len - (consonants_count));
      strncpy(&r[len - (consonants_count)], word, consonants_count);
    }
  }

  // Always add 'ay' at the end
  r[len] = 'a';
  r[len + 1] = 'y';

  return r;
}

static void flush(const char *word_ptr, char *r, unsigned int c_count) {
  char *word_to_translate = NULL;
  char *translated_word = NULL;

  // Space for the word, 'ay', a space and a null byte
  word_to_translate = calloc(c_count + 2 + 1, sizeof(char));
  memcpy(word_to_translate, word_ptr, c_count);
  translated_word = translate_word(word_to_translate);

  memcpy(&r[strlen(r)], translated_word, c_count + 2);

  free(translated_word);
  free(word_to_translate);
}

char *translate(const char *phrase) {
  char c = '\0';
  const char *word_ptr = NULL;
  char *r = calloc(strlen(phrase) * 3 + 1, sizeof(char));
  unsigned int c_count = 0;

  while ((c = *phrase) != '\0') {
    if (isalpha(c)) {
      if (word_ptr == NULL) {
        word_ptr = phrase;
      }
      c_count++;
    } else if (word_ptr != NULL && c_count > 0) {
      flush(word_ptr, r, c_count);

      // Add a space between words
      r[strlen(r)] = ' ';

      word_ptr = NULL;
      c_count = 0;
    }
    phrase++;
  }

  flush(word_ptr, r, c_count);

  r = realloc(r, (strlen(r) + 1) * sizeof(char));

  return r;
}
