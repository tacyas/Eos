/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosFunc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosFunc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosFunc ver%I%; Date:%D% %Z%";

#include "math.h"
#include "../inc/eosFunc.h"

double 
eosSinc(double x)
{
	double ret;

	if(x==0) {
		ret = 1;
	}  else {
		ret = sin(M_PI*x)/(M_PI*x);
	}

	return ret;
}

double 
eosRect(double x, double xmax) 
{
	double ret;

	if(x<xmax) {
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;
}
