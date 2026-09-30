/**
 * @file output.h
 * @brief Functions for writing output to stdout
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <unistd.h>

#include <constants.h>

/**
 * @overload
 */
int print_str(const char *s);

/**
 * @overload
 */
int print_int(const int value);

/**
 * @overload
 */
int print_size_t(const size_t value);

/**
 * @overload
 */
int print_ssize_t(const ssize_t value);

/**
 * @brief Prints a value to the standard output (stdout).
 *
 * @param VALUE The value to print.
 *
 * @return 0 on success, or -1 on error.
 */
#define print(VALUE) _Generic((VALUE), \
    int: print_int, \
    size_t: print_size_t, \
    ssize_t: print_ssize_t, \
    default: print_str \
)(VALUE)

/**
 * @brief Prints a null-terminated string to the standard output (stdout) followed by a newline character.
 *
 * @param s The string to print.
 *
 * @return 0 on success, or -1 on error.
 */
int println(const char *s);

#endif
