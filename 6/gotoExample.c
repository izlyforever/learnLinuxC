#include <stdio.h>

int main(void) {

  int i = 0;
label:
  printf("%d\n", i);
  ++i;
  if (i < 10) {
    goto label;
  }
  return 0;
}
