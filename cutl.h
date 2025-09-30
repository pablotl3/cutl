/**
 * Simple framework for tests
 * Author: @pablotl3 (GitHub)
 * Date:   21 november 2024
 * Version: 2.0
 */
#ifndef CUTL_H
#define CUTL_H


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


#define CUTL_VERSION    "3.1.1"


// The following methods MUST be implemented in the test file
// ----------------------------------------------------------

static void CUTL_BEFORE_ALL();  // Executes when BEGIN_TEST is called
static void CUTL_AFTER_ALL();   // Executes when END_TEST is called
static void CUTL_BEFORE_EACH(); // Executes before each test
static void CUTL_AFTER_EACH();  // Executes after each test


// Other CutL functions
// --------------------

static int  cutl_failed();       // Returns the number of failed tests


// CutL macros
// -----------

// macro  CUTL_BEGIN_TEST()
// macro  CUTL_END_TEST()
// macro  CUTL_TEST_FUNCTION(func, ...)

// macro  CUTL_REPORT_ERROR(msg)


// CutL assertions
// ---------------

/* NOTE: By default they come with the CUTL prefix, but it can be
 * removed from the macro names by defining CUTL_NO_PREFIXED_ASSERTIONS
 * before including this header file */

// macro  ASSERT(expr)
// macro  ASSERT_EQ(v1, v2)
// macro  ASSERT_NEQ(v1, v2)
// macro  ASSERT_NULL(v1)
// macro  ASSERT_NOT_NULL(v1)

// macro  ASSERT_EQ_UINT(v1, v2)
// macro  ASSERT_EQ_INT(v1, v2)
// macro  ASSERT_EQ_FLOAT(v1, v2)
// macro  ASSERT_EQ_DOUBLE(v1, v2)
// macro  ASSERT_EQ_BOOL(v1, v2)
// macro  ASSERT_EQ_CHAR(v1, v2)
// macro  ASSERT_EQ_STR(v1, v2)
// macro  ASSERT_EQ_PTR(v1, v2)

// macro  ASSERT_NEQ_UINT(v1, v2)
// macro  ASSERT_NEQ_INT(v1, v2)
// macro  ASSERT_NEQ_FLOAT(v1, v2)
// macro  ASSERT_NEQ_DOUBLE(v1, v2)
// macro  ASSERT_NEQ_BOOL(v1, v2)
// macro  ASSERT_NEQ_CHAR(v1, v2)
// macro  ASSERT_NEQ_STR(v1, v2)
// macro  ASSERT_NEQ_PTR(v1, v2)



// ==========================================================================
// Private globals and constants
// ==========================================================================


// CutL states

#define _CUTL_SUCCESS 0
#define _CUTL_FAILURE 1
#define _CUTL_ERROR   2

// Control of test failures

#define _CUTL_MAX_LEN_FUNC_NAME 128
#define _CUTL_MAX_LEN_MSG       256


static char *_cutl_current_file = NULL;    // Name of the file being tested
static char *_cutl_current_func = NULL;    // Name of the function being tested
static int   _cutl_current_line = -1;      // Line in the file where the function being tested was called

static unsigned int _cutl_n_tests_passed;   // Number of tests passed
static unsigned int _cutl_n_tests_failed;   // Number of tests failed

static int  _cutl_test_status;
static int  _cutl_failure_line;
static char _cutl_failure_msg[_CUTL_MAX_LEN_MSG];

// Logging and report settings
static FILE *_cutl_report_file = NULL;




// ==========================================================================
// Private functions declarations
// ==========================================================================

static void _CUTL_REPORT_SUCCESS(const char *msg, ...);
static void _CUTL_REPORT_FAILURE(const char *msg, ...);
static void _CUTL_REPORT_INFO(const char *msg, ...);
static void _CUTL_REPORT_DEBUG(const char *msg, ...);
static void _CUTL_REPORT_ERROR(const char *msg, ...);


static void _CUTL_REGISTER_TEST_FAILURE(const int line, const char *msg);
static void _CUTL_REGISTER_TEST_ERROR(const int line, const char *msg);

static void _CUTL_REPORT_TEST_RESULT(void);




// ==========================================================================
// REPORTS
// ==========================================================================


#define _CUTL_ANSI_RESET "\033[0m"
#define _CUTL_ANSI_RED   "\033[31m"
#define _CUTL_ANSI_GREEN "\033[32m"
#define _CUTL_ANSI_BLUE  "\033[34m"

#define _CUTL_RGB_SUCCESS _CUTL_ANSI_GREEN
#define _CUTL_RGB_FAILURE _CUTL_ANSI_RED
#define _CUTL_RGB_INFO    _CUTL_ANSI_RESET
#define _CUTL_RGB_DEBUG   _CUTL_ANSI_BLUE
#define _CUTL_RGB_ERROR   _CUTL_ANSI_RED



