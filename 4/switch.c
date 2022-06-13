#include <stdio.h>

void printDay(int day) {
  switch (day) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      printf("Weekday\n");
      break;
    case 6:
    case 7:
      printf("Weekend\n");
      break;
    default:
      printf("illegal day number!\n");
      break;
  }
}

int main(void) {
  printDay(1);
  printDay(6);
  printDay(11);
  return 0;
}
