#include "word_count.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

static int insert_word(const char *word_ptr, unsigned int letter_count,
                       word_count_word_t *words) {

  char sanitized_word[MAX_WORD_LENGTH] = {'\0'};
  char *sanitized_word_ptr = sanitized_word;

  // Lowercase the word
  for (unsigned int i = 0; i < letter_count; i++) {
    sanitized_word[i] = tolower(word_ptr[i]);
  }

  // Get rid of leading ' by replacing them with null bytes
  while (sanitized_word[letter_count - 1] == '\'') {
    sanitized_word[letter_count - 1] = '\0';
    letter_count--;
  }

  // Get rid of leading ' by incrementing the pointer
  while (*sanitized_word_ptr == '\'') {
    sanitized_word_ptr++;
    letter_count--;
  }

  // Check all word slots
  for (unsigned int i = 0; i < MAX_WORDS; i++) {
    // If the slot is empty, we know the word is not already in the struct
    if (strlen(words[i].text) == 0) {
      words[i].count = 1;
      strncpy(words[i].text, sanitized_word_ptr, letter_count);
      break;
    } else if (strncmp(words[i].text, sanitized_word_ptr, letter_count) == 0 &&
               strlen(words[i].text) == letter_count) {
      // If the slot contains the word and it has the same amount of letters,
      // increment the count. The number of letters could be different if the
      // word to insert is a substring of the word in the slot
      words[i].count++;

      // Return the number of word inserted, 0 or 1, so the caller can keep
      // track of how many unique words there are
      return 0;
    }
  }
  return 1;
}

int count_words(const char *sentence, word_count_word_t *words) {
  char c = '\0';
  bool next_non_space_is_word = true;
  unsigned int word_count = 0;
  unsigned int letter_count = 0;
  const char *beginning_of_word = NULL;

  // while the sentence contains characters
  while ((c = *sentence) != '\0') {
    // If we have a whitespace
    if (c == ' ' || c == ',' || c == '\n') {
      // Then the next non-whitespace is a word
      next_non_space_is_word = true;

      // If we were previously scanning a word
      if (letter_count > 0 && beginning_of_word != NULL) {
        // Insert it in the words struct
        word_count += insert_word(beginning_of_word, letter_count, words);

        // And reset the word scanning variables
        letter_count = 0;
        beginning_of_word = NULL;
      }
      // Next iteration
      sentence++;
      continue;
    } else if (!isalnum(c) && c != '\'') {
      // If character is not a letters, numbers or ', just go to next iteration
      sentence++;
      continue;
    } else if (next_non_space_is_word) {
      // If we got here it's because we found the start of a new word
      // Get a pointer to the beginning of the word
      beginning_of_word = sentence;
      // And be sure we don't get back here until we're in another word
      next_non_space_is_word = false;
    }

    // In any case, move the sentence pointer forward and increase the number of
    // letters
    sentence++;
    letter_count++;
  }

  // This takes care of trailing words that will not be followed by a whitespace
  if (letter_count > 0 && beginning_of_word != NULL) {
    word_count += insert_word(beginning_of_word, letter_count, words);
  }

  return word_count;
}
