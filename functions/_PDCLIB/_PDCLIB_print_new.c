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

	char specchar = 0;

	/* First come 0..n flags */
	do
	{
		specchar = *spec;

		if (specchar == '-') {
			/* left-aligned output */
			status->flags |= E_minus;
			++spec;
		}
		else if (specchar == '+') {
			/* positive numbers prefixed with '+' */
			status->flags |= E_plus;
			++spec;
		}
		else if (specchar == '#') {
			status->flags |= E_alt;
			++spec;
		}
		else if (specchar == ' ') {
			status->flags |= E_space;
			++spec;
		}
		else if (specchar == '0') {
			status->flags |= E_zero;
			++spec;
		}
		else {
			status->flags |= E_done;
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
	specchar = *spec;
	spec++;

	if (specchar == 'h') {
		if (*spec == 'h')
		{
			/* hh -> char */
			status->flags |= E_char;
			++spec;
		}
		else
		{
			/* h -> short */
			status->flags |= E_short;
		}
	}
	else if (specchar == 'l') {
		if (*spec == 'l')
		{
			/* ll -> long long */
			status->flags |= E_llong;
			++spec;
		}
		else
		{
			/* k -> long */
			status->flags |= E_long;
		}
	}
	else if (specchar == 'j') {
		/* j -> intmax_t, which might or might not be long long */
		status->flags |= E_intmax;
	}
	else if (specchar == 'z') {
		/* z -> size_t, which might or might not be unsigned int */
		status->flags |= E_size;
	}
	else if (specchar == 't') {
		/* t -> ptrdiff_t, which might or might not be long */
		status->flags |= E_ptrdiff;
	}
	else if (specchar == 'L') {
		/* L -> long double */
		status->flags |= E_ldouble;
	}
	else {
		--spec;
	}

	specchar = *spec;

	if (specchar == 'd' || specchar == 'i') {
		status->base = 10;
	}
	else if (specchar == 'o') {
		status->base = 8;
		status->flags |= E_unsigned;
	}
	else if (specchar == 'u') {
		status->base = 10;
		status->flags |= E_unsigned;
	}
	else if (specchar == 'x') {
		status->base = 16;
		status->flags |= (E_lower | E_unsigned);
	}
	else if (specchar == 'X') {
		status->base = 16;
		status->flags |= E_unsigned;
	}
	else if (specchar == 'f') {
		status->base = 2;
		status->flags |= (E_decimal | E_double | E_lower);
	}
	else if (specchar == 'F') {
		status->base = 2;
		status->flags |= (E_decimal | E_double);
	}
	else if (specchar == 'e') {
		status->base = 2;
		status->flags |= (E_exponent | E_double | E_lower);
	}
	else if (specchar == 'E') {
		status->base = 2;
		status->flags |= (E_exponent | E_double);
	}
	else if (specchar == 'g') {
		status->base = 2;
		status->flags |= (E_generic | E_double | E_lower);
	}
	else if (specchar == 'G') {
		status->base = 2;
		status->flags |= (E_generic | E_double);
	}
	else if (specchar == 'a') {
		status->base = 2;
		status->flags |= (E_hexa | E_double | E_lower);
	}
	else if (specchar == 'A') {
		status->base = 2;
		status->flags |= (E_hexa | E_double);
	}
	else if (specchar == 'c') {
		char c[1];
		c[0] = (char)va_arg(status->arg, int);
		status->flags |= E_char;
		_PDCLIB_print_string(c, status);
		return ++spec;
	}
	else if (specchar == 's') {
		/* TODO: wide chars. */
		_PDCLIB_print_string(va_arg(status->arg, char *), status);
		return ++spec;
	}
	else if (specchar == 'p') {
		status->base = 16;
		status->flags |= (E_lower | E_unsigned | E_alt | E_pointer);
	}
	else if (specchar == 'n') {
		int * val = va_arg(status->arg, int *);
		*val = status->i;
		return ++spec;
	}
	else {
		/* No conversion specifier. Bad conversion. */
		return orig_spec;
	}

	/* Do the actual output based on our findings */
	if (status->base != 0)
	{
		/* TODO: Check for invalid flag combinations. */
		if (status->flags & E_double)
		{
			/* Floating Point conversions */
			if (status->flags & E_ldouble)
			{
				long double value = va_arg(status->arg, long double);
				_PDCLIB_print_ldouble(value, status);
			}
			else
			{
				double value = va_arg(status->arg, double);
				_PDCLIB_print_double(value, status);
			}
		}
		else
		{
			if (status->flags & E_unsigned)
			{
				/* Integer conversions (unsigned) */
				uintmax_t value;
				imaxdiv_t div;

				int valcheck = status->flags & (E_char | E_short | E_long | E_llong | E_size | E_pointer | E_intmax);

				if (valcheck == E_char) {
					value = (uintmax_t)(unsigned char)va_arg(status->arg, int);
				}
				else if (valcheck == E_short) {
					value = (uintmax_t)(unsigned short)va_arg(status->arg, int);
				}
				else if (valcheck == 0) {
					value = (uintmax_t)va_arg(status->arg, unsigned int);
				}
				else if (valcheck == E_long) {
					value = (uintmax_t)va_arg(status->arg, unsigned long);
				}
				else if (valcheck == E_llong) {
					value = (uintmax_t)va_arg(status->arg, unsigned long long);
				}
				else if (valcheck == E_size) {
					value = (uintmax_t)va_arg(status->arg, size_t);
				}
				else if (valcheck == E_pointer) {
					value = (uintmax_t)(uintptr_t)va_arg(status->arg, void *);
				}
				else if (valcheck == E_intmax) {
					value = va_arg(status->arg, uintmax_t);
				}
				else {
					puts(GET_SYMBOL_ADDR("UNSUPPORTED PRINTF FLAG COMBINATION"));
					return NULL;
				}

				div.quot = value / status->base;
				div.rem = value % status->base;
				_PDCLIB_print_integer(div, status);
			}
			else
			{
				/* Integer conversions (signed) */
				intmax_t value;

				int valcheck = status->flags & (E_char | E_short | E_long | E_llong | E_intmax);

				if (valcheck == E_char) {
					value = (intmax_t)(char)va_arg(status->arg, int);
				}
				else if (valcheck == E_short) {
					value = (intmax_t)(short)va_arg(status->arg, int);
				}
				else if (valcheck == 0) {
					value = (intmax_t)va_arg(status->arg, int);
				}
				else if (valcheck == E_long) {
					value = (intmax_t)va_arg(status->arg, long);
				}
				else if (valcheck == E_llong) {
					value = (intmax_t)va_arg(status->arg, long long);
				}
				else if (valcheck == E_ptrdiff) {
					value = (intmax_t)va_arg(status->arg, ptrdiff_t);
				}
				else if (valcheck == E_intmax) {
					value = va_arg(status->arg, intmax_t);
				}
				else {
					puts(GET_SYMBOL_ADDR("UNSUPPORTED PRINTF FLAG COMBINATION"));
					return NULL;
				}

				_PDCLIB_print_integer(imaxdiv(value, status->base), status);
			}
		}

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
