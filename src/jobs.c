#include <jobs.h>
#include <commands.h>

int redirect_output(char *outfile_path, int *outfile_fd) {
    *outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (*outfile_fd == ERROR){
        print("Error opening output file: ");
        println(outfile_path);
        return FD_OPEN_ERROR;
    }

    return SUCCESS;
}

int is_last_stage(struct Job *job, unsigned int stage) {
    return (stage == job->num_stages - 1);
}

int close_open_files(int *infile_fd, int *outfile_fd) {
    int status = SUCCESS;

    if (*infile_fd != STDIN_FD) {
        status = status_keep_error(status, close(*infile_fd));
        *infile_fd = STDIN_FD;
    }
    if (*outfile_fd != STDOUT_FD) {
        status = status_keep_error(status, close(*outfile_fd));
        *outfile_fd = STDOUT_FD;
    }

    return status;
}

int run_job(struct Job *job) {
    /**
     * TODO:
     * This will become more complicated in other tickets when input redirection,
     * background processing, and multi-stage pipelines are implemented.
     */
    int status = SUCCESS;
    int infile_fd = STDIN_FD;
    int outfile_fd = STDOUT_FD;

    for (unsigned int i = 0; i < job->num_stages; i++) {
        if (is_last_stage(job, i) && job->outfile_path != NULL) {
            status = redirect_output(job->outfile_path, &outfile_fd);
            if (status != SUCCESS) {
                print("Error occurred while opening output file\n");
                // we can handle errno here,
                return FD_OPEN_ERROR;
            }
        }

        status = run_command(&job->pipeline[i], infile_fd, outfile_fd);
        if (status != SUCCESS) {
            print("Error occurred while running command\n");
        }

        status = status_keep_error(status, close_open_files(&infile_fd, &outfile_fd));
        if (status != SUCCESS) {
            print("Error occurred while closing file descriptors\n");
            return ERROR;
        }
    }

    return SUCCESS;
}