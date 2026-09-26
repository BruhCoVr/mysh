/**
 * @file lib.h
 * @brief A collection of utility functions
 */


#ifndef LIB_H
#define LIB_H

#include <stddef.h>
#include <unistd.h>

#include <constants.h>
#include <heap.h>
#include <output.h>

/**
 * @brief Returns the length of a null-terminated string.
 * 
 * @param s Pointer to the null-terminated string.
 * 
 * @return The length of the string (number of characters before the null terminator).
 */
unsigned int str_len(const char *s);

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
 * @brief Compares two null-terminated strings.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 *
 * @return 1 if the strings are equal, 0 otherwise
 */
int str_eq(const char *str1, const char *str2);

/**
 * @brief Compares two null-terminated strings up to a specified limit.
 * 
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @param limit The maximum number of characters to compare.
 * 
 * @return 1 if the strings are equal up to the limit, 0 otherwise.
 */
int str_eq_limit(const char *str1, const char *str2, int limit);

/**
 * @brief Copies a null-terminated string from the source to the destination.
 * 
 * @param dest The destination buffer where the string will be copied.
 * @param src The source string to copy.
 */
void str_cpy(char *dest, const char *src);

/**
 * @brief Concatenates a null-terminated string to the end of another string.
 * 
 * @param dest The destination buffer where the string will be concatenated.
 * @param src The source string to concatenate.
 */
void str_cat(char *dest, const char *src);

/** 
 * @brief Handles an error by printing an error message and returning an error code.
 * 
 * @param msg The error message to print.
 * @return -1
 */
int handle_error(const char *msg);

/** 
 * @brief Handles an error by printing an error message, cleaning up memory, and returning an error code.
 * 
 * @param msg The error message to print.
 * @return -1
 */
int handle_error_with_memory_cleanup(const char *msg);

#endif