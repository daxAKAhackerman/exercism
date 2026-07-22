#include "zebra_puzzle.h"
#include <stdbool.h>
#include <stdio.h>

static house_t houses[NUMBER_OF_HOUSES] = {0};

static bool has_duplicates() {
  unsigned int i;
  unsigned int j;

  for (i = 0; i < NUMBER_OF_HOUSES - 1; i++) {
    for (j = i + 1; j < NUMBER_OF_HOUSES; j++) {
      if (houses[i].animal != ANIMAL_UNKNOWN &&
          houses[i].animal == houses[j].animal) {
        return true;
      } else if (houses[i].color != COLOR_UNKNOWN &&
                 houses[i].color == houses[j].color) {
        return true;
      } else if (houses[i].drink != DRINK_UKNOWN &&
                 houses[i].drink == houses[j].drink) {
        return true;
      } else if (houses[i].hobby != HOBBY_UNKNOWN &&
                 houses[i].hobby == houses[j].hobby) {
        return true;
      } else if (houses[i].nationality != NATIONALITY_UNKNOWN &&
                 houses[i].nationality == houses[j].nationality) {
        return true;
      }
    }
  }
  return false;
}

static bool basic_condition_passes(int k1, int v1, int k2, int v2) {
  if (k1 == v1 && not_equal_and_defined(k2, v2)) {
    return false;
  } else if (k2 == v2 && not_equal_and_defined(k1, v1)) {
    return false;
  }

  return true;
}

static bool basic_position_condition_passes(int k, int v, int pk, int pv) {
  if (pk == pv && not_equal_and_defined(k, v)) {
    return false;
  } else if (k == v && pk != pv) {
    return false;
  }

  return true;
}

static bool validate_solution() {
  unsigned int i;

  if (has_duplicates()) {
    return false;
  }

  for (i = 0; i < NUMBER_OF_HOUSES; i++) {
    // The person in the middle house drinks milk.
    if (!basic_position_condition_passes(houses[i].drink, MILK, i, 2))
      return false;

    // The Norwegian lives in the first house.
    if (!basic_position_condition_passes(houses[i].nationality, NORWAY, i, 0))
      return false;

    // The Englishman lives in the red house.
    if (!basic_condition_passes(houses[i].color, RED, houses[i].nationality,
                                ENGLISH))
      return false;

    // The Spaniard owns the dog.
    if (!basic_condition_passes(houses[i].nationality, SPANISH,
                                houses[i].animal, DOG))
      return false;

    // The person in the green house drinks coffee.
    if (!basic_condition_passes(houses[i].color, GREEN, houses[i].drink,
                                COFFEE))
      return false;

    // The Ukrainian drinks tea.
    if (!basic_condition_passes(houses[i].nationality, UKRAINE, houses[i].drink,
                                TEA))
      return false;

    // The snail owner likes to go dancing.
    if (!basic_condition_passes(houses[i].animal, SNAIL, houses[i].hobby,
                                DANCING))
      return false;

    // The person in the yellow house is a painter.
    if (!basic_condition_passes(houses[i].color, YELLOW, houses[i].hobby,
                                PAINTING))
      return false;

    // The person who plays football drinks orange juice.
    if (!basic_condition_passes(houses[i].hobby, FOOTBALL, houses[i].drink,
                                ORANGE_JUICE))
      return false;

    // The Japanese person plays chess.
    if (!basic_condition_passes(houses[i].nationality, JAPAN, houses[i].hobby,
                                CHESS))
      return false;

    // The green house is immediately to the right of the ivory house.
    if (houses[i].color == GREEN && i == 0) {
      return false;
    } else if (houses[i].color == GREEN &&
               not_equal_and_defined(houses[i - 1].color, IVORY)) {
      return false;
    } else if (houses[i].color == IVORY && i == NUMBER_OF_HOUSES - 1) {
      return false;
    } else if (houses[i].color == IVORY &&
               not_equal_and_defined(houses[i + 1].color, GREEN)) {
      return false;
    }

    // The person who enjoys reading lives in the house next to the person with
    // the fox.
    if (houses[i].hobby == READING) {
      if (i == 0) {
        if (not_equal_and_defined(houses[i + 1].animal, FOX)) {
          return false;
        }
      } else if (i == NUMBER_OF_HOUSES - 1) {
        if (not_equal_and_defined(houses[i - 1].animal, FOX)) {
          return false;
        }
      } else {
        if (not_equal_and_defined(houses[i - 1].animal, FOX) &&
            not_equal_and_defined(houses[i + 1].animal, FOX)) {
          return false;
        }
      }
    } else if (houses[i].animal == FOX) {
      if (i == 0) {
        if (not_equal_and_defined(houses[i + 1].hobby, READING)) {
          return false;
        }
      } else if (i == NUMBER_OF_HOUSES - 1) {
        if (not_equal_and_defined(houses[i - 1].hobby, READING)) {
          return false;
        }
      } else {
        if (not_equal_and_defined(houses[i - 1].hobby, READING) &&
            not_equal_and_defined(houses[i + 1].hobby, READING)) {
          return false;
        }
      }
    }

    // The painter's house is next to the house with the FOX.
    if (houses[i].hobby == PAINTING) {
      if (i == 0) {
        if (not_equal_and_defined(houses[i + 1].animal, HORSE)) {
          return false;
        }
      } else if (i == NUMBER_OF_HOUSES - 1) {
        if (not_equal_and_defined(houses[i - 1].animal, HORSE)) {
          return false;
        }
      } else {
        if (not_equal_and_defined(houses[i - 1].animal, HORSE) &&
            not_equal_and_defined(houses[i + 1].animal, HORSE)) {
          return false;
        }
      }
    } else if (houses[i].animal == HORSE) {
      if (i == 0) {
        if (not_equal_and_defined(houses[i + 1].hobby, PAINTING)) {
          return false;
        }
      } else if (i == NUMBER_OF_HOUSES - 1) {
        if (not_equal_and_defined(houses[i - 1].hobby, PAINTING)) {
          return false;
        }
      } else {
        if (not_equal_and_defined(houses[i - 1].hobby, PAINTING) &&
            not_equal_and_defined(houses[i + 1].hobby, PAINTING)) {
          return false;
        }
      }
    }

    // The Norwegian lives next to the blue house.
    if (houses[i].nationality == NORWAY) {
      if (i == 0) {
        if (not_equal_and_defined(houses[i + 1].color, BLUE)) {
          return false;
        }
      } else if (i == NUMBER_OF_HOUSES - 1) {
        if (not_equal_and_defined(houses[i - 1].color, BLUE)) {
          return false;
        }
      } else {
        if (not_equal_and_defined(houses[i - 1].color, BLUE) &&
            not_equal_and_defined(houses[i + 1].color, BLUE)) {
          return false;
        }
      }
    } else if (houses[i].color == BLUE) {
      if (i == 0) {
        if (not_equal_and_defined(houses[i + 1].nationality, NORWAY)) {
          return false;
        }
      } else if (i == NUMBER_OF_HOUSES - 1) {
        if (not_equal_and_defined(houses[i - 1].nationality, NORWAY)) {
          return false;
        }
      } else {
        if (not_equal_and_defined(houses[i - 1].nationality, NORWAY) &&
            not_equal_and_defined(houses[i + 1].nationality, NORWAY)) {
          return false;
        }
      }
    }
  }
  return true;
}

