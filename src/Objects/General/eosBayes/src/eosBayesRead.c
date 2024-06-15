/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesRead ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/eosBayes.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"

void eosBayesDistributioncheck(FILE* fpt, eosBayes* d, int mode){
	char s[1024];

    
	d->numDistribution = 0;
	d->numLikelihood = 0;
 
	while(NULL != __getStringData(s,"In eosBayesRead",fpt,stdout,3)){

 
		if(STRING_COMMENT_LINE_ID==s[0]){
						d->numDistribution++;
						d->numLikelihood++;
		}
 
	}

	fseek(fpt,0,SEEK_SET);

}


void eosBayesDistributionRead(FILE* fpt, eosBayesDistribution* d, int mode){

  int i;
  char s[1024];

  i=0;
  while(NULL !=__getStringData(s,"In eosBayesDistributionRead",fpt,stdout,3)){
	
	if(STRING_COMMENT_LINE_ID==s[0]){
	  i=0;
	  d->min   = stringGetNthRealData(s,2,STRING_WORD_SEPARATOR);
	  d->max   = stringGetNthRealData(s,3,STRING_WORD_SEPARATOR);
	  d->delta = stringGetNthRealData(s,4,STRING_WORD_SEPARATOR);
	  d->n     = (int)(((d->max-d->min)/d->delta)+1);
	  DEBUGPRINT4("%f %f %f %d\n",d->min,d->max,d->delta,d->n);
	  d->value = (float*)malloc(sizeof(float)*d->n);
	  d->prob  = (float*)malloc(sizeof(float)*d->n);
	}else if('/' == s[0]){
	  DEBUGPRINT("break\n");
	  break;
	}else{
	  d->value[i] = stringGetNthRealData(s,1,STRING_WORD_SEPARATOR); 
	  d->prob[i] = stringGetNthRealData(s,2,STRING_WORD_SEPARATOR);
	  DEBUGPRINT2("%f\t%f\n",d->value[i],d->prob[i]);
	  i++;
	}
	
  }

  fseek(fpt,0,SEEK_SET);  
  
  DEBUGPRINT("DistributionRead end\n");

}



void eosBayesPriorRead(FILE* fpt, eosBayes* d, int mode){

	int i;

	DEBUGPRINT("eosBayesDistributioncheck start\n");
	eosBayesDistributioncheck(fpt,d,0);

	d->prior = (eosBayesDistribution*)malloc(sizeof(eosBayesDistribution)*d->numDistribution);


	for(i=0;i<d->numDistribution;i++){
		DEBUGPRINT("eosBayesDistributionRead start\n");
		eosBayesDistributionRead(fpt,&(d->prior[i]),1);
	}

}



void eosBayesPosteriorRead(FILE* fpt, eosBayes* d, int mode){

	int i;

	DEBUGPRINT("eosBayesDistributioncheck start\n");
	eosBayesDistributioncheck(fpt,d,0);

	d->posterior = (eosBayesDistribution*)malloc(sizeof(eosBayesDistribution)*d->numDistribution);

	DEBUGPRINT("eosBayesDistributionRead start\n");
	for(i=0;i<d->numDistribution;i++){
		eosBayesDistributionRead(fpt,&(d->posterior[i]),1);
	}

}


void eosBayesLikelihoodRead(FILE* fpt, eosBayes* d, int mode){
	int i;

	eosBayesDistributioncheck(fpt,d,1);

	d->likelihood = (eosBayesDistribution*)malloc(sizeof(eosBayesDistribution)*d->numLikelihood);

	for(i=0;i<d->numLikelihood;i++){
		eosBayesDistributionRead(fpt,&(d->likelihood[i]),1);
	}

}



void eosBayesRead(FILE* fpt, eosBayes* d, int mode){
}
