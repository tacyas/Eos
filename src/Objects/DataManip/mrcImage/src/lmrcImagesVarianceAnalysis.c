/*
# lmrcImagesVarianceMap.c  1.1
# The latest update : 01/23/97 at 10:37:08
#
#@(#) lmrcImagesVarianceAnalysis ver 1.1
#@(#) Created by tacyas 
#@(#)
#@(#) Usage : lmrcImagesVarianceAnalysis
#@(#) Usage : lmrcImagesVarianceAnalysis2
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
lmrcImagesVarianceAnalysisInformationPrint(FILE* fpt)
{
	fprintf(fpt, "---- Variance Analysis-----\n");
	fprintf(fpt, "-- Algorithm\n");
	fprintf(fpt, "   VarianceRatio := VarinceBetweenClasses/(SumOfVarianceWithinEachClass)\n");
	fprintf(fpt, "                  VarinceBetweenClasses: variance between classes\n");
	fprintf(fpt, "                  VarinceWithClasses:    variance within each class \n");
	fprintf(fpt, "                  \n");
	fprintf(fpt, "   \n");
	fprintf(fpt, "   ---- General Information -----\n");
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
lmrcImagesVarianceAnalysis(mrcImage* Prob, mrcImage* Variance, mrcImage** srcs, int* n1, int n2, long mode)
{
	lmrcImagesStatDataGetInfo linfo;
	lmrcImagesStatDataGetInfo* linfo1;
	mrcImage* src;
	mrcImage* Avgs;
	mrcImage* Vars;
	int i, j; 
	int total;

	if(n2<=2) {
		fprintf(stderr, "Variance ratio cannot be estimated because n2 is too small (<=2)\n");
		lmrcImagesVarianceAnalysisInformationPrint(stderr);
		exit(EXIT_FAILURE);
	}
	for(i=0, total=0; i<n2; i++)  {
		total += n1[i];
	}
	src    = (mrcImage*)memoryAllocate(sizeof(mrcImage)*(total), "in lmrcImagesVarianceAnalysis");
	Avgs   = (mrcImage*)memoryAllocate(sizeof(mrcImage)*(n2), "in lmrcImagesVarianceAnalysis");
	Vars   = (mrcImage*)memoryAllocate(sizeof(mrcImage)*(n2), "in lmrcImagesVarianceAnalysis");
	linfo1 = (lmrcImagesStatDataGetInfo*)memoryAllocate(sizeof(lmrcImagesStatDataGetInfo)*(n2), "in lmrcImagesVarianceAnalysis");

	total = 0;
	for(i=0; i<n2; i++) {
		for(j=0; j<n1[i]; j++) { 
			src[total] = srcs[i][j];
			total++;
		}
		linfo1[i].flagAvg = 1;
		linfo1[i].flagVar = 1;
		lmrcImagesStatDataGet(&(linfo1[i]), srcs[i], n1[i], mode);
		Avgs[i] = linfo1[i].Avg;
		Vars[i] = linfo1[i].Var;
	}
	memoryClear(&linfo, sizeof(linfo), 1);
	linfo.flagAvg  = 1;
	linfo.flagVar  = 1;
	lmrcImagesStatDataGet(&linfo,  src,  total, mode);
	lmrcImagesVarianceAnalysis2(Prob, Variance, &(linfo.Avg), &(linfo.Var), Avgs, Vars, n1, n2, mode);
}

void
lmrcImagesVarianceAnalysis2(mrcImage* Prob, mrcImage* Variance, mrcImage* Avg, mrcImage* Var, mrcImage* Avg1, mrcImage* Var1, int* n1, int n2, long mode) 
{
	double  var,  avg;
	double  varw,  avgw;
	double  varb,  avgb;
	double  dfw;  /* degrees of freedom */
	double  dfb;  /* degrees of freedom */
	double  ratio;
	double  prob;
	mrcImageParaTypeReal x, y, z;
	int i;

	Prob->Header     = Avg->Header;
	Variance->Header = Avg->Header;
	mrcInit(Prob, NULL);
	mrcInit(Variance, NULL);
	for(x=0; x<Variance->HeaderN.x; x++) {
		for(y=0; y<Variance->HeaderN.y; y++) {
			for(z=0; z<Variance->HeaderN.z; z++) {
				/* Variance between classes */  
				dfb  = n2 - 1;
				varb = 0;
				for(i=0; i<n2; i++) {
					mrcPixelDataGet(  Avg1,      x, y, z, &avg,  mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&(Avg1[i]),  x, y, z, &avgb, mrcPixelRePart, mrcPixelHowNearest);
					varb += (SQR(avg-avgb)*n1[i]);
				}
				varb /= dfb;

				/* Variance within each class */  
				dfw  = 0;
				varw = 0;	
				for(i=0; i<n2; i++) {
					mrcPixelDataGet(&(Var1[i]),  x, y, z, &var,  mrcPixelRePart, mrcPixelHowNearest);
					varw += (var*(n1[i] - 1));
					dfw  += (n1[i] - 1);
				}
				varw /= dfw;
				ratio = varb/varw;

				prob = betai(0.5*dfw, 0.5*dfb, dfw/(dfw + dfb*ratio));
				prob = 1 - prob*0.5;

				mrcPixelDataSet(Variance, x, y, z, ratio, mrcPixelRePart);
				mrcPixelDataSet(Prob,  x, y, z,    prob*100, mrcPixelRePart);
			}
		}
	}
}
