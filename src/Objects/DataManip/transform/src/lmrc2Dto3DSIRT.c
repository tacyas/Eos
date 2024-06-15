/*
# lmrc2Dto3DSIRT : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrc2Dto3DSIRT 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#undef DEBUG
#include "genUtil.h"
#include "./lmrc3Dto2D.h"
#include "./lmrc2Dto3D.h"
#include "lmrcImageSubtractionCalc.h"
#include "lmrcImageDensityNormalizationByImage.h"

/*
* SIRT:
*   2D(i+1) = Projection    *3D(i)
*   3D(i+1) = BackProjection*2D(i+1) 	 
*/

void
lmrc2Dto3DSIRT( mrcImage* Out, 
				mrcImage* in, 
				lmrc2Dto3DInfo* linfo,
				lmrc2Dto3DSIRTInfo* llinfo, 
				long mode)
{
	mrcImage tmp3D;
	mrcImage tmp3DDelta;
	mrcImage tmp2D;
	mrcImage tmp2DDelta;
	mrcImage nor2D;
	mrcImageInformation delInfo;
	mrcImageParaTypeRealCoord shift;
	static lmrcImageDensityNormalizationByImageInfo norInfo;
	double rms=MAXFLOAT;
	long iter = 0;
	int num;

	shift.x = shift.y = shift.z = 0;
	norInfo.sigma = 1.0;
	delInfo.mode = meanOfAll;
	lmrc2Dto3D(&tmp3D, in, linfo, mode);
	while(iter < llinfo->maxIter) {
		lmrcImageInformation(&delInfo, &tmp3D); 	rms = delInfo.rootMeanSquare;
		DEBUGPRINT3("SIRT tmp3D iter %ld rms %g mean %g\n", iter, rms, delInfo.mean);
		mrcFileWrite(&tmp3D, "file.tmp3D", "in lmrc2Dto3DSIRT", 0);	

		lmrcImage3Dto2DFollowingTailer(&tmp2D, &tmp3D, in, &llinfo->l3Dto2DInfo, mode);

		lmrcImageInformation(&delInfo, &tmp2D); 	rms = delInfo.rootMeanSquare;
		DEBUGPRINT3("SIRT tmp2D iter %ld rms %g mean %g\n", iter, rms, delInfo.mean);
		mrcFileWrite(&tmp2D, "file.tmp2D", "in lmrc2Dto3DSIRT", 0);	

		lmrcImageDenstiyNormalizationByImage(&nor2D, &tmp2D, in, &norInfo, 0);

		lmrcImageInformation(&delInfo, &nor2D); 	rms = delInfo.rootMeanSquare;
		DEBUGPRINT3("SIRT nor2D iter %ld rms %g mean %g\n", iter, rms, delInfo.mean);
		mrcFileWrite(&nor2D, "file.nor2D", "in lmrc2Dto3DSIRT", 0);	

		lmrcImageSubtractionCalc(&tmp2DDelta, in, &nor2D);

		lmrcImageInformation(&delInfo, &tmp2DDelta); 	rms = delInfo.rootMeanSquare;
		DEBUGPRINT3("SIRT tmp2DDelta iter %ld rms %g mean %g\n", iter, rms, delInfo.mean);
		mrcFileWrite(&tmp2DDelta, "file.tmp2DDelta", "in lmrc2Dto3DSIRT", 0);	

		tmp2DDelta.numTailer = tmp2DDelta.HeaderN.z;	
		mrcTailerInit(&tmp2DDelta, 0);
		mrcTailerCopy(&tmp2DDelta, in, 0); 
		lmrc2Dto3D(&tmp3DDelta, &tmp2DDelta, linfo, mode); 

		lmrcImageInformation(&delInfo, &tmp3DDelta); 	rms = delInfo.rootMeanSquare;
		DEBUGPRINT3("SIRT tmp3DDelta iter %ld rms %g mean %g\n", iter, rms, delInfo.mean);
		mrcFileWrite(&tmp3DDelta, "file.tmp3DDelta", "in lmrc2Dto3DSIRT", 0);	

		if(rms<llinfo->rms) {
			DEBUGPRINT("SIRT Finished\n");
			break;
		}

		lmrcImageMultiplying2(&tmp3DDelta, llinfo->lambda, 0);
		lmrcImageInformation(&delInfo, &tmp3DDelta); 	rms = delInfo.rootMeanSquare;
		DEBUGPRINT4("SIRT tmp3DDelta iter %ld rms %g mean %g lambda %f\n", iter, rms, delInfo.mean, llinfo->lambda);
		mrcFileWrite(&tmp3DDelta, "file.tmp3DDelta-lambda", "in lmrc2Dto3DSIRT", 0);	

		lmrcImageAdd(&tmp3D, &tmp3DDelta, &iter);
	}
	Out->Header.Cont = tmp3D.Header.Cont;
	mrcInit(Out, NULL);
	lmrcImageCopy(Out, &tmp3D, shift);
}

