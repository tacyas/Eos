/*
# mrcImageSuperResolution : $Revision$  
# $Date$ 
# Created by Ayumi Matsuura 
# Usage : mrcImageSuperResolution
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
#include "nr2.h"
#include "Memory.h"
#include "lmrcImageSubtractionCalc.h"

#define AREA_LOCATION 0x1
#define DENSITY 0x2
#define CONVERGENCE 0x4
#define LOWPASSFILTER_MODE 0x100
#define COUNTER_MODE 0x200
#define NONNEGATIVE 0x10
#define BINARIZATION 0x20
#define LABELING 0x40
#define SIXORIENTATION 0x80


typedef enum lmrcImageSuperResolutionMode {
	RealSpaceCalculatingbyAreaAndLocationwithCounter = (AREA_LOCATION | COUNTER_MODE),
	RealSpaceCalculatingbyDensitywithCounter = (DENSITY | COUNTER_MODE),
	RealSpaceCalculatingbyAreaAndLocationandDensitywithCounter = (AREA_LOCATION | DENSITY | COUNTER_MODE),

	RealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationwithCounter = 
	(AREA_LOCATION | COUNTER_MODE | BINARIZATION | SIXORIENTATION),
	RealSpaceCalculatingbyBinarizationandOrientationwithCounter = (COUNTER_MODE | BINARIZATION | SIXORIENTATION),
	RealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationandDensitywithCounter = 
	(AREA_LOCATION | DENSITY | COUNTER_MODE | BINARIZATION | SIXORIENTATION),

	RealSpaceCalculatingbyBinarizationandOrientationandLabelingwithCounter = 
	(BINARIZATION | LABELING | SIXORIENTATION | COUNTER_MODE),
	RealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter = 
	(BINARIZATION | SIXORIENTATION | LABELING | AREA_LOCATION | COUNTER_MODE),

	RealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter = 
	(BINARIZATION | SIXORIENTATION | LABELING | DENSITY |  CONVERGENCE | COUNTER_MODE),
	RealSpaceCalculatingbyAreaAndLocationforConvergencewithCounter = (AREA_LOCATION | CONVERGENCE | COUNTER_MODE),
	RealSpaceCalculatingbyDensityforConvergencewithCounter = (DENSITY | CONVERGENCE | COUNTER_MODE),
	RealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithCounter = 
	(AREA_LOCATION | DENSITY | CONVERGENCE | COUNTER_MODE),

	RealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter = 
	(DENSITY | CONVERGENCE | COUNTER_MODE | NONNEGATIVE),

	RealSpaceCalculatingbyAreaAndLocationwithLowpassfilter = (AREA_LOCATION | LOWPASSFILTER_MODE),
	RealSpaceCalculatingbyDensitywithLowpassfilter = (DENSITY | LOWPASSFILTER_MODE),
	RealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter = (AREA_LOCATION | DENSITY | LOWPASSFILTER_MODE),
	RealSpaceCalculatingbyAreaAndLocationforConvergencewithLowpassfilter = (AREA_LOCATION | CONVERGENCE | LOWPASSFILTER_MODE),
	RealSpaceCalculatingbyDensityforConvergencewithLowpassfilter = (DENSITY | CONVERGENCE | LOWPASSFILTER_MODE),
	RealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithLowpassfilter = 
	(AREA_LOCATION | DENSITY | CONVERGENCE | LOWPASSFILTER_MODE)

} lmrcImageSuperResolutionMode;

typedef enum lmrcImageLabelingMode {
	TheLargestLabelingSearch = 0,
	SomeVolumeLabelingSearch = 1	
} lmrcImageLabelingMode;

typedef struct lmrcImageSuperResolutionInfo {
	int t;
	int x00, x01;
	int y00, y01;
	int z00, z01;
	int x10, x11;
	int y10, y11;
	int z10, z11;
	float min, max;
	int shape;
	float hvp;
	int Inverse;
	int nMolecule;
	int MolecularWeight;
	float Density;
	long flagFFTInCount;
	long flaghvp;
	int incounter;
	char*  FFTInCount;
	float deltaDens;
	float deltaArea;
	float sub;
	float ratio;
	int tmax;
	float weightdelta;
	int weightmax; 	
	long flagdeltaDens;
	float tmpdensity; 
	double tmpscale; 
	long flagSub;

} lmrcImageSuperResolutionInfo;

extern void lmrcImageSuperResolution(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, 
lmrcImageSuperResolutionMode mode, lmrcImageLabelingMode labelingmode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationwithCounter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationforConvergencewithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationandDensitywithCounter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(mrcImage* tmpBinarization, mrcImage* tmpOrientation, 
mrcImage* tmpOrientationConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingwithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, 
lmrcImageLabelingMode labelingmode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, 
lmrcImageLabelingMode labelingmode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, lmrcImageLabelingMode labelingmode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationwithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(mrcImage* tmpConstraint, mrcImage* inPrev, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, float t);
extern float lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation2(mrcImage* tmpConstraint, mrcImage* inPrev, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, float t);
extern float lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(mrcImage* tmpConstraint, mrcImage* inPrev, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern float lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(mrcImage* tmpBinarization, 
mrcImage* tmpBinaryConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(mrcImage* tmpFFTConstraint, mrcImage* tmpFFTOrg, 
mrcImage* tmpFFTOut, mrcImage* tmpFFTPrev, lmrcImageSuperResolutionInfo linfo);
extern void lmrcImageSuperResolutionFourierSpaceCalculatingwithLowpassfilter(mrcImage* tmpConstraint, 
mrcImage* tmpFFTConstraint, mrcImage* tmpFFTOrg, mrcImage* tmpFFTOut, mrcImage* tmpFFTPrev, 
lmrcImageSuperResolutionInfo linfo);
extern int lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(mrcImage* inPrev, mrcImage* tmpOut, 
lmrcImageSuperResolutionInfo linfo);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeConstraint(mrcImage* tmpNonnegativeConstraint, 
mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling(mrcImage* tmpOrientation , mrcImage* tmpLabeling, 
mrcImage* tmpLabelingConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, 
lmrcImageLabelingMode labelingmode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling1(mrcImage* tmpOrientation, mrcImage* tmpLabeling, 
mrcImage* tmpLabelingConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling2(mrcImage* tmpOrientation, mrcImage* tmpLabeling, 
mrcImage* tmpLabelingConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode);
extern void lmrcImageSuperResolutionRealSpaceCalculatingbySubtraction(mrcImage* tmpSubConstraint, 
mrcImage* tmpPrevConstraint, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, double scale);
extern void lmrcImageSuperResolutionHelp(FILE* fpt);


int
main(int argc, char* argv[]) 
{

	mrcImageSuperResolutionInfo info;
	lmrcImageSuperResolutionInfo linfo;
	lmrcImageSuperResolutionMode mode;
	lmrcImageLabelingMode labelingmode;
	mrcImage inOrg;
	mrcImage inPrev;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mode = info.mode;
	labelingmode= info.labelingmode;
	
	linfo.x00 = info.x00; 
	linfo.x01 = info.x01;
	linfo.y00 = info.y00;
	linfo.y01 = info.y01;
	linfo.z00 = info.z00;
	linfo.z01 = info.z01;
	linfo.x10 = info.x10;
	linfo.x11 = info.x11;
	linfo.y10 = info.y10;
	linfo.y11 = info.y11;
	linfo.z10 = info.z10;
	linfo.z11 = info.z11;

	linfo.t = info.t;
	linfo.min = info.min;
	linfo.max = info.max;
	linfo.shape = info.shape;
	linfo.hvp = info.hvp;
 	linfo.flaghvp = info.flaghvp;
	linfo.Inverse = info.Inverse;
	linfo.nMolecule = info.nMolecule;
	linfo.MolecularWeight = info.MolecularWeight;
	linfo.Density = info.Density;
	linfo.flagFFTInCount = info.flagFFTInCount;
	linfo.FFTInCount = info.FFTInCount;	
	linfo.incounter = info.incounter;
	linfo.deltaDens = info.deltaDens;
	linfo.deltaArea = info.deltaArea;
	linfo.sub = info.sub;
	linfo.ratio = info.ratio;
	linfo.tmax = info.tmax;
	linfo.weightdelta = info.WeightDelta;
	linfo.weightmax = info.WeightMax;
	linfo.flagdeltaDens = info.flagdeltaDens;
	linfo.flagSub = info.Subtraction;

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&inOrg, info.InOriginal, "in main", 0);
	mrcFileRead(&inPrev, info.InPrevious, "in main", 0);
	lmrcImageSuperResolution(&out, &inPrev, &inOrg, linfo, mode, labelingmode);
	mrcFileWrite(&out, info.Out, "in main", 0);

	mrcImageFree(&inOrg, "in main");
	mrcImageFree(&inPrev, "in main");
	mrcImageFree(&out, "in main");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageSuperResolutionHelp(stderr);
/*	
	fprintf(stderr, "Either -hvp or -ic is required.\n");
	fprintf(stderr, "-hvp\n");
	fprintf(stderr, "     HalfValuePointMode(if you used some Lowpassfilter, select your hvp)\n");
	fprintf(stderr, "-ic\n");
	fprintf(stderr, "     CounterMode(Double tilt series)\n");
	fprintf(stderr, "-m Option\n");
	fprintf(stderr, "-counter Option\n");
*/	
}
void 
lmrcImageSuperResolutionHelp(FILE *fpt)
{
	fprintf(fpt, "-m Option\n");
	fprintf(fpt, "     1 : AreaAndLocation\n");
	fprintf(fpt, "     2 : Density\n");
	fprintf(fpt, "     3 : AreaAndLocationandDensity\n");
	fprintf(fpt, "    +4 : Convergence(Option)\n");
	fprintf(fpt, "   +16 : NonnegativeMode(before RealSpaceConstraint)\n");
	fprintf(fpt, "   +32 : Binarization(before RealSpaceConstraint)\n");
	fprintf(fpt, "   +64 : Labeling\n");
	fprintf(fpt, "  +128 : SixOrientation\n");
	fprintf(fpt, "  +256 : LowpassfilterMode(-hvp is required)\n");
	fprintf(fpt, "  +512 : CounterMode(-ic is required)\n");
	fprintf(fpt, "-----------------------------------------------------\n");
	fprintf(fpt, "-Inverse\n");
	fprintf(fpt, "If high density means the location of protein, -Inverse is required for volume calculation.\n");
	fprintf(fpt, "-wm and -wd\n");
	fprintf(fpt, "weight = counter / (weightmax + counter)\n");
	fprintf(fpt, "weightmax -> 0 (weightdelt by weightdelta) \n");
	fprintf(fpt, "-LabelinMode \n");
	fprintf(fpt, "     0 : TheLargestLabelingSearch \n");
	fprintf(fpt, "     1 : SomeVolumeLabelingSearch \n");
	fprintf(fpt, "-Subtraction\n");
	fprintf(fpt, "Real Space Constraint for desolving edge problem\n");
	fprintf(fpt, "\n");

}

