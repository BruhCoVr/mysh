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
void test_output_redirection(void);
void test_output_redirection_truncates(void);
void test_input_redirection(void);
void test_input_and_output_redirection(void);
void test_two_stage_pipeline(void);
void test_three_stage_pipeline(void);
void test_pipeline_with_input_redirection(void);
void test_pipeline_with_output_redirection(void);
void run_test_e2e(void);

#endif
