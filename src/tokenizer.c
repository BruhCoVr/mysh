#include <tokenizer.h>

void insert_argument(char *argv[], const char *token, int arg_count) {
    argv[arg_count] = alloc(MAX_TOKEN_SIZE);
    str_cpy(argv[arg_count], token);
}

void reset_arg_buffer(char *arg_buffer, int *arg_index) {
    arg_buffer[0] = NULL_TERMINATOR;
    *arg_index = 0;
}

void add_char_to_buffer(char *arg_buffer, char c, int arg_index) {
    arg_buffer[arg_index] = c;
    arg_buffer[arg_index + 1] = NULL_TERMINATOR;
}
    
void tokenize_input(char *input, struct Command *command) {
    int i = 0;
    int arg_count = 0;
    int arg_buffer_index = 0;
    char *arg_buffer = alloc(MAX_BUFFER_SIZE);
    
    char **argv = command->argv;

    while(input[i] != NULL_TERMINATOR && arg_count < MAX_ARGS - 1) {
        char c = input[i++];    
        
        if (c != ' ') {
            add_char_to_buffer(arg_buffer, c, arg_buffer_index++);
            continue;
        } 
        
        if (arg_buffer_index == 0) {
            continue;
        }
        
        insert_argument(argv, arg_buffer, arg_count++);
        reset_arg_buffer(arg_buffer, &arg_buffer_index);
    }

    if (arg_buffer_index > 0) {
        insert_argument(argv, arg_buffer, arg_count++);
    }

    command->argc = arg_count;
}
