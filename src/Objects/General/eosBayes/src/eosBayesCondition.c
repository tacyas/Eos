/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesCondition ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesCondition 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesCondition ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/eosBayes.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"

void eosBayesCondition(FILE* fptIn, eosBayes* d, eosBayesDistributionInfo* llinfo, int mode){

	int i;
	char s[1024];

	DEBUGPRINT("File read start\n");
	fseek(fptIn,0,SEEK_SET);

	for(i=0; i<d->numDistribution;i++){
		// read each of min, max, delta, mode, mean, sigma

		DEBUGPRINT2("%d/%d loop\n",i+1,d->numDistribution);
		stringGetFromFile(s, "in main", fptIn, stdout, 3);

		llinfo->min      = stringGetNthRealData(s, 2," \t");
		llinfo->max      = stringGetNthRealData(s, 3," \t");
		llinfo->delta    = stringGetNthRealData(s, 4," \t");
		llinfo->mode     = stringGetNthIntegerData(s, 5," \t");

		llinfo->mean     = stringGetNthRealData(s, 6," \t");
		llinfo->sigma    = stringGetNthRealData(s, 7," \t");
		
		DEBUGPRINT1("%s\n",s);
		DEBUGPRINT6("min:%f max:%f delta:%f mode:%u mean:%f sigma:%f\n",llinfo->min,llinfo->max,llinfo->delta,llinfo->mode,llinfo->mean,llinfo->sigma);


		if(llinfo->mode == 1){ 
		  llinfo->constant    = stringGetNthRealData(s, 8," \t");
		  DEBUGPRINT1("constant:%f\n",llinfo->constant);
		}
		
		eosBayesDistributionInit(&(d->prior[i]),llinfo,0);
		eosBayesDistributionInit(&(d->posterior[i]),llinfo,0);
		eosBayesDistributionInit(&(d->likelihood[i]),llinfo,0);
		eosBayesDistributionInitialProbabilitySet(&(d->prior[i]), llinfo, 0);
	}
	DEBUGPRINT("eosBayesConditon finish\n");
	

}

