/*
# %M% %Y% %I% # The latest update : %G% at %U% # #%Z% lmrcFFTInfo ver %I% #%Z% Created by #%Z% #%Z% Usage : lmrcFFTInfo #%Z% Attention #%Z%
*/
static char __sccs_id[] = "%Z%lmrcFFTInfo ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "Memory.h"
#include "Vector.h"
#include "./lmrcFFTInfo.h"

floatVector*
lmrcFSInfoXAxisMag(mrcImage* fft)
{
    floatVector* fv;
    float iX;
    double mag;
    unsigned long size, i;

    size = fft->HeaderN.x/2+1;

	fv = floatVectorInit(NULL, size);
    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
    }

    for(iX=0.0, i=0; iX>=-fft->HeaderN.x/2.0; iX--, i++) {
        mrcPixelDataGet(fft, iX, 0.0, 0.0, &mag, mrcPixelMag, mrcPixelHowNearest);
        fv->data[i] = mag;
    }
    return fv;
}

floatVector*
lmrcFSInfoXAxisPhase(mrcImage* fft)
{
    floatVector* fv;
    float iX;
    double phase;
    unsigned long size, i;

    size = fft->HeaderN.x/2+1;
	fv = floatVectorInit(NULL, size);

    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
    }

    for(iX=0.0, i=0; iX>=-fft->HeaderN.x/2.0; iX--, i++) {
        mrcPixelDataGet(fft, iX, 0.0, 0.0, &phase, mrcPixelPhase, mrcPixelHowNearest);
        fv->data[i] = phase;
    }
    return fv;
}

floatVector*
lmrcFSInfoYAxisMagAverage(mrcImage* fft)
{
    floatVector* fv;
    float iX, iY;
    double mag;
    unsigned long size, i;

    size = fft->HeaderN.y/2+1;
	fv = floatVectorInit(NULL, size);

    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
    }

    for(iY=0.0, i=0; iY>=-fft->HeaderN.y/2.0; iY--, i++) {
    	for(iX=0.0; iX<fft->HeaderN.x/2.0; iX++) {
       		mrcPixelDataGet(fft, iX, iY, 0.0, &mag, mrcPixelMag, mrcPixelHowNearest);
        	fv->data[i] += mag;
		}
		fv->data[i] /= (fft->HeaderN.x/2.0);
    }
    return fv;
}

floatVector*
lmrcFSInfoYAxisMag(mrcImage* fft)
{
    floatVector* fv;
    float iY;
    double mag;
    unsigned long size, i;

    size = fft->HeaderN.y/2+1;
	fv = floatVectorInit(NULL, size);

    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
    }

    for(iY=0.0, i=0; iY>=-fft->HeaderN.y/2.0; iY--, i++) {
        mrcPixelDataGet(fft, 0.0, iY, 0.0, &mag, mrcPixelMag, mrcPixelHowNearest);
        fv->data[i] = mag;
    }
    return fv;
}

floatVector*
lmrcFSInfoYAxisPhase(mrcImage* fft)
{
    floatVector* fv;
    float iY;
    double phase;
    unsigned long size, i;

    size = fft->HeaderN.y/2+1;
	fv = floatVectorInit(NULL, size);

    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
    }

    for(iY=0.0, i=0; iY>=-fft->HeaderN.y/2.0; iY--, i++) {
        mrcPixelDataGet(fft, 0.0, iY, 0.0, &phase, mrcPixelPhase, mrcPixelHowNearest);
        fv->data[i] = phase;
    }
    return fv;
}



