/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNullImageCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageNullImageCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNullImageCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrcImageNullImageCreateInfo {
	float a;
	int   b;
} lmrcImageNullImageCreateInfo;

typedef enum lmrcImageNullImageCreateMode {
	a=0,
	b=1
} lmrcImageNullImageCreateMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageNullImageCreateInfo info;
	mrcImage ref;
	mrcImage out;
	int x,y,z;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcDefaultHeaderValueSet(&out);
	out.HeaderN.x = info.Nx;
	out.HeaderN.y = info.Ny;
	out.HeaderN.z = info.Nz;
	out.HeaderMode = info.Mode;
	out.HeaderM.x = 0.0;
	out.HeaderM.y = 0.0;
	out.HeaderM.z = 0.0;

	if(info.flagRef) {
		mrcFileRead(&ref, info.Ref, "in main", 0);
		out.Header.Cont = ref.Header.Cont;
	}	
	if(info.Default) {
		mrcDefaultHeaderValueSetOnlyFixedValue(&out);
	}
	if(info.flagMode) {
		out.HeaderMode = info.Mode;
	}
	if(info.flagNx) {
		out.HeaderN.x = info.Nx;
	}
	if(info.flagNy) {
		out.HeaderN.y = info.Ny;
	}
	if(info.flagNz) {
		out.HeaderN.z = info.Nz;
	}
	if(info.flagd) {
		out.HeaderLength.x = info.d;  
		out.HeaderLength.y = info.d;
		out.HeaderLength.z = info.d;
	}

	mrcInit(&out ,NULL);
	for(z=0; z<out.HeaderN.z; z++) {
	for(y=0; y<out.HeaderN.y; y++) {
	for(x=0; x<out.HeaderN.x; x++) {
		mrcPixelDataSet(&out, x, y, z, info.Value, mrcPixelRePart);
	}
	}
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-r is used to define a reference header.\n");
	fprintf(stderr, "-Nx etc. are used preferentially.\n");
}
