/*
# mrcImageConnectivityNumberCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageConnectivityNumberCalc
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
#include "../inc/mrcImageConnectivityNumberCalc.h"
#include "lmrcImageConnectivityNumberCalc.h"

/*
Example:
typedef struct lmrcImageConnectivityNumberCalcInfo {
	float a;
	int   b;
} lmrcImageConnectivityNumberCalcInfo;

typedef enum lmrcImageConnectivityNumberCalcMode {
	a=0,
	b=1
} lmrcImageConnectivityNumberCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageConnectivityNumberCalcInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start.\n");

	mrcFileRead(&in, info.In , "in main" ,0);

	lmrcImageConnectivityNumberCalc(&in, &out, info.mode, info.form, info.invers);
	
	mrcFileWrite(&out, info.Out ,"in main" ,0);

	DEBUGPRINT("Program End.\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode   0 : Four Neighborhood. [default] : For 2 Dimension. \n" );
	fprintf(stderr, "       1 : Eight Nieghborhood.          : \n");
	fprintf(stderr, "       2 : Eighteen Neighborhood.       : For 3 Dimension. \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "form   0 : No change. [default]      \n" );
	fprintf(stderr, "       1 : Spread of pixel data 1.   \n" );
	fprintf(stderr, "       2 : Thin of pixel data 1.     \n" );
	fprintf(stderr, "       3 : Frame of image by data 1. \n" );
	fprintf(stderr, "\n");
	fprintf(stderr, "invers 0 : The object is 1 value. [default] \n");
	fprintf(stderr, "       1 : The background is 1 value.       \n");
	fprintf(stderr, "\n");
}
