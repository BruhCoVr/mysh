#include "../tlib/tlib.h"
#include "../include/input.h"
#include "../include/constants.h"

/*
void test_readline(void) {
    // run this and copy it into the terminal to get the test to pass
    // redundant, annoying test after it passes once
    // Also tested 258 characters and still got only 256 returned from the function,
    // so this follows expected behaviour as we do not allow more than 256 to be read
    // into the buffer anyways
    char test_buffer[256] = "Test the readline(char *input_buffer) with this test_buffer yipeeeeee!@!";
    TEST_ASSERT_EQUAL_INT(256, readline(test_buffer, STDIN_FD));
}
*/

void test_flush_buffer(void) {
    TEST_ASSERT_EQUAL_INT(0, flush_buffer(FALSE, STDIN_FD));
    TEST_ASSERT_EQUAL_INT(0, flush_buffer(TRUE, STDIN_FD));
}

/*
void test_stringify_buffer(void) {
    char buffer[] = "Hello world\n";
    stringify_buffer(buffer, 12);
    TEST_ASSERT_EQUAL_CHAR('\0', buffer[11]);

    // We should be keeping the 'H' here since we
    // don't want to overwrite any input we receive
    char buffer1[] = {'H'};
    stringify_buffer(buffer1, 1);
    TEST_ASSERT_EQUAL_CHAR('H', buffer1[0]);

    // Trying to see if it errors out like crazy here
    // I think it will since there isn't any checking on bounds
    char buffer2[] = {};
    stringify_buffer(buffer2, 0);
}
*/

void run_test_input(void) {
    /*RUN_TEST(test_readline);*/
    RUN_TEST(test_flush_buffer);
    /*RUN_TEST(test_stringify_buffer);*/
}