void 
lmrcImageSuperResolution(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, 
lmrcImageSuperResolutionMode mode, lmrcImageLabelingMode labelingmode)
{

	switch(mode & 0xfff) {
	
		case RealSpaceCalculatingbyAreaAndLocationwithLowpassfilter: {
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter(out, inPrev, inOrg, linfo, mode);
			break;
		}
		case  RealSpaceCalculatingbyAreaAndLocationwithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter(out, inPrev, inOrg, linfo, mode);
			break;
		}
		case RealSpaceCalculatingbyDensitywithLowpassfilter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter(out, inPrev, inOrg, linfo, mode);
			break;	
		}
		case RealSpaceCalculatingbyDensitywithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter(out, inPrev, inOrg, linfo, mode);
			break;
		}
		case RealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter(out, inPrev, inOrg, 
			linfo, mode);
			break;
		}
		case RealSpaceCalculatingbyAreaAndLocationandDensitywithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter(out, inPrev, inOrg, linfo, mode);
			break;
		}

	
		/*Convergence mode*/
	/*	
		case RealSpaceCalculatingbyAreaAndLocationforConvergencewithLowpassfilter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationforConvergencewithLowpassfilter(out, inPrev, inOrg, 
			linfo, mode);
			break;
		}
	*/
		case RealSpaceCalculatingbyAreaAndLocationforConvergencewithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationforConvergencewithCounter(out, inPrev, inOrg, linfo, mode);
			break;
		}
		/*
		case RealSpaceCalculatingbyDensityforConvergencewithLowpassfilter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithLowpassfilter(out, inPrev, inOrg, 
			linfo, mode);
			break;
		}
		*/
		case RealSpaceCalculatingbyDensityforConvergencewithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter(out, inPrev, inOrg, linfo, mode);
			break;
		}
		/*
		case RealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithLowpassfilter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithLowpassfilter
			(out, inPrev, inOrg, linfo, mode);
			break;
		}
		*/
		case RealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithCounter(out, inPrev, 
			inOrg, linfo, mode);
			break;
		}
		case RealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter(out, inPrev, 
			inOrg, linfo, mode);
			break;
		}
		case RealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationwithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationwithCounter
			(out, inPrev, inOrg, linfo, mode);
			break;
		}
		case RealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationandDensitywithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationandDensitywithCounter
			(out, inPrev, inOrg, linfo, mode);
			break;
		}

		case RealSpaceCalculatingbyBinarizationandOrientationandLabelingwithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingwithCounter(out, inPrev, 
			inOrg, linfo, mode, labelingmode);
			break;
		}
		case RealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter
			(out, inPrev, inOrg, linfo, mode, labelingmode);
			break;
		}
		case RealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter
			(out, inPrev, inOrg, linfo, mode, labelingmode);
			break;
		}

		case RealSpaceCalculatingbyBinarizationandOrientationwithCounter:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationwithCounter(out, inPrev, inOrg, linfo, 
			mode);
			break;
		}

		default:{ 
			fprintf(stderr, "Please select mode (%d is inavairable.)\n", mode );
			exit(EXIT_FAILURE);
			break;
		}	
		
	}
}

void
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpConstraint;
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;

	int i;
	float t;
	
	if(!linfo.flaghvp){
		fprintf(stderr, "-hvp is required.\n");
		exit(EXIT_FAILURE);
	}

	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);

	for(i = 0; i < linfo.t; i++ ){
		DEBUGPRINT1("i = %d\n", i);
		tmpConstraint.Header = inPrev->Header;
		mrcInit(&tmpConstraint, NULL);

		/*Real Space*/
		if(linfo.t == 1){
			t = 0.0;
		}else{
			t = (float)(i + 1) / linfo.t;
		}
		lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpConstraint, inPrev, linfo, mode, t);

		/*Fourie Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithLowpassfilter(&tmpConstraint, &tmpFFTConstraint, &tmpFFTOrg, 
		&tmpFFTOut, &tmpFFTPrev, linfo);

		/*Real space*/
		if(i != linfo.t - 1){
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
		}else{
			break;
		}

		DEBUGPRINT("\n");
	}
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithLowpassfilter");

}
	

void
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOut;
	mrcImage tmpFFTOrg;
	mrcImage tmpAreaConstraint;
	mrcImage tmpSubConstraint;
	int i;
	float t;

	DEBUGPRINT1("mode%d Start\n ", mode);
	
	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);

	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("i=%d\n", i);
		tmpAreaConstraint.Header = inPrev->Header; 
		mrcInit(&tmpAreaConstraint, NULL);
		tmpSubConstraint.Header = inPrev->Header; 
		mrcInit(&tmpSubConstraint, NULL);

		/*Real Space */
		if(linfo.t == 1){
			t = 0.0;
		}else{
			t = (float)(i + 1)/ linfo.t;
		}
		if(linfo.flagSub){
			DEBUGPRINT("Sub mode\n");
			linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation2(&tmpAreaConstraint, inPrev, 
			linfo, mode, t);
			lmrcImageSubtraction(&tmpSubConstraint, &tmpAreaConstraint, linfo.tmpdensity);
			lmrcImageFFT(&tmpFFTConstraint, &tmpSubConstraint, 0);
		}else{	
			lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpAreaConstraint, inPrev, linfo, mode, t);
			lmrcImageFFT(&tmpFFTConstraint, &tmpAreaConstraint, 0);
		}
		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);
		/*Real Space*/
		if(i != linfo.t - 1){
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
			mrcImageFree(&tmpSubConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
		}else{
			break;
		}
		DEBUGPRINT("\n");
   	}
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
	mrcImageFree(&tmpSubConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationwithCounter" );

}

void 
lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationwithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOut;
	mrcImage tmpFFTOrg;

	mrcImage tmpBinaryConstraint;
	mrcImage tmpAreaConstraint;
	mrcImage tmpBinarization;
	mrcImage tmpOrientation;
	mrcImage tmpOrientationConstraint;

	int i;
	float t;
	float delta, thres;

	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}
	DEBUGPRINT1("mode%d Start\n", mode);
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);
	
	for(i = 0; i< linfo.t; i++){
		DEBUGPRINT1("i=%d\n", i);

		tmpBinaryConstraint.Header = inPrev->Header;
		mrcInit(&tmpBinaryConstraint, NULL);
		tmpAreaConstraint.Header = inPrev->Header;
		mrcInit(&tmpAreaConstraint, NULL);
		tmpBinarization.Header = inPrev->Header;
		mrcInit(&tmpBinarization, NULL);
		tmpOrientation.Header = inPrev->Header;
		mrcInit(&tmpOrientation, NULL);
		tmpOrientationConstraint.Header = inPrev->Header;
		mrcInit(&tmpOrientationConstraint, NULL);
		
		if(linfo.t == 1){
			delta = 0.0; 
		}else{
			delta = (linfo.max - linfo.min) / (t -1);
		}

		thres = linfo.max - i* delta;
		linfo.tmpscale = thres / 100;
		/*Real Space*/
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(&tmpBinarization, 
		&tmpBinaryConstraint, inPrev, linfo, mode);
		lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
		&tmpOrientationConstraint, inPrev, linfo, mode);
		if(linfo.t == 1){
			t = 0.0;
		}else{
			t = (float)(i + 1) / linfo.t;
		}
		lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpAreaConstraint, &tmpOrientationConstraint, linfo, 
		mode, t);
		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpAreaConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);
		/*Real Space*/
		if(i != linfo.t - 1){
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
			mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
		}else{
			break;
		}
		DEBUGPRINT("\n");
 	}
	lmrcImageFFT(out, &tmpFFTOut, 0);

	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
	mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationwithCounter");
}