/**
 * Reports successfull test
 */
void _CUTL_REPORT_SUCCESS(const char *format, ...) {
    va_list args;

    va_start(args, format);

    if (_cutl_report_file == stdout) {
        fprintf(_cutl_report_file, _CUTL_RGB_SUCCESS "====[PASSED]==== ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, _CUTL_ANSI_RESET "\n");
    }
    else {
        fprintf(_cutl_report_file, "====[PASSED]==== ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, "\n");
    }

    va_end(args);
}


/**
 * Reports failed test
 */
void _CUTL_REPORT_FAILURE(const char *format, ...) {
    va_list args;

    va_start(args, format);

    if (_cutl_report_file == stdout) {
        fprintf(_cutl_report_file, _CUTL_RGB_FAILURE "====[FAILED]==== ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, _CUTL_ANSI_RESET "\n");
    }
    else {
        fprintf(_cutl_report_file, "====[FAILED]==== ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, "\n");
    }

    va_end(args);
}


/**
 * Reports some information
 */
void _CUTL_REPORT_INFO(const char *format, ...) {
    va_list args;

    va_start(args, format);

    if (_cutl_report_file == stdout) {
        fprintf(_cutl_report_file, _CUTL_RGB_INFO "=====[INFO]===== ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, _CUTL_ANSI_RESET "\n");
    }
    else {
        fprintf(_cutl_report_file, "=====[INFO]===== ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, "\n");
    }

    va_end(args);
}


/**
 * Reports some debug information
 */
void _CUTL_REPORT_DEBUG(const char *format, ...) {
    va_list args;

    va_start(args, format);

    if (_cutl_report_file == stdout) {
        fprintf(_cutl_report_file, _CUTL_RGB_DEBUG "====[DEBUG]====  ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, _CUTL_ANSI_RESET "\n");
    }
    else {
        fprintf(_cutl_report_file, "====[DEBUG]====  ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, "\n");
    }

    va_end(args);
}


/**
 * Reports an unexpected error (not test failure)
 */
void _CUTL_REPORT_ERROR(const char *format, ...) {
    va_list args;

    va_start(args, format);

    if (_cutl_report_file == stdout) {
        fprintf(_cutl_report_file, _CUTL_RGB_ERROR "====[ERROR]====  ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, _CUTL_ANSI_RESET "\n");
    }
    else {
        fprintf(_cutl_report_file, "====[ERROR]====  ");
        vfprintf(_cutl_report_file, format, args);
        fprintf(_cutl_report_file, "\n");
    }

    va_end(args);
}



// ==========================================================================
// MANAGING TESTS RESULTS
// ==========================================================================


/**
 * Registers a test failure, but does not handle it
 */
void _CUTL_REGISTER_TEST_FAILURE(const int line, const char *msg) {
    _cutl_test_status = _CUTL_FAILURE;
    _cutl_failure_line = line;
    strncpy(_cutl_failure_msg, msg, _CUTL_MAX_LEN_MSG);
}


/**
 * Registers a test error
 */
void _CUTL_REGISTER_TEST_ERROR(const int line, const char *msg) {
    _cutl_test_status = _CUTL_ERROR;
    _cutl_failure_line = line;
    strncpy(_cutl_failure_msg, msg, _CUTL_MAX_LEN_MSG);
}


/**
 * Reports whether if the last test run failed or was successful
 */
void _CUTL_REPORT_TEST_RESULT() {
    switch (_cutl_test_status) {
        case _CUTL_SUCCESS:
            _cutl_n_tests_passed++;
            _CUTL_REPORT_SUCCESS("%s l:%d (%s)",
                _cutl_current_file, _cutl_current_line, _cutl_current_func
            );

            break;

        case _CUTL_FAILURE:
            _cutl_n_tests_failed++;
            _CUTL_REPORT_FAILURE("%s l:%d (%s)\n\tFailure in line %d: %s",
                _cutl_current_file, _cutl_current_line, _cutl_current_func,
                _cutl_failure_line, _cutl_failure_msg
            );

            break;

        case _CUTL_ERROR:
            _cutl_n_tests_failed++;
            _CUTL_REPORT_ERROR("%s l:%d (%s)\n\tError in line %d: %s",
                _cutl_current_file, _cutl_current_line, _cutl_current_func,
                _cutl_failure_line, _cutl_failure_msg
            );

            break;

        default:
            break;
    }
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




// ==========================================================================
// MACROS FOR TESTING
// ==========================================================================


/**
 * Begins the testing mode
 */
#define CUTL_BEGIN_TEST() \
    do { \
        /* Set report file */                   \
        if (_cutl_report_file == NULL) {        \
            _cutl_report_file = stdout;         \
        }                                       \
        else {                                  \
            /* TODO : Change */                 \
            _cutl_report_file = stdout;         \
        }                                       \
                                                \
        /* Begin testing */                     \
        _cutl_current_file = __FILE__;          \
        _cutl_n_tests_passed = 0;               \
        _cutl_n_tests_failed = 0;               \
                                                \
        _CUTL_REPORT_INFO("Testing " __FILE__); \
                                                \
        CUTL_BEFORE_ALL();                      \
    } while (0)



/**
 * Ends the testing mode
 */
#define CUTL_END_TEST() \
    do { \
        CUTL_AFTER_ALL(); \
        _CUTL_REPORT_INFO( \
            "Tests passed: %u / %u (%s)", \
            _cutl_n_tests_passed, \
            _cutl_n_tests_passed + _cutl_n_tests_failed, \
            cutl_failed() ? "ERR" : "OK" \
        ); \
    } while (0)



/**
 * Tests a function and reports its result. The function must not
 * return void, but can receive any amount of params.
 * 
 * If a failure ocurrs while the function is being executed, it will
 * be reported and the executing function will be aborted.
 * 
 * If an error ocurrs while the function is being executed, it will
 * be reported and the program will be aborted.
 */
#define CUTL_TEST_FUNCTION(func, ...) \
    do { \
        _cutl_current_func = #func;         \
        _cutl_current_line = __LINE__;      \
                                            \
        CUTL_BEFORE_EACH();                 \
                                            \
        _cutl_test_status = _CUTL_SUCCESS;  \
                                            \
        func(__VA_ARGS__);                \
                                            \
        _CUTL_REPORT_TEST_RESULT();         \
                                            \
        CUTL_AFTER_EACH();                  \
    } while (0)



/**
 * Returns the number of failed tests
 */
int cutl_failed() {
    return _cutl_n_tests_failed;
}


// ==========================================================================
// ASSERTIONS
// ==========================================================================


// General assertions

#define CUTL_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, "ASSERT( " #expr " )"); \
            return; \
        } \
    } while (0)

#define CUTL_ASSERT_EQ(v1, v2) \
    do { \
        if ((v1) != (v2)) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, "ASSERT_EQ( " #v1 ", " #v2 " )"); \
            return; \
        }  \
    }while (0)

#define CUTL_ASSERT_NEQ(v1, v2) \
    do { \
        if ((v1) == (v2)) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, "ASSERT_NEQ( " #v1 ", " #v2 " )"); \
            return; \
        } \
    } while (0)

#define CUTL_ASSERT_NULL(v1) \
    do { \
        if ((v1) != NULL) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, "ASSERT_NULL( " #v1 " )"); \
            return; \
        } \
    } while (0)

#define CUTL_ASSERT_NOT_NULL(v1) \
    do { \
        if ((v1) == NULL) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, "ASSERT_NOT_NULL( " #v1 " )"); \
            return; \
        } \
    } while (0)



// (Specific type) Assert equal

#define _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, type, macro_name) \
    do { \
        if ( ((type)(v1)) != ((type)(v2)) ) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, macro_name "( " #v1 ", " #v2 " )"); \
            return; \
        } \
    } while (0)



#define CUTL_ASSERT_EQ_UINT(v1, v2) \
    _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, unsigned long long, "ASSERT_EQ_UINT")


#define CUTL_ASSERT_EQ_INT(v1, v2) \
    _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, long long, "ASSERT_EQ_INT")


#define CUTL_ASSERT_EQ_FLOAT(v1, v2) \
    _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, float, "ASSERT_EQ_FLOAT")


