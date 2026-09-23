#include "include/test_heap.h"

void test_alloc_no_pointer_overlap(void) {
    char* memp_0 = alloc(500);
    char* memp_1 = alloc(500);
    TEST_ASSERT_EQUAL_CHAR(FALSE, memp_0 == memp_1);
    char* memp_2 = alloc(128);
    TEST_ASSERT_EQUAL_CHAR(FALSE, memp_2 == memp_1);
}

void test_alloc_overfill(void) {
    char* memp_0 = alloc(HEAP_SIZE + 1);
    TEST_ASSERT_EQUAL_CHAR(ERROR, memp_0);
}
void test_alloc_exact_fill(void) {
    char* memp_0 = alloc(HEAP_SIZE);
    TEST_ASSERT_EQUAL_CHAR(TRUE, memp_0 > 0);
}

void test_free_all(void) {
    char* heap_startp = alloc(128);
    char* memp_0 = alloc(128);
    char* new_allocp = alloc(128);
    free_all();
    char* heap_startp_new = alloc(128);
    TEST_ASSERT_EQUAL_CHAR(heap_startp, heap_startp_new);
}

void run_test_heap(void) {
    RUN_TEST(test_alloc_no_pointer_overlap);
    RUN_TEST(test_alloc_overfill);
    RUN_TEST(test_alloc_exact_fill);
    RUN_TEST(test_free_all);
}