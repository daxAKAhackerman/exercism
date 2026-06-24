#ifndef MEETUP_H
#define MEETUP_H

typedef enum {
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} day_of_week_t;

typedef enum { TEENTH, FIRST, SECOND, THIRD, FOURTH, LAST } week_value_t;

int meetup_day_of_month(unsigned int year, unsigned int month, const char *week,
                        const char *day_of_week);

#endif
