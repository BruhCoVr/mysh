#include "main.h"
#include <env.h>

// int argc, char **argv
int main() {
    initialize_env();

    struct Job job;
    int status = get_job(&job, STDIN_FD);

    while (is_job_exit(job) == FALSE && status == SUCCESS) {
        status = run_job(&job);
        status = get_job(&job, STDIN_FD);
    }

    // Need to handle errors returned properly here. This is 
    // just some skeleton right now cause I didn't feel like 
    // finishing it at the moment
    // switch (status) {
    //     case ERROR:
    //         break;
    //     case TOKEN_LIMIT_REACHED:
    //         break;
    //     case TOKEN_TOO_LONG:
    //         break;
    //     case EMPTY_INPUT:
    //         break;
    //     case MISSING_FILENAME:
    //         break;
    //     case SYNTAX_ERROR:
    //         break;
    // }

    return 0;
}
