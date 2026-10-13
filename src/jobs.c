#include <jobs.h>
#include <commands.h>

int run_job(struct Job *job) {
    /**
     * TODO:
     * This will become more complicated in other tickets when input redirection,
     * background processing, and multi-stage pipelines are implemented.
     */
    int status = SUCCESS;
    if (job->num_stages > 0) {
        status = run_command(&job->pipeline[0]);
    } else {
        return ERROR;
    }

    if (status != SUCCESS) {
        return ERROR;
    }

    return SUCCESS;
}