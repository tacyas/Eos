/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesDistributionInitialProbabilitySet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesDistributionInitialProbabilitySet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesDistributionInitialProbabilitySet ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/eosBayes.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"


void eosBayesDistributionInitialProbabilitySet(eosBayesDistribution* d, eosBayesDistributionInfo* info, int mode){

	int i;
	float data;
	float sum;

	switch(info->mode){

	case eosBayesDistributionInfoModeGaussian:
	  fprintf(stderr, "-----Mode Gaussian distribution-----\n");
	  sum = 0;
	  for(i=0;i<d->n;i++){
		d->prob[i] = (1/sqrt(2*M_PI*info->sigma*info->sigma))*exp(-(((d->value[i]-info->mean)*(d->value[i]-info->mean))/(2*info->sigma*info->sigma)));
		sum += d->prob[i];
	  }
	  
	  for(i=0;i<d->n;i++){
		d->prob[i] /= sum;
	  }
	  
	  break;

	case eosBayesDistributionInfoModeConstant:
	  fprintf(stderr, "-----Mode Constant-----\n");
	  d->prob[0] = 1;
	  break;

	default:
	  break;

	}


}

void eosBayesProbabilityReset(FILE* fptIn, eosBayes* d, int n, int mode){
  int i;
  char s[1024];
  eosBayesDistributionInfo info;

  DEBUGPRINT("eosBayesProbabilityReset\n");
  fseek(fptIn,0,SEEK_SET);

  for(i=0;i<d->numDistribution;i++){
	DEBUGPRINT2("%d/%d loop\n",i+1,d->numDistribution);
	stringGetFromFile(s, "in main", fptIn, stdout, 3);
	if(d->prior[i].resetflag==1){
	  DEBUGPRINT("Set new prior\n");
	  info.min = stringGetNthRealData(s, 2," \t");
	  info.max = stringGetNthRealData(s, 3," \t");
	  info.delta = stringGetNthRealData(s, 4," \t");
	  info.mode = 0;
	  info.mean = stringGetNthRealData(s, 6," \t");
	  info.sigma = stringGetNthRealData(s, 7," \t");
	  info.delta = info.delta/n;
	  DEBUGPRINT1("%s\n",s);
	  DEBUGPRINT6("min:%f max:%f delta:%f mode:%u mean:%f sigma:%f\n",info.min,info.max,info.delta,info.mode,info.mean,info.sigma);
	  eosBayesDistributionInit(&(d->prior[i]),&info,1);
	  eosBayesDistributionInit(&(d->posterior[i]),&info,1);
	  eosBayesDistributionInit(&(d->likelihood[i]),&info,1);
	  eosBayesDistributionInitialProbabilitySet(&(d->prior[i]), &info, 1);  
	  eosBayesDistributionInitialProbabilitySet(&(d->posterior[i]), &info, 1);  
	  DEBUGPRINT1("dist%d was reset\n",i);
	  leosBayesParameterOfMaxPosteriorGet(&(d->posterior[i]),0);
	  d->posterior[i].maxposteriorflag = 0;
	  d->prior[i].resetflag = 0;
	}
  }

}


void eosBayesProbabilitysetLinear(eosBayesDistribution* d, float a, float b){

  int i;
  float sum;
  
  sum = 0;

  for(i=0;i<d->n;i++){
	d->prob[i] = a*d->value[i]+b; 
	sum += d->prob[i];
  }

  for(i=0;i<d->n;i++){
	d->prob[i] /= sum;
  }

}


