#include "../tlib/tlib.h"
#include "../include/constants.h"
#include "include/test_e2e.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MYSH_BIN "./mysh"
#define E2E_IN_PATH "/tmp/mysh_e2e.in"
#define E2E_OUT_PATH "/tmp/mysh_e2e.out"
#define E2E_REL_SCRIPT_PATH "/tmp/e2e_rel.sh"

// Overrides just the vars the prompt embeds, so it's identical
// regardless of who/where the test runs. PATH (needed for the
// path resolution) is left as inherited from the caller's shell.
#define E2E_ENV "env USER=tester HOME=/tmp PWD=/tmp "

// HOME=PWD below, so print_cwd() collapses the path to "~"
#define PROMPT GREEN_COLOR "tester" PURPLE_COLOR " ~ " SHELL_SYMBOL RESET_COLOR

// Runs mysh with the given input script, capturing its stdout+stderr
// and returning its exit code.
static int run_mysh_with_status(const char *input, char *out_buffer, size_t out_size) {
    FILE *in = fopen(E2E_IN_PATH, "w");
    fputs(input, in);
    fclose(in);

    int status = system(E2E_ENV MYSH_BIN " < " E2E_IN_PATH " > " E2E_OUT_PATH " 2>&1");

    FILE *out = fopen(E2E_OUT_PATH, "r");
    size_t n = fread(out_buffer, 1, out_size - 1, out);
    out_buffer[n] = '\0';
    fclose(out);

    return WEXITSTATUS(status);
}

static void run_mysh(const char *input, char *out_buffer, size_t out_size) {
    run_mysh_with_status(input, out_buffer, out_size);
}

// Resolves "echo" to an absolute path via the caller's PATH, so the
// absolute-path test doesn't hardcode a distro-specific location.
static void find_echo_absolute_path(char *out, size_t out_size) {
    FILE *p = popen("command -v echo", "r");
    fgets(out, out_size, p);
    pclose(p);

    size_t len = strlen(out);
    if (len > 0 && out[len - 1] == '\n') {
        out[len - 1] = '\0';
    }
}

void test_empty_line(void) {
    char output[256];
    run_mysh("\nexit\n", output, sizeof(output));

    TEST_ASSERT_EQUAL_CHAR_ARR(PROMPT PROMPT, output);
}

void test_redundant_spaces(void) {
    char output[256];
    run_mysh("echo   one    two\nexit\n", output, sizeof(output));

    TEST_ASSERT_EQUAL_CHAR_ARR(PROMPT "one two\n" PROMPT, output);
}

#define OVERFLOW_A_COUNT 300
// MAX_BUFFER_SIZE (256) - strlen("echo ") - 1 (null terminator slot)
#define TRUNCATED_A_COUNT 250

void test_buffer_overflow_truncation(void) {
    char input[OVERFLOW_A_COUNT + 32] = "echo ";
    memset(input + strlen(input), 'a', OVERFLOW_A_COUNT);
    input[strlen("echo ") + OVERFLOW_A_COUNT] = '\0';
    strcat(input, "\nexit\n");

    char a_run[TRUNCATED_A_COUNT + 1];
    memset(a_run, 'a', TRUNCATED_A_COUNT);
    a_run[TRUNCATED_A_COUNT] = '\0';

    char expected[TRUNCATED_A_COUNT + 128] = "";
    strcat(expected, PROMPT);
    strcat(expected, a_run);
    strcat(expected, "\n");
    strcat(expected, PROMPT);

    char output[TRUNCATED_A_COUNT + 128];
    run_mysh(input, output, sizeof(output));

    TEST_ASSERT_EQUAL_CHAR_ARR(expected, output);
}

// Each token costs a MAX_TOKEN_SIZE alloc() in insert_argument, plus
// MAX_BUFFER_SIZE*2 overhead for the input/arg buffers - with the
// current HEAP_SIZE, that runs out well before MAX_ARGS does (~37
// tokens), and alloc() now exit(1)s the whole shell on exhaustion
// rather than segfaulting
#define HEAP_EXHAUSTION_ARG_COUNT 50

