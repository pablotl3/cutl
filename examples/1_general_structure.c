/**
 * General structure of a test program using CutL
 *
 * Date:    2025-09-02
 * Version: 1.0
 */
#define TEST_IMPLEMENTATION
#include <cutl.h>


/* Special functions to run before or after the test functions
 * are called */
void before_all() {}
void after_all() {}
void before_each() {}
void after_each() {}


/* Test functions declaration */
static void test_1();
static void test_2();



int main() {
    BEGIN_TEST();

    TEST_FUNCTION(test_1);
    TEST_FUNCTION(test_2);

    END_TEST();

    return 0;
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
