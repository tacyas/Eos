/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDensityInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDensityInfo
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageDensityInfo ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageModeChange.h"
#include "Vector.h"
#include "lmrcImageDensity.h"

void
lmrcImageDensityInfoModePrint(FILE* fpt) 
{
	fprintf(fpt, "----- Attention !!!-----\n");
	fprintf(fpt, "In Eos system, positive values are regarded as density.\n");
	fprintf(fpt, "If a pixel has a negative value, the value of the pixel is regarded as zero.");
	fprintf(fpt, "lmrcImageDensityInfo Mode: \n");
	fprintf(fpt, "%d: PercentageVolume\n", mrcImageDensityInfoPercentageVolume);
	fprintf(fpt, "%d: CentreOfGravity \n", mrcImageDensityInfoCentreOfGravity);
	fprintf(fpt, "%d: Max             \n", mrcImageDensityInfoMax);
	fprintf(fpt, "%d: SD around CentreOfGravity \n", mrcImageDensityInfoCentreOfGravitySD);
	fprintf(fpt, "%d: SD around Max             \n", mrcImageDensityInfoMaxSD);
}

void
lmrcImageDensityInfo(lmrcImageDensityInfoInfo* linfo, mrcImage* in, long mode)
{
	if(mode&mrcImageDensityInfoPercentageVolume) {
		linfo->percentageVolume = lmrcImageDensityInfoPercentageVolume(in, linfo->deltaVolume, mode);
	}
	if(mode&mrcImageDensityInfoCentreOfGravity) {
		DEBUGPRINT("CENTER OF GRAVITY");
		linfo->centreOfGravity = lmrcImageDensityInfoCentreOfGravity(in, mode);
		DEBUGPRINT3("%f %f %f\n", linfo->centreOfGravity.x, linfo->centreOfGravity.y, linfo->centreOfGravity.z);
	}
	if(mode&mrcImageDensityInfoCentreOfGravitySD) {
		if(!(mode&mrcImageDensityInfoCentreOfGravity)) {
			linfo->centreOfGravity = lmrcImageDensityInfoCentreOfGravity(in, mode);
		}
		linfo->centreOfGravitySD = lmrcImageDensityInfoSD(in, linfo->centreOfGravity, mode);
	}
	if(mode&mrcImageDensityInfoMax) {
		linfo->max = lmrcImageDensityInfoMax(in, mode);
	}
	if(mode&mrcImageDensityInfoMaxSD) {
		if(!(mode&mrcImageDensityInfoMax)) {
			linfo->max = lmrcImageDensityInfoMax(in, mode);
		}
		linfo->maxSD = lmrcImageDensityInfoSD(in, linfo->max, mode);
	}
}

