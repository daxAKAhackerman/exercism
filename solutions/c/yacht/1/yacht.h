#ifndef YACHT_H
#define YACHT_H

#define NUM_FACES 5

typedef enum {
  ONES,
  TWOS,
  THREES,
  FOURS,
  FIVES,
  SIXES,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  LITTLE_STRAIGHT,
  BIG_STRAIGHT,
  CHOICE,
  YACHT
} category_t;

typedef struct {
  int faces[NUM_FACES];
} dice_t;

int score(dice_t dice, category_t category);

#endif
