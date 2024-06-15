/*
# lmrcImageCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageCorrelation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

static char __sccs_id[] = "%Z%lmrcImageCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"       
#include "./lmrcImageCorrelation.h"
#include "lDescartesIntoPolar.h"
#include "./lmrcImageTransformDescartesIntoPolar.h"
#include "Map2D.h"

/* 
	$lmrcImageEuclidDistanceCalc:  Calculate Euclid distance between two images $
		$arg: in1:  input mrcImage1 $
		$arg: in2:  input mrcImage2 $
		$arg: mode: input int $
		$mode: 0 Sum of SQR $
		$mode: 1 Distance $
		$mode: 2 normalized by pixel number
		$return: EuclidDistance $
*/
double 
lmrcImageEuclidDistanceCalc(mrcImage* in1, mrcImage* in2, int mode)
{
	double r;
	lmrcImageEuclidDistanceCalc2(&r, in1, in2, mode);
	return r;
}

void
lmrcImageEuclidDistanceCalc2(double* r, mrcImage* in1, mrcImage* in2, int mode)
{
	double data1, data2;
	double data;
	mrcImageParaTypeReal x, y, z;
	int count;
	if(in1->HeaderN.x!=in2->HeaderN.x
	 ||in1->HeaderN.y!=in2->HeaderN.y
	 ||in1->HeaderN.z!=in2->HeaderN.z) {
		fprintf(stderr, "Attention in lmrcImageEuclidDistanceCalc\n");
		fprintf(stderr, "size is different (%d, %d, %d) != (%d, %d, %d)\n", 
			in1->HeaderN.x, in1->HeaderN.y, in1->HeaderN.z,
			in2->HeaderN.x, in2->HeaderN.y, in2->HeaderN.z);
	}
	data = 0.0;
	for(z=0; z<in1->HeaderN.z; z++) {
	for(y=0; y<in1->HeaderN.y; y++) {
	for(x=0; x<in1->HeaderN.x; x++) {
		 mrcPixelDataGet(in1 ,x ,y ,z ,&data1 ,mrcPixelRePart ,mrcPixelHowNearest);
		 mrcPixelDataGet(in2 ,x ,y ,z ,&data2 ,mrcPixelRePart ,mrcPixelHowNearest);
		 data += SQR(data2-data1);
	}
	}
	}
	count = in1->HeaderN.x*in1->HeaderN.y*in1->HeaderN.z;

	switch(mode&0x01) {
		case 0: {
			break;
		}
		case 1: {
			if(data!=0) {
				data = sqrt(data);
			}
			break;
		}
	} 

	if(mode&0x02) {
		data /= count;
	}

	*r = data;
	//return data;
}

/*

*/
void
lmrcImageAutoRotationCorrelationRotationalCrossCorrelationFunction(
	mrcImage* out,  mrcImage* cor, 
    mrcImage* in, mrcImage* ref, 
	lmrcImageAutoRotationCorrelationInfo* linfo, int mode)
{
	mrcImage inPolar;
	mrcImage refPolar;
	mrcImage Cor;
	lmrcImageTransformDescartesIntoPolarInfo llinfoIn;
	lmrcImageTransformDescartesIntoPolarInfo llinfoRef;
	lDescartesIntoPolarInfo                  llinfo2In;
	lDescartesIntoPolarInfo                  llinfo2Ref;

	llinfoIn.dr     = ref->HeaderLength.x; 
	llinfoIn.dphi   = 2*M_PI/linfo->nRot;
	llinfoIn.dtheta = 2*M_PI;
	llinfoIn.flagImageCentreIsGravityCentre = 1;
	llinfoIn.flagDescartesIntoPolarInfo    = 0;
	llinfoIn.flagrWeight                    = 1;
	llinfoRef = llinfoIn;
	lmrcImageTransformDescartesIntoPolar(&inPolar,  in,  &llinfoIn,  &llinfo2In, 0);  
	lmrcImageTransformDescartesIntoPolar(&refPolar, ref, &llinfoRef, &llinfo2Ref, 0);  
	lmrcImageCorrelation(&Cor, &inPolar, &refPolar, mode);
	linfo->corInfo.mode = meanOfAll;
	lmrcImageInformation(&(linfo->corInfo), &Cor);
	linfo->max      = linfo->corInfo.max;
	linfo->maxP     = linfo->corInfo.maxCoord;
	linfo->maxTheta = linfo->maxP.x*llinfoIn.dphi;
	mrcImageFree(&inPolar, 0);
	mrcImageFree(&refPolar, 0);
	mrcImageFree(&Cor, 0);
}

/*
	lmrcImageAutoRotationCorrelation
*/

