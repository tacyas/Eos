/*
# mrcRefEstimate.c  1.1
# The latest update : 09/20/96 at 16:03:38
#
#@(#) mrcRefEstimate ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcRefEstimate
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcRefEstimate ver1.1; Date:96/09/20 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h" 

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefEstimateInfo info;

/* variables */
	mrcImage in;
	double avr,sd;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0); 
	avr =  lmrcRefSqrAverage(&in); 
	sd = lmrcRefStandardDeviation(&in);
	fprintf(stdout,"average of Square data value =%f \n",avr);
	fprintf(stdout,"square root = %f\n" ,sqrt(avr) );
	fprintf(stdout,"Standard Deviation = %f\n" ,sd );
	exit(EXIT_SUCCESS);

}

void
additionalUsage()
{
}

