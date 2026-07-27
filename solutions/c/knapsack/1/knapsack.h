#ifndef KNAPSACK_H
#define KNAPSACK_H

typedef struct {
  unsigned int weight;
  unsigned int value;
} item_t;

unsigned int maximum_value(unsigned int maximum_weight, item_t items[],
                           unsigned int item_count);

#endif