double
lmrcImageFSInfoScatteringAugularDistribution3DShell(mrcImage* fft, double minR, double maxR, mrcPixelDataHowToGet mode)
{
	float iX, iY, iZ;
	double delX, delY, delZ;
	double R;
	double data, sum;
	int    count;

	delX=1.0/fft->HeaderN.x/fft->HeaderLength.x;
	delY=1.0/fft->HeaderN.y/fft->HeaderLength.y;
	delZ=1.0/fft->HeaderN.z/fft->HeaderLength.z;

	sum = 0;
	count = 0;
	for(iZ=-(int)(fft->HeaderN.z/2+0.5); iZ< fft->HeaderN.z/2; iZ++) {
	for(iY=-(int)(fft->HeaderN.y/2+0.5); iY< fft->HeaderN.y/2; iY++) {
	for(iX=-(int)(fft->HeaderN.x/2+0.5); iX< fft->HeaderN.x/2; iX++) {
		R = SQR(iX*delX) + SQR(iY*delY) + SQR(iZ*delZ);
		if(0<R) {
			R = sqrt(R);
		} else {
			R =0;
		}
		if(minR<=R && R<maxR) {
			mrcPixelDataGet(fft, iX, iY, iZ, &data, (mrcPixelDataType)mode, mrcPixelHowNearest);
			sum += data;
			count++;
		}
	}
	}
	}
	DEBUGPRINT3("DEBUG: sum, count sum/count %f %d %f\n", sum, count, sum/count );
	return sum/count;
}

floatVector*
lmrcFSInfoScatteringAngularDistribution(mrcImage* fft)
{
    floatVector* fv;
    float iX, iY;
    double pow;
    int flag, i, R;
    float mul, mul2;
    unsigned long size;

    if(fft->HeaderN.x<fft->HeaderN.y) {
        flag = 0;
        size = fft->HeaderN.x/2+1;
        mul = ((float)fft->HeaderN.x)/((float)fft->HeaderN.y);
    } else {
        flag = 1;
        size = fft->HeaderN.y/2+1;
        mul = ((float)fft->HeaderN.y)/((float)fft->HeaderN.x);
    }
    mul2 = mul*mul;

	fv = floatVectorInit(NULL, size);
    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
    }


    if(flag==0) {
        for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX+iY*iY*mul2)+0.5);
				if(R<size) {
                	fv->data[R] += pow;
				}
            }
        }
    } else {
        for(iX=-fft->HeaderN.x/2.0+1; iX<=fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX*mul2+iY*iY)+0.5);
				if(R<size) {
                	fv->data[R] += pow;
				}
            }
        }
    }
    return fv;
}

floatVector*
lmrcFSInfoScatteringAngularDistributionAverage(mrcImage* fft)
{
    floatVector* fv;
    floatVector* count;
    float iX, iY;
    double pow;
    int flag, i, R;
    float mul, mul2;
    unsigned long size;

    if(fft->HeaderN.x<fft->HeaderN.y) {
        flag = 0;
        size = fft->HeaderN.x/2+1;
        mul = ((float)fft->HeaderN.x)/((float)fft->HeaderN.y);
    } else {
        flag = 1;
        size = fft->HeaderN.y/2+1;
        mul = ((float)fft->HeaderN.y)/((float)fft->HeaderN.x);
    }
    mul2 = mul*mul;
	fv    = floatVectorInit(NULL, size);
	count = floatVectorInit(NULL, size);
	DEBUGPRINT3("%d %d %d\n", count->size, fv->size, size);
    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
        count->data[i] = 0.0;
    }

    if(flag==0) {
        for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX+iY*iY*mul2)+0.5);
				if(R<size) {
                	fv->data[R] += pow;
                	count->data[R] ++;
				}
            }
        }
    } else {
        for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX*mul2+iY*iY)+0.5);
				if(R<size) {
                	fv->data[R] += pow;
                	count->data[R] ++;
				}
            }
        }
    }
    for(i=0; i<size; i++) {
		if(0!=count->data[i]) {
        	fv->data[i] /= count->data[i] ;
		} else {
			fv->data[i] = 0;
		}
    }
    return fv;
}

/*
 floatVector**
 lmrcFSInfoScatteringAngularDistributionDivisionAverage(
 	mrcImage* fft, 
	mrcImageParaTypeReal axis,	#	first axis angle [radian]
	mrcImageParaTypeInteger n,	#   number of division [] 
	int mode)
*/

floatVector**
lmrcFSInfoScatteringAngularDistributionDivisionAverage(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger n, int mode)
{
    floatVector** fv;
	float  delR;
	float  dX, dY;

	DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionAverage Start\n");
	dX   = 1.0/(fft->HeaderN.x*fft->HeaderLength.x);
	dY   = 1.0/(fft->HeaderN.y*fft->HeaderLength.y);
	delR = MAX(dX, dY);
	DEBUGPRINT1("delR: %f\n", delR);
	fv = lmrcFSInfoScatteringAngularDistributionDivisionAverageDelR(fft, axis, n, delR, mode);

    return fv;
}

