#include "cache.h"
#include "constants.h"
#include "lib.h"
#include "stderr.h"

struct CacheEntry {
    int in_use; // FALSE if not in use, TRUE if in use
    char command_name[CACHE_KEY_MAX];
    char path[CACHE_MAX_PATH];
};

static struct CacheEntry cache[CACHE_MAX_SIZE];

static unsigned int hash(const char *command_name) {
    // The seed is from "Trending Pages": 
    // https://prime-numbers.fandom.com/wiki/Category:4-Digit_Prime_Numbers
    unsigned int hash = 3929; 

    for (int i = 0; command_name[i] != NULL_TERMINATOR; i++) {
        hash = hash * 31 + (unsigned char)command_name[i];
    }

    return hash;
}

static unsigned int get_command_idx(const char *command_name) {
    return hash(command_name) % CACHE_MAX_SIZE;
}

int cache_lookup(const char *command_name, char *out_path) {
    unsigned int idx = get_command_idx(command_name);

    /** 
     * Worst case we loop through entire table.
     */
    for (int i = 0; i < CACHE_MAX_SIZE; i++) {
        idx = (idx + i) % CACHE_MAX_SIZE;
        struct CacheEntry *entry = &cache[idx];

        if (entry->in_use == FALSE) {
            return ENTRYNOTFOUND;
        }

        // Check if we actually found the command
        if (str_eq(entry->command_name, command_name)) {
            str_cpy(out_path, entry->path);
            return SUCCESS;
        }       
    }

    // Went through entire table and did not find itl
    return ENTRYNOTFOUND;
}

int cache_insert(const char *command_name, const char *path) {
    // Reject if command is too long
    if (str_len(command_name) > CACHE_KEY_MAX) {
        errprint("Command too long: ");
        return handle_error_with_memory_cleanup(command_name);
    }

    // Reject if path is too long
    if (str_len(path) > CACHE_MAX_PATH) {
        errprint("Path too long: ");
        return handle_error_with_memory_cleanup(path);
    }

    // Check if the command already exists
    char out_path[CACHE_MAX_PATH];
    int cmd_exists = cache_lookup(command_name, out_path);
    if (cmd_exists != ENTRYNOTFOUND) {
        return ENTRYEXISTS;
    }

    unsigned int idx = get_command_idx(command_name);
    
    for (int i = 0; i < CACHE_MAX_SIZE; i++) {
        idx = (idx + i) % CACHE_MAX_SIZE;
        struct CacheEntry *entry = &cache[idx];
        
        if (entry->in_use == FALSE) {
            str_cpy(entry->command_name, command_name);
            str_cpy(entry->path, path);
            entry->in_use = TRUE;

            return SUCCESS;
        }
    }

    // Since loop did not return, cache is full. Indicate this
    return CACHEFULL;

}