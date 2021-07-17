// main file

#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	int fd = -1;
	ssize_t wbyte = -1;
	char buf[] = "this is something new which I don't know of";

	if(2 > argc || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s file", argv[0]);

	fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, S_IRUSR | S_IWUSR);
	if(-1 == fd)
		errExit("open");

	/** first write */
	wbyte = write(fd, buf, strlen(buf));
	if(wbyte < strlen(buf))
		printf("partial write");
	else if(-1 == wbyte)
		errExit("write");

	/** seek to 5 pos. from start */
	if(-1 == lseek(fd, 5, SEEK_SET))
		errExit("lseek");

	/** write again */
	wbyte = write(fd, buf, strlen(buf) - 10);
	if(wbyte < strlen(buf) - 10)
		printf("partial write");
	else if(-1 == wbyte)
		errExit("write");


	/** close */
	if(-1 == close(fd))
		errExit("close");

	exit(EXIT_SUCCESS);
}