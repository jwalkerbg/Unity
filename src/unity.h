/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef UNITY_FRAMEWORK_H
#define UNITY_FRAMEWORK_H

#define UNITY

#ifdef __cplusplus
extern "C"
{
#endif

#include "unity_internals.h"

void setUp(void);
void tearDown(void);

//-------------------------------------------------------
// Configuration Options
//-------------------------------------------------------
// All options described below should be passed as a compiler flag to all files using Unity. If you must add #defines, place them BEFORE the #include above.

// Integers/longs/pointers
//     - Unity assumes 32 bit integers, longs, and pointers by default
//     - If your compiler treats ints of a different size, options are:
//       - define UNITY_USE_LIMITS_H to use limits.h to determine sizes
//       - define UNITY_INT_WIDTH, UNITY_LONG_WIDTH, nand UNITY_POINTER_WIDTH

// Floats
//     - define UNITY_INCLUDE_FLOAT to allow floating point comparisons
//     - define UNITY_FLOAT_PRECISION to specify the precision to use when doing TEST_ASSERT_EQUAL_FLOAT
//     - define UNITY_FLOAT_TYPE to specify doubles instead of single precision floats
//     - define UNITY_FLOAT_VERBOSE to print floating point values in errors (uses sprintf)
//     - define UNITY_INCLUDE_DOUBLE to allow double floating point comparisons
//     - define UNITY_DOUBLE_PRECISION to specify the precision to use when doing TEST_ASSERT_EQUAL_DOUBLE
//     - define UNITY_DOUBLE_TYPE to specify something other than double
//     - define UNITY_DOUBLE_VERBOSE to print floating point values in errors (uses sprintf)

// Output
//     - by default, Unity prints to standard out with putchar.  define UNITY_OUTPUT_CHAR(a) with a different function if desired

// Optimization
//     - by default, line numbers are stored in unsigned shorts.  Define UNITY_LINE_TYPE with a different type if your files are huge
//     - by default, test and failure counters are unsigned shorts.  Define UNITY_COUNTER_TYPE with a different type if you want to save space or have more than 65535 Tests.

// Test Cases
//     - define UNITY_SUPPORT_TEST_CASES to include the TEST_CASE macro, though really it's mostly about the runner generator script

// Parameterized Tests
//     - you'll want to create a define of TEST_CASE(...) which basically evaluates to nothing

//-------------------------------------------------------
// Test Running Macros
//-------------------------------------------------------

#define TEST_PROTECT() (UNITY_TRUE)

#define TEST_ABORT() {return 1;}

#ifndef RUN_TEST
#define RUN_TEST(func, line_num) UnityDefaultTestRun((func), #func, (line_num))
#endif

#define TEST_LINE_NUM (Unity.CurrentTestLineNumber)
#define TEST_IS_IGNORED (Unity.CurrentTestIgnored)

//-------------------------------------------------------
// Basic Fail and Ignore
//-------------------------------------------------------

#define TEST_FAIL_MESSAGE(message)                                                                 UNITY_TEST_FAIL(__LINE__, (message))
#define TEST_FAIL()                                                                                UNITY_TEST_FAIL(__LINE__, NULL)
#define TEST_IGNORE_MESSAGE(message)                                                               UNITY_TEST_IGNORE(__LINE__, (message))
#define TEST_IGNORE()                                                                              UNITY_TEST_IGNORE(__LINE__, NULL)
#define TEST_ONLY()

//-------------------------------------------------------
// Test Asserts (simple)
//-------------------------------------------------------

//Boolean
#define TEST_ASSERT(condition)                                                                     UNITY_TEST_ASSERT(       (condition), __LINE__, " Expression Evaluated To FALSE")
#define TEST_ASSERT_TRUE(condition)                                                                UNITY_TEST_ASSERT(       (condition), __LINE__, " Expected TRUE Was FALSE")
#define TEST_ASSERT_UNLESS(condition)                                                              UNITY_TEST_ASSERT(      !(condition), __LINE__, " Expression Evaluated To TRUE")
#define TEST_ASSERT_HIGHSTATE(condition)                                                           UNITY_TEST_ASSERT(       (condition), __LINE__, " Expected \'highstate\' Was \'lowstate\'")
#define TEST_ASSERT_FALSE(condition)                                                               UNITY_TEST_ASSERT(      !(condition), __LINE__, " Expected FALSE Was TRUE")
#define TEST_ASSERT_LOWSTATE(condition)                                                            UNITY_TEST_ASSERT(      !(condition), __LINE__, " Expected \'lowstate\' Was \'highstate\'")
#define TEST_ASSERT_NULL(pointer)                                                                  UNITY_TEST_ASSERT_NULL(    (pointer), __LINE__, " Expected NULL")
#define TEST_ASSERT_NOT_NULL(pointer)                                                              UNITY_TEST_ASSERT_NOT_NULL((pointer), __LINE__, " Expected Non-NULL")

//Integers (of all sizes)
#define TEST_ASSERT_EQUAL_INT(expected, actual)                                                    UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT8(expected, actual)                                                   UNITY_TEST_ASSERT_EQUAL_INT8((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT16(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_INT16((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT32(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_INT32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT64(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_INT64((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL(expected, actual)                                                        UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_NOT_EQUAL(expected, actual)                                                    UNITY_TEST_ASSERT(((expected) !=  (actual)), __LINE__, " Expected Not-Equal")
#define TEST_ASSERT_EQUAL_UINT(expected, actual)                                                   UNITY_TEST_ASSERT_EQUAL_UINT( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT8(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_UINT8( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT16(expected, actual)                                                 UNITY_TEST_ASSERT_EQUAL_UINT16( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT32(expected, actual)                                                 UNITY_TEST_ASSERT_EQUAL_UINT32( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT64(expected, actual)                                                 UNITY_TEST_ASSERT_EQUAL_UINT64( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX(expected, actual)                                                    UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX8(expected, actual)                                                   UNITY_TEST_ASSERT_EQUAL_HEX8( (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX16(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_HEX16((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX32(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX64(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_HEX64((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS(mask, expected, actual)                                                   UNITY_TEST_ASSERT_BITS((mask), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS_HIGH(mask, actual)                                                        UNITY_TEST_ASSERT_BITS((mask), (_UU32)(-1), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS_LOW(mask, actual)                                                         UNITY_TEST_ASSERT_BITS((mask), (_UU32)(0), (actual), __LINE__, NULL)
#define TEST_ASSERT_BIT_HIGH(bit, actual)                                                          UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(-1), (actual), __LINE__, NULL)
#define TEST_ASSERT_BIT_LOW(bit, actual)                                                           UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(0), (actual), __LINE__, NULL)

// Integers signed compares (of all sizes)
#define TEST_ASSERT_GREATER_INT(border,actual)                                                     UNITY_TEST_ASSERT_GREATER_INT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_INT8(border, actual)                                                   UNITY_TEST_ASSERT_GREATER_INT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_INT16(border, actual)                                                  UNITY_TEST_ASSERT_GREATER_INT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_INT32(border, actual)                                                  UNITY_TEST_ASSERT_GREATER_INT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_INT64(border, actual)                                                  UNITY_TEST_ASSERT_GREATER_INT64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_GREATER_OR_EQUAL_INT(border,actual)                                            UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_INT8(border, actual)                                          UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_INT16(border, actual)                                         UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_INT32(border, actual)                                         UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_INT64(border, actual)                                         UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_LESS_OR_EQUAL_INT(border,actual)                                               UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_INT8(border, actual)                                             UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_INT16(border, actual)                                            UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_INT32(border, actual)                                            UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_INT64(border, actual)                                            UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_LESS_INT(border,actual)                                                        UNITY_TEST_ASSERT_LESS_INT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_INT8(border, actual)                                                      UNITY_TEST_ASSERT_LESS_INT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_INT16(border, actual)                                                     UNITY_TEST_ASSERT_LESS_INT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_INT32(border, actual)                                                     UNITY_TEST_ASSERT_LESS_INT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_INT64(border, actual)                                                     UNITY_TEST_ASSERT_LESS_INT64((border), (actual), __LINE__, NULL)

// Integers unsigned compares (of all sizes)
#define TEST_ASSERT_GREATER_UINT(border,actual)                                                    UNITY_TEST_ASSERT_GREATER_UINT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_UINT8(border, actual)                                                  UNITY_TEST_ASSERT_GREATER_UINT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_UINT16(border, actual)                                                 UNITY_TEST_ASSERT_GREATER_UINT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_UINT32(border, actual)                                                 UNITY_TEST_ASSERT_GREATER_UINT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_UINT64(border, actual)                                                 UNITY_TEST_ASSERT_GREATER_UINT64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT(border,actual)                                           UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT8(border, actual)                                         UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT16(border, actual)                                        UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT32(border, actual)                                        UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT64(border, actual)                                        UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_LESS_OR_EQUAL_UINT(border,actual)                                              UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_UINT8(border, actual)                                            UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_UINT16(border, actual)                                           UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_UINT32(border, actual)                                           UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_UINT64(border, actual)                                           UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_LESS_UINT(border,actual)                                                       UNITY_TEST_ASSERT_LESS_UINT((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_UINT8(border, actual)                                                     UNITY_TEST_ASSERT_LESS_UINT8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_UINT16(border, actual)                                                    UNITY_TEST_ASSERT_LESS_UINT16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_UINT32(border, actual)                                                    UNITY_TEST_ASSERT_LESS_UINT32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_UINT64(border, actual)                                                    UNITY_TEST_ASSERT_LESS_UINT64((border), (actual), __LINE__, NULL)

// Integers hexadecimal compares (of all sizes)
#define TEST_ASSERT_GREATER_HEX(border,actual)                                                     UNITY_TEST_ASSERT_GREATER_HEX((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_HEX8(border,actual)                                                    UNITY_TEST_ASSERT_GREATER_HEX8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_HEX16(border,actual)                                                   UNITY_TEST_ASSERT_GREATER_HEX16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_HEX32(border,actual)                                                   UNITY_TEST_ASSERT_GREATER_HEX32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_HEX64(border,actual)                                                   UNITY_TEST_ASSERT_GREATER_HEX64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_GREATER_OR_EQUAL_HEX(border,actual)                                            UNITY_TEST_ASSERT_GREATER_OR_EQUAL_HEX((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_HEX8(border,actual)                                           UNITY_TEST_ASSERT_GREATER_OR_EQUAL_HEX8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_HEX16(border,actual)                                          UNITY_TEST_ASSERT_GREATER_OR_EQUAL_HEX16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_HEX32(border,actual)                                          UNITY_TEST_ASSERT_GREATER_OR_EQUAL_HEX32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_GREATER_OR_EQUAL_HEX64(border,actual)                                          UNITY_TEST_ASSERT_GREATER_OR_EQUAL_HEX64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_LESS_OR_EQUAL_HEX(border,actual)                                               UNITY_TEST_ASSERT_LESS_OR_EQUAL_HEX((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_HEX8(border,actual)                                              UNITY_TEST_ASSERT_LESS_OR_EQUAL_HEX8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_HEX16(border,actual)                                             UNITY_TEST_ASSERT_LESS_OR_EQUAL_HEX16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_HEX32(border,actual)                                             UNITY_TEST_ASSERT_LESS_OR_EQUAL_HEX32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_OR_EQUAL_HEX64(border,actual)                                             UNITY_TEST_ASSERT_LESS_OR_EQUAL_HEX64((border), (actual), __LINE__, NULL)
// ---
#define TEST_ASSERT_LESS_HEX(border,actual)                                                        UNITY_TEST_ASSERT_LESS_HEX((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_HEX8(border,actual)                                                       UNITY_TEST_ASSERT_LESS_HEX8((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_HEX16(border,actual)                                                      UNITY_TEST_ASSERT_LESS_HEX16((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_HEX32(border,actual)                                                      UNITY_TEST_ASSERT_LESS_HEX32((border), (actual), __LINE__, NULL)
#define TEST_ASSERT_LESS_HEX64(border,actual)                                                      UNITY_TEST_ASSERT_LESS_HEX64((border), (actual), __LINE__, NULL)

//Integer Ranges (of all sizes)
#define TEST_ASSERT_INT_WITHIN(delta, expected, actual)                                            UNITY_TEST_ASSERT_INT_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_INT8_WITHIN(delta, expected, actual)                                           UNITY_TEST_ASSERT_INT8_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_INT16_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_INT16_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_INT32_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_INT32_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_INT64_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_INT64_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_UINT_WITHIN(delta, expected, actual)                                           UNITY_TEST_ASSERT_UINT_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_UINT8_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_UINT8_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_UINT16_WITHIN(delta, expected, actual)                                         UNITY_TEST_ASSERT_UINT16_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_UINT32_WITHIN(delta, expected, actual)                                         UNITY_TEST_ASSERT_UINT32_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_UINT64_WITHIN(delta, expected, actual)                                         UNITY_TEST_ASSERT_UINT64_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_HEX_WITHIN(delta, expected, actual)                                            UNITY_TEST_ASSERT_HEX32_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_HEX8_WITHIN(delta, expected, actual)                                           UNITY_TEST_ASSERT_HEX8_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_HEX16_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_HEX16_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_HEX32_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_HEX32_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_HEX64_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_HEX64_WITHIN((delta), (expected), (actual), __LINE__, NULL)

//Structs and Strings
#define TEST_ASSERT_EQUAL_PTR(expected, actual)                                                    UNITY_TEST_ASSERT_EQUAL_PTR((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_STRING(expected, actual)                                                 UNITY_TEST_ASSERT_EQUAL_STRING((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_STRING_LEN(expected, actual, len)                                        UNITY_TEST_ASSERT_EQUAL_STRING_LEN((expected), (actual), (len), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_MEMORY(expected, actual, len)                                            UNITY_TEST_ASSERT_EQUAL_MEMORY((expected), (actual), (len), __LINE__, NULL)

//Arrays
#define TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements)                                UNITY_TEST_ASSERT_EQUAL_INT_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_INT8_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT16_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_INT16_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_INT32_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_INT64_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, actual, num_elements)                             UNITY_TEST_ASSERT_EQUAL_UINT16_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements)                             UNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements)                             UNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX_ARRAY(expected, actual, num_elements)                                UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_PTR_ARRAY(expected, actual, num_elements)                                UNITY_TEST_ASSERT_EQUAL_PTR_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements)                             UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements)                        UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY((expected), (actual), (len), (num_elements), __LINE__, NULL)

//Floating Point (If Enabled)
#define TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual)                                          UNITY_TEST_ASSERT_FLOAT_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_FLOAT(expected, actual)                                                  UNITY_TEST_ASSERT_EQUAL_FLOAT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_INF(actual)                                                           UNITY_TEST_ASSERT_FLOAT_IS_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NEG_INF(actual)                                                       UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NAN(actual)                                                           UNITY_TEST_ASSERT_FLOAT_IS_NAN((actual), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_DETERMINATE(actual)                                                   UNITY_TEST_ASSERT_FLOAT_IS_DETERMINATE((actual), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NOT_INF(actual)                                                       UNITY_TEST_ASSERT_FLOAT_IS_NOT_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NOT_NEG_INF(actual)                                                   UNITY_TEST_ASSERT_FLOAT_IS_NOT_NEG_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NOT_NAN(actual)                                                       UNITY_TEST_ASSERT_FLOAT_IS_NOT_NAN((actual), __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NOT_DETERMINATE(actual)                                               UNITY_TEST_ASSERT_FLOAT_IS_NOT_DETERMINATE((actual), __LINE__, NULL)

//Double (If Enabled)
#define TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual)                                         UNITY_TEST_ASSERT_DOUBLE_WITHIN((delta), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_DOUBLE(expected, actual)                                                 UNITY_TEST_ASSERT_EQUAL_DOUBLE((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements)                             UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY((expected), (actual), (num_elements), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_INF(actual)                                                          UNITY_TEST_ASSERT_DOUBLE_IS_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NEG_INF(actual)                                                      UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NAN(actual)                                                          UNITY_TEST_ASSERT_DOUBLE_IS_NAN((actual), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_DETERMINATE(actual)                                                  UNITY_TEST_ASSERT_DOUBLE_IS_DETERMINATE((actual), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NOT_INF(actual)                                                      UNITY_TEST_ASSERT_DOUBLE_IS_NOT_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NOT_NEG_INF(actual)                                                  UNITY_TEST_ASSERT_DOUBLE_IS_NOT_NEG_INF((actual), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NOT_NAN(actual)                                                      UNITY_TEST_ASSERT_DOUBLE_IS_NOT_NAN((actual), __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NOT_DETERMINATE(actual)                                              UNITY_TEST_ASSERT_DOUBLE_IS_NOT_DETERMINATE((actual), __LINE__, NULL)

//-------------------------------------------------------
// Test Asserts (with additional messages)
//-------------------------------------------------------

//Boolean
#define TEST_ASSERT_MESSAGE(condition, message)                                                    UNITY_TEST_ASSERT(       (condition), __LINE__, (message))
#define TEST_ASSERT_TRUE_MESSAGE(condition, message)                                               UNITY_TEST_ASSERT(       (condition), __LINE__, (message))
#define TEST_ASSERT_HIGHSTATE_MESSAGE(condition, message)                                          UNITY_TEST_ASSERT(       (condition), __LINE__, (message))
#define TEST_ASSERT_UNLESS_MESSAGE(condition, message)                                             UNITY_TEST_ASSERT(      !(condition), __LINE__, (message))
#define TEST_ASSERT_FALSE_MESSAGE(condition, message)                                              UNITY_TEST_ASSERT(      !(condition), __LINE__, (message))
#define TEST_ASSERT_LOWSTATE_MESSAGE(condition, message)                                           UNITY_TEST_ASSERT(      !(condition), __LINE__, (message))
#define TEST_ASSERT_NULL_MESSAGE(pointer, message)                                                 UNITY_TEST_ASSERT_NULL(    (pointer), __LINE__, (message))
#define TEST_ASSERT_NOT_NULL_MESSAGE(pointer, message)                                             UNITY_TEST_ASSERT_NOT_NULL((pointer), __LINE__, (message))

//Integers (of all sizes)
#define TEST_ASSERT_EQUAL_INT_MESSAGE(expected, actual, message)                                   UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT8_MESSAGE(expected, actual, message)                                  UNITY_TEST_ASSERT_EQUAL_INT8((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT16_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_INT16((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT32_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_INT32((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT64_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_INT64((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_MESSAGE(expected, actual, message)                                       UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_NOT_EQUAL_MESSAGE(expected, actual, message)                                   UNITY_TEST_ASSERT(((expected) !=  (actual)), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT_MESSAGE(expected, actual, message)                                  UNITY_TEST_ASSERT_EQUAL_UINT( (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_UINT8( (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT16_MESSAGE(expected, actual, message)                                UNITY_TEST_ASSERT_EQUAL_UINT16( (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected, actual, message)                                UNITY_TEST_ASSERT_EQUAL_UINT32( (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT64_MESSAGE(expected, actual, message)                                UNITY_TEST_ASSERT_EQUAL_UINT64( (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX_MESSAGE(expected, actual, message)                                   UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX8_MESSAGE(expected, actual, message)                                  UNITY_TEST_ASSERT_EQUAL_HEX8( (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX16_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_HEX16((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX64_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_HEX64((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_BITS_MESSAGE(mask, expected, actual, message)                                  UNITY_TEST_ASSERT_BITS((mask), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_BITS_HIGH_MESSAGE(mask, actual, message)                                       UNITY_TEST_ASSERT_BITS((mask), (_UU32)(-1), (actual), __LINE__, (message))
#define TEST_ASSERT_BITS_LOW_MESSAGE(mask, actual, message)                                        UNITY_TEST_ASSERT_BITS((mask), (_UU32)(0), (actual), __LINE__, (message))
#define TEST_ASSERT_BIT_HIGH_MESSAGE(bit, actual, message)                                         UNITY_TEST_ASSERT_BITS(((_UU32)1 << (bit)), (_UU32)(-1), (actual), __LINE__, (message))
#define TEST_ASSERT_BIT_LOW_MESSAGE(bit, actual, message)                                          UNITY_TEST_ASSERT_BITS(((_UU32)1 << (bit)), (_UU32)(0), (actual), __LINE__, (message))

// Signed integers compares (of all sizes)
#define TEST_ASSERT_GREATER_INT_MESSAGE(border,actual, message)                                    UNITY_TEST_ASSERT_GREATER_INT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_INT8_MESSAGE(border, actual, message)                                  UNITY_TEST_ASSERT_GREATER_INT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_INT16_MESSAGE(border, actual, message)                                 UNITY_TEST_ASSERT_GREATER_INT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_INT32_MESSAGE(border, actual, message)                                 UNITY_TEST_ASSERT_GREATER_INT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_INT64_MESSAGE(border, actual, message)                                 UNITY_TEST_ASSERT_GREATER_INT64((border), (actual), __LINE__, (message))
// ---
#define TEST_ASSERT_GREATER_OR_EQUAL_INT_MESSAGE(border,actual, message)                           UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_INT8_MESSAGE(border, actual, message)                         UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_INT16_MESSAGE(border, actual, message)                        UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_INT32_MESSAGE(border, actual, message)                        UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_INT64_MESSAGE(border, actual, message)                        UNITY_TEST_ASSERT_GREATER_OR_EQUAL_INT64((border), (actual), __LINE__, (message))
// ---
#define TEST_ASSERT_LESS_OR_EQUAL_INT_MESSAGE(border,actual, message)                              UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_INT8_MESSAGE(border, actual, message)                            UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_INT16_MESSAGE(border, actual, message)                           UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_INT32_MESSAGE(border, actual, message)                           UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_INT64_MESSAGE(border, actual, message)                           UNITY_TEST_ASSERT_LESS_OR_EQUAL_INT64((border), (actual), __LINE__, (message))
// ---
#define TEST_ASSERT_LESS_INT_MESSAGE(border,actual, message)                                       UNITY_TEST_ASSERT_LESS_INT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_INT8_MESSAGE(border, actual, message)                                     UNITY_TEST_ASSERT_LESS_INT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_INT16_MESSAGE(border, actual, message)                                    UNITY_TEST_ASSERT_LESS_INT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_INT32_MESSAGE(border, actual, message)                                    UNITY_TEST_ASSERT_LESS_INT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_INT64_MESSAGE(border, actual, message)                                    UNITY_TEST_ASSERT_LESS_INT64((border), (actual), __LINE__, (message))

// Unigned integers compares (of all sizes)
#define TEST_ASSERT_GREATER_UINT_MESSAGE(border,actual, message)                                   UNITY_TEST_ASSERT_GREATER_UINT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_UINT8_MESSAGE(border, actual, message)                                 UNITY_TEST_ASSERT_GREATER_UINT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_UINT16_MESSAGE(border, actual, message)                                UNITY_TEST_ASSERT_GREATER_UINT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_UINT32_MESSAGE(border, actual, message)                                UNITY_TEST_ASSERT_GREATER_UINT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_UINT64_MESSAGE(border, actual, message)                                UNITY_TEST_ASSERT_GREATER_UINT64((border), (actual), __LINE__, (message))
// --
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT_MESSAGE(border,actual, message)                          UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT8_MESSAGE(border, actual, message)                        UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT16_MESSAGE(border, actual, message)                       UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT32_MESSAGE(border, actual, message)                       UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_GREATER_OR_EQUAL_UINT64_MESSAGE(border, actual, message)                       UNITY_TEST_ASSERT_GREATER_OR_EQUAL_UINT64((border), (actual), __LINE__, (message))
// ---
#define TEST_ASSERT_LESS_OR_EQUAL_UINT_MESSAGE(border,actual, message)                             UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_UINT8_MESSAGE(border, actual, message)                           UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_UINT16_MESSAGE(border, actual, message)                          UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_UINT32_MESSAGE(border, actual, message)                          UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_OR_EQUAL_UINT64_MESSAGE(border, actual, message)                          UNITY_TEST_ASSERT_LESS_OR_EQUAL_UINT64((border), (actual), __LINE__, (message))
// ---
#define TEST_ASSERT_LESS_UINT_MESSAGE(border,actual, message)                                      UNITY_TEST_ASSERT_LESS_UINT((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_UINT8_MESSAGE(border, actual, message)                                    UNITY_TEST_ASSERT_LESS_UINT8((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_UINT16_MESSAGE(border, actual, message)                                   UNITY_TEST_ASSERT_LESS_UINT16((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_UINT32_MESSAGE(border, actual, message)                                   UNITY_TEST_ASSERT_LESS_UINT32((border), (actual), __LINE__, (message))
#define TEST_ASSERT_LESS_UINT64_MESSAGE(border, actual, message)                                   UNITY_TEST_ASSERT_LESS_UINT64((border), (actual), __LINE__, (message))

//Integer Ranges (of all sizes)
#define TEST_ASSERT_INT_WITHIN_MESSAGE(delta, expected, actual, message)                           UNITY_TEST_ASSERT_INT_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_INT8_WITHIN_MESSAGE(delta, expected, actual, message)                          UNITY_TEST_ASSERT_INT8_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_INT16_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_INT16_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_INT32_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_INT32_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_INT64_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_INT64_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_UINT_WITHIN_MESSAGE(delta, expected, actual, message)                          UNITY_TEST_ASSERT_UINT_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_UINT8_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_UINT8_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_UINT16_WITHIN_MESSAGE(delta, expected, actual, message)                        UNITY_TEST_ASSERT_UINT16_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_UINT32_WITHIN_MESSAGE(delta, expected, actual, message)                        UNITY_TEST_ASSERT_UINT32_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_UINT64_WITHIN_MESSAGE(delta, expected, actual, message)                        UNITY_TEST_ASSERT_UINT64_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_HEX_WITHIN_MESSAGE(delta, expected, actual, message)                           UNITY_TEST_ASSERT_HEX32_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_HEX8_WITHIN_MESSAGE(delta, expected, actual, message)                          UNITY_TEST_ASSERT_HEX8_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_HEX16_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_HEX16_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_HEX32_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_HEX32_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_HEX64_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_HEX64_WITHIN((delta), (expected), (actual), __LINE__, (message))

//Structs and Strings
#define TEST_ASSERT_EQUAL_PTR_MESSAGE(expected, actual, message)                                   UNITY_TEST_ASSERT_EQUAL_PTR((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual, message)                                UNITY_TEST_ASSERT_EQUAL_STRING((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE(expected, actual, len, message)                       UNITY_TEST_ASSERT_EQUAL_STRING_LEN((expected), (actual), (len), __LINE__, (message))
#define TEST_ASSERT_EQUAL_MEMORY_MESSAGE(expected, actual, len, message)                           UNITY_TEST_ASSERT_EQUAL_MEMORY((expected), (actual), (len), __LINE__, (message))

//Arrays
#define TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected, actual, num_elements, message)               UNITY_TEST_ASSERT_EQUAL_INT_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT8_ARRAY_MESSAGE(expected, actual, num_elements, message)              UNITY_TEST_ASSERT_EQUAL_INT8_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_INT16_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_INT32_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_INT64_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_INT64_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(expected, actual, num_elements, message)              UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT16_ARRAY_MESSAGE(expected, actual, num_elements, message)            UNITY_TEST_ASSERT_EQUAL_UINT16_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(expected, actual, num_elements, message)            UNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected, actual, num_elements, message)            UNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX_ARRAY_MESSAGE(expected, actual, num_elements, message)               UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected, actual, num_elements, message)              UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX16_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX32_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_HEX64_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_PTR_ARRAY_MESSAGE(expected, actual, num_elements, message)               UNITY_TEST_ASSERT_EQUAL_PTR_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected, actual, num_elements, message)            UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(expected, actual, len, num_elements, message)       UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY((expected), (actual), (len), (num_elements), __LINE__, (message))

//Floating Point (If Enabled)
#define TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, expected, actual, message)                         UNITY_TEST_ASSERT_FLOAT_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected, actual, message)                                 UNITY_TEST_ASSERT_EQUAL_FLOAT((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(expected, actual, num_elements, message)             UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_INF_MESSAGE(actual, message)                                          UNITY_TEST_ASSERT_FLOAT_IS_INF((actual), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_NEG_INF_MESSAGE(actual, message)                                      UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF((actual), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_NAN_MESSAGE(actual, message)                                          UNITY_TEST_ASSERT_FLOAT_IS_NAN((actual), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_DETERMINATE_MESSAGE(actual, message)                                  UNITY_TEST_ASSERT_FLOAT_IS_DETERMINATE((actual), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_NOT_INF_MESSAGE(actual, message)                                      UNITY_TEST_ASSERT_FLOAT_IS_NOT_INF((actual), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_NOT_NEG_INF_MESSAGE(actual, message)                                  UNITY_TEST_ASSERT_FLOAT_IS_NOT_NEG_INF((actual), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_NOT_NAN_MESSAGE(actual, message)                                      UNITY_TEST_ASSERT_FLOAT_IS_NOT_NAN((actual), __LINE__, (message))
#define TEST_ASSERT_FLOAT_IS_NOT_DETERMINATE_MESSAGE(actual, message)                              UNITY_TEST_ASSERT_FLOAT_IS_NOT_DETERMINATE((actual), __LINE__, (message))

//Double (If Enabled)
#define TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(delta, expected, actual, message)                        UNITY_TEST_ASSERT_DOUBLE_WITHIN((delta), (expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected, actual, message)                                UNITY_TEST_ASSERT_EQUAL_DOUBLE((expected), (actual), __LINE__, (message))
#define TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, actual, num_elements, message)            UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY((expected), (actual), (num_elements), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_INF_MESSAGE(actual, message)                                         UNITY_TEST_ASSERT_DOUBLE_IS_INF((actual), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_NEG_INF_MESSAGE(actual, message)                                     UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF((actual), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_NAN_MESSAGE(actual, message)                                         UNITY_TEST_ASSERT_DOUBLE_IS_NAN((actual), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_DETERMINATE_MESSAGE(actual, message)                                 UNITY_TEST_ASSERT_DOUBLE_IS_DETERMINATE((actual), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_NOT_INF_MESSAGE(actual, message)                                     UNITY_TEST_ASSERT_DOUBLE_IS_NOT_INF((actual), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_NOT_NEG_INF_MESSAGE(actual, message)                                 UNITY_TEST_ASSERT_DOUBLE_IS_NOT_NEG_INF((actual), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_NOT_NAN_MESSAGE(actual, message)                                     UNITY_TEST_ASSERT_DOUBLE_IS_NOT_NAN((actual), __LINE__, (message))
#define TEST_ASSERT_DOUBLE_IS_NOT_DETERMINATE_MESSAGE(actual, message)                             UNITY_TEST_ASSERT_DOUBLE_IS_NOT_DETERMINATE((actual), __LINE__, (message))

//end of UNITY_FRAMEWORK_H
#ifdef __cplusplus
}
#endif
#endif
