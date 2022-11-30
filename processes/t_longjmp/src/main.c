// main file

#include <setjmp.h>
#include <tlpi/tlpi_hdr.h>

static jmp_buf env;

static void f2(void) {
	longjmp(env, 2);
}

static void f1(int argc) {
	if(argc == 1) longjmp(env, 1);
	f2();
}

int main(int argc, char **argv) {
	switch(setjmp(env)) {
		case 0:  /* this is the return after the initial setjmp() */
			printf("Calling f1() after initial setjmp()\n");
			f1(argc);  /* never returns... */
			break;  /* ...but this is good form */
		case 1:
			printf("We jumped back from f1()\n");
			break;
		case 2:
			printf("We jumped back from f2()\n");
			break;
	}

	exit(EXIT_SUCCESS);
}

/** QUES: how does static function behaves in stack table ? */


/** The initial setjmp() returns 0, while the later "faked" return
 * supplies whatever value is specified in the val argument(sec arg of
 * longjmp()) of the longjmp(). Specifying the val argument to
 * longjmp() as 0 would, if unchecked cause the faked return from
 * setjmp() to look as thought it were the initial return. For this
 * reason, if val is specified as 0, longjmp() actually uses the value
 * The env argument used by bth function supplies the glue enabling
 * the jump to be accomplished. The setjmp() call saves various
 * information about the current process environment into env. This
 * allows longjmp() call, which must specify the same env variable, to
 * perform fake return. Since the setjmp() and longjmp() calls are in
 * different functions(otherwise, we could simply use goto), env is
 * declared globall or, less commonly, passed as a function argument.
 * */