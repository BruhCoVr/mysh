#include <string.h>
#include <stdlib.h>

#include "../tlib/tlib.h"
#include "jobs.h"
#include "include/test_tokenizer.h"
#include "tokenizer.h"

void insert_argument(char *argv[], const char *token, int arg_count);
void reset_arg_buffer(char *arg_buffer, int *arg_index);
void add_char_to_buffer(char *arg_buffer, char c, int arg_index);

static void init_command(struct Command *cmd) {
    memset(cmd, 0, sizeof(*cmd));
}

static void test_insert_argument(void) {
    char *argv[3] = {NULL, NULL, NULL};
    char token[] = "ls";

    insert_argument(argv, token, 1);

    // Should be null since we told insert_argument to insert 'ls' at index=1
    TEST_ASSERT_NULL(argv[0]);
    // This is where 'ls' should be
    TEST_ASSERT_NOT_NULL(argv[1]);
    // Was insertion done properly?
    TEST_ASSERT_EQUAL_CHAR_ARR("ls", argv[1]);
}

static void test_reset_arg_buffer(void) {
    char test_buf[] = {'H', 'e', 'l', 'l', 'o', '\n'};
    int idx = 5;

    reset_arg_buffer(test_buf, &idx);

    TEST_ASSERT_EQUAL_CHAR('\0', test_buf[0]);
    TEST_ASSERT_EQUAL_INT((int32_t) 0, (int32_t) idx);
}

static void test_add_char_to_buffer(void) {
    char test_buf[8];

    add_char_to_buffer(test_buf,'a', 0);
    TEST_ASSERT_EQUAL_CHAR('a', test_buf[0]);
    TEST_ASSERT_EQUAL_CHAR('\0', test_buf[1]);

    add_char_to_buffer(test_buf, 'b', 1);
    TEST_ASSERT_EQUAL_CHAR_ARR("ab", test_buf);
}

static void test_tokenize_input_single_token(void) {
    struct Command cmd;
    init_command(&cmd);
    char input[] = "ls";

    tokenize_input(input, &cmd);

    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("ls", cmd.argv[0]);
    TEST_ASSERT_NULL(cmd.argv[1]);
}

static void test_tokenize_input_multiple_tokens(void) {
    struct Command cmd; init_command(&cmd);
    char input[] = "echo hello world";
 
    tokenize_input(input, &cmd);
 
    TEST_ASSERT_EQUAL_INT((int32_t)3, (int32_t)cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("echo", cmd.argv[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("hello", cmd.argv[1]);
    TEST_ASSERT_EQUAL_CHAR_ARR("world", cmd.argv[2]);
    TEST_ASSERT_NULL(cmd.argv[3]);
}

static void test_tokenize_input_leading_spaces_ignored(void) {
    struct Command cmd; init_command(&cmd);
    char input[] = "   ls -l";
 
    tokenize_input(input, &cmd);
 
    TEST_ASSERT_EQUAL_INT((int32_t)2, (int32_t)cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("ls", cmd.argv[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("-l", cmd.argv[1]);
}

static void test_tokenize_input_trailing_spaces_ignored(void) {
    struct Command cmd; init_command(&cmd);
    char input[] = "ls -l   ";
 
    tokenize_input(input, &cmd);
 
    TEST_ASSERT_EQUAL_INT((int32_t)2, (int32_t)cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("-l", cmd.argv[1]);
    TEST_ASSERT_NULL(cmd.argv[2]);
}

static void test_tokenize_input_special_chars(void) {
    struct Command cmd; init_command(&cmd);
    char input[] = "grep -rn \"foo\" ./dir/*.c";
 
    tokenize_input(input, &cmd);
 
    TEST_ASSERT_EQUAL_INT((int32_t)4, (int32_t)cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("-rn", cmd.argv[1]);
    TEST_ASSERT_EQUAL_CHAR_ARR("\"foo\"", cmd.argv[2]);
    TEST_ASSERT_EQUAL_CHAR_ARR("./dir/*.c", cmd.argv[3]);
}

static void test_tokenize_input_tab_is_not_delimiter(void) {
    struct Command cmd; init_command(&cmd);
    char input[] = "a\tb";
 
    tokenize_input(input, &cmd);
 
    TEST_ASSERT_EQUAL_INT((int32_t)1, (int32_t)cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("a\tb", cmd.argv[0]);
}
 
static void test_tokenize_input_does_not_modify_input(void) {
    struct Command cmd; init_command(&cmd);
    char input[] = "  a  b ";
    char copy[]  = "  a  b ";
 
    tokenize_input(input, &cmd);
 
    TEST_ASSERT_EQUAL_CHAR_ARR(copy, input);
}

static void test_tokenize_buffer_resets_between_tokens(void) {
    // A long token followed by a short one must not leak leftover chars.
    struct Command cmd; 
    init_command(&cmd);
    char input[] = "longtoken x";
 
    tokenize_input(input, &cmd);
 
    TEST_ASSERT_EQUAL_INT((int32_t)2, (int32_t)cmd.argc);
    TEST_ASSERT_EQUAL_CHAR_ARR("longtoken", cmd.argv[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("x", cmd.argv[1]);
}

void run_test_tokenizer(void) {
    RUN_TEST(test_insert_argument);
    RUN_TEST(test_reset_arg_buffer);
    RUN_TEST(test_add_char_to_buffer);
    RUN_TEST(test_tokenize_input_single_token);
    RUN_TEST(test_tokenize_input_multiple_tokens);
    RUN_TEST(test_tokenize_input_leading_spaces_ignored);
    RUN_TEST(test_tokenize_input_trailing_spaces_ignored);
    RUN_TEST(test_tokenize_input_special_chars);
    RUN_TEST(test_tokenize_input_tab_is_not_delimiter);
    RUN_TEST(test_tokenize_input_does_not_modify_input);
    RUN_TEST(test_tokenize_buffer_resets_between_tokens);
}