void
lmrcImageDensityInfoWrite(FILE* fpt, lmrcImageDensityInfoInfo* linfo, long mode)
{
	int i;
	if(mode&mrcImageDensityInfoPercentageVolume) {
		for(i=0; i<linfo->percentageVolume.size; i++) {
			fprintf(fpt, "%10.2f : %15.6g\n", (float)i*linfo->deltaVolume, linfo->percentageVolume.data[i]);	
		}
	}
	if(mode&mrcImageDensityInfoCentreOfGravity) {
		fprintf(fpt, "GC(NoStart):     %10.4f %10.4f %10.4f\n", linfo->centreOfGravity.x, linfo->centreOfGravity.y, linfo->centreOfGravity.z);	
		fprintf(fpt, "GC(Start):       %10.4f %10.4f %10.4f\n", linfo->centreOfGravity.x+linfo->in.HeaderStartN.x, 
												linfo->centreOfGravity.y+linfo->in.HeaderStartN.y,
												linfo->centreOfGravity.z+linfo->in.HeaderStartN.z);	
		fprintf(fpt, "GC(NoStart[A]):  %10.4f %10.4f %10.4f\n", 
												linfo->centreOfGravity.x*linfo->in.HeaderLength.x, 
												linfo->centreOfGravity.y*linfo->in.HeaderLength.y, 
												linfo->centreOfGravity.z*linfo->in.HeaderLength.z);	
		fprintf(fpt, "GC(Start[A]):    %10.4f %10.4f %10.4f\n", 
												(linfo->centreOfGravity.x+linfo->in.HeaderStartN.x)*linfo->in.HeaderLength.x, 
												(linfo->centreOfGravity.y+linfo->in.HeaderStartN.y)*linfo->in.HeaderLength.y,
												(linfo->centreOfGravity.z+linfo->in.HeaderStartN.z)*linfo->in.HeaderLength.z);	
	}
	if(mode&mrcImageDensityInfoCentreOfGravitySD) {
		fprintf(fpt, "GCSD([pixel]):   %10.4f %10.4f %10.4f\n", linfo->centreOfGravitySD.x, linfo->centreOfGravitySD.y, linfo->centreOfGravitySD.z);	
		fprintf(fpt, "GCSD([A]):       %10.4f %10.4f %10.4f\n", 
												linfo->centreOfGravitySD.x*linfo->in.HeaderLength.x, 
												linfo->centreOfGravitySD.y*linfo->in.HeaderLength.y, 
												linfo->centreOfGravitySD.z*linfo->in.HeaderLength.z);	
	}

	if(mode&mrcImageDensityInfoMax) {
		fprintf(fpt, "Max(NoStart):    %10.4f %10.4f %10.4f\n", linfo->max.x, linfo->max.y, linfo->max.z);	
		fprintf(fpt, "Max(Start):      %10.4f %10.4f %10.4f\n", linfo->max.x+linfo->in.HeaderStartN.x, 
												linfo->max.y+linfo->in.HeaderStartN.y,
												linfo->max.z+linfo->in.HeaderStartN.z);	
		fprintf(fpt, "Max(NoStart[A]): %10.4f %10.4f %10.4f\n", 
												linfo->max.x*linfo->in.HeaderLength.x, 
												linfo->max.y*linfo->in.HeaderLength.y, 
												linfo->max.z*linfo->in.HeaderLength.z);	
		fprintf(fpt, "Max(Start[A]):   %10.4f %10.4f %10.4f\n", 
												(linfo->max.x+linfo->in.HeaderStartN.x)*linfo->in.HeaderLength.x, 
												(linfo->max.y+linfo->in.HeaderStartN.y)*linfo->in.HeaderLength.y,
												(linfo->max.z+linfo->in.HeaderStartN.z)*linfo->in.HeaderLength.z);	
	}
	if(mode&mrcImageDensityInfoMaxSD) {
		fprintf(fpt, "MaxSD([pixel]):  %10.4f %10.4f %10.4f\n", linfo->maxSD.x, linfo->maxSD.y, linfo->maxSD.z);	
		fprintf(fpt, "MaxSD([A]):      %10.4f %10.4f %10.4f\n", 
												linfo->maxSD.x*linfo->in.HeaderLength.x, 
												linfo->maxSD.y*linfo->in.HeaderLength.y, 
												linfo->maxSD.z*linfo->in.HeaderLength.z);	
	}
}

floatVector
lmrcImageDensityInfoPercentageVolume(mrcImage* in, double delta, long mode)
{
	mrcImage dst;
	long npixel;
	long nlevel; 
	long index, i, j, jstart;
	floatVector v;
	float*      fdata;
	double sum, now, flevel;
	extern int __lmrcImageDensityInfoPercentageVolumeCompareFloat(const void*, const void*);

	npixel = in->HeaderN.x*in->HeaderN.y*in->HeaderN.z;
	nlevel = (int)(100.0/delta+0.5);

	floatVectorInit(&v, nlevel);

	switch(in->HeaderMode) {
		case mrcFloatImage: {
			dst = *in;
			break;
		}
		default: {
			lmrcImageModeChange(&dst, in, mrcFloatImage);
			break;
		}
	}
	switch(dst.HeaderMode) {
		case mrcFloatImage: {
			fdata = (float*)memoryAllocate(sizeof(float)*npixel, "in lmrcImageDensityInfoPercentageVolume");
			memcpy(fdata, dst.ImageFloatImage, npixel*sizeof(float));
			qsort(fdata, npixel, sizeof(float), __lmrcImageDensityInfoPercentageVolumeCompareFloat); 
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageDensityInfoPercentageVolume \n");
			exit(EXIT_FAILURE);
			break;
		}
	}

	sum = 0.0;
	for(i=0; i<npixel; i++) {
		if(fdata[i]<0) {
			fdata[i] = 0;
		}
		sum += fdata[i];	
	}

	now = 0;
	jstart = 0;
	for(i=0; i<v.size; i++) {
		flevel = sum/nlevel*i;
		for(j=jstart; j<npixel; j++) {
			now += fdata[j]; 
			if(flevel <= now) {
				v.data[i] = fdata[j];
				jstart = j+1;
				break;
			}
		}
	}
	return v;
}

