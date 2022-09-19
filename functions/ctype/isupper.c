/* isupper( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <vnz/common.h>

#ifndef REGTEST

#include <locale.h>

int isupper( int c )
{
	_PDCLIB_lc_ctype_entry_t *entry = (_PDCLIB_lc_ctype_entry_t *)(GET_SYMBOL_ADDR(_ctype_entries_C) + sizeof(_PDCLIB_lc_ctype_entry_t));
    return ( entry[c].flags & _PDCLIB_CTYPE_UPPER );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( isupper( 'A' ) );
    TESTCASE( isupper( 'Z' ) );
    TESTCASE( ! isupper( 'a' ) );
    TESTCASE( ! isupper( 'z' ) );
    TESTCASE( ! isupper( ' ' ) );
    TESTCASE( ! isupper( '@' ) );
    return TEST_RESULTS;
}

#endif
