/**
 * Demonstration of how to use CutL assertions
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
static void test_general_assertions_success();
static void test_typed_assertions_success();
static void test_assertion_failure();



int main() {
    BEGIN_TEST();

    TEST_FUNCTION(test_general_assertions_success);
    TEST_FUNCTION(test_typed_assertions_success);
    TEST_FUNCTION(test_assertion_failure);

    END_TEST();

    return 0;
}


/**
 * Some general assertions that do no consider the variable
 * types.
 */
void test_general_assertions_success() {
    // Check if an expression is true
    ASSERT( 1 == 1 );
    ASSERT( 1 != 2 );

    // Check whether two values are equal or distinct
    ASSERT_EQ(1, 1);
    ASSERT_NEQ(1, 2);

    // Check if a pointer is NULL
    void *null_ptr = NULL;
    void *valid_ptr = &null_ptr;

    ASSERT_NULL(null_ptr);
    ASSERT_NOT_NULL(valid_ptr);
}


/**
 * Some general assertions that do consider the variable types.
 * The values providen to the macro are internally casted to the
 * desired type.
 */
void test_typed_assertions_success() {
    int    i[] = { 100, 200 };
    float  f[] = { 3.14, 2.71 };
    double d[] = { 3.14, 2.71};
    bool   b[] = { true, false };
    char*  str[] = { "Hi", "Bye" };
    void*  ptr[] = { &str[0], &str[1] };

    ASSERT_EQ_INT(    i[0],   i[0]);
    ASSERT_EQ_FLOAT(  f[0],   f[0]);
    ASSERT_EQ_DOUBLE( d[0],   d[0]);
    ASSERT_EQ_BOOL(   b[0],   b[0]);
    ASSERT_EQ_STR(    str[0], str[0]);
    ASSERT_EQ_PTR(    ptr[0], ptr[0]);


    ASSERT_NEQ_INT(    i[0],   i[1]);
    ASSERT_NEQ_FLOAT(  f[0],   f[1]);
    ASSERT_NEQ_DOUBLE( d[0],   d[1]);
    ASSERT_NEQ_BOOL(   b[0],   b[1]);
    ASSERT_NEQ_STR(    str[0], str[1]);
    ASSERT_NEQ_PTR(    ptr[0], ptr[1]);
}



/**
 * When an assertion fails, a failure is reported and the
 * function tested is inmediately ended.
 */
void test_assertion_failure() {
    ASSERT( 1 == 2 );
    ASSERT( 1 == 1 );
}
