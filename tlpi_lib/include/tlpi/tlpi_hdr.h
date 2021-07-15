#ifndef TLPI_HDR_H
#define TLPI_HDR_H  // prevent accidental double inclusions

#include <sys/types.h>  // type definitions
#include <stdio.h>  // standard I/O functions
#include <stdlib.h>  // prototypes of commonly used library functions, plus EXIT_SUCCESS and EXIT_FAILURE constansts

#include <unistd.h>  // prototypes for many system calls
#include <errno.h>  // declares errno and defines error constants
#include <string.h>  // commonly used string-handling functions

#include "get_num.h"  // declares our functions for handling numeric arguments(getInt(), getLong())

#include "error_functions.h"  // declares our error-handlin functions
typedef enum {FALSE, TRUE} Boolean;

#define min(m, n) ((m) > (n) ? (n) : (m))
#define max(m, n) ((m) > (n) ? (m) : (n))

#endif
