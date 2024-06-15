/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAutoRotationCorrelationResultPrint ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAutoRotationCorrelationResultPrint
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
#define DEBUG
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
	cor.HeaderN.y = shifty; 
	cor.HeaderN.z = shiftx; 
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
	}
	if(info.flagsminx) { /* Search Region */
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
}

void 
lmrcImageAutoRotationCorrelationInfoSet2(
	lmrcImageAutoRotationCorrelationForManyReferencesInfo* info2, 
	mrcImageAutoRotationCorrelationInfo info)
{

	/* Parameters Setting */ 
	/* Check Area Rotation */
	info2->nRot1		 = info.nRot1;
	info2->nRot1Step     = info.refStep1;
	info2->nRot1AreaMin  = info.nRot1AreaMin*RADIAN;
	info2->nRot1AreaMax  = info.nRot1AreaMax*RADIAN;
	info2->nRot1AreaStep = info.nRot1AreaStep*RADIAN;

	info2->nRot2		 = info.nRot2;
	info2->nRot2Step     = info.refStep2;
	info2->nRot2AreaMin  = info.nRot1AreaMin*RADIAN;
	info2->nRot2AreaMax  = info.nRot1AreaMax*RADIAN;
	info2->nRot2AreaStep = info.nRot1AreaStep*RADIAN;

	info2->nRot3		 = info.nRot3;
	info2->nRot3Step     = info.refStep3;
	info2->nRot3AreaMin  = info.nRot1AreaMin*RADIAN;
	info2->nRot3AreaMax  = info.nRot1AreaMax*RADIAN;
	info2->nRot3AreaStep = info.nRot1AreaStep*RADIAN;

	info2->In            = info.In;
	info2->Out           = info.Out;
	info2->corFile       = info.corFile;
	info2->fitFile       = info.fitFile;
	info2->fptOutASC     = info.fptOutASC;
	info2->mode          = info.mode;
}

#define NUM_PARAMETER (7)

