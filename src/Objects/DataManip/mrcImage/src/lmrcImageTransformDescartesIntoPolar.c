/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageTransformDescartesIntoPolar ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageTransformDescartesIntoPolar 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSymmetryFind ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#define DEBUG
#undef  DEBUG2
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "./lmrcImageCentre.h"
#include "./lDescartesIntoPolar.h"
#include "./lmrcImageTransformDescartesIntoPolar.h"

void 
lmrcImageDeterminationOfPolarAxisByAssumingNfold(mrcImageParaTypeRealCoord* centre, mrcImage* residue, mrcImage* in, lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo linfo, int mode)
{
	mrcImage fft;
	double Z;
	double X1, Y1;
	double X2, Y2;
	double R, PHI, iRot, jRot;
	double x, y, z;
	double ix, iy, iz;
	double phase1, phase2, sumphase, diff, sumdiff;
	double mag1, mag2;
	double ncount, ndiff;
	double weight;
	mrcImageInformation info;
    lmrcImageCenterOfMass centerOfMass;

	lmrcImageFFT(&fft, in, 0);
	lmrcImageCenterOfMassCalculate(&centerOfMass, *in);	
	DEBUGPRINT3("GC in lmrcImageDeterminationOfPolarAxisByAssumingNfold : %g %g %g\n", centerOfMass.x, centerOfMass.y, centerOfMass.z);
	DEBUGPRINT1("Rotational Symmetry: %d\n", linfo.nFold);
	residue->HeaderMode = mrcFloatImage;
	residue->HeaderN.x  = (int)((linfo.maxx - linfo.minx)/linfo.delx + 1); 
	residue->HeaderN.y  = (int)((linfo.maxy - linfo.miny)/linfo.dely + 1); 
	residue->HeaderN.z  = (int)((linfo.maxz - linfo.minz)/linfo.delz + 1); 
	residue->HeaderLength.x = linfo.delx;	
	residue->HeaderLength.y = linfo.dely;	
	residue->HeaderLength.z = linfo.delz;	
	mrcInit(residue, NULL);

	for(x=linfo.minx, ix=0; ix<residue->HeaderN.x; ix++, x+=linfo.delx) {
	for(y=linfo.miny, iy=0; iy<residue->HeaderN.y; iy++, y+=linfo.dely) {
	for(z=linfo.minz, iz=0; iz<residue->HeaderN.z; iz++, z+=linfo.delz) {
		sumphase = 0.0;
		ncount   = 0;
		for(Z=0; Z< fft.HeaderN.z/2.0; Z++) {		
		for(R=0; R<=fft.HeaderN.x/2.0; R++) {		
			for(PHI=0; PHI<2*M_PI/linfo.nFold; PHI+=linfo.delPHI) {
				sumdiff  = 0;	
				ndiff    = 0;
				for(iRot=0;      iRot<linfo.nFold; iRot++) {
				for(jRot=iRot+1; jRot<linfo.nFold; jRot++) {
					X1 = R*cos(PHI*iRot);
					Y1 = R*sin(PHI*iRot);
					X2 = R*cos(PHI*jRot);
					Y2 = R*sin(PHI*jRot);
					mrcPixelDataGet(&fft, X1, Y1, Z, &phase1, mrcPixelPhase, mrcPixelHowNearest); 					
					mrcPixelDataGet(&fft, X1, Y1, Z, &mag1,   mrcPixelMag,   mrcPixelHowNearest); 					
					mrcPixelDataGet(&fft, X2, Y2, Z, &phase2, mrcPixelPhase, mrcPixelHowNearest); 					
					mrcPixelDataGet(&fft, X2, Y2, Z, &mag2,   mrcPixelMag,   mrcPixelHowNearest); 					
					diff = NORMAL_PHASE(phase1 - 2*M_PI*(centerOfMass.x + x)*X1/fft.HeaderN.x
					                           - 2*M_PI*(centerOfMass.y + y)*Y1/fft.HeaderN.y
							                   - 2*M_PI*(centerOfMass.z + z)*Z /fft.HeaderN.z
							) 
					     - NORMAL_PHASE(phase2 - 2*M_PI*(centerOfMass.x + x)*X2/fft.HeaderN.x
			                                   - 2*M_PI*(centerOfMass.y + y)*Y2/fft.HeaderN.y
							                   - 2*M_PI*(centerOfMass.z + z)*Z /fft.HeaderN.z
						    );
					weight = (mag1+mag2)/2.0;
					sumdiff += fabs(MIN_NORMAL_PHASE(diff))*weight;
					ndiff   += weight;
				}
				}
				sumphase += sumdiff;
				ncount   += ndiff;
			}
		}
		}
		sumphase /= ncount;
#ifdef DEBUG2
		DEBUGPRINT5("res %g weight %g at %g %g %g\n", sumphase, ncount, x, y, z);
#endif
		mrcPixelDataSet(residue, ix, iy, iz, sumphase, mrcPixelRePart);
	}
	}
	}

	info.mode = meanOfAll;
	lmrcImageInformation(&info, residue);	
	
	centre->x = info.minCoord.x*linfo.delx + linfo.minx + centerOfMass.x;
	centre->y = info.minCoord.y*linfo.dely + linfo.miny + centerOfMass.y;
	centre->z = info.minCoord.z*linfo.delz + linfo.minz + centerOfMass.z; 
}

