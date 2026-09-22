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
 * @param is_buffer_empty A flag indicating whether the buffer is empty.
 * @return 0 on success, or ERROR on failure.
 */
int flush_buffer(int is_buffer_empty);

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
 * 
 * @return the number of bytes read, or ERROR on failure
 */
int prompt_input(char *buffer);

/**
 * @brief Reads a command from stdin and populates the provided Command structure.
 * @param command The Command structure to populate.
 * 
 * @return The number of bytes read, or ERROR on failure.
 */
int get_command(struct Command *command);

#endif
