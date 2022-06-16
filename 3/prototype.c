#include <stdio.h>

int main(void) {
  printf("Three empty lines:\n");
  threeline();
  printf("Another three empty lines:\n");
  threeline();
  return 0;
}

void newline(void) {
  printf("\n");
}

void threeline(void) {
  newline();
  newline();
  newline();
}
