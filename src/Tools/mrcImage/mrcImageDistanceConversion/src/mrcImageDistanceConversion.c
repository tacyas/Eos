/*
# mrcImageDistanceConversion : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageDistanceConversion
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
#include "../inc/mrcImageDistanceConversion.h"
#include "lmrcImageDistanceConversion.h"

/*
Example:
typedef struct lmrcImageDistanceConversionInfo {
	float a;
	int   b;
} lmrcImageDistanceConversionInfo;

typedef enum lmrcImageDistanceConversionMode {
	a=0,
	b=1
} lmrcImageDistanceConversionMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageDistanceConversionInfo info;

	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

    mrcFileRead(&in, info.In , "in main" ,0);

	lmrcImageDistanceConversion(&in,&out,info.mode,info.form);

	mrcFileWrite(&out, info.Out ,"in main" ,0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr,"mode  0 : 4 Neighborhood. [default]\n");
	fprintf(stderr,"      1 : 8 Neighborhood.\n");
	fprintf(stderr,"\n");
	fprintf(stderr,"form  0 : Only distance conversion. [default]\n");
	fprintf(stderr,"      1 : Distance conversion + Making frame.\n");
	fprintf(stderr,"\n");
}
