// main file

/** transitional LFS API version */

#define _LARGEFILE64_SOURCE

#include <sys/stat.h>
#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	printf("This is \"Transitional LFS API version\" of \
			program to demonstrate opening of large files\n.");
	int fd = -1;
	off64_t off = 0;

	if(3 != argc || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s pathname offset\n", argv[0]);

	fd = open64(argv[1], O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR);
	if(-1 == fd)
		errExit("open64");

	off = atoll(argv[2]);
	if(lseek64(fd, off, SEEK_SET) == -1)
		errExit("lseek64");

	if(write(fd, "test", 64) == -1)
		errExit("write");
	exit(EXIT_SUCCESS);
}