#include <stdint.h>
#include "tlib.h"
#include <stdio.h>
#include <string.h>

int test_failure_count = 0;

void assert_equal_uint8(uint8_t expected, uint8_t actual, const char* file, int line) {
    if (expected != actual) {
        printf(ANSI_COLOR_RED "[ASSERTION FAILED: UINT8 Mismatch] in %s at line %d\n" ANSI_COLOR_RESET, file, line);
        printf("\tExpected " ANSI_COLOR_YELLOW "%u (0x%02X)" ANSI_COLOR_RESET " and got " ANSI_COLOR_YELLOW "%u (0x%02X)\n" ANSI_COLOR_RESET, expected, expected, actual, actual);
        test_failure_count++;
    }
}

void assert_equal_uint16(uint16_t expected, uint16_t actual, const char* file, int line) {
    if (expected != actual) {
        printf(ANSI_COLOR_RED "[ASSERTION FAILED: UINT16 Mismatch] in %s at line %d\n" ANSI_COLOR_RESET, file, line);
        printf("\tExpected " ANSI_COLOR_YELLOW "%u (0x%04X)" ANSI_COLOR_RESET " and got " ANSI_COLOR_YELLOW "%u (0x%04X)\n" ANSI_COLOR_RESET, expected, expected, actual, actual);
        test_failure_count++;
    }
}

void assert_equal_uint32(uint32_t expected, uint32_t actual, const char* file, int line) {
    if (expected != actual) {
        printf(ANSI_COLOR_RED "[ASSERTION FAILED: UINT32 Mismatch] in %s at line %d\n" ANSI_COLOR_RESET, file, line);
        printf("\tExpected " ANSI_COLOR_YELLOW "%u (0x%08X)" ANSI_COLOR_RESET " and got " ANSI_COLOR_YELLOW "%u (0x%08X)\n" ANSI_COLOR_RESET, expected, expected, actual, actual);
        test_failure_count++;
    }
}

void assert_equal_int8(int8_t expected, int8_t actual, const char* file, int line) {
    if (expected != actual) {
        printf(ANSI_COLOR_RED "[ASSERTION FAILED: INT8 Mismatch] in %s at line %d\n" ANSI_COLOR_RESET, file, line);
        printf("\tExpected " ANSI_COLOR_YELLOW "%d (0x%02X)" ANSI_COLOR_RESET " and got " ANSI_COLOR_YELLOW "%d (0x%02X)\n" ANSI_COLOR_RESET, expected, expected, actual, actual);
        test_failure_count++;
    }
}

void assert_equal_int16(int16_t expected, int16_t actual, const char* file, int line) {
    if (expected != actual) {
        printf(ANSI_COLOR_RED "[ASSERTION FAILED: INT16 Mismatch] in %s at line %d\n" ANSI_COLOR_RESET, file, line);
        printf("\tExpected " ANSI_COLOR_YELLOW "%d (0x%04x)" ANSI_COLOR_RESET " and got " ANSI_COLOR_YELLOW "%d (0x%04x)\n" ANSI_COLOR_RESET, expected, expected, actual, actual);
        test_failure_count++;
    }
}

void assert_equal_int32(int32_t expected, int32_t actual, const char* file, int line) {
    if (expected != actual) {
        printf(ANSI_COLOR_RED "[ASSERTION FAILED: INT32 Mismatch] in %s at line %d\n" ANSI_COLOR_RESET, file, line);
        printf("\tExpected " ANSI_COLOR_YELLOW "%d (0x%08X)" ANSI_COLOR_RESET " and got " ANSI_COLOR_YELLOW "%d (0x%08X)\n" ANSI_COLOR_RESET, expected, expected, actual, actual);
        test_failure_count++;
    }
}

void assert_equal_char_arr(const char* expected, const char* actual, const char* file, int line) {
    // Use strcmp function from string.h to test if equal
    int areEqual = strcmp(expected, actual);
    if (areEqual != 0) {
        printf(ANSI_COLOR_RED "[ASSERTION FAILED: Char Array Mismatch] in %s at line %d\n" ANSI_COLOR_RESET, file, line);
        printf("\tExpected " ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET " and got " ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET, expected, actual);
        test_failure_count++;
    }
}
