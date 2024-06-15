/*
# mrcImage3DCTFObservation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage3DCTFObservation
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
#include "ctfInfo.h"

typedef struct lmrcImage3DCTFObservationInfo {
	float a;
	int   b;
} lmrcImage3DCTFObservationInfo;

/*
typedef enum lmrcImage3DCTFObservationMode {
	a=0,
	b=1
} lmrcImage3DCTFObservationMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage3DCTFObservationInfo info;
	mrcImage in;
	mrcImage out;
	ctfInfo  ctf;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, in.In, "in main", 0);  
	memoryClear(&ctf, sizeof(ctf), (char)0);
	ctfInfoRead(info.fptIn, &ctf, "", 0);


	mrcFileRead(&in, in.In, "in main", 0);  



	mrcFileWrite(&out, in.Out, "in main", 0);  
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
