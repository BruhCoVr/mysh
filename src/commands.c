#include "commands.h"
#include "expand.h"

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

    // Expand anything like $PATH, $HOME, etc...
    status = expand_variables(tokens);
    if (status != SUCCESS) {
        return status;
    }

    if (tokens[0] == NULL) {
        // used to return EMPTY_INPUT, but empty input can be safely ignored
        job->num_stages = 0;
        return SUCCESS; 
    }

    status = parse_job(tokens, job);

    return status;
}

int handle_redirection(int infile_fd, int outfile_fd) {
    int status = SUCCESS; 
    
    if (infile_fd != STDIN_FD) {
        status = status_keep_error(status, dup2(infile_fd, STDIN_FD));
        status = status_keep_error(status, close(infile_fd));
    }
    if (outfile_fd != STDOUT_FD) {
        status = status_keep_error(status, dup2(outfile_fd, STDOUT_FD));
        status = status_keep_error(status, close(outfile_fd));
    }

    return status;
}

void handle_child_process(struct Command *command, const char *absolute_path, int infile_fd, int outfile_fd, int fd_to_close) {
    int status = SUCCESS;
    if (command->argv[0] == NULL) {
        return;
    }

    // Closes the read end of the pipe (if in a pipeline) since we aren't using it
    if (fd_to_close != NONE) {
        status = status_keep_error(status, close(fd_to_close));
    }   

    // Handles redirection to file descriptors (pipe ends or files) if necessary
    status = status_keep_error(status, handle_redirection(infile_fd, outfile_fd));

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

pid_t run_command(struct Command *command, int infile_fd, int outfile_fd, int fd_to_close) {
    
    // Since parent must own the cache we need to find abs path before forking
    char absolute_path[256];
    if (get_absolute_path(command->argv[0], absolute_path) == ERROR) {
        print("Command not found: ");
        return handle_error_with_memory_cleanup(command->argv[0]);
    }

    pid_t pid;

    pid = fork();

    switch(pid) {
        case ERROR:
            return handle_error_with_memory_cleanup("Error occurred while forking process");
        case 0:
            handle_child_process(command, absolute_path, infile_fd, outfile_fd, fd_to_close);
            exit(ERROR);
        default:
            return pid;
    }
}

int is_job_exit(struct Job job){ 
    if (job.pipeline[0].argv[0] == NULL) {
        return FALSE;
    }

    return (str_eq(job.pipeline[0].argv[0], EXIT_COMMAND) == TRUE);
}
