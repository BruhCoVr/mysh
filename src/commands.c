#include "commands.h"

int get_job(struct Job *job, int fd) {
    char *input_buffer = alloc(MAX_BUFFER_SIZE);
    int bytes_read;

    bytes_read = prompt_input(input_buffer, fd);

    if (bytes_read == ERROR) {
        return ERROR;
    }

    // Allocate space for 64 tokens + NULL @ end of array
    // Note: This can be on stack since we want pointers to all the tokens stored
    // by the tokenizer. Tokenizer uses alloc() to store pointers to the tokens
    char *tokens[MAX_TOKENS + 1];
    int status = tokenize_input(input_buffer, tokens);
    
    if (status != SUCCESS) {
        return status;
    }

    if (tokens[0] == NULL) {
        // used to return EMPTY_INPUT, but empty input can be safely ignored
        return SUCCESS; 
    }

    status = parse_job(tokens, job);

    return status;
}

int handle_redirection(int input_fd, int output_fd) {
    int status = SUCCESS; 
    
    if (input_fd != STDIN_FD) {
        status = status_keep_error(status, dup2(input_fd, STDIN_FD));
        status = status_keep_error(status, close(input_fd));
    }
    if (output_fd != STDOUT_FD) {
        status = status_keep_error(status, dup2(output_fd, STDOUT_FD));
        status = status_keep_error(status, close(output_fd));
    }

    return status;
}

void handle_child_process(struct Command *command, int input_fd, int output_fd) {
    int status = SUCCESS;
    if (command->argv[0] == NULL) {
        return;
    }

    char absolute_path[256];

    if (get_absolute_path(command->argv[0], absolute_path) == ERROR) {
        print("Command not found: ");
        handle_error_with_memory_cleanup(command->argv[0]);
    }

    status = handle_redirection(input_fd, output_fd);

    if (status == ERROR) {
        handle_error_with_memory_cleanup("Error occurred while redirecting input/output");
    }

    // this sets errno, we have to handle it properly somehow
    status = execve(absolute_path, command->argv, environ);

    if (status == ERROR) {
        print("Error occurred while executing command: ");
        println(command->argv[0]);
    }
}

int run_command(struct Command *command, int input_fd, int output_fd) {
    pid_t pid;

    pid = fork();

    switch(pid) {
        case ERROR:
            return handle_error_with_memory_cleanup("Error occurred while forking process");
        case 0:
            handle_child_process(command, input_fd, output_fd);
            exit(ERROR);
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

int is_job_exit(struct Job job){ 
    if (job.pipeline[0].argv[0] == NULL) {
        return FALSE;
    }

    return (str_eq(job.pipeline[0].argv[0], EXIT_COMMAND) == TRUE);
}