void 
lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationwithCounter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpBinarization;
	mrcImage tmpBinaryConstraint;
	mrcImage tmpOrientation;
	mrcImage tmpOrientationConstraint;
	mrcImage tmpSubConstraint;

	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;

	int i;
	float delta;
	float thres;
	
	DEBUGPRINT1("mode%dStart\n", mode);
	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);
	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("i = %d\n", i);
		tmpBinarization.Header = inPrev->Header;
		mrcInit(&tmpBinarization, NULL);
		tmpBinaryConstraint.Header = inPrev->Header;
		mrcInit(&tmpBinaryConstraint, NULL);
		tmpOrientation.Header = inPrev->Header;
		mrcInit(&tmpOrientation, NULL);
		tmpOrientationConstraint.Header = inPrev->Header;
		mrcInit(&tmpOrientationConstraint, NULL);
		tmpSubConstraint.Header = inPrev->Header;
		mrcInit(&tmpSubConstraint, NULL);

		/*Real Space*/
		if(linfo.t == 1){
			delta = 0.0;	
		}else{
			delta = (linfo.max - linfo.min) / (linfo.t - 1);
		}
		thres = linfo.max - i * delta;
		linfo.tmpscale = thres / 100;

		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(&tmpBinarization, 
		&tmpBinaryConstraint, inPrev, linfo, mode);
		if(linfo.flagSub){
			DEBUGPRINT("SUB mode\n");
			lmrcImageSubtraction(&tmpSubConstraint, &tmpBinaryConstraint, linfo.tmpdensity);
			lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
			&tmpOrientationConstraint, &tmpSubConstraint, linfo, mode);
		}else{
			DEBUGPRINT("non sub mode\n");
			lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
			&tmpOrientationConstraint, inPrev, linfo, mode);
		}
		/*Fourier Scale*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpOrientationConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, 
		&tmpFFTPrev, linfo);

		if(i != linfo.t - 1){
			mrcImageFree(inPrev, NULL);
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpBinarization, NULL);
			mrcImageFree(&tmpBinaryConstraint, NULL);
			mrcImageFree(&tmpOrientation, NULL);
			mrcImageFree(&tmpOrientationConstraint, NULL);
			mrcImageFree(&tmpSubConstraint, NULL);
			mrcImageFree(&tmpFFTConstraint, NULL);
			mrcImageFree(&tmpFFTOut, NULL);
			mrcImageFree(&tmpFFTPrev, NULL);
		}else{
			break;
		}
		DEBUGPRINT("\n");
	}
	lmrcImageFFT(out, &tmpFFTOut, 0);
	
	mrcImageFree(&tmpBinarization, NULL);
	mrcImageFree(&tmpBinaryConstraint, NULL);
	mrcImageFree(&tmpOrientation, NULL);
	mrcImageFree(&tmpOrientationConstraint, NULL);
	mrcImageFree(&tmpSubConstraint, NULL);
	mrcImageFree(&tmpFFTConstraint, NULL);
	mrcImageFree(&tmpFFTOut, NULL);
	mrcImageFree(&tmpFFTPrev, NULL);
	mrcImageFree(&tmpFFTOrg, NULL);

}

void 
lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingwithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, 
lmrcImageLabelingMode labelingmode)
{
	mrcImage tmpBinarization;
	mrcImage tmpBinaryConstraint;
	mrcImage tmpOrientation;
	mrcImage tmpOrientationConstraint;
	mrcImage tmpLabeling;
	mrcImage tmpLabelingConstraint;
	mrcImage tmpSubConstraint;

	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;

	int i;
	float delta, thres; 
	DEBUGPRINT1("%d modeStart\n", mode); 
	if(!linfo.flagFFTInCount){ 
		fprintf(stderr, "-ic is required.\n"); 
		exit(EXIT_FAILURE);
	}
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);	
	for(i = 0; i < linfo.t ; i++){
		DEBUGPRINT1("i = %d\n", i);
		
		tmpBinarization.Header = inPrev->Header;
		mrcInit(&tmpBinarization, NULL);
		tmpBinaryConstraint.Header = inPrev->Header;
		mrcInit(&tmpBinaryConstraint, NULL);
		tmpOrientation.Header = inPrev->Header;
		mrcInit(&tmpOrientation, NULL);
		tmpOrientationConstraint.Header = inPrev->Header;
		mrcInit(&tmpOrientationConstraint, NULL);
		tmpLabeling.Header = inPrev->Header;
		mrcInit(&tmpLabeling, NULL);
		tmpLabelingConstraint.Header = inPrev->Header;
		mrcInit(&tmpLabelingConstraint, NULL);
		tmpSubConstraint.Header = inPrev->Header;
		mrcInit(&tmpSubConstraint, NULL);


		if(linfo.t == 1){
			delta = 0.0;
		}else{
			delta = (linfo.max - linfo.min) / (linfo.t - 1);
		}			
		thres = linfo.max - i * delta;
		linfo.tmpscale = thres / 100;

		/*real Space*/
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(&tmpBinarization, 
		&tmpBinaryConstraint, inPrev, linfo, mode);
		lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
		&tmpOrientationConstraint, inPrev, linfo, mode);
		if(linfo.flagSub){
			DEBUGPRINT("Subtraction mode\n");
			lmrcImageSubtraction(&tmpSubConstraint, &tmpBinaryConstraint, linfo.tmpdensity);
			lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling(&tmpOrientation, &tmpLabeling, &tmpLabelingConstraint, 
			&tmpSubConstraint, linfo, mode, labelingmode);
		}else{
			DEBUGPRINT("Non Subtraction mode\n");
			lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling(&tmpOrientation, &tmpLabeling, &tmpLabelingConstraint, 
			inPrev, linfo, mode, labelingmode);
		}

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpLabelingConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header; 
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);

		if(i != linfo.t - 1){
			mrcImageFree(inPrev, NULL);
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpBinarization, NULL);
			mrcImageFree(&tmpBinaryConstraint, NULL);
			mrcImageFree(&tmpOrientation, NULL);
			mrcImageFree(&tmpOrientationConstraint, NULL);
			mrcImageFree(&tmpLabeling, NULL);
			mrcImageFree(&tmpLabelingConstraint, NULL);
			mrcImageFree(&tmpSubConstraint, NULL);
			mrcImageFree(&tmpFFTConstraint, NULL);
			mrcImageFree(&tmpFFTPrev, NULL);
			mrcImageFree(&tmpFFTOut, NULL);
		}else{
			break;
		}
		DEBUGPRINT("\n");
	}
	lmrcImageFFT(out, &tmpFFTOut, 0);	
	mrcImageFree(&tmpBinarization, NULL);
	mrcImageFree(&tmpBinaryConstraint, NULL);
	mrcImageFree(&tmpOrientation, NULL);
	mrcImageFree(&tmpOrientationConstraint, NULL);
	mrcImageFree(&tmpLabeling, NULL);
	mrcImageFree(&tmpLabelingConstraint, NULL);
	mrcImageFree(&tmpSubConstraint, NULL);
	mrcImageFree(&tmpFFTConstraint, NULL);
	mrcImageFree(&tmpFFTPrev, NULL);
	mrcImageFree(&tmpFFTOut, NULL);
	mrcImageFree(&tmpFFTOrg, NULL);
}


void
lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, 
lmrcImageLabelingMode labelingmode)
{
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;

	mrcImage tmpBinarization;
	mrcImage tmpBinaryConstraint;
	mrcImage tmpOrientation;
	mrcImage tmpOrientationConstraint;
	mrcImage tmpLabeling;
	mrcImage tmpLabelingConstraint;
	mrcImage tmpAreaConstraint;
	float t;	
	int i;
	float delta, thres;

	DEBUGPRINT1("mode%d Start\n", mode);
	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}

	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);
	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("%d\n", i);

		tmpBinarization.Header = inPrev->Header;
		mrcInit(&tmpBinarization, NULL);
		tmpBinaryConstraint.Header = inPrev->Header;
		mrcInit(&tmpBinaryConstraint, NULL);
		tmpOrientation.Header = inPrev->Header;
		mrcInit(&tmpOrientation, NULL);
		tmpOrientationConstraint.Header = inPrev->Header;
		mrcInit(&tmpOrientationConstraint, NULL);
		tmpLabeling.Header = inPrev->Header;
		mrcInit(&tmpLabeling, NULL);
		tmpLabelingConstraint.Header = inPrev->Header;
		mrcInit(&tmpLabelingConstraint, NULL);
		tmpAreaConstraint.Header = inPrev->Header;
		mrcInit(&tmpAreaConstraint, NULL);

		/*Real Space*/
		if(linfo.t == 1){
			delta = 0.0;
		}else{
			delta = (linfo.max - linfo.min) / (t - 1);
		}
		thres = linfo.max - i* delta;
		linfo.tmpscale = thres / 100;

		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(&tmpBinarization, 
		&tmpBinaryConstraint, inPrev, linfo, mode);
		lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
		&tmpOrientationConstraint, inPrev, linfo, mode);
		lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling(&tmpOrientation, &tmpLabeling, &tmpLabelingConstraint, 
		inPrev, linfo, mode, labelingmode);
		if(linfo.t == 1){
			t = 0.0;
		}else{
			t = (float)(i + 1) / linfo.t;
		}
		lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpAreaConstraint, &tmpLabelingConstraint, linfo, 
		mode, t);

		/*Fourie Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpAreaConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);
		
		if(i != linfo.t - 1){
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpLabeling, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpLabelingConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
			mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
		}else{
			break;
		}
		DEBUGPRINT("\n");

	}
	lmrcImageFFT(out, &tmpFFTOut, 0);
	
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpLabeling, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpLabelingConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandAreaAndLocationwithCounter");

}

void
lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, 
lmrcImageLabelingMode labelingmode)
{
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;
	mrcImage tmpOut;

	mrcImage tmpBinarization;
	mrcImage tmpBinaryConstraint;
	mrcImage tmpOrientation;
	mrcImage tmpOrientationConstraint;
	mrcImage tmpLabeling;
	mrcImage tmpLabelingConstraint;
	mrcImage tmpDensityConstraint;

	int i = 0;
	int j = 0;
	float delta, thres;
	double scale;
	int flag = 1;

	DEBUGPRINT1("%d mode Start\n", mode);
	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}
	
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);

	do{
		DEBUGPRINT1("%d\n", i + 1);

		tmpBinarization.Header = inPrev->Header;
		mrcInit(&tmpBinarization, NULL);
		tmpBinaryConstraint.Header = inPrev->Header;
		mrcInit(&tmpBinaryConstraint, NULL);
		tmpOrientation.Header = inPrev->Header;
		mrcInit(&tmpOrientation, NULL);
		tmpOrientationConstraint.Header = inPrev->Header;
		mrcInit(&tmpOrientationConstraint, NULL);
		tmpLabeling.Header = inPrev->Header;
		mrcInit(&tmpLabeling, NULL);
		tmpLabelingConstraint.Header = inPrev->Header;
		mrcInit(&tmpLabelingConstraint, NULL);
		tmpDensityConstraint.Header = inPrev->Header;
		mrcInit(&tmpDensityConstraint, NULL);

		thres = linfo.max - j * linfo.deltaDens;	
		if(thres < linfo.min){
			thres = linfo.min;
		}
		linfo.tmpscale = thres / 100;	
		/*Real Space*/
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(&tmpBinarization, 
		&tmpBinaryConstraint, inPrev, linfo, mode );
		lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
		&tmpOrientationConstraint, inPrev, linfo, mode);
		lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling(&tmpOrientation, &tmpLabeling, &tmpLabelingConstraint, 
		inPrev, linfo, mode, labelingmode);

		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpDensityConstraint, 
		&tmpLabelingConstraint, linfo, mode);

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpDensityConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);
		lmrcImageFFT(&tmpOut, &tmpFFTOut, 0);

		if(i == linfo.t - 1){
			flag = 0;
		}else if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo) && 
		thres == linfo.min){
			flag = 0;
		}else{
			if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo)){
				j++;
			}
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpLabeling, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpLabelingConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
			mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
		}
		i++;

	}while(flag);
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpLabeling, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpLabelingConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandLabelingandDensityforConvergencewithCounter");

}



