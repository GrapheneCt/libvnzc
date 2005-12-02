/* $Id$ */

/* Release $Name$ */

/* atoi( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <_PDCLIB_int.h>

int atoi( const char * s )
{
    return (int) _PDCLIB_atomax( s );
}

#ifdef TEST
#include <_PDCLIB_test.h>

int main()
{
    BEGIN_TESTS;
    /* no tests for a simple wrapper */
    return TEST_RESULTS;
}

#endif