#define CUTL_ASSERT_EQ_DOUBLE(v1, v2) \
    _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, double, "ASSERT_EQ_DOUBLE")


#define CUTL_ASSERT_EQ_BOOL(v1, v2) \
    _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, bool, "ASSERT_EQ_BOOL")


#define CUTL_ASSERT_EQ_CHAR(v1, v2) \
    _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, char, "ASSERT_EQ_CHAR")


#define CUTL_ASSERT_EQ_STR(v1, v2) \
    do { \
        if (strcmp(v1, v2) != 0) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, "ASSERT_EQ_STR( " #v1 ", " #v2 " )"); \
            return;\
        } \
    } while (0)


#define CUTL_ASSERT_EQ_PTR(v1, v2) \
    _CUTL_ASSERT_EQ_SPECIFIC_TYPE(v1, v2, void *, "ASSERT_EQ_PTR")



// (Specific type) Assert distinct

#define _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, type, macro_name) \
    do { \
        if ( ((type)(v1)) == ((type)(v2)) ) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, macro_name "( " #v1 ", " #v2 " )"); \
            return; \
        } \
    } while (0)



#define CUTL_ASSERT_NEQ_UINT(v1, v2) \
    _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, unsigned long long, "ASSERT_NEQ_UINT")


#define CUTL_ASSERT_NEQ_INT(v1, v2) \
    _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, long long, "ASSERT_NEQ_INT")


