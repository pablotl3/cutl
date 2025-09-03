/**
 * Error handling with CutL
 * 
 */
#define CUTL_NO_PREFIXED_ASSERTIONS
#include <cutl.h>


/* Special functions to run before or after the test functions
 * are called */
void CUTL_BEFORE_ALL()  {}
void CUTL_AFTER_ALL()   {}
void CUTL_BEFORE_EACH() {}
void CUTL_AFTER_EACH()  {}


/**
 * Simulates a call to the malloc() function that
 * fails and returns NULL.
 */
static void *failing_malloc() { return NULL; }


/* Tests */
static void test_with_error();
static void test_without_error();


int main() {
    CUTL_BEGIN_TEST();

    CUTL_TEST_FUNCTION(test_with_error);
    CUTL_TEST_FUNCTION(test_without_error);

    CUTL_END_TEST();

    return cutl_failed();
}


void test_with_error() {
    int *numbers = failing_malloc();
    if (numbers == NULL) {
        // Free memory and other resources before calling CUTL_REPORT_ERROR
        CUTL_REPORT_ERROR("Memory allocation error");
    }

    // Never arrives here as CUTL_REPORT_ERROR returns
}

void test_without_error() {
    ASSERT( 33 == 33 );
}
