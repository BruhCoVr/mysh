/**
 * @file stderr.h 
    * @brief Functions for printing to stderr
*/

#include <unistd.h>
#include <lib.h>

#define STDOUT_FD 1
#define STDERR_FD 2
#define STDIN_FD 0


int errprint(const char *s);
int errprintln(const char *s);