// main file

#include <sys/uio.h>
#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	int rfd = -1, wfd = -1;
	struct stat myStruct; // first buffer
	int x;                // second buffer
#define STR_SZ 100
	/*char myStruct[STR_SZ];*/
	/*char x[STR_SZ];*/
	char str[STR_SZ];     // third buffer
	struct iovec iov[3] = {
		{
			.iov_base = &myStruct,
			.iov_len = sizeof(struct stat)
		},
		{
			.iov_base = &x,
			.iov_len = sizeof(x)
		},
		{
			.iov_base = str,
			.iov_len = STR_SZ
		}
	};
	ssize_t numRead = 0, numWrite = 0, totRequired = 0;
	for(size_t i = 0; i < 3; i++) totRequired += iov[i].iov_len;

	if(2 > argc || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s file\n", argv[0]);

	rfd = open(argv[1], O_RDONLY);
	if(-1 == rfd)
		errExit("open read file");

	if(argc > 2) {
		wfd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, S_IRUSR | S_IWUSR);
		if(-1 == wfd)
			errExit("open write file");
	}

	numRead = readv(rfd, iov , 3);
	if(-1 == numRead)
		errExit("readv");

	if(totRequired > numRead)
		printf("Read fewer bytes than requested\n");

	printf("total bytes requested: %ld; bytes read: %ld\n",
			(long)totRequired, (long)numRead);

	/** write to file */
	if(argc > 2) {
		numWrite = writev(wfd, iov, 3);
		if(-1 == numWrite)
			errExit("writev");

		if(numWrite < totRequired)
			printf("Write fewer bytes than requested\n");

		/** if there are partial write to file, than the file could
		 * contain some unwanted symbol(data) from the unfilled buffers,
		 * since I think those are written as well */

		if(close(wfd) == -1)
			errExit("close write file");
	}

	if(close(rfd) == -1)
		errExit("close read file");

	exit(EXIT_SUCCESS);
}