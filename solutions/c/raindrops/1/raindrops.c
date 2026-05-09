#include "raindrops.h"
#include <stdio.h>
#include <string.h>

void convert(char result[], int drops) {
  int divisible = 0;

  if (drops % 3 == 0) {
    strcat(result, "Pling");
    divisible = 1;
  }
  if (drops % 5 == 0) {
    strcat(result, "Plang");
    divisible = 1;
  }
  if (drops % 7 == 0) {
    strcat(result, "Plong");
    divisible = 1;
  }

  if (!divisible) {
    sprintf(result, "%d", drops);
  }
}
