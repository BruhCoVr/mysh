#include "include/test_input.h"
#include "include/test_heap.h"
#include "include/test_lib.h"
#include "include/test_output.h"
#include "include/test_tokenizer.h"
#include "include/test_commands.h"
#include <stdio.h>

int main() {
    printf("Testing lib.c\n");
    run_test_lib();
    printf("\nTesting output.c\n");
    run_test_output();
    printf("\nTesting input.c\n");
    run_test_input();
    printf("\nTesting heap.c\n");
    run_test_heap();
    printf("\nTesting tokenizer.c\n");
    run_test_tokenizer();
    printf("\nTesting commands.c\n");
    run_test_commands();
}