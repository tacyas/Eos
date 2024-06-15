/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesParameterOfMaxPosterior ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesParameterOfMaxPosterior 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesParameterOfMaxPosterior ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/eosBayes.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"


void eosBayesParameterOfMaxPosteriorGet(eosBayesDistribution* d, int numDistribution, int mode){

  int i;

  for(i=0;i<numDistribution;i++){
	DEBUGPRINT2("dist%dflag:%d\n",i,d[i].maxposteriorflag);
	if(d[i].maxposteriorflag == 0){
	  DEBUGPRINT1("---dist%d get---\n",i);
	  leosBayesParameterOfMaxPosteriorGet(&(d[i]),mode);
	}
	DEBUGPRINT1("---dist%d---\n",i);
	DEBUGPRINT2("value[%d]:%f\n",d[i].iofmaxposterior,d[i].valueofmaxposterior);
  }

}

void leosBayesParameterOfMaxPosteriorGet(eosBayesDistribution* d, int mode){

  int i;

	  d->valueofmaxposterior = d->value[0];
	  d->probofmaxposterior = d->prob[0];
	  d->iofmaxposterior = 0;
	  for(i=0;i<d->n;i++){
		if(d->probofmaxposterior < d->prob[i]){
		  d->valueofmaxposterior = d->value[i];
		  d->probofmaxposterior = d->prob[i];
		  d->iofmaxposterior = i;
		}
	  }

}
