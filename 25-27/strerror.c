#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void) {
	FILE *fp = fopen("abcde", "r");
	if (fp == NULL) {
    const char* err = strerror(errno);
    printf("%s\n", err);
		exit(1);
	}
	return 0;
}
