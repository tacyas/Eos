/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAutoRotationCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAutoRotationCorrelation
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrcImageAutoRotationCorrelation ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageCorrelation.h"
#include "lmrcImageROI2D.h"
#include "Map2D.h"

extern void lmrcImageAutoRotationCorrelationInfoSet2(lmrcImageAutoRotationCorrelationForManyReferencesInfo* info2, mrcImageAutoRotationCorrelationInfo info);
extern void lmrcImageAutoRotationCorrelationInfoSet(lmrcImageAutoRotationCorrelationInfo* linfo, mrcImageAutoRotationCorrelationInfo info, mrcImage in);
extern void lmrcImageAutoRotationCorrelationROIInfoSet(lmrcImageSingleROIInfo* roiInfo, mrcImage ref, int offsetx, int offsety);

int
main(int argc, char* argv[]) 
{
	mrcImageAutoRotationCorrelationInfo info;
	lmrcImageAutoRotationCorrelationForManyReferencesInfo info2;
	lmrcImageAutoRotationCorrelationInfo linfo;
	mrcImage in;
	mrcImage tmp;
	mrcImage ref;
	static mrcImage cor;
	int offsetx, shiftx;
	int offsety, shifty;
	lmrcImageSingleROIInfo roiInfo;
	mrcImageParaTypeReal x, y, z;
	int flagPVM = 0;
#ifdef PVM
	lmrcImageCorrelationPVMInfo linfoPVM;
#endif
	memset(&info,  0, sizeof(info ));
	memset(&info2, 0, sizeof(info2));
	memset(&linfo, 0, sizeof(linfo));

	/* Argument Check */
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

#ifdef PVM
	if(info.flagpvmList) {
		lmrcImageCorrelationServerStart(&linfoPVM, info.fptpvmList, 0); 
		flagPVM = 1;
	} else if(info.flagpvm) {
		lmrcImageCorrelationServerStart(&linfoPVM, NULL, info.pvm); 
		flagPVM = 1;
	} else {
		flagPVM = 0;
	}
	if(flagPVM) {
		LOGPRINT2(info.fptLog, "Start", "Correlation", "PVM: flag %d numTask: %d\n", flagPVM, linfoPVM.numTask);
	}
#endif /* PVM */

	/* Data Read */
	mrcFileRead(&in,  info.In,  "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	lmrcImageAutoRotationCorrelationInfoSet (&linfo, info, in); 
	lmrcImageAutoRotationCorrelationInfoSet2(&info2, info); 

	if(ref.HeaderN.z!=ref.numTailer) { /* RefDataCheck */ 
		fprintf(stderr, "in ref: numTailer %d is different from ref.HeaderN.z %d\n", ref.numTailer, ref.HeaderN.z);
		if(0==ref.numTailer) {
			ref.numTailer = ref.HeaderN.z;
			mrcTailerInit(&ref, 0);
		} else {
			fprintf(stderr, "Something wrong!! Please pay attention to your files.\n");
			fprintf(stderr, "The number of tailer infomation is different from that of prepared projetion maps\n");
			exit(EXIT_FAILURE);
		}
	}

	/* Size different */
	if(!info.Shift) {
		if(in.HeaderN.x!=ref.HeaderN.x
		 ||in.HeaderN.y!=ref.HeaderN.y) {
		 	fprintf(stderr, "The size of in (%d,%d) is different from that of rerom that of ref (%d,%d)\n", 
				in.HeaderN.x, in.HeaderN.y, ref.HeaderN.x, ref.HeaderN.y);	
			exit(EXIT_FAILURE);	
		}
	}

	shiftx = in.HeaderN.x - ref.HeaderN.x;
	shifty = in.HeaderN.y - ref.HeaderN.y;
	DEBUGPRINT2("shift: %d %d\n", shiftx, shifty);

	roiInfo.FileName = info.In;
	roiInfo.Shape    = Rect;

	cor.HeaderN.x = info.nRot1*info.nRot2*info.nRot3;
	cor.HeaderN.y = MAX(1,shifty); 
	cor.HeaderN.z = MAX(1,shiftx); 
	cor.HeaderMode = mrcFloatImage;
	mrcInit(&cor, NULL);

	for(offsetx=0; offsetx<=shiftx; offsetx++) {
	for(offsety=0; offsety<=shifty; offsety++) {
		DEBUGPRINT2("offset: %d %d\n", offsetx, offsety);
		/* */
		lmrcImageAutoRotationCorrelationInfoSet2(&info2, info); 
		lmrcImageAutoRotationCorrelationROIInfoSet(&roiInfo, ref, offsetx, offsety);
		/* */
		lmrcImageSingleROI(&tmp, &in, &roiInfo, mrcPixelHowNearest); 
		lmrcImageAutoRotationCorretionForManyReferences(&tmp, &ref, &info2, &linfo, 0);
		mrcImageFree(&tmp, "in main");
	}
	}

	if(info.flagOut) {
		mrcFileWrite(&(info2.out), info.Out, "in main", 0);
	}

	if(info.flagfitFile) { 
		mrcFileWrite(&(info2.fittedMap), info.fitFile, "in main", 0);	
	}
	if(info.flagcorFile) { 
		mrcFileWrite(&(info2.cor), info.corFile, "in main", 0);	
	}
	if(info.flagfitFile2) { 
		mrcFileWrite(&(info2.fittedMap2), info.fitFile2, "in main", 0);	
	}
	if(info.flagcorFile2) { 
		mrcFileWrite(&(info2.cor2), info.corFile2, "in main", 0);	
	}

#ifdef PVM
	lmrcImageCorrelationServerEnd(linfoPVM);
#endif
	exit(EXIT_SUCCESS);
}


void
additionalUsage()
{
	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "When, -Method 0(Default:Correlation)\n");
	lmrcImageCorrelationModePrint(stderr);
	fprintf(stderr, "      ----- Attention -----\n");
	fprintf(stderr, "      You must not set bit 16: bit 16 is set in this program as default.\n");
	fprintf(stderr, "When, -Method 1 (SSDA:Sequential Similarity Detection Algorithm)\n");
	fprintf(stderr, "When, -Method 2 (Rotational Cross-Correlation Function)\n");
	fprintf(stderr, "-m NotSupported\n");
	fprintf(stderr, "\n");
	fprintf(stderr, ">>>>>>>> Attention 1 -----\n");
	fprintf(stderr, "You should set -n or -range. These parameters are used for reference image rotation\n");
	fprintf(stderr, "\n");
	fprintf(stderr, ">>>>>>>> Attention 2 -----\n");
	fprintf(stderr, "You must set -nRot1/2/3.\n");
	fprintf(stderr, "-nRot[1|2|3]     Number of Reference Images: \n");
	fprintf(stderr, "You should set -dRot1/2/3.\n");
	fprintf(stderr, "-dRot[1|2|3]     Delta Angle [degree] of Reference Images: \n");
	fprintf(stderr, "You should set -startRot1/2/3.\n");
	fprintf(stderr, "-startRot[1|2|3] Start Angle [degree] of Reference Images: \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  e.g.) If mrc3Dto2D -Rot1 89 91 1 -Rot2 0 359 2 -Rot3 3 12 3, \n");
	fprintf(stderr, "           -nRot1 3   -dRot1 1 -startRot1 89 \n");
	fprintf(stderr, "           -nRot2 180 -dRot2 2 -startRot2  0 \n");
	fprintf(stderr, "           -nRot3 4   -dRot1 3 -startRot1  3 \n");
	fprintf(stderr, "\n");
	fprintf(stderr, ">>>>>>>> Attention 3 : the relation between dRot1 and nRotArea ----\n");
	fprintf(stderr, "-nRot[1|2|3]Area Min[degree] Max[degree] Step[degree]\n");
	fprintf(stderr, "If not -dRot[1|2|3], we cannot estimate nStep, which is the number of skip step using referencefiles .\n");
	fprintf(stderr, "\n");
	fprintf(stderr, ">>>>>>>> Attention 4 : Stack order of ref-image -----\n");
	fprintf(stderr, "-StackOrder\n");
	fprintf(stderr, "    %d: for pdb2mrc2d : default\n", lmrcImageAutoRotationCorrelationForManyReferencesStackOrderRot1Rot2Rot3);
	fprintf(stderr, "    %d: for mrc3Dto2D \n", lmrcImageAutoRotationCorrelationForManyReferencesStackOrderRot3Rot2Rot1);
	fprintf(stderr, "If not -dRot[1|2|3], we cannot estimate nStep, which is the number of skip step using referencefiles .\n");
	fprintf(stderr, "\n");
	fprintf(stderr, ">>>>>>>> Attention 5 : Refinement Mode -----\n");
	fprintf(stderr, "-RefineMode \n");
	fprintf(stderr, "    %d: for LinearCorrelation;  default\n", lmrcImageAutoRotationCorrelationForManyReferencesRefinementModeLinear);
	fprintf(stderr, "    %d: for SetModeCorrelation \n", lmrcImageAutoRotationCorrelationForManyReferencesRefinementModeSetMode);
	fprintf(stderr, "\n");
	fprintf(stderr, ">>>>>>>> Attention 6 : Search Area -----\n");
	fprintf(stderr, "-refStep[1|2|3] \n");
	fprintf(stderr, "     Skip image number: Just skip ref-images \n");
	fprintf(stderr, " or \n");
	fprintf(stderr, "-nRot[1|2|3]Area \n");
	fprintf(stderr, "     Set the search area. You finally can refine parameters by each ref-image following -RefineMode. \n");
	fprintf(stderr, "\n");
}


