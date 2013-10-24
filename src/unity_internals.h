/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef UNITY_INTERNALS_H
#define UNITY_INTERNALS_H

#include <stdio.h>

// Unity attempts to determine sizeof(various types)
// based on UINT_MAX, ULONG_MAX, etc. These are typically
// defined in limits.h.
#ifdef UNITY_USE_LIMITS_H
#include <limits.h>
#endif
// As a fallback, hope that including stdint.h will
// provide this information.
#ifndef UNITY_EXCLUDE_STDINT_H
#include <stdint.h>
#endif

//-------------------------------------------------------
// Guess Widths If Not Specified
//-------------------------------------------------------

// Determine the size of an int, if not already specificied.
// We cannot use sizeof(int), because it is not yet defined
// at this stage in the trnslation of the C program.
// Therefore, infer it from UINT_MAX if possible.
#ifndef UNITY_INT_WIDTH
  #ifdef UINT_MAX
    #if (UINT_MAX == 0xFFFF)
      #define UNITY_INT_WIDTH (16)
    #elif (UINT_MAX == 0xFFFFFFFF)
      #define UNITY_INT_WIDTH (32)
    #elif (UINT_MAX == 0xFFFFFFFFFFFFFFFF)
      #define UNITY_INT_WIDTH (64)
      #ifndef UNITY_SUPPORT_64
      #define UNITY_SUPPORT_64
      #endif
    #endif
  #endif
#endif
#ifndef UNITY_INT_WIDTH
  #define UNITY_INT_WIDTH (32)
#endif

// Determine the size of a long, if not already specified,
// by following the process used above to define
// UNITY_INT_WIDTH.
#ifndef UNITY_LONG_WIDTH
  #ifdef ULONG_MAX
    #if (ULONG_MAX == 0xFFFF)
      #define UNITY_LONG_WIDTH (16)
    #elif (ULONG_MAX == 0xFFFFFFFF)
      #define UNITY_LONG_WIDTH (32)
    #elif (ULONG_MAX == 0xFFFFFFFFFFFFFFFF)
      #define UNITY_LONG_WIDTH (64)
      #ifndef UNITY_SUPPORT_64
      #define UNITY_SUPPORT_64
      #endif
    #endif
  #endif
#endif
#ifndef UNITY_LONG_WIDTH
  #define UNITY_LONG_WIDTH (32)
#endif

// Determine the size of a pointer, if not already specified,
// by following the process used above to define
// UNITY_INT_WIDTH.
#ifndef UNITY_POINTER_WIDTH
  #ifdef UINTPTR_MAX
    #if (UINTPTR_MAX <= 0xFFFF)
      #define UNITY_POINTER_WIDTH (16)
    #elif (UINTPTR_MAX <= 0xFFFFFFFF)
      #define UNITY_POINTER_WIDTH (32)
    #elif (UINTPTR_MAX <= 0xFFFFFFFFFFFFFFFF)
      #define UNITY_POINTER_WIDTH (64)
      #ifndef UNITY_SUPPORT_64
      #define UNITY_SUPPORT_64
      #endif
    #endif
  #endif
#endif
#ifndef UNITY_POINTER_WIDTH
  #ifdef INTPTR_MAX
    #if (INTPTR_MAX <= 0x7FFF)
      #define UNITY_POINTER_WIDTH (16)
    #elif (INTPTR_MAX <= 0x7FFFFFFF)
      #define UNITY_POINTER_WIDTH (32)
    #elif (INTPTR_MAX <= 0x7FFFFFFFFFFFFFFF)
      #define UNITY_POINTER_WIDTH (64)
      #ifndef UNITY_SUPPORT_64
      #define UNITY_SUPPORT_64
      #endif
    #endif
  #endif
#endif
#ifndef UNITY_POINTER_WIDTH
  #define UNITY_POINTER_WIDTH (32)
#endif

//-------------------------------------------------------
// Int Support
//-------------------------------------------------------

#if (UNITY_INT_WIDTH == 32)
    typedef unsigned char   _UU8;
    typedef unsigned short  _UU16;
    typedef unsigned int    _UU32;
    typedef signed char     _US8;
    typedef signed short    _US16;
    typedef signed int      _US32;
