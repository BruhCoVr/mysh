#ifndef TLIB_H
#define TLIB_H

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\e[0;33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

extern int test_failure_count;

#define TEST_ASSERT_EQUAL_UINT(expected, actual) \
    _Generic((expected), \
        uint8_t: assert_equal_uint8, \
        uint16_t: assert_equal_uint16, \
        uint32_t: assert_equal_uint32 \
    )((expected), (actual), __FILE__, __LINE__)

#define TEST_ASSERT_EQUAL_INT(expected, actual) \
    _Generic((expected), \
        int8_t: assert_equal_int8, \
        int16_t: assert_equal_int16, \
        int32_t: assert_equal_int32 \
    )((expected), (actual), __FILE__, __LINE__)

void assert_equal_uint8(uint8_t expected, uint8_t actual, const char* file, int line);
void assert_equal_uint16(uint16_t expected, uint16_t actual, const char* file, int line);
void assert_equal_uint32(uint32_t expected, uint32_t actual, const char* file, int line);
void assert_equal_int8(int8_t expected, int8_t actual, const char* file, int line);
void assert_equal_int16(int16_t expected, int16_t actual, const char* file, int line);
void assert_equal_int32(int32_t expected, int32_t actual, const char* file, int line);


#define TEST_ASSERT_EQUAL_CHAR_ARR(expected, actual) \
    assert_equal_char_arr((expected), (actual), __FILE__, __LINE__)

void assert_equal_char_arr(const char* expected, const char* actual, const char* file, int line);

#define TEST_ASSERT_EQUAL_CHAR(expected, actual) \
    assert_equal_char((expected), (actual), __FILE__, __LINE__)
    
void assert_equal_char(const char expected, const char actual, const char* file, int line);

#define RUN_TEST(test_function) do { \
    int prev_fails = test_failure_count; \
    printf("Running %s ... ", #test_function); \
    test_function(); \
    if (test_failure_count == prev_fails) { \
        printf(ANSI_COLOR_GREEN "PASS\n" ANSI_COLOR_RESET); \
    } else { \
        printf(ANSI_COLOR_RED "FAIL\n" ANSI_COLOR_RESET); \
    } \
} while(0)

#endif