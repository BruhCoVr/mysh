/**
 * @file main.h
 * @brief Orchestrates main shell program functionality
 */

#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <errno.h>

#include <constants.h>
#include <lib.h>
#include <types.h>

/**
 * @brief Reads a line of input from stdin into the provided buffer.
 * Places at most MAX_BUFFER_SIZE characters into the buffer.
 * Null terminates the buffer, omiting the newline character.
 * 
 * @param buffer The buffer to store the input.
 * 
 * @return The number of characters read, or -1 on error.
 */
int readline(char *buffer);

/**
 * @brief Ensures the input buffer has no leftover characters after reading MAX_BUFFER_SIZE characters.
 * Clears characters out until a newline character is encountered.
 * 
 * @return void
 */
void flush_buffer();

/**
 * @brief Converts the input buffer to a null-terminated string.
 * Will either replace the newline character or the last character in the buffer.
 * 
 * @param input_buffer The buffer containing the input.
 * @param bytes_read The number of bytes read into the buffer.
 * @return void
 */
void stringify_buffer(char* input_buffer, int bytes_read);

/**
 * @brief Tokenizes the input string into an array of tokens.
 * 
 * @param input The null-terminated string to tokenize.
 * @param tokens The array to store the resulting tokens.
 * 
 * @return The number of tokens generated, or -1 on error.
 */
int tokenize_input(char *input, Tokens tokens);

/**
 * @brief Prints the input string to stdout, followed by a newline.
 * 
 * @param input The null-terminated string to print.
 * @return ssize_t The number of bytes written, or -1 on error.
 */
ssize_t echo_input(char *input);

#endif