/*
# mrcImageTrans : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageTrans
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
#include "lmrcImageMove.h"

/*
Example:
typedef struct lmrcImageTransInfo {
	float a;
	int   b;
} lmrcImageTransInfo;

typedef enum lmrcImageTransMode {
	a=0,
	b=1
} lmrcImageTransMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageTransInfo info;
	mrcImage in;
	mrcImage out;
	Matrix3D mat;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	matrix3DFileRead(info.fptInMatrix, mat);

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageTrans(&out, &in, mat, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode: Interpolation mode\n");
}
