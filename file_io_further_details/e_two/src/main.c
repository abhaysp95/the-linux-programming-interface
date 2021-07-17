// main file

#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	int fd = -1;
	off_t offset = 0;

	if(argc != 2 || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s file\n", argv[0]);

	fd = open(argv[1], O_WRONLY | O_APPEND);
	if(-1 == fd)
		errExit("open");

	printf("current offset(before lseek): %lld\n", (long long)lseek(fd, 0, SEEK_CUR));

	/** seek to begining */
	if(-1 == lseek(fd, offset, SEEK_SET))
		errExit("lseek");

	printf("current offset(after lseek): %lld\n", (long long)lseek(fd, 0, SEEK_CUR));

	// writing custom data
	if(-1 == write(fd, "this is a line from program\n", 28))
		errExit("write");

	if(-1 == close(fd))
		errExit("close");

	exit(EXIT_SUCCESS);
}

/** if open in O_APPEND mode, whatever you set the offset, before each write(),
 * the file offset is positioned at the end of the file, as if with lseek() */