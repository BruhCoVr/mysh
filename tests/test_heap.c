#include "../include/heap.h"
#include "../include/constants.h"
#include "../tlib/tlib.h"
#include "include/test_heap.h"
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>

void test_alloc_blocks(void) {
    free_all();

    char *first = alloc(10);
    char *second = alloc(20);

    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (first != NULL));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (second != NULL));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (first != second));
}

void test_alloc_exhaustion(void) {
    pid_t pid = fork();

    if (pid == 0) {
        free_all();
        alloc(HEAP_SIZE);
        alloc(1); // heap is now full; this should exit(1)
        _exit(0); // unreachable if alloc() behaves correctly
    }

    int status;
    waitpid(pid, &status, 0);

    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) WIFEXITED(status));
    TEST_ASSERT_EQUAL_INT((int8_t) 1, (int8_t) WEXITSTATUS(status));
}

void test_free_all(void) {
    free_all();

    char *first = alloc(10);
    free_all();
    char *after_reset = alloc(10);

    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (first == after_reset));
}

void run_test_heap(void) {
    RUN_TEST(test_alloc_blocks);
    RUN_TEST(test_alloc_exhaustion);
    RUN_TEST(test_free_all);
}