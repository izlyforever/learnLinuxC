/* a.c */
// int printf(const char* fmt, ...);
void swap(int *a, int *b);
extern int shared;
int main() {
	int a = 100;
	swap(&a, &shared);
//	printf("%d\n", a);
}
