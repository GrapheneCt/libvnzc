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

/*
Based on: 

		log(x) = log((1+m) * (2^n))
		log(x) = n * log(2) + log(1 + m)
		log(1+m) = Poly(1+m)
		
		where Poly(x) is the Minimax approximation of log(x) over the 
		range [1, 2]

Test func : logf(x)
Test Range: 1 < x < 10000
Peak Error:	~0.000601%
RMS  Error: ~0.000005%
*/

#include <math.h>
#include <vnz/common.h>

static const float __logf_lut[8] = {
	-2.295614848256274, 	//p0
	-2.470711633419806, 	//p4
	-5.686926051100417, 	//p2
	-0.165253547131978, 	//p6
	+5.175912446351073, 	//p1
	+0.844006986174912, 	//p5
	+4.584458825456749, 	//p3
	+0.014127821926000		//p7
};

float logf(float x)
{
	float a, b, c, d, xx;
	int m;
	
	union {
		float   f;
		int 	i;
	} r;
	
	//extract exponent
	r.f = x;
	m = (r.i >> 23);
	m = m - 127;
	r.i = r.i - (m << 23);
		
	//Taylor Polynomial (Estrins)
	xx = r.f * r.f;
	a = (GET_SYMBOL_PFLOAT(__logf_lut)[4] * r.f) + (GET_SYMBOL_PFLOAT(__logf_lut)[0]);
	b = (GET_SYMBOL_PFLOAT(__logf_lut)[6] * r.f) + (GET_SYMBOL_PFLOAT(__logf_lut)[2]);
	c = (GET_SYMBOL_PFLOAT(__logf_lut)[5] * r.f) + (GET_SYMBOL_PFLOAT(__logf_lut)[1]);
	d = (GET_SYMBOL_PFLOAT(__logf_lut)[7] * r.f) + (GET_SYMBOL_PFLOAT(__logf_lut)[3]);
	a = a + b * xx;
	c = c + d * xx;
	xx = xx * xx;
	r.f = a + c * xx;

	//add exponent
	r.f = r.f + ((float) m) * 0.693147180f;

	return r.f;
}