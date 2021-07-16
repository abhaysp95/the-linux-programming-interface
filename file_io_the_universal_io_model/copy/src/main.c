// main file

#include <sys/stat.h>
#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

/** Allow "cc -D" to override this defination */
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char **argv) {
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead = 0;
	char buf[BUF_SIZE];

	if(3 != argc || strncmp(argv[1], "--help", 7) == 0)
		usageErr("%s old-file new-file\n", argv[0]);

	inputFd = open(argv[1], O_RDONLY);
	if(inputFd == -1)
		errExit("opening file %s", argv[1]);

	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP
		| S_IROTH | S_IWOTH;

	outputFd = open(argv[2], openFlags, filePerms);

	/** transfer data until end of input or error is met */
	while((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
		if(write(outputFd, buf, numRead) != numRead)
			fatal("couldn't write whole buffer");
	if(numRead == -1)
		errExit("read");

	if(close(inputFd) == -1)
		errExit("close input");
	if(close(outputFd) == -1)
		errExit("close output");

	exit(EXIT_SUCCESS);
}


/** NOTE: this file also works as second exercise for this chapter */