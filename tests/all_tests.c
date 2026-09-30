#include "include/test_input.h"
#include "include/test_heap.h"
#include "include/test_lib.h"
#include "include/test_output.h"

int main() {
    run_test_lib();
    run_test_output();
    run_test_input();
    run_test_heap();
}