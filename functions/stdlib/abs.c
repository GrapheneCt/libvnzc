/* abs( int )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
int abs( int j )
{
	__asm volatile (
		"blti			$1,0,NEG_%= 			\n\t"
		"mov			$0,$1					\n\t"
		"ret									\n\t"
		"NEG_%=:								\n\t"
		"neg			$0,$1					\n\t"
		"ret									\n\t"
		:::
		);
}
#pragma GCC diagnostic pop

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

#include <limits.h>

int main( void )
{
	TESTCASE( abs( 0 ) == 0 );
	TESTCASE( abs( INT_MAX ) == INT_MAX );
	TESTCASE( abs( INT_MIN + 1 ) == -( INT_MIN + 1 ) );
	return TEST_RESULTS;
}

#endif
