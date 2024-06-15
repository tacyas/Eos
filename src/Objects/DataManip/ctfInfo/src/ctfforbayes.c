/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfforbayes ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfforbayes 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfforbayes ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "eosBayes.h"
#include "../inc/ctfInfo.h"
#include "./ctffuncforbayes.h"




#define DEBUG
#include "genUtil.h"
#include "eosString.h"



void ctfforbayesInit(FILE* fpt, ctfforbayes* ctf, int mode){

	char s[1024];

	ctf->n = 0;
	while(NULL != __getStringData(s,"In ctfforbayesInit",fpt,stdout,3)){
		ctf->n++;
	}
	DEBUGPRINT1("ctf.n:%d\n",ctf->n);
	ctf->R = (float*)malloc(sizeof(float)*ctf->n);

	fseek(fpt,0,SEEK_SET);

}


void intensityforbayesInit(intensityforbayes* intensity, int Inum, int MTFmode, int Ainmode, int mode){

  intensity->MTFmode = MTFmode;
  intensity->Ainmode = Ainmode;

  intensity->normI = (float*)malloc(sizeof(float)*Inum);
  intensity->logI = (float*)malloc(sizeof(float)*Inum);

  intensity->normII = (float*)malloc(sizeof(float)*Inum);
  intensity->logII = (float*)malloc(sizeof(float)*Inum);

  intensity->mode = 1;

  DEBUGPRINT1("Intensityinit finitsh! Inum:%d\n",Inum);
  DEBUGPRINT1("---MTFmode:%d---\n",MTFmode);
  DEBUGPRINT1("---Ainmode:%d---\n",Ainmode);

}



void spatialfrequencyRead(FILE* fpt, ctfforbayes* ctf, float rmax, float rmin, int mode){

	int i;
	char s[1024];
	
	i=0;
	while(NULL != __getStringData(s,"In spatialfrequencyRead",fpt,stdout,3)){
		ctf->R[i] = atof(s);
		i++; 
	}

	ctf->rmax = rmax;
	ctf->rmin = rmin;

	DEBUGPRINT2("Rmax:%f Rmin:%f\n", ctf->rmax,ctf->rmin);

}


void intensityRead(char* filename, intensityforbayes* intensity, int count, int mode){
	FILE* fin;
	int i;
	char s[1024];

	if( NULL == (fin = fopen(filename, "r"))){
		DEBUGPRINT1("%s was not opend\n",filename);
		exit(EXIT_FAILURE);
	}

	i=0;
	while(NULL != __getStringData(s,"In IntensityRead",fin,stdout,3)){
		intensity->normI[i] = atof(s);
		intensity->logI[i] = log(intensity->normI[i]);
		i++;
	}

	fclose(fin);

	DEBUGPRINT1("Intensity read!!: %dtimes\n",count+1);

}


void intensitySet(ctfforbayes* ctf, intensityforbayes* intensity, int mode){
  
  switch(intensity->mode){

  case normal:
	/*Normal*/
	//DEBUGPRINT("----Intensity mode Normal----\n");
	  ctf->I = intensity->normI;
	  ctf->Ii = intensity->normII;
	break;

  case logarithm:
	/*Log*/
	//DEBUGPRINT("----Intensity mode Log----\n");
	  ctf->I = intensity->logI;
	  ctf->Ii = intensity->logII;
	break;
	
  default:

	fprintf(stderr,"\n");
	break;

  }

}



