#include "main.h"

// int argc, char **argv
int main() {
    struct Command command;
    get_command(&command, STDIN_FD);

    while (is_command_exit(command) == FALSE) {
        run_command(&command);
        get_command(&command, STDIN_FD);
    }

    return 0;
}

int get_command(struct Command *command, int fd) {
    char *input_buffer = alloc(MAX_BUFFER_SIZE);
    int bytes_read;

    bytes_read = prompt_input(input_buffer, fd);

    if (bytes_read == ERROR) {
        return handle_error_with_memory_cleanup("Error occurred while prompting input");
    }

    tokenize_input(input_buffer, command);

    free_all();

    return 0;
}

int run_command(struct Command *command){
    pid_t pid;

    pid = fork();

    switch(pid) {
        case ERROR:
            return handle_error_with_memory_cleanup("Error occurred while forking process");
        case 0:
            print("Child process executing command: ");
            print(command->argv[0]);
            print("\n");
            exit(handle_input(*command, command->argc));
        default:
            int status;
            waitpid(pid, &status, 0);
            println("Child process completed");

            print("Exit status: ");
            print(status);
            print("\n");

            if (WIFEXITED(status)) {
                println("Child process exited normally");
            } else if (WIFSIGNALED(status)) {
                println("Child process terminated by signal");
            } else if (WIFSTOPPED(status)) {
                println("Child process stopped");
            } else if (WIFCONTINUED(status)) {
                println("Child process continued");
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

int is_command_exit(struct Command command){
    return (str_eq(command.argv[0], EXIT_COMMAND) == TRUE);
}
