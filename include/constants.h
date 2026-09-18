/**
 * @file constants.h
 * @brief Defines constants used throughout the project
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Arbitrary 256 command cap
#define MAX_BUFFER_SIZE 256
// Related token size cap
#define MAX_TOKENS 256
#define MAX_TOKEN_SIZE 256

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
#define SHELL_PROMPT "$ "

#define TRUE 1
#define FALSE 0
// System calls return -1 on error
#define ERROR -1
#define SUCCESS 0
#define EXIT 1


#endif