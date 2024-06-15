/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFourierNeighborCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFourierNeighborCorrelation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageFourierNeighborCorrelation ver%I%; Date:%D% %Z%";

#undef DEBUG
#undef DEBUG2
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageMultiplying.h"
#include "./lmrcImageNoiseCreate.h"
#include "./lmrcImageFourierNeighborCorrelation.h"

void
lmrcImageFourierNeighborCorrelation(lmrcImageFourierNeighborCorrelationResult* res,
	mrcImage* in,
	lmrcImageFourierNeighborCorrelationInfo linfo, int mode)
{
	int    iR;
	double RR;
	float X, Y, Z;
	double XX, YY, ZZ;
	int nX, nY, nZ;
	double delX, delY, delZ;	
	mrcImage f;
	mrcImageParaTypeRealCoord shift;
	mrcImage s;
	int idelta;
	double rdata1, rdata2, idata1, idata2;
	double* sumFpFp;
	double* sumFhFh;
	double* sumFpFh;
	double FpFp;
	double max;
	double minW;

	delX = 1.0/(in->HeaderN.x*in->HeaderLength.x);	
	delY = 1.0/(in->HeaderN.y*in->HeaderLength.y);	
	delZ = 1.0/(in->HeaderN.z*in->HeaderLength.z);	

	if(IsImage(in, "in lmrcImageFourierNeighborCorrelation", 0)) {
		switch(linfo.flagCentre) {
			case lmrcImageFourierNeighborCorrelationCentreModeCentre: {
				shift.x = -(in->HeaderN.x-1)/2.0;
				shift.y = -(in->HeaderN.y-1)/2.0;
				shift.z = -(in->HeaderN.z-1)/2.0;
				break;
			}
			case lmrcImageFourierNeighborCorrelationCentreModeBottomLeft: {
				shift.x = 0;
				shift.y = 0;
				shift.z = 0;
				break;
			}
			case lmrcImageFourierNeighborCorrelationCentreModeUseStartN: {
				shift.x = in->HeaderStartN.x;
				shift.y = in->HeaderStartN.y;
				shift.z = in->HeaderStartN.z;
				break;
			}
			default: {
				fprintf(stderr, "Not supported CentreMode: %d \n", linfo.flagCentre);
				fprintf(stderr, "Use Centre\n");
				break;
			}
		}
		lmrcImageShift(&s, in, shift, linfo.shiftMode);
		lmrcImageFFT(&f, &s, 0);
	} else {
		fprintf(stderr, "Not supported: Use Image\n");
		exit(EXIT_FAILURE);
	}

	max = sqrt(SQR(1.0/(2*in->HeaderLength.x)) + SQR(1.0/(2*in->HeaderLength.y)) + SQR(1.0/(2*in->HeaderLength.z)));  
	res->nR = (int)(max/linfo.delta) + 1;
	DEBUGPRINT2("max: %f nR %d \n", max, res->nR);
	res->data = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
	res->R    = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
	res->N    = (int*)   memoryAllocate(sizeof(int)   *res->nR, "in FNC");
	sumFpFp   = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
	sumFhFh   = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
	sumFpFh   = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");

	for(iR=0; iR<res->nR; iR++) {
		sumFpFp[iR] = sumFhFh[iR] = sumFpFh[iR] = 0;
	}
	for(Z=-in->HeaderN.z/2.0+1; Z< in->HeaderN.z/2.0; Z++) { 
		ZZ = Z*delZ;
	for(Y=-in->HeaderN.y/2.0+1; Y< in->HeaderN.y/2.0; Y++) { 
		YY = Y*delY;
	for(X=-in->HeaderN.x/2.0+1; X< in->HeaderN.x/2.0; X++) {
		XX = X*delX;
		RR = SQR(XX) + SQR(YY) + SQR(ZZ);
		if(0<RR) {
			RR = sqrt(RR);
			iR = (int)(RR/linfo.delta + 0.5);
			if(res->nR <= iR) {
				DEBUGPRINT2("Something Wrong: RR %f iR %d\n", RR, iR);
				iR = res->nR-1;
			}
		} else {
			RR = 0;
			iR = 0;
		}
		res->N[iR]++;
		mrcPixelDataGet(&f, X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&f, X, Y, Z, &idata1, mrcPixelImPart, mrcPixelHowNearest);
		FpFp = (SQR(rdata1) + SQR(idata1));

		//
		if(1<in->HeaderN.x) {
			//
			mrcPixelDataGet(&f, X-1, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&f, X-1, Y, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
			sumFpFp[iR] += FpFp;
			sumFhFh[iR] += (SQR(rdata2) + SQR(idata2));
			sumFpFh[iR] += (rdata1*rdata2 + idata1*idata2);
#ifdef DEBUG2
			if(10<=X && X<11) {
			DEBUGPRINT5("FpFh %f %f %f %f %f \n", (rdata1*rdata2 + idata1*idata2), rdata1, rdata2, idata1, idata2);
			}
#endif
			//
			mrcPixelDataGet(&f, X+1, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&f, X+1, Y, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
			sumFpFp[iR] += FpFp;
			sumFhFh[iR] += (SQR(rdata2) + SQR(idata2));
			sumFpFh[iR] += (rdata1*rdata2 + idata1*idata2);
		}
		if(1<in->HeaderN.y) {
			//
			mrcPixelDataGet(&f, X, Y-1, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&f, X, Y-1, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
			sumFpFp[iR] += FpFp;
			sumFhFh[iR] += (SQR(rdata2) + SQR(idata2));
			sumFpFh[iR] += (rdata1*rdata2 + idata1*idata2);
			//
			mrcPixelDataGet(&f, X, Y+1, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&f, X, Y+1, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
			sumFpFp[iR] += FpFp;
			sumFhFh[iR] += (SQR(rdata2) + SQR(idata2));
			sumFpFh[iR] += (rdata1*rdata2 + idata1*idata2);
		}
		if(1<in->HeaderN.z) {
			//
			mrcPixelDataGet(&f, X, Y, Z-1, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&f, X, Y, Z-1, &idata2, mrcPixelImPart, mrcPixelHowNearest);
			sumFpFp[iR] += FpFp;
			sumFhFh[iR] += (SQR(rdata2) + SQR(idata2));
			sumFpFh[iR] += (rdata1*rdata2 + idata1*idata2);
			//
			mrcPixelDataGet(&f, X, Y, Z+1, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&f, X, Y, Z+1, &idata2, mrcPixelImPart, mrcPixelHowNearest);
			sumFpFp[iR] += FpFp;
			sumFhFh[iR] += (SQR(rdata2) + SQR(idata2));
			sumFpFh[iR] += (rdata1*rdata2 + idata1*idata2);
		}
	}
	}
	}

	for(iR=0; iR<res->nR; iR++) {
		res->R[iR]    = iR*linfo.delta; 	
		if(0<sumFpFp[iR]*sumFhFh[iR]) {
			res->data[iR] = sumFpFh[iR]/sqrt(sumFpFp[iR]*sumFhFh[iR]);
		} else {
			res->data[iR] = 0.0;
		}
#ifdef DEBUG2
		DEBUGPRINT5("R %f FNC %f FpFh %f FpFp %f FhFh %f\n", res->R[iR], res->data[iR], sumFpFh[iR], sumFpFp[iR], sumFhFh[iR]);
#endif
	}

	if(linfo.flagPredictedFSC) {
		mrcImage obj;
		mrcImage back;
		int N;
		lmrcImageFourierNeighborCorrelationInfo   linfoObj = linfo;
		lmrcImageFourierNeighborCorrelationResult resObj  = *res;
		lmrcImageFourierNeighborCorrelationInfo   linfoBack = linfo;
		lmrcImageFourierNeighborCorrelationResult resBack = *res;;
		linfoObj.flagPredictedFSC = linfoBack.flagPredictedFSC = 0;	

		// FNCN and FNCF
		DEBUGPRINT("Start FNCF\n");
		lmrcImageNoiseCreate(&obj, in, 1.0, 0);
		for(Z=0; Z< in->HeaderN.z; Z++) { 
		for(Y=0; Y< in->HeaderN.y; Y++) { 
		for(X=0; X< in->HeaderN.x; X++) {
			mrcPixelDataGet(&obj,          X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&(linfo.objMask), X, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			if(rdata2<0.5) {
				mrcPixelDataSet(&obj, X, Y, Z, 0.0, mrcPixelRePart);
			}
		}
		}
		}
		lmrcImageFourierNeighborCorrelation(&resObj, &obj, linfoObj, mode); 

		DEBUGPRINT("Start FNCN\n");
		lmrcImageNoiseCreate(&back, in, 1.0, 0);
		DEBUGPRINT("NOISE\n");
		for(Z=0; Z< in->HeaderN.z; Z++) { 
		for(Y=0; Y< in->HeaderN.y; Y++) { 
		for(X=0; X< in->HeaderN.x; X++) {
			mrcPixelDataGet(&back,             X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&(linfo.backMask), X, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
			if(rdata2<0.5) {
				mrcPixelDataSet(&back, X, Y, Z, 0.0, mrcPixelRePart);
			}
		}
		}
		}
		DEBUGPRINT("CALC\n");
		lmrcImageFourierNeighborCorrelation(&resBack, &back, linfoBack, mode); 

		DEBUGPRINT("Averaged FNCF/FNCN Start\n");
		res->FNCN=0;
		res->FNCF=0;
		N = 0;	
		for(iR=0; iR<res->nR; iR++) {
			res->FNCF += resObj.data[iR] *resObj.N[iR];
			res->FNCN += resBack.data[iR]*resBack.N[iR];
			N+=resObj.N[iR];
		}
		res->FNCF /= N;
		res->FNCN /= N;
		fprintf(stdout, "FNCF %f FNCN %f\n", res->FNCF, res->FNCN);
		res->FNCFs = resObj.data;
		res->FNCNs = resBack.data;

		//
		res->SNR  = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
		res->FSC  = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");

		if(res->flagFSCfull) {
			res->FSCfull  = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
		}
		if(res->flagCref || res->flagNoiseWeighted) {
			res->Cref = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
		}
		if(res->flagNoiseWeighted) {
			res->NoiseWeighted = (double*)memoryAllocate(sizeof(double)*res->nR, "in FNC");
		}

		// approximated SNR
		// predicted FSC
		minW = 1;
		for(iR=0; iR<res->nR; iR++) {
			res->SNR[iR] = (res->FNCN - res->data[iR])
			              /(res->data[iR] - res->FNCF);
			res->FSC[iR] = (res->data[iR] - res->FNCN)
			              /(2*res->FNCF - res->FNCN - res->data[iR]);
	
			if(res->flagFSCfull) {
				res->FSCfull[iR] = 2*res->FSC[iR]/(1+res->FSC[iR]);
			}
			if(res->flagCref || res->flagNoiseWeighted) {
				if(res->FSC[iR]<=0) {
					res->Cref[iR] = 0;
				} else {
					res->Cref[iR] = sqrt(2*res->FSC[iR]/(1 + res->FSC[iR]));
				}
			}
			if(res->flagNoiseWeighted) {
				if(res->Cref[iR]<=0) {
					minW = 0;
				}
				res->NoiseWeighted[iR] = minW*res->Cref[iR]*exp(-res->Brestore/4.0*SQR(res->R[iR]));
			}
		}
	}

	mrcImageFree(&f, "in main");
	mrcImageFree(&s, "in main");

	memoryFree(sumFpFh);
	memoryFree(sumFpFp);
	memoryFree(sumFhFh);
}

void
lmrcImageFourierNeighborCorrelationPrint(FILE* fpt, lmrcImageFourierNeighborCorrelationResult* res,
	lmrcImageFourierNeighborCorrelationInfo linfo, int mode)
{
	int R;

	for(R=0; R<res->nR; R++) {
		fprintf(fpt, "%10.6f % 10.6f % 10d ", res->R[R], res->data[R], res->N[R]);
		if(linfo.flagPredictedFSC) {
			fprintf(fpt, "FSC %10.6f SNR % 10.6e FNCF % 10.6f FNCN % 10.6f ", res->FSC[R], res->SNR[R], res->FNCFs[R], res->FNCNs[R]);
		}
		if(res->flagFSCfull) {
			fprintf(fpt, "FSCfull %10.6f ", res->FSCfull[R]);
		}
		if(res->flagCref) {
			fprintf(fpt, "Cref %10.6f ", res->Cref[R]);
		}
		if(res->flagNoiseWeighted) {
			fprintf(fpt, "NoiseWeighted %10.6f ", res->NoiseWeighted[R]);
		}
		fprintf(fpt, "\n");
	}
}

void
lmrcImageFourierNeighborCorrelationPrintCentreMode(FILE* fpt)
{
	fprintf(fpt, "%d: Centre is ImageCentre Shift: (Nx/2.0, Ny/2.0, Nz/2.0 ) \n", lmrcImageFourierNeighborCorrelationCentreModeCentre);
	fprintf(fpt, "%d: Centre is BottomLeft  Shift: (0,      0,      0      ) \n", lmrcImageFourierNeighborCorrelationCentreModeBottomLeft);
	fprintf(fpt, "%d: Use StartN            Shift: (StartNx,StartNy,StartNz) \n", lmrcImageFourierNeighborCorrelationCentreModeUseStartN);

	fprintf(fpt, "Duncan Sousa, Nikolaus Grigorieff, 2007, JSB \n");
}

