/* iscntrl( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <ctype.h>
#include <vnz/common.h>

#ifndef REGTEST

#include <locale.h>

int iscntrl( int c )
{
	_PDCLIB_lc_ctype_entry_t *entry = (_PDCLIB_lc_ctype_entry_t *)(GET_SYMBOL_ADDR(_ctype_entries_C) + sizeof(_PDCLIB_lc_ctype_entry_t));
    return ( entry[c].flags & _PDCLIB_CTYPE_CNTRL );
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    TESTCASE( iscntrl( '\a' ) );
    TESTCASE( iscntrl( '\b' ) );
    TESTCASE( iscntrl( '\n' ) );
    TESTCASE( ! iscntrl( ' ' ) );
    return TEST_RESULTS;
}

#endif