mrcImageParaTypeRealCoord
lmrcImageDensityInfoCentreOfGravity(mrcImage* in, long mode)
{
	mrcImageParaTypeRealCoord c;
	float x, y, z;
	double data;
	double cx, cy, cz;
	double sum;

	DEBUGPRINT("lmrcImageDensityInfoCentreOfGravity\n");
	cx = cy = cz = 0;
	sum = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
		if(0<data) {
			cx  += x*data;
			cy  += y*data;
			cz  += z*data;
			sum += data;
		}
	}
	}
	}
	c.x = cx/sum;
	c.y = cy/sum;
	c.z = cz/sum;
	DEBUGPRINT3("%f %f %f\n", c.x, c.y, c.z);
	return c;
}

mrcImageParaTypeRealCoord
lmrcImageDensityInfoMax(mrcImage* in, long mode)
{
	mrcImageParaTypeRealCoord p;
	float x, y, z;
	double data;
	double max;

	p.x = p.y = p.z = 0;
	max = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
		if(max<data) {
			p.x = x;	
			p.y = y;	
			p.z = z;	
			max = data;
		}
	}
	}
	}

	return p;
}

mrcImageParaTypeRealCoord
lmrcImageDensityInfoSD(mrcImage* in, mrcImageParaTypeRealCoord p0, long mode)
{
	mrcImageParaTypeRealCoord p;
	float x, y, z;
	double weight;
	double sumWeight;

	p.x = p.y = p.z = 0;
	sumWeight = weight = 0.0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in, x, y, z, &weight, mrcPixelRePart, mrcPixelHowNearest);	
		p.x += (SQR(x-p0.x)*weight);	
		p.y += (SQR(y-p0.y)*weight);	
		p.z += (SQR(z-p0.z)*weight);	
		sumWeight += weight;
	}
	}
	}
	p.x = sqrt(p.x/sumWeight);
	p.y = sqrt(p.y/sumWeight);
	p.z = sqrt(p.z/sumWeight);
	return p;
}

int 
__lmrcImageDensityInfoPercentageVolumeCompareFloat(const void* a, const void* b)
{
	if(*(float*)a<*(float*)b) {
		return 1;
	} else if(*(float*)a==*(float*)b) {
		return  0;
	} else {
		return -1;
	}
}


/*
	Estimation of the change of density distribution
*/
void 
lmrcImageDensityChangeEstimationModePrint(FILE* fpt)
{
	fprintf(fpt, "----- Attention !!!-----\n");
	fprintf(fpt, "In Eos system, positive values are regarded as density.\n");
	fprintf(fpt, "If a pixel has a negative value, the value of the pixel is regarded as zero.");
	fprintf(fpt, "lmrcImageDensityChangeEstimation Mode: \n");
	fprintf(fpt, "%d: CentreOfGravity \n", mrcImageDensityChangeEstimationCentreOfGravity);
	fprintf(fpt, "%d: Max             \n", mrcImageDensityChangeEstimationMax);
	fprintf(fpt, "%d: SD around CentreOfGravity \n", mrcImageDensityChangeEstimationCentreOfGravitySD);
	fprintf(fpt, "%d: SD around Max             \n", mrcImageDensityChangeEstimationMaxSD);
}

void 
lmrcImageDensityChangeEstimation(lmrcImageDensityChangeEstimationInfo* linfo, mrcImage* in1, mrcImage* in2, long mode)
{
	linfo->in1 = *in1;
	linfo->in2 = *in2;
	if(mode&mrcImageDensityChangeEstimationCentreOfGravity) {
		lmrcImageDensityChangeEstimationCentreOfGravity(&(linfo->CG), in1, in2, mode);
	}
	if(mode&mrcImageDensityChangeEstimationCentreOfGravitySD) {
		if(!(mode&mrcImageDensityChangeEstimationCentreOfGravity)) {
			lmrcImageDensityChangeEstimationCentreOfGravity(&(linfo->CG), in1, in2, mode);
		}
		lmrcImageDensityChangeEstimationSD(&(linfo->CG), in1, in2, mode);
	}
	if(mode&mrcImageDensityChangeEstimationMax) {
		lmrcImageDensityChangeEstimationMax(&(linfo->Max), in1, in2, mode);
	}
	if(mode&mrcImageDensityChangeEstimationMaxSD) {
		if(!(mode&mrcImageDensityChangeEstimationMax)) {
			lmrcImageDensityChangeEstimationMax(&(linfo->Max), in1, in2, mode);
		}
		lmrcImageDensityChangeEstimationSD(&(linfo->Max), in1, in2, mode);
	}
}

