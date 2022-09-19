/* puts( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>
#include <uart.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

int puts( const char * s )
{
	int count = 0;

    while ( *s != '\0' )
    {
		uart_write(UART_TX_BUS, *s++);
		count++;
    }

	uart_write(UART_TX_BUS, '\n');

	return count;
}

#endif

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    FILE * fh;
    const char * message = "SUCCESS testing puts()";
    char buffer[23];
    buffer[22] = 'x';
    TESTCASE( ( fh = freopen( testfile, "wb+", stdout ) ) != NULL );
    TESTCASE( puts( message ) >= 0 );
    rewind( fh );
    TESTCASE( fread( buffer, 1, 22, fh ) == 22 );
    TESTCASE( memcmp( buffer, message, 22 ) == 0 );
    TESTCASE( buffer[22] == 'x' );
    TESTCASE( fclose( fh ) == 0 );
    TESTCASE( remove( testfile ) == 0 );
    return TEST_RESULTS;
}

#endif
