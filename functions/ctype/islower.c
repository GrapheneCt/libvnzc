/* islower( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <vnz/common.h>

#ifndef REGTEST

#include <locale.h>

int islower( int c )
{
	_PDCLIB_lc_ctype_entry_t *entry = (_PDCLIB_lc_ctype_entry_t *)(GET_SYMBOL_ADDR(_ctype_entries_C) + sizeof(_PDCLIB_lc_ctype_entry_t));
    return ( entry[c].flags & _PDCLIB_CTYPE_LOWER );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( islower( 'a' ) );
    TESTCASE( islower( 'z' ) );
    TESTCASE( ! islower( 'A' ) );
    TESTCASE( ! islower( 'Z' ) );
    TESTCASE( ! islower( ' ' ) );
    TESTCASE( ! islower( '@' ) );
    return TEST_RESULTS;
}

#endif