void 
lmrcImageDensityChangeEstimationWrite(FILE* fpt, lmrcImageDensityChangeEstimationInfo* linfo, long mode)
{

	int i;
	if(mode&mrcImageDensityInfoCentreOfGravity) {
		fprintf(fpt, "GC[pixel]:      %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->CG.change.x, 
												linfo->CG.change.y, 
												linfo->CG.change.z,
												linfo->CG.delta,
												linfo->CG.deltaXY);
		fprintf(fpt, "GC[A]:          %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->CG.change.x*linfo->in1.HeaderLength.x, 
												linfo->CG.change.y*linfo->in1.HeaderLength.y,
												linfo->CG.change.z*linfo->in1.HeaderLength.z,
												linfo->CG.delta*linfo->in1.HeaderLength.x,
												linfo->CG.deltaXY*linfo->in1.HeaderLength.x);
	}
	if(mode&mrcImageDensityInfoCentreOfGravitySD) {
		fprintf(fpt, "GCSD[pixel]:    %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->CG.changeSD.x, 
												linfo->CG.changeSD.y, 
												linfo->CG.changeSD.z,
												linfo->CG.deltaSD,
												linfo->CG.deltaXYSD);
		fprintf(fpt, "GCSD[A]:        %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->CG.changeSD.x*linfo->in1.HeaderLength.x, 
												linfo->CG.changeSD.y*linfo->in1.HeaderLength.y, 
												linfo->CG.changeSD.z*linfo->in1.HeaderLength.z,
												linfo->CG.deltaSD*linfo->in1.HeaderLength.x,
												linfo->CG.deltaXYSD*linfo->in1.HeaderLength.x);
	}

	if(mode&mrcImageDensityInfoMax) {
		fprintf(fpt, "Max[pixel]:     %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->Max.change.x, 
												linfo->Max.change.y, 
												linfo->Max.change.z,
												linfo->Max.delta,
												linfo->Max.deltaXY);
		fprintf(fpt, "Max[A]:         %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->Max.change.x*linfo->in1.HeaderLength.x, 
												linfo->Max.change.y*linfo->in1.HeaderLength.y, 
												linfo->Max.change.z*linfo->in1.HeaderLength.z,
												linfo->Max.delta*linfo->in1.HeaderLength.x,
												linfo->Max.deltaXY*linfo->in1.HeaderLength.x);
	}
	if(mode&mrcImageDensityInfoMaxSD) {
		fprintf(fpt, "MaxSD([pixel]): %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->Max.changeSD.x, 
												linfo->Max.changeSD.y, 
												linfo->Max.changeSD.z,
												linfo->Max.deltaSD,
												linfo->Max.deltaXYSD);
		fprintf(fpt, "MaxSD([A]):     %10.4f %10.4f %10.4f %10.4f %10.4f\n", 
												linfo->Max.changeSD.x*linfo->in1.HeaderLength.x, 
												linfo->Max.changeSD.y*linfo->in1.HeaderLength.y, 
												linfo->Max.changeSD.z*linfo->in1.HeaderLength.z,
												linfo->Max.deltaSD*linfo->in1.HeaderLength.x,
												linfo->Max.deltaXYSD*linfo->in1.HeaderLength.x);
	}
}

void
lmrcImageDensityChangeEstimationCentreOfGravity(lmrcImageDensityChangeEstimationInfo0* CG, mrcImage* in1, mrcImage* in2, long mode)
{
	mrcImageParaTypeReal x1, y1, z1;
	mrcImageParaTypeReal x2, y2, z2;
	double sumWeight;
	double weight1;
	double weight2;
	mrcImageParaTypeRealCoord p; 
	double length;
	double lengthXY;
	double sumLength;
	double sumLengthXY;
	double weight;

	sumWeight = sumLength = sumLengthXY = 0.0;
	length = p.x = p.y = p.z = 0;
	for(x1=0; x1<in1->HeaderN.x; x1++) {
		DEBUGPRINT1("lmrcImageDensityChangeEstimationCentreOfGravity: %10.4f\n", x1);
	for(y1=0; y1<in1->HeaderN.y; y1++) {
	for(z1=0; z1<in1->HeaderN.z; z1++) {
		mrcPixelDataGet(in1, x1, y1, z1, &weight1, mrcPixelRePart, mrcPixelHowNearest);	
		if(0<weight1) {
			for(x2=0; x2<in2->HeaderN.x; x2++) {
			for(y2=0; y2<in2->HeaderN.y; y2++) {
			for(z2=0; z2<in2->HeaderN.z; z2++) {
				mrcPixelDataGet(in2, x2, y2, z2, &weight2, mrcPixelRePart, mrcPixelHowNearest);	
				if(0<weight2) {
					weight = weight1*weight2;
					length     = sqrt(SQR(x1-x2)+SQR(y1-y2)+SQR(z1-z2)); 
					lengthXY   = sqrt(SQR(x1-x2)+SQR(y1-y2)); 
					sumLength   += length  *weight; 	
					sumLengthXY += lengthXY*weight; 	
					p.x += fabs(x1-x2)*weight;
					p.y += fabs(y1-y2)*weight;
					p.z += fabs(z1-z2)*weight;
					sumWeight += weight; 
					DEBUGPRINT6("%10.4g %10.4f %10.4f %10.4f %10.4f %10.4f\n", weight, length, lengthXY, fabs(x1-x2), fabs(y1-y2), fabs(z1-z2));
					DEBUGPRINT2("%10.4g %10.4f\n", weight1, weight2);
				}
			}
			}
			}
		}

	}
	}
	}
	CG->change.x = p.x/sumWeight; 
	CG->change.y = p.y/sumWeight; 
	CG->change.z = p.z/sumWeight; 
	CG->delta   = sumLength/sumWeight;
	CG->deltaXY = sumLengthXY/sumWeight;
}

