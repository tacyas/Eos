/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRefScaleChangeWithPad ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRefScaleChangeWithPad
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageRefScaleChangeWithPad ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <stdlib.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrcImageRefScaleChangeWithPadInfo {
	float a;
	int   b;
} lmrcImageRefScaleChangeWithPadInfo;

typedef enum lmrcImageRefScaleChangeWithPadMode {
	a=0,
	b=1
} lmrcImageRefScaleChangeWithPadMode;
*/

void
main(int argc, char* argv[]) 
{
	char command[200];
	mrcImageRefScaleChangeWithPadInfo info;
	mrcImage in;
	mrcImage ref;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	if(!(   in.HeaderLength.x==ref.HeaderLength.x
	      &&in.HeaderLength.y==ref.HeaderLength.y
		  &&in.HeaderLength.z==ref.HeaderLength.z)) {
		fprintf(stderr, "Different size between in(%ld,%ld,%ld) and ref(%ld,%ld,%ld)\n"
						,in.HeaderLength.x, ref.HeaderLength.x
						,in.HeaderLength.y, ref.HeaderLength.y
						,in.HeaderLength.z, ref.HeaderLength.z);
		exit(EXIT_FAILURE);
	}

	if(    in.HeaderN.x < ref.HeaderN.x
	     &&in.HeaderN.y < ref.HeaderN.y
		 &&in.HeaderN.z < ref.HeaderN.z) {
		fprintf(stderr, "A in(%ld,%ld,%ld) is smaller than ref(%ld,%ld,%ld)\n"
						,in.HeaderN.x, ref.HeaderN.x
						,in.HeaderN.y, ref.HeaderN.y
						,in.HeaderN.z, ref.HeaderN.z);
		exit(EXIT_FAILURE);
	}

		sprintf( command, "%s %s %s %s %s %s %d %s %d %s","mrcImagePad","-i",info.In,"-o",info.Out,"-W",(int)info.width,"-H",(int)in.HeaderN.y,"-m 1");
		system(command);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
