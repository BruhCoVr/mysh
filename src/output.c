#include "output.h"
#include "lib.h"

int print_str(const char *s) {
    unsigned int len = str_len(s);
    ssize_t bytes_written = write(STDOUT_FD, s, len);

    if (bytes_written == ERROR) {
        return ERROR;
    }

    return SUCCESS;
}

int print_int(const int value) {
    char buffer[ITOA_BUFFER_SIZE];

    itoa_int(value, buffer);

    return print(buffer);
}

int print_size_t(const size_t value) {
    char buffer[ITOA_BUFFER_SIZE];

    itoa_size_t(value, buffer);

    return print(buffer);
}

int print_ssize_t(const ssize_t value) {
    char buffer[ITOA_BUFFER_SIZE];

    itoa_ssize_t(value, buffer);

    return print(buffer);
}

int println(const char *s) {
    if (print(s) == ERROR) {
        return ERROR;
    }

    if (write(STDOUT_FD, "\n", 1) == ERROR) {
        return ERROR;
    }

    return SUCCESS;
}
