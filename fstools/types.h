#ifndef FSTOOLS_TYPES_H
#define FSTOOLS_TYPES_H 1

#include <stddef.h>
#include <stdint.h>

/*
 * INTERNAL USAGE ONLY
 * None of the types or defines are namespaced.
 * As such this header must not be exposed in any
 * way to the API headers.
 */

#define null NULL

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;

#define U8_MAX UINT8_MAX
#define U16_MAX UINT16_MAX
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define I8_MIN INT8_MIN
#define I8_MAX INT8_MAX
#define I16_MIN INT16_MIN
#define I16_MAX INT16_MAX
#define I32_MIN INT32_MIN
#define I32_MAX INT32_MAX
#define I64_MIN INT64_MIN
#define I64_MAX INT64_MAX

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

#define USIZE_MAX SIZE_MAX

typedef size_t usize;

#define false 0
#define true 1

typedef uint bool;

#endif