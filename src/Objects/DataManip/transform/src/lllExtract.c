/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllExtract ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllExtract 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllExtract ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lllExtract.h"

void
lllExtract(llData* out1, llData* out2, mrcImage* in, lllExtractInfo* info)
{
    long l;
    long i;
	double re, im;
    double R, delR, delZ;
	int iRMax;
    double xShift; 
	double F, PHI, RR;

    DEBUGPRINT("Information Check\n");
    if(info->xStep!=in->HeaderLength.x) {
        fprintf(stderr, "xStep(%g) in CtrlFile != Length.x(%g) in mrcImage\n", 
			info->xStep, in->HeaderLength.x);
    }
    if(info->yStep!=in->HeaderLength.y) {
        fprintf(stderr, "yStep(%g) in CtrlFile != Length.y(%g) in mrcImage\n", 
			info->yStep, in->HeaderLength.y);
    }

    iRMax = info->MaxX;
    delR = 1.0/(info->xStep*in->HeaderN.x);
    delZ = 1.0/(info->yStep*in->HeaderN.y);

	/* xShift [A] */
    xShift = info->xStep*info->xShift; 

    if(fabs(1.0/delR-info->delRInv)>1e-2) {
        fprintf(stderr, "delRInv(%g) in CtrlFile != Length.x*N.x(%g) in mrcImage\n", 
			info->delRInv, 1.0/delR);
        fprintf(stderr, "Use delRInv\n");
        delR = 1.0/info->delRInv;
    }

	DEBUGPRINT("llData Information Set: Total information\n");
    out1->llMax 	= out2->llMax 	  = info->llMax;
    out1->nRMax 	= out2->nRMax 	  = info->MaxX; 
	out1->truePitch = out2->truePitch = info->truePitch;

    llDataHeaderInit(out1);
    llDataHeaderInit(out2);

    DEBUGPRINT("llData Information Set: Near/Far common information \n");
    for(l=0; l<info->llMax; l++) {
        out1->LL[l].nn = info->n[l]; 
        out1->LL[l].nl = info->l[l];
        out1->LL[l].Z  = info->Y[l];
        out1->LL[l].Weight = info->weight[l];
		out1->LL[l].delBR  = delR;
		out2->LL[l] = out1->LL[l];
    }

    DEBUGPRINT("llData Information Set: Near/Far special information \n");
    for(l=0; l<out1->llMax; l++) { /* Near Side */ 
		if(0<=out1->LL[l].nn) {
			out1->LL[l].iRMin = info->leftMin[l];
			out1->LL[l].iRMax = info->leftMax[l];
		} else {
			out1->LL[l].iRMin = info->rightMin[l];
			out1->LL[l].iRMax = info->rightMax[l];
		}
		out1->LL[l].RMin = delR*out1->LL[l].iRMin; 
		out1->LL[l].RMax = delR*out1->LL[l].iRMax; 
		out1->LL[l].nR   = out1->LL[l].iRMax - out1->LL[l].iRMin + 1;
		out1->LL[l].Side = NearSide;
	}
    for(l=0; l<out2->llMax; l++) { /* Far Side */ 
		if(0<=out2->LL[l].nn) {
			out2->LL[l].iRMin = info->rightMin[l];
			out2->LL[l].iRMax = info->rightMax[l];
		} else {
			out2->LL[l].iRMin = info->leftMin[l];
			out2->LL[l].iRMax = info->leftMax[l];
		}
		out2->LL[l].RMin = delR*out2->LL[l].iRMin; 
		out2->LL[l].RMax = delR*out2->LL[l].iRMax; 
		out2->LL[l].nR   = out2->LL[l].iRMax - out2->LL[l].iRMin + 1;
		out2->LL[l].Side = FarSide;
	}

	DEBUGPRINT("llData->LL[l].data Initialize\n");
	llDataDataInit(out1);
	llDataDataInit(out2);

    for(l=0; l<out1->llMax; l++) { /* Near Side */ 
        if(out1->LL[l].nn>=0) {
            for(R=out1->LL[l].iRMin, i=0; R<=out1->LL[l].iRMax; R++, i++) {
                RR = R*delR;    
                mrcPixelDataGet(in, -R, out1->LL[l].Z, 0.0, &F,   mrcPixelMag,    mrcPixelHowNearest);
                mrcPixelDataGet(in, -R, out1->LL[l].Z, 0.0, &PHI, mrcPixelPhase,  mrcPixelHowNearest);
#ifdef DEBUG
				if(l==0 && R<1) {
                	mrcPixelDataGet(in, -R, out1->LL[l].Z, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
                	mrcPixelDataGet(in, -R, out1->LL[l].Z, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
					DEBUGPRINT3("PHI: %f Re: %f Im: %f at (0, 0) in lllExtract\n", PHI, re, im);
				}
#endif
                PHI += (2*PI*RR*xShift);
                out1->LL[l].data[i].RR  = RR;    
				out1->LL[l].data[i].F   = F;
				out1->LL[l].data[i].PHI = NORMAL_PHASE(PHI);
				out1->LL[l].data[i].Re  = F*cos(PHI);
				out1->LL[l].data[i].Im  = F*sin(PHI);
            }
        } else {
            for(R=out1->LL[l].iRMin, i=0; R<=out1->LL[l].iRMax; R++, i++) {
                RR = R*delR;    
                mrcPixelDataGet(in, R, out1->LL[l].Z, 0.0, &F,   mrcPixelMag,    mrcPixelHowNearest);
                mrcPixelDataGet(in, R, out1->LL[l].Z, 0.0, &PHI, mrcPixelPhase,  mrcPixelHowNearest);
                PHI -= (2*PI*RR*xShift);
                out1->LL[l].data[i].RR  = RR;    
				out1->LL[l].data[i].F   = F;
				out1->LL[l].data[i].PHI = NORMAL_PHASE(PHI);
				out1->LL[l].data[i].Re = F*cos(PHI);
				out1->LL[l].data[i].Im = F*sin(PHI);
            }
        }
    }
	out1->Side = out1->LL[0].Side;
	out1->Pole = llDataPoleNormal;

    for(l=0; l<out2->llMax; l++) { /* Far Side */
        if(out2->LL[l].nn>=0) {
            for(R=out2->LL[l].iRMin, i=0; R<=out2->LL[l].iRMax; R++, i++) {
                RR = R*delR;    
                mrcPixelDataGet(in, R, out2->LL[l].Z, 0.0, &F,   mrcPixelMag,    mrcPixelHowNearest);
                mrcPixelDataGet(in, R, out2->LL[l].Z, 0.0, &PHI, mrcPixelPhase,  mrcPixelHowNearest);
                PHI -= (2*PI*RR*xShift);
                out2->LL[l].data[i].RR  = RR;    
				out2->LL[l].data[i].F   = F;
				out2->LL[l].data[i].PHI = NORMAL_PHASE(PHI);
				out2->LL[l].data[i].Re = F*cos(PHI);
				out2->LL[l].data[i].Im = F*sin(PHI);
            }
        } else {
            for(R=out2->LL[l].iRMin, i=0; R<=out2->LL[l].iRMax; R++, i++) {
                RR = R*delR;    
                mrcPixelDataGet(in, -R, out2->LL[l].Z, 0.0, &F,   mrcPixelMag,    mrcPixelHowNearest);
                mrcPixelDataGet(in, -R, out2->LL[l].Z, 0.0, &PHI, mrcPixelPhase,  mrcPixelHowNearest);
                PHI += (2*PI*RR*xShift);
                out2->LL[l].data[i].RR  = RR;    
				out2->LL[l].data[i].F   = F;
				out2->LL[l].data[i].PHI = NORMAL_PHASE(PHI);
				out2->LL[l].data[i].Re = F*cos(PHI);
				out2->LL[l].data[i].Im = F*sin(PHI);
            }
        }
		if(out1->LL[l].nR!=out2->LL[l].nR) {
			fprintf(stderr, "Something wrong in llExtract: nR(Nea) != nR(Far)\n");
		}
    }
	out2->Side = out2->LL[0].Side;
	out2->Pole = llDataPoleNormal;
}

