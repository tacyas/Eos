/*
# mrcSinogramFET : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcSinogramFET
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
#include "lmrcSinogramFET.h"

int
main(int argc, char* argv[]) 
{
	mrcSinogramFETInfo info;
	lmrcSinogramFETInfo linfo;
	mrcImage in;
	mrcImage out;
	mrcImage OutC;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main",0);

	linfo.flagsm= info.flagsm;
	linfo.sm = info.sm;
	lmrcSinogramFET(&in,&out,linfo,0);

	mrcFileWrite(&out, info.Out, "in main" ,0);
	
	if(info.flagOutC){
		//mrcFileRead(&out, info.Out, "in main" ,0);
		lmrcSinogramFETc(&out, &OutC, 0);
		mrcFileWrite(&OutC, info.OutC, "in main" ,0);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-sm : move range of column smoothing by moving-average\n");
}