void 
lmrcImageAutoRotationCorrelationROIInfoSet(lmrcImageSingleROIInfo* roiInfo, mrcImage ref, int offsetx, int offsety)
{
	/* offset */
	roiInfo->blx = offsetx;
	roiInfo->bly = offsety;
	roiInfo->brx = offsetx+ref.HeaderN.x-1;
	roiInfo->bry = offsety;
	roiInfo->trx = offsetx+ref.HeaderN.x-1;
	roiInfo->try = offsety+ref.HeaderN.y-1;
	roiInfo->tlx = offsetx;
	roiInfo->tly = offsety+ref.HeaderN.y-1;
	roiInfo->mode = ref.HeaderMode;
	roiInfo->flagWidth  = 0;
	roiInfo->flagHeight = 0;
	roiInfo->flagMagnifiedWidth  = 0;
	roiInfo->flagMagnifiedHeight = 0;
	roiInfo->flagLayerLine       = 0;
}

void 
lmrcImageAutoRotationCorrelationInfoSet(
	lmrcImageAutoRotationCorrelationInfo* linfo, 
	mrcImageAutoRotationCorrelationInfo   info,
	mrcImage in)
{
	/* AutoRotationCorrelation Paramter Set */
	linfo->iter           = info.Iter;
	linfo->nRot           = info.Rot;
	linfo->flagXshiftOnly = info.Xshift;
	linfo->flagNoShift    = info.NoShift;

	linfo->Method         = info.Method;
	if(info.flagminAngle && info.flagmaxAngle) {
		linfo->flagRestrictionArea = 1;	
		linfo->thetaMin = info.minAngle*RADIAN;
		linfo->thetaMax = info.maxAngle*RADIAN;
	} else {
		linfo->flagRestrictionArea = 0;	
		linfo->thetaMin = 0;
		linfo->thetaMax = 2*M_PI;
	}
	if(info.flagsminx) { /* Search Region */
		DEBUGPRINT("Set Search Region\n");
		linfo->flagShiftRange = 1;
		linfo->shiftMinX = info.sminx;
		linfo->shiftMinY = info.sminy;
		linfo->shiftMaxX = info.smaxx;
		linfo->shiftMaxY = info.smaxy;
		linfo->SSDAInfo.smin.x =  info.sminx; 
		linfo->SSDAInfo.smin.y =  info.sminy; 
		linfo->SSDAInfo.smax.x =  info.smaxx; 
		linfo->SSDAInfo.smax.y =  info.smaxy; 
	} else {
		linfo->SSDAInfo.smin.x = 0;
		linfo->SSDAInfo.smin.y = 0;
		linfo->SSDAInfo.smax.x = in.HeaderN.x - 1;
		linfo->SSDAInfo.smax.y = in.HeaderN.y - 1;
	}
	linfo->SSDAInfo.Threshold = 1e30;

	linfo->flagMagnification = info.flagMagRangeMax;
	linfo->MagMax = info.MagRangeMax;
	linfo->MagMin = info.MagRangeMin;
	linfo->MagStep = info.MagRangeStep;
}