#elif (UNITY_INT_WIDTH == 16)
    typedef unsigned char   _UU8;
    typedef unsigned int    _UU16;
    typedef unsigned long   _UU32;
    typedef signed char     _US8;
    typedef signed int      _US16;
    typedef signed long     _US32;
#else
    #error Invalid UNITY_INT_WIDTH specified! (16 or 32 are supported)
#endif

//-------------------------------------------------------
// 64-bit Support
//-------------------------------------------------------

#ifndef UNITY_SUPPORT_64

//No 64-bit Support
typedef _UU32 _U_UINT;
typedef _US32 _U_SINT;

#else

//64-bit Support
#if (UNITY_LONG_WIDTH == 32)
    typedef unsigned long long _UU64;
    typedef signed long long   _US64;
#elif (UNITY_LONG_WIDTH == 64)
    typedef unsigned long      _UU64;
    typedef signed long        _US64;
#else
    #error Invalid UNITY_LONG_WIDTH specified! (32 or 64 are supported)
#endif
typedef _UU64 _U_UINT;
typedef _US64 _U_SINT;

#endif

//-------------------------------------------------------
// Pointer Support
//-------------------------------------------------------

#if (UNITY_POINTER_WIDTH == 32)
    typedef _UU32 _UP;
#define UNITY_DISPLAY_STYLE_POINTER UNITY_DISPLAY_STYLE_HEX32
#elif (UNITY_POINTER_WIDTH == 64)
#ifndef UNITY_SUPPORT_64
#error "You've Specified 64-bit pointers without enabling 64-bit Support. Define UNITY_SUPPORT_64"
#endif
    typedef _UU64 _UP;
#define UNITY_DISPLAY_STYLE_POINTER UNITY_DISPLAY_STYLE_HEX64
#elif (UNITY_POINTER_WIDTH == 16)
    typedef _UU16 _UP;
#define UNITY_DISPLAY_STYLE_POINTER UNITY_DISPLAY_STYLE_HEX16
#else
    #error Invalid UNITY_POINTER_WIDTH specified! (16, 32 or 64 are supported)
#endif

#ifndef UNITY_PTR_ATTRIBUTE
  #define UNITY_PTR_ATTRIBUTE
#endif

//-------------------------------------------------------
// Float Support
//-------------------------------------------------------

#ifdef UNITY_EXCLUDE_FLOAT

//No Floating Point Support
#undef UNITY_FLOAT_PRECISION
#undef UNITY_FLOAT_TYPE
#undef UNITY_FLOAT_VERBOSE

#else

//Floating Point Support
#ifndef UNITY_FLOAT_PRECISION
#define UNITY_FLOAT_PRECISION (0.00001f)
#endif
#ifndef UNITY_FLOAT_TYPE
#define UNITY_FLOAT_TYPE float
#endif
typedef UNITY_FLOAT_TYPE _UF;

#endif

//-------------------------------------------------------
// Double Float Support
//-------------------------------------------------------

//unlike FLOAT, we DON'T include by default
#ifndef UNITY_EXCLUDE_DOUBLE
#ifndef UNITY_INCLUDE_DOUBLE
#define UNITY_EXCLUDE_DOUBLE
#endif
#endif

#ifdef UNITY_EXCLUDE_DOUBLE

//No Floating Point Support
#undef UNITY_DOUBLE_PRECISION
#undef UNITY_DOUBLE_TYPE
#undef UNITY_DOUBLE_VERBOSE

#else

//Floating Point Support
#ifndef UNITY_DOUBLE_PRECISION
#define UNITY_DOUBLE_PRECISION (1e-12f)
#endif
#ifndef UNITY_DOUBLE_TYPE
#define UNITY_DOUBLE_TYPE double
#endif
typedef UNITY_DOUBLE_TYPE _UD;

#endif

//-------------------------------------------------------
// Output Method
//-------------------------------------------------------

#ifndef UNITY_OUTPUT_CHAR
//Default to using putchar, which is defined in stdio.h above
#define UNITY_OUTPUT_CHAR(a) putchar(a)
#else
//If defined as something else, make sure we declare it here so it's ready for use
extern int UNITY_OUTPUT_CHAR(int);
#endif

