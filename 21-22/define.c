#define x 3
#define f(a) f(x * (a))
#undef x
#define x 2
#define g f
#define t(a) a

int main(void) {
  // gcc -E
  // f(2 * (0)) + t(1);
  t(t(g)(0) + t)(1);
  return 0;
}
