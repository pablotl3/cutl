/**
 * Demonstration of how to use the functions that execute
 * before/after each test function and before/after the
 * test
 * 
 * Date:    2025-09-03
 * Version: 1.0
 */
#include <stdio.h>
#define CUTL_NO_PREFIXED_ASSERTIONS
#include <cutl.h>


/* Special functions to run before or after the test functions
 * are called */
void CUTL_BEFORE_ALL()  { printf("Inside CUTL_BEFORE_ALL\n");  }
void CUTL_AFTER_ALL()   { printf("Inside CUTL_AFTER_ALL\n");   }
void CUTL_BEFORE_EACH() { printf("Inside CUTL_BEFORE_EACH\n"); }
void CUTL_AFTER_EACH()  { printf("Inside CUTL_AFTER_EACH\n");  }


static void test_1() { return; }
static void test_2() { return; }
static void test_3() { return; }


int main() {
    CUTL_BEGIN_TEST();

    CUTL_TEST_FUNCTION(test_1);
    CUTL_TEST_FUNCTION(test_2);
    CUTL_TEST_FUNCTION(test_3);

    CUTL_END_TEST();

    return cutl_failed();
}
