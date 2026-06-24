#include "meetup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static day_of_week_t get_day_of_week(const char *day_of_week) {
  if (strncmp(day_of_week, "Sunday", 6) == 0) {
    return SUNDAY;
  } else if (strncmp(day_of_week, "Monday", 6) == 0) {
    return MONDAY;
  } else if (strncmp(day_of_week, "Tuesday", 7) == 0) {
    return TUESDAY;
  } else if (strncmp(day_of_week, "Wednesday", 9) == 0) {
    return WEDNESDAY;
  } else if (strncmp(day_of_week, "Thursday", 8) == 0) {
    return THURSDAY;
  } else if (strncmp(day_of_week, "Friday", 6) == 0) {
    return FRIDAY;
  } else if (strncmp(day_of_week, "Saturday", 8) == 0) {
    return SATURDAY;
  } else {
    fprintf(stderr, "Bad day of week '%s'", day_of_week);
    exit(1);
  }
}

static week_value_t get_week_value(const char *week) {
  if (strncmp(week, "teenth", 6) == 0) {
    return TEENTH;
  } else if (strncmp(week, "first", 5) == 0) {
    return FIRST;
  } else if (strncmp(week, "second", 6) == 0) {
    return SECOND;
  } else if (strncmp(week, "third", 5) == 0) {
    return THIRD;
  } else if (strncmp(week, "fourth", 6) == 0) {
    return FOURTH;
  } else if (strncmp(week, "last", 4) == 0) {
    return LAST;
  } else {
    fprintf(stderr, "Bad week value '%s'", week);
    exit(1);
  }
}

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week,
                        const char *day_of_week) {
  struct tm *gmtime_ptr = NULL;

  // Get first of month
  struct tm fotm = {
      .tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = 1, .tm_hour = -1};
  time_t first_of_the_month = mktime(&fotm);
  gmtime_ptr = gmtime(&first_of_the_month);
  struct tm normalized_fotm = *gmtime_ptr;

  // And the last of the month
  struct tm lotm = {
      .tm_year = year - 1900, .tm_mon = month, .tm_mday = 0, .tm_hour = -1};
  time_t last_of_the_month = mktime(&lotm);
  gmtime_ptr = gmtime(&last_of_the_month);
  struct tm normalized_lotm = *gmtime_ptr;

  // Get the week and day_of_week as indexes
  week_value_t week_value = get_week_value(week);
  day_of_week_t dow = get_day_of_week(day_of_week);

  // Switch cases cannot contain declarations, so doing it here
  unsigned int thirteenth = 0;
  unsigned int offset = 0;

  switch (week_value) {
  case TEENTH:
    // Find the DOW of the 13th, then increment the offset until the desired DOW
    thirteenth = (normalized_fotm.tm_wday + 12) % 7;
    while ((thirteenth + offset) % 7 != dow) {
      offset++;
    }
    return 13 + offset;
  case FIRST:
  case SECOND:
  case THIRD:
  case FOURTH:
    // Increment the offset to find the first occurence of the desired DOW, then
    // scale with the week value
    while ((normalized_fotm.tm_wday + offset) % 7 != dow) {
      offset++;
    }
    return 1 + offset + 7 * (week_value - 1);
  case LAST:
    // Increment the offset to find the first occurence of the desired DOW
    // We add 7 to the wday to avoid negative integers. Modulo will cancel it
    // anyway.
    while ((normalized_lotm.tm_wday + 7 - offset) % 7 != dow) {
      offset++;
    }
    return normalized_lotm.tm_mday - offset;
  default:
    fprintf(stderr, "Unhandled case");
    exit(1);
  }
}
