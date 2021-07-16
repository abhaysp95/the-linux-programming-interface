// main file

#include <fcntl.h>
#include <ctype.h>
#include <tlpi/tlpi_hdr.h>

#define BUF_SIZE 100
#define printable(ch) (isprint((unsigned char)ch) ? ch : '#')

static void usageError(char* prog_name, char* msg, int opt) {
	if(NULL != msg && 0 != opt)
		fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
	fprintf(stderr, "Usage: %s [-a] [file]\n", prog_name);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	int stdin_fd = dup(STDIN_FILENO);  // there's a chance that value of STDIN_FILENO can change
	int num_read = 0, write_fd = -1;
	char buf[BUF_SIZE];
	Boolean is_file_open = FALSE;

	int opt = 0;
	char* pstr = NULL;

	while((opt = getopt(argc, argv, ":a:")) != -1) {
		switch(opt) {
			case 'a':
				pstr = optarg;
				write_fd = open(pstr, O_RDWR | O_APPEND | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
				is_file_open = TRUE;
				if(-1 == write_fd)
					errExit("open file");
				break;
			case ':':
				usageError(argv[0], "missing argument", optopt);
				break;
			case '?':
				usageError(argv[0], "unrecognized option", optopt);
				break;
			default:
				fatal("Unexpected case occured");
				break;
		}
	}

	if(-1 == write_fd)  // that means "option -a" was not provided
		if(optind < argc) {
			write_fd = open(argv[optind], O_RDWR | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			is_file_open = TRUE;
		}
	if(TRUE == is_file_open)
		if(-1 == write_fd)
			errExit("open file");

	while((num_read = read(stdin_fd, buf, BUF_SIZE)) > 0) {
		if(TRUE == is_file_open)
			if(write(write_fd, buf, num_read) != num_read)
				fatal("write to file");
		// ===> this is what I did(since, read lenght is stored in num_read)
		printf("%.*s", num_read, buf);
	}
	if(-1 == num_read) errExit("read");

	if(TRUE == is_file_open)
		if(close(write_fd) == -1)
			errExit("close file");

	exit(EXIT_SUCCESS);
}