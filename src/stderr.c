#include "stderr.h"

int errprint(const char *s) {
    unsigned int len = str_len(s);
    ssize_t bytes_written = write(STDERR_FD, s, len);

    if (bytes_written == ERROR) {
        return ERROR;
    }

    return SUCCESS;
}

int errprintln(const char *s) {
    if (errprint(s) == ERROR) {
        return ERROR;
    }

    if (write(STDERR_FD, "\n", 1) == ERROR) {
        return ERROR;
    }

    return SUCCESS;
}