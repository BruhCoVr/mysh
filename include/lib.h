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
 * @brief Compares two null-terminated strings.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 *
 * @return 1 if the strings are equal, 0 otherwise
 */
int str_eq(const char *str1, const char *str2);

/**
 * @brief Prints a null-terminated string to the standard output (stdout) followed by a newline character.
 *
 * @param s The string to print.
 *
 * @return 0 on success, or -1 on error.
 */
int println(const char *s);

/**
 * @brief Copies a null-terminated string from the source to the destination.
 * 
 * @param dest The destination buffer where the string will be copied.
 * @param src The source string to copy.
 */
void str_cpy(char *dest, const char *src);


#endif