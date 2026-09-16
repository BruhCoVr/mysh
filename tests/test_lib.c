#include "../include/lib.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int success_state = TRUE;

void TEST_ASSERT_EQUAL_UINT8(__uint8_t expected, __uint8_t actual) {
    if (expected == actual) {
        printf(ANSI_COLOR_GREEN "PASS\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_RED "FAIL: %d does not equal %d\n" ANSI_COLOR_RESET, expected, actual);
    success_state = FALSE;
}

void test_str_len(void) {
    printf("Testing str_len empty: ");
    TEST_ASSERT_EQUAL_UINT8(0, str_len(""));
    printf("Testing str_len of 5: ");
    TEST_ASSERT_EQUAL_UINT8(5, str_len("Hello"));
    printf("Testing str_len of 255 string: ");
    TEST_ASSERT_EQUAL_UINT8(255, str_len("This is two hundred and fifty five characters of text and I am testing the str_len function to see if it will  return 255. Currently I have tested an empty string, five character string, and now a two hundred and fifty five character string. Wee wee Boo b"));
}

int main(void) {
    test_str_len();
    return success_state;
}