//-------------------------------------------------------
// Footprint
//-------------------------------------------------------

#ifndef UNITY_LINE_TYPE
#define UNITY_LINE_TYPE _U_UINT
#endif

#ifndef UNITY_COUNTER_TYPE
#define UNITY_COUNTER_TYPE _U_UINT
#endif

//-------------------------------------------------------
// Internal Structs Needed
//-------------------------------------------------------

typedef void (*UnityTestFunction)(void);

#define UNITY_DISPLAY_RANGE_INT  (0x10)
#define UNITY_DISPLAY_RANGE_UINT (0x20)
#define UNITY_DISPLAY_RANGE_HEX  (0x40)
#define UNITY_DISPLAY_RANGE_AUTO (0x80)

typedef enum
{
#if (UNITY_INT_WIDTH == 16)
    UNITY_DISPLAY_STYLE_INT      = 2 + UNITY_DISPLAY_RANGE_INT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH  == 32)
    UNITY_DISPLAY_STYLE_INT      = 4 + UNITY_DISPLAY_RANGE_INT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH  == 64)
    UNITY_DISPLAY_STYLE_INT      = 8 + UNITY_DISPLAY_RANGE_INT + UNITY_DISPLAY_RANGE_AUTO,
#endif
    UNITY_DISPLAY_STYLE_INT8     = 1 + UNITY_DISPLAY_RANGE_INT,
    UNITY_DISPLAY_STYLE_INT16    = 2 + UNITY_DISPLAY_RANGE_INT,
    UNITY_DISPLAY_STYLE_INT32    = 4 + UNITY_DISPLAY_RANGE_INT,
#ifdef UNITY_SUPPORT_64
    UNITY_DISPLAY_STYLE_INT64    = 8 + UNITY_DISPLAY_RANGE_INT,
#endif

#if (UNITY_INT_WIDTH == 16)
    UNITY_DISPLAY_STYLE_UINT     = 2 + UNITY_DISPLAY_RANGE_UINT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH  == 32)
    UNITY_DISPLAY_STYLE_UINT     = 4 + UNITY_DISPLAY_RANGE_UINT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH  == 64)
    UNITY_DISPLAY_STYLE_UINT     = 8 + UNITY_DISPLAY_RANGE_UINT + UNITY_DISPLAY_RANGE_AUTO,
#endif
    UNITY_DISPLAY_STYLE_UINT8    = 1 + UNITY_DISPLAY_RANGE_UINT,
    UNITY_DISPLAY_STYLE_UINT16   = 2 + UNITY_DISPLAY_RANGE_UINT,
    UNITY_DISPLAY_STYLE_UINT32   = 4 + UNITY_DISPLAY_RANGE_UINT,
#ifdef UNITY_SUPPORT_64
    UNITY_DISPLAY_STYLE_UINT64   = 8 + UNITY_DISPLAY_RANGE_UINT,
#endif
    UNITY_DISPLAY_STYLE_HEX8     = 1 + UNITY_DISPLAY_RANGE_HEX,
    UNITY_DISPLAY_STYLE_HEX16    = 2 + UNITY_DISPLAY_RANGE_HEX,
    UNITY_DISPLAY_STYLE_HEX32    = 4 + UNITY_DISPLAY_RANGE_HEX,
#ifdef UNITY_SUPPORT_64
    UNITY_DISPLAY_STYLE_HEX64    = 8 + UNITY_DISPLAY_RANGE_HEX,
#endif
    UNITY_DISPLAY_STYLE_UNKNOWN
} UNITY_DISPLAY_STYLE_T;

typedef unsigned char UNITY_BOOL;
#define UNITY_TRUE (!0)
#define UNITY_FALSE (0)

typedef void (*unity_void_fn)(void);

struct _Unity
{
    const char* TestFile;
    const char* CurrentTestName;
    unity_void_fn setUp;
    unity_void_fn tearDown;
    UNITY_LINE_TYPE CurrentTestLineNumber;
    UNITY_COUNTER_TYPE NumberOfTests;
    UNITY_COUNTER_TYPE TestFailures;
    UNITY_COUNTER_TYPE TestIgnores;
    UNITY_COUNTER_TYPE CurrentTestFailed;
    UNITY_COUNTER_TYPE CurrentTestIgnored;
};

