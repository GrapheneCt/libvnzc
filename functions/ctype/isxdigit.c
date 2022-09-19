/* isxdigit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <vnz/common.h>

#ifndef REGTEST

#include <locale.h>

int isxdigit( int c )
{
	_PDCLIB_lc_ctype_t *ctype_struct = (_PDCLIB_lc_ctype_t *)(GET_SYMBOL_ADDR(_PDCLIB_lc_ctype_C));
    return ( isdigit( c ) ||
             ( c >= ctype_struct->Xdigits_low && c <= ctype_struct->Xdigits_high ) ||
             ( c >= ctype_struct->xdigits_low && c <= ctype_struct->xdigits_high )
           );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( isxdigit( '0' ) );
    TESTCASE( isxdigit( '9' ) );
    TESTCASE( isxdigit( 'a' ) );
    TESTCASE( isxdigit( 'f' ) );
    TESTCASE( ! isxdigit( 'g' ) );
    TESTCASE( isxdigit( 'A' ) );
    TESTCASE( isxdigit( 'F' ) );
    TESTCASE( ! isxdigit( 'G' ) );
    TESTCASE( ! isxdigit( '@' ) );
    TESTCASE( ! isxdigit( ' ' ) );
    return TEST_RESULTS;
}

#endif
