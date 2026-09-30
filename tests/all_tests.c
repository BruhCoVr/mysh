#include "include/test_input.h"
#include "include/test_heap.h"
#include "include/test_lib.h"
#include "include/test_output.h"
#include "include/test_e2e.h"
#include "include/test_run.h"

int main() {
    run_test_lib();
    run_test_output();
    run_test_input();
    run_test_heap();
    run_test_e2e();
    run_test_run();
}