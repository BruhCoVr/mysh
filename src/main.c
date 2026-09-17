#include "main.h"

// int argc, char **argv
int main() {
    while (TRUE) {
        print(SHELL_PROMPT);

        char input_buffer[MAX_BUFFER_SIZE];
        int bytes_read = readline(input_buffer);

        if (bytes_read == ERROR) {
            print("Error reading input\n");
            return 1;
        }

        stringify_buffer(input_buffer, bytes_read);

        if(strcmp(input_buffer, EXIT_COMMAND) == TRUE) {
            return 0;
        }


        echo_input(input_buffer);
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
        flush_buffer(i);
    }
    
    return i;
}

void flush_buffer(int bytes_read) {
    if (bytes_read == MAX_BUFFER_SIZE) {        
        char c;
        while(read(0, &c, 1) == 1 && c != LF);
    }
}

void stringify_buffer(char *buffer, int bytes_read) {
    buffer[bytes_read - 1] = NULL_TERMINATOR;
}

void echo_input(char *input) {
    if (str_len(input) == 0) {
        return;
    }

    print(input);
    print("\n");
}