extern struct _Unity Unity;

//-------------------------------------------------------
// Test Suite Management
//-------------------------------------------------------

void UnityBegin(unity_void_fn up, unity_void_fn down);
int  UnityEnd(void);
void UnityConcludeTest(void);
void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum);

//-------------------------------------------------------
// Test Output
//-------------------------------------------------------

void UnityPrint(const char* string);
void UnityPrintMask(const _U_UINT mask, const _U_UINT number);
void UnityPrintNumberByStyle(const _U_SINT number, const UNITY_DISPLAY_STYLE_T style);
void UnityPrintNumber(const _U_SINT number);
void UnityPrintNumberUnsigned(const _U_UINT number);
void UnityPrintNumberHex(const _U_UINT number, const char nibbles);

#ifdef UNITY_FLOAT_VERBOSE
void UnityPrintFloat(const _UF number);
#endif

//-------------------------------------------------------
// Test Assertion Fuctions
//-------------------------------------------------------
//  Use the macros below this section instead of calling
//  these directly. The macros have a consistent naming
//  convention and will pull in file and line information
//  for you.

UNITY_BOOL UnityAssertEqualNumber(const _U_SINT expected,
                            const _U_SINT actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber,
                            const UNITY_DISPLAY_STYLE_T style);

UNITY_BOOL UnityAssertEqualIntArray(UNITY_PTR_ATTRIBUTE const void* expected,
                              UNITY_PTR_ATTRIBUTE const void* actual,
                              const _UU32 num_elements,
                              const char* msg,
                              const UNITY_LINE_TYPE lineNumber,
                              const UNITY_DISPLAY_STYLE_T style);

