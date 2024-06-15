/*
# mrcImageSphereCheck : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSphereCheck
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

typedef struct lmrcImageSphereCheckInfo {
	float a;
	int   b;
} lmrcImageSphereCheckInfo;
/*
typedef enum lmrcImageSphereCheckMode {
	a=0,
	b=1
} lmrcImageSphereCheckMode;
*/

extern void lmrcImageSphereCheck(lmrcImageSphereCheckInfo* linfo, mrcImage* in, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageSphereCheckInfo info;
	lmrcImageSphereCheckInfo linfo;

	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageSphereCheck(&linfo, &in, info.mode);

	lmrcImageSphereCheckPrint(info.fptOut, linfo, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}



void
lmrcImageSphereCheck(lmrcImageSphereCheckInfo* linfo, mrcImage* in, int mode)
{

}


void
lmrcImageSphereCheckPrint(lmrcImageSphereCheckInfo* linfo, mrcImage* in, int mode)
{

}


