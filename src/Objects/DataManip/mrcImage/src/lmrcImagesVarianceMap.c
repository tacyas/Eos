/*
# lmrcImagesVarianceMap.c  1.1
# The latest update : 01/23/97 at 10:37:08
#
#@(#) lmrcImagesVarianceMap ver 1.1
#@(#) Created by tacyas 
#@(#)
#@(#) Usage : lmrcImagesVarianceMap
#@(#) Usage : lmrcImagesVarianceMap2
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)lmrcImagesTTest ver1.1; Date:97/01/23 @(#)";

#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "nr2.h"
#include "lmrcImagesStatDataGet.h"

void 
lmrcImagesVarianceMapInformationPrint(FILE* fpt)
{
	fprintf(fpt, "---- Variance Map -----\n");
	fprintf(fpt, "-- Algorithm\n");
	fprintf(fpt, "   VarianceMap := VarinceOfAll/((VarianceOfDataSet1*n1+VarianceOfDataSet2*n2)/n1+n2)\n");
	fprintf(fpt, "                  VarinceOfAll:      variance of all data from Set1 and Set2\n");
	fprintf(fpt, "                  VarinceOfDataSet1: variance of all data from Set1 \n");
	fprintf(fpt, "                  VarinceOfDataSet2: variance of all data from Set2 \n");
	fprintf(fpt, "                  \n");
	fprintf(fpt, "   \n");
	fprintf(fpt, "   Kai-distribution: Kai^2 = SumOf (Xi - AvgOfXi)^2/sigma^2  \n");
	fprintf(fpt, "                           = s^2*(n-1)/sigma^2  : degree of freedom n-1 \n");
	fprintf(fpt, "                             when variables Xi are due to N(u, sigma^2)\n");
	fprintf(fpt, "   Kai-distribution: Kai^2 = Kai1^2 + Kai2^2 : degree of freedom m1 + m2\n");
	fprintf(fpt, "   F-distribution: F = (Kai1^2/k1)/(Kai2^2/k2)           : degree of freedom : (k1, k2)\n");
	fprintf(fpt, "                       (s1^2/sigma1^2)/(s2^2/sigma2^2)   : degree of freedom : (k1-1, k2-1)\n");
	fprintf(fpt, "   If sigma1 == sigma2, then                    \n");
	fprintf(fpt, "                       s1^2/s2^2  (Variance Ratio)       : degree of freedom : (k1-1, k2-1)\n");
}

void
lmrcImagesVarianceMap(mrcImage* Prob, mrcImage* Variance, mrcImage* src1, int n1, mrcImage* src2, int n2, long mode)
{
	lmrcImagesStatDataGetInfo linfo;
	lmrcImagesStatDataGetInfo linfo1;
	lmrcImagesStatDataGetInfo linfo2;
	mrcImage* src;
	int i; 

	src = (mrcImage*)memoryAllocate(sizeof(mrcImage)*(n1+n2), "in lmrcImagesVarianceMap");
	for(i=0; i<n1; i++) {
		src[i]    = src1[i];
	}
	for(i=0; i<n2; i++) {
		src[i+n1] = src2[i];
	}
	linfo.flagAvg  = 1;
	linfo.flagVar  = 1;
	linfo1.flagAvg = 1;
	linfo1.flagVar = 1;
	linfo2.flagAvg = 1;
	linfo2.flagVar = 1;
	lmrcImagesStatDataGet(&linfo,  src,  n1+n2, mode);
	lmrcImagesStatDataGet(&linfo1, src1, n1,    mode);
	lmrcImagesStatDataGet(&linfo2, src2, n2,    mode);

	if(n1<2 || n2<2) {
		fprintf(stderr, "Image Number is too small\n");
		lmrcImagesVarianceMapInformationPrint(stderr);
		exit(EXIT_FAILURE);
	}
	lmrcImagesVarianceMap2(Prob, Variance, &(linfo.Avg), &(linfo.Var), &(linfo1.Avg), &(linfo1.Var), n1, &(linfo2.Avg), &(linfo2.Var), n2, mode);
}

void 
lmrcImagesVarianceMap2(mrcImage* Prob, mrcImage* Variance, mrcImage* Avg, mrcImage* Var, mrcImage* Avg1, mrcImage* Var1, int n1, mrcImage* Avg2, mrcImage* Var2, int n2, long mode) 
{
	double var,  avg;
	double var1, avg1;
	double var2, avg2;
	double variance;
	double df;  /* degrees of freedom */
	double df1; /* degrees of freedom */
	double df2; /* degrees of freedom */
	double df3; /* degrees of freedom */
	double prob;
	mrcImageParaTypeReal x, y, z;

	Prob->Header  = Avg->Header;
	Variance->Header = Avg->Header;
	mrcInit(Prob, NULL);
	mrcInit(Variance, NULL);
	for(x=0; x<Variance->HeaderN.x; x++) {
		for(y=0; y<Variance->HeaderN.y; y++) {
			for(z=0; z<Variance->HeaderN.z; z++) {
				mrcPixelDataGet(Var,  x, y, z, &var,  mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Var1, x, y, z, &var1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(Var2, x, y, z, &var2, mrcPixelRePart, mrcPixelHowNearest);

				df  = n1 + n2 - 1;
				df1 = n1 - 1;
				df2 = n2 - 1;
				df3 = df1 + df2;
				variance = (var/df) 
						  /((var1*df1 + var2*df2)/(df3)/(df3));

				if(variance>1.0) {
					prob = 2.0*betai(0.5*df3, 0.5*df,  df3/(df3 + df*variance));
				} else {
					prob = 2.0*betai(0.5*df,  0.5*df3, df /(df  + df3*(1.0/variance)));
				}
				if(prob>1.0) prob = 2.0 - prob;
				prob = 1 - prob*0.5;
				if(variance>1.0) {
					prob =  prob; 
				} else {
					prob = -prob; 
				}

				mrcPixelDataSet(Variance, x, y, z, variance, mrcPixelRePart);
				mrcPixelDataSet(Prob,  x, y, z,    prob*100, mrcPixelRePart);
			}
		}
	}
}

