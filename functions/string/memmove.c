/* memmove( void *, const void *, size_t )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <string.h>

#ifndef REGTEST

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
void * memmove( void * s1, const void * s2, size_t n )
{
	__asm volatile (
		"beqz			$3,LOC1_%=		\n\t"
		"sltu3			$0,$1,$2		\n\t"
		"beqz			$0,LOC2_%=		\n\t"
		"mov			$12,$1			\n\t"
		"erepeat		REPEND1_%=		\n\t"
		"lb				$11,($2)		\n\t"
		"add			$2,1			\n\t"
		"add			$3,-1			\n\t"
		"sb				$11,($12)		\n\t"
		"REPEND1_%=:					\n\t"
		"add			$12,1			\n\t"
		"beqz			$3,LOC1_%=		\n\t"
		"LOC2_%=:						\n\t"
		"add3			$12,$1,$3		\n\t"
		"add3			$11,$2,$3		\n\t"
		"erepeat		REPEND2_%=		\n\t"
		"add			$3,-1			\n\t"
		"add			$11,-1			\n\t"
		"lb				$10,($11)		\n\t"
		"add			$12,-1			\n\t"
		"REPEND2_%=:					\n\t"
		"sb				$10,($12)		\n\t"
		"beqz			$3,LOC1_%=		\n\t"
		"LOC1_%=:						\n\t"
		"mov			$0,$1			\n\t"
		"ret							\n\t"
		:::
	);
}
#pragma GCC diagnostic pop

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    char s[] = "xxxxabcde";
    TESTCASE( memmove( s, s + 4, 5 ) == s );
    TESTCASE( s[0] == 'a' );
    TESTCASE( s[4] == 'e' );
    TESTCASE( s[5] == 'b' );
    TESTCASE( memmove( s + 4, s, 5 ) == s + 4 );
    TESTCASE( s[4] == 'a' );
    return TEST_RESULTS;
}

#endif
