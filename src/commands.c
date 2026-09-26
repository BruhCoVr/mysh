#include "commands.h"

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

void handle_child_process(struct Command *command) {
    char absolute_path[256];

    if (get_absolute_path(command->argv[0], absolute_path) == ERROR) {
        print("Command not found: ");
        handle_error_with_memory_cleanup(command->argv[0]);
    }

    // this sets errno, we have to handle it properly somehow
    int status = execv(absolute_path, command->argv);

    if (status == ERROR) {
        handle_error_with_memory_cleanup("Error occurred while executing command");
    }
}

int run_command(struct Command *command){
    pid_t pid;

    pid = fork();

    switch(pid) {
        case ERROR:
            return handle_error_with_memory_cleanup("Error occurred while forking process");
        case 0:
            handle_child_process(command);
            exit(0);
        default:
            int status;
            waitpid(pid, &status, 0);

            // if (WIFEXITED(status)) {
            //     println("Child process exited normally");
            // } else if (WIFSIGNALED(status)) {
            //     println("Child process terminated by signal");
            // } else if (WIFSTOPPED(status)) {
            //     println("Child process stopped");
            // } else if (WIFCONTINUED(status)) {
            //     println("Child process continued");
            // }
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
