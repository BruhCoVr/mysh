#include "lib.h"

unsigned int str_len(const char *s) {
    unsigned int len = 0;

    while (s[len] != NULL_TERMINATOR) {
        len++;
    }

    return len;
}

char* reverse(char* str) {
    char* start = str;
    char* end = str;

    // Move the end pointer to the last character
    while (*end != NULL_TERMINATOR) {
        end++;
    }
    end--;

    // Swap characters from start and end until they meet in the middle
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }

    return str;
}

char digit_to_char(int digit) {
    return '0' + digit;
}

char* itoa_int(int value, char* str) {
    char* ptr = str;
    
    int is_negative = 0;
    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

    do {
        *ptr++ = digit_to_char(value % 10);
        value /= 10;
    } while (value > 0);

    if (is_negative) {
        *ptr++ = '-';
    }
    *ptr = NULL_TERMINATOR;

    return reverse(str);
} 

char* itoa_size_t(size_t value, char* str) {
    char* ptr = str;

    do {
        *ptr++ = digit_to_char(value % 10);
        value /= 10;
    } while (value > 0);

    *ptr = NULL_TERMINATOR;

    return reverse(str);
}

char* itoa_ssize_t(ssize_t value, char* str) {
    char* ptr = str;

    if (value == ERROR) {
        ptr[0] = '-';
        ptr[1] = '1';
        ptr[2] = NULL_TERMINATOR;

        return str;
    }    

    do {
        *ptr++ = digit_to_char(value % 10);
        value /= 10;
    } while (value > 0);

    *ptr = NULL_TERMINATOR;

    return reverse(str);
}


int str_eq(const char *str1, const char *str2) {
    int i1 = 0;
    int i2 = 0;

    while (str1[i1] != NULL_TERMINATOR && str2[i2] != NULL_TERMINATOR) {
        if (str1[i1] != str2[i2]) {
            return FALSE;
        }

        i1++;
        i2++;
    }

    return str1[i1] == str2[i2];
}

void str_cpy(char *dest, const char *src) {
    int i = 0;

    while (src[i] != NULL_TERMINATOR) {
        dest[i] = src[i];
        i++;
    }

    dest[i] = NULL_TERMINATOR;
}

void exit(int status) {
    // Mask as 0-255 are the only valid status exit codes
    status = status & 255;
    syscall(SYS_exit_group, status);
}

int handle_error(const char *msg) {
    if (str_eq(msg, "") == FALSE) {
        println(msg);
    }

    return ERROR;
}

int handle_error_with_memory_cleanup(const char *msg) {
    free_all();
    return handle_error(msg);
}