/**
 * @file lib.h
 * @brief A collection of utility functions
 */


#ifndef LIB_H
#define LIB_H

#include <stddef.h>
#include <unistd.h>

#include <constants.h>

/**
 * @brief Returns the length of a null-terminated string.
 * 
 * @param s Pointer to the null-terminated string.
 * 
 * @return The length of the string (number of characters before the null terminator).
 */
int str_len(const char *s);

/**
 * @brief Reverses a null-terminated string in place.
 * 
 * @param str Pointer to the null-terminated string to reverse.
 * 
 * @return Pointer to the reversed string.
 */
char* reverse(char* str);

/**
 * @overload
 */
char* itoa_int(int value, char* str);

/**
 * @overload
 */
char* itoa_size_t(size_t value, char* str);

/**
 * @overload
 */
char* itoa_ssize_t(ssize_t value, char* str);

/**
 * @brief Converts an number to its string representation.
 *
 * @param VALUE The integer value to convert.
 * @param STR The buffer to store the resulting string.
 *
 * @return Pointer to the resulting string.
 */
#define itoa(VALUE, STR) _Generic((VALUE), \
    int: itoa_int, \
    size_t: itoa_size_t, \
    ssize_t: itoa_ssize_t \
)(VALUE, STR)
    

/**
 * @overload
 */
ssize_t print_str(const char *s);

/**
 * @overload
 */
ssize_t print_int(const int value);

/**
 * @overload
 */
ssize_t print_size_t(const size_t value);

/**
 * @overload
 */
ssize_t print_ssize_t(const ssize_t value);

/**
 * @brief Prints a value to the standard output (stdout).
 * 
 * @param VALUE The value to print.
 * 
 * @return The number of bytes written, or -1 on error.
 */
#define print(VALUE) _Generic((VALUE), \
    int: print_int, \
    size_t: print_size_t, \
    ssize_t: print_ssize_t, \
    default: print_str \
)(VALUE)

int strcmp(const char *str1, const char *str2);

#endif