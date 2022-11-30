// main file

#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

void file_status_flags(int fd, char* name) {
	int fflags = fcntl(fd, F_GETFL);
	if(-1 == fflags)
		errExit("fnctl F_GETFL %s", name);
	printf("file opened %s O_APPEND(check from \"%s\")\n", (fflags & O_APPEND) ? "with" : "without", name);
}

void file_offset(int fd, char* name) {
	off_t offset = lseek(fd, 0, SEEK_CUR);
	if(-1 == offset)
		errExit("lseek SEEK_CUR %s", name);
	printf("Current file offset with \"%s\" is %ld\n", name, (long)offset);
}

int main(int argc, char **argv) {
	int fd = -1;

	if(2 > argc || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s file\n", argv[0]);

	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(-1 == fd)
		errExit("open");

	int dfd = dup(fd);
	if(-1 == dfd)
		errExit("dup");

	printf("check for O_APPEND initially\n");
	file_status_flags(dfd, "dfd");
	/** set O_APPEND flag */
	if(-1 == fcntl(dfd, F_SETFL, O_APPEND))
		errExit("fcntl F_SETFL dfd");
	printf("check after adding O_APPEND\n");
	file_status_flags(fd, "fd");

	printf("initial file offset\n");
	file_offset(dfd, "dfd");
	if(-1 == lseek(dfd, 10, SEEK_END))
		errExit("lseek SEEK_END");
	printf("check after changing offset value\n");
	file_offset(fd, "fd");

	if(-1 == close(fd))
		errExit("close fd");
	exit(EXIT_SUCCESS);
}

/** Note: these are check with duplicated file descriptor, not for two different
 * process(opening same file(same inode)). Although, result should be same
 * because 'file_ptr' of different processes opening same file, share common
 * 'file offset', 'status flag' and 'inode ptr' from 'open file table' */