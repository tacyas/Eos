/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageEnhancementWithFuzzySets ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageEnhancementWithFuzzySets
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageEnhancementWithFuzzySets ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageEnhancementWithFuzzySetsInfo {
	mrcImageParaTypeReal Fe;
	mrcImageParaTypeReal Fd;
	mrcImageParaTypeInteger r;
} lmrcImageEnhancementWithFuzzySetsInfo;

extern void lmrcImageEnhancementWithFuzzySets(mrcImage* out, mrcImage* in, lmrcImageEnhancementWithFuzzySets* linfo, long mode);
void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageEnhancementWithFuzzySetsInfo info;
	mrcImage in;
	mrcImage out;
	lmrcImageEnhancementWithFuzzySetsInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	mrcFileRead(&in, info.In, "in main", 0);

	linfo.Fe = info.Fe;
	linfo.Fd = info.Fd;
	linfo.r  = info.r;

	lmrcImageEnhancementWithFuzzySets(&out, &in, &linfo, 0);


	mrcFileWrite(&in, info.In, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

/*
	x      -> p         : To Fuzzy Sets 
	p      -> pprime    : Enhancement
	pprime -> xprime    : From Fuzzy Sets
*/

void 
__lmrcImageEnhancementWithFuzzySetsToFuzzySets(mrcImage* pmn, mrcImage* xmn, lmrcImageEnhancementWithFuzzySets* linfo, long mode)
{
	mrcImageParaTypeReal x, y;
	double data;

	pmn->Header = xmn->Header;
	mrcInit(pmn, NULL);

	for(x=0; x->HeaderN.x; x++) {
		for(y=0; y->HeaderN.y; y++) {
			mrcPixelDataGet(xmn, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
			data = pow(1 + (linfo.max - data)/linfo.Fd, linfo.Fe);
			mrcPixelDataSet(pmn, x, y, 0.0, data, mrcPixelRePart);
		}
	}
}

void 
__lmrcImageEnhancementWithFuzzySetsFromFuzzySets(mrcImage* xmn, mrcImage* pmn, lmrcImageEnhancementWithFuzzySets* linfo, long mode)
{
	xmn->Header = pmn->Header;
	mrcInit(xmn, NULL);

	for(x=0; x->HeaderN.x; x++) {
		for(y=0; y->HeaderN.y; y++) {
			mrcPixelDataGet(pmn, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
			data = linfo.max - (pow(data, -linfo.Fe) - 1)*linfo.Fd
			mrcPixelDataSet(xmn, x, y, 0.0, data, mrcPixelRePart);
		}
	}
}

void 
__lmrcImageEnhancementWithFuzzySetsPtoPprime(mrcImage* pprime, mrcImage* p, lmrcImageEnhancementWithFuzzySets* linfo, long mode)
{
	int i;
	mrcImage* tmppprime;	

	tmppprime = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.r);

	for(i=0; i<linfo.r; i++) {
		tmppprime[i].Header = p->Header;
		mrcInit(&(tmpprime[i]), NULL);
		for(x=0; x->HeaderN.x; x++) {
			for(y=0; y->HeaderN.y; y++) {
				mrcPixelDataGet(pmn, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
				if(0 <= data && data <= 0.5) {
					data = 2.0*SQR(data);	
				} else if(0.5 < data && data<=1.0) {
					data = 1.0 - 2.0*SQR(1.0 - data);
				} else {
					fprintf(stderr, "Something wrong in __lmrcImageEnhancementWithFuzzySetPtoPprime: (%f %f), %d th, %f\n",
										x, y, i, data);
				}
				mrcPixelDataSet(xmn, x, y, 0.0, data, mrcPixelRePart);
			}
		}
	}

	pprime = tmppprime[r-1];
	for(i=0; i<linfo.r-1; i++) {
		mrcImageFree(&(tmpprime[i]), NULL);
	}
	free(tmpprime);
}

void 
lmrcImageEnhancementWithFuzzySets(mrcImage* out, mrcImage* in, lmrcImageEnhancementWithFuzzySets* linfo, long mode)
{
	mrcImage  p;
	mrcImage pprime;

	__lmrcImageEnhancementWithFuzzySetsToFuzzySets(&p, in, linfo, mode)
	__lmrcImageEnhancementWithFuzzySetsPtoPprime(mrcImage* pprime, mrcImage* p, linfo, mode)
	__lmrcImageEnhancementWithFuzzySetsFromFuzzySets(out, &pprime, linfo, mode)
}

