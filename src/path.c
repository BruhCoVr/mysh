#include <path.h>

int file_exists(const char *path) {
    return access(path, F_OK) == 0;
}

int is_relative_path(const char *path) {
    return str_eq_limit(path, "./", 1);
}

void relative_path_to_absolute(const char *relative_path, char *absolute_path) {
    str_cpy(absolute_path, get_pwd());
    str_cat(absolute_path, relative_path + 1); // Skip the "."
}

/**
 * This function basically loops through all available "paths"
 * set in the PATH environment.
 * 
 * @param input_path The relative path to check for existence in the PATH environment.
 * @param path The relative path to check for existence in the PATH environment.
 * 
 * @return 0 if the file exists in one of the paths, ERROR if not.
 */
int check_env_paths(const char *input_path, char* path) {
    char *env_path = get_path();

    // big ugly loop without a split() function
    while (*env_path != NULL_TERMINATOR) {
        int i = 0;
        
        while (*env_path != ':' && *env_path != NULL_TERMINATOR) {
            path[i++] = *env_path++;
        }
        path[i] = NULL_TERMINATOR;

        // Construct the full path
        str_cat(path, "/");
        str_cat(path, input_path);

        if (file_exists(path) == TRUE) {
            return SUCCESS;
        }

        if (*env_path == ':') {
            env_path++; // Move past the colon
        }
    }

    return ERROR;
}

int get_absolute_path(const char *input_path, char *path) {
    // do cache lookup here. If not found continue on and then add it to cache
    if (cache_lookup(input_path, path) == SUCCESS) {
        // Make sure the file actually exists otherwise we have a stale cache entry
        if (file_exists(path)) {
            return SUCCESS;
        }
    }

    // check if absolute path
    if (file_exists(input_path) == TRUE) {
        str_cpy(path, input_path);
        return SUCCESS;
    }

    if (is_relative_path(input_path) == TRUE) {
        relative_path_to_absolute(input_path, path);
        return file_exists(path) ? SUCCESS : ERROR;     
    }

    int status = check_env_paths(input_path, path);
    // Since env path found the file we can add it to the cache
    if (status == SUCCESS) {
        cache_insert(input_path, path);
    }

    return status; 
}