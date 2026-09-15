#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <errno.h>

#include <lib.h>

int readline(char *buffer);

void flush_buffer(int bytes_read);

void stringify_buffer(char* input_buffer, int bytes_read);

void echo_input(char *input);

#endif