void
lmrcImageDensityChangeEstimationMax(lmrcImageDensityChangeEstimationInfo0* max, mrcImage* in1, mrcImage* in2, long mode)
{
	mrcImageParaTypeRealCoord max1;
	mrcImageParaTypeRealCoord max2;

	max1 = lmrcImageDensityInfoMax(in1, mode);
	max2 = lmrcImageDensityInfoMax(in2, mode);

	max->change.x = fabs(max1.x - max2.x); 
	max->change.y = fabs(max1.y - max2.y); 
	max->change.z = fabs(max1.z - max2.z); 
	max->delta    = sqrt(SQR(max->change.x)+SQR(max->change.y)+SQR(max->change.z));
	max->deltaXY  = sqrt(SQR(max->change.x)+SQR(max->change.y));
}

void
lmrcImageDensityChangeEstimationSD(lmrcImageDensityChangeEstimationInfo0* linfo,
								mrcImage* in1, mrcImage* in2,
								long mode) 
{
	mrcImageParaTypeReal x1, y1, z1;
	mrcImageParaTypeReal x2, y2, z2;
	double sumWeight;
	double weight1;
	double weight2;
	mrcImageParaTypeRealCoord p; 
	double length;
	double lengthXY;
	double sumLength;
	double sumLengthXY;

	sumWeight = sumLength = sumLengthXY = 0.0;
	length = p.x = p.y = p.z = 0;
	for(x1=0; x1<in1->HeaderN.x; x1++) {
		DEBUGPRINT1("lmrcImageDensityChangeEstimationCentreOfGravitySD: %10.4f\n", x1);
	for(y1=0; y1<in1->HeaderN.y; y1++) {
	for(z1=0; z1<in1->HeaderN.z; z1++) {
		mrcPixelDataGet(in1, x1, y1, z1, &weight1, mrcPixelRePart, mrcPixelHowNearest);	
		if(0<weight1) {
			for(x2=0; x2<in2->HeaderN.x; x2++) {
			for(y2=0; y2<in2->HeaderN.y; y2++) {
			for(z2=0; z2<in2->HeaderN.z; z2++) {
				mrcPixelDataGet(in2, x2, y2, z2, &weight2, mrcPixelRePart, mrcPixelHowNearest);	
				if(0<weight2) {
					length   = sqrt(SQR(x1-x2)+SQR(y1-y2)+SQR(z1-z2)); 
					lengthXY = sqrt(SQR(x1-x2)+SQR(y1-y2)); 
					sumLength   += SQR(length  -linfo->delta  )*weight1*weight2; 	
					sumLengthXY += SQR(lengthXY-linfo->deltaXY)*weight1*weight2; 	
					p.x       += SQR(fabs(x1-x2) - linfo->change.x)*weight1*weight2; 	
					p.y       += SQR(fabs(y1-y2) - linfo->change.y)*weight1*weight2; 	
					p.z       += SQR(fabs(y1-z2) - linfo->change.z)*weight1*weight2; 	
					sumWeight += (weight1*weight2);
				}
			}
			}
			}
		}

	}
	}
	}
	linfo->changeSD.x = sqrt(p.x/sumWeight);
	linfo->changeSD.y = sqrt(p.y/sumWeight);
	linfo->changeSD.z = sqrt(p.z/sumWeight);
	linfo->deltaSD   = sqrt(sumLength/sumWeight);
	linfo->deltaXYSD = sqrt(sumLengthXY/sumWeight);
}

