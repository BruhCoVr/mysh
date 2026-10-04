/**
 * @file constants.h
 * @brief Defines constants used throughout the project
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Arbitrary 256 command cap
#define MAX_BUFFER_SIZE 256
#define MAX_TOKEN_SIZE 256
#define MAX_ARGS 64
#define MAX_TOKENS 64
#define MAX_PIPELINE_LEN 2

// Custom heap size for "dynamic" memory managements
#define HEAP_SIZE 10000

// Numbers will be max 20 digits long + 1 for the null terminator
#define ITOA_BUFFER_SIZE 21

// for read/write system calls, the fd parameter 
// is the where to read/write from/to.
// 0 is stdin, 1 is stdout; the console.
#define STDOUT_FD 1
#define STDIN_FD 0

#define LF '\n'
#define NULL_TERMINATOR '\0'
#define EXIT_COMMAND "exit"
#define SHELL_SYMBOL "$ "
#define GREEN_COLOR "\033[1;32m"
#define PURPLE_COLOR "\033[1;34m"
#define RESET_COLOR "\033[0m"


#define TRUE 1
#define FALSE 0
// System calls return -1 on error
#define ERROR -1
#define NULLY 0
#define SUCCESS 0
#define EXIT 1

// For parser, tokenizer and commands
#define TOKEN_LIMIT_REACHED -2
#define TOKEN_TOO_LONG -3
#define EMPTY_INPUT -4
// used in parser to indicate something wrong with the command
#define SYNTAX_ERROR -5
// flag to indicate missing filename for > or < operator
#define MISSING_FILENAME -6
#define ARG_MAX_EXCEEDED -7
#define TOO_MANY_STAGES -8

#endif