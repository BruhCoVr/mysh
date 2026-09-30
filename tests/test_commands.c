#include "include/test_commands.h"
#include "../tlib/tlib.h"
#include "commands.h"
#include <string.h>

static void init_command(struct Command *cmd) {
    memset(cmd, 0, sizeof(*cmd));
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

static void test_get_command_single_token(void) {
    struct Command cmd;
    init_command(&cmd);
    int fd = make_pipe("ls\n");
    TEST_ASSERT_TRUE(fd >= 0);

    int ret_status = get_command(&cmd, fd);
    close(fd);

    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) ret_status);
    TEST_ASSERT_EQUAL_INT((int32_t) 1, (int32_t) cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("ls", cmd.argv[0]);
    TEST_ASSERT_NULL(cmd.argv[1]);
}

static void test_get_command_multiple_tokens(void) {
    struct Command cmd; 
    init_command(&cmd);
    int fd = make_pipe("echo hello world\n");
    TEST_ASSERT_TRUE(fd >= 0);
 
    int ret_status = get_command(&cmd, fd);
    close(fd);
 
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) ret_status);
    TEST_ASSERT_EQUAL_INT((int32_t) 3, (int32_t) cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("echo", cmd.argv[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("hello", cmd.argv[1]);
    TEST_ASSERT_EQUAL_CHAR_ARR("world", cmd.argv[2]);
    TEST_ASSERT_NULL(cmd.argv[3]);
}

static void test_get_command_empty_line(void) {
    struct Command cmd; 
    init_command(&cmd);
    int fd = make_pipe("\n");
    TEST_ASSERT_TRUE(fd >= 0);
 
    int ret_status = get_command(&cmd, fd);
    close(fd);
 
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) ret_status);
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) cmd.argc);
    TEST_ASSERT_NULL(cmd.argv[0]);
}

static void test_get_command_invalid_fd_returns_error(void) {
    struct Command cmd; 
    init_command(&cmd);
 
    int ret = get_command(&cmd, -1);
 
    TEST_ASSERT_TRUE(ret != 0);
    TEST_ASSERT_EQUAL_INT((int32_t)0, (int32_t)cmd.argc);
}


void run_test_commands(void) {
    RUN_TEST(test_get_command_single_token);
    RUN_TEST(test_get_command_multiple_tokens);
    RUN_TEST(test_get_command_empty_line);
    RUN_TEST(test_get_command_invalid_fd_returns_error);
}
