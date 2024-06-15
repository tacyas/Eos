/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFilteringbyFileForVariance ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFilteringbyFileForVariance
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFilteringbyFileForVariance ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"



void
main(int argc, char* argv[]) 
{
/* variables */
	mrcImageFilteringbyFileForVarianceInfo info;
	mrcImage in;
	mrcImage out;
	FILE* fpfilter;
	double** filterval;
	int filternum,i;
	double dummy;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if((fpfilter=fopen(info.Filter,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	filternum=0;
	while(fscanf(fpfilter,"%lf %lf \n",&dummy,&dummy )!=EOF ){
	  filternum++;
	}
	if ( ( filterval = (double** )malloc(sizeof(double*)*(filternum+1)) ) == NULL ){
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	for (i=0 ; i<=filternum ;i++){
	  if ( ( filterval[i] = (double* )malloc(sizeof(double)*2) ) == NULL ){
	    fprintf(stderr ,"Enough memoly is not available.");
	    exit(EXIT_FAILURE);
	  }
	} 
	filternum=0;
	fclose(fpfilter);
	if((fpfilter=fopen(info.Filter,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	while(fscanf(fpfilter,"%lf %lf \n",&filterval[filternum][0],&filterval[filternum][1] )!=EOF ){
	  filternum++;
	}
	filterval[filternum][0] = -1;
	lmrcImageFilteringbyFileForVariance(&out ,&in ,filterval ,0); 
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}


void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}





