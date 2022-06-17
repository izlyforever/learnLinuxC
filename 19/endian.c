#include <stdio.h>

typedef union {
  struct {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
  } point;
  unsigned int x;
} demo_type;

int main(void) {
  demo_type u = {{ 'a', 'b', 'c', 'd' }};
  unsigned int t = u.x;
  printf("%u\n", t);
  unsigned int ans = (unsigned int)u.point.a;
  ans += (unsigned int)u.point.b << 8;
  ans += (unsigned int)u.point.c << 16;
  ans += (unsigned int)u.point.d << 24;
  printf("%u\n", ans);
  return 0;
}