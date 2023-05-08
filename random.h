#pragma once

#if defined(__clang__) || defined(__GNUC__) //for llvm
    #define _rdrand64_step(val) \
    ({ \
        uint64_t __rdrand_result; \
        unsigned char __rdrand_status; \
        asm volatile ("rdrand %0; setc %1" \
            : "=r" (__rdrand_result), "=qm" (__rdrand_status)); \
        (*val) = __rdrand_result; \
        __rdrand_status; \
    })

    #define _rdrand32_step(val) \
    ({ \
        uint32_t __rdrand_result; \
        unsigned char __rdrand_status; \
        asm volatile ("rdrand %0; setc %1" \
            : "=r" (__rdrand_result), "=qm" (__rdrand_status)); \
        (*val) = __rdrand_result; \
        __rdrand_status; \
    })    

    #define _rdrand16_step(val) \
    ({ \
        uint16_t __rdrand_result; \
        unsigned char __rdrand_status; \
        asm volatile ("rdrand %0; setc %1" \
            : "=r" (__rdrand_result), "=qm" (__rdrand_status)); \
        (*val) = __rdrand_result; \
        __rdrand_status; \
    })

#else
    #if defined(_M_ARM64) || defined(__aarch64__) || defined(_M_ARM) || defined(__arm__)
    #include <arm_neon.h>
    #elif defined(_M_X64) || defined(__amd64__) || defined(_M_IX86) || defined(__i386__)
    #include <immintrin.h>
    #endif
#endif 

#ifndef _rdrand16
#define _rdrand16 _rdrand16_step
#endif 

#ifndef _rdrand32
#define _rdrand32 _rdrand32_step
#endif 

#ifndef _rdrand64
#define _rdrand64 _rdrand64_step
#endif 

bool rdrand16(unsigned short* value) {
    return _rdrand16(value) != 0;
}

bool rdrand32(unsigned int *value) {
    return _rdrand32(value) != 0;
}

bool rdrand64(unsigned long long* value) {
    return _rdrand64(value) != 0;
}

