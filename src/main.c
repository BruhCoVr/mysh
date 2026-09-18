#include "main.h"

// int argc, char **argv
int main() {
    char input_buffer[MAX_BUFFER_SIZE];
    int bytes_read;
    int token_count;
    Tokens tokens;

    while (TRUE) {
        bytes_read = prompt_input(input_buffer);

        if (bytes_read == ERROR) {
            println("Error occurred while reading input");
            exit(1);
        }
        
        stringify_buffer(input_buffer, bytes_read);

        token_count = tokenize_input(input_buffer, tokens);

        if (token_count == 0) {
            continue;
        }
        
        int handle_input_statuts = handle_input(tokens, token_count);
        
        if (handle_input_statuts == ERROR) {
            println("Error occurred while handling input");
            exit(1);
        }

        if (handle_input_statuts == EXIT) {
            println("Bye bye o/...");
            return 0;
        }
    }   

    return 0;
}

int prompt_input(char *buffer) {
    if (print(SHELL_PROMPT) == ERROR) {
        println("Error occurred while printing shell prompt");
        return ERROR;
    }

    return readline(buffer);
}

int handle_input(Tokens tokens, int token_count) {
    int status = echo_input(tokens, token_count);    
    
    if(strcmp(tokens[0], EXIT_COMMAND) == TRUE) {
        return 1;
    }

    return status;
}



int echo_input(Tokens tokens, int token_count) {
    for (int i = 0; i < token_count; i++) {
        if (print(tokens[i]) == ERROR || print(" ") == ERROR) {
            return ERROR;
        }
    }

    return println("");
}
