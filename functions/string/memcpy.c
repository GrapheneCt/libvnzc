/* memcpy( void *, const void *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

#ifndef REGTEST

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
void * memcpy( void * _PDCLIB_restrict s1, const void * _PDCLIB_restrict s2, size_t n )
{
	__asm volatile (
		"mov			$0,$1					\n\t"
		"add3			$12,$3,-1				\n\t"
		"beqz			$3,END_%=				\n\t"
		"repeat			$12,REPEND_%=			\n\t"
		"lb				$12,($2)				\n\t"
		"add			$2,1					\n\t"
		"REPEND_%=:								\n\t"
		"sb				$12,($1)				\n\t"
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
    char s[] = "xxxxxxxxxxx";
    TESTCASE( memcpy( s, abcde, 6 ) == s );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == '\0' );
    TESTCASE( memcpy( s + 5, abcde, 5 ) == s + 5 );
    TESTCASE( s[9] == 'e' );
    TESTCASE( s[10] == 'x' );
    return TEST_RESULTS;
}

#endif