/*
 floatVector**
 lmrcFSInfoScatteringAngularDistributionDivisionSD(
 	mrcImage* fft, 
	mrcImageParaTypeReal axis,	#	first axis angle [radian]
	mrcImageParaTypeInteger n,	#   number of division [] 
	int mode)
*/

floatVector**
lmrcFSInfoScatteringAngularDistributionDivisionSD(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger n, int mode)
{
    floatVector** fv;
	float  delR;
	float  dX, dY;

	DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionSD Start\n");
	dX   = 1.0/(fft->HeaderN.x*fft->HeaderLength.x);
	dY   = 1.0/(fft->HeaderN.y*fft->HeaderLength.y);
	delR = MAX(dX, dY);
	DEBUGPRINT1("delR: %f\n", delR);
	fv = lmrcFSInfoScatteringAngularDistributionDivisionSDDelR(fft, axis, n, delR, mode);

    return fv;
}


/*
 floatVector**
 lmrcFSInfoScatteringAngularDistributionDivisionAverage(
 	mrcImage* fft, 
	mrcImageParaTypeReal    axis,	#	first axis angle [radian]
	mrcImageParaTypeInteger nDiv,	#   number of division [] 
	mrcImageParaTypeReal    delR,	#   delR [] 
	int mode)
*/

floatVector**
lmrcFSInfoScatteringAngularDistributionDivisionAverageDelR(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger nDiv, mrcImageParaTypeReal delR, int mode)
{
    floatVector** fv;
    floatVector** count;
    int iX, iY;
    double re, im, pow;
    int flag, i, j, iAngle;
	float dX, dY, angle, R;
    float mul, mul2;
    float* data;
    unsigned long size;
	float maxX, maxY, maxR;
	float dXdX, dYdY;
	int iR;


	DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionAverageDelR");
	DEBUGPRINT3("delR: %f nDiv: %d axis: %f\n", delR, nDiv, axis);

	/* dX, dY [/A] */
	dX   = 1.0/(fft->HeaderN.x*fft->HeaderLength.x);
	dXdX = SQR(dX);
	dY   = 1.0/(fft->HeaderN.y*fft->HeaderLength.y);
	dYdY = SQR(dY);
	DEBUGPRINT5("delR: %g dX: %g dXdX %g dY: %g dYdY: %g\n", delR, dX, dXdX, dY, dYdY);

	/* size */
	maxX = 1.0/(2*fft->HeaderLength.x);
	maxY = 1.0/(2*fft->HeaderLength.y);
	maxR = MAX(maxX, maxY);
	size = (int)(maxR/delR) + 1;


	fv     = memoryAllocate(sizeof(floatVector*)*nDiv, "in lmrcFSInfoScatteringAngularDistributionDivisionAverage");
	count  = memoryAllocate(sizeof(floatVector*)*nDiv, "in lmrcFSInfoScatteringAngularDistributionDivisionAverage");
	for(i=0; i<nDiv; i++) {
		fv[i]    = floatVectorInit(NULL, size);
		count[i] = floatVectorInit(NULL, size);
	}
	DEBUGPRINT3("count size %d fv size %d size %d\n", count[0]->size, fv[0]->size, size);
    /* Clear */
    for(i=0; i<nDiv; i++) {
    for(j=0; j<size; j++) {
        fv[i]->data[j] = 0.0;
        count[i]->data[j] = 0.0;
    }
	}

    for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
    for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
    	mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
        R  = sqrt(SQR(iX*dX)+SQR(iY*dY));
		iR = (int)(R/delR + 0.5);
		//DEBUGPRINT5("%g / %g -> %d @ %d %d\n", R, delR, iR, iX, iY);
		angle = atan2(iY*dY, iX*dX) - axis;
		iAngle = ((int)(fmod(angle+4.0*M_PI, 2.0*M_PI)/(2.0*M_PI/nDiv) + 0.5))%nDiv; 
		if(iR<size) {
			//if(0<pow) {
			 	//DEBUGPRINT2("@ %d %d\n", iX, iY);
			 	//DEBUGPRINT5("fv[%d]->data[%d] %f @ %g %g\n", iAngle, iR, pow, angle*DEGREE, R);
			//}
        	fv[iAngle]->data[iR]    += pow;
        	count[iAngle]->data[iR] ++;
		}
    }
    } 
	
    for(i=0; i<nDiv; i++) {
    for(j=0; j<size; j++) {
		if(0!=count[i]->data[j]) {
        	fv[i]->data[j] /= count[i]->data[j] ;
			DEBUGPRINT3("fv[%d]->data[%d] %f\n", i, j, fv[i]->data[j]);
		} else {
			fv[i]->data[j] = 0;
		}
    }
	}
    return fv;
}

