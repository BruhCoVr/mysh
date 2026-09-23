/**
 * @file main.h
 * @brief Orchestrates main shell program functionality
 */

#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include <constants.h>
#include <lib.h>
#include <output.h>
#include <types.h>
#include <input.h>
#include <tokenizer.h>
#include <jobs.h>

/**
 * @brief handles the input tokens and executes the appropriate command
 * @param tokens the array of tokens to handle
 * @param token_count the number of tokens in the array
 * 
 * @return 0 on success, or ERROR on failure.
 */
int handle_input(struct Command command, int token_count);

/**
 * @brief echoes the input tokens to the terminal
 * @param tokens the array of tokens to echo
 * @param token_count the number of tokens in the array
 * 
 * @return 0 on success, or ERROR on failure.
 */
int echo_input(struct Command command, int token_count);


#endif