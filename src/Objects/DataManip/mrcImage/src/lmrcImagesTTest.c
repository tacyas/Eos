/*
# lmrcImagesTTest.c  1.1
# The latest update : 01/23/97 at 10:37:08
#
#@(#) lmrcImagesTTest ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : lmrcImagesTTest 
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)lmrcImagesTTest ver1.1; Date:97/01/23 @(#)";

#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "nr2.h"
#include "lmrcImagesStatDataGet.h"

void
lmrcImagesTTest(mrcImage* Prob, mrcImage* TTest, mrcImage* src1, int n1, mrcImage* src2, int n2, long mode)
{
	lmrcImagesStatDataGetInfo linfo1;
	lmrcImagesStatDataGetInfo linfo2;

	linfo1.flagAvg = 1;
	linfo1.flagVar = 1;
	linfo2.flagAvg = 1;
	linfo2.flagVar = 1;
	if(n1<2 || n2<2) {
		fprintf(stderr, "Image Number is too small\n");
		exit(EXIT_FAILURE);
	}
	lmrcImagesStatDataGet(&linfo1, src1, n1, mode);
	lmrcImagesStatDataGet(&linfo2, src2, n2, mode);

	lmrcImagesTTest2(Prob, TTest, &(linfo1.Avg), &(linfo1.Var), n1, &(linfo2.Avg), &(linfo2.Var), n2, mode);
}

void 
lmrcImagesTTest2(mrcImage* Prob, mrcImage* TTest, mrcImage* Avg1, mrcImage* Var1, int n1, mrcImage* Avg2, mrcImage* Var2, int n2, long mode) 
{
	double var1, avg1;
	double var2, avg2;
	double t;
	double df; /* degrees of freedom */
	double prob;
	mrcImageParaTypeReal x, y, z;

	Prob->Header  = Avg1->Header;
	TTest->Header = Avg1->Header;
	mrcInit(Prob, NULL);
	mrcInit(TTest, NULL);
	for(x=0; x<TTest->HeaderN.x; x++) {
		for(y=0; y<TTest->HeaderN.y; y++) {
			for(z=0; z<TTest->HeaderN.z; z++) {
				mrcPixelDataGet(Avg1, x, y, z, &avg1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Var1, x, y, z, &var1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Avg2, x, y, z, &avg2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Var2, x, y, z, &var2, mrcPixelRePart, mrcPixelHowNearest);

				if(0==var1 && 0==var2) {
					if(avg1 < avg2) {
						mrcPixelDataSet(TTest, x, y, z, -100, mrcPixelRePart);
					} else if(avg2 < avg1) {
						mrcPixelDataSet(TTest, x, y, z,  100, mrcPixelRePart);
					} else {
						mrcPixelDataSet(TTest, x, y, z,    0, mrcPixelRePart);
					}
				} else {
					t  = (avg1-avg2)/sqrt(var1/n1 + var2/n2);
					df = SQR(var1/n1 + var2/n2)/(SQR(var1/n1)/(n1-1)+SQR(var2/n2)/(n2-1));
					if(df<1e-3) {
						df = 0;
					}
					if(1e3<fabs(t)) {
						t = 1e3;
					}
					DEBUGPRINT3("(%f,%f,%f): ", x, y, z);
					DEBUGPRINT4("1: %f %f 2: %f %f ", avg1, var1, avg2, var2);
					DEBUGPRINT2("%f %f\n", t, df);
					prob = betai(0.5*df, 0.5, df/(df+SQR(t)));
					switch(mode) {
						case 0: {
							prob = 1 - prob;
							if(t<0) {
								prob = -prob;
							}
							break;
						}
						case 1: {
							if(t<0) {
								prob = -prob;
							}
							break;
						}
						default: {
							fprintf(stderr, "Not supported in TTest : %d \n", mode);
							exit(EXIT_FAILURE);
						}
					}
					mrcPixelDataSet(TTest, x, y, z, t, mrcPixelRePart);
					mrcPixelDataSet(Prob,  x, y, z, prob*100, mrcPixelRePart);
				}
			}
		}
	}
}

