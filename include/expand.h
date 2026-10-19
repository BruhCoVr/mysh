#ifndef EXPAND_H
#define EXPAND_H

#include <constants.h>

extern char **environ;

/**
 * @brief Expands any variables such as $PATH, $USER, $HOME inside of the tokens
 * array.
 * 
 * @param tokens The array of tokens to expand variables in
 * 
 * @return SUCCESS, EXPANSION_TOO_LONG
 */
int expand_variables(char *tokens[]);

#endif