/*
 floatVector**
 lmrcFSInfoScatteringAngularDistributionDivisionSDDelR(
 	mrcImage* fft, 
	mrcImageParaTypeReal    axis,	#	first axis angle [radian]
	mrcImageParaTypeInteger nDiv,	#   number of division [] 
	mrcImageParaTypeReal    delR,	#   delR [] 
	int mode)
*/

floatVector**
lmrcFSInfoScatteringAngularDistributionDivisionSDDelR(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger nDiv, mrcImageParaTypeReal delR, int mode)
{
    floatVector** fv;
    floatVector** fv2;
    floatVector** count;
    int iX, iY;
    double re, im, pow;
    int flag, i, j, iAngle;
	float dX, dY, angle, R;
    float mul, mul2;
    float* data;
    unsigned long size;
	float maxX, maxY, maxR;
	float dXdX, dYdY;
	int iR;


	DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionAverageDelR");
	DEBUGPRINT3("delR: %f nDiv: %d axis: %f\n", delR, nDiv, axis);

	/* dX, dY [/A] */
	dX   = 1.0/(fft->HeaderN.x*fft->HeaderLength.x);
	dXdX = SQR(dX);
	dY   = 1.0/(fft->HeaderN.y*fft->HeaderLength.y);
	dYdY = SQR(dY);
	DEBUGPRINT5("delR: %g dX: %g dXdX %g dY: %g dYdY: %g\n", delR, dX, dXdX, dY, dYdY);

	/* size */
	maxX = 1.0/(2*fft->HeaderLength.x);
	maxY = 1.0/(2*fft->HeaderLength.y);
	maxR = MAX(maxX, maxY);
	size = (int)(maxR/delR) + 1;


	fv     = memoryAllocate(sizeof(floatVector*)*nDiv, "in lmrcFSInfoScatteringAngularDistributionDivisionAverage");
	fv2    = memoryAllocate(sizeof(floatVector*)*nDiv, "in lmrcFSInfoScatteringAngularDistributionDivisionAverage");
	count  = memoryAllocate(sizeof(floatVector*)*nDiv, "in lmrcFSInfoScatteringAngularDistributionDivisionAverage");
	for(i=0; i<nDiv; i++) {
		fv[i]    = floatVectorInit(NULL, size);
		fv2[i]   = floatVectorInit(NULL, size);
		count[i] = floatVectorInit(NULL, size);
	}
	DEBUGPRINT3("count size %d fv size %d size %d\n", count[0]->size, fv[0]->size, size);
    /* Clear */
    for(i=0; i<nDiv; i++) {
    for(j=0; j<size; j++) {
        fv[i]->data[j] = 0.0;
        fv2[i]->data[j] = 0.0;
        count[i]->data[j] = 0.0;
    }
	}

    for(iY=-fft->HeaderN.y/2.0+1; iY<=fft->HeaderN.y/2.0; iY++) {
    for(iX=-fft->HeaderN.x/2.0+1; iX<=fft->HeaderN.x/2.0; iX++) {
    	mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
        R  = sqrt(SQR(iX*dX)+SQR(iY*dY));
		iR = (int)(R/delR + 0.5);
		//DEBUGPRINT5("%g / %g -> %d @ %d %d\n", R, delR, iR, iX, iY);
		angle = atan2(iY*dY, iX*dX) - axis;
		iAngle = ((int)(fmod(angle+4.0*M_PI, 2.0*M_PI)/(2.0*M_PI/nDiv) + 0.5))%nDiv; 
		if(iR<size) {
			//if(0<pow) {
			 	//DEBUGPRINT2("@ %d %d\n", iX, iY);
			 	//DEBUGPRINT5("fv[%d]->data[%d] %f @ %g %g\n", iAngle, iR, pow, angle*DEGREE, R);
			//}
        	fv[iAngle]->data[iR]    += pow;
        	count[iAngle]->data[iR] ++;
		}
    }
    } 
	
    for(i=0; i<nDiv; i++) {
    for(j=0; j<size; j++) {
		if(0!=count[i]->data[j]) {
        	fv[i]->data[j] /= count[i]->data[j];
			DEBUGPRINT3("fv[%d]->data[%d] %f\n", i, j, fv[i]->data[j]);
		} else {
			fv[i]->data[j] = 0;
		}
    }
	}

    for(iY=-fft->HeaderN.y/2.0+1; iY<=fft->HeaderN.y/2.0; iY++) {
    for(iX=-fft->HeaderN.x/2.0+1; iX<=fft->HeaderN.x/2.0; iX++) {
    	mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
        R  = sqrt(SQR(iX*dX)+SQR(iY*dY));
		iR = (int)(R/delR + 0.5);
		//DEBUGPRINT5("%g / %g -> %d @ %d %d\n", R, delR, iR, iX, iY);
		angle = atan2(iY*dY, iX*dX) - axis;
		iAngle = ((int)(fmod(angle+4.0*M_PI, 2.0*M_PI)/(2.0*M_PI/nDiv) + 0.5))%nDiv; 
		if(iR<size) {
			//if(0<pow) {
			 	//DEBUGPRINT2("@ %d %d\n", iX, iY);
			 	//DEBUGPRINT5("fv[%d]->data[%d] %f @ %g %g\n", iAngle, iR, pow, angle*DEGREE, R);
			//}
        	fv2[iAngle]->data[iR] += SQR(pow-fv[iAngle]->data[iR]);
		}
    }
    } 

    for(i=0; i<nDiv; i++) {
    for(j=0; j<size; j++) {
		if(0!=count[i]->data[j]) {
        	fv[i]->data[j] = sqrt(fv2[i]->data[j]/count[i]->data[j]);
			DEBUGPRINT3("fv[%d]->data[%d] %f\n", i, j, fv[i]->data[j]);
		} else {
			fv[i]->data[j] = 0;
		}
    }
	}
	
	for(i=0; i<nDiv; i++) {
		floatVectorFree(fv2[i]);
		floatVectorFree(count[i]);
	}
    return fv;
}

