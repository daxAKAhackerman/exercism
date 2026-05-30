#include "yacht.h"
#include <stdlib.h>

static int comp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
static int sum_of_dices(dice_t dice, unsigned int num_rolls) {
  int sum = 0;
  for (unsigned int i = 0; i < num_rolls; i++) {
    sum += dice.faces[i];
  }
  return sum;
}

int score(dice_t dice, category_t category) {
  int score = 0;
  qsort(dice.faces, NUM_FACES, sizeof(int), comp);

  switch (category) {
  case ONES:
  case TWOS:
  case THREES:
  case FOURS:
  case FIVES:
  case SIXES:
    for (unsigned int i = 0; i < NUM_FACES; i++) {
      if (dice.faces[i] == (int)category + 1) {
        score += category + 1;
      }
    }
    return score;
  case FULL_HOUSE:
    if (dice.faces[0] != dice.faces[4] &&
        ((dice.faces[0] == dice.faces[2] && dice.faces[3] == dice.faces[4]) ||
         (dice.faces[0] == dice.faces[1] && dice.faces[2] == dice.faces[4]))) {
      return sum_of_dices(dice, NUM_FACES);
    }
    break;
  case FOUR_OF_A_KIND:
    if (dice.faces[0] == dice.faces[3] || dice.faces[1] == dice.faces[4]) {
      return dice.faces[1] * 4;
    }
    break;
  case LITTLE_STRAIGHT:
  case BIG_STRAIGHT:
    if (dice.faces[0] != (int)category - 7) {
      return 0;
    }
    for (int i = 0; i < NUM_FACES; i++) {
      if (dice.faces[i] != i + (int)category - 7) {
        return 0;
      }
    }
    return 30;
  case CHOICE:
    return sum_of_dices(dice, NUM_FACES);
  case YACHT:
    if (dice.faces[0] == dice.faces[4]) {
      return 50;
    }
    break;
  default:
    break;
  }

  return 0;
}
