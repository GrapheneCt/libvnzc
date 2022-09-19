/* exit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

void exit( int status )
{
    _Exit( status );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Unwinding of regstack tested in atexit(). */
    return TEST_RESULTS;
}

#endif
