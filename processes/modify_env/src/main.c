// main file

#define _GNU_SOURCE

#include <stdlib.h>
#include <tlpi/tlpi_hdr.h>

extern char** environ;

int main(int argc, char **argv) {
	clearenv();  /* erase entire environment */

	for(int j = 1; j < argc; j++)
		if(putenv(argv[j]) != 0) errExit("putenv: %s", argv[j]);

	if(setenv("GREET", "Hello World", 0) == -1) errExit("setenv");

	unsetenv("BYE");

	for(char** ep = environ; *ep != NULL; ep++) puts(*ep);

	exit(EXIT_SUCCESS);
}

/** putenv() function adds a new variable to the calling process's
 * environment or modifies the value of an existing variable. It
 * doesn't duplicates the string pointed to by string(argument), so be
 * cautious */

/** setenv() function creates a new environment variable by allocating
 * a memory buffer for a string of the form 'name=value', and copying
 * the strings pointed by name and value to that buffer. This function
 * doesn't change the environment if the variable identified by name
 * already exists and overwrite(3rd arg of setenv()) has the value 0
 * */

/** unsetenv() is opposite of setenv() */


/** clearenv() does 'environ = NULL;'. However, if setenv() and
 * putenv() find that environ is NULL, they create a new environment
 * list and set environ pointing to it, with the result that the above
 * loop(one which prints env) operates correctly */