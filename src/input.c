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
    // read_state > 0 as long as buffer is still full
    ssize_t read_state = read(fd, &c, 1);

    while (read_state > 0 && c != LF) {
        read_state = read(fd, &c, 1);
    }

    if (read_state == ERROR) {
        return ERROR;
    }
    // while(isBufferFull && c != LF) {

    //     read(fd, &c, 1);
    //     if (isBufferFull == ERROR) {
    //         return ERROR;
    //     }
    // }

    return SUCCESS;
}

void stringify_buffer(char *buffer, int bytes_read) {
    buffer[bytes_read - 1] = NULL_TERMINATOR;
}

int print_cwd() {    
    int home_len = str_len(get_home());

    if (str_eq_limit(get_pwd(), get_home(), home_len)) {
        print("~");
        return print(get_pwd()+home_len);
    }
    return print(get_pwd());
}

int print_shell_prompt() {
    int status = SUCCESS;

    status = print(GREEN_COLOR);
    status = print(get_user());
    status = print(PURPLE_COLOR);
    status = print(" ");
    status = print_cwd();
    status = print(" ");
    status = print(SHELL_SYMBOL);
    status = print(RESET_COLOR);

    return status;
}

int prompt_input(char *buffer, int fd) {
    if (print_shell_prompt() == ERROR) {
        handle_error("Error occurred while printing shell prompt");
    }

    int bytes_read = readline(buffer, fd);
    if (bytes_read == ERROR) {
        handle_error("Error occurred while reading input");
    }

    stringify_buffer(buffer, bytes_read);

    return bytes_read;
}