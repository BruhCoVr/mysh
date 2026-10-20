/**
 * @file stderr.h 
    * @brief Functions for printing to stderr
*/

#include <unistd.h>
#include <lib.h>
#include <constants.h>


int errprint(const char *s);
int errprintln(const char *s);