#ifndef ENV_H
#define ENV_H

#include <unistd.h>
#include <lib.h>

// Global environment for fun stuff
struct Env {
    char user[64];
    char home[256];
    char path[256];
    char pwd[256];
};

extern struct Env env;

/**
 * @brief Initializes the environment variables by searching through the system's environment.
 */
void initialize_env();

/**
 * @brief Retrieves the value of the USER environment variable.
 */
char* get_user();

/**
 * @brief Retrieves the value of the HOME environment variable.
 */
char* get_home();

/**
 * @brief Retrieves the value of the PATH environment variable.
 */
char* get_path();

/**
 * @brief Retrieves the value of the PWD environment variable.
 */ 
char* get_pwd();

#endif