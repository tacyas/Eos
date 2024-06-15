/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesWrite ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesWrite 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesWrite ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/eosBayes.h"

#undef DEBUG
#include "genUtil.h"


void eosBayesDistributionWrite(FILE* fpt, eosBayesDistribution* d, int mode){

	int i;
	
	switch(mode){
	
		case 1:
				fprintf(fpt,"#dist:\t%f\t%f\t%f\t%d\n",d->min,d->max,d->delta,d->n);
				DEBUGPRINT4("#dist:\t%f\t%f\t%f\t%d\n",d->min,d->max,d->delta,d->n);
				for(i=0;i<d->n;i++){
					fprintf(fpt,"%f\t%f\n",d->value[i],d->prob[i]);
					DEBUGPRINT2("%f %f\n",d->value[i],d->prob[i]);
				}

				break;
		case 2:
				break;

		default:
				fprintf(stderr,"");
				break;

	}

}


void eosBayesPriorWrite(eosBayes* d, int mode){

  FILE* fpt;
  int i;
  char s[1024];

  for(i=0;i<d->numDistribution;i++){
	sprintf(s,"%s%d.out","./prior",i);
	if((fpt=fopen(s,"w"))==NULL){
	  fprintf(stderr,"fopen error: %s\n",s);
	  exit(1);
	}
	eosBayesDistributionWrite(fpt,&(d->prior[i]),1);
	fclose(fpt);
  }
  
}

void eosBayesPosteriorWrite(eosBayes* d, int mode){

  FILE* fpt;
  int i;
  char s[1024];

  for(i=0;i<d->numDistribution;i++){
	sprintf(s,"%s%d.out","./posterior",i);
	if((fpt=fopen(s,"w"))==NULL){
	  fprintf(stderr,"fopen error: %s\n",s);
	  exit(1);
	}
	eosBayesDistributionWrite(fpt,&(d->posterior[i]),1);
	fclose(fpt);
  }

}



void eosBayesLikelihoodWrite(eosBayes* d, int mode){

  FILE* fpt;
  int i;
  char s[1024];

  for(i=0;i<d->numDistribution;i++){
	sprintf(s,"%s%d.out","./likelihood",i);
	if((fpt=fopen(s,"w"))==NULL){
	  fprintf(stderr,"fopen error: %s\n",s);
	  exit(1);
	}
	eosBayesDistributionWrite(fpt,&(d->likelihood[i]),1);
	fclose(fpt);
  }

}



void eosBayesWrite(FILE* fpt, eosBayes* d, int mode){
}


void DistributionChangeCheck(eosBayes* d, int count, int mode){

  FILE* fpt;
  int i;
  int j;
  char s[1024];

  for(i=0;i<d->numDistribution;i++){
	if(d->prior[i].n!=1){
	  sprintf(s,"%s%d_%d.out","./dist",i,count);
	
	  switch(mode){

	  case 0:
	  
		/*write prior prob*/
		if((fpt=fopen(s,"a"))==NULL){
		  fprintf(stderr,"fopen error: %s\n",s);
		  exit(1);
		}
	  
		fprintf(fpt,"#dist: %f\t%f\t%f\t%d\n",d->prior[i].min,d->prior[i].max,d->prior[i].delta,d->prior[i].n);
		for(j=0;j<d->prior[i].n;j++){
		  fprintf(fpt,"%f %f\n",d->prior[i].value[j],d->prior[i].prob[j]);
		}
		fprintf(fpt,"\n\n");  
	  
		fclose(fpt);
		break;
	  
	  case 1:
		/*write posterior prob*/
		if((fpt=fopen(s,"a"))==NULL){
		  fprintf(stderr,"fopen error: %s\n",s);
		  exit(1);
		}
	  
		for(j=0;j<d->posterior[i].n;j++){
		  fprintf(fpt,"%f %f\n",d->posterior[i].value[j],d->posterior[i].prob[j]);
		}
		fprintf(fpt,"\n\n");
		
		fclose(fpt);
		break;


	  default:
		fprintf(stderr,"\n");
		break;
	  
	  
	  } 
	}

  }
  
}


void LikelihoodChangeCheck(eosBayes* d, int count, int mode){
  
  FILE* fpt;
  int i;
  int j;
  char s[1024];

  for(i=0;i<d->numDistribution;i++){
	if(d->prior[i].n!=1){
	  sprintf(s,"%s%d_%d.out","./likelihood",i,count);
	
	  if((fpt=fopen(s,"a"))==NULL){
		fprintf(stderr,"fopen error: %s\n",s);
		exit(1);
	  }

	  for(j=0;j<d->likelihood[i].n;j++){
		fprintf(fpt,"%f %f\n",d->likelihood[i].value[j],d->likelihood[i].prob[j]);
	  }
	  fprintf(fpt,"\n\n");
	  fclose(fpt);
	  
	}
  }
  
}
