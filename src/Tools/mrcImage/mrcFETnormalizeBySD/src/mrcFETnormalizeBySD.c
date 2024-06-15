/*
# mrcFETnormalizeBySD : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFETnormalizeBySD
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcFETnormalizeBySD.h"

/*
Example:
typedef struct lmrcFETnormalizeBySDInfo {
	float a;
	int   b;
} lmrcFETnormalizeBySDInfo;

typedef enum lmrcFETnormalizeBySDMode {
	a=0,
	b=1
} lmrcFETnormalizeBySDMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcFETnormalizeBySDInfo info;
	lmrcFETnormalizeBySDInfo linfo;
	mrcImage readSD;
	mrcImage writeSD;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.InList = info.fptIn;
	if(info.flagInSample)
		linfo.InSampleList = info.fptInSample;
	else
		linfo.InSampleList = info.fptIn;
	if(info.flagreadSD){
		mrcFileRead(&readSD,info.readSD,"in main",0);
		linfo.readSD = &readSD;
	}
	linfo.flagReadSD = info.flagreadSD;
	if(info.flagwriteSD){
		linfo.writeSD = &writeSD;
	}
	linfo.flagWriteSD = info.flagwriteSD;
	if(info.flagOut)
		linfo.Out = &out;
	linfo.flagOut = info.flagOut;

	lmrcFETnormalizeBySD(linfo,0);

	if(info.flagwriteSD) mrcFileWrite(linfo.writeSD, info.writeSD, "in main", 0);
	if(info.flagOut) mrcFileWrite(linfo.Out, info.Out, "in main", 0); 

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n----- Additional Usage -----\n");
	fprintf(stderr, "-is  :[inputsample] is FileList for SDcalculation.\n");
	fprintf(stderr, "           use when the inputFileList is large\n");
	fprintf(stderr, "-rSD : to use SDdata(without calculate) mrc format\n");
	fprintf(stderr, "-wSD : write out the SDdata as mrc format\n");
	fprintf(stderr, "       this file can be used next normalize with \"-rSD\"command.\n");
	fprintf(stderr, "-o   : save all normalized data into one mrcImage.\n");
	fprintf(stderr, "       do not use when the inputFileList is large\n\n");
}
