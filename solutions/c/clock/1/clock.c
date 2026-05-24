#include "clock.h"
#include <stdio.h>
#include <string.h>

static unsigned int sanitize_minutes(int hour, int minute) {
  // Get number of total minutes
  int minutes_total = hour * 60 + minute;
  // Get rid of the rollover
  minutes_total %= (24 * 60);
  // Get rid of negative
  if (minutes_total < 0) {
    minutes_total += (24 * 60);
  }

  return minutes_total;
}

clock_t clock_create(int hour, int minute) {
  int minutes_total = sanitize_minutes(hour, minute);

  hour = minutes_total / 60;
  minute = minutes_total % 60;

  clock_t clock = {0};
  sprintf(clock.text, "%02d:%02d", (unsigned int)hour, (unsigned int)minute);
  return clock;
}

clock_t clock_add(clock_t clock, int minute_add) {
  unsigned int hour = 0;
  unsigned int minute = 0;
  sscanf(clock.text, "%02u:%02u", &hour, &minute);

  unsigned int minutes_total = sanitize_minutes(hour, minute + minute_add);

  return clock_create(minutes_total / 60, minutes_total % 60);
}

clock_t clock_subtract(clock_t clock, int minute_subtract) {
  unsigned int hour = 0;
  unsigned int minute = 0;
  sscanf(clock.text, "%02u:%02u", &hour, &minute);

  unsigned int minutes_total = sanitize_minutes(hour, minute - minute_subtract);

  return clock_create(minutes_total / 60, minutes_total % 60);
}

bool clock_is_equal(clock_t a, clock_t b) {
  return strncmp(a.text, b.text, MAX_STR_LEN) == 0;
}
