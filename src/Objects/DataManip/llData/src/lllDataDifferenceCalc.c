/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataDifferenceCalc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataDifferenceCalc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataDifferenceCalc ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "lllDataDifferenceCalc.h"

/*
	S = Sum(test(a) - A*ref(b))^2 
	dS/dA = -2*ref(b)*(test(a) - A*ref(b)) 
	when S is min, then dS/dA = 0. Thus
	ref(b)*(test(a) - A*ref(b)) = 0
	A*ref(b)^2 = test(a)*ref(b)
	Therefore, 
		k = Sum(test(a)*ref(b))/Sum(ref(b)*ref(b))

*/

double
lllDataDifferenceCalcWithNormalizing(llData* dst, llData* newa, llData* a, llData* b, lllDataDifferenceCalcInfo* linfo, int mode)
{
	int l, R;
	double sumBB;
	double sumAB;
	double returnValue;

	if( a->llMax!=b->llMax) {
		fprintf(stderr, "Diffent Size in lllDataDifferenceCalc\n");
		fprintf(stderr, "a(%d), b(%d)\n", a->llMax, b->llMax);
		exit(EXIT_FAILURE);
	}
	llDataFandPHISet(a);
	llDataFandPHISet(b);

	sumBB = sumAB = 0;
	for(l=0; l<a->llMax; l++) {
		if(  a->LL[l].nn==b->LL[l].nn
		  && a->LL[l].nl==b->LL[l].nl) {
		    for(R=0; R<a->LL[l].nR; R++) {
				sumBB += b->LL[l].data[R].F*b->LL[l].data[R].F; 
				sumAB += a->LL[l].data[R].F*b->LL[l].data[R].F; 
			}
		} else {
			fprintf(stderr, "Different Type Layer Line Data\n");
			fprintf(stderr, "%d : (%d, %d) = (%d, %d) - (%d %d)\n",
				l, 
				dst->LL[l].nn, dst->LL[l].nl,
				a->LL[l].nn, a->LL[l].nl,
				b->LL[l].nn, b->LL[l].nl);

			exit(EXIT_FAILURE);
		}
	}
	linfo->A = sumAB/sumBB;
	switch(mode) {
		case 0: {
			llDataInitWithReference(newa, a);
			break;
		}
		case 1: {
			break;
		}
		default: {
			fprintf(stderr, "Not supported\n");
		}
	}
	lllDataCopy(newa, a);
	lllDataMultiplyReal(newa, 1.0/linfo->A);
	returnValue = lllDataDifferenceCalc(dst, newa, b, mode);
	return returnValue;
}

