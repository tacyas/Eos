/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataAxisSearch ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataAxisSearch 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataAxisSearch ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "../inc/llData.h"
#include "lllDataAxisSearch.h"
#include "lllDataFit.h"

/*
	llDataAxisSearch(
		llData* nea,     LayerLineData Pointer to be treated
		llData* far,     LayerLineData Pointer to be treated
    	llDataFittedParam* p,
    	long               mode);
*/
    
#define PI M_PI
#define COUNT_MAX (4)
#define END_VALUE (1e-4)
#define CUTOFF (0.25)
#define STEP   (20.0)
#define STEP2  (STEP/2.0)

extern inline int __lllDataAxisSearchCheck0(llDataParamToFit* fit, llDataParamToFit* p, long mode);
extern inline void __lllDataAxisSearch1(llData* nea, llData* far, llDataParamToFit* P, llDataParamToFit* R, char* filename, long mode);
extern inline void __lllDataAxisSearch0(llData* nea, llData* far, llDataParamToFit* Para, long mode);
extern inline void __lllDataAxisSearchQValue0(llData* nea, llData* far, llDataParamToFit* Para, long mode);
extern inline void __lllDataAxisSearchQ2Value0(llData* nea, llData* far, llDataParamToFit* Para, long mode);

static char* __P2FileName__ = (char*)NULL;

