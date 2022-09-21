/* _PDCLIB_print( const char *, struct _PDCLIB_status_t * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#ifndef REGTEST

#include "pdclib/_PDCLIB_print.h"

void debug_printU32(unsigned int value) {
	char i_buf[4];
	char a_buf[12];

	memcpy(i_buf, &value, sizeof(unsigned int));
	memset(a_buf, '0', 12);
	a_buf[1] = 'x';
	a_buf[10] = 0;
	a_buf[11] = 0;

	for (int i = 0; i < 4; i -= -1) {
		a_buf[9 - i * 2] = ((char *)GET_SYMBOL_ADDR(_PDCLIB_Xdigits))[i_buf[i] & 0x0F];
		a_buf[8 - i * 2] = ((char *)GET_SYMBOL_ADDR(_PDCLIB_Xdigits))[(i_buf[i] & 0xF0) >> 4];
	}

	puts(a_buf);
}

const char * _PDCLIB_print( const char * spec, struct _PDCLIB_status_t * status )
{
	const char * orig_spec = spec;

    if ( *( ++spec ) == '%' )
    {
        /* %% -> print single '%' */
        PUT( *spec );
        return ++spec;
    }
	/*
	switch (*spec) {
	case 'X':
	case 'x':
		debug_printU32(va_arg(status->arg, unsigned int));
		break;
	case 'S':
	case 's':;
		char c[1];
		c[0] = (char)va_arg(status->arg, int);
		puts(c);
		break;
	default:
		break;
	}

	return ++spec;*/

	/* Initializing status structure */
	status->flags = 0;
	status->base = 0;
	status->current = 0;
	status->width = 0;
	status->prec = EOF;

	/* First come 0..n flags */
	do
	{
		switch (*spec)
		{
		case '#':
			/* alternative format (leading 0x for hex, 0 for octal) */
			status->flags |= E_alt;
			++spec;
			break;

		case '0':
			/* right-aligned padding done with '0' instead of ' ' */
			status->flags |= E_zero;
			++spec;
			break;

		default:
			/* not a flag, exit flag parsing */
			status->flags |= E_done;
			break;
		}
	} while (!(status->flags & E_done));

	/* Optional field width */
	if (*spec == '*')
	{
		/* Retrieve width value from argument stack */
		int width = va_arg(status->arg, int);

		if (width < 0)
		{
			status->flags |= E_minus;
			status->width = abs(width);
		}
		else
		{
			status->width = width;
		}

		++spec;
	}
	else
	{
		/* If a width is given, strtol() will return its value. If not given,
		   strtol() will return zero. In both cases, endptr will point to the
		   rest of the conversion specifier - just what we need.
		*/
		status->width = (int)strtol(spec, (char **)&spec, 10);
	}

	/* Optional precision */
	if (*spec == '.')
	{
		++spec;

		if (*spec == '*')
		{
			/* Retrieve precision value from argument stack. A negative value
			   is as if no precision is given - as precision is initalized to
			   EOF (negative), there is no need for testing for negative here.
			*/
			status->prec = va_arg(status->arg, int);
			++spec;
		}
		else
		{
			char * endptr;
			status->prec = (int)strtol(spec, &endptr, 10);

			if (spec == endptr)
			{
				/* Decimal point but no number - equals zero */
				status->prec = 0;
			}

			spec = endptr;
		}

		/* Having a precision cancels out any zero flag. */
		status->flags &= ~E_zero;
	}

	/* Optional length modifier
	   We step one character ahead in any case, and step back only if we find
	   there has been no length modifier (or step ahead another character if it
	   has been "hh" or "ll").
	*/
	switch (*(spec++))
	{
	case 'l':
		if (*spec == 'l')
		{
			/* ll -> long long */
			status->flags |= E_llong;
			++spec;
		}

		break;

	default:
		--spec;
		break;
	}

	/* Conversion specifier */
	char ch = *spec;
	if (ch == 'x') {
		status->base = 16;
		status->flags |= (E_lower | E_unsigned);
	}
	else if (ch == 'X') {
		status->base = 16;
		status->flags |= E_unsigned;
	}
	else if (ch == 'd' || ch == 'i') {
		status->base = 10;
	}
	else if (ch == 'u') {
		status->base = 10;
		status->flags |= E_unsigned;
	}
	else if (ch == 'c') {
		char c[1];
		c[0] = (char)va_arg(status->arg, int);
		status->flags |= E_char;
		_PDCLIB_print_string(c, status);
		return ++spec;
	}
	else if (ch == 's') {
		/* TODO: wide chars. */
		_PDCLIB_print_string(va_arg(status->arg, char *), status);
		return ++spec;
	}
	else {
		/* No conversion specifier. Bad conversion. */
		return orig_spec;
	}

	/* Do the actual output based on our findings */
	if (status->base != 0)
	{
		/* Integer conversions (unsigned) */
		uintmax_t value;
		imaxdiv_t div;

		switch (status->flags & (E_llong))
		{
		case 0:
			value = (uintmax_t)va_arg(status->arg, unsigned int);
			break;

		case E_llong:
			value = (uintmax_t)va_arg(status->arg, unsigned long long);
			break;

		default:
			puts(GET_SYMBOL_ADDR("UNSUPPORTED PRINTF FLAG COMBINATION"));
			return NULL;
		}

		div.quot = value / status->base;
		div.rem = value % status->base;
		_PDCLIB_print_integer(div, status);

		if (status->flags & E_minus)
		{
			/* Left-aligned filling */
			while (status->current < status->width)
			{
				PUT(' ');
				++(status->current);
			}
		}

		if (status->i >= status->n && status->n > 0)
		{
			status->s[status->n - 1] = '\0';
		}
	}

	return ++spec;
}

#endif

#ifdef TEST
#define _PDCLIB_FILEID "_PDCLIB/print.c"
#define _PDCLIB_STRINGIO

#include "_PDCLIB_test.h"

#ifndef REGTEST

static int testprintf( char * buffer, const char * format, ... )
{
    /* Members: base, flags, n, i, current, s, width, prec, stream, arg      */
    struct _PDCLIB_status_t status;
    status.base = 0;
    status.flags = 0;
    status.n = 100;
    status.i = 0;
    status.current = 0;
    status.s = buffer;
    status.width = 0;
    status.prec = EOF;
    status.stream = NULL;
    va_start( status.arg, format );
    memset( buffer, '\0', 100 );

    if ( *( _PDCLIB_print( format, &status ) ) != '\0' )
    {
        printf( "_PDCLIB_print() did not return end-of-specifier on '%s'.\n", format );
        ++TEST_RESULTS;
    }

    va_end( status.arg );
    return status.i;
}

#endif

#define TEST_CONVERSION_ONLY

#include <float.h>

int main( void )
{
#ifndef REGTEST
    char target[100];
#include "printf_testcases.h"
#endif
    return TEST_RESULTS;
}

#endif