void 
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	
	mrcImage tmpConstraint;
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;
	//mrcImage tmpOut;

	int i;
	float t;
	float delta;
	float thres;
	double scale;

	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);

	if(!linfo.flaghvp){
		fprintf(stderr, "-hvp is required.\n");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("i = %d\n", i);
		/*AreaAndLocation*/	
		tmpConstraint.Header = inPrev->Header;
		mrcInit(&tmpConstraint, NULL); 
		
		/* Real Space */
		if(linfo.t <= 2){
			t = 1.0;
		}else{
			t = (float)((i + 2) / 2) / ((linfo.t + 1) / 2 );
		}	
		lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpConstraint, inPrev, linfo, mode, t);

		/*  Fourier Space */
		lmrcImageFFT(&tmpFFTConstraint, &tmpConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);	

		lmrcImageSuperResolutionFourierSpaceCalculatingwithLowpassfilter(&tmpConstraint, &tmpFFTConstraint, &tmpFFTOrg, 
		&tmpFFTOut, &tmpFFTPrev, linfo);
		i++;

		if(i <= (linfo.t - 1)){
			DEBUGPRINT1("i=%d\n", i);
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
		
			/*Density*/
			tmpConstraint.Header = inPrev->Header;
			mrcInit(&tmpConstraint, NULL); 
			/* Real Space */
			delta = (linfo.max - linfo.min) / (linfo.t / 2 - 1);
			thres = linfo.max - ((i - 1) / 2) * delta;
			
			scale = thres / 100;
			lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpConstraint, inPrev, linfo, mode);

			/*  Fourier Space */
			lmrcImageFFT(&tmpFFTConstraint, &tmpConstraint, 0);
			lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
			tmpFFTOut.Header = tmpFFTPrev.Header;
			mrcInit(&tmpFFTOut, NULL);	
	
			lmrcImageSuperResolutionFourierSpaceCalculatingwithLowpassfilter(&tmpConstraint, &tmpFFTConstraint, &tmpFFTOrg, 
			&tmpFFTOut, &tmpFFTPrev, linfo);
			/* Real Space */
			if(i != linfo.t - 1){
				mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
				lmrcImageFFT(inPrev, &tmpFFTOut, 0);
				mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
				mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
				mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
				mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
			}else{
				break;
			}
		
		}else{
			break;
		}
		DEBUGPRINT("\n");
	}
	

	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithLowpassfilter");


	//mrcImageFree(&tmpOut, 0);
	
}

void 
lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandOrientationandAreaAndLocationandDensitywithCounter
(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpBinaryConstraint;
	mrcImage tmpAreaDensityConstraint;
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOut;
	mrcImage tmpFFTOrg;
	mrcImage tmpBinarization;
	mrcImage tmpOrientation;
	mrcImage tmpOrientationConstraint;

	int i;
	int j = 0;
	float t;
	float delta, thres;

	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}	
	
	thres = linfo.max;
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);
	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("i = %d\n", i);

		tmpBinaryConstraint.Header = inPrev->Header;
		mrcInit(&tmpBinaryConstraint, NULL);
		tmpAreaDensityConstraint.Header = inPrev->Header;
		mrcInit(&tmpAreaDensityConstraint, NULL);
		tmpBinarization.Header = inPrev->Header;
		mrcInit(&tmpBinarization, NULL);
		tmpOrientation.Header = inPrev->Header;
		mrcInit(&tmpOrientation, NULL);
		tmpOrientationConstraint.Header = inPrev->Header;
		mrcInit(&tmpOrientationConstraint, NULL);

		/*Real Space*/
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(&tmpBinarization, 
		&tmpBinaryConstraint, inPrev, linfo, mode);
		lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
		&tmpOrientationConstraint, inPrev, linfo, mode);
		if(linfo.t <= 2){
			t = 1.0;
		}else{
			t = (float)((i + 2) / 2) / ((linfo.t + 1) / 2);
		}
		lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpAreaDensityConstraint, &tmpOrientationConstraint, 
		linfo, mode, t);

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpAreaDensityConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);
		
		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);
		i++;
		if(i <= linfo.t - 1){
			DEBUGPRINT1("%d\n", i);
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpAreaDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			
			/*Density*/
			tmpBinaryConstraint.Header = inPrev->Header;
			mrcInit(&tmpBinaryConstraint, NULL);
			tmpAreaDensityConstraint.Header = inPrev->Header;
			mrcInit(&tmpAreaDensityConstraint, NULL);
			tmpOrientation.Header = inPrev->Header;
			mrcInit(&tmpOrientation, NULL);
			tmpOrientationConstraint.Header = inPrev->Header;
			mrcInit(&tmpOrientationConstraint, NULL);

			linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(&tmpBinarization, 
			&tmpBinaryConstraint, inPrev, linfo, mode );
			lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(&tmpBinarization, &tmpOrientation, 
			&tmpOrientationConstraint, inPrev, linfo, mode);
			if(linfo.flagdeltaDens && thres > linfo.min){
				thres = linfo.max - j * linfo.deltaDens;
				j++;
				DEBUGPRINT1("thres = %lf\n", thres);
			}else{
				delta = (linfo.max - linfo.min) / (linfo.t / 2 - 1);
				thres = linfo.max - (i - 1) / 2 * delta;
			}
			linfo.tmpscale = thres / 100;
			linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpAreaDensityConstraint, 
			&tmpOrientationConstraint, linfo, mode);
			/*Fourier Space*/	
			lmrcImageFFT(&tmpFFTConstraint, &tmpAreaDensityConstraint, 0);
			lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
			tmpFFTOut.Header = tmpFFTPrev.Header;
			mrcInit(&tmpFFTOut, NULL);

			lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, 
			&tmpFFTPrev, linfo);
			if(i != linfo.t - 1){
				mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				lmrcImageFFT(inPrev, &tmpFFTOut, 0);
				mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpAreaDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
			}else{
				break;
			}

		}else{
			break;
		}
		DEBUGPRINT("\n");
	}
	lmrcImageFFT(out, &tmpFFTOut, 0 );
	mrcImageFree(&tmpBinaryConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpAreaDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpBinarization, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpOrientation, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpOrientationConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarizationandAreaAndLocationandDensitywithCounter");
}
void
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpConstraint;
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;

	int i;
	int j = 0;
	float t;
	float delta;
	float thres;
	double scale;

	
	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}
	thres = linfo.max;
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);
	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("i=%d\n", i);

		tmpConstraint.Header = inPrev->Header;
		mrcInit(&tmpConstraint, NULL);

		/*Real Space*/	
		if(linfo.t <= 2){
			t = 1.0;
		}else{
			t = (float)((i + 2) / 2) / ((linfo.t + 1) / 2);
 		}
		lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpConstraint, inPrev, linfo, mode, t);

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, linfo);
		i++;
		if(i <= linfo.t - 1){
			
			DEBUGPRINT1("i=%d\n", i);
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");

			/*Density*/
			tmpConstraint.Header = inPrev->Header;
			mrcInit(&tmpConstraint, NULL);
			if(linfo.flagdeltaDens && thres > linfo.min){
				thres = linfo.max - j * linfo.deltaDens;
				j++;
			}else{
				delta = (linfo.max - linfo.min) / (linfo.t / 2 - 1);
				thres = linfo.max - (i - 1) / 2 *delta;
			}
			scale = thres / 100;
			linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpConstraint, inPrev, linfo, mode);

			/*Fourier Space*/
			lmrcImageFFT(&tmpFFTConstraint, &tmpConstraint, 0);
			lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
			tmpFFTOut.Header = tmpFFTPrev.Header;
			mrcInit(&tmpFFTOut, NULL);

			lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, linfo);

			/*Real Space*/ 
			if(i != linfo.t - 1){
				mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
				lmrcImageFFT(inPrev, &tmpFFTOut, 0);
				mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
				mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
			}else{
				break;
			}
		}else{
			break;
		}
		DEBUGPRINT("\n");
	}
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensitywithCounter");

	
}

void
lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	
	mrcImage tmpConstraint;
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;

	int i;
	float delta;
	float thres;
	double scale;

	if(!linfo.flaghvp){
		fprintf(stderr, "-hvp is required.\n");
		exit(EXIT_FAILURE);
	}

	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);

	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("i=%d\n", i);
		tmpConstraint.Header = inPrev->Header;
		mrcInit(&tmpConstraint, NULL);

		/*Real Space*/
		delta = (linfo.max - linfo.min) / (linfo.t - 1);
		thres = linfo.max - i*delta;
	
		scale = thres / 100;
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpConstraint, inPrev, linfo, mode);

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithLowpassfilter(&tmpConstraint, &tmpFFTConstraint, &tmpFFTOrg, 
		&tmpFFTOut, &tmpFFTPrev, linfo);
		
		if(i != linfo.t - 1){
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
		}else{
			break;
		}

		DEBUGPRINT("\n");
	}
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithLowpassfilter");

}


void
lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter(mrcImage* out, mrcImage* inPrev, mrcImage* inOrg, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpDensityConstraint;
	mrcImage tmpSubConstraint;
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;
	int i;
	float delta;
	float thres;

	DEBUGPRINT1("mode%d Start\n", mode);
	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}

	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);

	for(i = 0; i < linfo.t; i++){
		DEBUGPRINT1("i=%d\n", i);
		tmpDensityConstraint.Header = inPrev->Header;
		mrcInit(&tmpDensityConstraint, NULL);
		tmpSubConstraint.Header = inPrev->Header;
		mrcInit(&tmpSubConstraint, NULL);
	
		/*Real Space*/
		if(linfo.t == 1){
			delta = 0.0;
		}else{
			delta = (linfo.max - linfo.min) / (linfo.t - 1);
		}
		thres = linfo.max - i*delta;
		linfo.tmpscale = thres / 100;
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpDensityConstraint, inPrev, linfo, mode);
		if(linfo.flagSub){
			DEBUGPRINT("Sub mode\n");
			lmrcImageSubtraction(&tmpSubConstraint, &tmpDensityConstraint, linfo.tmpdensity);
			lmrcImageFFT(&tmpFFTConstraint, &tmpSubConstraint, 0);
		}else{
			DEBUGPRINT("non SUb mode\n");
			lmrcImageFFT(&tmpFFTConstraint, &tmpDensityConstraint, 0);
		}

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);
		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, linfo);

		if(i != linfo.t - 1){
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
			mrcImageFree(&tmpSubConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
		}else{
			break;
		}
		DEBUGPRINT("\n");
	}
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
	mrcImageFree(&tmpSubConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensitywithCounter");
}