void
lllDataAxisSearch(llData* nea, llData* far, llDataFittedParam* p, long mode)
{
	if(!nea->FmaxSet) {
		llDataFmaxSet(nea, 0);
	}
	if(!far->FmaxSet) {
		llDataFmaxSet(far, 0);
	}
	if(!p->Para.flagLLTable) {
		p->Para.flagLLTable = nea->llMax;
		p->Para.llTable = llDataTableBetweenTwollDataCreate(nea, far, 0);
	}

	switch(0x0f&mode) {
		case QVALUE_MODE: {
			DEBUGPRINT("in lllDataAxisSearch\n");
        	__lllDataAxisSearch1(nea, far, &(p->Para), &(p->QPara), __P2FileName__, 
				mode&(QVALUE_MODE|lllDataAxisSearchModeSearchProcess));
	    	p->Para.x.Value     = p->QPara.x.Value;
	    	p->Para.Omega.Value = p->QPara.Omega.Value;
			p->Para.R           = p->QPara.R;
			break;
		}
		case Q2VALUE_MODE: {
			DEBUGPRINT("in lllDataAxisSearch: Q2\n");
        	__lllDataAxisSearch1(nea, far, &(p->Para), &(p->Q2Para), __P2FileName__, 
				mode&(Q2VALUE_MODE|lllDataAxisSearchModeSearchProcess));
	    	p->Para.x.Value     = p->Q2Para.x.Value;
	    	p->Para.Omega.Value = p->Q2Para.Omega.Value;
			p->Para.R           = p->Q2Para.R;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode : %ld in lllDataAxisSearch\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

void
lllDataAxisSearchWithFile(llData* nea, llData* far, llDataFittedParam* p, char* filename, long mode)
{
	__P2FileName__ = filename;
	lllDataAxisSearch(nea, far, p, mode);
	__P2FileName__ = (char*)NULL;
}

void 
__lllDataAxisSearch1(llData* nea, llData* far, llDataParamToFit* P, llDataParamToFit* R, char* filename, long mode)
{
    llDataParaTypeReal ix, iOmega;
	llDataParamToFit tmp, otmp;
   	mrcImage  mrc;
	llDataParaTypeInteger count;

	DEBUGPRINT("----- __lllDataAxisSearch1 Start -----\n");

	/* Initialization */
    tmp = *R = *P; /* Order is important */

	/* Fist Trial */
    tmp.Omega.Value = P->Omega.Max;
    tmp.x.Value     = P->x.Max;
    __lllDataAxisSearch0(nea, far, &tmp, mode);
    *R = tmp;
	
	/* Parameter Set */
	if(NULL!=filename) {
		DEBUGPRINT1(, "");
		mrc.HeaderN.x = fabs((tmp.x.Max     - tmp.x.Min)    /tmp.x.Delta)     + 1.0;
		mrc.HeaderN.y = fabs((tmp.Omega.Max - tmp.Omega.Min)/tmp.Omega.Delta) + 1.0;
		mrc.HeaderN.z = 1.0;
		mrc.HeaderMode = mrcFloatImage;
		mrc.HeaderLength.x = tmp.x.Delta; 
		mrc.HeaderLength.y = tmp.Omega.Delta; 
		mrc.HeaderStartN.x = tmp.x.Min; 
		mrc.HeaderStartN.y = tmp.Omega.Min; 
		mrcInit(&mrc, NULL);
	}

	count = 0;
	DEBUGPRINT("AxisSearch Start\n");
	while(count<COUNT_MAX) {
		otmp = tmp;

	    for(tmp.Omega.Value=tmp.Omega.Min, iOmega=0; tmp.Omega.Value<=tmp.Omega.Max; tmp.Omega.Value+=tmp.Omega.Delta, iOmega++) {
			DEBUGPRINT1("AxisSearch : Omega %15.6f\n", tmp.Omega.Value);
		    for(tmp.x.Value=tmp.x.Min, ix=0; tmp.x.Value<=tmp.x.Max; tmp.x.Value+=tmp.x.Delta, ix++) {
   	    		__lllDataAxisSearch0(nea, far, &tmp, mode);

				if(NULL!=filename 
				&&    0==count) {
					mrcPixelDataSet(&mrc, ix, iOmega, 0.0, tmp.R, mrcPixelRePart);
				}

 	        	__lllDataAxisSearchCheck0(R, &tmp, mode);
    	    }
	    }

		if(R->R <= otmp.R) {
			if(otmp.R - R->R < END_VALUE) {
				break;
			}
		} else {
			fprintf(stderr, "Something wrong in axis-search: R %f old %f\n", R->R, otmp.R);
			break;
		}

		tmp.x.Value      = R->x.Value;
		tmp.Omega.Value  = R->Omega.Value;
		lllDataNewFittedParameterSet0(&(tmp.x));
		lllDataNewFittedParameterSet0(&(tmp.Omega));
		count++;
    }
	DEBUGPRINT("Fitting End\n");
	if(NULL!=filename) {
		mrcFileWrite(&mrc, filename, "in lllDataAxisSearch", 0);
	}
}

inline int
__lllDataAxisSearchCheck0(llDataParamToFit* minimum, llDataParamToFit* current, long mode)
{
    if(minimum->R>=current->R) {
		*minimum = *current;
        if(mode&lllDataAxisSearchModeSearchProcessPrint) {
            fprintf(stdout, "R %15.6f O %15.6f x %15.6f\n", 
				(float)minimum->R*DEGREE, 
				(float)minimum->Omega.Value*DEGREE, 
				(float)minimum->x.Value);
        }
		return 1;
    } else {
		return 0;
	}
}    

void
__lllDataAxisSearch0(llData* nea, llData* far, llDataParamToFit* Para, long mode)
{
    switch(0x0f&mode) {
		case QVALUE_MODE: {
			__lllDataAxisSearchQValue0(nea, far, Para, mode&QVALUE_MODE);
			break;
		}	
		case Q2VALUE_MODE: {
			__lllDataAxisSearchQ2Value0(nea, far, Para, mode&Q2VALUE_MODE);
			break;
		}
    }
}

void
__lllDataAxisSearchQValue0(llData* nea, llData* far, llDataParamToFit* Para, long  mode)
{
    long lnea, lfar, R, sig;
    llDataParaTypeInteger nn;
    llDataParaTypeReal dtheta, Sum, neap, neap2, farp, farp2, F, weight;

	weight = 1.0;
    Para->R = Sum = 0;
    for(lnea=0; lnea<nea->llMax; lnea++) {
		lfar = Para->llTable[lnea];
        if(lfar<far->llMax) {
            if(nea->LL[lnea].nl==far->LL[lfar].nl 
			 &&nea->LL[lnea].nn==far->LL[lfar].nn) {
				if(nea->LL[lnea].Weight!=0.0
				 ||far->LL[lfar].Weight!=0.0) {
	                /* Reference Layer Number = Layer Number */
					nn = nea->LL[lnea].nn;
	                if(   (nn>=0&&nea->LL[lnea].Side==NearSide)
	                    ||(nn< 0&&nea->LL[lnea].Side==FarSide)) {
	                    sig = -1.0;
	                } else {
	                    sig = 1.0;
	                }
			    	for(R=0; R<nea->LL[lnea].nR; R++) {
	    		        F = fabs((nea->LL[lnea].data[R].F+far->LL[lfar].data[R].F)/2.0);
						if(0.0 < F) {
							if(nea->LL[lnea].Fmax*CUTOFF < F && far->LL[lfar].Fmax*CUTOFF < F) {
		                    	weight = nea->LL[lnea].Weight;
							} else if (0.0 < F){
		                    	weight = nea->LL[lnea].Weight*0.5;
							}
                    		/* Phase Transform */
                    		neap = nearSidePhaseGet(nea->LL[lnea].data[R].PHI, nn, nea->LL[lnea].Side, nea->Pole);
                    		farp = nearSidePhaseGet(far->LL[lfar].data[R].PHI, nn, far->LL[lfar].Side, far->Pole);
                    		neap2 = NORMAL_PHASE(neap - sig*(2*PI*Para->x.Value*nea->LL[lnea].data[R].RR + sin(Para->Omega.Value)*nn*PI));
                    		farp2 = NORMAL_PHASE(farp + sig*(2*PI*Para->x.Value*far->LL[lfar].data[R].RR + sin(Para->Omega.Value)*nn*PI));
                    		/* Phase Residual Calculation */
            				dtheta = fmod(fabs(neap2-farp2), 2*PI);
							dtheta = fabs(MIN(2*PI-dtheta, dtheta));
                    		Sum     += F*weight;
		            		Para->R += F*weight*dtheta;
						}
	    			}
				}
	    	}	
        }
    }
	Para->R = Para->R/Sum;
}

void
__lllDataAxisSearchQ2Value0(llData* nea, llData* far, llDataParamToFit* Para, long  mode)
{
    long lnea, lfar, R, sig;
    llDataParaTypeInteger nn;
    llDataParaTypeReal dtheta, dtheta2, Sum, neap, neap2, farp, farp2, farp3, F, weight;

    Para->R = Sum = 0;
    for(lnea=0; lnea<nea->llMax; lnea++) {
		lfar = Para->llTable[lnea];
        if(lfar<far->llMax) {
            if(nea->LL[lnea].nl==far->LL[lfar].nl 
			 &&nea->LL[lnea].nn==far->LL[lfar].nn) {
				if(nea->LL[lnea].Weight!=0.0
				 ||far->LL[lfar].Weight!=0.0) {
	                /* Reference Layer Number = Layer Number */
					nn = nea->LL[lnea].nn;
	                if(   (nn>=0&&nea->LL[lnea].Side==NearSide)
	                    ||(nn< 0&&nea->LL[lnea].Side==FarSide)) {
	                    sig = -1.0;
	                } else {
	                    sig = 1.0;
	                }
			    	for(R=0; R<nea->LL[lnea].nR; R++) {
	    		        F = fabs((nea->LL[lnea].data[R].F+far->LL[lfar].data[R].F)/2.0);
						if(0.0 < F) {
							if(nea->LL[lnea].Fmax*CUTOFF < F && far->LL[lfar].Fmax*CUTOFF < F) {
		                    	weight = nea->LL[lnea].Weight;
							} else if (0.0 < F){
		                    	weight = nea->LL[lnea].Weight*0.5;
							}
	                    	/* Phase Transform */
	                    	neap = nearSidePhaseGet(nea->LL[lnea].data[R].PHI, nn, nea->LL[lnea].Side, nea->Pole);
	                    	farp = nearSidePhaseGet(far->LL[lfar].data[R].PHI, nn, far->LL[lfar].Side, far->Pole);
	                    	neap2 = NORMAL_PHASE(neap - sig*(2*PI*Para->x.Value*nea->LL[lnea].data[R].RR + sin(Para->Omega.Value)*nn*PI));
	                    	farp2 = NORMAL_PHASE(farp + sig*(2*PI*Para->x.Value*far->LL[lfar].data[R].RR + sin(Para->Omega.Value)*nn*PI));
	                    	farp3 = NORMAL_PHASE(farp + sig*(2*PI*Para->x.Value*far->LL[lfar].data[R].RR + sin(Para->Omega.Value)*nn*PI) + nn*PI);
	                    	/* Phase Residual Calculation */
	            			dtheta = fmod(fabs(neap2-farp2), 2*PI);
							dtheta = fabs(MIN(2*PI-dtheta, dtheta));

	            			dtheta2 = fmod(fabs(neap2-farp3), 2*PI);
							dtheta2 = fabs(MIN(2*PI-dtheta2, dtheta2));

							if(dtheta2<dtheta) {
								dtheta = dtheta2;
							}
	                    	weight = nea->LL[lnea].Weight;
	                    	Sum += F*weight;
		            		Para->R += F*weight*dtheta;
						}
	    			}
				}
	    	}
       	}
    }
	Para->R = Para->R/Sum;
}