#define CUTL_ASSERT_NEQ_FLOAT(v1, v2) \
    _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, float, "ASSERT_NEQ_FLOAT")


#define CUTL_ASSERT_NEQ_DOUBLE(v1, v2) \
    _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, double, "ASSERT_NEQ_DOUBLE")


#define CUTL_ASSERT_NEQ_BOOL(v1, v2) \
    _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, bool, "ASSERT_NEQ_BOOL")


#define CUTL_ASSERT_NEQ_CHAR(v1, v2) \
    _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, char, "ASSERT_NEQ_CHAR")


#define CUTL_ASSERT_NEQ_STR(v1, v2) \
    do { \
        if (strcmp(v1, v2) == 0) { \
            _CUTL_REGISTER_TEST_FAILURE(__LINE__, "ASSERT_NEQ_STR( " #v1 ", " #v2 " )"); \
            return;\
        } \
    } while (0)


#define CUTL_ASSERT_NEQ_PTR(v1, v2) \
    _CUTL_ASSERT_NEQ_SPECIFIC_TYPE(v1, v2, void *, "ASSERT_NEQ_ptr")




#if defined(CUTL_NO_PREFIXED_ASSERTIONS)

    #define ASSERT(expr)                CUTL_ASSERT(expr)
    #define ASSERT_EQ(v1, v2)           CUTL_ASSERT_EQ(v1, v2)
    #define ASSERT_NEQ(v1, v2)          CUTL_ASSERT_NEQ(v1, v2)
    #define ASSERT_NULL(v1)             CUTL_ASSERT_NULL(v1)
    #define ASSERT_NOT_NULL(v1)         CUTL_ASSERT_NOT_NULL(v1)

    #define ASSERT_EQ_UINT(v1, v2)      CUTL_ASSERT_EQ_UINT(v1, v2)
    #define ASSERT_EQ_INT(v1, v2)       CUTL_ASSERT_EQ_INT(v1, v2)
    #define ASSERT_EQ_FLOAT(v1, v2)     CUTL_ASSERT_EQ_FLOAT(v1, v2)
    #define ASSERT_EQ_DOUBLE(v1, v2)    CUTL_ASSERT_EQ_DOUBLE(v1, v2)
    #define ASSERT_EQ_BOOL(v1, v2)      CUTL_ASSERT_EQ_BOOL(v1, v2)
    #define ASSERT_EQ_CHAR(v1, v2)      CUTL_ASSERT_EQ_CHAR(v1, v2)
    #define ASSERT_EQ_STR(v1, v2)       CUTL_ASSERT_EQ_STR(v1, v2)
    #define ASSERT_EQ_PTR(v1, v2)       CUTL_ASSERT_EQ_PTR(v1, v2)

    #define ASSERT_NEQ_UINT(v1, v2)     CUTL_ASSERT_NEQ_UINT(v1, v2)
    #define ASSERT_NEQ_INT(v1, v2)      CUTL_ASSERT_NEQ_INT(v1, v2)
    #define ASSERT_NEQ_FLOAT(v1, v2)    CUTL_ASSERT_NEQ_FLOAT(v1, v2)
    #define ASSERT_NEQ_DOUBLE(v1, v2)   CUTL_ASSERT_NEQ_DOUBLE(v1, v2)
    #define ASSERT_NEQ_BOOL(v1, v2)     CUTL_ASSERT_NEQ_BOOL(v1, v2)
    #define ASSERT_NEQ_CHAR(v1, v2)     CUTL_ASSERT_NEQ_CHAR(v1, v2)
    #define ASSERT_NEQ_STR(v1, v2)      CUTL_ASSERT_NEQ_STR(v1, v2)
    #define ASSERT_NEQ_PTR(v1, v2)      CUTL_ASSERT_NEQ_PTR(v1, v2)

#endif /* CUTL_NO_PREFIXED_ASSERTIONS */



// ==========================================================================
// ERRORS
// ==========================================================================

#define CUTL_REPORT_ERROR(msg) \
    do { \
        _CUTL_REGISTER_TEST_ERROR(__LINE__, msg); \
        return; \
    } while (0)




#endif /* CUTL_H */
