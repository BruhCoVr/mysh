#include "../tlib/tlib.h"
#include "../include/input.h"
#include "../include/constants.h"
#include <string.h>

/**
 * Fake console input by creating a pipe.
 * @return file descriptor
 */
static int make_pipe(const char *data) {
    int fd_arr[2];
    pipe(fd_arr);
    write(fd_arr[1], data, strlen(data));
    close(fd_arr[1]);
    return fd_arr[0];
}


void test_readline_normal_input(void) {
    char test_buf[MAX_BUFFER_SIZE] = {0};
    int fd = make_pipe("hello\n");
    int num_bytes_read = readline(test_buf, fd);
    close(fd);

    TEST_ASSERT_EQUAL_INT(6, num_bytes_read);
    TEST_ASSERT_EQUAL_CHAR('\n', test_buf[5]);
}

void test_readline_empty(void) {
    char test_buf[MAX_BUFFER_SIZE] = {0};
    int fd = make_pipe("\n");
    int num_bytes_read = readline(test_buf, fd);
    close(fd);
    TEST_ASSERT_EQUAL_INT(1, num_bytes_read);
    TEST_ASSERT_EQUAL_CHAR('\n', test_buf[0]);
}

void test_readline_max_buffer(void) {
    char test_buf[MAX_BUFFER_SIZE];
    // Fill entire buffer with 'T'
    memset(test_buf, 'T', sizeof(test_buf));
    
    char new_buf[MAX_BUFFER_SIZE] = {0};
    int fd = make_pipe(test_buf);
    // test_buf is attached to fd, we want to read test_buf into new_buf
    int num_bytes_read = readline(new_buf, fd);
    close(fd);

    TEST_ASSERT_EQUAL_INT(MAX_BUFFER_SIZE, num_bytes_read);
}

void test_readline_overfull_buffer(void) {
    char overfull_buf[MAX_BUFFER_SIZE + 10];
    memset(overfull_buf, 'T', sizeof(overfull_buf));
    // Put LF past where buffer should be able to be read
    overfull_buf[MAX_BUFFER_SIZE + 3] = '\n';

    char new_buf[MAX_BUFFER_SIZE] = {0};
    int fd = make_pipe(overfull_buf);
    int num_bytes_read = readline(new_buf, fd);
    close(fd);

    TEST_ASSERT_EQUAL_INT(MAX_BUFFER_SIZE, num_bytes_read);
}

void test_stringify_buffer(void) {
    char test_buf[] = "hello\n";
    stringify_buffer(test_buf, 6);
    TEST_ASSERT_EQUAL_CHAR('\0', test_buf[5]);
    char* expected = "hello";
    TEST_ASSERT_EQUAL_CHAR_ARR(expected, test_buf);
}

void test_flush_buffer(void) {
    TEST_ASSERT_EQUAL_INT(0, flush_buffer(FALSE, STDIN_FD));
    TEST_ASSERT_EQUAL_INT(0, flush_buffer(TRUE, STDIN_FD));
}

void run_test_input(void) {
    RUN_TEST(test_readline_normal_input);
    RUN_TEST(test_readline_empty);
    RUN_TEST(test_readline_max_buffer);
    RUN_TEST(test_readline_overfull_buffer);
    RUN_TEST(test_stringify_buffer);
    RUN_TEST(test_flush_buffer);
}