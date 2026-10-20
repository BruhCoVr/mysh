#include "../tests/include/test_cache.h"
#include "../tlib/tlib.h"
#include "../include/cache.h"
#include "../include/constants.h"
#include <stdio.h>
#include <unistd.h>

static void test_insert_then_lookup(void) {
    char out_path[CACHE_MAX_PATH] = {0};
    
    int insert_status = cache_insert("echo", "/usr/bin/echo");
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) insert_status);

    int lookup_status = cache_lookup("echo", out_path);
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) lookup_status);
    TEST_ASSERT_EQUAL_CHAR_ARR("/usr/bin/echo", out_path);
}

static void test_lookup_missing(void) {
    char out_path[CACHE_MAX_PATH] = "no command";
    int lookup_status = cache_lookup("not_a_cached_command", out_path);
    
    TEST_ASSERT_EQUAL_INT((int32_t) ENTRYNOTFOUND, lookup_status);

    TEST_ASSERT_EQUAL_CHAR_ARR("no command", out_path);
}

static void test_insert_duplicate(void) {
    char out_path[CACHE_MAX_PATH] = {0};
    
    int insert_status = cache_insert("ls", "/bin/ls");
    
    insert_status = cache_insert("ls", "/bin/ls");

    TEST_ASSERT_EQUAL_INT((int32_t) ENTRYEXISTS, insert_status);
}

static void test_insert_multiple(void) {
    char out_path[CACHE_MAX_PATH] = {0};
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) insert_tracked("grep", "/usr/bin/grep"));
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) insert_tracked("sort", "/usr/bin/sort"));
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) insert_tracked("wc", "/usr/bin/wc"));
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) cache_lookup("grep", out_path));
    TEST_ASSERT_EQUAL_CHAR_ARR("/usr/bin/grep", out_path);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) cache_lookup("sort", out_path));
    TEST_ASSERT_EQUAL_CHAR_ARR("/usr/bin/sort", out_path);
 
    TEST_ASSERT_EQUAL_INT((int32_t) SUCCESS, (int32_t) cache_lookup("wc", out_path));
    TEST_ASSERT_EQUAL_CHAR_ARR("/usr/bin/wc", out_path);
}

static void test_insert_too_long(void) {
    // Setup key w/ null terminator
    char long_cmd[CACHE_KEY_MAX + 5];
    memset(long_cmd, 't', CACHE_KEY_MAX + 4);
    long_cmd[CACHE_KEY_MAX + 1] = '\0';

    char out_path[CACHE_KEY_MAX] = {0};

    int insert_status = cache_insert(long_cmd, "/bin/longcmd");
    TEST_ASSERT_TRUE(insert_status == ERROR);
}

void run_test_cache(void) {
    RUN_TEST(test_insert_then_lookup);
    RUN_TEST(test_lookup_missing);
    RUN_TEST(test_insert_duplicate);
    RUN_TEST(test_insert_multiple);
    RUN_TEST(test_insert_too_long);
}

