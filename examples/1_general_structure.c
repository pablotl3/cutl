/**
 * General structure of a test program using CutL
 *
 * Date:    2025-09-03
 * Version: 2.0
 */
#include <cutl.h>


/* Special functions to run before or after the test functions
 * are called */
void CUTL_BEFORE_ALL()  {}
void CUTL_AFTER_ALL()   {}
void CUTL_BEFORE_EACH() {}
void CUTL_AFTER_EACH()  {}


/* Test functions declaration */
static void test_1();
static void test_2();



int main() {
    CUTL_BEGIN_TEST();

    CUTL_TEST_FUNCTION(test_1);
    CUTL_TEST_FUNCTION(test_2);

    CUTL_END_TEST();

    return cutl_failed();
}


/**
 * Test function 1
 */
void test_1() {
    return;
}

/**
 * Test function 2
 */
void test_2() {
    return;
}
