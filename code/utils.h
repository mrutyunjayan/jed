/* date = January 9th 2021 10:37 am */

#ifndef UTILS_H
#define UTILS_H

#pragma warning(push)
#pragma warning( disable : 4514 )
#include <stdint.h>
#include <stddef.h>

//~ TYPEDEFS

typedef int8_t         s8;
typedef int16_t        s16;
typedef int32_t        s32;
typedef int64_t        s64;

typedef uint8_t        u8;
typedef uint16_t       u16;
typedef uint32_t       u32;
typedef uint64_t       u64;

typedef int32_t        b32;
typedef unsigned int   uint;

typedef size_t          size_t;
typedef size_t          memoryIndex;

typedef float          f32;
typedef double         f64;
typedef uintptr_t      p64;

#define U32_MAX        0xFFFFFFFF
#define U64_MAX        0xFFFFFFFFFFFFFFFF

//~ MACROS

#define localPersist  static
#define global        static
#define internal      static
#define readOnly      const

#define PI            3.14159265359f

#define KB(value)     (value * 1024LL)
#define MB(value)     (KB(value) * 1024LL)
#define GB(value)     (MB(value) * 1024LL)
#define TB(value)     (GB(value) * 1024LL)

#define ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))

#if JED_SLOW
#define ASSERT(expression)\
if(!(expression)) {\
*(volatile int*)0 = 0;\
}
#else
#define ASSERT(expression)
#endif

#define STRING(name) #name

#define IS_POWER_OF_2(x) ((x & (x - 1)) == 0)

#define CLAMP(value, min, max) (value <= min) ? min : (value >= max) ? max : value;

//~-------------Swap ----------------------
#define SWAP(a, b) do { \
u8 swapTemp[(sizeof(a) == sizeof(b)) ? sizeof(a) : -1]; \
memcpy(swapTemp, &a, sizeof(a)); \
memcpy(&a, &b, sizeof(a)); \
memcpy(&b, swapTemp, sizeof(a)); \
} while(0)

//~ Truncate
inline internal u32 
truncate_safe_s64(s64 value) {
    // TODO(Jai): Defines for maximum values (u32_t)
    ASSERT(value <= 0xFFFFFFFF);
    u32 result = (u32)value;
    
    return result;
}
#pragma warning(pop)
#endif //UTILS_H
