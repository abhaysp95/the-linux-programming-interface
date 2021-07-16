// main file

#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	int fd = -1;
	fd = open(argv[1], O_WRONLY);  // check if file exists
	if(-1 != fd) {  // open succeeded
		printf("[PID %ld] FILE \"%s\" already exists\n",
				(long)getpid(), argv[1]);
		close(fd);
	}
	else {
		if(ENOENT != errno)  // failed for unexpected reason
			errExit("open");
		else {
			printf("[PID %ld] File \"%s\" doesn't exist yet\n",
					(long)getpid(), argv[1]);
			if(2 < argc) {
				sleep(5);
				printf("[PID %ld] Done sleeping\n", (long)getpid());
			}
			/*fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);*/
			fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
			// using O_CREAT in conjunction with O_EXCL guarantees the atomic operation
			// of checking the prior existence of file and creation of file

			if(-1 == fd)
				errExit("open");

			char buf[50];
			snprintf(buf, 13 + sizeof(long), "%ld is the PID.", (long)getpid());

			if((write(fd, buf, strlen(buf))) == -1)
				fatal("write");
			// check the file content of argv[1] to see the difference
			// (and notice the benefit of atomic operation)

			printf("[PID %ld] Created file \"%s\" exclusively\n",
					(long)getpid(), argv[1]);  // may not be true;
		}
	}
	return 0;
}