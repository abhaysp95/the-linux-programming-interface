#include "tlpi/error_functions.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void
sysconfPrint(const char *msg, int name)
{
	long lim;

	errno = 0;
	lim = sysconf(name);
	if (-1 != lim) {
		printf("%s %ld\n", msg, lim);
	} else {
		if (0 == errno) {
			printf("%s (indeterminate)\n,", msg);
		} else {
			errExit("sysconf %s", msg);
		}
	}
}

int main(void) {
	sysconfPrint("_SC_ARG_MAX: ", _SC_ARG_MAX);
	sysconfPrint("_SC_LOGIN_NAME_MAX: ", _SC_LOGIN_NAME_MAX);
	sysconfPrint("_SC_OPEN_MAX: ", _SC_OPEN_MAX);
	sysconfPrint("_SC_NGROUPS_MAX: ", _SC_NGROUPS_MAX);
	sysconfPrint("_SC_PAGESIZE: ", _SC_PAGESIZE);
	sysconfPrint("_SC_RTSIG_MAX: ", _SC_RTSIG_MAX);

	exit(EXIT_SUCCESS);
}
