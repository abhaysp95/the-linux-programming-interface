// main file

#include <setjmp.h>
#include <tlpi/tlpi_hdr.h>

static jmp_buf env;

static void x(void) {
	printf("x start\n");
	setjmp(env);
	printf("x finish\n");
}

static void y(void) {
	printf("y start\n");
	longjmp(env, 1);
	printf("y finish\n");
}

int main(int argc, char **argv) {
	x();
	y();
	return 0;
}