#include <input.h>
#include <constants.h>

int readline(char *input_buffer, int fd) {
    int bytes_read = 0;

    while(bytes_read < MAX_BUFFER_SIZE) {
        ssize_t read_status = read(fd, &input_buffer[bytes_read], 1);

        if (read_status == ERROR) {
            return ERROR;
        }

        if (input_buffer[bytes_read] == LF) {
            bytes_read++;
            break;
        }

        bytes_read++;
    }

    if (flush_buffer(bytes_read, fd) == ERROR) {
        return ERROR;
    }

    return bytes_read;
}

int flush_buffer(int bytes_read, int fd) {
    if (bytes_read < MAX_BUFFER_SIZE) {
        return SUCCESS;
    }

    char c;
    ssize_t read_status;

    do {
        read_status = read(fd, &c, 1);
    } while (read_status > 0 && c != LF);

    if (read_status == ERROR) {
        return ERROR;
    }

    return SUCCESS;
}

void stringify_buffer(char *buffer, int bytes_read) {
    buffer[bytes_read - 1] = NULL_TERMINATOR;
}


int prompt_input(char *buffer, int fd) {
    if (print(SHELL_PROMPT) == ERROR) {
        handle_error("Error occurred while printing shell prompt");
    }

    int bytes_read = readline(buffer, fd);
    if (bytes_read == ERROR) {
        handle_error("Error occurred while reading input");
    }

    stringify_buffer(buffer, bytes_read);

    return bytes_read;
}

int get_command(struct Command *command, int fd) {
    char *input_buffer = alloc(MAX_BUFFER_SIZE);
    int bytes_read;

    // if (input_buffer == ERROR) {
    //     return handle_error("Error occurred while allocating memory for input buffer");
    // }

    bytes_read = prompt_input(input_buffer, fd);

    if (bytes_read == ERROR) {
        return handle_error_with_memory_cleanup("Error occurred while prompting input");
    }

    tokenize_input(input_buffer, command);
    
    free_all();

    return 0;
}