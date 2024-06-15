#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#define DEBUG
#include "genUtil.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageSmoothingInfo info;
	mrcImage dst;
	mrcImage src;
	lmrcImageSmoothingInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

    __verbose__ = info.verbose;
    switch(info.mode2%2){
		case 0: {
	  		linfo.sx = info.sx;
	  		linfo.sy = info.sy;
	  		linfo.sz = info.sz;
	  		linfo.mode = info.mode;
	  		break;
		}
		case 1: {
	  		linfo.sx = linfo.sy = linfo.sz = info.r;
	  		linfo.mode = info.mode;
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode2: %d\n", info.mode2);
			exit(EXIT_FAILURE);
		}
	}
	linfo.sigma = info.sigma;

	mrcFileRead(&src, info.In, "in main", 0);

	if (src.HeaderN.z == 1){
	  linfo.sz=1;
	  DEBUGPRINT1("%f \n",linfo.sz);
	}

	DEBUGPRINT1("%d ",info.mode2);

	if(1==info.times) {
		lmrcImageSmoothing(&dst, &src, &linfo, info.mode2);
	} else {
		mrcImage tmp;
		mrcImageParaTypeRealCoord to;
		to.x = to.y = to.z = 0;
		for(i=0; i<info.times; i++) {
			lmrcImageSmoothing(&tmp, &src, &linfo, info.mode2);
			if(i+1==info.times) {
				dst.Header = tmp.Header;
				mrcInit(&dst, NULL);
				lmrcImageCopy(&dst, &tmp, to);
			} else {
				lmrcImageCopy(&src, &tmp, to);
			}
			mrcImageFree(&tmp, "in main"); 
		}
	}
	mrcStatDataSet(&dst, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode <<<< \n");
	lmrcImageSmoothingModeInfo(stderr);
}

