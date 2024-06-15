/*
# lmrcImagesFTest.c  1.1
# The latest update : 01/23/97 at 10:41:03
#
#@(#) lmrcImagesFTest ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : lmrcImagesFTest 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lmrcImagesFTest ver1.1; Date:97/01/23 @(#)";

#include <stdlib.h>
#include "nr2.h"
#include "lmrcImagesStatDataGet.h"

void
lmrcImagesFTest(mrcImage* FProb,  mrcImage* FValue, mrcImage* src1, int n1, mrcImage* src2, int n2, long mode)
{
	lmrcImagesStatDataGetInfo linfo1;
	lmrcImagesStatDataGetInfo linfo2;

	linfo1.flagAvg = 1;
	linfo1.flagVar = 1;
	linfo2.flagAvg = 1;
	linfo2.flagVar = 1;
	lmrcImagesStatDataGet(&linfo1, src1, n1, mode);
	lmrcImagesStatDataGet(&linfo2, src2, n2, mode);
	lmrcImagesFTest2(FProb, FValue, &(linfo1.Avg), &(linfo1.Var), n1, &(linfo2.Avg), &(linfo2.Var), n2, mode); 
}

void
lmrcImagesFTest2(mrcImage* FProb, mrcImage* FValue, mrcImage* Avg1, mrcImage* Var1, int n1, mrcImage* Avg2, mrcImage* Var2, int n2, long mode)
{
	double var1, avg1;
	double var2, avg2;
	double f;
	double df1, df2; /* degrees of freedom */
	double prob;
	mrcImageParaTypeReal x, y, z;

	if(n1<2 || n2<2) {
		fprintf(stderr, "Image Number is too small\n");
		exit(EXIT_FAILURE);
	}
	FProb->Header  = Avg1->Header;
	FValue->Header = Avg1->Header;
	mrcInit(FProb, NULL);
	mrcInit(FValue, NULL);
	for(x=0; x<FValue->HeaderN.x; x++) {
		for(y=0; y<FValue->HeaderN.y; y++) {
			for(z=0; z<FValue->HeaderN.z; z++) {
				mrcPixelDataGet(Avg1, x, y, z, &avg1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Var1, x, y, z, &var1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Avg2, x, y, z, &avg2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Var2, x, y, z, &var2, mrcPixelRePart, mrcPixelHowNearest);

				if(var2<var1) {
					f = var1/var2;
					df1 = n1-1;
					df2 = n2-1;
				} else {
					f = var2/var1;
					df1 = n2-1;
					df2 = n1-1;
				}

				prob = 2.0*betai(0.5*df2, 0.5*df1, df2/(df2+df1*f));
				if(prob>1.0) prob=2.0-prob;

				mrcPixelDataSet(FValue, x, y, z, f, mrcPixelRePart);
				mrcPixelDataSet(FProb,  x, y, z, prob, mrcPixelRePart);
			}
		}
	}
}
