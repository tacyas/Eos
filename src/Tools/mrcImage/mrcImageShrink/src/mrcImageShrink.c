#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"


int
main(int argc, char* argv[]) 
{
        mrcImageShrinkInfo info;
	mrcImage dst;
	mrcImage src;
	mrcImageParaTypeIntegerCoord S;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	
        mrcFileRead(&src, info.In, "in main", 0);
	if (info.flagS){
	  S.x = S.y = S.z = info.S ;
	} else {
	  S.x = info.Sx;
	  S.y = info.Sy;
	  S.z = info.Sz;
	}
	if (src.HeaderN.x == 1){
	  S.x = 1;
	}
	if (src.HeaderN.y == 1){
	  S.y = 1;
	}
	if (src.HeaderN.z == 1){
	  S.z = 1;
	}
        lmrcImageShrink(&dst, &src, S, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);
}


void
additionalUsage()
{
	fprintf(stderr, "---- Note -----\n");
	fprintf(stderr, "If S = 2, N.x -> N.x/2 and Length.x -> 2*Length.x.\n");
	fprintf(stderr, "Image 0 0 1 1 -> Image 0   1 \n");
	fprintf(stderr, "      0 0 1 1                \n");
	fprintf(stderr, "      0 0 1 1          0   1 \n");
	fprintf(stderr, "      0 0 1 1                \n");
	fprintf(stderr, "Option S is stronger than option Sx, Sy, Sz\n");
}

