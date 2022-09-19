/*
Math-NEON:  Neon Optimised Math Library based on cmath
Contact:    lachlan.ts@gmail.com
Copyright (C) 2009  Lachlan Tychsen - Smith aka Adventus

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <math.h>
#include <vnz/common.h>

static const float __sinf_rng[2] = {
	2.0 / M_PI,
	M_PI / 2.0
};

static const float __sinf_lut[4] = {
	-0.00018365f,	//p7
	-0.16664831f,	//p3
	+0.00830636f,	//p5
	+0.99999661f,	//p1
};

float sinf(float x)
{
	union {
		float 	f;
		int 	i;
	} ax;
	
	float r, a, b, xx;
	int m, n;
	
	ax.f = fabsf(x);

	//Range Reduction:
	m = (int) (ax.f * GET_SYMBOL_PFLOAT(__sinf_rng)[0]);
	ax.f = ax.f - (((float)m) * GET_SYMBOL_PFLOAT(__sinf_rng)[1]);

	//Test Quadrant
	n = m & 1;
	ax.f = ax.f - n * GET_SYMBOL_PFLOAT(__sinf_rng)[1];
	m = m >> 1;
	n = n ^ m;
	m = (x < 0.0);
	n = n ^ m;	
	n = n << 31;
	ax.i = ax.i ^ n; 

	//Taylor Polynomial (Estrins)
	xx = ax.f * ax.f;	
	a = (GET_SYMBOL_PFLOAT(__sinf_lut)[0] * ax.f) * xx + (GET_SYMBOL_PFLOAT(__sinf_lut)[2] * ax.f);
	b = (GET_SYMBOL_PFLOAT(__sinf_lut)[1] * ax.f) * xx + (GET_SYMBOL_PFLOAT(__sinf_lut)[3] * ax.f);
	xx = xx * xx;
	r = b + a * xx;

	return r;
}