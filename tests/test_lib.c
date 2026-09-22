#include "../include/lib.h"
#include "../tlib/tlib.h"
#include "include/test_lib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void test_str_len(void) {
    TEST_ASSERT_EQUAL_UINT((uint8_t) 0, (uint8_t) str_len(""));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 5, (uint8_t) str_len("Hello"));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 255, (uint8_t) str_len("This is two hundred and fifty five characters of text and I am testing the str_len function to see if it will  return 255. Currently I have tested an empty string, five character string, and now a two hundred and fifty five character string. Wee wee Boo b"));
}

void test_str_cmp(void) {
    TEST_ASSERT_EQUAL_UINT((uint8_t) 0, (uint8_t) str_cmp("H", "Hi"));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) str_cmp("Hi", "Hi"));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) str_cmp("Hello : World!", "Hello : World!"));
}

void test_reverse(void) {
    char test1[] = "test";
    char test2[] = "hi";
    char test3[] = "office chair";
    TEST_ASSERT_EQUAL_CHAR_ARR("tset", reverse(test1));
    TEST_ASSERT_EQUAL_CHAR_ARR("ih", reverse(test2));
    TEST_ASSERT_EQUAL_CHAR_ARR("riahc eciffo", reverse(test3));
}

//test negative numbers and numbers larger than 20 characters
//i dont think we can checkt numbers larger than 20 due to the biggest value c can take in
void test_itoa_int(void) {
    int num = 2345;
    int neg_num = -9436;
    char buffer[ITOA_BUFFER_SIZE];

    TEST_ASSERT_EQUAL_CHAR_ARR("2345", itoa(num, buffer));
    TEST_ASSERT_EQUAL_CHAR_ARR("-9436", itoa(neg_num, buffer));
}

void test_itoa_sizet(void) {
    size_t num = 2345;
    size_t large_num = 1234567891234567892;
    char buffer[ITOA_BUFFER_SIZE];

    TEST_ASSERT_EQUAL_CHAR_ARR("2345", itoa(num, buffer));
    TEST_ASSERT_EQUAL_CHAR_ARR("1234567891234567892", itoa(large_num, buffer));
}

void test_itoa_ssizet(void) {
    ssize_t num = 2345;
    ssize_t neg_num = -1;
    ssize_t large_num = 1234567891234567892;
    char buffer[ITOA_BUFFER_SIZE];

    TEST_ASSERT_EQUAL_CHAR_ARR("2345", itoa(num, buffer));
    TEST_ASSERT_EQUAL_CHAR_ARR("-1", itoa(neg_num, buffer));
    TEST_ASSERT_EQUAL_CHAR_ARR("1234567891234567892", itoa(large_num, buffer));
}

void test_digit_to_char(void) {
    char expected_digits[3] = {'0' + 8 ,'0' + 1, '0' + 2};
    TEST_ASSERT_EQUAL_CHAR(expected_digits[0], '8');
    TEST_ASSERT_EQUAL_CHAR(expected_digits[1], '1');
    TEST_ASSERT_EQUAL_CHAR(expected_digits[2], '2');
}

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

void test_str_cpy(void) {
    const char* str = "Test of strcpy\n";
    char dest[30];

    str_cpy(dest, str);
    TEST_ASSERT_EQUAL_INT(0, strcmp(str, dest));
}

void run_test_lib(void) {
    RUN_TEST(test_str_len);
    RUN_TEST(test_str_cmp);
    RUN_TEST(test_reverse);
    RUN_TEST(test_itoa_int);
    RUN_TEST(test_itoa_sizet);
    RUN_TEST(test_itoa_ssizet);
    RUN_TEST(test_digit_to_char);
    RUN_TEST(test_print_str);
    RUN_TEST(test_println);
    RUN_TEST(test_str_cpy);
}