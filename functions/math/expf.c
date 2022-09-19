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

		e ^ x = (1+m) * (2^n)
		x = log(1+m) + n * log(2)
		n = (int) (x * 1.0 / log(2))
		(1+m) = e ^ (x - n * log(2))
		(1+m) = Poly(x - n * log(2))
		
		where Poly(x) is the Minimax approximation of e ^ x over the 
		range [-Log(2), Log(2)]

Test func : expf(x)
Test Range: 0 < x < 50
Peak Error:	~0.00024%
RMS  Error: ~0.00007%
*/



#include <math.h>
#include <vnz/common.h>

const float __expf_rng[2] = {
	1.442695041f,
	0.693147180f
};

const float __expf_lut[8] = {
	0.9999999916728642,		//p0
	0.04165989275009526, 	//p4
	0.5000006143673624, 	//p2
	0.0014122663401803872, 	//p6
	1.000000059694879, 		//p1
	0.008336936973260111, 	//p5
	0.16666570253074878, 	//p3
	0.00019578093328483123	//p7
};

float expf(float x)
{
	float a, b, c, d, xx;
	int m;
	
	union {
		float   f;
		int 	i;
	} r;
		
	//Range Reduction:
	m = (int) (x * GET_SYMBOL_PFLOAT(__expf_rng)[0]);
	x = x - ((float) m) * GET_SYMBOL_PFLOAT(__expf_rng)[1];
	
	//Taylor Polynomial (Estrins)
	a = (GET_SYMBOL_PFLOAT(__expf_lut)[4] * x) + (GET_SYMBOL_PFLOAT(__expf_lut)[0]);
	b = (GET_SYMBOL_PFLOAT(__expf_lut)[6] * x) + (GET_SYMBOL_PFLOAT(__expf_lut)[2]);
	c = (GET_SYMBOL_PFLOAT(__expf_lut)[5] * x) + (GET_SYMBOL_PFLOAT(__expf_lut)[1]);
	d = (GET_SYMBOL_PFLOAT(__expf_lut)[7] * x) + (GET_SYMBOL_PFLOAT(__expf_lut)[3]);
	xx = x * x;
	a = a + b * xx; 
	c = c + d * xx;
	xx = xx* xx;
	r.f = a + c * xx; 
	
	//multiply by 2 ^ m 
	m = m << 23;
	r.i = r.i + m;

	return r.f;
}