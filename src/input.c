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
