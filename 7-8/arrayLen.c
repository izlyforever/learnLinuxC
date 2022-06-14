#include <stdio.h>

// calculate the length of an array
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))

void solve() {
  int a[3][2];

  int x = ARRLEN(a);
  int x0 = ARRLEN(a[0]);

  printf("%d %d\n", x, x0);
}

int main() {
  solve();
  return 0;
}
