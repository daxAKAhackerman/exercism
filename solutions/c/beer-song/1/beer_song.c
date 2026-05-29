#include "beer_song.h"
#include <stdint.h>
#include <stdio.h>

void recite(uint8_t start_bottles, uint8_t take_down, char **song) {
  char limit = start_bottles - take_down;

  for (; start_bottles > limit; start_bottles--) {
    if (start_bottles > 1) {
      snprintf(*song++, MAX_LINE_LEN,
               "%d bottles of beer on the wall, %d bottles of beer.",
               start_bottles, start_bottles);
    } else if (start_bottles == 1) {
      snprintf(*song++, MAX_LINE_LEN,
               "%d bottle of beer on the wall, %d bottle of beer.",
               start_bottles, start_bottles);
    } else {
      snprintf(*song++, MAX_LINE_LEN,
               "No more bottles of beer on the wall, no more bottles of beer.");
      snprintf(
          *song++, MAX_LINE_LEN,
          "Go to the store and buy some more, 99 bottles of beer on the wall.");
      break;
    }

    if (start_bottles - 1 > 1) {
      snprintf(
          *song++, MAX_LINE_LEN,
          "Take one down and pass it around, %d bottles of beer on the wall.",
          start_bottles - 1);
    } else if (start_bottles - 1 == 1) {
      snprintf(
          *song++, MAX_LINE_LEN,
          "Take one down and pass it around, %d bottle of beer on the wall.",
          start_bottles - 1);
    } else {
      snprintf(*song++, MAX_LINE_LEN,
               "Take it down and pass it around, no more bottles of beer on "
               "the wall.");
    }
    ++song;
  }
}
