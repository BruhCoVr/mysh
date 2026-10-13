/** 
 * @file jobs.h
 * @brief Defines the Command structure for job management
 */

#ifndef JOBS_H
#define JOBS_H

#include <constants.h>

/**
 * @brief Represents a command as an array of string arguments.
 * 
 * @param argv An array of string arguments for the command.
 * @param argc The number of arguments in the command.
 */
struct Command {
  char *argv[MAX_ARGS+1];
  unsigned int argc;
};

/**
 * @brief Represents a job, which can consist of multiple commands in a pipeline.
 * 
 * @param pipeline An array of Command structures representing the commands in the job.
 * @param num_stages The number of commands in the pipeline.
 * @param outfile_path The path to the output file for redirection, NULL = no output redirection.
 * @param infile_path The path to the input file for redirection, NULL = no input redirection.
 * @param is_background A flag indicating whether the job should run in the background (1) or foreground (0).
 */
struct Job {
  struct Command pipeline[MAX_PIPELINE_LEN];
  unsigned int num_stages;
  char *outfile_path;
  char *infile_path;
  int is_background;
};

/**
 * @brief Runs the job inside the job struct
 * 
 * @param job The job to be ran
 * 
 * @return SUCCESS or ERROR
 */
int run_job(struct Job *job);

#endif
