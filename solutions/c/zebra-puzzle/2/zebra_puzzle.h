#ifndef ZEBRA_PUZZLE_H
#define ZEBRA_PUZZLE_H

#define NUMBER_OF_HOUSES 5

#define not_equal_and_defined(a, b) (((a) != (b)) && (a) != 0)

typedef struct {
  const char *drinks_water;
  const char *owns_zebra;
} solution_t;

typedef enum {
  COLOR_UNKNOWN,
  RED,
  GREEN,
  IVORY,
  YELLOW,
  BLUE,
} color_t;

typedef enum {
  NATIONALITY_UNKNOWN,
  ENGLISH,
  SPANISH,
  UKRAINE,
  NORWAY,
  JAPAN,
} nationality_t;

typedef enum {
  ANIMAL_UNKNOWN,
  DOG,
  SNAIL,
  FOX,
  HORSE,
  ZEBRA,
} animal_t;

typedef enum {
  DRINK_UKNOWN,
  COFFEE,
  TEA,
  MILK,
  ORANGE_JUICE,
  WATER,
} drink_t;

typedef enum {
  HOBBY_UNKNOWN,
  DANCING,
  PAINTING,
  READING,
  FOOTBALL,
  CHESS,
} hobby_t;

typedef struct {
  animal_t animal;
  color_t color;
  drink_t drink;
  hobby_t hobby;
  nationality_t nationality;
} house_t;

solution_t solve_puzzle(void);

#endif
