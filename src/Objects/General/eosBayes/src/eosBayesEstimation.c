/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesEstimation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesEstimation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesEstimation ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/eosBayes.h"

#define DEBUG
#include "genUtil.h"

void eosBayesEstimation(eosBayes* d, int mode){
	int i;
	int j;
	float sum = 0;

	char s[1024];

	for(i=0;i<d->numDistribution;i++){
		DEBUGPRINT2("----%dDistribution num:%d----\n",i,d->prior[i].n);
		if(d->prior[i].n!=1){
		  sum=0;
		  for(j=0;j<d->prior[i].n;j++){
			d->posterior[i].prob[j] = d->likelihood[i].prob[j]*d->prior[i].prob[j];
			sum += d->posterior[i].prob[j];
		  }
		  for(j=0;j<d->prior[i].n;j++){
			d->posterior[i].prob[j] /= sum;
			DEBUGPRINT2("post:%f %f\n",d->posterior[i].value[j],d->posterior[i].prob[j]);
		  }
		}

	}

}



void eosBayesPosteriortoPrior(eosBayes* d,int mode){

	int i;
	int j;

	for(i=0;i<d->numDistribution;i++){
	  if(d->prior[i].n!=1){
		for(j=0;j<d->prior[i].n;j++){
		  d->prior[i].prob[j] = d->posterior[i].prob[j];
		}
	  }
	}

}



void eosBayesloop(eosBayesDistribution* d, int* L, int numDist, int length){

  int N1;
  int N2;

  int i;

  N1=1;
  N2=1;

  for(i=0;i<numDist-1;i++){
	N2    = d[i].n;
	L[i]  = (length/N1)%N2;
	N1   *= d[i].n;
  }
  L[numDist-1] = length/N1;


}
