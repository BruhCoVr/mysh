/**
 * @file tokenizer.h
 * @brief Functions for splitting input into tokens
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <constants.h>
#include <lib.h>

/**
 * @brief Tokenizes the input string into an array of tokens.
 * 
 * @param input The null-terminated input string to tokenize.
 * @param tokens The array of tokens to be populated.
 * 
 * @return SUCCESS if successful; TOKEN_LIMIT_REACHED or TOKEN_TOO_LONG otherwise
 */
int tokenize_input(char *input, char *tokens[]);

#endif