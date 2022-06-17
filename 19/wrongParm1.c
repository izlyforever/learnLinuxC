int foo();
int bar();

int main(void) {
  return foo(2, 3, 5);
}

// a = 2, b = 3
int foo(int a, int b) {
  return bar(a);
}

// c = 2, d = 3
int bar(int c, int d) {
  int e = d - c;
  return e;
}
// gcc wrongParm1.c -g
// see bt in gcc
