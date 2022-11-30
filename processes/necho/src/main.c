// main file

#include <tlpi/tlpi_hdr.h>

/** you can also have argc and argv as global variable(though this is
 * less common approach). You can also take a look at commandline
 * arguments in '/proc/PID/cmdline' file */

extern char** argv;
extern int argc;

int main() {
	for(int j = 0; j < argc; j++)
		printf("argv[%d] = %s\n", j, argv[j]);
	return 0;
}

/*int main(int argc, char **argv) {
	for(int j = 0; j < argc; j++)
		printf("argv[%d] = %s\n", j, argv[j]);
	return 0;
}*/