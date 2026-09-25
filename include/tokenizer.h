/**
 * @file tokenizer.h
 * @brief Functions for splitting input into tokens
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <constants.h>
#include <lib.h>
#include <jobs.h>

/**
 * @brief Tokenizes the input string into an array of tokens.
 * 
 * @param input The null-terminated string to tokenize.
 * @param command The command structure to store the resulting tokens. 
 */
void tokenize_input(char *input, struct Command *command);

#endif
