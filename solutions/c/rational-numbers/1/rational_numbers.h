#ifndef RATIONAL_NUMBERS_H
#define RATIONAL_NUMBERS_H

#include <math.h>
#include <stdint.h>

typedef struct {
  int numerator;
  int denominator;
} rational_t;

static inline double root(double p, double q) { return pow(p, 1.0 / q); }

rational_t add(rational_t a, rational_t b);

rational_t subtract(rational_t a, rational_t b);

rational_t multiply(rational_t a, rational_t b);

rational_t divide(rational_t a, rational_t b);

rational_t absolute(rational_t n);

rational_t exp_rational(rational_t n, int exp);

float exp_real(uint16_t n, rational_t exp);

rational_t reduce(rational_t n);

#endif
