// main file

#include <ctype.h>
#include <tlpi/tlpi_hdr.h>

#define printable(ch) (isprint((unsigned char)ch) ? ch : '#')

// try noreturn here

static void usageError(char* progName, char* msg, int opt) {
	if(NULL != msg && 0 != opt)
		fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
	fprintf(stderr, "Usage: %s [-p arg] [-x]\n", progName);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	int opt = 0, xfnd = 0;
	char* pstr = NULL;

	/** setting ':' at start of optarg is same as saying opterr = 0(though
	 * it has some difference) also, the option which require an arugment
	 * should be followed by a ':', initially 'x' doesn't require argument,
	 * but if you'll make it 'x:' then it'll require argument and case ':'
	 * will be executed. Putting + means that it avoids permutation of argv
	 * :: specifies optional argument, but there should be no space between
	 * option and arugment */
	while((opt = getopt(argc, argv, "+:p::x")) != -1) {
		printf("opt =%3d (%c); optind = %d", opt, printable(opt), optind);
		if(opt == '?' || opt == ':')
			printf("; optopt =%3d (%c)", optopt, printable(optopt));
		printf("\n");

		switch(opt) {
			case 'p':
				pstr = optarg;
				printf("I came here\n");
				break;
			case 'x':
				xfnd++;
				break;
			case ':':
				usageError(argv[0], "Missing argument", optopt);
			case '?':
				usageError(argv[0], "Unrecognized option", optopt);
			default:
				fatal("Unexpected case in switch()");
		}
	}

	if(0 != xfnd) printf("-x was specified (count=%d)\n", xfnd);
	if(NULL != pstr)
		printf("-p was specified with the value \"%s\"\n", pstr);
	if(optind < argc)
		printf("First nonoption argument is \"%s\" at argv[%d]\n", argv[optind], optind);
	exit(EXIT_SUCCESS);
}

/** there are also 'getopt_long, getopt_long_only' and 'getsubopt' for more commandline parsing */