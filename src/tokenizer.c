#include <tokenizer.h>

static int is_operator(char c) {
    return c == '<'
        || c == '>'
        || c == '|'
        || c == '&';
}

static int insert_token(char *tokens[], const char *token, int *token_count) { 
    int status = SUCCESS;
    if (*token_count >= MAX_TOKENS - 1) {
        status = TOKEN_LIMIT_REACHED;
    }
    
    if (status == SUCCESS) {
        tokens[*token_count] = alloc(MAX_TOKEN_SIZE);
        str_cpy(tokens[*token_count], token);
        (*token_count)++;
    }
    
    return status;
}

static void reset_token_buffer(char *token_buffer, int *token_len) {
    token_buffer[0] = NULL_TERMINATOR;
    *token_len = 0;
}

static int add_char_to_buffer(char *token_buffer, char c, int *token_len) {
    int status = SUCCESS;
    if (*token_len >= MAX_TOKEN_SIZE - 1) {
        status = TOKEN_TOO_LONG;
    }
    
    if (status == SUCCESS) {
        token_buffer[*token_len] = c;
        token_buffer[*token_len + 1] = NULL_TERMINATOR;
        (*token_len)++;
    }

    return status;
}

int tokenize_input(char *input, char *tokens[]) {
    int status = 0;
    int token_count = 0;
    int token_len = 0;
    char *token_buffer = alloc(MAX_TOKEN_SIZE);

    for (int i = 0; input[i] != NULL_TERMINATOR && status == 0; i++) {
        char c = input[i];

        // Still building token here
        if (c != ' ' && !is_operator(c)) {
            status = add_char_to_buffer(token_buffer, c, &token_len);
            continue;
        }
        
        // If we hit this point we either have an operator or white space
        // signifying end of token
        if (token_len > 0) {
            status = insert_token(tokens, token_buffer, &token_count);
            reset_token_buffer(token_buffer, &token_len);
        }

        // Now check if there is an operator sitting in c and make it 
        // it's own token
        if (status == 0 && is_operator(c)) {
            status = add_char_to_buffer(token_buffer, c, &token_len);
            status = insert_token(tokens, token_buffer, &token_count);
            reset_token_buffer(token_buffer, &token_len);
        }

    }

    if (status == 0 && token_len > 0) {
        status = insert_token(tokens, token_buffer, &token_count);
    }

    // Should free token_buffer here?

    tokens[token_count] = NULL;
    return status;
}
