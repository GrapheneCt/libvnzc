/* memset( void *, int, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

#ifndef REGTEST

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
void * memset( void * s, int c, size_t n )
{
	__asm volatile (
		"mov			$0,$1					\n\t"
		"add3			$12,$3,-1				\n\t"
		"beqz			$3,END_%=				\n\t"
		"repeat			$12,REPEND_%=			\n\t"
		"nop									\n\t"
		"REPEND_%=:								\n\t"
		"sb				$2,($1)					\n\t"
		"add			$1,1					\n\t"
		"END_%=:								\n\t"
		"ret									\n\t"
		:::
		);
}
#pragma GCC diagnostic pop

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char s[] = "xxxxxxxxx";
    TESTCASE( memset( s, 'o', 10 ) == s );
    TESTCASE( s[9] == 'o' );
    TESTCASE( memset( s, '_', ( 0 ) ) == s );
    TESTCASE( s[0] == 'o' );
    TESTCASE( memset( s, '_', 1 ) == s );
    TESTCASE( s[0] == '_' );
    TESTCASE( s[1] == 'o' );
    return TEST_RESULTS;
}

#endif
