#include <stdio.h>

int main(void) {
	void foo();
	char c = 60;
	foo(c);
	return 0;
}

void foo(double d) {
	printf("%f\n", d);
}
