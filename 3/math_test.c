#include <math.h>
#include <stdio.h>

// math function lies in libm.so
// gcc math_test.c -lm
int main(void) {
  double pi = 3.1416;
  printf("sin(pi / 2) = %f\n", sin(pi / 2));
  printf("ln(1) = %f\n", log(1.0));
  return 0;
}
