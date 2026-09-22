/**
 * @file token.h
 * @brief Functions for splitting input into tokens
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <constants.h>
#include <lib.h>
#include <types.h>

/**
 * @brief Tokenizes the input string into an array of tokens.
 * 
 * @param input The null-terminated string to tokenize.
 * @param tokens The array to store the resulting tokens.
 * 
 * @return The number of tokens generated, or -1 on error.
 */
int tokenize_input(char *input, Tokens tokens);

#endif
