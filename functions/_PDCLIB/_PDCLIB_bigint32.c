/* _PDCLIB_bigint32( _PDCLIB_bigint_t *, uint_least32_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#ifndef REGTEST

#include "pdclib/_PDCLIB_internal.h"

_PDCLIB_bigint_t * _PDCLIB_bigint32( _PDCLIB_bigint_t * bigint, _PDCLIB_uint_least32_t value )
{
    *bigint = { { value }, 1 };

    if ( value == 0 )
    {
        bigint->size = 0;
    }

    return bigint;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <stdint.h>

int main( void )
{
#ifndef REGTEST
    _PDCLIB_bigint_t big;
    _PDCLIB_bigint_t * bigptr;
    bigptr = _PDCLIB_bigint32( &big, UINT32_C( 0 ) );
    TESTCASE( bigptr == &big );
    TESTCASE( big.size == 0 );
    _PDCLIB_bigint32( &big, UINT32_C( 0x12345678 ) );
    TESTCASE( big.size == 1 );
    TESTCASE( big.data[0] == UINT32_C( 0x12345678 ) );
#endif
    return TEST_RESULTS;
}

#endif
