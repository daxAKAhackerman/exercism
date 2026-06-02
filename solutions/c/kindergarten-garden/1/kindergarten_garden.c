#include "kindergarten_garden.h"

plants_t plants(const char *diagram, const char *student) {
  plants_t plants = {0};
  char plants_raw[4] = {'\0'};

  students_t studend_id = (students_t)*student - 'A';

  const char *diagram_second_row = diagram;
  while (*diagram_second_row++ != '\n')
    ;

  plants_raw[0] = diagram[studend_id * 2];
  plants_raw[1] = diagram[studend_id * 2 + 1];
  plants_raw[2] = diagram_second_row[studend_id * 2];
  plants_raw[3] = diagram_second_row[studend_id * 2 + 1];

  for (unsigned int i = 0; i < 4; i++) {
    switch (plants_raw[i]) {
    case 'G':
      plants.plants[i] = GRASS;
      break;
    case 'C':
      plants.plants[i] = CLOVER;
      break;
    case 'R':
      plants.plants[i] = RADISHES;
      break;
    case 'V':
      plants.plants[i] = VIOLETS;
      break;
    }
  }

  return plants;
}
