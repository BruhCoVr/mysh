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
        return EMPTY_INPUT;
    }

    status = parse_job(tokens, job);

    return status;
}

void handle_child_process(struct Command *command) {
    if (command->argv[0] == NULL) {
        return;
    }

    char absolute_path[256];

    if (get_absolute_path(command->argv[0], absolute_path) == ERROR) {
        print("Command not found: ");
        handle_error_with_memory_cleanup(command->argv[0]);
    }

    // this sets errno, we have to handle it properly somehow
    int status = execve(absolute_path, command->argv, environ);

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
            _exit(0);
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