UNITY_BOOL UnityAssertBits(const _U_SINT mask,
                     const _U_SINT expected,
                     const _U_SINT actual,
                     const char* msg,
                     const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertEqualString(const char* expected,
                            const char* actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertEqualStringArray( const char** expected,
                                  const char** actual,
                                  const _UU32 num_elements,
                                  const char* msg,
                                  const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertEqualMemory( UNITY_PTR_ATTRIBUTE const void* expected,
                             UNITY_PTR_ATTRIBUTE const void* actual,
                             const _UU32 length,
                             const _UU32 num_elements,
                             const char* msg,
                             const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertNumbersWithin(const _U_SINT delta,
                              const _U_SINT expected,
                              const _U_SINT actual,
                              const char* msg,
                              const UNITY_LINE_TYPE lineNumber,
                              const UNITY_DISPLAY_STYLE_T style);

UNITY_BOOL UnityFail(const char* message, const UNITY_LINE_TYPE line);

UNITY_BOOL UnityIgnore(const char* message, const UNITY_LINE_TYPE line);

#ifndef UNITY_EXCLUDE_FLOAT
UNITY_BOOL UnityAssertFloatsWithin(const _UF delta,
                             const _UF expected,
                             const _UF actual,
                             const char* msg,
                             const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertEqualFloatArray(UNITY_PTR_ATTRIBUTE const _UF* expected,
                                UNITY_PTR_ATTRIBUTE const _UF* actual,
                                const _UU32 num_elements,
                                const char* msg,
                                const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertFloatIsInf(const _UF actual,
                           const char* msg,
                           const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertFloatIsNegInf(const _UF actual,
                              const char* msg,
                              const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertFloatIsNaN(const _UF actual,
                           const char* msg,
                           const UNITY_LINE_TYPE lineNumber);
#endif

#ifndef UNITY_EXCLUDE_DOUBLE
UNITY_BOOL UnityAssertDoublesWithin(const _UD delta,
                              const _UD expected,
                              const _UD actual,
                              const char* msg,
                              const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertEqualDoubleArray(UNITY_PTR_ATTRIBUTE const _UD* expected,
                                 UNITY_PTR_ATTRIBUTE const _UD* actual,
                                 const _UU32 num_elements,
                                 const char* msg,
                                 const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertDoubleIsInf(const _UD actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertDoubleIsNegInf(const _UD actual,
                               const char* msg,
                               const UNITY_LINE_TYPE lineNumber);

UNITY_BOOL UnityAssertDoubleIsNaN(const _UD actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber);
#endif

//-------------------------------------------------------
// Basic Fail and Ignore
//-------------------------------------------------------

#define UNITY_TEST_FAIL(line, message)   { UnityFail(   (message), (UNITY_LINE_TYPE)line); return; }
#define UNITY_TEST_IGNORE(line, message) { UnityIgnore( (message), (UNITY_LINE_TYPE)line); return; }

//-------------------------------------------------------
// Test Asserts
//-------------------------------------------------------

#define UNITY_TEST_ASSERT(condition, line, message)                                              if (condition) {} else {UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, message);}
#define UNITY_TEST_ASSERT_NULL(pointer, line, message)                                           UNITY_TEST_ASSERT(((pointer) == NULL),  (UNITY_LINE_TYPE)line, message)
#define UNITY_TEST_ASSERT_NOT_NULL(pointer, line, message)                                       UNITY_TEST_ASSERT(((pointer) != NULL),  (UNITY_LINE_TYPE)line, message)

#define UNITY_TEST_ASSERT_EQUAL_INT(expected, actual, line, message)                             if (UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_INT8(expected, actual, line, message)                            if (UnityAssertEqualNumber((_U_SINT)(_US8 )(expected), (_U_SINT)(_US8 )(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_INT16(expected, actual, line, message)                           if (UnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_INT32(expected, actual, line, message)                           if (UnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT(expected, actual, line, message)                            if (UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT8(expected, actual, line, message)                           if (UnityAssertEqualNumber((_U_SINT)(_US8 )(expected), (_U_SINT)(_US8 )(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT16(expected, actual, line, message)                          if (UnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT32(expected, actual, line, message)                          if (UnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX8(expected, actual, line, message)                            if (UnityAssertEqualNumber((_U_SINT)(_US8 )(expected), (_U_SINT)(_US8 )(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX8) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX16(expected, actual, line, message)                           if (UnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX16) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX32(expected, actual, line, message)                           if (UnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX32) != 0) return;
#define UNITY_TEST_ASSERT_BITS(mask, expected, actual, line, message)                            if (UnityAssertBits((_U_SINT)(mask), (_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;

#define UNITY_TEST_ASSERT_INT_WITHIN(delta, expected, actual, line, message)                     if (UnityAssertNumbersWithin((_U_SINT)(delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT) != 0) return;
#define UNITY_TEST_ASSERT_UINT_WITHIN(delta, expected, actual, line, message)                    if (UnityAssertNumbersWithin((_U_SINT)(delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT) != 0) return;
#define UNITY_TEST_ASSERT_HEX8_WITHIN(delta, expected, actual, line, message)                    if (UnityAssertNumbersWithin((_U_SINT)(_U_UINT)(_UU8 )(delta), (_U_SINT)(_U_UINT)(_UU8 )(expected), (_U_SINT)(_U_UINT)(_UU8 )(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX8) != 0) return;
#define UNITY_TEST_ASSERT_HEX16_WITHIN(delta, expected, actual, line, message)                   if (UnityAssertNumbersWithin((_U_SINT)(_U_UINT)(_UU16)(delta), (_U_SINT)(_U_UINT)(_UU16)(expected), (_U_SINT)(_U_UINT)(_UU16)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX16) != 0) return;
#define UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, line, message)                   if (UnityAssertNumbersWithin((_U_SINT)(_U_UINT)(_UU32)(delta), (_U_SINT)(_U_UINT)(_UU32)(expected), (_U_SINT)(_U_UINT)(_UU32)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX32) != 0) return;

#define UNITY_TEST_ASSERT_EQUAL_PTR(expected, actual, line, message)                             if (UnityAssertEqualNumber((_U_SINT)(_UP)(expected), (_U_SINT)(_UP)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_POINTER) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_STRING(expected, actual, line, message)                          if (UnityAssertEqualString((const char*)(expected), (const char*)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, line, message)                     if (UnityAssertEqualMemory((UNITY_PTR_ATTRIBUTE void*)(expected), (UNITY_PTR_ATTRIBUTE void*)(actual), (_UU32)(len), 1, (message), (UNITY_LINE_TYPE)line) != 0) return;

#define UNITY_TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements, line, message)         if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements, line, message)        if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT8) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_INT16_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT16) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT32) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, line, message)        if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT8) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, actual, num_elements, line, message)      if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT16) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements, line, message)      if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT32) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, line, message)        if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX8) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX16) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(expected), (UNITY_PTR_ATTRIBUTE const void*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX32) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_PTR_ARRAY(expected, actual, num_elements, line, message)         if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const void*)(_UP*)(expected), (const void*)(_UP*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_POINTER) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements, line, message)      if (UnityAssertEqualStringArray((const char**)(expected), (const char**)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, line, message) if (UnityAssertEqualMemory((UNITY_PTR_ATTRIBUTE void*)(expected), (UNITY_PTR_ATTRIBUTE void*)(actual), (_UU32)(len), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line) != 0) return;

#ifdef UNITY_SUPPORT_64
#define UNITY_TEST_ASSERT_EQUAL_INT64(expected, actual, line, message)                           if (UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT64) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT64(expected, actual, line, message)                          if (UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT64) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX64(expected, actual, line, message)                           if (UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX64) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const _U_SINT*)(expected), (UNITY_PTR_ATTRIBUTE const _U_SINT*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT64) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements, line, message)      if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const _U_SINT*)(expected), (UNITY_PTR_ATTRIBUTE const _U_SINT*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT64) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualIntArray((UNITY_PTR_ATTRIBUTE const _U_SINT*)(expected), (UNITY_PTR_ATTRIBUTE const _U_SINT*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX64) != 0) return;
#define UNITY_TEST_ASSERT_HEX64_WITHIN(delta, expected, actual, line, message)                   if (UnityAssertNumbersWithin((_U_SINT)(delta), (_U_SINT)(expected), (_U_SINT)(actual), NULL, (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX64) != 0) return;
#endif

#ifdef UNITY_EXCLUDE_FLOAT
#define UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, line, message)                   UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, line, message)                           UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, line, message)       UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_FLOAT_IS_INF(actual, line, message)                                    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, line, message)                                UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, line, message)                                    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#else
#define UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, line, message)                   if (UnityAssertFloatsWithin((_UF)(delta), (_UF)(expected), (_UF)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, line, message)                           UNITY_TEST_ASSERT_FLOAT_WITHIN((_UF)(expected) * (_UF)UNITY_FLOAT_PRECISION, (_UF)expected, (_UF)actual, (UNITY_LINE_TYPE)line, message)
#define UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, line, message)       if (UnityAssertEqualFloatArray((_UF*)(expected), (_UF*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_FLOAT_IS_INF(actual, line, message)                                    if (UnityAssertFloatIsInf((_UF)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, line, message)                                if (UnityAssertFloatIsNegInf((_UF)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, line, message)                                    if (UnityAssertFloatIsNaN((_UF)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#endif

#ifdef UNITY_EXCLUDE_DOUBLE
#define UNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, line, message)                  UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, line, message)                          UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, line, message)      UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, line, message)                                   UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, line, message)                               UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, line, message)                                   UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#else
#define UNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, line, message)                  if (UnityAssertDoublesWithin((_UD)(delta), (_UD)(expected), (_UD)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, line, message)                          UNITY_TEST_ASSERT_DOUBLE_WITHIN((_UD)(expected) * (_UD)UNITY_DOUBLE_PRECISION, (_UD)expected, (_UD)actual, (UNITY_LINE_TYPE)line, message)
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, line, message)      if (UnityAssertEqualDoubleArray((_UD*)(expected), (_UD*)(actual), (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, line, message)                                   if (UnityAssertDoubleIsInf((_UD)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, line, message)                               if (UnityAssertDoubleIsNegInf((_UD)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#define UNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, line, message)                                   if (UnityAssertDoubleIsNaN((_UD)(actual), (message), (UNITY_LINE_TYPE)line) != 0) return;
#endif

#endif