floatVector*
lmrcFSInfoScatteringAngularDistributionSD(mrcImage* fft)
{
    floatVector* fv;
    doubleVector* ave;
    doubleVector* ave2;
    doubleVector* count;
    doubleVector* count2;
    double iX, iY;
    double re, im, pow;
    int flag, i, R;
    double mul, mul2;
    double* data;
    unsigned long size;

    if(fft->HeaderN.x<fft->HeaderN.y) {
        flag = 0;
        size = fft->HeaderN.x/2+1;
        mul = ((double)fft->HeaderN.x)/((double)fft->HeaderN.y);
    } else {
        flag = 1;
        size = fft->HeaderN.y/2+1;
        mul = ((double)fft->HeaderN.y)/((double)fft->HeaderN.x);
    }
    mul2 = mul*mul;
	fv    = floatVectorInit(NULL, size);
	ave   = doubleVectorInit(NULL, size);
	ave2  = doubleVectorInit(NULL, size);
	count = doubleVectorInit(NULL, size);
	count2= doubleVectorInit(NULL, size);
	DEBUGPRINT3("%d %d %d\n", count->size, fv->size, size);
    /* Clear */
    for(i=0; i<size; i++) {
        fv->data[i] = 0.0;
        ave->data[i] = 0.0;
        ave2->data[i] = 0.0;
        count->data[i] = 0.0;
        count2->data[i] = 0.0;
    }
	/* Calc Mean */ 
    if(flag==0) {
        for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX+iY*iY*mul2)+0.5);
				if(R<size) {
                	ave->data[R] += pow;
                	count->data[R] ++;
				}
            }
        }
    } else {
        for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX*mul2+iY*iY)+0.5);
				if(R<size) {
                	ave->data[R]   += pow;
                	count->data[R] ++;
				}
            }
        }
    }
    for(i=0; i<size; i++) {
		if(0!=count->data[i]) {
        	ave->data[i]  /= count->data[i] ;
		} else {
			ave->data[i] = 0;
		}
    }
	/* Calc SD  */
    if(flag==0) {
        for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX+iY*iY*mul2)+0.5);
				if(R<size) {
                	ave2->data[R] += SQR(pow - ave->data[R]);
                	count2->data[R] ++;
				}
            }
        }
    } else {
        for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
            for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++) {
                mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
                R = (int)(sqrt(iX*iX*mul2+iY*iY)+0.5);
				if(R<size) {
					if(R<=2) {
						DEBUGPRINT3("%d %f %f\n", R, pow, ave->data[R]);
					}
                	ave2->data[R] += SQR(pow - ave->data[R]);
                	count2->data[R] ++;
				}
            }
        }
    }
    for(i=0; i<size; i++) {
		if(0!=count2->data[i]) {
			if(count->data[i]!=count2->data[i]) {
				fprintf(stderr, "Something Wrong\n");
			}
        	fv->data[i] = sqrt(ave2->data[i]/count2->data[i]);
			DEBUGPRINT6("%d %f %f %f %f %f\n", i, count2->data[i], ave->data[i], ave2->data[i], fv->data[i], fv->data[i]/sqrt(count2->data[i]));
		} else {
			fv->data[i] = 0;
		}
    }

    return fv;
}