void 
lmrcImageAutoRotationCorrelationInfoSet2(
	lmrcImageAutoRotationCorrelationForManyReferencesInfo* info2, 
	mrcImageAutoRotationCorrelationInfo info)
{

	/* Parameters Setting */ 
	info2->StackOrder = info.StackOrder	;

	/* Check Area Rotation */
	if(!info.flagdRot1) {
		info.dRot1	= 360.0/info.nRot1;
	}
	if(!info.flagdRot2) {
		info.dRot2	= 360.0/info.nRot2;
	}
	if(!info.flagdRot3) {
		info.dRot3	= 360.0/info.nRot3;
	}
	info2->nRot1Delta =  info.dRot1*RADIAN;
	info2->nRot2Delta =  info.dRot2*RADIAN;
	info2->nRot3Delta =  info.dRot3*RADIAN;
	info2->nRot1Start =  info.startRot1*RADIAN;
	info2->nRot2Start =  info.startRot2*RADIAN;
	info2->nRot3Start =  info.startRot3*RADIAN;

	info2->nRot1		 = info.nRot1;
	if(info.flagnRot1AreaMin) {
		info2->nRot1AreaMin  = info.nRot1AreaMin*RADIAN;
		info2->nRot1AreaMax  = info.nRot1AreaMax*RADIAN;
		info2->nRot1AreaStep = info.nRot1AreaStep*RADIAN;
		if(info.flagdRot1) {
			info2->nRot1Step     = MAX(1,info.nRot1AreaStep/info.dRot1+0.5);
			fprintf(stderr, "Rot1Step %d = round(%f = %f / %f) \n", info2->nRot1Step, info2->nRot1Step*info.dRot1, info.nRot1AreaStep, info.dRot1); 	
		} else {
			fprintf(stderr, "Ignore nRot1AreaStep %f, and so set 1 to nRot1Step.\n",  info2->nRot1AreaStep); 	
			info2->nRot1Step     = 1;
		}
	} else {
		info2->nRot1AreaMin  = 0;
		info2->nRot1AreaMax  = 2*M_PI;
		info2->nRot1Step     = info.refStep1;
	}

	info2->nRot2		 = info.nRot2;
	if(info.flagnRot2AreaMin) {
		info2->nRot2AreaMin  = info.nRot2AreaMin*RADIAN;
		info2->nRot2AreaMax  = info.nRot2AreaMax*RADIAN;
		info2->nRot2AreaStep = info.nRot2AreaStep*RADIAN;
		if(info.flagdRot2) {
			info2->nRot2Step     = MAX(1,info.nRot2AreaStep/info.dRot2+0.5);
			fprintf(stderr, "Rot2Step %d = round(%f = %f / %f) \n", info2->nRot2Step, info2->nRot2Step*info.dRot2, info.nRot2AreaStep, info.dRot2); 	
		} else {
			fprintf(stderr, "Ignore nRot2AreaStep %f, and so set 1 to nRot2Step.\n",  info2->nRot2AreaStep); 	
			info2->nRot2Step     = 1;
		}
	} else {
		info2->nRot2AreaMin  = 0;
		info2->nRot2AreaMax  = 2*M_PI;
		info2->nRot2Step     = info.refStep1;
	}

	info2->nRot3		 = info.nRot3;
	if(info.flagnRot3AreaMin) {
		info2->nRot3AreaMin  = info.nRot3AreaMin*RADIAN;
		info2->nRot3AreaMax  = info.nRot3AreaMax*RADIAN;
		info2->nRot3AreaStep = info.nRot3AreaStep*RADIAN;
		if(info.flagdRot3) {
			info2->nRot3Step     = MAX(1, info.nRot3AreaStep/info.dRot3+0.5);
			fprintf(stderr, "Rot3Step %d = round(%f = %f / %f) \n", info2->nRot3Step, info2->nRot3Step*info.dRot3, info.nRot3AreaStep, info.dRot3); 	
		} else {
			fprintf(stderr, "Ignore nRot3AreaStep %f, and so set 1 to nRot3Step.\n",  info2->nRot3AreaStep); 	
			info2->nRot3Step     = 1;
		}
	} else {
		info2->nRot3AreaMin  = 0;
		info2->nRot3AreaMax  = 2*M_PI;
		info2->nRot3Step     = info.refStep2;
	}		

	info2->RefinementMode    = info.RefineMode;

	info2->In            = info.In;
	info2->Out           = info.Out;
	info2->corFile       = info.corFile;
	info2->fitFile       = info.fitFile;
	info2->corFile2      = info.corFile2;
	info2->fitFile2      = info.fitFile2;
	info2->fptOutASC     = info.fptOutASC;
	info2->mode          = info.mode;

}

