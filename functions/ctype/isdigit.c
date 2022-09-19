/* isdigit( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <vnz/common.h>

#ifndef REGTEST

#include <locale.h>

int isdigit( int c )
{
	_PDCLIB_lc_ctype_t *ctype_struct = (_PDCLIB_lc_ctype_t *)(GET_SYMBOL_ADDR(_PDCLIB_lc_ctype_C));
    return ( c >= ctype_struct->digits_low && c <= ctype_struct->digits_high );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( isdigit( '0' ) );
    TESTCASE( isdigit( '9' ) );
    TESTCASE( ! isdigit( ' ' ) );
    TESTCASE( ! isdigit( 'a' ) );
    TESTCASE( ! isdigit( '@' ) );
    return TEST_RESULTS;
}

#endif
