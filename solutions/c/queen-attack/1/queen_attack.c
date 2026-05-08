#include "queen_attack.h"
#include <stdint.h>
#include <stdlib.h>

attack_status_t can_attack(position_t queen_1, position_t queen_2) {
  char positions_as_array[] = {queen_1.column, queen_1.row, queen_2.column,
                               queen_2.row};

  // Queens can't be on the same square
  if ((queen_1.column == queen_2.column) && (queen_1.row == queen_2.row)) {
    return INVALID_POSITION;
  }

  // Positions need to be valid
  for (int i = 0; i < NUMBERS_OF_POSITIONS; i++) {
    if (positions_as_array[i] < 0 || positions_as_array[i] > 7) {
      return INVALID_POSITION;
    }
  }

  if (queen_1.row == queen_2.row) {
    return CAN_ATTACK;
  } else if (queen_1.column == queen_2.column) {
    return CAN_ATTACK;
  } else if (abs(queen_1.row - queen_2.row) ==
             abs(queen_1.column - queen_2.column)) {
    return CAN_ATTACK;
  }

  return CAN_NOT_ATTACK;
}
