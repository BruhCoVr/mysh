/**
 * @file commands.h
 * @brief Functions for getting and running shell commands
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <constants.h>
#include <lib.h>
#include <output.h>
#include <input.h>
#include <tokenizer.h>
#include <jobs.h>
#include <path.h>

/**
 * @brief Reads a command from the given fd and populates the provided Command structure.
 * @param command The Command structure to populate.
 * @param fd The file descriptor to read from.
 *
 * @return 0 on success, or ERROR on failure.
 */
int get_command(struct Command *command, int fd);

/**
 * @brief Executes the given command.
 * @param command The Command structure containing the command to execute.
 *
 * @return 0 on success, or ERROR on failure.
 */
int run_command(struct Command *command);

/**
 * @brief handles the input tokens and executes the appropriate command
 * @param command the command to handle
 * @param token_count the number of tokens in the command
 *
 * @return 0 on success, or ERROR on failure.
 */
int handle_input(struct Command command, int token_count);

/**
 * @brief echoes the input tokens to the terminal
 * @param command the command to echo
 * @param token_count the number of tokens in the command
 *
 * @return 0 on success, or ERROR on failure.
 */
int echo_input(struct Command command, int token_count);

 /**
 * @brief checks if the command is an exit command
 * @param command the command to check
 *
 * @return TRUE if the command is an exit command, FALSE otherwise.
 */
int is_command_exit(struct Command command);

#endif