void
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationforConvergencewithCounter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{

}
void
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode )
{
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;
	mrcImage tmpOut;
	mrcImage tmpAreaConstraint;
	mrcImage tmpDensityConstraint;

	int i = 0, j = 0, k = 0;
	float t = 0.0 ;
	float thres;
	double scale;
	int flag = 1; 
		
	DEBUGPRINT1("mode%d Start\n", mode);	

	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}
	
	do{
		DEBUGPRINT1("i = %d\n", i);

		tmpAreaConstraint.Header = inPrev->Header;
		mrcInit(&tmpAreaConstraint, NULL);
		
		/*Real Space*/
		t += (j + 1) * linfo.deltaArea; 
		if(t > 1.0){
			t = 1.0;
		}	
		lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(&tmpAreaConstraint, inPrev, linfo, mode, t);

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpAreaConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);

		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, linfo);
		/*Real Space*/
		lmrcImageFFT(&tmpOut, &tmpFFTOut, 0);
		if(i == linfo.tmax - 1){
			flag = 0;
		}else if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo) && 1.0 == t){
			flag = 0;
		}else{
			if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo)){
				j++;	
			}
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
			mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
			mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
			
			i++;

			DEBUGPRINT1("i = %d\n", i);
			tmpDensityConstraint.Header = inPrev->Header;
			mrcInit(&tmpDensityConstraint, NULL);
	
			thres = linfo.max - k * linfo.deltaDens;
			if(thres < linfo.min){
				thres = linfo.min;
			}
			scale = thres / 100;		
			linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpDensityConstraint, inPrev, linfo, 
			mode);
	
			/*Fourier Space*/
			lmrcImageFFT(&tmpFFTConstraint, &tmpDensityConstraint, 0);
			lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
			tmpFFTOut.Header = tmpFFTPrev.Header;
			mrcInit(&tmpFFTOut, NULL);
			lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, linfo);
			/*Real Space*/
			lmrcImageFFT(&tmpOut, &tmpFFTOut, 0);
			if(linfo.tmax - 1){
				flag = 0;
			}else if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo) && thres == linfo.min){
				flag = 0;
			}else{
 				if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo)){
					k++;
				}	
				mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
				lmrcImageFFT(inPrev, &tmpFFTOut, 0);
				mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
				mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
				mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
				mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
				mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
			}
		}
		
	}while(flag);
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
	mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
	mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
	mrcImageFree(&tmpAreaConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocationandDensityforConvergencewithConter");
	

}
void 
lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter(mrcImage* out, mrcImage* inPrev, 
mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpDensityConstraint;
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;
	mrcImage tmpOut;

	int i = 0;
	int j = 0;
	float thres;
	double scale;
	int flag = 1;
	
	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}

	DEBUGPRINT1("mode%d Start\n", mode);

	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);
	do{
		DEBUGPRINT1("i = %d\n", i + 1);
		/*Real Space*/
		thres = linfo.max - j * linfo.deltaDens;
		if( thres < linfo.min){
			thres = linfo.min;
		}
		tmpDensityConstraint.Header = inPrev -> Header;
		mrcInit(&tmpDensityConstraint, NULL);
		scale = thres / 100;
	
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpDensityConstraint, inPrev, linfo, mode);

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpDensityConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);
		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);
		lmrcImageFFT(&tmpOut, &tmpFFTOut, 0);
		if(i == linfo.tmax - 1){
			flag = 0;
			DEBUGPRINT("Automatical end\n");
		}else if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo) && 
		thres == linfo.min){
			DEBUGPRINT("Program Done.\n");
			flag = 0;
		}else{
 			/*Real Space*/ 
			if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo)){
				j++;
			}
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
			mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
		}			
		i++;
	}while(flag);
	
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");
	mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensityforConvergencewithCounter");


}

