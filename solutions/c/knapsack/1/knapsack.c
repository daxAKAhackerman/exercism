#include "knapsack.h"

unsigned int maximum_value(unsigned int maximum_weight, item_t items[],
                           unsigned int item_count) {
  unsigned int total_weight;
  unsigned int total_value;

  unsigned int max_value = 0;

  // Each candidate has two possible states (in the bag or not), so the number
  // of possibilities is 2^item_count
  unsigned int number_of_candidates = 1 << item_count;

  // Each candidate is represented by an integer where each bit is the state of
  // an item
  for (unsigned int candidate = 0; candidate <= number_of_candidates;
       candidate++) {

    total_weight = 0;
    total_value = 0;

    // For each item's bit that is 1
    for (unsigned int i = 0; i < item_count; i++) {
      if ((candidate >> i) & 0x1) {
        total_weight += items[i].weight;
        total_value += items[i].value;
      }
    }

    if (total_weight <= maximum_weight && total_value > max_value)
      max_value = total_value;
  }

  return max_value;
}