void
lmrcImageAutoRotationCorrelation(mrcImage* out,  mrcImage* cor, 
                                 mrcImage* in, mrcImage* ref, 
								 lmrcImageAutoRotationCorrelationInfo* linfo, int mode)
{
	int i;
	int ntheta;
	int itheta;
	float dtheta;
	float theta;
	float minTheta;
	float maxTheta;
	float maxOld;
	double current;
	mrcImageParaTypeRealCoord currentp;
	mrcImage rotproj;
	mrcImage inFFT;
	mrcImage inImage;
	double data;
	mrcImageParaTypeReal x, y, z;
	double distance;

	DEBUGPRINT("Start lmrcImageAutoRotationCorrelation---\n");
	/* 
		Real Space to Fourier Space 
			Set inImage and inFFT 
	*/
	if(IsImage(in, "IsImage", 0)) {
		lmrcImageFFT(&inFFT, in, 0);
		inImage = *in;
	} else if(IsFT(in, "IsFT", 0)) {
		lmrcImageFFT(&inImage, in, 0);
		inFFT = *in;
	} else {
		fprintf(stderr, "Not supported mode: %d\n", in->HeaderMode);
	}
	
	/* 
		Calculate corralation between in and rotated ref 
			Set search area
	*/
	if(linfo->flagRestrictionArea == 1) {
		minTheta = linfo->thetaMin;
		maxTheta = linfo->thetaMax;
	} else {
		minTheta = 0;                       /* minimum theta */  
		maxTheta = 2.0*M_PI;       			/* maximum theta */
	}
	ntheta = linfo->nRot;         		  /* Number of Rotation */
	dtheta = (maxTheta-minTheta)/ntheta;  /* Delta of Rotation */  
	linfo->corInfo.mode = meanOfAll;

	DEBUGPRINT4("nRot: %d %f<->%f delta %f\n", ntheta, maxTheta, minTheta, dtheta);

	switch(linfo->Method) {
		case lmrcImageAutoRotationCorrelationMethodRotationAndCorrelation:
		case lmrcImageAutoRotationCorrelationMethodRotationAndCorrelationSSDA: {
			current  = -1e30; linfo->max = maxOld = -1e30; /* Initial */ 
			for(i=0; i<linfo->iter; i++) {
				//for(theta=minTheta; theta<maxTheta; theta+=dtheta) {
				for(itheta=0; itheta<ntheta; itheta++) {
					theta = minTheta +  itheta*dtheta;
					/* Rotate ref to rotproj */ 
					//fprintf(stderr, "nRot: %d theta: %f %f<->%f delta %f\n", ntheta, theta*DEGREE, maxTheta*DEGREE, minTheta*DEGREE, dtheta*DEGREE);
					DEBUGPRINT5("nRot: %d theta: %f %f<->%f delta %f\n", ntheta, theta, maxTheta, minTheta, dtheta);
					lmrcImageRotation2DPeriodicBoundary(&rotproj, ref, theta, mrcPixelHowLinear); 
					switch(linfo->Method) {
						case lmrcImageAutoRotationCorrelationMethodRotationAndCorrelation: {
							lmrcImageCorrelation(cor, &inFFT, &rotproj, mode); 
							if(linfo->flagXshiftOnly) {
								current = -1e30;
								for(x=0; x<cor->HeaderN.x; x++) {
									//mrcPixelDataGet(cor, x, 0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
									data = cor->ImageFloatImage[(int)(x+0.5)];
									if(current<data) {
										current    = data;
										currentp.x = x; 
										currentp.y = 0.0;
										currentp.z = 0.0;
									}
								}
							} else if(linfo->flagNoShift) {
								currentp.x = currentp.y = currentp.z = 0.0;
								mrcPixelDataGet(cor, 0, 0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
								data = cor->ImageFloatImage[0]; 
								current = data;   
							} else if(linfo->flagShiftRange) {
								DEBUGPRINT("ShiftRange Restruction\n");
								//mrcPixelDataGet(cor, 0, 0, 0, &current, mrcPixelRePart, mrcPixelHowNearest);
								current = cor->ImageFloatImage[0];
								for(x=linfo->shiftMinX; x<=linfo->shiftMaxX; x++) {
								for(y=linfo->shiftMinY; y<=linfo->shiftMaxY; y++) {
									//mrcPixelDataGet(cor, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
									data = cor->ImageFloatImage[(int)(x+0.5)+(int)(y+0.5)*cor->HeaderN.x+(int)(z+0.5)*cor->HeaderN.x*cor->HeaderN.y];
									if(current<data) {
										currentp.x = x;
										currentp.y = y;
										currentp.z = 0.0;
										current = data;
									}
								}
								}
							} else {
								lmrcImageInformation(&(linfo->corInfo), cor);
								current  = linfo->corInfo.max;
								currentp = linfo->corInfo.maxCoord;
							}
							break;
						}
						case lmrcImageAutoRotationCorrelationMethodRotationAndCorrelationSSDA: {
							lmrcImageSSDAAutomaticThresholdAndFineSearch(&inImage, &rotproj, &linfo->SSDAInfo, mode);
							current = 1/(1+linfo->SSDAInfo.Error);
							currentp = linfo->SSDAInfo.optimump;
							DEBUGPRINT4("Angle: %15.6f Correlation: %15.6g at %15.6f %15.6f :: CurrentMax :: Linear \n", 
								theta*DEGREE, current, currentp.x, currentp.y);
							break;
						}
						default: {
							fprintf(stderr, "Not supported Method in lmrcImageAutoRotationCorrelation: %d\n", 
								linfo->Method);
							exit(EXIT_FAILURE);
							break;
						}
					}
					if(linfo->max<current) { /* When bettern correlation */ 
						linfo->max      = current;
						linfo->maxTheta = theta;
						linfo->maxP     = currentp;
						DEBUGPRINT4("Angle: %15.6f Correlation: %15.6g at %15.6f %15.6f :: CurrentMax :: Linear \n", 
							theta*DEGREE, current, currentp.x, currentp.y);
						fprintf(stderr, "Angle: %15.6f Correlation: %15.6g at %15.6f %15.6f :: CurrentMax :: Linear \n", 
							theta*DEGREE, current, currentp.x, currentp.y);
					}
					mrcImageFree(&rotproj, 0);
					mrcImageFree(cor, 0);
				}
				/*
				if(fabs(maxOld+linfo->max)!=0) {
					if(fabs(maxOld-linfo->max)/fabs(maxOld+linfo->max)<1e-6) {
						break;
					} else {
						maxOld = linfo->max;
						minTheta = linfo->maxTheta - dtheta; 
						maxTheta = linfo->maxTheta + dtheta; 
						dtheta  /= 10.0;
					}
				} else {
					maxOld = linfo->max;
					minTheta = linfo->maxTheta - dtheta; 
					maxTheta = linfo->maxTheta + dtheta; 
					dtheta  /= 10.0;
				}
				*/
				maxOld = linfo->max;
				minTheta = linfo->maxTheta - dtheta; 
				maxTheta = linfo->maxTheta + dtheta; 
				dtheta  /= 10.0;
			}
			break;
		}
		case lmrcImageAutoRotationCorrelationMethodRotationalFunction: { /* Rotational Correlation Function */
			lmrcImageAutoRotationCorrelationRotationalCrossCorrelationFunction(out, cor, in, ref, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Method in lmrcImageAutoRotationCorrelation: %d\n", linfo->Method);
			exit(EXIT_FAILURE);
			break;
		}
	}
	/* Calculate final correlation map and correlation peak */
	lmrcImageRotation2DPeriodicBoundary(&rotproj, ref, linfo->maxTheta, mrcPixelHowCubicConv); 
	lmrcImageCorrelation(cor, &inFFT, &rotproj, mode);
	
	if(linfo->flagXshiftOnly) {
		linfo->max = -1e30;
		for(x=0; x<cor->HeaderN.x; x++) {
			//mrcPixelDataGet(cor, x, 0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
			data = cor->ImageFloatImage[(int)(x+0.5)];
			if(linfo->max<data) {
				linfo->max    = data;
				linfo->maxP.x = x;
				linfo->maxP.y = 0.0;
				linfo->maxP.z = 0.0;
			}
		}
	} else if(linfo->flagNoShift) {
		//mrcPixelDataGet(cor, 0, 0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		data = cor->ImageFloatImage[0];  
		linfo->max = data;
		linfo->maxP.x = linfo->maxP.y = linfo->maxP.z = 0.0;
	} else if(linfo->flagShiftRange) {
		DEBUGPRINT("Last ShiftRange Restruction\n");
		DEBUGPRINT4("Angle: %15.6f Correlation: %15.6f at %15.6f %15.6f :: MaxPoint:: Cubic\n", 
			linfo->maxTheta*DEGREE, linfo->maxP.x, linfo->maxP.y, linfo->corInfo.maxCoord.z); 
	} else {
		linfo->corInfo.mode = meanOfAll;
		lmrcImageInformation(&(linfo->corInfo), cor);
		DEBUGPRINT4("Angle: %15.6f Correlation: %15.6f at %15.6f %15.6f :: MaxPoint:: Cubic\n", \
			linfo->maxTheta*DEGREE, linfo->corInfo.max, linfo->corInfo.maxCoord.x, linfo->corInfo.maxCoord.y); 
		linfo->max  = linfo->corInfo.max;
		linfo->maxP = linfo->corInfo.maxCoord;
	}
	mrcImageFree(&rotproj, 0);

	/* Calculate outImage from inImage */
	currentp.x = -linfo->maxP.x;
	currentp.y = -linfo->maxP.y;
	currentp.z = -linfo->maxP.z;
	lmrcImageShift(&rotproj, &inImage, currentp, mrcPixelHowCubicConv); 
	lmrcImageRotation2DPeriodicBoundary(out, &rotproj, -linfo->maxTheta, mrcPixelHowCubicConv); 
	//lmrcImageRotation2DPeriodicBoundary(&rotproj, &inImage, -linfo->maxTheta, mrcPixelHowCubicConv); 
	//lmrcImageShift(&out, &rotproj, currentp, mrcPixelHowCubicConv); 
	lmrcImageEuclidDistanceCalc2(&distance, out, ref, 1);  
	linfo->EuclidDistance = distance;	
	lmrcImageLinearCorrelation2 (&distance,out, ref, 1);  
	linfo->LinearCorrelation = distance;
	DEBUGPRINT1("EuclidDistance:    %f \n", linfo->EuclidDistance); 
	DEBUGPRINT1("LinearCorrelation: %f \n", linfo->LinearCorrelation); 

	mrcImageFree(&rotproj, 0);
	if(IsImage(in, "IsImage", 0)) {
		mrcImageFree(&inFFT, 0);
	} else if(IsFT(in, "IsFT", 0)) {
		mrcImageFree(&inImage, 0);
	} else {
		fprintf(stderr, "Not supported mode: %d\n", in->HeaderMode);
	}
}

void
lmrcImageCorrelationRefinement(mrcImage* out, mrcImage* shift, mrcImage* in, mrcImage* ref, lmrcImageCorrelationRefinementInfo* info, long mode)
{
    mrcImage inFFT;
    mrcImage refFFT;
    mrcImage shiftFFT;
	long     flagIn  = 0;
	long     flagRef = 0;
	mrcImageParaTypeReal  x,  y,  z;
	mrcImageParaTypeReal ix, iy, iz;
	mrcImageParaTypeReal nx, ny, nz;
	mrcImageParaTypeReal sx, sy, sz;
	mrcImageParaTypeReal dx, dy, dz;
	mrcImageParaTypeReal X, Y, Z;
	double mag, phase;
	double rmag, rphase;
	double eval;
	double sum;
	double deltaPhase;
	double dp;

    if(IsImage(in, "", 0)&&IsImage(ref, "", 0)) {
        lmrcImageFFT(&inFFT,  in, 0);
        lmrcImageFFT(&refFFT, ref, 0);
		flagIn = flagRef = 1;
    } else if(IsFT(in, "", 0)&&IsImage(ref, "", 0)) {
        inFFT = *in;
        lmrcImageFFT(&refFFT, ref, 0);
		flagRef = 1;
    } else if(IsImage(in, "", 0)&&IsFT(ref, "", 0)) {
        lmrcImageFFT(&inFFT,  in, 0);
        refFFT = *ref;
		flagIn = 1;
    } else if(IsFT(in, "", 0)&&IsFT(ref, "", 0)) {
        inFFT = *in;
        refFFT = *ref;
    } else {
        fprintf(stderr, "Nut supported Mode (in %d, ref %d)\n", in->HeaderMode, ref->HeaderMode);
        exit(EXIT_FAILURE);
   	}

	if(1<in->HeaderN.x) {
		sx = info->shift.x - info->range.x; 
		nx = 2*info->range.x/info->step.x + 1;
	} else {
		sx = 0;
		nx = 1;
	}
	if(1<in->HeaderN.y) {
		sy = info->shift.y - info->range.y; 
		ny = 2*info->range.y/info->step.y + 1;
	} else {
		sy = 0;
		ny = 1;
	}
	if(1<in->HeaderN.z) {
		sz = info->shift.z - info->range.z; 
		nz = 2*info->range.z/info->step.z + 1;
	} else {
		sz = 0;
		nz = 1;
	}
	dx = info->step.z;
	dy = info->step.z;
	dz = info->step.z;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = nx;
	out->HeaderN.y = ny;
	out->HeaderN.z = nz;
	out->HeaderMode = mrcFloatImage;
	out->HeaderLength.x = dx*in->HeaderLength.x;
	out->HeaderLength.y = dy*in->HeaderLength.y;
	out->HeaderLength.z = dz*in->HeaderLength.z;
	mrcInit(out, NULL);

	for(ix=0, x=sx; ix<nx; ix++, x+=dx) {
	for(iy=0, y=sy; iy<ny; iy++, y+=dy) {
	for(iz=0, z=sz; iz<nz; iz++, z+=dz) {
		eval = sum = 0.0;
		for(X=0;                  X<=in->HeaderN.x/2.0; X++) {
		for(Y=-in->HeaderN.y/2.0; Y< in->HeaderN.y/2.0; Y++) {
		for(Z=-in->HeaderN.z/2.0; Z< in->HeaderN.z/2.0; Z++) {
			deltaPhase = -2*M_PI*x*X/in->HeaderN.x 
						 -2*M_PI*y*Y/in->HeaderN.y
						 -2*M_PI*z*Z/in->HeaderN.z;
			mrcPixelDataGet(&inFFT, X, Y, Z, &mag,    mrcPixelMag,   mrcPixelHowNearest);
			mrcPixelDataGet(&inFFT, X, Y, Z, &phase,  mrcPixelPhase, mrcPixelHowNearest);
			mrcPixelDataGet(&refFFT, X, Y, Z, &rmag,   mrcPixelMag,   mrcPixelHowNearest);
			mrcPixelDataGet(&refFFT, X, Y, Z, &rphase, mrcPixelPhase, mrcPixelHowNearest);
			switch(info->mode&0x0000000f) {
				case 0: { /* Normal Correlation */
					eval += (SQR(mag*cos(phase+deltaPhase) - rmag*cos(rphase)) 
							+SQR(mag*sin(phase+deltaPhase) - rmag*sin(rphase)));
					sum  += SQR(rmag);
					break;
				}
				case 1: { /* Phase Correlation */
					dp = NORMAL_PHASE(phase+deltaPhase - rphase);
					dp = MIN(dp, 2*M_PI - dp);
					eval += rmag*dp;
					sum  += rmag; 
					break;
				}
				case 2: { /* Weighted Phase Correlation */
					dp = NORMAL_PHASE(phase+deltaPhase - rphase);
					dp = MIN(dp, 2*M_PI - dp);
					eval += rmag*SQR(dp);
					sum  += rmag; 
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d in lmrcImageCorrelation\n", info->mode);
					exit(EXIT_FAILURE);
					break;
				}
			}
		}
		}
		}
		switch(info->mode&0x0000000f) {
			case 0: { /* Normal Correlation */
				eval = sqrt(eval/sum); 
				break;
			}
			case 1: { /* Phase Correlation */
				eval =      eval/sum;
				break;
			}
			case 2: { /* Weighted Phase Correlation */
				eval = sqrt(eval/sum);
				break;
			}
		}
		DEBUGPRINT4("(%g %g %g): %g\n", x, y, z, eval);
		mrcPixelDataSet(out, ix, iy, iz, eval, mrcPixelRePart);
	}
	}
	}
	info->corInfo.mode = meanOfAll;
	lmrcImageInformation(&(info->corInfo), out);
	info->corInfo.minCoord.x = sx + info->corInfo.minCoord.x*dx;   
	info->corInfo.minCoord.y = sy + info->corInfo.minCoord.y*dy;   
	info->corInfo.minCoord.z = sz + info->corInfo.minCoord.z*dz;   

	shiftFFT = inFFT;
	mrcInit(&shiftFFT, NULL);

	x = info->corInfo.minCoord.x;
	y = info->corInfo.minCoord.y;
	z = info->corInfo.minCoord.z;
	DEBUGPRINT4("min (%g %g %g) %g", x, y, z, info->corInfo.min);
	for(X=0;                    X<=inFFT.HeaderN.x/2.0; X++) {
	for(Y=-inFFT.HeaderN.y/2.0; Y< inFFT.HeaderN.y/2.0; Y++) {
	for(Z=-inFFT.HeaderN.z/2.0; Z< inFFT.HeaderN.z/2.0; Z++) {
		deltaPhase = -2*M_PI*x*X/inFFT.HeaderN.x
					 -2*M_PI*y*Y/inFFT.HeaderN.y
					 -2*M_PI*z*Z/inFFT.HeaderN.z;
		mrcPixelDataGet(&inFFT,       X, Y, Z, &mag,    mrcPixelMag,   mrcPixelHowNearest);
		mrcPixelDataGet(&inFFT,       X, Y, Z, &phase,  mrcPixelPhase, mrcPixelHowNearest);
		mrcPixelDataSet(&shiftFFT, X, Y, Z, mag*cos(phase+deltaPhase),  mrcPixelRePart);
		mrcPixelDataSet(&shiftFFT, X, Y, Z, mag*sin(phase+deltaPhase),  mrcPixelImPart);
	}
	}
	}
	lmrcImageFFT(shift, &shiftFFT, 0);
	mrcImageFree(&shiftFFT, "in lmrcImageCorrelation");

	if(flagIn) {
		mrcImageFree(&inFFT, "in lmrcImageCorrelation");
	}
	if(flagRef) {
		mrcImageFree(&refFFT, "in lmrcImageCorrelation");
	}
}

double
lmrcImageLinearCorrelation(mrcImage* in1, mrcImage* in2, long mode)
{
	double r;

	lmrcImageLinearCorrelation2(&r, in1, in2, mode);
	return r;
}

void
lmrcImageLinearCorrelation2(double* r, mrcImage* in1, mrcImage* in2, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data1, data2;
	double sum1, sum2;
	double avg1, avg2;
	double xy, xx, yy;
	double count;
	//double r;

	sum1 = sum2 = count = 0.0;
	for(x=0; x<in1->HeaderN.x; x++) {
	for(y=0; y<in1->HeaderN.y; y++) {
	for(z=0; z<in1->HeaderN.z; z++) {
		//mrcPixelDataGet(in1, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
		data1 = in1->ImageFloatImage[(int)(x+0.5)+(int)(y+0.5)*in1->HeaderN.x+(int)(z+0.5)*in1->HeaderN.x*in1->HeaderN.y];
		sum1 += data1;
		//mrcPixelDataGet(in2, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
		data2 = in2->ImageFloatImage[(int)(x+0.5)+(int)(y+0.5)*in2->HeaderN.x+(int)(z+0.5)*in2->HeaderN.x*in2->HeaderN.y]; 
		sum2 += data2;
		count += 1;
	}
	}
	}

	avg1 = sum1/count;
	avg2 = sum2/count;

	xx = yy = xy = 0.0;
	for(x=0; x<in1->HeaderN.x; x++) {
	for(y=0; y<in1->HeaderN.y; y++) {
	for(z=0; z<in1->HeaderN.z; z++) {
		//mrcPixelDataGet(in1, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
		//mrcPixelDataGet(in2, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
		data1 = in1->ImageFloatImage[(int)(x+0.5)+(int)(y+0.5)*in1->HeaderN.x+(int)(z+0.5)*in1->HeaderN.x*in1->HeaderN.y];
		data2 = in2->ImageFloatImage[(int)(x+0.5)+(int)(y+0.5)*in2->HeaderN.x+(int)(z+0.5)*in2->HeaderN.x*in2->HeaderN.y];
		xx += SQR(data1-avg1);
		yy += SQR(data2-avg2);	
		xy += (data1-avg1)*(data2-avg2);
	}
	}
	}

	*r = xy/sqrt(xx)/sqrt(yy);

	//return r;
}

void
lmrcImageCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, long mode)
{
    mrcImage  inFFT;
    mrcImage refFFT;
    mrcImage outFFT;
	long     flagIn, flagRef;
	mrcImageParaTypeReal X, Y, Z;
	double mag, phase;

	flagIn = flagRef = 0;
    if(!(   in->HeaderN.x==ref->HeaderN.x
          &&in->HeaderN.y==ref->HeaderN.y
          &&in->HeaderN.z==ref->HeaderN.z)) {
        fprintf(stderr, "Different size between in(%d,%d,%d) and ref(%d,%d,%d)\n"
                        ,in->HeaderN.x, ref->HeaderN.x
                        ,in->HeaderN.y, ref->HeaderN.y
                        ,in->HeaderN.z, ref->HeaderN.z);
        exit(EXIT_FAILURE);
    }

    if(IsImage(in, "", 0)&&IsImage(ref, "", 0)) {
        lmrcImageFFT(&inFFT,  in, 0);
        lmrcImageFFT(&refFFT, ref, 0);
		flagIn = flagRef = 1;
    } else if(IsFT(in, "", 0)&&IsImage(ref, "", 0)) {
        inFFT = *in;
        lmrcImageFFT(&refFFT, ref, 0);
		flagRef = 1;
    } else if(IsImage(in, "", 0)&&IsFT(ref, "", 0)) {
        lmrcImageFFT(&inFFT,  in, 0);
        refFFT = *ref;
		flagIn = 1;
    } else if(IsFT(in, "", 0)&&IsFT(ref, "", 0)) {
        inFFT = *in;
        refFFT = *ref;
    } else {
        fprintf(stderr, "Nut supported Mode (in %d, ref %d)\n", in->HeaderMode, ref->HeaderMode);
        exit(EXIT_FAILURE);
    }
	switch(mode&0x0000000f) {
		case 0: { /* Normal Correlation */
    		lmrcFFTFGconj(&outFFT, &inFFT, &refFFT);
			break;
		}
		case 1: { /* Phase Correlation */
    		lmrcFFTFGconj(&outFFT, &inFFT, &refFFT);
			//Z = 0;
			for(Z=-outFFT.HeaderN.z/2.0; Z<outFFT.HeaderN.z/2.0; Z++) {
			for(Y=-outFFT.HeaderN.y/2.0; Y<outFFT.HeaderN.y/2.0; Y++) {
			for(X=0; X<=outFFT.HeaderN.x/2.0; X++) {
					mrcPixelDataSet(&outFFT, X, Y, Z, 1.0, mrcPixelMag);
			}
			}
			}
			break;
		}
		case 2: { /* Weighted Phase Correlation */
    		lmrcFFTFGconj(&outFFT, &inFFT, &refFFT);
			//Z = 0;
			for(Z=-outFFT.HeaderN.z/2.0; Z<outFFT.HeaderN.z/2.0; Z++) {
			for(Y=-outFFT.HeaderN.y/2.0; Y<outFFT.HeaderN.y/2.0; Y++) {
			for(X=0; X<=outFFT.HeaderN.x/2.0; X++) {
					mrcPixelDataGet(&outFFT, X, Y, Z, &mag, mrcPixelMag, mrcPixelHowNearest);
					mrcPixelDataSet(&outFFT, X, Y, Z, sqrt(mag), mrcPixelMag);
			}
			}
			}
			break;
		}
		case 3: { /* Normalized Correlation */
			double F, G;
			double W;

			mrcPixelDataGet(&inFFT,  0, 0, 0, &F, mrcPixelMag, mrcPixelHowNearest);
			mrcPixelDataGet(&refFFT, 0, 0, 0, &G, mrcPixelMag, mrcPixelHowNearest);
			W = F*G;
    		lmrcFFTFGconj(&outFFT, &inFFT, &refFFT);
			Z = 0;
			for(Z=-outFFT.HeaderN.z/2.0; Z<outFFT.HeaderN.z/2.0; Z++) {
			for(Y=-outFFT.HeaderN.y/2.0; Y<outFFT.HeaderN.y/2.0; Y++) {
			for(X=0; X<=outFFT.HeaderN.x/2.0; X++) {
					mrcPixelDataGet(&outFFT, X, Y, Z, &mag, mrcPixelMag, mrcPixelHowNearest);
					mrcPixelDataSet(&outFFT, X, Y, Z, mag/W, mrcPixelMag);
			}
			}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %ld in lmrcImageCorrelation\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	if(flagIn) {
		mrcImageFree(&inFFT, "in lmrcImageCorrelation");
	}
	if(flagRef) {
		mrcImageFree(&refFFT, "in lmrcImageCorrelation");
	}
	if(0 != (mode&0x00000010)) {
		mrcPixelDataSet(&outFFT, 0.0, 0.0, 0.0, 0.0, mrcPixelRePart);
		mrcPixelDataSet(&outFFT, 0.0, 0.0, 0.0, 0.0, mrcPixelImPart);
	}
    lmrcImageFFT(out, &outFFT, 0);
	mrcImageFree(&outFFT, "in lmrcImageCorrelation");
}

void
lmrcImageCorrelationModePrint(FILE* fpt)
{
	fprintf(fpt, "0: Normal Correlation FxG*\n");
	fprintf(fpt, "1: Phase  Correlation FxG*/     |FxG*|\n");
	fprintf(fpt, "2: Phase  Correlation FxG*/sqrt(|FxG*|)\n");
	fprintf(fpt, "3: Normalized Normal Correlation FxG*/|F||G|)\n");
	fprintf(fpt, "16: (0,0) = 0 \n");
	fprintf(fpt, "Refinement Correlation Map\n");
	fprintf(fpt, "0: sqrt(Sum |Fi-Gi|^2                 / Sum |Gi|^2)\n");
	fprintf(fpt, "1:      Sum |Gi||phaseFi - phaseGi|   / Sum |Gi|  \n");
	fprintf(fpt, "2: sqrt(Sum |Gi||phaseFi - phaseGi|^2 / Sum |Gi|  )\n");
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
	mrcImage fit;
	mrcImage cor;
    int i, inext;
    int i1, i2, i3;
    mrcImageParaTypeReal x, y;
    char s[5];
    double correlationMax=-1e30;
    double correlationMaxRot1=0;
    double correlationMaxRot2=0;
    double correlationMaxRot3=0;
    double correlation2Max=-1e30;
    double correlation2MaxRot1=0;
    double correlation2MaxRot2=0;
    double correlation2MaxRot3=0;
    double correlation;
    int flagMap;
	int flagFree;
	char* tmpImageFit;
	char* tmpImageCor;
	int i1startFirst=0;
	int i2startFirst=0;
	int i3startFirst=0;
	int i1start=0;
	int i2start=0;
	int i3start=0;
	int whileCount=0;
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

    DEBUGPRINT4("nRot1Area:  %f %f %f skip: %d\n", info->nRot1AreaMin*DEGREE, info->nRot1AreaMax*DEGREE, info->nRot1AreaStep*DEGREE, info->nRot1Step);
    DEBUGPRINT4("nRot2Area:  %f %f %f skip: %d\n", info->nRot2AreaMin*DEGREE, info->nRot2AreaMax*DEGREE, info->nRot2AreaStep*DEGREE, info->nRot2Step);
    DEBUGPRINT4("nRot3Area:  %f %f %f skip: %d\n", info->nRot3AreaMin*DEGREE, info->nRot3AreaMax*DEGREE, info->nRot3AreaStep*DEGREE, info->nRot3Step);
    s[4] = '\0';

    if(ref->HeaderN.z < info->nRot1*info->nRot2*info->nRot3-1) {
	    flagMap = 1;
    } else {
	    flagMap = 0;	
    }
	info->fittedMap.Image= NULL;
	info->cor.Image = NULL;
	info->fittedMap2.Image = NULL;
	info->cor2.Image = NULL;
	whileCount=0;
    i = -1;
    while(1) {
		i1start = MAX(0,(int)((info->nRot1AreaMin-info->nRot1Start)/info->nRot1Delta + 0.5));
		i2start = MAX(0,(int)((info->nRot2AreaMin-info->nRot2Start)/info->nRot2Delta + 0.5));
		i3start = MAX(0,(int)((info->nRot3AreaMin-info->nRot3Start)/info->nRot3Delta + 0.5));
        DEBUGPRINT4("nRotAreaMin:  %f %f %f while %d\n", info->nRot1AreaMin*DEGREE, info->nRot2AreaMin*DEGREE, info->nRot3AreaMin*DEGREE, whileCount); 
        DEBUGPRINT4("nRotDelta:  %f %f %f while %d\n",   info->nRot1Delta*DEGREE,   info->nRot2Delta*DEGREE,   info->nRot3Delta*DEGREE,   whileCount); 
        DEBUGPRINT4("nRotStart:  %f %f %f while %d\n",   info->nRot1Start*DEGREE,   info->nRot2Start*DEGREE,   info->nRot3Start*DEGREE,   whileCount); 
        DEBUGPRINT4("StartI:  %d %d %d while %d\n", i1start, i2start, i3start, whileCount); 
        DEBUGPRINT4("nRot1:  %d %d %d while %d\n", info->nRot1, info->nRot2, info->nRot3, whileCount); 
        for(i1=i1start; i1<info->nRot1; i1+=info->nRot1Step) {
        for(i2=i2start; i2<info->nRot2; i2+=info->nRot2Step) {
        for(i3=i3start; i3<info->nRot3; i3+=info->nRot3Step) {
            if(flagMap==0) {	
				switch(info->StackOrder) {
					case lmrcImageAutoRotationCorrelationForManyReferencesStackOrderRot1Rot2Rot3: {
            			i = i1 + i2*info->nRot1 + i3*info->nRot1*info->nRot2;
						break;
					}
					case lmrcImageAutoRotationCorrelationForManyReferencesStackOrderRot3Rot2Rot1: {
            			i = i3 + i2*info->nRot3 + i1*info->nRot2*info->nRot3;
						break;
					}
				}
	   			fprintf(stdout, "i1 %d i2 %d i3 %d total %d\n", i1, i2, i3, i ); fflush(stdout); 
	    	} else {
				i++;
				if(ref->HeaderN.z<=i) break;
	   			fprintf(stdout, "%d\n", i ); 
	    	}
            if( !(((info->nRot1AreaMin<=ref->Tailer[i].Cont.Rot1        && ref->Tailer[i].Cont.Rot1       <=info->nRot1AreaMax)
                 ||(info->nRot1AreaMin<=ref->Tailer[i].Cont.Rot1+2*M_PI && ref->Tailer[i].Cont.Rot1+2*M_PI<=info->nRot1AreaMax)
                 ||(info->nRot1AreaMin<=ref->Tailer[i].Cont.Rot1-2*M_PI && ref->Tailer[i].Cont.Rot1-2*M_PI<=info->nRot1AreaMax))
                &&((info->nRot2AreaMin<=ref->Tailer[i].Cont.Rot2        && ref->Tailer[i].Cont.Rot2       <=info->nRot2AreaMax)
                 ||(info->nRot2AreaMin<=ref->Tailer[i].Cont.Rot2+2*M_PI && ref->Tailer[i].Cont.Rot2+2*M_PI<=info->nRot2AreaMax)
                 ||(info->nRot2AreaMin<=ref->Tailer[i].Cont.Rot2-2*M_PI && ref->Tailer[i].Cont.Rot2-2*M_PI<=info->nRot2AreaMax))
                &&((info->nRot3AreaMin<=ref->Tailer[i].Cont.Rot3        && ref->Tailer[i].Cont.Rot3       <=info->nRot3AreaMax) 
                 ||(info->nRot3AreaMin<=ref->Tailer[i].Cont.Rot3+2*M_PI && ref->Tailer[i].Cont.Rot3+2*M_PI<=info->nRot3AreaMax) 
                 ||(info->nRot3AreaMin<=ref->Tailer[i].Cont.Rot3-2*M_PI && ref->Tailer[i].Cont.Rot3-2*M_PI<=info->nRot3AreaMax))) ){
                DEBUGPRINT3("Exclusion Area: Rot %f %f %f \n",  ref->Tailer[i].Cont.Rot1*DEGREE,
                                                                ref->Tailer[i].Cont.Rot2*DEGREE,
                                                                ref->Tailer[i].Cont.Rot3*DEGREE);
            } else {
                DEBUGPRINT3("Calculation Area: Rot %f %f %f \n", ref->Tailer[i].Cont.Rot1*DEGREE,
                                                                 ref->Tailer[i].Cont.Rot2*DEGREE,
                                                                 ref->Tailer[i].Cont.Rot3*DEGREE);
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
				fit = proj;
				cor = proj;

				mrcInit(&fit, NULL);
				mrcInit(&cor, NULL);

                lmrcImageAutoRotationCorrelation(&fit, &cor, in, &proj, linfo, info->mode);
				DEBUGPRINT4("correlation %f angle %f at %f %f\n", linfo->max, linfo->maxTheta, linfo->maxP.x, linfo->maxP.y);

                correlation = linfo->LinearCorrelation;
                mrcPixelDataSet(&out, 0, 0, i, linfo->max,      mrcPixelRePart);
                mrcPixelDataSet(&out, 1, 0, i, linfo->maxTheta, mrcPixelRePart);
                mrcPixelDataSet(&out, 2, 0, i, linfo->maxP.x,   mrcPixelRePart);
                
                mrcPixelDataSet(&out, 4, 0, i, x, mrcPixelRePart);
                mrcPixelDataSet(&out, 5, 0, i, y, mrcPixelRePart);
                mrcPixelDataSet(&out, 6, 0, i, correlation, mrcPixelRePart);

                fprintf(info->fptOutASC, "%d: ", i);
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
				tmpImageFit = info->fittedMap.Image;
				tmpImageCor = info->cor.Image;
				flagFree=1;
                if(correlationMax<correlation) {
                    correlationMax     = correlation;
                    correlationMaxRot1 = ref->Tailer[i].Cont.Rot1;
                    correlationMaxRot2 = ref->Tailer[i].Cont.Rot2;
                    correlationMaxRot3 = ref->Tailer[i].Cont.Rot3;
					if(NULL!=info->fittedMap.Image
					&& NULL!= info->cor.Image
					&& info->fittedMap.Image != info->fittedMap2.Image 
					&& info->cor.Image       != info->cor2.Image ) {
						DEBUGPRINT6("Free1 %p %p %p %p %p %p\n", \
								info->fittedMap.Image, info->cor.Image,  info->fittedMap2.Image, info->cor2.Image, tmpImageFit, tmpImageCor)
						mrcImageFree(&info->fittedMap, "");
						mrcImageFree(&info->cor, "");
					}
					info->fittedMap = fit;
					info->cor = cor;
					flagFree=0;
                } 
                if(correlation2Max<linfo->max) {
                    correlation2Max     = linfo->max;
                    correlation2MaxRot1 = ref->Tailer[i].Cont.Rot1;
                    correlation2MaxRot2 = ref->Tailer[i].Cont.Rot2;
                    correlation2MaxRot3 = ref->Tailer[i].Cont.Rot3;
					if(NULL!=info->fittedMap2.Image 
					&& NULL!= info->cor2.Image
					&& info->fittedMap2.Image != tmpImageFit 
					&& info->cor2.Image       != tmpImageCor) {
						DEBUGPRINT6("Free2 %p %p %p %p %p %p\n", \
								info->fittedMap.Image, info->cor.Image,  info->fittedMap2.Image, info->cor2.Image, tmpImageFit, tmpImageCor)
						mrcImageFree(&info->fittedMap2, "");
						mrcImageFree(&info->cor2, "");
					}
					info->fittedMap2 = fit;
					info->cor2 = cor;
					flagFree=0;
                } 
                if(flagFree) {
					mrcImageFree(&fit, "");
					mrcImageFree(&cor, "");
				}
            }

        }
        }
        }
        if(1<info->nRot1Step
         ||1<info->nRot2Step
         ||1<info->nRot3Step) {
			switch(info->RefinementMode) {
				case lmrcImageAutoRotationCorrelationForManyReferencesRefinementModeLinear: { 
			        DEBUGPRINT3("MAX Point: Rot %f %f %f\n", correlationMaxRot1*DEGREE, correlationMaxRot2*DEGREE, correlationMaxRot3*DEGREE);
			        info->nRot1AreaMin = correlationMaxRot1-info->nRot1AreaStep;
			        info->nRot1AreaMax = correlationMaxRot1+info->nRot1AreaStep;
			        info->nRot2AreaMin = correlationMaxRot2-info->nRot2AreaStep;
			        info->nRot2AreaMax = correlationMaxRot2+info->nRot2AreaStep;
			        info->nRot3AreaMin = correlationMaxRot3-info->nRot3AreaStep;
			        info->nRot3AreaMax = correlationMaxRot3+info->nRot3AreaStep;
					break;
				}
				case lmrcImageAutoRotationCorrelationForManyReferencesRefinementModeSetMode: { 
			        DEBUGPRINT3("MAX Point: Rot %f %f %f\n", correlationMaxRot1*DEGREE, correlationMaxRot2*DEGREE, correlationMaxRot3*DEGREE);
			        info->nRot1AreaMin = correlation2MaxRot1-info->nRot1AreaStep;
			        info->nRot1AreaMax = correlation2MaxRot1+info->nRot1AreaStep;
			        info->nRot2AreaMin = correlation2MaxRot2-info->nRot2AreaStep;
			        info->nRot2AreaMax = correlation2MaxRot2+info->nRot2AreaStep;
			        info->nRot3AreaMin = correlation2MaxRot3-info->nRot3AreaStep;
			        info->nRot3AreaMax = correlation2MaxRot3+info->nRot3AreaStep;

					break;
				}
			}
			info->nRot1Step = MAX(1,info->nRot1Step/5);
			info->nRot2Step = MAX(1,info->nRot2Step/5);
			info->nRot3Step = MAX(1,info->nRot3Step/5);
			info->nRot1AreaStep = info->nRot1Step*info->nRot1Delta;
			info->nRot2AreaStep = info->nRot2Step*info->nRot2Delta;
			info->nRot3AreaStep = info->nRot3Step*info->nRot3Delta;
			DEBUGPRINT3("nRot1Area:  %f %f %f\n", info->nRot1AreaMin*DEGREE, info->nRot1AreaMax*DEGREE, info->nRot1AreaStep*DEGREE);
			DEBUGPRINT3("nRot2Area:  %f %f %f\n", info->nRot2AreaMin*DEGREE, info->nRot2AreaMax*DEGREE, info->nRot2AreaStep*DEGREE);
			DEBUGPRINT3("nRot3Area:  %f %f %f\n", info->nRot3AreaMin*DEGREE, info->nRot3AreaMax*DEGREE, info->nRot3AreaStep*DEGREE);

        } else {
            break;
        }
		whileCount++;
    }
    info->out = out;
}


