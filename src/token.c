#include <token.h>

void insert_token(Tokens tokens, const char *token, int token_count) {
    str_cpy(tokens[token_count], token);
}

void reset_token_buffer(char *token_buffer, int *token_index) {
    token_buffer[0] = NULL_TERMINATOR;
    *token_index = 0;
}

void add_char_to_buffer(char *token_buffer, char c, int token_index) {
    token_buffer[token_index] = c;
    token_buffer[token_index + 1] = NULL_TERMINATOR;
}

int tokenize_input(char *input, Tokens tokens) {
    int i = 0;
    int token_count = 0;
    int token_buffer_index = 0;
    Token token_buffer = "";

    while(input[i] != NULL_TERMINATOR) {
        char c = input[i++];    
        
        if (c != ' ') {
            add_char_to_buffer(token_buffer, c, token_buffer_index++);
            continue;
        } 
        
        if (token_buffer_index == 0) {
            continue;
        }
        
        insert_token(tokens, token_buffer, token_count++);
        reset_token_buffer(token_buffer, &token_buffer_index);
    }

    if (token_buffer_index > 0) {
        insert_token(tokens, token_buffer, token_count++);
    }

    return token_count;
}
