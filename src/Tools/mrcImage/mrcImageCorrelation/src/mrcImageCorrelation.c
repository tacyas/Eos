/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "mrcImage.h"
#include "lmrcImageCorrelation.h"
#include "genUtil.h"
#include "mrcRefUtil.h"


int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageCorrelationInfo info;
	lmrcImageCorrelationRefinementInfo linfo;
	mrcImage in;
	mrcImage out;
	mrcImage Out;
	mrcImage ref;
	mrcImage avg;
	mrcImage shift;
	mrcImageInformation imgInfo;
	mrcImageParaTypeRealCoord shiftCoord;
	double cor;
	long   num;
	
	DEBUGPRINT("Init Start\n");
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);
	
	switch(info.mode2){
		case 0: {
			DEBUGPRINT("Correlation by FFT\n");
			/* Correlation following info.mode */
	  		lmrcImageCorrelation(&out, &in, &ref, info.mode);  
			imgInfo.mode=meanOfAll;
			lmrcImageInformation(&imgInfo, &out);
			/* out: correlation map */ 
			if(info.flagRefineStep) {
				DEBUGPRINT("Refinement\n");
				/* Initial value set from correlation map */
				linfo.shift.x  = -imgInfo.maxCoord.x;
				linfo.shift.y  = -imgInfo.maxCoord.y;	
				linfo.shift.z  = -imgInfo.maxCoord.z;	
				linfo.step.x  = linfo.step.y  = linfo.step.z  = info.RefineStep;
				linfo.range.x = linfo.range.y = linfo.range.z = info.RefineRange;
				linfo.mode    = info.RefineMode;
				if(info.flagOut2) {
	  				lmrcImageCorrelationRefinement(&Out, &shift, &in, &ref, &linfo, info.mode);
				} else {
	  				lmrcImageCorrelationRefinement(&out, &shift, &in, &ref, &linfo, info.mode);
				}
	  			fprintf(info.fptOutCor, "Shift:       %g %g %g\n", 
						linfo.corInfo.minCoord.x,
						linfo.corInfo.minCoord.y,
						linfo.corInfo.minCoord.z);
	  			fprintf(info.fptOutCor, "Residual: %g \n",
						linfo.corInfo.min);
				/*
					out:   residual map 
					shift: shifted input file
					linfo.corInfo.min:      residual minimum
					linfo.corInfo.minCoord: the point where the rediue is minimum
				*/ 
			} else {
				shiftCoord.x  = -imgInfo.maxCoord.x;	
				shiftCoord.y  = -imgInfo.maxCoord.y;	
				shiftCoord.z  = -imgInfo.maxCoord.z;	
	  			fprintf(info.fptOutCor, "Shift:       %g %g %g\n", 
						imgInfo.maxCoord.x, imgInfo.maxCoord.y, imgInfo.maxCoord.z);
	  			fprintf(info.fptOutCor, "Correlation: %g \n",      imgInfo.max);
				lmrcImageShift(&shift, &in, shiftCoord, mrcPixelHowNearest); 
				/* 
					out:              correlation map 
					shift:            shifted input file
					imgInfo.max:      max correlation 
					imgInfo.maxCoord: the point where correlation is max
				*/
			}
			if(info.flagShift) { /* Shifted input file write */ 
				mrcFileWrite(&shift, info.Shift, "in main", 0);
			}
			if(info.flagAvg) { /* average between shifted input file and reference */
				num = 1;
				lmrcImageAdd(&shift, &ref, &num);
				lmrcImageDividedByReal(&shift, num);
				mrcFileWrite(&shift, info.Avg, "in main", 0);
			}
			if(info.flagOut) { /* correlation map or residual map is written down */
	  			mrcFileWrite(&out, info.Out, "in main", 0); 
			}
			if(info.flagOut2 && info.flagRefineStep) {
	  			mrcFileWrite(&Out, info.Out2, "in main", 0); 
			} else if(info.flagOut2) {
				fprintf(stderr, "-O option is inactive unless -Refine\n");
			}
			cor = lmrcImageCorrelationinSpace(&in, &ref, 0);
			fprintf(info.fptOutCor, "CorrelationRealSpace: %g\n", cor);
	  		break;
		}
		case 1: {
	  		cor = lmrcImageCorrelationinSpace(&in, &ref, 0);
	  		fprintf(info.fptOutCor, "Correlation: %g\n",cor);
			break;
		}
	}
	return 0;
}

void 
additionalUsage()
{
	fprintf(stderr, "----- Mode:  -m -----\n");
	lmrcImageCorrelationModePrint(stderr);
	fprintf(stderr, "----- Mode2: -M -----\n");
	fprintf(stderr, "mode 0: Correlation by FFT.  Output is a mrcImage to file.\n");
	fprintf(stderr, "            -a : Averaged image after Shift Transform [pixel unit] and Averaging\n");
	fprintf(stderr, "            -s : Shifted  image after Shift Transform [pixel unit]\n");
	fprintf(stderr, "            -o : Correation Map \n");
	fprintf(stderr, "mode 1: Correlation by multiplying in normal space.  Output is a real value \n");
	fprintf(stderr, "            Normalized correlation value\n");
	fprintf(stderr, "            No shift transform \n");
	fprintf(stderr, "            No Correlation Map \n");
	fprintf(stderr, "----- Refinement:  -refine -----\n");
	fprintf(stderr, "            refineStep[PixelUnit]  : refinement step size \n");
	fprintf(stderr, "            refineRange[PixelUnit] : refinement range     \n");
	fprintf(stderr, "            refineMode             : refinement mode      \n");
	fprintf(stderr, "            --- search area ----- \n");
	fprintf(stderr, "            the position of max correlation +- refineRange / refineStep \n");
	fprintf(stderr, "            Attention: If this option is set, the meaning of -o option is changed to a residual map \n");
}

