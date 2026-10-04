/**
 * @file commands.h
 * @brief Functions for getting and running shell commands
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include <sys/wait.h>

#include <constants.h>
#include <lib.h>
#include <output.h>
#include <input.h>
#include <tokenizer.h>
#include <jobs.h>
#include <path.h>
#include <parser.h>

/**
 * @brief Reads from the given fd and populates the given Job structure.
 * @param job The Job structure to populate.
 * @param fd The file descriptor to read from.
 *
 * @return One of the following: SUCCESS, ERROR, TOKEN_LIMIT_REACHED, TOKEN_TOO_LONG,
 * EMPTY_INPUT, MISSING_FILENAME, SYNTAX_ERROR
 */
int get_job(struct Job *job, int fd);

/**
 * @brief Executes the given command.
 * @param command The Command structure containing the command to execute.
 *
 * @return 0 on success, or ERROR on failure.
 */
int run_command(struct Command *command);

 /**
 * @brief checks if the command is an exit command
 * @param command the command to check
 *
 * @return TRUE if the command is an exit command, FALSE otherwise.
 */
int is_job_exit(struct Job job);

#endif