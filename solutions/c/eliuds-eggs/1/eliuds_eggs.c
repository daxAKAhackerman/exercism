#include "eliuds_eggs.h"

unsigned int egg_count(int num) {
  unsigned int num_of_eggs = 0;

  while (num != 0) {
    num_of_eggs += num & 1;
    num >>= 1;
  }

  return num_of_eggs;
}