double
lllDataDifferenceCalc(llData* dst, llData* a, llData* b, int mode)
{
	int l, R;
	double rms;
	double sumRMS;
	double RMS;
	double re, im;
	double returnValue;

	if( a->llMax!=b->llMax) {
		fprintf(stderr, "Diffent Size in lllDataDifferenceCalc\n");
		fprintf(stderr, "a(%d), b(%d)\n", a->llMax, b->llMax);
		exit(EXIT_FAILURE);
	}
	switch(mode) {
		case 0: {
			llDataInitWithReference(dst, a);
			break;
		}
		case 1: {
			if( dst->llMax!=a->llMax) {
			    fprintf(stderr, "Diffent Size in lllDataDifferenceCalc\n");
				fprintf(stderr, "dst(%d), a(%d)\n", dst->llMax, a->llMax);
				exit(EXIT_FAILURE);
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d in lllDataDifferenceCalc\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	sumRMS=0;

	llDataFandPHISet(a);
	for(l=0; l<a->llMax; l++) {
		if(  a->LL[l].nn==b->LL[l].nn
		  && a->LL[l].nl==b->LL[l].nl
		  && dst->LL[l].nn==a->LL[l].nn
		  && dst->LL[l].nl==a->LL[l].nl) {
		    for(R=0; R<a->LL[l].nR; R++) {
				dst->LL[l].data[R].RR = a->LL[l].data[R].RR;
				llDataValueGet(b, l, a->LL[l].data[R].RR, &re, &im); 
				dst->LL[l].data[R].Re = a->LL[l].data[R].Re - re; 
				dst->LL[l].data[R].Im = a->LL[l].data[R].Im - im; 
				RMS = (SQR(a->LL[l].data[R].F)+(SQR(re)+SQR(im)))/2.0;
				sumRMS += RMS;
			}
		} else {
			fprintf(stderr, "Different Type Layer Line Data\n");
			fprintf(stderr, "%d : (%d, %d) = (%d, %d) - (%d %d)\n",
				l, 
				dst->LL[l].nn, dst->LL[l].nl,
				a->LL[l].nn, a->LL[l].nl,
				b->LL[l].nn, b->LL[l].nl);

			exit(EXIT_FAILURE);
		}
	}
	llDataFandPHISet(dst);
	rms=0;
	for(l=0; l<a->llMax; l++) {
		for(R=0; R<a->LL[l].nR; R++) {
			rms += SQR(dst->LL[l].data[R].F);
		}
	}
	if(0<sumRMS) {
		returnValue = rms/sumRMS;
		if(0<returnValue) {
			returnValue = sqrt(returnValue);
		} else {
			returnValue = 0;
		}
	} else {
		returnValue = 0;
	}
	return returnValue;
}

double
lllDataDifferencePValueCalc(llData* a, llData* b, int mode)
{
	double P;
	double sumF;
	double phia, Fa;
	double phib, Fb, F;
	int l, R;
	double re, im;
	double dP;
	double returnValue;

	P    = 0;
	sumF = 0.0;
	for(l=0; l<a->llMax; l++) {
		if(  a->LL[l].nn==b->LL[l].nn
		  && a->LL[l].nl==b->LL[l].nl) {
		    for(R=0; R<a->LL[l].nR; R++) {
				llDataValueGet(b, l, a->LL[l].data[R].RR, &re, &im); 
				if(0<a->LL[l].data[R].F) {
					Fa   = a->LL[l].data[R].F;
					phia = atan2(a->LL[l].data[R].Im, a->LL[l].data[R].Re);
				} else {
					Fa   = 0.0;
					phia = 0.0;
				}
				Fb = SQR(re) + SQR(im);
				if(0<Fb) {
					Fb   = sqrt(Fb); 
					phib = atan2(im, re); 
				} else {
					Fb   = 0.0;
					phib = 0.0;
				}
				F = (Fa + Fb)/2.0;
				dP = NORMAL_PHASE(phia - phib);
				dP = MIN(fabs(dP), fabs(2*M_PI - dP));
				P    += (F*SQR(dP));
				sumF += F;
			}
		} else {
			fprintf(stderr, "Different Type Layer Line Data\n");
			fprintf(stderr, "%d :  (%d, %d) - (%d %d)\n",
				l, 
				a->LL[l].nn, a->LL[l].nl,
				b->LL[l].nn, b->LL[l].nl);

			exit(EXIT_FAILURE);
		}
	}
	if(0<sumF) {
		returnValue = P/sumF;
		if(0<returnValue) {
			returnValue = sqrt(returnValue);
		} else {
			returnValue = 0.0;
		}
	} else {
		returnValue = 0.0;
	}
	return returnValue;
}

double
lllDataDifferencePValueCalc2(floatVector* fv, llData* a, llData* b, int mode)
{
	double P;
	double sumF;
	double phia, Fa;
	double phib, Fb, F;
	int l, R;
	double re, im;
	double dP;
	double returnValue;

	P    = 0;
	sumF = 0.0;
	for(l=0; l<a->llMax; l++) {
		if(  a->LL[l].nn==b->LL[l].nn
		  && a->LL[l].nl==b->LL[l].nl) {
		    for(R=0; R<a->LL[l].nR; R++) {
				llDataValueGet(b, l, a->LL[l].data[R].RR, &re, &im); 
				if(0<a->LL[l].data[R].F) {
					Fa   = a->LL[l].data[R].F;
					phia = atan2(a->LL[l].data[R].Im, a->LL[l].data[R].Re);
				} else {
					Fa   = 0.0;
					phia = 0.0;
				}
				Fb = SQR(re) + SQR(im);
				if(0<Fb) {
					Fb   = sqrt(Fb); 
					phib = atan2(im, re); 
				} else {
					Fb   = 0.0;
					phib = 0.0;
				}
				F = (Fa + Fb)/2.0;
				dP = NORMAL_PHASE(phia - phib);
				dP = MIN(fabs(dP), fabs(2*M_PI - dP));
				P    += (F*SQR(dP));
				sumF += F;
			}
		} else {
			fprintf(stderr, "Different Type Layer Line Data\n");
			fprintf(stderr, "%d :  (%d, %d) - (%d %d)\n",
				l, 
				a->LL[l].nn, a->LL[l].nl,
				b->LL[l].nn, b->LL[l].nl);

			exit(EXIT_FAILURE);
		}
	}
	if(0<sumF) {
		returnValue = P/sumF;
		if(0<returnValue) {
			returnValue = sqrt(returnValue);
		} else {
			returnValue = 0.0;
		}
	} else {
		returnValue = 0.0;
	}
	return returnValue;
}

double
lllDataDifferenceRValueCalc(llData* a, llData* b, int mode)
{
	double P;
	double sumF;
	double phia, Fa;
	double phib, Fb, F;
	int l, R;
	double re, im;
	double returnValue;

	P    = 0.0;
	sumF = 0.0;
	llDataFandPHISet(a);
	for(l=0; l<a->llMax; l++) {
		if(  a->LL[l].nn==b->LL[l].nn
		  && a->LL[l].nl==b->LL[l].nl) {
		    for(R=0; R<a->LL[l].nR; R++) {
				llDataValueGet(b, l, a->LL[l].data[R].RR, &re, &im); 
				switch(mode) {
					case 0: {
						P    += (SQR(re - a->LL[l].data[R].Re) + SQR(im - a->LL[l].data[R].Im));
						break;
					}
					case 1: {
						P    += (SQR(sqrt(SQR(re) + SQR(im)) - sqrt(SQR(a->LL[l].data[R].F))));
						break;
					}
					default: {
						fprintf(stderr, "Not supported mode: %d", mode);
						exit(EXIT_FAILURE);
					}
				}
				P    += (SQR(re - a->LL[l].data[R].Re) + SQR(im - a->LL[l].data[R].Im));
				sumF += sqrt((SQR(re) + SQR(im))*SQR(a->LL[l].data[R].F));
			}
		} else {
			fprintf(stderr, "Different Type Layer Line Data\n");
			fprintf(stderr, "%d :  (%d, %d) - (%d %d)\n",
				l, 
				a->LL[l].nn, a->LL[l].nl,
				b->LL[l].nn, b->LL[l].nl);

			exit(EXIT_FAILURE);
		}
	}
	if(0<sumF) {
		returnValue = P/sumF;
		if(0<returnValue) {
			returnValue = sqrt(returnValue);
		} else {
			returnValue = 0.0;
		}
	} else {
		returnValue = 0.0;
	}
	return returnValue;
}

