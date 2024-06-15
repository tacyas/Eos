/*
# mrcImageOneLineSimilarityCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageOneLineSimilarityCalc
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
#include "lmrcImageOneLineSimilarityCalc.h"

int
main(int argc, char* argv[]) 
{
	mrcImageOneLineSimilarityCalcInfo info;
	lmrcImageOneLineSimilarityCalcInfo linfo;
	mrcImage in1;
	mrcImage in2;
	double ans;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in1,  info.In1 , "in main" ,0);
	mrcFileRead(&in2,  info.In2 , "in main" ,0);

	linfo.shiftflag = info.shiftflag;
	linfo.shiftrange = info.value;
	linfo.methodmode = info.methodmode;

	ans=lmrcImageOneLineSimilarityCalc(&in1, &in2, linfo);

	fprintf(stdout,"%f\n",ans);
	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
