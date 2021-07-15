#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

/** prints a message on standard error(prints error text correspondin to
 * current value of 'errno'- this consists of the error name, such as EPERM,
 * plus the error description as returned by stderror()-followed by the
 * formatted output specified in the argument list) */
void errMsg(const char* format, ...);

#ifdef __GNUC__
/**
  * this macro stops 'gcc -Wall' from complaining that "control reaches end of
  * non-void function" if we use the following functions to terminate main() or
  * some other non-void functions
  */
#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/**
  * similar to errMsg(), but also terminates the program, either by calling
  * exit() or, if environment variable EF_DUMPCORE is defined with a nonempty
  * string value, by calling abort() to produce a core dump file for use with
  * the debugger */
void errExit(const char* format, ...) NORETURN;

/**
  * similar to errExit() function, but differs in two respects:
  * 1. It doesn't flush standard output before printing the error message
  * 2. It terminates the process by calling _exit() instead of exit(). This
  *    causes the process to terminate without flushing stdio buffers or
  *    invoking exit handlers */
void err_exit(const char* format, ...) NORETURN;

/**
  * similar to errExit(), except that instead of printing the error text
  * corresponding to the current value of 'errno', it prints the text
  * corresponding to error number(thus, the EN suffix) given in the argument
  * 'errnum' */
void errExitEN(int errnum, const char* format, ...) NORETURN;

/**
  * used to diagnose general error, including errors from library functions
  * that don't set errno
  */
void fatal(const char* format, ...) NORETURN;

/**
  * used to diagnose errors in command-line argument usage */

void usageErr(const char* format, ...) NORETURN;

/**
  * similar to usageErr(), but intended for diagnosing errors in command-line
  * arguments specified to a program */
void cmdLineErr(const char* format, ...) NORETURN;

#endif
