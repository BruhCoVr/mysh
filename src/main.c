#include "main.h"

// int argc, char **argv
int main() {
    while (TRUE) {
        print(SHELL_PROMPT);
        
        char input_buffer[MAX_BUFFER_SIZE];
        int bytes_read = readline(input_buffer);

        if (bytes_read == ERROR) {
            println("Error reading input");
            return 1;
        }

        stringify_buffer(input_buffer, bytes_read);

        Tokens tokens;
        int token_count = tokenize_input(input_buffer, tokens);

        for (int i = 0; i < token_count; i++) {
            print(tokens[i]);
            print(" ");
        }
        println("");
        
        if(strcmp(tokens[0], EXIT_COMMAND) == TRUE) {
            return 0;
        }
    }   

    return 0;
}

int readline(char *input_buffer) {
    int i = 0;

    int is_buffer_empty = 0;

    while(i < MAX_BUFFER_SIZE) {
        ssize_t bytes_read = read(STDIN_FD, &input_buffer[i], 1);

        if (bytes_read == ERROR) {
            return ERROR;
        }

        if (input_buffer[i] == LF) {
            is_buffer_empty = 1;
            i++;
            break;
        }

        i++;
    }

    if(!is_buffer_empty) {
        flush_buffer();
    }
    
    return i;
}

void flush_buffer() {
    char c;
    ssize_t isBufferFull = read(0, &c, 1);

    while(isBufferFull && c != LF) {
        read(0, &c, 1);
        if (isBufferFull == ERROR) {
            break;
        }
    }
}

void stringify_buffer(char *buffer, int bytes_read) {
    buffer[bytes_read - 1] = NULL_TERMINATOR;
}


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


ssize_t echo_input(char *input) {
    if (str_len(input) == 0) {
        return 0;
    }

    return println(input);
}
