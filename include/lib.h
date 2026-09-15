#ifndef LIB_H
#define LIB_H

#include <stddef.h>
#include <unistd.h>


int str_len(const char *s);

char* reverse(char* str);

char* itoa_int(int value, char* str);
char* itoa_size_t(size_t value, char* str);
char* itoa_ssize_t(ssize_t value, char* str);

#define itoa(VALUE, STR) _Generic((VALUE), \
    int: itoa_int, \
    size_t: itoa_size_t, \
    ssize_t: itoa_ssize_t \
)(VALUE, STR)
    

ssize_t print_str(const char *s);
ssize_t print_int(const int value);
ssize_t print_size_t(const size_t value);
ssize_t print_ssize_t(const ssize_t value);

#define print(VALUE) _Generic((VALUE), \
    int: print_int, \
    size_t: print_size_t, \
    ssize_t: print_ssize_t, \
    default: print_str \
)(VALUE)

int strcmp(const char *str1, const char *str2);

#endif