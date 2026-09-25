/**
 * @file input.h
 * @brief Functions for reading input from stdin
 */

#ifndef INPUT_H
#define INPUT_H

#include <unistd.h>
#include <heap.h>
#include <jobs.h>
#include <lib.h>
#include <tokenizer.h>
#include <output.h>

/**
 * @brief Reads a line of input from the given fd into the provided buffer.
 * Places at most MAX_BUFFER_SIZE characters into the buffer.
 * Null terminates the buffer, omiting the newline character.
 *
 * @param buffer The buffer to store the input.
 * @param fd The file descriptor to read from.
 *
 * @return The number of characters read, or -1 on error.
 */
int readline(char *buffer, int fd);

/**
 * @brief Ensures the input buffer has no leftover characters after reading MAX_BUFFER_SIZE characters.
 * Clears characters out until a newline character is encountered.
 *
 * @param is_buffer_empty A flag indicating whether the buffer is empty.
 * @param fd The file descriptor to read from.
 * @return 0 on success, or ERROR on failure.
 */
int flush_buffer(int is_buffer_empty, int fd);

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
 * @brief prompts the user for input and reads it into the provided buffer as a string
 * @param buffer the buffer to read input into
 * @param fd the file descriptor to read from
 *
 * @return the number of bytes read, or ERROR on failure
 */
int prompt_input(char *buffer, int fd);

#endif
