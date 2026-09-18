#include "../include/lib.h"
#include "../tlib/tlib.h"
#include <stdio.h>

void test_str_len() {
    TEST_ASSERT_EQUAL_UINT((uint8_t) 0, (uint8_t) str_len(""));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 5, (uint8_t) str_len("Hello"));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 255, (uint8_t) str_len("This is two hundred and fifty five characters of text and I am testing the str_len function to see if it will  return 255. Currently I have tested an empty string, five character string, and now a two hundred and fifty five character string. Wee wee Boo b"));
}

void test_str_cmp() {
    TEST_ASSERT_EQUAL_UINT((uint8_t) 0, (uint8_t) str_cmp("H", "Hi"));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) str_cmp("Hi", "Hi"));
    TEST_ASSERT_EQUAL_UINT((uint8_t) 1, (uint8_t) str_cmp("Hello : World!", "Hello : World!"));
}

void test_reverse() {
    char test1[] = "test";
    char test2[] = "hi";
    char test3[] = "office chair";
    TEST_ASSERT_EQUAL_CHAR_ARR("tset", reverse(test1));
    TEST_ASSERT_EQUAL_CHAR_ARR("ih", reverse(test2));
    TEST_ASSERT_EQUAL_CHAR_ARR("riahc eciffo", reverse(test3));
}

/*
void test_digit_to_char() {

}

void test_itoa_int() {

}
*/
int main(void) {
    RUN_TEST(test_str_len);
    RUN_TEST(test_str_cmp);
    RUN_TEST(test_reverse);
    return 0;
}