void
lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter(mrcImage* out, 
mrcImage* inPrev, mrcImage* inOrg, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImage tmpFFTConstraint;
	mrcImage tmpFFTPrev;
	mrcImage tmpFFTOrg;
	mrcImage tmpFFTOut;
	mrcImage tmpOut;
	mrcImage tmpDensityConstraint;
	mrcImage tmpNonnegativeConstraint;

	int i = 0;
	int j = 0;
	float thres;
	double scale;
	int flag = 1;
	
	DEBUGPRINT1("mode%d Strat\n", mode);

	if(!linfo.flagFFTInCount){
		fprintf(stderr, "-ic is required.\n");
		exit(EXIT_FAILURE);
	}
	lmrcImageFFT(&tmpFFTOrg, inOrg, 0);

	do{
		thres = linfo.max - j * linfo.deltaDens;
		if(thres < linfo.min){
			thres = linfo.min;
		}
		scale = thres / 100;
		/*Real Space*/
		tmpDensityConstraint.Header = inPrev->Header;
		mrcInit(&tmpDensityConstraint, NULL);
		tmpNonnegativeConstraint.Header = inPrev->Header;
		mrcInit(&tmpNonnegativeConstraint, NULL);

		DEBUGPRINT1("i = %d\n", i+1);
		lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeConstraint(&tmpNonnegativeConstraint, inPrev, linfo);
		linfo.tmpdensity = lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(&tmpDensityConstraint, 
		&tmpNonnegativeConstraint, linfo, mode);

		/*Fourier Space*/
		lmrcImageFFT(&tmpFFTConstraint, &tmpDensityConstraint, 0);
		lmrcImageFFT(&tmpFFTPrev, inPrev, 0);
		tmpFFTOut.Header = tmpFFTPrev.Header;
		mrcInit(&tmpFFTOut, NULL);
		lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(&tmpFFTConstraint, &tmpFFTOrg, &tmpFFTOut, &tmpFFTPrev, 
		linfo);
		lmrcImageFFT(&tmpOut, &tmpFFTOut, 0);

		if(i == linfo.tmax - 1){
			flag = 0;	
			DEBUGPRINT("Automatical End.\n");
		}else if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo) && thres == linfo.min){
			flag = 0;	
			DEBUGPRINT("Program Done.\n");
		}else{
			/*Real Space*/
			if(lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(inPrev, &tmpOut, linfo)){
				j++;
			}
			mrcImageFree(inPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
			lmrcImageFFT(inPrev, &tmpFFTOut, 0);
			mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
			mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
			mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
			mrcImageFree(&tmpNonnegativeConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
			mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
		}
		i++;
	}while(flag);
	lmrcImageFFT(out, &tmpFFTOut, 0);
	mrcImageFree(&tmpFFTConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTPrev, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTOrg, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
	mrcImageFree(&tmpFFTOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
	mrcImageFree(&tmpOut, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
	mrcImageFree(&tmpNonnegativeConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");
	mrcImageFree(&tmpDensityConstraint, "in lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeandDensityforConvergencewithCounter");

}
void
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation(mrcImage* tmpConstraint, mrcImage* inPrev, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, float t)
{

	double data;
	int x0i, y0i, z0i;
	int x1i, y1i, z1i;
	//int	thresx, thresy, thresz; 
	mrcImageParaTypeReal x, y, z;
	char s[1024];
	static int i = 0; 

	/*Shape 0*/
	if(linfo.shape == 0){

		DEBUGPRINT1("t=%lf\n", t);
		x0i = (int)(((1 - t) * linfo.x00 + t * linfo.x01) + 0.5);
		y0i = (int)(((1 - t) * linfo.y00 + t * linfo.y01) + 0.5);
		z0i = (int)(((1 - t) * linfo.z00 + t * linfo.z01) + 0.5);
		x1i = (int)(((1 - t) * linfo.x10 + t * linfo.x11) + 0.5);
		y1i = (int)(((1 - t) * linfo.y10 + t * linfo.y11) + 0.5);
		z1i = (int)(((1 - t) * linfo.z10 + t * linfo.z11) + 0.5);
		
		DEBUGPRINT6("%d%d%d%d%d%d\n", x0i,y0i,z0i,x1i,y1i,z1i);
		for(z = 0.0; z < tmpConstraint->HeaderN.z; z++){
		for(y = 0.0; y < tmpConstraint->HeaderN.y; y++){
		for(x = 0.0; x < tmpConstraint->HeaderN.x; x++){
			mrcPixelDataGet(inPrev, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if((z0i <= z && z <= z1i) && (y0i <= y && y <= y1i) && (x0i <= x && x <= x1i)){
				mrcPixelDataSet(tmpConstraint, x, y, z, data, mrcPixelRePart);
			}else{
				mrcPixelDataSet(tmpConstraint, x, y, z, 0.0, mrcPixelRePart);
			}
			
		}	
		}
		}


	}
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpconstraint-area--%03d.mrc3d", i);
	//mrcFileWrite(tmpConstraint, s, NULL, 0);
	i++;
}
float
lmrcImageSuperResolutionRealSpaceCalculatingbyAreaAndLocation2(mrcImage* tmpConstraint, mrcImage* inPrev, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, float t)
{

	double dstdata, data, data0, data1, data2;
	int x0i, y0i, z0i;
	int x1i, y1i, z1i;
	//int	thresx, thresy, thresz; 
	mrcImageParaTypeReal x, y, z;
	char s[1024];
	static int i = 0; 

	
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpconstraint-area2-prev%03d.mrc3d", i);
	//mrcFileWrite(inPrev, s, NULL, 0);

	/*Shape 0*/
	if(linfo.shape == 0){

		DEBUGPRINT1("t=%lf\n", t);
		x0i = (int)(((1 - t) * linfo.x00 + t * linfo.x01) + 0.5);
		y0i = (int)(((1 - t) * linfo.y00 + t * linfo.y01) + 0.5);
		z0i = (int)(((1 - t) * linfo.z00 + t * linfo.z01) + 0.5);
		x1i = (int)(((1 - t) * linfo.x10 + t * linfo.x11) + 0.5);
		y1i = (int)(((1 - t) * linfo.y10 + t * linfo.y11) + 0.5);
		z1i = (int)(((1 - t) * linfo.z10 + t * linfo.z11) + 0.5);
		
		DEBUGPRINT6("%d%d%d%d%d%d\n", x0i,y0i,z0i,x1i,y1i,z1i);
		for(z = 0.0; z < tmpConstraint->HeaderN.z; z++){
		for(y = 0.0; y < tmpConstraint->HeaderN.y; y++){
		for(x = 0.0; x < tmpConstraint->HeaderN.x; x++){
			mrcPixelDataGet(inPrev, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if((z0i <= z && z <= z1i) && (y0i <= y && y <= y1i) && (x0i <= x && x <= x1i)){
				mrcPixelDataSet(tmpConstraint, x, y, z, data, mrcPixelRePart);
			}else{
				mrcPixelDataSet(tmpConstraint, x, y, z, 0.0, mrcPixelRePart);
			}
			
		}	
		}
		}

		for(z = 0.0; z < tmpConstraint->HeaderN.z; z++){
		for(y = 0.0; y < tmpConstraint->HeaderN.y; y++){
		for(x = 0.0; x < tmpConstraint->HeaderN.x; x++){
			if(z == z0i && y == y0i && x == x0i){
				mrcPixelDataGet(tmpConstraint, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
			}else if(z == z1i && y == y1i && x == x1i){
				mrcPixelDataGet(tmpConstraint, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
			}
		}
		}
		}
		data0 = MIN(data1, data2);

		DEBUGPRINT1("data0 = %lf\n", data0);
		return(data0);


	}
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpconstraint-area2--%03d.mrc3d", i);
	//mrcFileWrite(tmpConstraint, s, NULL, 0);
	i++;
}
void 
lmrcImageSuperResolutionRealSpaceCalculatingbyNonnegativeConstraint(mrcImage* tmpNonnegativeConstraint, mrcImage* inPrev, 
lmrcImageSuperResolutionInfo linfo)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	double dstre;

	for(z = 0.0; z < inPrev->HeaderN.z; z++){
	for(y = 0.0; y < inPrev->HeaderN.y; y++){
	for(x = 0.0; x < inPrev->HeaderN.x; x++){
		mrcPixelDataGet(inPrev, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data < 0.0 ){
			dstre = data * 0.5;
			mrcPixelDataSet(tmpNonnegativeConstraint, x, y, z, dstre, mrcPixelRePart);
		}else{
			mrcPixelDataSet(tmpNonnegativeConstraint, x, y, z, data, mrcPixelRePart);
		}	
	}
	}
	}

}

float
lmrcImageSuperResolutionRealSpaceCalculatingbyDensity(mrcImage* tmpConstraint, mrcImage* inPrev, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode) 
{ 
	mrcImageParaTypeReal x, y, z;
	float* data;
	double tmpdata, vol;
	int j;
	unsigned long n, k, level;
	float density;
	char s[1024];
	static int i = 0;
		
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/density-inprev-%03d.mrc3d", i);
	//mrcFileWrite(inPrev, s, NULL, 0);

	DEBUGPRINT("a");
	n = tmpConstraint->HeaderN.x * tmpConstraint->HeaderN.y * tmpConstraint->HeaderN.z;
	DEBUGPRINT3("Headerx=%d Headery =%d Headerx=%d\n", tmpConstraint->HeaderN.x, tmpConstraint->HeaderN.y, 
	tmpConstraint->HeaderN.z);
	DEBUGPRINT1("n = %d\n", n);

	data = (float*) memoryAllocate(sizeof(float) * (n + 1), "in lmrcImageSuperResolutionRealSpaceCalculatingbyDensity");
	
	j = 1;
	for(z = 0; z < tmpConstraint->HeaderN.z; z++){
	for(y = 0; y < tmpConstraint->HeaderN.y; y++){
	for(x = 0; x < tmpConstraint->HeaderN.x; x++){
		mrcPixelDataGet(inPrev, x, y, z, &(tmpdata), mrcPixelRePart, mrcPixelHowNearest);
		data[j] = tmpdata;
		j++;
	}
	}
	}
	
	DEBUGPRINT("b");
	vol = tmpConstraint->HeaderLength.x * tmpConstraint->HeaderLength.y * tmpConstraint->HeaderLength.z;
	level = ((double)linfo.nMolecule) * linfo.MolecularWeight / linfo.Density * 10.0 / 6.02;

	DEBUGPRINT2("vol = %lf level = %d\n",vol, level);
	DEBUGPRINT1("scale=%lf\n", linfo.tmpscale);

	if(linfo.Inverse == 0){
		k = (unsigned int)((double)level) * linfo.tmpscale / vol;
	}else{	
		k = n - (unsigned int)((double)level) * linfo.tmpscale / vol;
	}

	density = nrselect(k, n, data);
	DEBUGPRINT2("k =%d n = %d\n", k , n);
	DEBUGPRINT1("density = %lf\n", density);

	for(z = 0; z < tmpConstraint->HeaderN.z; z++){
	for(y = 0; y < tmpConstraint->HeaderN.y; y++){
	for(x = 0; x < tmpConstraint->HeaderN.x; x++){
		mrcPixelDataGet(inPrev, x, y, z, &(tmpdata), mrcPixelRePart, mrcPixelHowNearest);
		if(tmpdata >= density){
			mrcPixelDataSet(tmpConstraint, x, y, z, tmpdata, mrcPixelRePart);
		}else{
			mrcPixelDataSet(tmpConstraint, x, y, z, 0.0, mrcPixelRePart);
		}
	}
	}
	}
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/density-tmpconstraint-%03d.mrc3d", i);
	//mrcFileWrite(tmpConstraint, s, NULL, 0);
	DEBUGPRINT("c\n");
	free(data);
	i++;
	return(density);
}	

float
lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization(mrcImage* tmpBinarization, mrcImage* tmpBinaryConstraint, 
mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{

	mrcImageParaTypeReal x, y, z;
	float* data;
	double tmpdata, dstre, vol;
	
	static int i = 0;
	int j;
	unsigned long n, k, level;
	float density;
	char s[1024];

	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/binary-inprev-%03d.mrc3d", i);	
	//mrcFileWrite(inPrev, s, NULL, 0);	

	n = inPrev->HeaderN.x * inPrev->HeaderN.y * inPrev->HeaderN.z;
	DEBUGPRINT1("n=%d\n", n);
	data = (float*) memoryAllocate(sizeof(float) * (n + 1), "in lmrcImageSuperResolutionRealSpaceCalculatingbyBinarization");
	
	j = 1;
	for(z = 0.0; z < inPrev->HeaderN.z; z++){
	for(y = 0.0; y < inPrev->HeaderN.y; y++){
	for(x = 0.0; x < inPrev->HeaderN.x; x++){
		mrcPixelDataGet(inPrev, x, y, z, &(tmpdata), mrcPixelRePart, mrcPixelHowNearest);
		data[j] = tmpdata;
		j++;
	}
	}
	}

	vol = inPrev->HeaderLength.x * inPrev->HeaderLength.y * inPrev->HeaderLength.z;
	level = ((double)linfo.nMolecule) * linfo.MolecularWeight / linfo.Density * 10.0 / 6.02;
	DEBUGPRINT2("vol = %lf level = %d\n",vol, level);

	if(linfo.Inverse == 0){
		k = (unsigned int)((double)level) * linfo.tmpscale / vol;
	}else{
		k = n - (unsigned int)((double)level) * linfo.tmpscale / vol;
	}
	density = nrselect(k, n, data);
	DEBUGPRINT1("density=%lf\n", density);

	for(z = 0.0; z < inPrev->HeaderN.z; z++){
	for(y = 0.0; y < inPrev->HeaderN.y; y++){
	for(x = 0.0; x < inPrev->HeaderN.x; x++){
		mrcPixelDataGet(inPrev, x, y, z, &tmpdata, mrcPixelRePart, mrcPixelHowNearest);
		if(tmpdata >= density){
			mrcPixelDataSet(tmpBinarization, x, y, z, 1.0, mrcPixelRePart);
		}else{
			mrcPixelDataSet(tmpBinarization, x, y, z, 0.0, mrcPixelRePart);
		}
	}
	}
	}

	for(z = 0.0; z < inPrev->HeaderN.z; z++){
	for(y = 0.0; y < inPrev->HeaderN.y; y++){
	for(x = 0.0; x < inPrev->HeaderN.x; x++){
		mrcPixelDataGet(inPrev, x, y, z, &tmpdata, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(tmpBinarization, x, y, z, &dstre, mrcPixelRePart, mrcPixelHowNearest);
		if(dstre == 1.0){
			mrcPixelDataSet(tmpBinaryConstraint, x, y, z, tmpdata, mrcPixelRePart);
		}else if(dstre == 0.0){
			mrcPixelDataSet(tmpBinaryConstraint, x, y, z, 0.0, mrcPixelRePart);
		}else{
			fprintf(stderr, "binary error\n");
			exit(EXIT_FAILURE);
		}

	}
	}
	}
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpBinarization-%03d.mrc3d", i);
	//mrcFileWrite(tmpBinarization, s, NULL, 0);
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpBinaryConstraint-%03d.mrc3d", i);
	//mrcFileWrite(tmpBinaryConstraint, s, NULL, 0);
	
	
	free(data);
	i++;
	
	return(density);
}
void
lmrcImageSuperResolutionRealSpaceCalculatingbyOrientation(mrcImage* tmpBinarization, mrcImage* tmpOrientation, 
mrcImage* tmpOrientationConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	double tmpcenter;
	double tmpright, tmpleft;
	double tmpover, tmpbelow;
	double tmpforward, tmpbackward;
	double tmpdata, dstre;
	mrcImageParaTypeReal x, y, z;
	char s[1024];
	static int i = 0;


	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(tmpBinarization, x, y, z, &tmpcenter, mrcPixelRePart, mrcPixelHowNearest);
		if(1.0 == tmpcenter){
			mrcPixelDataGet(tmpBinarization, x + 1.0, y, z, &tmpright, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpBinarization, x - 1.0, y, z, &tmpleft, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpBinarization, x, y + 1.0, z, &tmpover, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpBinarization, x, y - 1.0, z, &tmpbelow, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpBinarization, x, y, z + 1.0, &tmpforward, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpBinarization, x, y, z - 1.0, &tmpbackward, mrcPixelRePart, mrcPixelHowNearest);
			if(0.0 == tmpright && 0.0 == tmpleft && 0.0 == tmpover && 0.0 == tmpbelow && 0.0 == tmpforward && 0.0 == tmpbackward){
				mrcPixelDataSet(tmpOrientation, x, y, z, 0.0, mrcPixelRePart);
			}else{
				mrcPixelDataSet(tmpOrientation, x, y, z, 1.0, mrcPixelRePart);
			}
		}else if(0.0 == tmpcenter){
			mrcPixelDataSet(tmpOrientation, x, y, z, 0.0, mrcPixelRePart);
		}else{
			fprintf(stderr, "orientation error\n" );
			exit(EXIT_FAILURE);
		}
	}
	}
	}


	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(tmpOrientation, x, y, z, &tmpdata, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(inPrev, x, y, z, &dstre, mrcPixelRePart, mrcPixelHowNearest);
		if(tmpdata == 1.0){
			mrcPixelDataSet(tmpOrientationConstraint, x, y, z, dstre, mrcPixelRePart);
		}else if(tmpdata == 0.0){
			mrcPixelDataSet(tmpOrientationConstraint, x, y, z, 0.0, mrcPixelRePart);
		}else{
			fprintf(stderr, "orientation error\n");
			exit(EXIT_FAILURE);
		}

	}
	}
	}

	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpOrientation-%d.mrc3d", i);
	//mrcFileWrite(tmpOrientation, s, NULL, 0);
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpOrientationConstraint-%d.mrc3d", i);
	//mrcFileWrite(tmpOrientationConstraint, s, NULL, 0);

	i++;
}

void
lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling(mrcImage* tmpOrientation ,mrcImage* tmpLabeling, 
mrcImage* tmpLabelingConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, 
lmrcImageLabelingMode labelingmode)
{
	switch(labelingmode & 0xfff){
		case TheLargestLabelingSearch:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling1(tmpOrientation, tmpLabeling, tmpLabelingConstraint, 
			inPrev, linfo, mode);
			break;
		}
		case SomeVolumeLabelingSearch:{
			lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling2(tmpOrientation, tmpLabeling, tmpLabelingConstraint, 
			inPrev, linfo, mode);
			break;
		}
		default:{
			fprintf(stderr, "Please select Labeling mode\n", labelingmode);
			exit(EXIT_FAILURE);
			break;
		}
		
	}
}
void
lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling1(mrcImage* tmpOrientation,  mrcImage* tmpLabeling, 
mrcImage* tmpLabelingConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{

	mrcImageParaTypeReal x, y, z;
	mrcImage label;
	double data, data0, data1, data2, data3, dstre;
	int sum[100000];
	int number, lastnumber, targetlabel;
	int total;
	int i;
	int j = 0;
	static int k = 0;
	char s[1024];
	double mindata, maxdata;
	
	label.Header = tmpOrientation->Header;
	mrcInit(&label, NULL);
	
	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataSet(&label, x, y, z, 0.0, mrcPixelRePart);
	}
	}
	}
	
	do{

		DEBUGPRINT1("j=%d\n", j);
		number = 0;
		total = 0;
		for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
		for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
		for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
			mrcPixelDataGet(tmpOrientation, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(data == 1.0){
				mrcPixelDataGet(&label, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x - 1.0, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y - 1.0, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y, z - 1.0, &data3, mrcPixelRePart, mrcPixelHowNearest);
				
				if(data0 == 0.0 && data1 == 0.0 && data2 == 0.0 && data3 == 0.0){
					number++;
					mrcPixelDataSet(&label, x, y, z, number, mrcPixelRePart);
				}else if(data1 != 0.0 || data2 != 0.0 || data3 != 0.0){
					mindata = data0;
					if(data1 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data1);
						}else{
							mindata = data1;
			 			}
					}
					if(data2 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data2);
						}else{
							mindata = data2;
						}
					}
					if(data3 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data3);
						}else{
							mindata = data3;
						}
					}
					if(mindata != data0){
						mrcPixelDataSet(&label, x, y, z, mindata, mrcPixelRePart);
						total++;
					}
				}
			}	

		}
		}
		}
		DEBUGPRINT1("total1=%d\n", total);
		DEBUGPRINT1("number1=%d\n", number);

		number = 0; 
		for(z = tmpOrientation->HeaderN.z ; z > 0.0; z--){
		for(y = tmpOrientation->HeaderN.y ; y > 0.0; y--){
		for(x = tmpOrientation->HeaderN.x ; x > 0.0; x--){
			mrcPixelDataGet(tmpOrientation, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(data == 1.0){
				mrcPixelDataGet(&label, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x + 1.0, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y + 1.0, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y, z + 1.0, &data3, mrcPixelRePart, mrcPixelHowNearest);

				if(0.0 == data0 && 0.0 == data1 && 0.0 == data2 && 0.0 == data3){
					number++;
					mrcPixelDataSet(&label, x, y, z, number, mrcPixelRePart);
				}else if(data1 != 0.0 || data2 != 0.0 || data3 != 0.0){
					mindata = data0;
					if(data1 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data1);
						}else{
							mindata = data1;
						}
					}
					if(data2 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data2);
						}else{
							mindata = data2;
						}
					}
					if(data3 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data3);
						}else{
							mindata = data3;
						}
					}
					if(mindata != data0){
						mrcPixelDataSet(&label, x, y, z, mindata, mrcPixelRePart);
						total++;
					}
				}
			}
		}
		}
		}
		j++;
		DEBUGPRINT1("total2 =%d\n", total);
		DEBUGPRINT1("number2=%d\n", number);
	}while(total != 0);
	
	lastnumber = 1;	
	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(&label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data > lastnumber){
			lastnumber = data;
		}

	}
	}
	}
	for(i = 0; i <= lastnumber; i++){
		sum[i] = 0;
	}

	DEBUGPRINT1("lastnumber=%d\n", lastnumber);
	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(&label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data != 0.0){
			for(i = 1; i <= lastnumber; i++){
				if(i == data){
					sum[i]++;	
					break;
				}
			}	
		}else if(data == 0.0){
			sum[0]++;
		}
	}
	}
	}
