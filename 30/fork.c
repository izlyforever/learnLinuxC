#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork failed");
		exit(1);
	}
	int n;
	const char *message;
	if (pid == 0) {
		message = "This is the child\n";
		n = 6;
	} else {
		message = "This is the parant\n";
		n = 3;
	}
	while (n--) {
		printf("%s", message);
		sleep(1);
	}
	return 0;
}

