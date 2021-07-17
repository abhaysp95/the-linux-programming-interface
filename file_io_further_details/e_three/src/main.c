// main file

#include <fcntl.h>
#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {

	int fd = -1;

	if(argc < 3 || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s filename num-bytes [ch] [x]\n", argv[0]);

	long num = getLong(argv[2], GN_NONNEG | GN_ANY_BASE, "num-bytes");

	Boolean x = (argc == 5) && (strncmp(argv[4], "x", 1) == 0);

	int flags = O_WRONLY | O_CREAT | O_TRUNC;

	if(!x)
		flags |= O_APPEND;

	fd = open(argv[1], flags, S_IRUSR | S_IWUSR);
	if(-1 == fd)
		errExit("open");
	printf("file opened(PID): %ld\n", (long)getpid());


	int fflags = -1, accessmode = -1;
	fflags = fcntl(fd, F_GETFL);
	if(-1 == fflags)
		errExit("fcntl");

	accessmode = fflags & O_ACCMODE;
	if(O_APPEND == accessmode)   /** this doesn't seem to work */
		printf("file opened with O_APPEND\n");
	else
		printf("file not opened with O_APPEND\n");

	char* ch = ((4 <= argc) ? argv[3] : "c");

	printf("before write(PID): %ld\n", (long)getpid());
	while(num--) {
		if(x) {
			if(-1 == lseek(fd, 1, SEEK_END))
				errExit("lseek");
		}
		if(-1 == write(fd, ch, 1))
			errExit("write");
		// this isn't going to do any change
		/** if(x) {
			if(-1 == pwrite(fd, ch, 1, lseek(fd, 0, SEEK_END)))
				errExit("pwrite");
		}
		else {
			if(-1 == write(fd, ch, 1))
				errExit("write");
		} */
	}
	printf("after write: %ld\n", (long)getpid());

	if(-1 == close(fd))
		errExit("close");

	exit(EXIT_SUCCESS);
}

/**
 * 1. First run:
 *    $ ./e_three f1.txt 100000 a & ./e_three f1.txt 100000 b
 *    file size: around 2mb(approx. 1 mb from both execution)
 * 2. Second run:
 *    $ ./e_three f2.txt 100000 a x & ./e_three f2.txt 100000 b x
 *    file size: little more than 1 mb
 *
 * Reason:
 * -------
 * Reason behind providing 'a' & 'b' as different character for both execution
 * is to check that how much time a job is preempted by the second one, that
 * means to see if all the 'b's are written after 'a's or they are in mixed
 * way(and they are in mixed way). But still, every write is done. Now, since
 * 'execution without "x"' means to open file in O_APPEND(append mode), that
 * means "seek and write" is going to be atomic operation. And that's why even
 * though first job(execution of program) is preempted by second one, almost
 * every 'a' and 'b' are written.
 *
 * But 'execution with "x"' is different story. In it files are opened with no
 * append mode, in program before every write their is a lseek operation, which
 * sets the offset to SEEK_END. Now, technically write should happen at SEEK_END
 * + 1, but let's a job 'A' wrote and then set the 'file offset' to SEEK_END and
 * now this file offset is updated in 'open file table'(look for "Relationship
 * between 'file descriptor table' and 'open file table'"). Now, consider a
 * scenario where job 'A' has just done write and got preempted by job 'B', at
 * this point 'file offset' in 'open file table' would be SEEK_END + 1(courtesy
 * of write()), but since there's a lseek() before every write, lseek() from job
 * 'B' will set the 'file offset' to SEEK_END and then write, which in turn
 * would mean overwriting in the offset. Same is true, if job 'A' gets preempted
 * after lseek() but before write() operation and job 'B' starts from lseek()
 * operation.
 */