/*	
	for(i = 0; i<= lastnumber; i++){
		if(sum[i] != 0){
			DEBUGPRINT2("sum[%d] = %d\n",i,sum[i]);
		}	
	}
*/
	maxdata = sum[1];
	targetlabel = 1;
	for(i = 1; i < lastnumber; i++){
		if(sum[i+1] != maxdata){
			if(sum[i + 1] > maxdata){
				maxdata = sum[i+1];
				targetlabel = i+1;
			}
		}
	}

	DEBUGPRINT1("targetlabel = %d\n", targetlabel);


	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(&label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data == targetlabel){
			mrcPixelDataSet(tmpLabeling, x, y, z, 1.0, mrcPixelRePart);	
		}else{
			mrcPixelDataSet(tmpLabeling, x, y, z, 0.0, mrcPixelRePart);
		}
	}
	}
	}

	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(tmpLabeling, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(inPrev, x, y, z, &dstre, mrcPixelRePart, mrcPixelHowNearest);
		if(data == 1.0){
			mrcPixelDataSet(tmpLabelingConstraint, x, y, z, dstre, mrcPixelRePart);
		}else{
			mrcPixelDataSet(tmpLabelingConstraint, x, y, z, 0.0, mrcPixelRePart);
		}
	}
	}
	}

	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpLabeling-%03d.mrc3d", k);
	//mrcFileWrite(tmpLabeling, s, NULL, 0);
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpLabelingConstraint-%03d.mrc3d", k);
	//mrcFileWrite(tmpLabelingConstraint, s, NULL, 0);

	mrcImageFree(&label, "in lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling");

	k++;

}

