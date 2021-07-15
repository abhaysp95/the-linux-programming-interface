// main file

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	int fd, cnt;
	char msg[128];
	fd = open("input.txt", O_RDWR, S_IRUSR);
	if(-1 == fd) {
		/** perror puts the message you gave, and then also prints the char*
		 * recieved from strerrror(errno) */
		/*perror(strerror(errno));*/  // this will print <same msg>: <same msg>
		perror("open");  // this will print "open: <same msg>"
		exit(EXIT_FAILURE);
	}
	cnt = read(fd, msg, 126);
	if(-1 == cnt) {
		if(EINTR == errno) {
			fprintf(stderr, "read was interrupted by signal\n");
		}
		else {
			perror(strerror(errno));
		}
	}
	printf("message: %s", msg);
	if(-1 == close(fd)) {
		perror(strerror(errno));
	}
	return 0;
}