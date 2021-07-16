// main file

#define _FILE_OFFSET_BITS 64

#include <sys/stat.h>
#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	printf("This is \"Transitional LFS API version\" of \
			program to demonstrate opening of large files\n.");
	int fd = -1;
	off_t off = 0;

	if(3 != argc || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s pathname offset\n", argv[0]);

	fd = open(argv[1], O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR);
	if(-1 == fd)
		errExit("open64");

	off = atoll(argv[2]);
	if(lseek(fd, off, SEEK_SET) == -1)
		errExit("lseek64");

	if(write(fd, "test", 64) == -1)
		errExit("write");
	exit(EXIT_SUCCESS);
}

/** with _FILE_OFFSET_BITS feature test macro defined, you don't need to call 64
 * bit version(one with 64 as suffix) functions of File I/O */