void
lmrcImageSuperResolutionRealSpaceCalculatingbyLabeling2(mrcImage* tmpOrientation, mrcImage* tmpLabeling, 
mrcImage* tmpLabelingConstraint, mrcImage* inPrev, lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImage label;
	double data, data0, data1, data2, data3, dstre;
	int sum[100000];
	int number, lastnumber, targetlabel;
	int total;
	int i;
	int j = 0;
	double mindata, maxdata;	
	
	label.Header = tmpOrientation->Header;
	mrcInit(&label, NULL);

	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataSet(&label, x, y, z, 0.0, mrcPixelRePart);
	}
	}
	}

	do{
		DEBUGPRINT1("j=%d\n", j);
		number = 0;
		total = 0;

		for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
		for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
		for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
			mrcPixelDataGet(tmpOrientation, x, y,z, &data, mrcPixelRePart, mrcPixelHowNearest);		
			if(data == 1.0){
				mrcPixelDataGet(&label, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x - 1.0, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y - 1.0, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y, z - 1.0, &data3, mrcPixelRePart, mrcPixelHowNearest);

				if(data0 == 0.0 && data1 == 0.0 && data2 == 0.0 && data3 == 0.0){
					number;
					mrcPixelDataSet(&label, x, y, z, number, mrcPixelRePart);
				}else if(data1 != 0.0 || data2 != 0.0 || data3 != 0.0){
					mindata = data0;
					if(data1 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data1);
						}else{
							mindata = data1;
						}
					}
					if(data2 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data2);
						}else{
							mindata = data2;
						}
					}
					if(data3 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data3);
						}else{
							mindata = data3;
						}
					}
					if(mindata != data0){
						mrcPixelDataSet(&label, x, y, z, mindata, mrcPixelRePart);
						total++;
					}
				}
			}
			
		}
		}
		}
		DEBUGPRINT1("total1 = %d\n", total);
		DEBUGPRINT1("number1= %d\n", number);

		number = 0;

		for(z = tmpOrientation->HeaderN.z; z > 0.0; z--){
		for(y = tmpOrientation->HeaderN.y; y > 0.0; y--){
		for(x = tmpOrientation->HeaderN.x; x > 0.0; x--){
			mrcPixelDataGet(tmpOrientation, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(data == 1.0){
				mrcPixelDataGet(&label, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x + 1.0, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y + 1.0, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&label, x, y, z + 1.0, &data3, mrcPixelRePart, mrcPixelHowNearest);

				if(0.0 == data0 && 0.0 == data1 && 0.0 == data2 && 0.0 == data3){
					number++;
					mrcPixelDataSet(&label, x, y, z, number, mrcPixelRePart);
				}else if(data1 != 0.0 || data2 != 0.0 || data3 != 0.0){
					mindata = data0;
					if(data1 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data1);
						}else{
							mindata = data1;
						}
					}
					if(data2 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data2);
						}else{
							mindata = data2;
						}
					}
					if(data3 != 0.0){
						if(mindata != 0.0){
							mindata = MIN(mindata, data3);
						}else{
							mindata = data3;
						}
					}
					if(mindata != data0){
						mrcPixelDataSet(&label, x, y, z, mindata, mrcPixelRePart);
						total++;
					}
				}
			}
		}
		}
		}
		j++;
		DEBUGPRINT1("total2=%d\n", total);
		DEBUGPRINT1("number2=%d\n", number);
	}while(total != 0);
	
	lastnumber = 1; 
	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(&label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data > lastnumber){
			lastnumber = data;
		}
	}
	}
	}
	for(i = 0; i <= lastnumber; i++){
		sum[i] = 0;
	}

	DEBUGPRINT1("lastnumber=%d\n", lastnumber);

	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(&label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data != 0.0){
			for(i = 1; i <= lastnumber; i++){
				if(i == data){
					sum[i]++;
					break;
				}
			}
		}else if(data == 0.0){
			sum[0]++;
		}
	}
	}
	}

	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(&label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(sum[(int)data] >= 145){
			mrcPixelDataSet(tmpLabeling, x, y, z, 1.0, mrcPixelRePart);
		}else{
			mrcPixelDataSet(tmpLabeling, x, y, z, 0.0, mrcPixelRePart);
		}
	}
	}
	}

	for(z = 0.0; z < tmpOrientation->HeaderN.z; z++){
	for(y = 0.0; y < tmpOrientation->HeaderN.y; y++){
	for(x = 0.0; x < tmpOrientation->HeaderN.x; x++){
		mrcPixelDataGet(tmpLabeling , x, y, z ,&data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(inPrev, x, y, z ,&dstre, mrcPixelRePart, mrcPixelHowNearest);
		if(data == 1.0){
			mrcPixelDataSet(tmpLabelingConstraint, x, y, z, dstre, mrcPixelRePart);
		}else{
			mrcPixelDataSet(tmpLabelingConstraint, x, y, z, 0.0, mrcPixelRePart);
		}

	}
	}
	}

	mrcImageFree(&label, NULL);
}
/*DoubleTiltMode*/
void
lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter(mrcImage* tmpFFTConstraint, mrcImage* tmpFFTOrg, 
mrcImage* tmpFFTOut, mrcImage* tmpFFTPrev, lmrcImageSuperResolutionInfo linfo)
{
	mrcImage FFTinCount; 
	double rePrev, reConstraint, reCount, imPrev, imConstraint, imCount, dstre, dstim;
	float iX, iY, iZ;
	float weight;
	static int k = 0;
	double counter;
	double tmpdata, rethres, imthres;
	static int i = 0;
	char s[1024];

	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpfftprev-%03d.fft", i);
	//mrcFileWrite(tmpFFTPrev, s, NULL, 0);
	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpfftconstraint-%03d.fft", i);
	//mrcFileWrite(tmpFFTConstraint, s, NULL, 0);

	mrcFileRead(&FFTinCount, linfo.FFTInCount, "in lmrcImageSuperResolutionFourierSpaceCalculatingDoubleMode", 0);
	tmpdata = linfo.weightmax - k * linfo.weightdelta;
	DEBUGPRINT2("k = %d tmp=%lf\n", k, tmpdata);

	for(iZ = -tmpFFTConstraint->HeaderN.z / 2.0; iZ < tmpFFTConstraint->HeaderN.z / 2.0; iZ++){
	for(iY = -tmpFFTConstraint->HeaderN.y / 2.0; iY < tmpFFTConstraint->HeaderN.y / 2.0; iY++){
	for(iX = 0.0; iX < tmpFFTConstraint->HeaderN.x / 2.0; iX++){
		mrcPixelDataGet(&FFTinCount, iX, iY, iZ, &reCount, mrcPixelRePart, mrcPixelHowNearest);
		counter = reCount;
		mrcPixelDataGet(tmpFFTPrev, iX, iY, iZ, &rePrev, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(tmpFFTPrev, iX, iY, iZ, &imPrev, mrcPixelImPart, mrcPixelHowNearest);
		mrcPixelDataGet(tmpFFTConstraint, iX, iY, iZ, &reConstraint, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(tmpFFTConstraint, iX, iY, iZ, &imConstraint, mrcPixelImPart, mrcPixelHowNearest);

		weight = counter / (tmpdata  + counter);
		rethres = (reConstraint * (linfo.incounter - counter) + rePrev * counter) / linfo.incounter;
		imthres = (imConstraint * (linfo.incounter - counter) + imPrev * counter) / linfo.incounter;

		if(0 <= counter && counter < linfo.incounter){
			if(tmpdata > 0){
				dstre = weight * rethres;
				dstim = weight * imthres;
			}else{
				dstre = rethres;
				dstim = imthres;
			}
		}else{
			dstre =  rePrev;
			dstim =  imPrev;
		}
		mrcPixelDataSet(tmpFFTOut, iX, iY, iZ, dstre, mrcPixelRePart);
		mrcPixelDataSet(tmpFFTOut, iX, iY, iZ, dstim, mrcPixelImPart);
	}
	}
	}

	sprintf(s, "/home/people/ayumi/ayumiFS04/SuperResolution/debug/tmpfftout-%03d.fft", i);
	//mrcFileWrite(tmpFFTOut, s, NULL, 0);
	mrcImageFree(&FFTinCount, "in lmrcImageSuperResolutionFourierSpaceCalculatingwithCounter");
	if(tmpdata > 0){
		k++; 
	}	 		
	DEBUGPRINT1("%d\n", k);
	i++;
}

/*hvpmode*/
void
lmrcImageSuperResolutionFourierSpaceCalculatingwithLowpassfilter(mrcImage* tmpConstraint, mrcImage* tmpFFTConstraint, 
mrcImage* tmpFFTOrg, mrcImage* tmpFFTOut, mrcImage* tmpFFTPrev, lmrcImageSuperResolutionInfo linfo)
{

	double lengthx, lengthy, lengthz;
	double mulx, muly, mulz;
	double re, im, dstre, dstim;
	float iX, iY, iZ;
	double r;
	
	lengthx = 1.0 / (tmpConstraint->HeaderN.x * tmpConstraint->HeaderLength.x);
	lengthy = 1.0 / (tmpConstraint->HeaderN.y * tmpConstraint->HeaderLength.y);
	lengthz = 1.0 / (tmpConstraint->HeaderN.z * tmpConstraint->HeaderLength.z);

		for(iZ = -tmpFFTConstraint->HeaderN.z / 2.0; iZ < tmpFFTConstraint->HeaderN.z / 2.0; iZ++){
		for(iY = -tmpFFTConstraint->HeaderN.y / 2.0; iY < tmpFFTConstraint->HeaderN.y / 2.0; iY++){
		for(iX = 0.0; iX < tmpFFTConstraint->HeaderN.x / 2.0; iX++){
			mulx = iX * lengthx;
			muly = iY * lengthy;
			mulz = iZ * lengthz;

			r = sqrt(mulx * mulx + muly * muly + mulz * mulz); 
			
			if(r < linfo.hvp){
				mrcPixelDataGet(tmpFFTPrev, iX, iY, iZ, &re, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(tmpFFTPrev, iX, iY, iZ, &im, mrcPixelImPart, mrcPixelHowNearest);
				dstre = re;
				dstim = im;
				mrcPixelDataSet(tmpFFTOut, iX, iY, iZ, dstre, mrcPixelRePart);
				mrcPixelDataSet(tmpFFTOut, iX, iY, iZ, dstim, mrcPixelImPart);
			}else{
				mrcPixelDataGet(tmpFFTConstraint, iX, iY, iZ, &re, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(tmpFFTConstraint, iX, iY, iZ, &im, mrcPixelImPart, mrcPixelHowNearest);
				dstre = re;
				dstim = im;
				mrcPixelDataSet(tmpFFTOut, iX, iY, iZ, dstre, mrcPixelRePart);
				mrcPixelDataSet(tmpFFTOut, iX, iY, iZ, dstim, mrcPixelImPart);
			}
		}
		}
		}
}

int
lmrcImageSuperResolutionRealSpaceCalculatingformrcImageSubtraction(mrcImage* inPrev, mrcImage* tmpOut, 
lmrcImageSuperResolutionInfo linfo)
{
	
	mrcImageParaTypeReal x, y, z;
	double reinPrev, retmpOut;
	int subcount = 0;
	unsigned long n;

	for(z = 0.0; z < inPrev->HeaderN.z; z++){
	for(y = 0.0; y < inPrev->HeaderN.y; y++){
	for(x = 0.0; x < inPrev->HeaderN.x; x++){
		mrcPixelDataGet(inPrev, x, y, z, &reinPrev, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(tmpOut, x, y, z, &retmpOut, mrcPixelRePart, mrcPixelHowNearest);
		if(fabs(reinPrev - retmpOut) > linfo.sub) {
			subcount++;
		}
	}
	}
	}
	n = inPrev->HeaderN.x * inPrev->HeaderN.y * inPrev->HeaderN.z;
	DEBUGPRINT1("subcount=%d\n", subcount);
	DEBUGPRINT1("n=%d\n", n);
	if(subcount <= n * linfo.ratio){
		return 1;
	}else{
		return 0;
	}
}

void
lmrcImageSuperResolutionRealSpaceCalculatingbySubtraction(mrcImage* tmpSubConstraint, mrcImage *tmpPrevConstraint, 
lmrcImageSuperResolutionInfo linfo, lmrcImageSuperResolutionMode mode, double scale)
{
	mrcImageParaTypeReal x, y, z;
	float* data;
	double tmpdata, dstdata, vol;
	int j;
	unsigned long n, k, level;
	float density;

	DEBUGPRINT("a");
	n = tmpSubConstraint->HeaderN.x * tmpSubConstraint->HeaderN.y * tmpSubConstraint->HeaderN.z; 
	DEBUGPRINT3("Headerx = %d Headery =%d Header=%d\n", tmpSubConstraint->HeaderN.x, tmpSubConstraint->HeaderN.y, 
	tmpSubConstraint->HeaderN.z);
	DEBUGPRINT1("n=%d\n", n);

	data = (float*)memoryAllocate(sizeof(float) * (n + 1), NULL);
	j = 1;
	for(z = 0.0; z < tmpSubConstraint->HeaderN.z; z++){
	for(y = 0.0; y < tmpSubConstraint->HeaderN.y; y++){
	for(x = 0.0; x < tmpSubConstraint->HeaderN.x; x++){
		mrcPixelDataGet(tmpPrevConstraint, x, y, z, &(tmpdata), mrcPixelRePart, mrcPixelHowNearest);
		data[j] = tmpdata;
		j++;
	}
	}
	}
	DEBUGPRINT("b");
	vol = tmpSubConstraint->HeaderLength.x * tmpSubConstraint->HeaderLength.y * tmpSubConstraint->HeaderLength.z;
	level = ((double)linfo.nMolecule) * linfo.MolecularWeight / linfo.Density * 10.0 / 6.02;

	DEBUGPRINT2("vol = %lf level = %d\n", vol, level);
	DEBUGPRINT1("scale = %lf\n", scale);

	if(linfo.Inverse == 0){
		k = (unsigned int)((double)level) * scale / vol;
	}else{
		k = n - (unsigned int)((double)level) * scale / vol;
	}
	density = nrselect(k, n, data);
	DEBUGPRINT2("k = %d n = %d\n", k , n);
	DEBUGPRINT1("density = %lf\n", density);


	for(z = 0.0; z < tmpSubConstraint->HeaderN.z; z++){
	for(y = 0.0; y < tmpSubConstraint->HeaderN.y; y++){
	for(x = 0.0; x < tmpSubConstraint->HeaderN.x; x++){
		mrcPixelDataGet(tmpPrevConstraint, x, y, z, &(tmpdata), mrcPixelRePart, mrcPixelHowNearest);
		if(tmpdata != 0.0 ){
			dstdata = tmpdata - density;	
			mrcPixelDataSet(tmpSubConstraint, x, y, z, dstdata, mrcPixelRePart);
		}
		if(dstdata < 0.0){
			fprintf(stderr, "error\n");
			exit(EXIT_FAILURE);
		}

	}
	}
	}

	free(data);

}
