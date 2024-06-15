/*
# mrc2png : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrc2png
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
#include "pngFile.h"

/*
Example:
typedef struct lmrc2pngInfo {
	float a;
	int   b;
} lmrc2pngInfo;

typedef enum lmrc2pngMode {
	a=0,
	b=1
} lmrc2pngMode;
*/

int
main(int argc, char* argv[]) 
{
	mrc2pngInfo info;
	lmrc2pngInfo linfo;
	mrcImage mrc;
	pngFile  png;
	int z;
	char s[1024];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&mrc, info.In, "in main", 0);

	if(mrc.HeaderN.z<=1) {	
		linfo.z = 0;
		lmrc2png(&png, &mrc, &linfo, info.mode); 
		pngFileWrite(&png, info.Out, 0); 
	} else if(info.flagz) {
		linfo.z = info.z;
		lmrc2png(&png, &mrc, &linfo, info.mode); 
		pngFileWrite(&png, info.Out, 0); 
	} else {
		for(z=0; z<mrc.HeaderN.z; z++) {
			sprintf(s, info.Format, info.Out, z); 
			linfo.z = z;
			lmrc2png(&png, &mrc, &linfo, info.mode); 
			pngFileWrite(&png, s, 0); 
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
