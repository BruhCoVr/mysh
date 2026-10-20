#ifndef CACHE_H
#define CACHE_H

#include <stderr.h>

/**
 * @brief Looks up the command in the cache.
 * 
 * @param command_name the command to look up
 * @param out_path the path corresponding to the command if it exists
 * 
 * @return SUCCESS if found with out_path containing path to command, ENTRYNOTFOUND if command not found
 */
int cache_lookup(const char *command_name, char *out_path);

/**
 * @brief Inserts given command and path into the cache
 * 
 * @param command_name the command name to insert (i.e "echo")
 * @param path the path associated with the command (i.e. "/usr/bin/echo")
 * 
 * @return SUCCESS if successful
 *         otherwise:
 *         ERROR (command / path are too long) | ENTRYEXISTS | CACHEFULL
 * 
 */
int cache_insert(const char *command_name, const char *path);

#endif