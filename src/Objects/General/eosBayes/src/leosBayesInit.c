/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% leosBayesInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : leosBayesInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%leosBayesInit ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/eosBayes.h"


void leosBayesInit(eosBayes* d, int numDistribution, int numLikelihood, int mode){
	
	d->numDistribution = numDistribution;
	d->numLikelihood   = numLikelihood;

	d->prior      = (eosBayesDistribution*)malloc(sizeof(eosBayesDistribution)*numDistribution);
	d->posterior  = (eosBayesDistribution*)malloc(sizeof(eosBayesDistribution)*numDistribution);

	d->likelihood = (eosBayesDistribution*)malloc(sizeof(eosBayesDistribution)*numLikelihood); 

}
