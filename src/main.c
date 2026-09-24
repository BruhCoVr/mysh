#include "main.h"

// int argc, char **argv
int main() {
    struct Command command;

    while (TRUE) {
        get_command(&command, STDIN_FD);
        
        int handle_input_statuts = handle_input(command, command.argc);
        
        if (handle_input_statuts == ERROR) {
            handle_error("Error occurred while handling input");
        }

        if (handle_input_statuts == EXIT) {
            println("Bye bye o/...");
            return 0;
        }
    }   

    return 0;
}

int handle_input(struct Command command, int token_count) {
    int status = echo_input(command, token_count);    
    
    if(str_eq(command.argv[0], EXIT_COMMAND) == TRUE) {
        return 1;
    }

    return status;
}




int echo_input(struct Command command, int token_count) {
    for (int i = 0; i < token_count; i++) {
        if (print(command.argv[i]) == ERROR || print(" ") == ERROR) {
            return handle_error("");
        }
    }

    return println("");
}
