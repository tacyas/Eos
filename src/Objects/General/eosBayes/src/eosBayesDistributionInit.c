/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesDistributionInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesDistributionInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesDistributionInit ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/eosBayes.h"


#define  DEBUG
#include "genUtil.h"
#include "eosString.h"

void eosBayesDistributionInit(eosBayesDistribution* d, eosBayesDistributionInfo* info, int mode){

	int i;


	if(mode==1){
	  free(d->value);
	  free(d->prob);
	}

	d->min   = info->min;
	d->max   = info->max;
	d->delta = info->delta;
	d->resetflag = 0;
	d->maxposteriorflag = 0;
	d->rangechangeflag = 0;
	d->percentageofrange = 0.95;
	d->nofpartitions = 10;

	switch(info->mode){

	case 0:
	  d->n     = (int)(((info->max-info->min)/info->delta)+1);
	  d->value = (float*)malloc(sizeof(float)*d->n);
	  d->prob  = (float*)malloc(sizeof(float)*d->n);
	  info->mode = eosBayesDistributionInfoModeGaussian;
	  for(i=0;i<d->n;i++){
		d->value[i] = d->min+(d->delta*i);
	  }
	  break;
	case 1:
	  d->n = 1;
	  d->value = (float*)malloc(sizeof(float)*d->n);
	  d->prob  = (float*)malloc(sizeof(float)*d->n);
	  info->mode = eosBayesDistributionInfoModeConstant;
	  d->value[0] = info->constant;
	  break;

	default:
	  break;
	  
	}


}
