// main file

#include <tlpi/tlpi_hdr.h>

int main(int argc, char **argv) {
	FILE* unique_file = NULL;

	unique_file = tmpfile();
	if(NULL == unique_file)
		errExit("tmpfile");

	/** fix here */

	if(-1 == write(unique_file, "this", 4))
		errExit("write");
	return 0;
}