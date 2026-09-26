#ifndef PATH_H
#define PATH_H

#include <unistd.h>

#include <env.h>

/**
 * @brief Checks if a file exists at the given path.
 * 
 * @param path The path to check.
 * @return 0 if the file exists, -1 otherwise.
 */
int get_absolute_path(const char *input_path, char *path);

#endif