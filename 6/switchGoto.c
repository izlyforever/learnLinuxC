#include <stdio.h>

// ideal from https://en.wikipedia.org/wiki/Duff%27s_device
void ncopy(int* from, int* to, unsigned count) {
  int n = count / 8;
  switch (count % 8) {
    case 0: while (n-- > 0) {
              *to++ = *from++;
    case 7:   *to++ = *from++;
    case 6:   *to++ = *from++;
    case 5:   *to++ = *from++;
    case 4:   *to++ = *from++;
    case 3:   *to++ = *from++;
    case 2:   *to++ = *from++;
    case 1:   *to++ = *from++;
            }
  }
}
// -Wno-implicit-fallthrough or using C++17/C23 [[fallthrough]];

#define AR_LEN(a) sizeof (a) / sizeof (a[0])

int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void test(int count) {
  int b[AR_LEN(a) + 1] = {};
  ncopy(a, b, count);

  printf("test(%d)\n", count);
  for (int i = 0; i < AR_LEN(b); ++i) {
    printf("%d ", b[i]);
  }
  printf("\n");
}

int main(void) {
  test(0);
  test(1);
  test(7);
  test(8);
  test(10);
  return 0;
}
