#ifndef TEST_E2E_H
#define TEST_E2E_H

void test_empty_line(void);
void test_redundant_spaces(void);
void test_buffer_overflow_truncation(void);
void test_heap_exhaustion_exits_with_status_1(void);
void test_unknown_command(void);
void test_multi_arg_command(void);
void test_absolute_path_invocation(void);
void test_relative_path_invocation(void);
void test_bare_exit_first_command(void);
void test_input_after_exit_ignored(void);
void test_multiple_sequential_commands(void);
void run_test_e2e(void);

#endif
