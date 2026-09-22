#include "../include/output.h"
#include "../tlib/tlib.h"
#include "include/test_output.h"
#include <stdint.h>

void test_print_str(void) {
    /**
     * Quick note on the other print functions such as print_size_t(const size_t value)
     * It is not necessary to test those as they all call functions that are tested
     * before this one.
     */
    const char* str = "This is a test string\n";
    const char* str1 = "Now another test string with some fun #)(&*^& characters and 1234134 numbers\n";
    int8_t result = print_str(str);
    int8_t result1 = print_str(str1);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(0, result1);
}

void test_println(void) {
    const char* str = "This is a test string";
    const char* str1 = "Now another test string with some fun #)(&*^& characters and 1234134 numbers";
    int8_t result = println(str);
    int8_t result1 = println(str1);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(0, result1);
}

void run_test_output(void) {
    RUN_TEST(test_print_str);
    RUN_TEST(test_println);
}
