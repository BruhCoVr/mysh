/**
 * @file parser.h
 * @brief Functionality for parsing tokens into commands and commands
 * into jobs.
 */

#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>

#include "jobs.h"
#include "constants.h"
#include "lib.h"

/**
 * @brief Parses tokens from input into a Job
 * 
 * @param tokens Array of pointers to strings of tokens
 * @param job Job to be populated with command pipeline
 * 
 * @return SUCCESS, MISSING_FILENAME if no filename given for > or < operators,
 * SYNTAX_ERROR for any other malformed input
 */
int parse_job(char *tokens[], struct Job *job);

#endif