void test_heap_exhaustion_exits_with_status_1(void) {
    char input[256] = "echo";
    int offset = strlen(input);

    for (int i = 0; i < HEAP_EXHAUSTION_ARG_COUNT; i++) {
        offset += snprintf(input + offset, sizeof(input) - offset, " x");
    }
    strcat(input, "\nexit\n");

    char output[256];
    int exit_code = run_mysh_with_status(input, output, sizeof(output));

    // The shell exits before echo ever runs or "exit" is ever read
    TEST_ASSERT_EQUAL_CHAR_ARR(PROMPT, output);
    TEST_ASSERT_EQUAL_INT(1, exit_code);
}

void test_unknown_command(void) {
    char output[512];
    run_mysh("not_a_real_binary\nexit\n", output, sizeof(output));

    char expected[512] = "";
    strcat(expected, PROMPT);
    strcat(expected, "Command not found: not_a_real_binary\n");
    strcat(expected, "Error occurred while executing command\n");
    strcat(expected, PROMPT);

    TEST_ASSERT_EQUAL_CHAR_ARR(expected, output);
}

void test_multi_arg_command(void) {
    char output[512];
    run_mysh("echo -n hi\nexit\n", output, sizeof(output));

    char expected[512] = "";
    strcat(expected, PROMPT);
    strcat(expected, "hi");
    strcat(expected, PROMPT);

    TEST_ASSERT_EQUAL_CHAR_ARR(expected, output);
}

void test_absolute_path_invocation(void) {
    char echo_path[256];
    find_echo_absolute_path(echo_path, sizeof(echo_path));

    char input[320];
    snprintf(input, sizeof(input), "%s hi\nexit\n", echo_path);

    char output[512];
    run_mysh(input, output, sizeof(output));

    char expected[512] = "";
    strcat(expected, PROMPT);
    strcat(expected, "hi\n");
    strcat(expected, PROMPT);

    TEST_ASSERT_EQUAL_CHAR_ARR(expected, output);
}

void test_relative_path_invocation(void) {
    system("printf '#!/bin/sh\\necho relative_ok\\n' > " E2E_REL_SCRIPT_PATH
           " && chmod +x " E2E_REL_SCRIPT_PATH);

    char output[512];
    run_mysh("./e2e_rel.sh\nexit\n", output, sizeof(output));

    char expected[512] = "";
    strcat(expected, PROMPT);
    strcat(expected, "relative_ok\n");
    strcat(expected, PROMPT);

    TEST_ASSERT_EQUAL_CHAR_ARR(expected, output);
}

void test_bare_exit_first_command(void) {
    char output[256];
    int exit_code = run_mysh_with_status("exit\n", output, sizeof(output));

    TEST_ASSERT_EQUAL_CHAR_ARR(PROMPT, output);
    TEST_ASSERT_EQUAL_INT(0, exit_code);
}

void test_input_after_exit_ignored(void) {
    char output[256];
    run_mysh("exit\necho nope\n", output, sizeof(output));

    TEST_ASSERT_EQUAL_CHAR_ARR(PROMPT, output);
}

void test_multiple_sequential_commands(void) {
    char output[512];
    run_mysh("echo first\necho second\nexit\n", output, sizeof(output));

    char expected[512] = "";
    strcat(expected, PROMPT);
    strcat(expected, "first\n");
    strcat(expected, PROMPT);
    strcat(expected, "second\n");
    strcat(expected, PROMPT);

    TEST_ASSERT_EQUAL_CHAR_ARR(expected, output);
}

void run_test_e2e(void) {
    RUN_TEST(test_empty_line);
    RUN_TEST(test_redundant_spaces);
    RUN_TEST(test_buffer_overflow_truncation);
    RUN_TEST(test_heap_exhaustion_exits_with_status_1);
    RUN_TEST(test_unknown_command);
    RUN_TEST(test_multi_arg_command);
    RUN_TEST(test_absolute_path_invocation);
    RUN_TEST(test_relative_path_invocation);
    RUN_TEST(test_bare_exit_first_command);
    RUN_TEST(test_input_after_exit_ignored);
    RUN_TEST(test_multiple_sequential_commands);
}