/*
* lmrcFSInfoSpacing(
	mrcImage* fft		#
	)
	return: Spacing Information as floatVector;
*/
floatVector*
lmrcFSInfoSpacing(mrcImage* fft)
{
    floatVector* fv;
    int flag, i, R; 
	unsigned long size;

    if(fft->HeaderN.x<fft->HeaderN.y) {
        flag = 0;
        size = fft->HeaderN.x/2+1;
    } else {
        flag = 1;
        size = fft->HeaderN.y/2+1;
    }
	fv    = floatVectorInit(NULL, size);
	DEBUGPRINT2("%d %d\n", fv->size, size);
	if(fft->HeaderN.x<fft->HeaderN.y) {
    	for(i=0; i<size; i++) {
       		fv->data[i] = i/(fft->HeaderN.x*fft->HeaderLength.x);
    	}
	} else {
    	for(i=0; i<size; i++) {
       		fv->data[i] = i/(fft->HeaderN.y*fft->HeaderLength.y);
    	}
	}
    return fv;
}

/*
* lmrcFSInfoSpacing2(
	mrcImage* fft,					# 	
	mrcImageParaTypeReal    dR		# deltaR [/A]
	);
	return: Spacing Information as floatVector;
*/

floatVector*
lmrcFSInfoSpacing2(mrcImage* fft, mrcImageParaTypeReal dR)
{
    floatVector* fv;
    int flag, i, R; 
	unsigned long size;
	double maxR;

	if(fft->HeaderLength.x<fft->HeaderLength.y) { 
		maxR = 1.0/(fft->HeaderLength.x)/2.0;
	} else  {
		maxR = 1.0/(fft->HeaderLength.y)/2.0;
	}
	size = (int)(maxR/dR) + 1;
	fv    = floatVectorInit(NULL, size);
    for(i=0; i<size; i++) {
		fv->data[i] = i*dR;
    }
    return fv;
}

