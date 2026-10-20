#include <string.h>
#include <stdlib.h>

#include "../tlib/tlib.h"
#include "include/test_tokenizer.h"
#include "../include/tokenizer.h"
#include "../include/constants.h"

/**
 * Allocate a bunch of chars to mimic program functionality
 * while reading input
 */
static void init_tokens(char *tokens[]) {
    memset(tokens, 0, sizeof(char *) * (MAX_TOKENS + 1));
}

/**
 * Helper to count the number of tokens we have
 */
static int count_tokens(char *tokens[]) {
    int count = 0;
    while (count < MAX_TOKENS + 1 && tokens[count] != NULL) {
        count++;
    }
    return count;
}

static void test_tokenize_input_single_token(void) {
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "ls";

    int status = tokenize_input(input, tokens);

    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) status);
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) count_tokens(tokens));
    TEST_ASSERT_EQUAL_CHAR_ARR("ls", tokens[0]);
    TEST_ASSERT_NULL(tokens[1]);
}

static void test_tokenize_input_multiple_tokens(void) {
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "echo hello world";
 
    int status = tokenize_input(input, tokens);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) status);
    TEST_ASSERT_EQUAL_INT((int32_t)3, (int32_t) count_tokens(tokens));
    TEST_ASSERT_EQUAL_CHAR_ARR("echo", tokens[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("hello", tokens[1]);
    TEST_ASSERT_EQUAL_CHAR_ARR("world", tokens[2]);
    TEST_ASSERT_NULL(tokens[3]);
}

static void test_tokenize_input_leading_spaces_ignored(void) {
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "   ls -l";
 
    int status = tokenize_input(input, tokens);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) status);
    TEST_ASSERT_EQUAL_INT((int32_t)2, (int32_t) count_tokens(tokens));
    TEST_ASSERT_EQUAL_CHAR_ARR("ls", tokens[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("-l", tokens[1]);
}

static void test_tokenize_input_trailing_spaces_ignored(void) {
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "ls -l   ";
 
    int status = tokenize_input(input, tokens);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) status);
    TEST_ASSERT_EQUAL_INT((int32_t)2, (int32_t) count_tokens(tokens));
    TEST_ASSERT_EQUAL_CHAR_ARR("-l", tokens[1]);
    TEST_ASSERT_NULL(tokens[2]);
}

static void test_tokenize_input_special_chars(void) {
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "grep -rn \"foo\" ./dir/*.c";
 
    int status = tokenize_input(input, tokens);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) status);
    TEST_ASSERT_EQUAL_INT((int32_t)4, (int32_t) count_tokens(tokens));
    TEST_ASSERT_EQUAL_CHAR_ARR("-rn", tokens[1]);
    TEST_ASSERT_EQUAL_CHAR_ARR("\"foo\"", tokens[2]);
    TEST_ASSERT_EQUAL_CHAR_ARR("./dir/*.c", tokens[3]);
}

static void test_tokenize_input_tab_is_not_delimiter(void) {
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "a\tb";
 
    int status = tokenize_input(input, tokens);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) status);
    TEST_ASSERT_EQUAL_INT((int32_t)1, (int32_t) count_tokens(tokens));
    TEST_ASSERT_EQUAL_CHAR_ARR("a\tb", tokens[0]);
}
 
static void test_tokenize_input_does_not_modify_input(void) {
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "  a  b ";
    char copy[]  = "  a  b ";
 
    tokenize_input(input, tokens);
 
    TEST_ASSERT_EQUAL_CHAR_ARR(copy, input);
}

static void test_tokenize_buffer_resets_between_tokens(void) {
    // A long token followed by a short one must not leak leftover chars.
    char *tokens[MAX_TOKENS + 1];
    init_tokens(tokens);
    char input[] = "longtoken x";
 
    int status = tokenize_input(input, tokens);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) status);
    TEST_ASSERT_EQUAL_INT((int32_t)2, (int32_t) count_tokens(tokens));
    TEST_ASSERT_EQUAL_CHAR_ARR("longtoken", tokens[0]);
    TEST_ASSERT_EQUAL_CHAR_ARR("x", tokens[1]);
}

void run_test_tokenizer(void) {
    RUN_TEST(test_tokenize_input_single_token);
    RUN_TEST(test_tokenize_input_multiple_tokens);
    RUN_TEST(test_tokenize_input_leading_spaces_ignored);
    RUN_TEST(test_tokenize_input_trailing_spaces_ignored);
    RUN_TEST(test_tokenize_input_special_chars);
    RUN_TEST(test_tokenize_input_tab_is_not_delimiter);
    RUN_TEST(test_tokenize_input_does_not_modify_input);
    RUN_TEST(test_tokenize_buffer_resets_between_tokens);
}