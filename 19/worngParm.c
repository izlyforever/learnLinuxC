int foo();
int bar();

int main(void) {
  return foo(2, 3, 5);
}

int foo(int a, int b) {
  return bar(a);
}

int bar(int c, int d) {
  int e = d - c;
  return e;
}
