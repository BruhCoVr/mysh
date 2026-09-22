/** 
 * @file jobs.h
 * @brief Defines the Command structure for job management
 */

#ifndef JOBS_H
#define JOBS_H

#define MAX_ARGS 128

/**
 * @brief Represents a command as an array of string arguments.
 * 
 * @param argv An array of string arguments for the command.
 * @param argc The number of arguments in the command.
 */
struct Command {
  char *argv[MAX_ARGS+1];
  unsigned int argc;
};

#endif
