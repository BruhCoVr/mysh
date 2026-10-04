#include "parser.h"

/**
 * @brief Checks if token1 and token2 are equal.
 * 
 * @param token1 The first token.
 * @param token2 The token to check against token1.
 * 
 * @return TRUE if token1 == token2, FALSE otherwise
 */
static int are_tokens_equal(const char *token1, const char *token2) {
    if (token1 != NULL && str_eq(token1, token2)) {
        return TRUE;
    }
    return FALSE;
}

/**
 * Returns TRUE if the given token is an operator
 * and FALSE otherwise. 
 */
static int is_token_operator(const char *token) {
    return are_tokens_equal(token, "|")
        || are_tokens_equal(token, ">")
        || are_tokens_equal(token, "<")
        || are_tokens_equal(token, "&");
}

/**
 * @brief Parses tokens into a command. Stops parsing when hitting a terminal
 * or end of tokens. Does not consume the terminal token (i.e. |, >, <, &).
 * 
 * @param tokens Array of pointers to strings of tokens
 * @param cmd The command structure to populate
 * @param token_idx The current place to start reading tokens from
 * 
 * @return SUCCESS or SYNTAX_ERROR
 */
static int parse_command(char* tokens[], struct Command *cmd, int *token_idx) {

    cmd->argc = 0; // make sure init to 0

    // Build the command here
    while (tokens[*token_idx] != NULL && !is_token_operator(tokens[*token_idx])) {
        if (cmd->argc >= MAX_ARGS) {
            return ARG_MAX_EXCEEDED;
        }

        cmd->argv[cmd->argc++] = tokens[*token_idx];
        (*token_idx)++;
    }

    cmd->argv[cmd->argc] = NULL;

    // If no arguments were added to the command we should let the user know
    if (cmd->argc == 0) {
        return SYNTAX_ERROR;
    }

    return SUCCESS;
}

/**
 * @brief Parses tokens into a Job pipeline
 * 
 * @param tokens Array of pointers to strings of tokens
 * @param token_idx The current place to start reading tokens from
 * @param job The job structure to populate
 */
static int parse_pipeline(char *tokens[], int *token_idx, struct Job *job) {
    while(TRUE) {
        if (job->num_stages >= MAX_PIPELINE_LEN) {
            return TOO_MANY_STAGES;
        }

        int cur_stages = job->num_stages;
        int status = parse_command(tokens, &job->pipeline[cur_stages], token_idx);
        if (status != SUCCESS) {
            return status;
        }
        job->num_stages++; // Parse was successful so move to the next stage

        // Need to check if parse_command stopped on a pipe, if yes we need to
        // continue parsing commands to finish the pipeline
        int is_pipeline = are_tokens_equal(tokens[*token_idx], "|");
        if (!is_pipeline) {
            return SUCCESS;
        }
        // If at this point we saw a pipe so keep parsing commands
        (*token_idx)++;
    }
}

int parse_job(char *tokens[], struct Job *job) {
    int token_idx = 0;
    // Set initial values for job
    job->num_stages = 0;
    job->outfile_path = NULL;
    job->infile_path = NULL;
    job->is_background = FALSE;

    int status = parse_pipeline(tokens, &token_idx, job);

    if (status != SUCCESS) {
        return status;
    }
    
    // Which terminal token did we stop at?
    if (are_tokens_equal(tokens[token_idx], "<")) {
        token_idx++;
        if (tokens[token_idx] == NULL || is_token_operator(tokens[token_idx])) {
            return MISSING_FILENAME;
        }
        job->infile_path = tokens[token_idx++];
    }

    if (are_tokens_equal(tokens[token_idx], "<")) {
        token_idx++;
        if (tokens[token_idx] == NULL || is_token_operator(tokens[token_idx])) {
            return MISSING_FILENAME;
        }
        job->outfile_path = tokens[token_idx++];
    }

    if (are_tokens_equal(tokens[token_idx], "&")) {
        token_idx++;
        job->is_background = TRUE;
    }

    if (tokens[token_idx] == NULL) {
        return SUCCESS;
    }
    return SYNTAX_ERROR;
}