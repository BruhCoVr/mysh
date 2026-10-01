#include "../tlib/tlib.h"
#include "../include/commands.h"
#include "../include/lib.h"
#include "../include/constants.h"
#include "./include/test_run.h"


void test_command(void){
	struct Command command = {
		.argv = {"/bin/echo", "hello", NULL},
		.argc = 2
	};

	TEST_ASSERT_EQUAL_INT(SUCCESS, run_command(&command));
}

void test_nonexistent_path(void){
	struct Command command = {
		.argv = {"/definitely/not/a/real/command", NULL},
		.argc = 1
	};
	struct Command recovery_command = {
		.argv = {"/bin/echo", "still running", NULL},
		.argc = 2
	};

	//TEST_ASSERT_EQUAL_INT(ERROR, run_command(&command));
	TEST_ASSERT_EQUAL_INT(SUCCESS, run_command(&recovery_command));
}

void test_non_zero_exit(void){
	struct Command command = {
		.argv = {"/bin/false", NULL},
		.argc = 1
	};
	struct Command recovery_command = {
		.argv = {"/bin/echo", "still running", NULL},
		.argc = 2
	};

	//TEST_ASSERT_EQUAL_INT(ERROR, run_command(&command));
	TEST_ASSERT_EQUAL_INT(SUCCESS, run_command(&recovery_command));
}

void run_many_arg(void){
	struct Command command = {
		.argv = {"/bin/echo", "one", "two", "three", "four", "five",
				 "six", "seven", "eight", "nine", "ten", NULL},
		.argc = 11
	};

	TEST_ASSERT_EQUAL_INT(SUCCESS, run_command(&command));
}

void run_test_run(void){
	RUN_TEST(test_command);
	RUN_TEST(test_nonexistent_path);
	RUN_TEST(test_non_zero_exit);
	RUN_TEST(run_many_arg);

}