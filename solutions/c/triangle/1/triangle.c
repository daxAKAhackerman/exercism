#include "triangle.h"
#include <stdbool.h>

static bool is_triangle(triangle_t triangle) {
  if (triangle.a <= 0 || triangle.b <= 0 || triangle.c <= 0) {
    return false;
  }

  if (triangle.a + triangle.b < triangle.c ||
      triangle.b + triangle.c < triangle.a ||
      triangle.a + triangle.c < triangle.b) {
    return false;
  }

  return true;
}

bool is_equilateral(triangle_t triangle) {
  if (is_triangle(triangle) && triangle.a == triangle.b &&
      triangle.b == triangle.c) {
    return true;
  }

  return false;
}

bool is_isosceles(triangle_t triangle) {
  if (is_triangle(triangle) &&
      (triangle.a == triangle.b || triangle.b == triangle.c ||
       triangle.c == triangle.a)) {
    return true;
  }
  return false;
}

bool is_scalene(triangle_t triangle) {
  if (is_triangle(triangle) && triangle.a != triangle.b &&
      triangle.b != triangle.c && triangle.c != triangle.a) {
    return true;
  }

  return false;
}