static bool is_complete() {
  for (unsigned int i = 0; i < NUMBER_OF_HOUSES; i++) {
    if (houses[i].animal == ANIMAL_UNKNOWN) {
      return false;
    } else if (houses[i].color == COLOR_UNKNOWN) {
      return false;
    } else if (houses[i].drink == DRINK_UKNOWN) {
      return false;
    } else if (houses[i].hobby == HOBBY_UNKNOWN) {
      return false;
    } else if (houses[i].nationality == NATIONALITY_UNKNOWN) {
      return false;
    }
  }
  return true;
}

static void set_value_for_depth_level(unsigned int depth, int v) {
  unsigned int i = depth / 5;
  int prop = depth % 5;

  switch (prop) {
  case 0:
    houses[i].animal = v;
    break;
  case 1:
    houses[i].color = v;
    break;
  case 2:
    houses[i].drink = v;
    break;
  case 3:
    houses[i].hobby = v;
    break;
  case 4:
    houses[i].nationality = v;
    break;
  }
}

static void copy_houses(house_t d[NUMBER_OF_HOUSES],
                        house_t s[NUMBER_OF_HOUSES]) {
  for (unsigned int i = 0; i < NUMBER_OF_HOUSES; i++) {
    d[i] = s[i];
  }
}

static bool backtrack(unsigned int depth) {
  house_t snapshot[NUMBER_OF_HOUSES] = {0};
  copy_houses(snapshot, houses);
  for (int candidate = 1; candidate <= 5; candidate++) {
    set_value_for_depth_level(depth, candidate);
    if (validate_solution()) {
      if (is_complete()) {
        return true;
      }
      if (backtrack(depth + 1))
        return true;
    }
  }
  copy_houses(houses, snapshot);
  return false;
}

static char *get_nat_str(int i) {
  switch (i) {
  case 1:
    return "Englishman";
  case 2:
    return "Spaniard";
  case 3:
    return "Ukrainian";
  case 4:
    return "Norwegian";
  default:
    return "Japanese";
  }
}

solution_t solve_puzzle(void) {
  backtrack(0);

  int drinks_water;
  for (unsigned int i = 0; i < NUMBER_OF_HOUSES; i++) {
    if (houses[i].drink == WATER) {
      drinks_water = houses[i].nationality;
    }
  }

  int owns_zebra;
  for (unsigned int i = 0; i < NUMBER_OF_HOUSES; i++) {
    if (houses[i].animal == ZEBRA) {
      owns_zebra = houses[i].nationality;
    }
  }

  solution_t solution = {.drinks_water = get_nat_str(drinks_water),
                         .owns_zebra = get_nat_str(owns_zebra)};

  return solution;
}
