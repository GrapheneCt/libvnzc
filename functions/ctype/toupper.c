/* toupper( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <vnz/common.h>

#ifndef REGTEST

#include <locale.h>

int toupper( int c )
{
	_PDCLIB_lc_ctype_entry_t *entry = (_PDCLIB_lc_ctype_entry_t *)(GET_SYMBOL_ADDR(_ctype_entries_C) + sizeof(_PDCLIB_lc_ctype_entry_t));
    return entry[c].upper;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( toupper( 'a' ) == 'A' );
    TESTCASE( toupper( 'z' ) == 'Z' );
    TESTCASE( toupper( 'A' ) == 'A' );
    TESTCASE( toupper( 'Z' ) == 'Z' );
    TESTCASE( toupper( '@' ) == '@' );
    TESTCASE( toupper( '[' ) == '[' );
    return TEST_RESULTS;
}

#endif
