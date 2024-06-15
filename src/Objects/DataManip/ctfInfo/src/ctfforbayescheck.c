/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfforbayescheck ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfforbayescheck 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfforbayescheck ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eosBayes.h"
#include "../inc/ctfInfo.h"
#include "./ctffuncforbayes.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"





void ctfforbayescheckRvsValue(char* filename, float R, float value, int count){

  FILE* fpt;
  char s[1024];

  sprintf(s,"./%s%d.out",filename,count);

  if((fpt=fopen(s,"a"))==NULL){
	fprintf(stderr,"fopen error: %s\n",s);
	exit(1);
  }

  fprintf(fpt,"%f %f\n",R,value);

  fclose(fpt);
  
}


void ctfforbayescheckdifference(char* filename, defocuslikelihoodforbayes* l, eosBayesDistribution* d, int numLikelihood, int count, int mode){
  
  FILE* fpt;
  char s[1024];
  int i;
  int j;
  
  DEBUGPRINT("----difference check----\n");
  for(i=0;i<numLikelihood;i++){
	sprintf(s,"./%s%d[%d].out",filename,i,count);
	if((fpt=fopen(s,"a"))==NULL){
	  fprintf(stderr,"fopen error: %s\n",s);
	  exit(1);
	}
	for(j=0;j<d[i].n;j++){
	  fprintf(fpt,"%f %f\n",d[i].value[j],l->x[i][j]);
	}
	fclose(fpt);
  }
  
}


void ctfforbayescheckintensity(ctfforbayes ctf, eosBayesDistribution* d, int numLikelihood, int count, int mode){

  FILE* fpt;
  char s[1024];

  int length;

  int i;
  int j;

  int* L;
  
  DEBUGPRINT("----intensity check----\n");
  
  length = 1;
  for(i=0;i<numLikelihood;i++){
	length *= d[i].n;
  }

  L = (int *)malloc(sizeof(int)*numLikelihood);
  


	switch(mode){
	case 0:
	  for(i=0;i<length;i++){
		eosBayesloop(d,L,numLikelihood,i);
		sprintf(s,"./intensitycheck0/[%d][%d][%d].out",L[0],L[1],L[2]);
		if((fpt=fopen(s,"a"))==NULL){
		  fprintf(stderr,"fopen error: %s\n",s);
		  exit(1);
		}
		fprintf(fpt,"# d:%f A:%f B:%f\n",d[0].value[L[0]],d[1].value[L[1]],d[2].value[L[2]]);
		for(j=0;j<ctf.n;j++){
		  fprintf(fpt,"%f %f %f %f\n",ctf.R[j],ctf.I[j],ctf.Ii[j],ctf.I[j]-ctf.Ii[j]);
		}
		fprintf(fpt,"\n");
		fclose(fpt);	 
		}
	break;

	case 1:
	  for(i=0;i<length;i++){

		eosBayesloop(d,L,numLikelihood,i);

		if(L[0]==19){
		  sprintf(s,"./intensitycheck0/[%d][%d][%d][%d].out",L[0],L[1],L[2],L[3]);
		  if((fpt=fopen(s,"a"))==NULL){
			fprintf(stderr,"fopen error: %s\n",s);
			exit(1);
		  }
		  fprintf(fpt,"# d:%f A:%f B:%f k:%f\n",d[0].value[L[0]],d[1].value[L[1]],d[2].value[L[2]],d[3].value[L[3]]);
		  for(j=0;j<ctf.n;j++){
			fprintf(fpt,"%f %f %f %f\n",ctf.R[j],ctf.I[j],ctf.Ii[j],ctf.I[j]-ctf.Ii[j]);
		  }
		  fprintf(fpt,"\n");
		  fclose(fpt);
		}

	  }

	  break;
	default:
	  fprintf(stderr,"Please select mode again\n");
	  break;

	}


  free(L);
 

}


void ctfforbayescheckIntensityOfMaxPosterior(ctfforbayes ctf, eosBayesDistribution* d, int numDistribution, ctfInfo* info, int MTFmode, int Ainmode, int Intensitymode, int mode){

  FILE* fpt;
  FILE* fin;
  char s[1024];
  
  int i;

  float* parameter;
  float* intensity;
  float* meanintensity;

  parameter = (float*)malloc(sizeof(float)*numDistribution);
  intensity = (float*)malloc(sizeof(float)*ctf.n);
  meanintensity = (float*)malloc(sizeof(float)*ctf.n);  

  if(NULL == (fin = fopen("mean.spec","r"))){
	DEBUGPRINT("mean.spec was not opend\n");
	exit(EXIT_FAILURE);
  }

  i=0;
  while(NULL != __getStringData(s,"In IntensityRead",fin,stdout,3)){
	meanintensity[i] = atof(s);
	i++;
  }

  fclose(fin);
  DEBUGPRINT("Mean intensity read!!\n");


  DEBUGPRINT("----intesity of Max Prior check----\n");

  eosBayesParameterOfMaxPosteriorGet(d,numDistribution,0);

  for(i=0;i<numDistribution;i++){
	parameter[i] = d[i].valueofmaxposterior;
	fprintf(stderr,"parameter%d:%f\n",i,parameter[i]);
  }

  for(i=0;i<ctf.n;i++){

	switch(Intensitymode){
	case 0:
	  intensity[i] = ctfforbayesIntensityCalculation(parameter,ctf.R[i],info,MTFmode,Ainmode,mode);
	  break;
	  
	case 1:
	  intensity[i] = log(ctfforbayesIntensityCalculation(parameter,ctf.R[i],info,MTFmode,Ainmode,mode));
	  break;

	default:
	  fprintf(stderr,"\n");
	  break;
	}

    fprintf(stderr,"R:%f intensity:%f\n",ctf.R[i],intensity[i]);
  }


  sprintf(s,"./intensityofmaxposterior.out");
  if((fpt=fopen(s,"a"))==NULL){
	fprintf(stderr,"fopen error: %s\n",s);
	exit(1);
  }

  switch(MTFmode){
    /*
  case 0:

	fprintf(fpt,"# d:%f A:%f B:%f\n",d[0].valueofmaxposterior,d[1].valueofmaxposterior,d[2].valueofmaxposterior);
	break;
    */

  case 0:
	fprintf(fpt,"# d:%f A:%f B:%f k:%f\n",d[0].valueofmaxposterior,d[1].valueofmaxposterior,d[2].valueofmaxposterior,d[3].valueofmaxposterior);
	break;

  case 1:
	fprintf(fpt,"# d:%f A:%f B:%f k:%f m:%f Ain:%f\n",d[0].valueofmaxposterior,d[1].valueofmaxposterior,d[2].valueofmaxposterior,d[3].valueofmaxposterior,d[4].valueofmaxposterior,d[5].valueofmaxposterior);
	break;

  default:
	fprintf(stderr,"\n");
	break;

  }


  for(i=0;i<ctf.n;i++){
	fprintf(fpt,"%f %f %f %f\n",ctf.R[i],log(meanintensity[i]),intensity[i],log(meanintensity[i])-intensity[i]);
  }
  fprintf(fpt,"\n\n");
  fclose(fpt);
  
  free(parameter);
  free(intensity);
  free(meanintensity);

}