void eosBayesProbabilityRangeChange(eosBayes* d, int mode){

  int i;
  int j;
  int iofmax;
  int iofmin;
  float total = 0;
  float sigma1;
  float sigma2;
  eosBayesDistributionInfo info;

  DEBUGPRINT("eosBayesProbabilityRangeChangeStart\n");

  for(i=0;i<d->numDistribution;i++){
	DEBUGPRINT2("%d/%d loop\n",i+1,d->numDistribution);
	if(d->posterior[i].rangechangeflag==1){
	  if(d->posterior[i].n == 1){
		d->posterior[i].n = (int)(((d->posterior[i].max - d->posterior[i].min)/d->posterior[i].delta)+1);
		DEBUGPRINT1("SET n: %d\n",d->posterior[i].n);
	  }
	  DEBUGPRINT("Range change\n");
	  DEBUGPRINT1("Percentage of range:%f\n",d->posterior[i].percentageofrange);
	  DEBUGPRINT1("Namber of pertition:%d\n",d->posterior[i].nofpartitions);

	  total  = d->posterior[i].probofmaxposterior;
	  DEBUGPRINT1("start total:%f\n",total);
	  if(total>d->posterior[i].percentageofrange){
	    iofmin  = d->posterior[i].iofmaxposterior-1;
	    iofmax  = d->posterior[i].iofmaxposterior+1;
	    DEBUGPRINT1("iofmin:%d\n",iofmin);
	    DEBUGPRINT1("value:%f\n",d->posterior[i].value[iofmin]);
	    DEBUGPRINT1("iofmax:%d\n",iofmax);
	    DEBUGPRINT1("value:%f\n",d->posterior[i].value[iofmax]);
	    DEBUGPRINT1("end total:%f\n",total);
	  }else{
	    iofmin  =  d->posterior[i].iofmaxposterior;
	    iofmax  = d->posterior[i].iofmaxposterior;
	    for(j=1; total <= d->posterior[i].percentageofrange ;j++){
	      if(d->posterior[i].iofmaxposterior-j >= 0){
		iofmin  =  d->posterior[i].iofmaxposterior-j;
		total  +=  d->posterior[i].prob[iofmin];
		DEBUGPRINT1("iofmin:%d\n",iofmin);
		DEBUGPRINT1("value:%f\n",d->posterior[i].value[iofmin]);
	      }
	      if(d->posterior[i].iofmaxposterior+j < d->posterior[i].n){
		iofmax  = d->posterior[i].iofmaxposterior+j;
		total  += d->posterior[i].prob[iofmax];
		DEBUGPRINT1("iofmax:%d\n",iofmax);
		DEBUGPRINT1("value:%f\n",d->posterior[i].value[iofmax]);
	      }
	      DEBUGPRINT1("end total:%f\n",total);
	    } 
	  }

	  DEBUGPRINT("Set new prior\n");
	  info.min = d->posterior[i].value[iofmin];
	  info.max = d->posterior[i].value[iofmax];
	  info.delta = (info.max-info.min)/d->posterior[i].nofpartitions;
	  info.mode = 0;
	  info.mean =  d->posterior[i].valueofmaxposterior;

	  sigma1 = info.mean - info.min;
	  sigma2 = info.max  - info.mean;
	  if(sigma1>sigma2){
		info.sigma = sigma1;
	  }else if(sigma2>=sigma1){
		info.sigma = sigma2;
	  }
	  DEBUGPRINT6("min:%f max:%f delta:%f mode:%u mean:%f sigma:%f\n",info.min,info.max,info.delta,info.mode,info.mean,info.sigma);

	  eosBayesDistributionInit(&(d->prior[i]),&info,1);
	  eosBayesDistributionInit(&(d->posterior[i]),&info,1);
	  eosBayesDistributionInit(&(d->likelihood[i]),&info,1);
	  eosBayesDistributionInitialProbabilitySet(&(d->prior[i]), &info, 1);  
	  eosBayesDistributionInitialProbabilitySet(&(d->posterior[i]), &info, 1);  
	  DEBUGPRINT1("dist%d range was chaged\n",i);
	  leosBayesParameterOfMaxPosteriorGet(&(d->posterior[i]),0);
	  d->posterior[i].maxposteriorflag = 0;
	  d->posterior[i].rangechangeflag = 0;

	}
  }

}