void
lmrcFSInfoYAxisProjection(mrcImage* out, mrcImage* in, long mode)
{
	floatVector* YAxisMagAvg;
	mrcImageParaTypeReal iY;
	mrcImageParaTypeInteger i;
	double data;

	YAxisMagAvg = lmrcFSInfoYAxisMagAverage(in);

	out->HeaderN.x = 1;
	out->HeaderN.y = in->HeaderN.y;
	out->HeaderN.z = 1;
	out->HeaderLength.x = in->HeaderLength.x;
	out->HeaderLength.y = in->HeaderLength.y;
	out->HeaderLength.z = in->HeaderLength.z;
	out->HeaderMode = mrcComplexFloatFT;
	
	mrcInit(out, NULL);

	data= 0.0;
    for(iY=-out->HeaderN.y/2.0; iY < out->HeaderN.y/2.0; iY++) {
			if(iY < 0) {
				i = (int)floor(-iY +0.5);
			} else {
				i = (int)floor( iY +0.5);
			}
        	data = YAxisMagAvg->data[i];
        	DEBUGPRINT3("data=%15.6f iY=%f i=%5d\n", data, iY, (int)i);
       		mrcPixelDataSet(out, 0.0, iY, 0.0, data, mrcPixelRePart);
       		mrcPixelDataSet(out, 0.0, iY, 0.0,  0.0, mrcPixelImPart);
    }
}

void
lmrcFSInfoXFiltering(mrcImage* out, mrcImage* in, float RMaxX, long mode)
{
	mrcImageParaTypeReal iX, iY;
	mrcImageParaTypeInteger RX;
	float sampling;
	double re, im;

	RX = (int)(RMaxX*in->HeaderN.x*in->HeaderLength.x);  /* Pixel */
	sampling = 0.5/in->HeaderLength.x;
	
    DEBUGPRINT2("RMaxX=%15.6f Pixel=%5d\n", RMaxX, (int)RX);
    DEBUGPRINT1("Pixel Sampling %15.6f \n", sampling);

	if (RMaxX > sampling) {
		fprintf(stderr, "RMaxX:%15.6f  beyond this pixel sampling %15.6f \n", 
							RMaxX, sampling);
		fprintf(stderr, "Pixel sampling is :1/(%15.6f * 2)\n", 
							in->HeaderLength.x);
		fprintf(stderr, "RMaxX is substitide for sampling\n");
		RMaxX = sampling;
		RX = (int)(RMaxX*in->HeaderN.x*in->HeaderLength.x);  /* Pixel */
	}

    DEBUGPRINT2("RMaxX=%15.6f Pixel=%5d\n", RMaxX, (int)RX);

	out->HeaderN.x = 2*RX;
	out->HeaderN.y = in->HeaderN.y;
	out->HeaderN.z = in->HeaderN.z;
	out->HeaderLength.x = in->HeaderLength.x;
	out->HeaderLength.y = in->HeaderLength.y;
	out->HeaderLength.z = in->HeaderLength.z;
	out->HeaderMode = mrcComplexFloatFT;
	
	mrcInit(out, NULL);

	re = 0.0;
	im = 0.0;

    for(iY=-in->HeaderN.y/2.0; iY<=in->HeaderN.y/2.0 -1; iY++) {
    	for(iX=0.0; iX<=RX; iX++) {
       		mrcPixelDataGet(in , iX, iY, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
       		mrcPixelDataGet(in , iX, iY, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
       		mrcPixelDataSet(out, iX, iY, 0.0,  re, mrcPixelRePart);
       		mrcPixelDataSet(out, iX, iY, 0.0,  im, mrcPixelImPart);
		}
    }
}

/*
* lmrcFSInfo
* 
*/

void 
lmrcFSInfo(mrcFSInfo* linfo, mrcImage* mrc)
{
	mrcImageParaTypeReal X, Y, Z;
	double data;	

	mrcPixelDataGet(mrc, 0, 0, 0, &(linfo->F00), mrcPixelMag, mrcPixelHowNearest);

	linfo->Max = 0.0;
	linfo->MaxExceptForF00 = 0.0;
	for(X=0; X<=mrc->HeaderN.x/2.0; X++) {
	for(Y=-mrc->HeaderN.y/2.0; Y<mrc->HeaderN.y/2.0; Y++) {
	for(Z=-mrc->HeaderN.z/2.0; Z<mrc->HeaderN.z/2.0; Z++) {
		mrcPixelDataGet(mrc, X, Y, Z, &data, mrcPixelMag, mrcPixelHowNearest);
		if(linfo->Max<data) {
			linfo->Max = data;
		}
		if(! (X==0 && Y==0 && Z==0) && linfo->MaxExceptForF00 < data) {
			linfo->MaxExceptForF00 = data;
		}
	}
	}
	}
}