void 
lmrcImageAutoRotationCorretionForManyReferences(mrcImage* in, mrcImage* ref, 
	lmrcImageAutoRotationCorrelationForManyReferencesInfo* info,
	lmrcImageAutoRotationCorrelationInfo* linfo,
	int mode)
{
	mrcImage proj;
	mrcImage out;
	long i;
	long i1, i2, i3;
	mrcImageParaTypeReal x, y;
	char s[5];
	double correlationMax=-1e30;
	double correlationMaxRot1=0;
	double correlationMaxRot2=0;
	double correlationMaxRot3=0;
	double correlation;

	/* Parameter Output file */
	out.HeaderN.x = NUM_PARAMETER;
	out.HeaderN.y = 1;
	out.HeaderN.z = ref->HeaderN.z;
	out.HeaderLength.x = 1;
	out.HeaderLength.y = 1;
	out.HeaderLength.z = 1;
	out.HeaderMode = mrcFloatImage;
	mrcInit(&out, NULL);
	out.numTailer = ref->HeaderN.z;
	mrcTailerInit(&out, 0);

	DEBUGPRINT3("nRot1Area:  %f %f %f\n", info->nRot1AreaMin*DEGREE, info->nRot1AreaMax*DEGREE, info->nRot1AreaStep*DEGREE);
	DEBUGPRINT3("nRot2Area:  %f %f %f\n", info->nRot2AreaMin*DEGREE, info->nRot2AreaMax*DEGREE, info->nRot2AreaStep*DEGREE);
	DEBUGPRINT3("nRot3Area:  %f %f %f\n", info->nRot3AreaMin*DEGREE, info->nRot3AreaMax*DEGREE, info->nRot3AreaStep*DEGREE);
	s[4] = '\0';
	i = 0;
	while(1) {
		for(i1=0; i1<info->nRot1; i1+=info->nRot1Step) {
		for(i2=0; i2<info->nRot2; i2+=info->nRot2Step) {
		for(i3=0; i3<info->nRot3; i3+=info->nRot3Step) {
			i = i1 + i2*info->nRot1 + i3*info->nRot1*info->nRot2;

			if(!(info->nRot1AreaMin<=ref->Tailer[i].Cont.Rot1 && ref->Tailer[i].Cont.Rot1<=info->nRot1AreaMax
			   &&info->nRot2AreaMin<=ref->Tailer[i].Cont.Rot2 && ref->Tailer[i].Cont.Rot2<=info->nRot2AreaMax
			   &&info->nRot3AreaMin<=ref->Tailer[i].Cont.Rot3 && ref->Tailer[i].Cont.Rot3<=info->nRot3AreaMax)) {
			  	DEBUGPRINT3("Exclusion Area: Rot %g %g %g \n",  ref->Tailer[i].Cont.Rot1, 
																ref->Tailer[i].Cont.Rot2, 
																ref->Tailer[i].Cont.Rot3);
			} else {
				map2DCoordGet(&x, &y, 
					ref->Tailer[i].Cont.Rot1, 
					ref->Tailer[i].Cont.Rot2,
					1, 1, 1);
			/* 
				!!!! Attention !!!!! This is true !!!!!
					map2DCoordGet(&x, &y, -ref->Tailer[i].Cont.Rot1, 
										   ref->Tailer[i].Cont.Rot2, 
								 out.HeaderN.x, out.HeaderN.y, 1);
			*/
				mrcImageSectionGet(&proj, ref, i, 0);

				/* Correlation */
				lmrcImageAutoRotationCorrelation(&(info->fittedMap), &(info->cor), in, &proj, linfo, info->mode);

				correlation = linfo->LinearCorrelation;
				mrcPixelDataSet(&out, 0, 0, i, linfo->max,      mrcPixelRePart);
				mrcPixelDataSet(&out, 1, 0, i, linfo->maxTheta, mrcPixelRePart);
				mrcPixelDataSet(&out, 2, 0, i, linfo->maxP.x,   mrcPixelRePart);
				mrcPixelDataSet(&out, 3, 0, i, linfo->maxP.x,   mrcPixelRePart);
				mrcPixelDataSet(&out, 4, 0, i, x, mrcPixelRePart); 
				mrcPixelDataSet(&out, 5, 0, i, y, mrcPixelRePart); 
				mrcPixelDataSet(&out, 6, 0, i, correlation, mrcPixelRePart); 

				fprintf(info->fptOutASC, "%ld: ", i);
				strncpy(s, ref->Tailer[i].Cont.EulerAngleMode, 4);	
				LOGPRINT12(info->fptOutASC, "", "", \
					"%4s %15.6f %15.6f %15.6f : %15.6f theta %15.6f at %15.6f %15.6f onMap %15.6f %15.6f %s Cor %15.6f\n", 
												s,
												ref->Tailer[i].Cont.Rot1*DEGREE,
												ref->Tailer[i].Cont.Rot2*DEGREE,
												ref->Tailer[i].Cont.Rot3*DEGREE,
												linfo->max, linfo->maxTheta*DEGREE,
												linfo->maxP.x, linfo->maxP.y,
												x, y,
												info->In,
												correlation);
				if(correlationMax<correlation) {
					correlationMax     = correlation;
					correlationMaxRot1 = ref->Tailer[i].Cont.Rot1; 
					correlationMaxRot2 = ref->Tailer[i].Cont.Rot2; 
					correlationMaxRot3 = ref->Tailer[i].Cont.Rot3; 
				}
			}
		}
		}
		}
		if(1<info->nRot1Step
		 ||1<info->nRot2Step
		 ||1<info->nRot3Step) {
			DEBUGPRINT3("MAX Point: Rot %f %f %f\n", correlationMaxRot1*DEGREE, correlationMaxRot2*DEGREE, correlationMaxRot3*DEGREE);
			info->nRot1AreaStep /= 5;
			info->nRot2AreaStep /= 5;
			info->nRot3AreaStep /= 5;
			info->nRot1AreaMin = correlationMaxRot1-info->nRot1AreaStep;
			info->nRot1AreaMax = correlationMaxRot1+info->nRot1AreaStep;
			info->nRot2AreaMin = correlationMaxRot2-info->nRot2AreaStep;
			info->nRot2AreaMax = correlationMaxRot2+info->nRot2AreaStep;
			info->nRot3AreaMin = correlationMaxRot3-info->nRot3AreaStep;
			info->nRot3AreaMax = correlationMaxRot3+info->nRot3AreaStep;
			DEBUGPRINT3("nRot1Area:  %f %f %f\n", info->nRot1AreaMin*DEGREE, info->nRot1AreaMax*DEGREE, info->nRot1AreaStep*DEGREE);
			DEBUGPRINT3("nRot2Area:  %f %f %f\n", info->nRot2AreaMin*DEGREE, info->nRot2AreaMax*DEGREE, info->nRot2AreaStep*DEGREE);
			DEBUGPRINT3("nRot3Area:  %f %f %f\n", info->nRot3AreaMin*DEGREE, info->nRot3AreaMax*DEGREE, info->nRot3AreaStep*DEGREE);
			info->nRot1Step = MAX(1,info->nRot1Step/5);
			info->nRot2Step = MAX(1,info->nRot2Step/5);
			info->nRot3Step = MAX(1,info->nRot3Step/5);
		} else {
			break;
		}
	}
	info->out = out;
}

