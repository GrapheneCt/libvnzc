/* vfprintf( FILE *, const char *, va_list )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <uart.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_glue.h"

#ifndef __STDC_NO_THREADS__
#include <threads.h>
#endif

int vfprintf( struct _PDCLIB_file_t * _PDCLIB_restrict stream, const char * _PDCLIB_restrict format, va_list arg )
{
	if (stream != stderr && stream != stdout)
		return EOF;

    /* TODO: This function should interpret format as multibyte characters.  */
	struct _PDCLIB_status_t status;
	status.base = 0;
	status.flags = 0;
	status.n = SIZE_MAX;
	status.i = 0;
	status.current = 0;
	status.s = NULL;
	status.width = 0;
	status.prec = EOF;
	status.stream = stream;

    va_copy( status.arg, arg );

    while ( *format != '\0' )
    {
        const char * rc = format + 1;

        if ( ( *format != '%' ) || ( ( rc = _PDCLIB_print( format, &status ) ) == format ) )
        {
            /* No conversion specifier, print verbatim */
			uart_write(UART_TX_BUS, *format);

            ++format;
            status.i++;
        }
        else
        {
            /* Continue parsing after conversion specifier */
            format = rc;
        }
    }

    va_end( status.arg );

    return status.i;
}

#endif

#ifdef TEST

#include <stddef.h>
#include <float.h>

#define _PDCLIB_FILEID "stdio/vfprintf.c"
#define _PDCLIB_FILEIO

#include "_PDCLIB_test.h"

static int testprintf( FILE * stream, const char * format, ... )
{
    int i;
    va_list arg;
    va_start( arg, format );
    i = vfprintf( stream, format, arg );
    va_end( arg );
    return i;
}

int main( void )
{
    FILE * target;
    TESTCASE( ( target = tmpfile() ) != NULL );
#include "printf_testcases.h"
    TESTCASE( fclose( target ) == 0 );
    return TEST_RESULTS;
}

#endif
