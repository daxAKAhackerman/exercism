#include "rational_numbers.h"
#include <math.h>
#include <stdlib.h>

static int gcd(int a, int b) {
  int n = abs(a < b ? a : b);

  while ((a % n != 0 || b % n != 0) && n > 1) {
    n--;
  }

  return n;
}

rational_t reduce(rational_t n) {
  if (n.numerator == 0) {
    n.denominator = 1;
    return n;
  }

  int gcd_n = gcd(n.numerator, n.denominator);

  n.numerator /= gcd_n;
  n.denominator /= gcd_n;

  if (n.denominator < 0) {
    n.numerator *= -1;
    n.denominator *= -1;
  }

  return n;
}

rational_t add(rational_t a, rational_t b) {
  rational_t r = {.numerator =
                      a.numerator * b.denominator + b.numerator * a.denominator,
                  .denominator = a.denominator * b.denominator};

  return reduce(r);
}

rational_t subtract(rational_t a, rational_t b) {
  rational_t r = {.numerator =
                      a.numerator * b.denominator - b.numerator * a.denominator,
                  .denominator = a.denominator * b.denominator};

  return reduce(r);
}

rational_t multiply(rational_t a, rational_t b) {
  rational_t r = {.numerator = a.numerator * b.numerator,
                  .denominator = a.denominator * b.denominator};

  return reduce(r);
}

rational_t divide(rational_t a, rational_t b) {
  rational_t r = {.numerator = a.numerator * b.denominator,
                  .denominator = b.numerator * a.denominator};

  return reduce(r);
}

rational_t absolute(rational_t n) {
  rational_t r = {.numerator = abs(n.numerator),
                  .denominator = abs(n.denominator)};

  return reduce(r);
}

rational_t exp_rational(rational_t n, int exp) {
  rational_t r = {0};
  if (exp >= 0) {
    r.numerator = pow(n.numerator, exp);
    r.denominator = pow(n.denominator, exp);
  } else {
    r.numerator = pow(n.denominator, abs(exp));
    r.denominator = pow(n.numerator, abs(exp));
  }

  return reduce(r);
}

float exp_real(uint16_t n, rational_t exp) {
  return (float)root(pow(n, exp.numerator), exp.denominator);
}
