#include "tlpi/error_functions.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// pathconf() and fpathconf() limit values can change over the lifetime of a process, unlike sysconf
static void
fpathconfPrint(const char *msg, int fd, int name)
{
	long lim = 0;

	errno = 0;
	lim = fpathconf(fd, name);
	if (-1 != lim) {
		printf("%s %ld\n", msg, lim);
	} else {
		if (0 == errno) {
			printf("%s (indeterminate)\n", msg);
		} else {
			errExit("fpathconf %s", msg);
		}
	}
}

int main(void)
{
	fpathconfPrint("_PC_NAME_MAX: ", STDIN_FILENO, _PC_NAME_MAX);
	fpathconfPrint("_PC_PATH_MAX: ", STDIN_FILENO, _PC_PATH_MAX);
	fpathconfPrint("_PC_PIPE_BUF: ", STDIN_FILENO, _PC_PIPE_BUF);

	exit(EXIT_SUCCESS);

}
