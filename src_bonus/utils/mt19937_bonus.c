/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt19937.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:28:03 by junmlee           #+#    #+#             */
/*   Updated: 2024/09/20 16:28:36 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

	 1. Redistributions of source code must retain the above copyright
		notice, this list of conditions and the following disclaimer.

	 2. Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in the
		documentation and/or other materials provided with the distribution.

	 3. The names of its contributors may not be used to endorse or promote 
		products derived from this software without specific prior written 
		permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

// original code : 
// http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/MT2002/CODES/mt19937ar.c
// Converting to norminette v4 compliance by junmlee

#include "structures_bonus.h"

/* initializes mt[N] with a seed */
void	init_genrand(t_MT19937 *state, unsigned long s)
{
	state->mt[0] = s & 0xffffffffUL;
	state->mti = 1;
	while (state->mti < N)
	{
		state->mt[state->mti] = (1812433253UL * (state->mt[state->mti - 1] \
			^ (state->mt[state->mti - 1] >> 30)) + state->mti);
		state->mt[state->mti] &= 0xffffffffUL;
		state->mti++;
	}
}

void	twist(t_MT19937 *state)
{
	unsigned long			y;
	static unsigned long	mag01[2];
	int						kk;

	mag01[0] = 0x0UL;
	mag01[1] = MATRIX_A;
	kk = 0;
	while (kk < N - M)
	{
		y = (state->mt[kk] & UPPER_MASK) | (state->mt[kk + 1] & LOWER_MASK);
		state->mt[kk] = state->mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		kk++;
	}
	while (kk < N - 1)
	{
		y = (state->mt[kk] & UPPER_MASK) | (state->mt[kk + 1] & LOWER_MASK);
		state->mt[kk] = state->mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		kk++;
	}
	y = (state->mt[N - 1] & UPPER_MASK) | (state->mt[0] & LOWER_MASK);
	state->mt[N - 1] = state->mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
	state->mti = 0;
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long	genrand_int32(t_MT19937 *state)
{
	unsigned long			y;

	if (state->mti >= N)
		twist(state);
	y = state->mt[state->mti++];
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);
	return (y);
}

/* generates a random number on (0,1)-real-interval */
double	grand_r3(t_MT19937 *state)
{
	return ((((double)genrand_int32(state)) + 0.5) * (1.0 / 4294967296.0));
}
