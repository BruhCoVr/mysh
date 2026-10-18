#ifndef PATH_H
#define PATH_H

#include <unistd.h>
#include <cache.h>
#include <env.h>

/**
 * @brief Checks if a file exists at the given path.
 * 
 * @param path The path to check.
 * @return SUCCESS if the file exists, ERROR otherwise.
 */
int get_absolute_path(const char *input_path, char *path);

#endif