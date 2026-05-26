#include "square_root.h"

unsigned int square_root(unsigned int number) {
  unsigned int result = 0;
  unsigned int power = 1;

  while (power <= number) {
    power <<= 2;
  }

  power >>= 2;

  while (power != 0) {
    if (number >= result + power) {
      number -= result + power;
      result += 2 * power;
    }
    result /= 2;
    power /= 4;
  }

  return result;
}
