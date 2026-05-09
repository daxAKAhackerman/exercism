#include "dnd_character.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

static int comp(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int modifier(int score) { return (int)floor(((double)score - 10.0) / 2.0); }

int ability(void) {
  int dice_rolls[4] = {0};
  int ability_value = 0;

  srand(time(NULL));
  for (int i = 0; i < 4; i++) {
    dice_rolls[i] = (rand() % 6) + 1;
  }

  qsort(dice_rolls, 4, sizeof(int), comp);

  for (int i = 1; i < 4; i++) {
    ability_value += dice_rolls[i];
  }

  return ability_value;
}

dnd_character_t make_dnd_character(void) {
  int constitution = ability();

  return (dnd_character_t){ability(),
                           ability(),
                           constitution,
                           ability(),
                           ability(),
                           ability(),
                           10 + modifier(constitution)};
}
