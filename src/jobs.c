#include <jobs.h>
#include <commands.h>


int handle_input_redirection(int *infile_fd, char *infile_path) {
    if (infile_path != NULL) {
        *infile_fd = open(infile_path, O_RDONLY);

        if (*infile_fd == ERROR){
            errprint("Error opening input file: ");
            errprintln(infile_path);
            return FD_OPEN_ERROR;
        }
    }

    return SUCCESS;
}

int handle_output_redirection(int *outfile_fd, char *outfile_path) {
    if (outfile_path != NULL) {
        *outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

        if (*outfile_fd == ERROR){
            errprint("Error opening output file: ");
            errprintln(outfile_path);
            return FD_OPEN_ERROR;
        }
    }

    return SUCCESS;
}

int close_input_file(int *infile_fd) {
    if (*infile_fd != STDIN_FD) {
        int status = close(*infile_fd);
        *infile_fd = STDIN_FD;
        return status;
    }
    return SUCCESS;
}

int close_output_file(int *outfile_fd) {
    if (*outfile_fd != STDOUT_FD) {
        int status = close(*outfile_fd);
        *outfile_fd = STDOUT_FD;
        return status;
    }
    return SUCCESS;
}

int close_open_files(int *infile_fd, int *outfile_fd) {
    int status = SUCCESS;
    status = status_keep_error(status, close_input_file(infile_fd));
    status = status_keep_error(status, close_output_file(outfile_fd));
    return status;
}

int handle_pipeline(struct Job *job, int *infile_fd) {
    int status = SUCCESS;
    int pipefd[2];
    int pid_count = 0;

    for (unsigned int stage = 0; stage < job->num_stages - 1; stage++) {
        status = pipe(pipefd); // sets errno
        if (status == ERROR) {
            errprint("Error occurred while creating pipe\n");
            return ERROR;
        }

        pid_t pid = run_command(&job->pipeline[stage], *infile_fd, pipefd[WRITE_END], pipefd[READ_END]);
        
        if (pid == ERROR) {
            close(pipefd[READ_END]);
            close(pipefd[WRITE_END]);
            errprint("Error occurred while running command\n");
            return ERROR;
        }
        
        status = close(pipefd[WRITE_END]);
        // This handles closing the old read end of the previous pipe
        status = status_keep_error(status, close_input_file(infile_fd));

        *infile_fd = pipefd[READ_END];
        job->pids[stage] = pid;

        pid_count++;

        if (status == ERROR) {
            errprint("Error occurred while closing input file\n");
            return ERROR;
        } 
    }

    return pid_count;
}

void wait_for_job(struct Job *job, int pid_count) {
    for (int stage = 0; stage < pid_count; stage++) {
        int wstatus;
        waitpid(job->pids[stage], &wstatus, 0);
    }
}

int run_job(struct Job *job) {
    int status = SUCCESS;
    int infile_fd = STDIN_FD;
    int outfile_fd = STDOUT_FD;
    int pid_count;

    if (job->num_stages == 0) {
        return SUCCESS;
    }

    status = handle_input_redirection(&infile_fd, job->infile_path);

    if (status != SUCCESS) {
        close_input_file(&infile_fd);
        errprint("Error occurred while opening input file\n");
        return status;
    }

    pid_count = handle_pipeline(job, &infile_fd);

    if (pid_count == ERROR) {
        close_open_files(&infile_fd, &outfile_fd);
        errprint("Error occurred while handling pipeline\n");
        return ERROR;
    }

    status = handle_output_redirection(&outfile_fd, job->outfile_path);

    if (status != SUCCESS) {
        close_open_files(&infile_fd, &outfile_fd);
        errprint("Error occurred while opening output file\n");
        return ERROR;
    }

    // Finally, run the last command in the pipeline
    pid_t pid = run_command(&job->pipeline[job->num_stages - 1], infile_fd, outfile_fd, NONE);
    if (pid == ERROR) {
        close_open_files(&infile_fd, &outfile_fd);
        errprint("Error occurred while running command\n");
        return ERROR;
    }

    pid_count++;

    status = close_open_files(&infile_fd, &outfile_fd);

    job->pids[job->num_stages - 1] = pid;

    if (!job->is_background) {
        wait_for_job(job, pid_count);
    }

    return status;
}

void reap_zombies(void) {
    int wait_status;
    pid_t pid = waitpid(-1, &wait_status, WNOHANG);
    
    /**
     * Basically as long as a pid is being returned we are reaping
     * children. Gotta keep calling it because there may be more unreaped.
     * If we're in a child we obviously stop because it has not exited yet.
     * Otherwise there's the possibility of an error, if we wanna handle that
     * we can. There are 5 possible errors to get.
     */
    while (pid > 0) {
        pid = waitpid(-1, &wait_status, WNOHANG);
    }
}