void ctfFunctionforbayes(ctfforbayes* ctf, intensityforbayes* intensity, eosBayes* d, ctfInfo* info, defocuslikelihoodforbayes* l, int count, int mode){

	float* parameter;
	int*  L;

	//	char s[1024];
	//	FILE* fpt;

	int   length;

	int   i;
	int   j;
	int   k;

	DEBUGPRINT("In ctf\n");

	parameter = (float*)malloc(sizeof(float)*d->numLikelihood);

	length = 1;
	for(i=0;i<d->numLikelihood;i++){
	  length *= d->likelihood[i].n;
	}
	
	//DEBUGPRINT("L malloc\n");
	
	L = (int *)malloc(sizeof(int)*d->numLikelihood);
	
	//DEBUGPRINT("L malloc\n");


	for(i=0;i<d->numLikelihood;i++){
	  l->width[i] = 0;
	  for(j=0;j<d->likelihood[i].n;j++){
		l->x[i][j] = 0;
	  }
	}


	DEBUGPRINT("likelihood culcuration start\n");
	for(i=0;i<length;i++){
	  eosBayesloop(d->likelihood,L,d->numLikelihood,i);

	  for(k=0;k<d->numLikelihood;k++){
		if(d->posterior[k].maxposteriorflag == 1){ 
		  parameter[k] = d->posterior[k].valueofmaxposterior;
		}else{
		  parameter[k] = d->likelihood[k].value[L[k]];
		}
	  }
	  //DEBUGPRINT3("%d:%d:%d\n",L[0],L[1],L[2]);
	  /*
	  sprintf(s,"./intensitycheck0/[%.2f][%.2f][%.2f][%.2f].out",parameter[0],parameter[1],parameter[2],parameter[3]);
	  if((fpt=fopen(s,"a"))==NULL){
	    fprintf(stderr,"fopen error: %s\n",s);
	    exit(1);
	  }
	  */

	  for(j=0;j<ctf->n;j++){
	    intensity->normII[j] = ctfforbayesIntensityCalculation(parameter,ctf->R[j],info,intensity->MTFmode,intensity->Ainmode,mode);
	    //fprintf(stderr,"II: %f\n",intensity->normII[j]);
	    intensity->logII[j]  = log(intensity->normII[j]);
	  }

	  /*
	  fprintf(fpt,"# d:%f A:%f B:%f k:%f\n",parameter[0],parameter[1],parameter[2],parameter[4]);
	  for(j=0;j<ctf->n;j++){
	    fprintf(fpt,"%f %f\n",ctf->R[j],intensity->normII[j]);
	  }
	  fprintf(fpt,"\n");
	  fclose(fpt);
	  */

	  intensitySet(ctf,intensity,0);
	  ctfforbayesXofLikelihoodCalculation(l,ctf,d,L,0,0);
	  
	}

	defocusLikelihood(l,ctf,d,i,0);

	DEBUGPRINT("likelihood culcuration end\n");
	LikelihoodChangeCheck(d,count,0);
	
	free(parameter);
	free(L);
	
}


float ctfforbayesIntensityCalculation(float* parameter, float R, ctfInfo* info, int MTFmode, int Ainmode, int mode){

	float S;
	float N;
	float k;
	float CTF;
	float MTF;
	float A;
	float B;

	A = 0;
	B = 0;
	k = 0;

	info->defocus = parameter[0];
	info->I0 = parameter[1];
	info->WhiteNoise = parameter[2]/parameter[1];

	switch(MTFmode){
	  
	case 0:
	  break;
	  
	case 1:
	  info->MTFMode = 0;
	  info->BofMTF = parameter[4];
	  break;
	  
	default:
	  fprintf(stderr,"\n");
	  break;
	  
	}

	switch(Ainmode){
	  
	case 0:
	  break;
	  
	case 1:
	  info->Ain = parameter[5];
	  break;
	  
	default:
	  fprintf(stderr,"\n");
	  break;
	  
	}

//	CTF = ctfFunction(info, R, 0);
//	MTF = ctfMTFFunction(info, R, 0);

	/*value check*/

	switch(mode){

	case 0:
	  //DEBUGPRINT("----ctfmode 0----\n");
	 // A = S*S;
	  A = ctfSignalPowerFunction(info,R,0);
	  break;
	  
	case 1:
	  //  DEBUGPRINT("----ctfmode 1----\n");
	  //  DEBUGPRINT("signalcalculation\n");
	  k = parameter[3];
	  info->MolecEnv = 0;
	  //A = S*S*exp(-2*(k*k)*(R*R));
	  A = ctfSignalPowerFunction(info,R,0)*exp(-2*(k*k)*(R*R));
	  break;

	default:
	  fprintf(stderr,"\n");
	  break;

	}

	//DEBUGPRINT("noisecalculation\n");
	B = ctfNoisePowerFunction(info,R,0);

	//	fprintf(stderr,"R:%f,p[1]:%f,p[2]%f,p[3]:%f,p[4]:%f,MTF:%f\n",R,info->defocus,S,N,k,m);

	//DEBUGPRINT("return\n");
	return A+B;

}


void ctfforbayesFree(ctfforbayes* ctf, intensityforbayes* intensity, defocuslikelihoodforbayes* likelihood, int numLikelihood){
  
  int i;
  
  DEBUGPRINT("In ctfforbayesfree\n");

  for(i=0;i<numLikelihood;i++){
    free(likelihood->x[i]);
  }
  
  free(likelihood->width);
  free(likelihood->x);

  free(ctf->R);
  
  free(intensity->normI);
  free(intensity->logI);

  free(intensity->normII);
  free(intensity->logII);

  DEBUGPRINT("compreated ctfforbayesfree\n");

}