void eosBayesRefinementCondition(FILE* fptIn, eosBayes* d, eosBayesDistributionInfo* llinfo, int n, int mode){

  int i;
  char s[1024];
  float value[3];
  float prob[3];

  DEBUGPRINT("eosBayesRefinementConditon start\n");
  fseek(fptIn,0,SEEK_SET);
  
  for(i=0;i<d->numDistribution;i++){
	  DEBUGPRINT2("%d/%d loop\n",i+1,d->numDistribution);
	  stringGetFromFile(s, "in main", fptIn, stdout, 3);
	  if(d->posterior[i].maxposteriorflag==1){
		DEBUGPRINT2("dist%d use maxposteriorparameter: %f\n",i,d->posterior[i].valueofmaxposterior);
	  }else{
		switch(d->posterior[i].refmode){
		  
		case eosBayesDistributionRefinementModeGaussian:
		  DEBUGPRINT("mode Gaussian\n");
		  eosBayesGettopthreepoint(&(d->posterior[i]),value,prob);
		  llinfo->min = value[0];
		  llinfo->max = value[2];
		  llinfo->sigma = d->posterior[i].delta;
		  llinfo->mean = value[1];
		  llinfo->delta = d->posterior[i].delta/n;
		  llinfo->mode = 0;
		  DEBUGPRINT1("%s\n",s);
		DEBUGPRINT6("min:%f max:%f delta:%f mode:%u mean:%f sigma:%f\n",llinfo->min,llinfo->max,llinfo->delta,llinfo->mode,llinfo->mean,llinfo->sigma);
		eosBayesDistributionInit(&(d->prior[i]),llinfo,1);
		eosBayesDistributionInit(&(d->posterior[i]),llinfo,1);
		eosBayesDistributionInit(&(d->likelihood[i]),llinfo,1);
		eosBayesDistributionInitialProbabilitySet(&(d->prior[i]), llinfo, 0);
		break;

	  case eosBayesDistributionRefimentModelinear:
		DEBUGPRINT("mode linear\n");
		eosBayesGettopthreepoint(&(d->posterior[i]),value,prob);
		llinfo->min = value[0];
		llinfo->max = value[2];
		llinfo->sigma = d->posterior[i].delta;
		llinfo->mean = value[1];
		llinfo->delta = d->posterior[i].delta/n;
		llinfo->mode = 0;
		DEBUGPRINT1("%s\n",s);
		DEBUGPRINT6("min:%f max:%f delta:%f mode:%u mean:%f sigma:%f\n",llinfo->min,llinfo->max,llinfo->delta,llinfo->mode,llinfo->mean,llinfo->sigma);
		eosBayesDistributionInit(&(d->prior[i]),llinfo,1);
		eosBayesDistributionInit(&(d->posterior[i]),llinfo,1);
		eosBayesDistributionInit(&(d->likelihood[i]),llinfo,1);
		eosBayesLiniearinterpolationofTopthreepoint(&(d->prior[i]),value,prob);
		break;
  
	  case eosBayesDistributionRefinementModeConstant:
		if(d->posterior[i].constantflag==1){
		  DEBUGPRINT("mode Constant\n");
		  DEBUGPRINT("")
		  break;
		}else if(d->posterior[i].constantflag==0){
		  DEBUGPRINT("mode Constant->Gaussian\n");
		  llinfo->min      = stringGetNthRealData(s, 2," \t");
		  llinfo->max      = stringGetNthRealData(s, 3," \t");
		  llinfo->delta    = stringGetNthRealData(s, 4," \t");
		  llinfo->mean     = stringGetNthRealData(s, 6," \t");
		  llinfo->sigma    = stringGetNthRealData(s, 7," \t");
		  llinfo->mode = 0;
		  DEBUGPRINT1("%s\n",s);
		  DEBUGPRINT6("min:%f max:%f delta:%f mode:%u mean:%f sigma:%f\n",llinfo->min,llinfo->max,llinfo->delta,llinfo->mode,llinfo->mean,llinfo->sigma);
		  eosBayesDistributionInit(&(d->prior[i]),llinfo,1);
		  eosBayesDistributionInit(&(d->posterior[i]),llinfo,1);
		  eosBayesDistributionInit(&(d->likelihood[i]),llinfo,1);
		  eosBayesDistributionInitialProbabilitySet(&(d->prior[i]), llinfo, 0);
		  break;
		}
	  
	  default:
		break;
	  }

	}
  
  }
  
  DEBUGPRINT("eosBayesRefinementConditon finish\n");

}


void eosBayesGettopthreepoint(eosBayesDistribution* d, float* value, float* prob){

  if(d->valueofmaxposterior==d->min){
	value[0] = d->valueofmaxposterior;
	prob[0] = d->probofmaxposterior;
  }else{
	value[0] = d->value[d->iofmaxposterior-1];
	prob[0] = d->prob[d->iofmaxposterior-1];
  }

  value[1] = d->valueofmaxposterior;
  prob[1] = d->probofmaxposterior;

  if(d->valueofmaxposterior==d->max){
	value[2] = d->valueofmaxposterior;
	prob[2] = d->probofmaxposterior;
  }else{
	value[2] = d->value[d->iofmaxposterior+1];
	prob[2] = d->prob[d->iofmaxposterior+1];
  }
}


void eosBayesLiniearinterpolationofTopthreepoint(eosBayesDistribution* d, float* value, float* prob){
  float a1;
  float a2;
  float b1;
  float b2;

  int i;
  float sum;

  a1 = 0;
  a2 = 0;
  b1 = 0;
  b2 = 0;

  if(value[0] != value[1]){ 
	a1 = (prob[0]-prob[1])/(value[0]-value[1]);
	b1 = -a1*value[1]+prob[1];
  }

  if(value[2] != value[1]){ 
	a2 = (prob[1]-prob[2])/(value[1]-value[2]);
	b2 = -a2*value[1]+prob[1];
  }

  sum = 0;
  for(i=0;i<d->n;i++){
	if(d->value[i]<value[1]){
	  d->prob[i] = a1*d->value[i]+b1;
	}else if(value[1]<=d->value[i]){
	  d->prob[i] = a2*d->value[i]+b2;
	}
	sum += d->prob[i];
  }

  for(i=0;i<d->n;i++){
	d->prob[i] /= sum;
  }
  
}
