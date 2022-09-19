/* fputc( int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <uart.h>
#include <vnz/common.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

int fputc( int c, struct _PDCLIB_file_t * stream )
{
	if (stream != stderr && stream != stdout)
		return EOF;

	uart_write(UART_TX_BUS, c);

    return c;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    /* Testing covered by ftell.c */
    return TEST_RESULTS;
}

#endif
