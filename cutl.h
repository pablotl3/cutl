/**
 * Simple framework for tests
 * Author: pablotl3
 * Date:   21 november 2024
 * Version: 2.0
 */
#ifndef TESTS_H
#define TESTS_H

#if defined (TEST_IMPLEMENTATION)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define ANSI_RESET "\033[0m"
#define ANSI_RED   "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_BLUE  "\033[34m"

#define RGB_SUCCESS ANSI_GREEN
#define RGB_FAILURE ANSI_RED
#define RGB_INFO    ANSI_RESET
#define RGB_DEBUG   ANSI_BLUE
#define RGB_ERROR   ANSI_RED


// Methods that must be implemented in the test file

static void before_all();
static void after_all();
static void before_each();
static void after_each();


#define _MAX_LEN_FUNC 128
#define _MAX_LEN_MSG  256

static unsigned int _count_passed;
static unsigned int _count_failed;

static bool _test_passed;
static char _failed_func[_MAX_LEN_FUNC];
static int  _failed_line;
static char _failure_msg[_MAX_LEN_MSG];


// ==========================================================================
// PRINT MACROS
// ==========================================================================

/**
 * Prints success message in green ending with new line
 */
#define _SUCCESS(msg, ...) \
    printf(RGB_SUCCESS "====[PASSED]==== " msg ANSI_RESET "\n", ##__VA_ARGS__)


/**
 * Prints failure message in red ending with new line
 */
#define _FAILURE(msg, ...) \
    printf(RGB_FAILURE "====[FAILED]==== " msg ANSI_RESET "\n", ##__VA_ARGS__)


/**
 * Prints a debug message in blue ending with new line
 */
#define _INFO(msg, ...) \
    printf(RGB_INFO "=====[INFO]===== " msg ANSI_RESET "\n", ##__VA_ARGS__)


/**
 * Prints a debug message in blue ending with new line
 */
#define _DEBUG(msg, ...) \
    printf(RGB_DEBUG "====[DEBUG]====  " msg ANSI_RESET "\n", ##__VA_ARGS__)


/**
 * Prints a debug message in blue ending with new line
 */
#define _ERROR(msg, ...) \
    printf(RGB_ERROR "====[ERROR]====  " msg ANSI_RESET "\n", ##__VA_ARGS__)



// ==========================================================================
// LIBRARY UTILS
// ==========================================================================

void _REGISTER_FAILURE(const char *func, const int line, const char *msg)
{
    _test_passed = false;
    strncpy(_failed_func, func, _MAX_LEN_FUNC);
    strncpy(_failure_msg, msg, _MAX_LEN_MSG);
    _failed_line = line;
}


// Setup errors

#define _REPORT_GLOB_SETUP_ERROR(file, line, func, msg, ...) \
    do { \
        _ERROR("%s l:%d (%s)\n\tError during global setup: " msg, file, line, func, ##__VA_ARGS__); \
        abort(); \
    } while (0)


#define _REPORT_FUNC_SETUP_ERROR(file, line, func, msg, ...) \
    do { \
        _ERROR("%s l:%d (%s)\n\tError during funtion setup: " msg, file, line, func, ##__VA_ARGS__); \
        abort(); \
    } while (0)


// Test results

void _REPORT_TEST_RESULT(const char *file, const int line, const char *func)
{
    if (_test_passed)
    {
        _count_passed++;
        _SUCCESS("%s l:%d (%s)", file, line, func);
    }
    else
    {
        _count_failed++;
        _FAILURE("%s l:%d (%s)\n\tError in line %d: %s", file, line, func, _failed_line, _failure_msg);
    }
}



// ==========================================================================
// MACROS FOR TESTING
// ==========================================================================

#define BEGIN_TEST() \
    _count_passed = 0; \
    _count_failed = 0; \
    printf("\n"); \
    _INFO("Testing %s", __FILE__); \
    before_all()

#define END_TEST() \
    after_all(); \
    _INFO("Tests passed: %u / %u", _count_passed, _count_passed + _count_failed)


#define TEST_FUNCTION(func, ...) \
    do { \
        const char *__file = __FILE__; int __line = __LINE__; \
        before_each(); \
        _test_passed = true; \
        func(##__VA_ARGS__); \
        _REPORT_TEST_RESULT(__file, __line, #func); \
        after_each(); \
    } while (0)



// ==========================================================================
// ASSERTIONS
// ==========================================================================

#define TEST_BOOL   "%d"
#define TEST_DOUBLE "%lf"
#define TEST_FLOAT  "%f"
#define TEST_INT8   "%d"
#define TEST_INT16  "%d"
#define TEST_INT32  "%d"
#define TEST_INT64  "%ld"
#define TEST_UINT8  "%u"
#define TEST_UINT16 "%u"
#define TEST_UINT32 "%u"
#define TEST_UINT64 "%lu"


// Setup

#define GLOB_SETUP_ASSERT(expr, msg, ...) \
    if (!(expr)) _REPORT_GLOB_SETUP_ERROR(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)

#define FUNC_SETUP_ASSERT(expr, msg, ...) \
    if (!(expr)) _REPORT_FUNC_SETUP_ERROR(__FILE__, __LINE__, __func__, msg, ##__VA_ARGS__)



// Tests

#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            _REGISTER_FAILURE(__func__, __LINE__, "Expression " #expr " is false"); \
            return; \
        } \
    } while (0)

#define ASSERT_EQ(v1, v2) \
    do { \
        if (v1 != v2) { \
            _REGISTER_FAILURE(__func__, __LINE__, "Expected " #v1 " == " #v2 " but they are different"); \
            return; \
        }  \
    }while (0)

#define ASSERT_NEQ(v1, v2) \
    do { \
        if (v1 == v2) { \
            _REGISTER_FAILURE(__func__, __LINE__, "Expected " #v2 " != " #v2 " but they are equal"); \
            return; \
        } \
    } while (0)

#define ASSERT_NULL(v1) \
    do { \
        if (v1 != NULL) { \
            _REGISTER_FAILURE(__func__, __LINE__, "Expected " #v1 " to be NULL"); \
            return; \
        } \
    } while (0)

#define ASSERT_NOT_NULL(v1) \
    do { \
        if (v1 == NULL) { \
            _REGISTER_FAILURE(__func__, __LINE__, "Expected " #v1 " to be not NULL"); \
            return; \
        } \
    } while (0)



#define ASSERT_EQ_INT(v1, v2) \
    ASSERT_EQ(v1, v2)

#define ASSERT_EQ_FLOAT(v1, v2) \
    ASSERT_EQ(v1, v2)

#define ASSERT_EQ_DOUBLE(v1, v2) \
    ASSERT_EQ(v1, v2)

#define ASSERT_EQ_BOOL(v1, v2) \
    ASSERT_EQ(v1, v2)

#define ASSERT_EQ_STR(v1, v2) \
    do { \
        if (strcmp(v1, v2)) { \
            _REGISTER_FAILURE(__func__, __LINE__, "Expected " #v1 " == " #v2 " but they are different"); \
            return;\
        } \
    } while (0)

#define ASSERT_EQ_PTR(v1, v2) \
    ASSERT_EQ(v1, v2)



#define ASSERT_NEQ_INT(v1, v2) \
    ASSERT_NEQ(v1, v2)

#define ASSERT_NEQ_FLOAT(v1, v2) \
    ASSERT_NEQ(v1, v2)

#define ASSERT_NEQ_DOUBLE(v1, v2) \
    ASSERT_NEQ(v1, v2)

#define ASSERT_NEQ_BOOL(v1, v2) \
    ASSERT_NEQ(v1, v2)

#define ASSERT_NEQ_STR(v1, v2) \
    do { \
        if (!strcmp(v1, v2)) { \
            _REGISTER_FAILURE(__func__, __LINE__, "Expected " #v1 " == " #v2 " but they are different"); \
            return; \
        } \
    } while (0)

#define ASSERT_NEQ_PTR(v1, v2) \
    ASSERT_NEQ(v1, v2)


// ==========================================================================
// MORE
// ==========================================================================

#define REPORT_ERROR(msg, ...) \
    _ERROR("%s l:%d (%s): " msg, __FILE__, __LINE__, __func__, ##__VA_ARGS__)



#endif /* TEST_IMPLEMENTATION */

#endif /* TESTS_H */
