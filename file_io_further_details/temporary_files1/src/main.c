// main file

#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	int fd = -1;

	// atleast XXXXXX are required to create unique file name by mkstemp
	char template[] = "/tmp/somestringXXXXXX";

	/** creates the file with read and write file permissions for the file
	 * owner(no permission for other users) and opens it with O_EXCL
	 * flag(which guarentees that caller has exclusive acess to this file) */
	fd = mkstemp(template); // template will be modified
	if(-1 == fd)
		errExit("mkstemp");
	printf("Generated filename was: %s\n", template);

	// sleep(10);  // if you want to check if file exists in that location, uncomment it
	/** if you'll add sleep after unlink(...) you'll not see the file, cause 'name' disappears immediately */

	// Name disappears immediately, but the file is removed after close();
	unlink(template);


	// some I/O system calls to this file - read(), write() and so on

	if(-1 == close(fd))
		errExit("close");

	exit(EXIT_SUCCESS);
}