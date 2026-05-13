#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
  return (robot_status_t){.direction = direction,
                          .position = (robot_position_t){.x = x, .y = y}};
}

void robot_move(robot_status_t *robot, const char *commands) {
  char c = '\0';

  while ((c = *commands++) != '\0') {
    switch (c) {
    case 'R':
      robot->direction = robot->direction == DIRECTION_WEST
                             ? DIRECTION_NORTH
                             : robot->direction + 1;
      break;
    case 'L':
      robot->direction = robot->direction == DIRECTION_NORTH
                             ? DIRECTION_WEST
                             : robot->direction - 1;
      break;
    case 'A':
      switch (robot->direction) {
      case DIRECTION_NORTH:
        robot->position.y++;
        break;
      case DIRECTION_EAST:
        robot->position.x++;
        break;
      case DIRECTION_SOUTH:
        robot->position.y--;
        break;
      case DIRECTION_WEST:
        robot->position.x--;
        break;
      default:
        break;
      }
    default:
      break;
    }
  }
}
