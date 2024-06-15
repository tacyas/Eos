/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% defocuslikelihood ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : defocuslikelihood 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%defocuslikelihood ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "eosBayes.h"
#include "../inc/ctfInfo.h"
#include "./ctffuncforbayes.h"


#undef DEBUG
#undef DEBUG2
#include "genUtil.h"
#include "eosString.h"


void defocusLikelihoodInit(defocuslikelihoodforbayes* l, eosBayes* d, int mode){

  int i;
  int j;
  DEBUGPRINT("In defocusLikelihoodInit\n");

  if(mode==1){
	for(i=0;i<d->numLikelihood;i++){
	  free(l->x[i]);
	}
	free(l->width);
	free(l->x);
  }
  
  l->width = (double*)malloc(sizeof(double)*d->numLikelihood);
  l->x = (float**)malloc(sizeof(float*)*d->numLikelihood);
  for(i=0;i<d->numLikelihood;i++){
	l->x[i] = (float*)malloc(sizeof(float)*d->likelihood[i].n);
  }
  DEBUGPRINT("x and width init\n");  

  l->mode0 = 0;
  l->mode1 = 0;
  l->mode2 = 0;
  
}


void ctfforbayesXofLikelihoodCalculation(defocuslikelihoodforbayes* l, ctfforbayes* ctf, eosBayes* d, int* L, int count, int mode){


  DEBUGPRINT("In ctfforbayesXofLikelihoodCaluculation\n");

  switch(l->mode0){

  case difference:
	DEBUGPRINT("xmode is difference\n");
	ctfforBayesDifferenceCalculation(l,ctf,d->likelihood,d->numLikelihood,L,count,mode);
	break;

  case correlation:
	/*
	ctfforBayesCorrelationCalculation();
	*/
	fprintf(stderr,"This mode hasn't been inserted yet.\n");
	break;

  default:
	fprintf(stderr,"Please select mode again\n");
	break;

  }
}



void defocusLikelihood(defocuslikelihoodforbayes* l, ctfforbayes* ctf, eosBayes* d, int count, int mode){

  DEBUGPRINT("In defocuslikelihood\n");

  switch(l->mode1){
	
  case mean:
	DEBUGPRINT("widthmode is mean\n");
	ctfforBayesMeanCalculation(l,d->likelihood,d->numLikelihood,count,0);
	break;

  case median:
	/*
	ctfforBayesmedianculuculartion();
	*/
	fprintf(stderr,"This mode hasn't been inserted yet.\n");
	break;

  default:
	fprintf(stderr,"Please select mode again\n");

  }


  switch(l->mode2){
  
  case lorentz:
	DEBUGPRINT("likelihoodmode is lorentz\n");
	defocusLikelihoodCalculationLorentz(l, d->likelihood, d->numLikelihood, count, 0);
	break;
	
  default:
	fprintf(stderr,"Please select mode again\n");
	break;
	
  }


}



void ctfforBayesDifferenceCalculation(defocuslikelihoodforbayes* l, ctfforbayes* ctf, eosBayesDistribution* d, int numLikelihood, int* L, int count, int mode){

  float difference;
  int length;

  int i;

  DEBUGPRINT("In ctfforBayesDifferenceCaluculation\n");


  DEBUGPRINT("difference caluculattion start\n");

	difference = 0;
	for(i=0;i<ctf->n;i++){
	  if((ctf->rmin<=ctf->R[i]) && (ctf->R[i]<=ctf->rmax)){
		difference += (ctf->I[i]-ctf->Ii[i])*(ctf->I[i]-ctf->Ii[i]);
	  }
	}

#ifdef DEBUG2
	DEBUGPRINT3("L[0]:%d L[1]:%d L[2]:%d\n",L[0],L[1],L[2]);
#endif

	for(i=0;i<numLikelihood;i++){
	  l->x[i][L[i]] += difference;
	}


  DEBUGPRINT("difference caluculattion stop\n");

  
}



void ctfforBayesMeanCalculation(defocuslikelihoodforbayes* l, eosBayesDistribution* d, int numLikelihood, int count, int mode){

  int i;
  int j;


  DEBUGPRINT("In ctfforBayesMeanculculation\n");

  for(i=0;i<numLikelihood;i++){
	for(j=0;j<d[i].n;j++){
	  l->width[i] += l->x[i][j];
	}
	l->width[i] = l->width[i]/d[i].n;
	DEBUGPRINT2("width[%d]:%f\n",i,l->width[i]);
  }

  
}



void defocusLikelihoodCalculationLorentz(defocuslikelihoodforbayes* l, eosBayesDistribution* d, int numLikelihood, int count, int mode){
  
  float* sum;

  int i;
  int j;

  DEBUGPRINT("In defocuslikelihoodcaluculationLorentz \n");

  sum = (float*)malloc(sizeof(float)*numLikelihood);

  DEBUGPRINT("sum malloc\n");
  for(i=0;i<numLikelihood;i++){
	sum[i] = 0;
	for(j=0;j<d[i].n;j++){
	  d[i].prob[j] = 0;
	}
  }
  DEBUGPRINT("prob init\n");


  DEBUGPRINT("likelihood culcu\n");
  DEBUGPRINT("append\n");
  for(i=0;i<numLikelihood;i++){
	for(j=0;j<d[i].n;j++){
	  d[i].prob[j] = (float)(l->width[i]/(l->x[i][j]+l->width[i]));
	  sum[i] += d[i].prob[j];
	  }
	}
	
  /*
	original likelihood function is 1/(difference+exp(-6))
  */

  for(i=0;i<numLikelihood;i++){
	DEBUGPRINT2("%dlikelihood.n:%d\n",i,d[i].n);
	for(j=0;j<d[i].n;j++){
	  d[i].prob[j] /= sum[i];
	  DEBUGPRINT2("likelihood%d:%f\n",i,d[i].prob[j]);
	}
  }
  
  DEBUGPRINT("sum free\n");
  free(sum);

}
