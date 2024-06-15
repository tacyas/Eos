/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% stringIsSame ver %I%
#%Z% Created by tacyas`:w
#%Z%
#%Z% Usage : stringIsSame 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%stringIsSame ver%I%; Date:%D% %Z%";

#include "genUtil.h"
#include "../inc/eosString.h"

long
stringIsSame(char* s1, char* s2, long n)
{
    long i;
	long nn;
	long n1;
	long n2;

	n1 = stringLength(s1);
	n2 = stringLength(s2);
	nn = MIN(n1, n);	
	if(n2<nn) {
		return 0;
	} else {
    	for(i=0; i<nn; i++) {
       		if(s1[i]!=s2[i]) {
            	return 0;
        	}
    	}
	}
    return 1;
}
