#include <unistd.h>

#include <expand.h>
#include <lib.h>

/**
 * @brief Determines if the given token contains a '$' symbol indicating
 * the start of a variable. Loops through entire token because foo$HOME/bar
 * is a valid token, so not all tokens will have '$' at token[0]
 * 
 * @param token The token to check for $
 * 
 * @return TRUE if contains '$', FALSE otherwise.
 */
static int contains_dollar(const char *token) {
    
    for (int i = 0; token[i] != NULL_TERMINATOR; i++) {
        if (token[i] == '$') {
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * @brief Determines if a character can be part of a variable name
 * (letters, digits, underscore). The null terminator is not a name
 * character, which is what stops the name scan at the end of a token.
 * 
 * @param c The character to check
 * 
 * @return 0 if c can't be a part of variable name, >0 otherwise
 */
static int is_name_char(char c) {
    return (c >= 'a' && c <= 'z')
           || (c >= 'A' && c <= 'Z')
           || (c >= '0' && c <= '9')
           || c == '_';
}

/**
 * @brief Looks up a variable in the process environment.
 * 
 * @param name Start of the variable name. NOT null terminated at the end of
 * the name (it runs into the rest of the token), so name_len is required.
 * @param name_len Length of the variable name
 * 
 * @return Pointer to the value inside environ, or NULL if the variable is not set.
 */
static const char *get_env_value(const char *name, int name_len) {
    
    for (int i = 0; environ[i] != NULL; i++) {
        if (str_eq_limit(environ[i], name, name_len) && environ[i][name_len] == '=') {
            return environ[i] + name_len + 1;
        }
    }
 
    return NULL;
}

/**
 * @brief Appends a single character to the output buffer.
 * 
 * @return SUCCESS, EXPANSION_TOO_LONG otherwise.
 */
static int append_char(char *out, int *out_len, char c) {
    if (*out_len >= MAX_EXPANDED_TOKEN_SIZE - 1) {
        return EXPANSION_TOO_LONG;
    }
 
    out[*out_len] = c;
    (*out_len)++;
    return SUCCESS;
}

/**
 * @brief Helper to append a string to the output buffer, checking bounds.
 * 
 * @return SUCCESS, EXPANSION_TOO_LONG otherwise.
 */
static int append_string(char *out, int *out_len, const char *str) {
    int status = SUCCESS;
 
    for (int i = 0; str[i] != NULL_TERMINATOR && status == SUCCESS; i++) {
        status = append_char(out, out_len, str[i]);
    }
 
    return status;
}

/**
 * @brief Expands a single token into the appropriate value.
 * 
 * @param token The token to expand
 * @param expanded_token The output buffer to write the expanded token to.
 * Must be at least MAX_EXPANDED_TOKEN_SIZE bytes.
 * 
 * @return SUCCESS, EXPANSION_TOO_LONG otherwise.
 */
static int expand_token(const char *token, char *expanded_token) {
    int status = SUCCESS;
    int expanded_tok_len = 0;
    int i = 0;
 
    while (token[i] != NULL_TERMINATOR && status == SUCCESS) {
 
        if (token[i] != '$') {
            status = append_char(expanded_token, &expanded_tok_len, token[i]);
            i++;
            continue;
        } 

        // Found a '$'. Search until seeing a char that cannot be in env var name
        int name_start = i + 1;
        int j = name_start;

        while (is_name_char(token[j])) {
            j++;
        }
 
        int name_len = j - name_start;
 
        if (name_len == 0) {
            // '$' on it's own. Keep it since there's nothing we can do with it
            status = append_char(expanded_token, &expanded_tok_len, '$');
            i++;
        } else {
            const char *env_value = get_env_value(token + name_start, name_len);
 
            // Check if the env var is not set. If it is we just continue looping
            // to finish expanded_token
            if (env_value != NULL) {
                status = append_string(expanded_token, &expanded_tok_len, env_value);
            }
 
            // Continue after the name to finish expanded_token and not lose
            // anything that may have been after the '$'
            i = j;
        }
    }
 
    // Null terminate token. Same behaviour as in tokenizer
    expanded_token[expanded_tok_len] = NULL_TERMINATOR;
    return status;
}

int expand_variables(char *tokens[]) {

    for (int i = 0; tokens[i] != NULL; i++) {

        if (!contains_dollar(tokens[i])) {
            continue;
        }

        char *expanded_token = alloc(MAX_EXPANDED_TOKEN_SIZE);
        int status = expand_token(tokens[i], expanded_token);
        if (status != SUCCESS) {
            // PRINT ERROR HERE WHEN MERGED
            return status;
        }

        tokens[i] = expanded_token; // replace old token

    }

    return SUCCESS;
}