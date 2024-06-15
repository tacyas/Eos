/*
# imodst2mrc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : imodst2mrc
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

/*
Example:
typedef struct limodst2mrcInfo {
	float a;
	int   b;
} limodst2mrcInfo;

typedef enum limodst2mrcMode {
	a=0,
	b=1
} limodst2mrcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	imodst2mrcInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	if(in.flagCCP4) {
		fprintf(stderr, "%d %d\n", in.Header.ContCCP4.NSYMBT, in.numTailer);
		in.Header.ContCCP4.NSYMBT = 0;
		in.ImageOffset = MRC_HEADER;
		in.numTailer=0;
		in.SymmetryOperator=NULL;
		in.HeaderLength.x = in.HeaderLength.x/in.HeaderM.x;
		in.HeaderLength.y = in.HeaderLength.y/in.HeaderM.y;
		in.HeaderLength.z = in.HeaderLength.x;
		in.HeaderM.x = 1;
		in.HeaderM.y = 1;
		in.HeaderM.z = 1;
	}

	if(info.flagOut) { 
		mrcFileWrite(&in, info.Out, "in main", 0);
	} else if(info.Output) {
		int i;
		char s[1024];
		mrcImage sec;

		for(i=0; i<in.HeaderN.z; i++) {
			sprintf(s, "%s.%03d", info.In, i);
			mrcImageSectionGet(&sec, &in, i, 0);
			sec.numTailer=0;
			sec.Header.ContCCP4.NSYMBT = 0;
			sec.ImageOffset = MRC_HEADER;
			mrcFileWrite(&sec, s, "in main", 0);
			fprintf(stderr, "%d %d %d %d %d\n", i, sec.Header.ContCCP4.NSYMBT, sec.numTailer, sec.ImageOffset, sec.BytePerImage);
		}
	} else {
		fprintf(stderr, "-O or -o is necessary \n");
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
