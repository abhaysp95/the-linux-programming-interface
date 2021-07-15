// main file

#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	size_t len;
	off_t offset;  // data-type for offset(with lseek)
	int fd, ap, j;
	char* buf;
	ssize_t numRead = 0, numWritten = 0;

	if(argc < 3 || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s file {r<length>|R<Length>|w<string>|s<offset>}...\n", argv[0]);

	fd = open(argv[1], O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);  // perm: rw-rw-rw
	if(-1 == fd)
		errExit("open");

	for(ap = 2; ap < argc; ap++) {
		switch(argv[ap][0]) {
			case 'r':  // display bytes at current offset, as text
			case 'R':  // display bytes at current offset, in hex
				len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);

				buf = (char*)malloc(len);
				if(NULL == buf) errExit("malloc");

				numRead = read(fd, buf, len);
				if(-1 == numRead) errExit("read");

				if(0 == numRead) {
					printf("%s: end-of-file\n", argv[ap]);
				}
				else {
					printf("%s: ", argv[ap]);
					for(j = 0; j < numRead; j++) {
						if('r' == argv[ap][0])
							printf("%c ", isprint((unsigned char)buf[j]) ? buf[j] : '?');
						else
							printf("%02x ", (unsigned int)buf[j]);
					}
					printf("\n");
				}
				free(buf);
				break;
			case 'w':  // write string at current offset
				numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
				if(-1 == numWritten) errExit("write");
				printf("%s: wrote %ld bytes\n", argv[ap], (long)numWritten);
				break;
			case 's':
				offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
				if(lseek(fd, offset, SEEK_SET) == -1)
					errExit("lseek");
				printf("%s: seek succeeded\n", argv[ap]);
				break;
			default:
				cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
		}
	}

	exit(EXIT_SUCCESS);
}