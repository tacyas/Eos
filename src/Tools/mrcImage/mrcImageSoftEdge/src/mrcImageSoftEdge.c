/*
# mrcImageSoftEdge : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSoftEdge
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
#include "lmrcImageSoftEdge.h"

int
main(int argc, char* argv[]) 
{
	mrcImageSoftEdgeInfo info;
	lmrcImageSoftEdgeInfo linfo;
    mrcImage in;
    mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    linfo.width   =  info.width;
    linfo.envelop =  info.envelop;

    mrcFileRead(&in, info.In, "in main", 0);

    lmrcImageSoftEdge(&out, &in, linfo, info.mode);

    mrcFileWrite(&out, info.Out, "in main", 0);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
