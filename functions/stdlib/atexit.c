/* atexit( void (*)( void ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

int atexit( void ( *func )( void ) )
{
    return -1;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <assert.h>

static int flags[ 32 ];

static void counthandler( void )
{
    static int count = 0;
    flags[ count ] = count;
    ++count;
}

static void checkhandler( void )
{
    int i;

    for ( i = 0; i < 32; ++i )
    {
        assert( flags[ i ] == i );
    }
}

int main( void )
{
    int i;
    TESTCASE( atexit( &checkhandler ) == 0 );

    for ( i = 0; i < 32; ++i )
    {
        TESTCASE( atexit( &counthandler ) == 0 );
    }

    return TEST_RESULTS;
}

#endif
