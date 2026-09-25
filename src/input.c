#include <input.h>
#include <constants.h>

int readline(char *input_buffer, int fd) {
    int i = 0;

    int is_buffer_empty = 0;

    while(i < MAX_BUFFER_SIZE) {
        ssize_t bytes_read = read(fd, &input_buffer[i], 1);

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

    if (flush_buffer(is_buffer_empty, fd) == ERROR) {
        return ERROR;
    }

    return i;
}

int flush_buffer(int is_buffer_empty, int fd) {
    if (is_buffer_empty) {
        return SUCCESS;
    }

    char c;
    ssize_t isBufferFull = read(fd, &c, 1);

    while(isBufferFull && c != LF) {

        read(fd, &c, 1);
        if (isBufferFull == ERROR) {
            return ERROR;
        }
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