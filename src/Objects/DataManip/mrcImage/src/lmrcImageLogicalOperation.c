/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageLogicalOperation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageLogicalOperation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageLogicalOperation ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include "./lmrcImageLogic.h"

void
lmrcImageLogicalOpModePrint(FILE* fpt)
{
	
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeAND,  "AND(P*Q)");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeOR,   "OR(P+Q)");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeNOT,  "^(1-P)");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeXOR,  "XOR");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeXNOR, "XNOR");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeNAND, "NAND");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeNOR,  "NOR");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeF,    "False");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeT,    "True");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeP,    "P");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeQ,    "Q");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeIMP,   "IMP(^P+Q)   : Implication: P -> Q");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeNIMP,  "NIMP(P*^Q)  : Not Implication: P -\\-> Q");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeIIMP,  "IIMP(P+^Q)  : Inverse Implication: Q -> P");
	fprintf(fpt, "mode %d: %s\n", lmrcImageLogicalOpModeNIIMP, "NIIMP(^P*Q) : Not Inverse Implication: Q -\\-> P");
}

double
lmrcImageLogicalOperation(mrcImage* out, mrcImage* P, mrcImage* Q, lmrcImageLogicalOpMode mode)
{
	mrcImageParaTypeReal x, y, z;
	double p;
	double q;
	double r;
	
	out->Header.Cont = P->Header.Cont;
	mrcInit(out, NULL);

	for(z=0; z<P->HeaderN.z; z++) {	
	for(y=0; y<P->HeaderN.y; y++) {	
	for(x=0; x<P->HeaderN.x; x++) {	
		mrcPixelDataGet(P, x, y, z, &p, mrcPixelRePart, mrcPixelHowNearest);
		if(NULL!=Q) {
			mrcPixelDataGet(Q, x, y, z, &q, mrcPixelRePart, mrcPixelHowNearest);
		}
		switch(mode) {
			case lmrcImageLogicalOpModeAND:
				r = MAX(0, MIN(p*q, 1));	
				break;
			case lmrcImageLogicalOpModeOR:
				r = MAX(0, MIN(p+q, 1));
				break;
			case lmrcImageLogicalOpModeNOT:
				r = MAX(0, MIN(1 - p, 1));
				break;
			case lmrcImageLogicalOpModeXOR:
				r = MAX(0, MIN((1-p)*q + p*(1-q), 1));
				break;
			case lmrcImageLogicalOpModeXNOR:
				r = MAX(0, MIN((1-p)*(1-q) + p*q, 1));
				break;
			case lmrcImageLogicalOpModeNAND:
				r = MAX(0, MIN((1-p*q), 1));
				break;
			case lmrcImageLogicalOpModeNOR:
				r = MAX(0, MIN(1-(p+q), 1));
				break;
			case lmrcImageLogicalOpModeF:
				r = 1;
				break;
			case lmrcImageLogicalOpModeT:
				r = 0;
				break;
			case lmrcImageLogicalOpModeP:
				r = MAX(0, MIN(p, 1));
				break;
			case lmrcImageLogicalOpModeQ:
				r = MAX(0, MIN(q, 1));
				break;
			case lmrcImageLogicalOpModeIMP:
				r = MAX(0, MIN((1-p)+q, 1));
				break;
			case lmrcImageLogicalOpModeNIMP:
				r = MAX(0, MIN(p*(1-q), 1));
				break;
			case lmrcImageLogicalOpModeIIMP:
				r = MAX(0, MIN(p+(1-q), 1));
				break;
			case lmrcImageLogicalOpModeNIIMP:
				r = MAX(0, MIN((1-p)*q, 1));
				break;
			default: {
				fprintf(stderr, "Not supproted Operation; %d\n", mode);
				exit(EXIT_FAILURE);
				break;
			}
		}
		mrcPixelDataSet(out, x, y, z, r, mrcPixelRePart);
	}
	}
	}
	return (double)r;
}
