/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataAvgTo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataAvgTo ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdlib.h>
#include "../inc/llData.h"
#include "genUtil.h"

void
lllDataAvgToNea(llData* nea, llData* avg)
{
	lllDataAvgTo(nea, avg, NearSide);
}

void
lllDataAvgToFar(llData* far, llData* avg)
{
	lllDataAvgTo(far, avg, FarSide);
}

void
lllDataAvgTo(llData* dst, llData* src, llDataParaTypeInteger side)
{
    int l, r;
    double PHI, F;

	switch(side) {
		case NearSide:
		case AverageSide: {
			dst->Side = NearSide;
	    	for(l=0; l<src->llMax; l++) {
				dst->LL[l].Side = NearSide;
   		 		for(r=0; r<src->LL[l].nR; r++) {
       		   		dst->LL[l].data[r].Re = src->LL[l].data[r].Re;
            		dst->LL[l].data[r].Im = src->LL[l].data[r].Im;
            		dst->LL[l].data[r].F   = src->LL[l].data[r].F;
            		dst->LL[l].data[r].PHI = src->LL[l].data[r].PHI;
				}
			}
			break;
		}
		case FarSide: {
			dst->Side = FarSide;
	    	for(l=0; l<src->llMax; l++) {
				dst->LL[l].Side = FarSide;
   		 		for(r=0; r<src->LL[l].nR; r++) {
					PHI = farSidePhaseGet(src->LL[l].data[r].PHI, src->LL[l].nn, src->LL[l].Side, src->Pole);
					F   = src->LL[l].data[r].F;
       		   		dst->LL[l].data[r].Re = F*cos(PHI); 
            		dst->LL[l].data[r].Im = F*sin(PHI);
            		dst->LL[l].data[r].F   = F;
            		dst->LL[l].data[r].PHI = PHI;
				}
			}
			break;
		}
	}
}
