/**
 * Configure CuTL so that it stops the execution upon test
 * failure.
 *
 * Date:    2026-04-26
 * Version: 1.0
 */
#define CUTL_NO_PREFIXED_ASSERTIONS
#include <cutl.h>


/* Special functions to run before or after the test functions
 * are called */
void CUTL_BEFORE_ALL()  {}
void CUTL_AFTER_ALL()   {}
void CUTL_BEFORE_EACH() {}
void CUTL_AFTER_EACH()  {}


/* Test functions declaration */
static void test_1_success();   // Expected to PASS
static void test_2_failure();   // Expected to FAIL
static void test_3_success();   // Shall not be executed
static void test_4_success();   // Shall not be executed


int main() {
    cutl_config(CUTL_FLAG_STOP_AT_FAIL);

    CUTL_BEGIN_TEST();

    CUTL_TEST_FUNCTION(test_1_success);
    CUTL_TEST_FUNCTION(test_2_failure);
    CUTL_TEST_FUNCTION(test_3_success);
    CUTL_TEST_FUNCTION(test_4_success);

    CUTL_END_TEST();

    return cutl_failed();
}


void test_1_success() { ASSERT_EQ_INT(1138, 1138); }
void test_2_failure() { ASSERT_EQ_INT(1138,   66); }
void test_3_success() { ASSERT_EQ_INT(1138, 1138); }
void test_4_success() { ASSERT_EQ_INT(1138, 1138); }
