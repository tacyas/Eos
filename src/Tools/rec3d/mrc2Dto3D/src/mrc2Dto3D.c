/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc2Dto3D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc2Dto3D
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrc2Dto3D ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define GLOBAL_DECLARATION
#undef DEBUG
#include "../inc/config.h"
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"
#include "Matrix3D.h"
#include "eosPThread.h"
#include "lmrcImageRhoFiltering.h"
#include "lmrc2Dto3D.h"

extern void lmrc2Dto2DMulti(mrcImage* out, char** filename, int number, FILE* fptInfo, int mode);
extern void lmrc2Dto2DEach(lmrc2Dto3DInfo* linfo, char** filename, int number, FILE* fptInfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrc2Dto3DInfo info;
	static lmrc2Dto3DInfo linfo;
	static lmrc2Dto3DSIRTInfo llinfo;
	static mrcImage  In;
	static mrcImage Out;

	init0(&info);
	argCheck(&info, argc, argv);
    init1(&info);

	linfo.Rmax = info.Rmax;
	linfo.mode = info.mode;
	linfo.singleTiltMode = info.single;
	linfo.singleFilterMode = info.singleFilter;
	linfo.flagDouble     = info.Double;
	linfo.flagPlusXrot   = info.PlusXrot;
	linfo.InterpolationMode = info.InterpolationMode;
	linfo.rhoInfo.counterThreshold = info.CounterThreshold;
	linfo.rhoInfo.counterThresholdMode = info.CounterThresholdMode;
	linfo.rhoInfo.weightMode     = info.WeightMode;
	linfo.rhoInfo.SubSampling    = info.SubSampling;
	linfo.rhoInfo.flagThicknessWeight = info.thicknessWeight;
	__eosPThread__ = info.flagpthreadMax;
	__eosPThreadNum__ = info.pthreadMax;

	if(info.flagNx) {
		linfo.flagOutputSize = 1;
		linfo.Nx = info.Nx;
		linfo.Ny = info.Ny;
		linfo.Nz = info.Nz;
	}
	if(info.SIRT) {
		llinfo.maxIter = info.maxIter;
		llinfo.rms = info.rms;
		llinfo.lambda = 0.1;
	} else {
	}

	if(info.flagIn) {
		mrcFileRead(&In, info.In, "in main", 0); 
	} else if (info.flagIn2) {
		if(info.each) {
			lmrc2Dto2DEach(&linfo, info.In2, info.flagIn2, info.fptIn2List, 0);
		} else {
			lmrc2Dto2DMulti(&In, info.In2, info.flagIn2, info.fptIn2List, 0);
		}
	} else {
		fprintf(stderr, "-i or -I is required\n");
		exit(EXIT_FAILURE);
	}

	if(info.SIRT) {
		lmrc2Dto3DSIRT(&Out, &In, &linfo, &llinfo, 0);
	} else {
		if(info.each) {
			lmrc2Dto3D(&Out, NULL, &linfo, 0);
		} else {
			lmrc2Dto3D(&Out, &In, &linfo, 0);
		}
	}

	mrcFileWrite(&Out, info.Out, "in main", 0); 
	if(info.flagOut2) {
		mrcFileWrite(&In, info.Out2, "in main", 0);
	}
	if(info.Double && info.flagDoubleCounter) {
		if(NULL!=linfo.CounterForWeight) {
			mrcFileWrite(linfo.CounterForWeight, info.DoubleCounter, "in main", 0);
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m Option\n");
	fprintf(stderr, "    %d:SimpleBackProjection\n", mrc2Dto3DModeSimpleBackProjection);
	fprintf(stderr, "    %d:FilteredBackProjection(Fourier Space)\n", mrc2Dto3DModeFilteredBackProjection);
	fprintf(stderr, "    %d:WeightedBackProjection(Real Space)\n", mrc2Dto3DModeWeightedBackProjection);
	fprintf(stderr, "-single 0|1 \n");
	fprintf(stderr, "    0: tilt axis is parallel to x-axis\n");
	fprintf(stderr, "    1: tilt axis is parallel to y-axis\n");
	fprintf(stderr, "-singleFilter 0|1|2 \n");
	fprintf(stderr, "    0: simple rho filter\n");
	fprintf(stderr, "    1: Ram-Lak Filter\n");
	fprintf(stderr, "    2: Shepp-Logan Filter\n");
	fprintf(stderr, "-Double \n");
	fprintf(stderr, "    Double Tilt \n");
	fprintf(stderr, "-WeightMode \n");
	fprintf(stderr, "    1 : RealSpace: Circle(same density)\n");
	fprintf(stderr, "    2 : RealSpace: Circle(weighted density)\n");
	fprintf(stderr, "    3 : RealSpace: Square(weighted density) \n");
	fprintf(stderr, "    4 : Fourier Space : Plane(same density) -CounterThreshold 0.5\n");
	fprintf(stderr, "    5 : Fourier Space : Plane(Linear Gradient)-CounterThreshold 0.5\n");
	fprintf(stderr, "    6 : Fourier Space : Plane(Cosine Gradient) Current Recommende using -CounterThreshold 0.5\n");
	fprintf(stderr, "-------------------------------\n");
	fprintf(stderr, "-I Option file format\n");
	fprintf(stderr, "filename0 RotationOrder0 rot1 rot2 rot3\n");
	fprintf(stderr, "filename1 RotationOrder1 rot1 rot2 rot3\n");
	fprintf(stderr, ".......................................\n");
	fprintf(stderr, ">>> RotationOrder : Eular Angle Expression <<< \n");
	fprintf(stderr, "Example: YOYS : RotY(rot3)RotX(rot2)RotY(rot1)*v\n");
	fprintf(stderr, "First Rotation  : y-axis : Y: Y     : [X|Y|Z] Axis used initially\n");
	fprintf(stderr, "Second Rotation : x-axis : O: Odd   : [O|E]   Parity of axis permutation\n");
	fprintf(stderr, "Last Rotation   : z-axis : Y: Yes   : [Y|N]   Repetition of initial axis as last\n");
	fprintf(stderr, "v1 = A v0                : S: Staic : [S|R]   Frame from which axes are taken\n");

}

void
lmrc2Dto2DMulti(mrcImage* out, char** filename, int number, FILE* fptInfo, int mode)
{
	long i;
	mrcImage* in; 
	mrcImageParaTypeInteger Nx, Ny;
	mrcImageParaTypeReal    Length;
	mrcImageParaTypeReal    srcx, srcy, srcz;
	mrcImageParaTypeReal    dstx, dsty, dstz;
	char s[1024];
	double data;

	in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*number, "in lmrc2Dto2DMulti");
	Nx = 0;
	Ny = 0;
	Length = 1e6;
	for(i=0; i<number; i++) {
		DEBUGPRINT1("Opening:%s\n", filename[i]);
		mrcFileRead(&(in[i]), filename[i], "in lmrc2Dto2DMulti", 0);
		if(Nx < in[i].HeaderN.x) {
			Nx = in[i].HeaderN.x;
		}
		if(Ny < in[i].HeaderN.y) {
			Ny = in[i].HeaderN.y;
		}
		if(in[i].HeaderLength.x < Length) {
			Length = in[i].HeaderLength.x;
		}
		if(in[i].HeaderLength.y < Length) {
			Length = in[i].HeaderLength.y;
		}
	}	
	out->HeaderN.x = Nx;
	out->HeaderN.y = Ny;
	out->HeaderN.z = number;
	out->HeaderMode = mrcFloatImage;
	out->HeaderLength.x = Length;
	out->HeaderLength.y = Length;
	out->HeaderLength.z = Length;
	mrcInit(out, NULL);
	srcz = 0;
	for(dstz=0; dstz<number; dstz++) {
		for(dstx=0; dstx<in->HeaderN.x; dstx++) {
			for(dsty=0; dsty<in->HeaderN.y; dsty++) {
				srcx = dstx - (out->HeaderN.x - in->HeaderN.x)/2.0;
				srcy = dsty - (out->HeaderN.y - in->HeaderN.y)/2.0;
				mrcPixelDataGet(&(in[(int)dstz]), srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowLinear);
				mrcPixelDataSet(out,              dstx, dsty, dstz,  data, mrcPixelRePart);
			}
		}
	}
	out->numTailer = number;
	out->Tailer = (mrcImageTailer*)memoryAllocate(sizeof(mrcImageTailer)*number, "in lmrc2Dto2DMulti");
	fseek(fptInfo, 0L, SEEK_SET);
	for(i=0; i<number; i++) {
		stringGetFromFile(s, "", fptInfo, stdout, 3);
		out->Tailer[i].Cont.Mode = mrcImageTailerMode2DProjection;
		stringCopy(out->Tailer[i].Cont.EulerAngleMode, stringGetNthWord(s, 2, " \t,"), 4);
		out->Tailer[i].Cont.Rot1 = stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		out->Tailer[i].Cont.Rot2 = stringGetNthRealData(s, 4, " ,\t")*RADIAN;
		out->Tailer[i].Cont.Rot3 = stringGetNthRealData(s, 5, " ,\t")*RADIAN;
	}
	for(i=0; i<number; i++) {
		mrcImageFree(&(in[i]), "in lmrc2Dto2DMulti");
	}
	free(in);
}

void
lmrc2Dto2DEach(lmrc2Dto3DInfo* linfo, char** filename, int number, FILE* fptInfo, int mode)
{
	char s[1024];
	long i;

	linfo->inFileNum = number; 
	linfo->inFileList= filename; 
	linfo->Tailer = (mrcImageTailer*)memoryAllocate(sizeof(mrcImageTailer)*number, "in lmrc2Dto2DEach");
	fseek(fptInfo, 0L, SEEK_SET);
	for(i=0; i<number; i++) {
		stringGetFromFile(s, "", fptInfo, stdout, 3);
		linfo->Tailer[i].Cont.Mode = mrcImageTailerMode2DProjection;
		stringCopy(linfo->Tailer[i].Cont.EulerAngleMode, stringGetNthWord(s, 2, " \t,"), 4);
		linfo->Tailer[i].Cont.Rot1 = stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		linfo->Tailer[i].Cont.Rot2 = stringGetNthRealData(s, 4, " ,\t")*RADIAN;
		linfo->Tailer[i].Cont.Rot3 = stringGetNthRealData(s, 5, " ,\t")*RADIAN;
	}
}

