#include <input.h>
#include <constants.h>

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
    
    if (flush_buffer(is_buffer_empty) == ERROR) {
        return ERROR;
    }

    return i;
}

int flush_buffer(int is_buffer_empty) {
    if (is_buffer_empty) {
        return SUCCESS;
    }
    
    char c;
    ssize_t isBufferFull = read(STDIN_FD, &c, 1);
    
    while(isBufferFull && c != LF) {
        
        read(STDIN_FD, &c, 1);
        if (isBufferFull == ERROR) {
            return ERROR;
        }
    }

    return SUCCESS;
}

void stringify_buffer(char *buffer, int bytes_read) {
    buffer[bytes_read - 1] = NULL_TERMINATOR;
}


int prompt_input(char *buffer) {
    if (print(SHELL_PROMPT) == ERROR) {
        handle_error("Error occurred while printing shell prompt");
    }

    int bytes_read = readline(buffer);
    if (bytes_read == ERROR) {
        handle_error("Error occurred while reading input");
    }

    stringify_buffer(buffer, bytes_read);    

    return bytes_read;
}

int get_command(struct Command *command) {
    char *input_buffer = alloc(MAX_BUFFER_SIZE);
    int bytes_read;

    // if (input_buffer == ERROR) {
    //     return handle_error("Error occurred while allocating memory for input buffer");
    // }

    bytes_read = prompt_input(input_buffer);
    
    if (bytes_read == ERROR) {
        return handle_error_with_memory_cleanup("Error occurred while prompting input");
    }

    tokenize_input(input_buffer, command);
    
    free_all();

    return 0;
}