/* 
	mode: No use at present, for the future 
*/
void
lmrcImageTransformDescartesIntoPolar(
	mrcImage* out,
	mrcImage* in,
	lmrcImageTransformDescartesIntoPolarInfo* linfo,
	lDescartesIntoPolarInfo* linfo2,
	long mode)
{
    double x, y, z;
    double r,theta, phi;
    double data, data1;
    double radian;
	double rr;
    lmrcImageCenterOfMass centerOfMass;
	PolarCoord     pp;
	DescartesCoord dp;

	if(linfo->flagRotationalSymmetry) {
		mrcImage residue;
		mrcImageParaTypeRealCoord centre;
		lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo info;

		info       = linfo->axisInfo;	
		info.nFold = linfo->nRotationalSymmetry;
		lmrcImageDeterminationOfPolarAxisByAssumingNfold(&centre, &residue, in, info, 0);
		linfo2->centre.x = centre.x;	
		linfo2->centre.y = centre.y;	
		linfo2->centre.z = centre.z;	
	} else if(linfo->flagImageCentreIsGravityCentre) { /* Centre is centre of gravity. */
    	lmrcImageCenterOfMassCalculate(&centerOfMass, *in);
    	linfo2->centre.x = centerOfMass.x;
    	linfo2->centre.y = centerOfMass.y;
    	linfo2->centre.z = centerOfMass.z;
    	DEBUGPRINT3("gccenter=(%f,%f,%f)\n", centerOfMass.x, centerOfMass.y, centerOfMass.z);
	} else if(linfo->flagCentre) {
		linfo2->centre.x = linfo->Centre.x;
		linfo2->centre.y = linfo->Centre.y;
		linfo2->centre.z = linfo->Centre.z;
	} else {
		fprintf(stderr, "Centre was not defined. So the image centre will be defined as the centre\n");
		linfo2->centre.x = in->HeaderN.x/2.0;
		linfo2->centre.y = in->HeaderN.y/2.0;
		linfo2->centre.z = in->HeaderN.z/2.0;
	}
	if(!linfo->flagDescartesIntoPolarInfo) {
		linfo2->xaxis.x = 1;
		linfo2->xaxis.y = 0;
		linfo2->xaxis.z = 0;
		linfo2->zaxis.x = 0;
		linfo2->zaxis.y = 0;
		linfo2->zaxis.z = 1;
	}
	lDescartesAxisCalc(linfo2, 0);

    out->Header = in->Header;
	if(1==in->HeaderN.z) { /* Two dimensional */
		out->HeaderN.x = 2.0*M_PI/linfo->dphi;
		out->HeaderN.y = MIN((in->HeaderN.x-1)*in->HeaderLength.x/2.0, 
		                     (in->HeaderN.y-1)*in->HeaderLength.y/2.0)/linfo->dr + 1;
		out->HeaderN.z = 1;
		out->HeaderLength.x = linfo->dphi*DEGREE;
		out->HeaderLength.y = linfo->dr;
		out->HeaderLength.z = linfo->dr;
		out->HeaderStartN.x = 0;
		out->HeaderStartN.y = 0;
		out->HeaderStartN.z = 0;
	} else if(1<in->HeaderN.z) { /* Three dimensional */ 
		out->HeaderN.x = 2.0*M_PI/linfo->dphi;  
		out->HeaderN.y = M_PI/linfo->dtheta;  
		out->HeaderN.z = MIN((in->HeaderN.x-1)*in->HeaderLength.x/2.0, 
						 MIN((in->HeaderN.y-1)*in->HeaderLength.y/2.0,
						     (in->HeaderN.z-1)*in->HeaderLength.z/2.0))/linfo->dr + 1;
		out->HeaderLength.x = linfo->dphi*DEGREE;
		out->HeaderLength.y = linfo->dtheta*DEGREE;
		out->HeaderLength.z = linfo->dr;
		out->HeaderStartN.x = 0;
		out->HeaderStartN.y = 0;
		out->HeaderStartN.z = 0;
	} else {
		fprintf(stderr, "Dimmension of z is Wrong: %d\n", in->HeaderN.z);
	}
    mrcInit(out,NULL);
	
	if(1==in->HeaderN.z) { /* Two dimensional */
		for(r=0;     r<out->HeaderN.y; r++)   {
		for(phi=0; phi<out->HeaderN.x; phi++) {
			radian = phi*linfo->dphi;
			rr     = r*linfo->dr;
			x = linfo2->centre.x + rr*cos(radian)/in->HeaderLength.x - in->HeaderStartN.x;
			y = linfo2->centre.y + rr*sin(radian)/in->HeaderLength.y - in->HeaderStartN.y;
			z = 0;
        	mrcPixelDataGet(in, x, y, z,&data, mrcPixelRePart, mrcPixelHowLinear);
			if(linfo->flagrWeight) {
				data1 = data*rr;
			} else {
				data1 = data;
			}
        	mrcPixelDataSet(out, phi, r, 0, data1, mrcPixelRePart);
		}
		}
	} else if(1<in->HeaderN.z) { /* Three dimensional */ 
		for(r=0;         r<out->HeaderN.z; r++)   {
		for(phi=0;     phi<out->HeaderN.x; phi++) {
		for(theta=0; theta<out->HeaderN.y; theta++) {
			pp.r     = r    *linfo->dr; 
			pp.phi   = phi  *linfo->dphi;
			pp.theta = theta*linfo->dtheta;  
			dp = lPolarCoordIntoDescartesCoord(pp, *linfo2, 0);
			x = dp.x/in->HeaderLength.x - in->HeaderStartN.x;
			y = dp.y/in->HeaderLength.y - in->HeaderStartN.y;
			z = dp.z/in->HeaderLength.z - in->HeaderStartN.z;
        	mrcPixelDataGet(in,    x, y, z,&data, mrcPixelRePart, mrcPixelHowLinear);
			if(linfo->flagrWeight) {
				data1 = data*pp.r;
			} else {
				data1 = data;
			}
        	mrcPixelDataSet(out, phi, out->HeaderN.y - 1 - theta, r, data1, mrcPixelRePart);
		}
		}
		}
	} else {
		fprintf(stderr, "Dimmension of z is Wrong: %d\n", in->HeaderN.z);
	}

    mrcStatDataSet(out,0);
}

