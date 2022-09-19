#include <string_cop.h>

#ifndef REGTEST

void * memzero16(void *s, size_t n)
{
	void *ret = s;

	__asm volatile (
		"blti			$2,1,END_%=				\n\t"
		"cdmoviu		$c13,0					\n\t"
		"cdmoviu		$c12,0					\n\t"
		"cdmoviu		$c11,0					\n\t"
		"cdmoviu		$c10,0					\n\t"
		"add			$2,-1					\n\t"
		"repeat			$2,REPEND_%=			\n\t"
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

void * memzero32(void *s, size_t n)
{
	void *ret = s;

	__asm volatile (
		"blti			$2,1,END_%=				\n\t"
		"cdmoviu		$c13,0					\n\t"
		"cdmoviu		$c12,0					\n\t"
		"cdmoviu		$c11,0					\n\t"
		"cdmoviu		$c10,0					\n\t"
		"add			$2,-1					\n\t"
		"repeat			$2,REPEND_%=			\n\t"
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
