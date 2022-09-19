#ifndef _PDCLIB_STRING_COP_H
#define _PDCLIB_STRING_COP_H _PDCLIB_STRING_COP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pdclib/_PDCLIB_lib_ext1.h"
#include "pdclib/_PDCLIB_internal.h"

#ifndef _PDCLIB_SIZE_T_DEFINED
#define _PDCLIB_SIZE_T_DEFINED _PDCLIB_SIZE_T_DEFINED
typedef _PDCLIB_size_t size_t;
#endif

#ifndef _PDCLIB_NULL_DEFINED
#define _PDCLIB_NULL_DEFINED _PDCLIB_NULL_DEFINED
#define NULL _PDCLIB_NULL
#endif

/* String function conventions */

_PDCLIB_PUBLIC void *memcpy16(void *s1, const void *s2, size_t n);

_PDCLIB_PUBLIC void *memcpy32(void *s1, const void *s2, size_t n);

_PDCLIB_PUBLIC void *memzero16(void *s, size_t n);

_PDCLIB_PUBLIC void *memzero32(void *s, size_t n);

#ifdef __cplusplus
}
#endif

#endif
