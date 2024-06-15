/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDatarMaxLimit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDatarMaxLimit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDatarMaxLimit ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "llData.h"
#include "genUtil.h"
#include "Memory.h"

#include "lllDatarMaxLimit.h"

inline int
lllDatarMaxLimitCheck(float R, int n, float rMax)
{
	if((fabs(n) - 2.0)/(2.0*PI*rMax) <= R) {
		return 1;
	} else {
		return 0;
	}
}

inline float 
lllDatarMaxLimitWeight(float R, int n, float rMax, float rMaxMin)
{
	float RR, RRMin;
	float nn;
	float weight;
	/*
	|n| - 2 <= 2*PI*rMax*R 
	*/
	nn = fabs(n);
	if(nn<=2) {
		weight = 1.0;
	} else {
		RR    = (nn - 2.0)/(2.0*PI*rMax); 
		RRMin = (nn - 2.0)/(2.0*PI*rMaxMin); 

		weight = (R - RR)/(RRMin - RR); 
	}
	return weight;
}

void
lllDatarMaxLimit(llData* llIn, lllDatarMaxLimitInfo linfo, int mode)
{
    int l, R;
	int newnR;
	int startR;
	llComplex* data;
	float weight;

	DEBUGPRINT("Start lllDatarMaxLimit\n");
	switch(mode) {
		case lllDatarMaxLimitModeNoMemorySave: {
			if(linfo.flagrMaxMin) {
			    for(l=0; l<llIn->llMax; l++) {
			    	for(R=0; R<llIn->LL[l].nR; R++) {
						weight = lllDatarMaxLimitWeight(llIn->LL[l].data[R].RR, llIn->LL[l].nn, linfo.rMax, linfo.rMaxMin);
						if(weight<0) { /* rMax < r */
							llIn->LL[l].data[R].Re = 0.0;
							llIn->LL[l].data[R].Im = 0.0;
							llIn->LL[l].data[R].F   = 0.0;
							llIn->LL[l].data[R].PHI = 0.0;
						} else if(weight<1.0) { /* rMaxMin < r < rMax */
							llIn->LL[l].data[R].Re = weight*llIn->LL[l].data[R].Re;
							llIn->LL[l].data[R].Im = weight*llIn->LL[l].data[R].Im;
							llIn->LL[l].data[R].F  = weight*llIn->LL[l].data[R].F;
						} else {
							break;
						}
					}
			    }
			} else {
			    for(l=0; l<llIn->llMax; l++) {
			    	for(R=0; R<llIn->LL[l].nR; R++) {
			            if(0==lllDatarMaxLimitCheck(llIn->LL[l].data[R].RR, llIn->LL[l].nn, linfo.rMax)) {
							llIn->LL[l].data[R].Re = 0.0;
							llIn->LL[l].data[R].Im = 0.0;
							llIn->LL[l].data[R].F   = 0.0;
							llIn->LL[l].data[R].PHI = 0.0;
						} else {
							break;
						}
					}
			    }
			}
			break;
		}
		case lllDatarMaxLimitModeMemorySave: {
		    for(l=0; l<llIn->llMax; l++) {
				newnR = 0;
		    	for(R=0; R<llIn->LL[l].nR; R++) {
		            if(lllDatarMaxLimitCheck(llIn->LL[l].data[R].RR, llIn->LL[l].nn, linfo.rMax)) {
						if(newnR==0) {
							startR = R;
						}
						newnR++;
		            }
		    	}
				llIn->LL[l].nR = newnR;
				if(0<newnR) {
					data = (llComplex*)memoryAllocate(sizeof(llData)*newnR, "in lllDatarMaxLimit");
		    		for(R=0; R<newnR; R++) {
						data[R] = llIn->LL[l].data[startR+R];
		    		}
					free(llIn->LL[l].data);
					llIn->LL[l].data = data;
		
					/* */
					llIn->LL[l].RMin  = llIn->LL[l].data[0].RR;
					llIn->LL[l].iRMin = startR + llIn->LL[l].iRMin; 
				} else {
					llIn->LL[l].RMin  = 0;
					llIn->LL[l].iRMin = 0;
					llIn->LL[l].RMax  = 0;
					llIn->LL[l].iRMax = 0;
				}
				DEBUGPRINT2("%d: %d\n", l, newnR);
		    }
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode in lllDatarMaxLimit: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

