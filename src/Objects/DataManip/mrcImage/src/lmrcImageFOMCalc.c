/*
# lmrcImageFOMCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFOMCalc 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#undef  DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageFOMCalc.h"
#include <math.h> 

static double __XCalc(double scale, double Fem, double Rem, double Iem, double Fcalc, double Rcalc, double Icalc, int mode);


/* 
 * meaning of indexing
 *  em:    from em
 *  calc:  from model
 *
 */

double
lmrcImageFOMXMaxCalc(mrcImage* in, mrcImage* ref, lmrcImageFOMCalcInfo* linfo, int mode)
{
	mrcImageParaTypeReal X, Y, Z;	
	double R;	
	double delX, delY, delZ;
	double* w;
	double* scale;

	double* XX;
	double  XXMax;

	//
	double Fcalc;
	double Rcalc;
	double Icalc;
	//
	double* Fem;
	double* Rem;
	double* Iem;

	int i;
	int n;     // inImageNum

	DEBUGPRINT("Start lmrcImageFOMXMaxCalc\n");
	delX = 1.0/in->HeaderN.x/in->HeaderLength.x;
	delY = 1.0/in->HeaderN.y/in->HeaderLength.y;
	delZ = 1.0/in->HeaderN.z/in->HeaderLength.z;

	DEBUGPRINT3("delX,delY,delZ: %f %f %f\n", delX, delY, delZ);
	n   = linfo->inImageNumber; // number of inImage
	w   = linfo->Weight;
	scale = linfo->Scale;
	XX  = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 

	Fem = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	Rem = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	Iem = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 

	// DEBUGPRINT3("Size: %d %d %d\n", in->HeaderN.x, in->HeaderN.y, in->HeaderN.z);
	XXMax = 0;	
	//DEBUGPRINT1("XXMax: %d \n", XXMax);	
	for(Z=-in->HeaderN.z/2.0; Z<in->HeaderN.z/2.0; Z++) {
	for(Y=-in->HeaderN.y/2.0; Y<in->HeaderN.y/2.0; Y++) {
	for(X=0; X<=in->HeaderN.x/2; X++) {
		R = sqrt(SQR(((int)(X+0.5))*delX)+SQR(((int)(Y+0.5))*delY)+SQR(((int)(Z+0.5))*delZ)); // R: Resolution  /A
		//DEBUGPRINT6("R: %f Rmin: %f Rmax: %f @ %f %f %f\n", R, linfo->minR, linfo->maxR, X, Y, Z);
		if(linfo->minR<R && R <= linfo->maxR) { // within ring
			//DEBUGPRINT3("R: %f Rmin: %f Rmax: %f\n", R, linfo->minR, linfo->maxR);
			mrcPixelDataGet(ref, X, Y, Z, &Fcalc,     mrcPixelMag,    mrcPixelHowNearest); 
			mrcPixelDataGet(ref, X, Y, Z, &Rcalc,     mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(ref, X, Y, Z, &Icalc,     mrcPixelImPart, mrcPixelHowNearest); 

			for(i=0; i<n; i++) { 
				mrcPixelDataGet(&in[i],  X, Y, Z, &Fem[i],   	 mrcPixelMag,    mrcPixelHowNearest); 
				mrcPixelDataGet(&in[i],  X, Y, Z, &Rem[i],   	 mrcPixelRePart, mrcPixelHowNearest); 
				mrcPixelDataGet(&in[i],  X, Y, Z, &Iem[i],   	 mrcPixelImPart, mrcPixelHowNearest); 
				if(linfo->flagRScale) {
					XX[i] = __XCalc(w[i]*scale[i]*R/(linfo->maxR - linfo->minR), Fem[i], Rem[i], Iem[i], Fcalc, Rcalc, Icalc, 0); 
				} else {
					XX[i] = __XCalc(w[i]*scale[i], Fem[i], Rem[i], Iem[i], Fcalc, Rcalc, Icalc, 0); 
				}
				if(XXMax<XX[i]) {
					XXMax = XX[i];
				}
				DEBUGPRINT2("XXMax after: %g %g\n", XXMax, XX[i]);	
			}

		}
	}
	}
	}
	//DEBUGPRINT1("XXMax: %g\n", XXMax);	

	return XXMax;
}


double
lmrcImageFOMScaleCalc(mrcImage* in, mrcImage* ref, lmrcImageFOMCalcInfo* linfo, int mode)
{
	mrcImageParaTypeReal X, Y, Z;	
	double R;	
	double delX, delY, delZ;
	double* w;

	double Fcalc;
	double Fem;

	double sumFcalc;
	double sumFem;
	int n;
	double scale;

	DEBUGPRINT("Start lmrcImageFOMScaleCalc\n");
	delX = 1.0/in->HeaderN.x/in->HeaderLength.x;
	delY = 1.0/in->HeaderN.y/in->HeaderLength.y;
	delZ = 1.0/in->HeaderN.z/in->HeaderLength.z;

	sumFcalc = sumFem = 0;
	n = 0;
	for(Z=-in->HeaderN.z/2.0; Z<in->HeaderN.z/2.0; Z++) {
	for(Y=-in->HeaderN.y/2.0; Y<in->HeaderN.y/2.0; Y++) {
	for(X=0; X<=in->HeaderN.x/2.0; X++) {
		R = sqrt(SQR(((int)(X+0.5))*delX)+SQR(((int)(Y+0.5))*delY)+SQR(((int)(Z+0.5))*delZ)); // R: Resolution  /A
		if(linfo->minR<R && R <= linfo->maxR) { // within ring
		 	DEBUGPRINT3("R: %f %f %f\n", R, linfo->minR, linfo->maxR);
			mrcPixelDataGet(ref, X, Y, Z, &Fcalc,  mrcPixelMag, mrcPixelHowNearest); 
			mrcPixelDataGet(in,  X, Y, Z, &Fem, mrcPixelMag, mrcPixelHowNearest); 
			sumFem  += Fem;
			sumFcalc += Fcalc;
		}
	}
	}
	}

	if(0<sumFem) {
		scale = sumFcalc/sumFem;
	} else {
		scale = 0;
	}

	return scale;
}

static
double
__XCalc(double scale, double Fem, double Rem, double Iem, double Fcalc, double Rcalc, double Icalc, int mode)
{
	double XXINV ;
	double XX;


	XXINV = SQR(scale*Rem-Rcalc)+SQR(scale*Iem-Icalc);
	//XXINV = sqrt(SQR(scale*Rem-Rcalc)+SQR(scale*Iem-Icalc));

	//DEBUGPRINT3("data calc: %g %g %g \n", Fcalc, Rcalc, Icalc);
	//DEBUGPRINT3("data   em: %g %g %g \n", Fem,   Rem,   Iem);
	//DEBUGPRINT2("data XX_INV w: %g %g \n",  XXINV, scale);

	if(0<XXINV) {
		XX = 2*scale*Fem*Fcalc/XXINV;
		//XX = 2*sqrt(scale*Fem*Fcalc)/XXINV;
	} else {
		if(0<Fem || 0<Fcalc){
			XX = 1e20;
		} else { 
			XX = 1e20;
		}
	}

	//if(1e6 <=XX) XX = 1e6;
	DEBUGPRINT1("data XX: %g\n", XX);
	return XX;
}

double
lmrcImageFOMCalc(mrcImage* in, mrcImage* ref, lmrcImageFOMCalcInfo* linfo, int mode)
{
	mrcImageParaTypeReal X, Y, Z;	
	double R;	
	double delX, delY, delZ;
	double sumPP;
	double sumPPRe;
	double sumPPIm;
	double* w;
	double* scale;
	double alpha;

	double* X1;
	double* X2;
	double* XX;
	double  offset;
	
	double Pem, Pcalc, PP;
	//
	double AlphaCalc;
	double Fcalc;
	double Rcalc;
	double Icalc;
	//
	double* AlphaEM;
	double* Fem;
	double* Rem;
	double* Iem;
	double FF;
	double Re,  Im;
	double XXMax;
	double FOM;
	double FEM;

	double sector;

	int i;
	int Num ;  // Data Number within a Ring
	int n;     // inImageNum

	int k, nstep;
	double deltaAlpha;

	DEBUGPRINT("Start lmrcImageFOMCalc\n");
	DEBUGPRINT1("linfo->XXMax: %g\n", linfo->XXMax);
	delX = 1.0/in->HeaderN.x/in->HeaderLength.x;
	delY = 1.0/in->HeaderN.y/in->HeaderLength.y;
	delZ = 1.0/in->HeaderN.z/in->HeaderLength.z;

	FOM = 0; // FOM
	Num = 0; // Number of Data
	n   = linfo->inImageNumber; // number of inImage
	w   = linfo->Weight;
	scale = linfo->Scale;

	XX  = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	X1  = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	X2  = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	AlphaEM = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	Fem = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	Rem = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 
	Iem = memoryAllocate(sizeof(double)*n, "in lmrcImageFOMCalc"); 

	// DEBUGPRINT3("Size: %d %d %d\n", in->HeaderN.x, in->HeaderN.y, in->HeaderN.z);
	for(Z=-in->HeaderN.z/2.0; Z< in->HeaderN.z/2.0; Z++) {
	for(Y=-in->HeaderN.y/2.0; Y< in->HeaderN.y/2.0; Y++) {
	for(X=0;                  X<=in->HeaderN.x/2.0; X++) {
		R = sqrt(SQR(((int)(X+0.5))*delX)+SQR(((int)(Y+0.5))*delY)+SQR(((int)(Z+0.5))*delZ)); // R: Resolution  /A
		if(0<R) {
			sector = fabs(asin(((int)(Z+0.5))*delZ/R));
		} else {
			sector = 0;	
		}
		//DEBUGPRINT3("R: %f %f %f\n", R, linfo->minR, linfo->maxR);
		DEBUGPRINT6("R: %f %f <-> %f sector %f %f <-> %f\n", R, linfo->minR, linfo->maxR, sector, linfo->minSector, linfo->maxSector);
		//DEBUGPRINT6("R: %f %f %f @ %f %f %f\n", R, linfo->minR, linfo->maxR, X, Y, Z);
		if(linfo->minR      < R       &&      R <= linfo->maxR
		 &&linfo->minSector <= sector && sector <= linfo->maxSector  ) { // within ring
		 	DEBUGPRINT3("R: %f %f %f\n", R, linfo->minR, linfo->maxR);
			mrcPixelDataGet(ref, X, Y, Z, &AlphaCalc, mrcPixelPhase, mrcPixelHowNearest); 
			mrcPixelDataGet(ref, X, Y, Z, &Fcalc,     mrcPixelMag, mrcPixelHowNearest); 
			mrcPixelDataGet(ref, X, Y, Z, &Rcalc,     mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(ref, X, Y, Z, &Icalc,     mrcPixelImPart, mrcPixelHowNearest); 
		 	DEBUGPRINT4("data ref: %g %g %g %g\n", AlphaCalc*DEGREE, Fcalc, Rcalc, Icalc);

			//DEBUGPRINT1("filenumber: %d \n", n);
			XXMax = 0;
			for(i=0; i<n; i++) { 
				mrcPixelDataGet(&in[i],  X, Y, Z, &AlphaEM[i],   mrcPixelPhase,  mrcPixelHowNearest); 
				mrcPixelDataGet(&in[i],  X, Y, Z, &Fem[i],   	 mrcPixelMag,    mrcPixelHowNearest); 
				mrcPixelDataGet(&in[i],  X, Y, Z, &Rem[i],   	 mrcPixelRePart, mrcPixelHowNearest); 
				mrcPixelDataGet(&in[i],  X, Y, Z, &Iem[i],   	 mrcPixelImPart, mrcPixelHowNearest); 
		 		DEBUGPRINT4("data  em: %g %g %g %g\n", AlphaEM[i]*DEGREE, Fem[i], Rem[i], Iem[i]);

				if(linfo->flagRScale) {
					XX[i] = __XCalc(w[i]*scale[i]*R/(linfo->maxR -linfo->minR), Fem[i], Rem[i], Iem[i], Fcalc, Rcalc, Icalc, 0); 
				} else {
					XX[i] = __XCalc(w[i]*scale[i], Fem[i], Rem[i], Iem[i], Fcalc, Rcalc, Icalc, 0); 
				}
				X1[i] = X2[i] = XX[i];
				//X1[i] = X2[i] = XX[i];
				DEBUGPRINT3("check XX: %g %g %g \n", XX[i], X1[i], X2[i]);
				if(XXMax<XX[i]) {
					XXMax = XX[i];	
				}
			}
			
			// Integral
			nstep = (int)(2*M_PI/linfo->deltaAlpha);
			if(nstep%2) nstep++;	// nstep is even
			deltaAlpha = 2*M_PI/nstep;	
			//DEBUGPRINT2("Integral: %d %f\n", nstep, deltaAlpha*DEGREE);

			// Integral by Simpson Methods
			offset = XXMax; 	// offset: Escape from the computational limit.
								//         Function as a weight of exp(-offset). 
								//         Actually, this factor will be neglected 
								//         because the same weight is multipled to
								//         jboth of a denominator and a numerator.
			sumPP = sumPPRe = sumPPIm = 0;
			for(i=0; i<n; i++) {
				DEBUGPRINT3("check XX: %g %g %g \n", X1[i], X2[i], offset);
				// odd: 4 
				for(k=1; k<nstep-1; k+=2) {
					alpha = k*deltaAlpha;
					Pcalc = exp(X2[i]*cos(alpha-AlphaCalc )-offset); 
					Pem   = exp(X1[i]*cos(alpha-AlphaEM[i])-offset);
					PP    = Pem*Pcalc;
					DEBUGPRINT5("check in Intgral 1 :%g %g %g %g %g\n", X1[i], X2[i], alpha, AlphaCalc, AlphaEM[i]);
					DEBUGPRINT3("check in Intgral 1 :%g %g %g\n", X2[i]*cos(alpha-AlphaCalc )-offset, X1[i]*cos(alpha-AlphaEM[i])-offset, offset);
					DEBUGPRINT3("check in Intgral 1 :%g %g %g\n", Pcalc, Pem, PP);
					sumPP   += 4*PP;
					sumPPRe += 4*PP*Fem[i]*cos(alpha);
					sumPPIm += 4*PP*Fem[i]*sin(alpha);
				}
				//DEBUGPRINT3("check Intgral 1 :%f %f %f\n", sumPP, sumPPRe, sumPPIm);

				// Even: 2
				for(k=2; k<nstep-1; k+=2) {
					alpha = k*deltaAlpha;
					Pcalc = exp(X2[i]*cos(alpha-AlphaCalc )-offset);
					Pem   = exp(X1[i]*cos(alpha-AlphaEM[i])-offset);
					PP    = Pem*Pcalc;
					sumPP   += 2*PP;
					sumPPRe += 2*PP*Fem[i]*cos(alpha);
					sumPPIm += 2*PP*Fem[i]*sin(alpha);
				}
				//DEBUGPRINT3("check Intgral 2 :%f %f %f\n", sumPP, sumPPRe, sumPPIm);

				// Both ends
				alpha = 0;
				Pcalc   = exp(X2[i]*cos(alpha-AlphaCalc )-offset);
				Pem     = exp(X1[i]*cos(alpha-AlphaEM[i])-offset);
				PP  = Pem*Pcalc;
				sumPP   += PP;
				sumPPRe += PP*Fem[i]*cos(alpha);
				sumPPIm += PP*Fem[i]*sin(alpha);
			
				alpha = 2*M_PI;
				Pcalc   = exp(X2[i]*cos(alpha-AlphaCalc )-offset);
				Pem     = exp(X1[i]*cos(alpha-AlphaEM[i])-offset);
				PP  = Pem*Pcalc;
				sumPP   += PP;
				sumPPRe += PP*Fem[i]*cos(alpha);
				sumPPIm += PP*Fem[i]*sin(alpha);

				
				DEBUGPRINT3("check Intgral :%f %f %f\n", sumPP, sumPPRe, sumPPIm);
				if(0<sumPP) {
					Re = sumPPRe/sumPP;
					Im = sumPPIm/sumPP;
				} else {
					fprintf(stderr, "sumPP is zero\n");
				}
				Num++;
				FF = sqrt(SQR(Re)+SQR(Im));
				FF /= Fem[i];
				FOM += FF;
				DEBUGPRINT3("check :%g %g %g\n", sumPP, sumPPRe, sumPPIm);
				//DEBUGPRINT3("check :%g %g %d\n", Im, Re, Num);
				//DEBUGPRINT1("check :%g\n", FF);
			} // file index
		} // within ring
	}
	}
	}
	FOM /= Num;

	// DEBUGPRINT3("Size: %d %d %d\n", in->HeaderN.x, in->HeaderN.y, in->HeaderN.z);
	DEBUGPRINT2("End: lmrcImageFOMCalc %f %d\n", FOM, Num)	

	linfo->FOM = FOM;
	linfo->Num = Num;
	return FOM;
}
