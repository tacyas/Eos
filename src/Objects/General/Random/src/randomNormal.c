/*
# randomNormal.c  1.1
# The latest update : 01/23/97 at 11:04:15
#
#@(#) randomNormal ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : randomNormal 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)randomNormal ver1.1; Date:97/01/23 @(#)";

#include "../inc/Random.h"

randomParaTypeReal 
randomNormalGet(long mode)
{
	static randomParaTypeReal random;
	static randomParaTypeReal t, u;
	static randomParaTypeReal r1, r2, s;
	static int sw=0;
	
	switch(mode) {
		case 0: {
			random = random() + random() + random() 
				   + random() + random() + random() 
				   + random() + random() + random() 
				   + random() + random() + random() 
				   -6.0;
			break;
		}
		case 1: {
			if(0==sw) {
				sw = 1;
				t = sqrt(-2.0*log(1-random()));
				u = 2*M_PI*random();
				random = t*cos(u);
			} else {
				sw = 0;
				random = t*sin(u);
			}
			break;
		}
		case 2: {
			if(0==sw) {
				sw = 1;
				do {
					r1 = 2.0*random() - 1.0;
					r2 = 2.0*random() - 1.0;
					s  = r1*r1 + r2*r2;
				} while(s > 1 || s==0);
				s = sqrt(-2.0*log(s)/s);
				random = r1*s;
			} else {
				sw = 0;
				random = r2*s;
			}
			break;
		}
	}
	return random;
}
