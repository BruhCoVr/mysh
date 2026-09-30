#include "../include/heap.h"
#include "../include/constants.h"
#include "../tlib/tlib.h"
#include "include/test_heap.h"
#include <stdint.h>

void test_alloc_blocks(void) {
    free_all();

    char *first = alloc(10);
    char *second = alloc(20);

    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (first != NULL));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (second != NULL));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (first != second));
}

void test_alloc_exhaustion(void) {
    free_all();

    char *block = alloc(HEAP_SIZE);
    char *overflow = alloc(1);

    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (block != NULL));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) (overflow == NULL));
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