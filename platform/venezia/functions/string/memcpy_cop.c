#include <string_cop.h>

#ifndef REGTEST

void * memcpy16( void *s1, const void *s2, size_t n )
{
	void *ret = s1;

	__asm volatile (
		"blti			$3,1,END_%=				\n\t"
		"add			$3,-1					\n\t"
		"repeat			$3,REPEND_%=			\n\t"
		"lwcpi			$c13,($2+)				\n\t"
		"lwcpi			$c12,($2+)				\n\t"
		"lwcpi			$c11,($2+)				\n\t"
		"lwcpi			$c10,($2+)				\n\t"
		"swcpi			$c13,($1+)				\n\t"
		"swcpi			$c12,($1+)				\n\t"
		"REPEND_%=:								\n\t"
		"swcpi			$c11,($1+)				\n\t"
		"swcpi			$c10,($1+)				\n\t"
		"END_%=:								\n\t"
		::: "$1"
		);

	return ret;
}

void * memcpy32(void *s1, const void *s2, size_t n)
{
	void *ret = s1;

	__asm volatile (
		"blti			$3,1,END_%=				\n\t"
		"add			$3,-1					\n\t"
		"repeat			$3,REPEND_%=			\n\t"
		"lmcpi			$c13,($2+)				\n\t"
		"lmcpi			$c12,($2+)				\n\t"
		"lmcpi			$c11,($2+)				\n\t"
		"lmcpi			$c10,($2+)				\n\t"
		"smcpi			$c13,($1+)				\n\t"
		"smcpi			$c12,($1+)				\n\t"
		"REPEND_%=:								\n\t"
		"smcpi			$c11,($1+)				\n\t"
		"smcpi			$c10,($1+)				\n\t"
		"END_%=:								\n\t"
		::: "$1"
	);

	return ret;
}

#endif

#ifdef TEST


#endif
