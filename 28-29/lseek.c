#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);
	if (fd < 0) {
		perror("open /dev/tty fail\n");
		exit(1);
	}
	char buf[10];
	for (int i = 0; i < 5; ++i) {
		int n = read(fd, buf, 10);
		if (n >= 0) {
			break;
		}
		if (errno != EAGAIN) {
			perror("read /dev/tty\n");
			exit(1);
		}
		sleep(1);
		write(STDOUT_FILENO, "try again\n", strlen("try agian\n"));
	}
	close(fd);
	return 0;
}
