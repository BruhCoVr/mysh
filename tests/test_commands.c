#include "include/test_commands.h"
#include "../tlib/tlib.h"
#include "../include/commands.h"
#include "../include/constants.h"
#include <string.h>

static void init_job(struct Job *job) {
    memset(job, 0, sizeof(*job));
}

/**
 * @return file descriptor
 */
static int make_pipe(const char *data) {
    int fd_arr[2];
    pipe(fd_arr);
    write(fd_arr[1], data, strlen(data));
    close(fd_arr[1]);
    return fd_arr[0];
}

static void test_get_job_single_token(void) {
    struct Job job;
    init_job(&job);
    int fd = make_pipe("ls\n");
    TEST_ASSERT_TRUE(fd >= 0);

    int ret_status = get_job(&job, fd);
    close(fd);

    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) ret_status);
    TEST_ASSERT_EQUAL_INT((int32_t) 1, (int32_t) job.num_stages);
    TEST_ASSERT_EQUAL_INT((int32_t) 1, (int32_t) job.pipeline[0].argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("ls", job.pipeline[0].argv[0]);
    TEST_ASSERT_NULL(job.pipeline[0].argv[1]);
}

static void test_get_job_multiple_tokens(void) {
    struct Job job;
    init_job(&job);
    int fd = make_pipe("echo hello world\n");
    TEST_ASSERT_TRUE(fd >= 0);
 
    int ret_status = get_job(&job, fd);
    close(fd);
 
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) ret_status);
    TEST_ASSERT_EQUAL_INT((int32_t) 1, (int32_t) job.num_stages);
    TEST_ASSERT_EQUAL_INT((int32_t) 3, (int32_t) job.pipeline[0].argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("echo", job.pipeline[0].argv[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("hello", job.pipeline[0].argv[1]);
    TEST_ASSERT_EQUAL_CHAR_ARR("world", job.pipeline[0].argv[2]);
    TEST_ASSERT_NULL(job.pipeline[0].argv[3]);
}

static void test_get_job_empty_line(void) {
    struct Job job;
    init_job(&job);
    int fd = make_pipe("\n");
    TEST_ASSERT_TRUE(fd >= 0);
 
    int ret_status = get_job(&job, fd);
    close(fd);
 
    // Empty input is ignored: success, but no stages in the job
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) ret_status);
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) job.num_stages);
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) job.pipeline[0].argc);
    TEST_ASSERT_NULL(job.pipeline[0].argv[0]);
}

static void test_get_job_invalid_fd_returns_error(void) {
    struct Job job;
    init_job(&job);
 
    int ret = get_job(&job, -1);
 
    TEST_ASSERT_TRUE(ret != 0);
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) job.num_stages);
}

void run_test_commands(void) {
    RUN_TEST(test_get_job_single_token);
    RUN_TEST(test_get_job_multiple_tokens);
    RUN_TEST(test_get_job_empty_line);
    RUN_TEST(test_get_job_invalid_fd_returns_error);
}