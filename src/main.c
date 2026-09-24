#include "main.h"

// int argc, char **argv
int main() {
    struct Command command;
    get_command(&command);
    

    while (is_command_exit(command) == FALSE) {
        run_command(&command);
        get_command(&command);
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

int run_command(struct Command *command){
    int handle_input_statuts = handle_input(*command, command->argc);
        
    if (handle_input_statuts == ERROR) {
        return handle_error("Error occurred while handling input");
        }
    return 0;
}

int is_command_exit(struct Command command){
    return (str_eq(command.argv[0], EXIT_COMMAND) == TRUE);
}