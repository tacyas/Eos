/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataSingleCTFCompensation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataSingleCTFCompensation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataSingleCTFCompensation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "llData.h"
#include "lllDataCTFCompensation.h"

void
lllDataSingleCTFCompensationModePrint(FILE* fpt)
{
	fprintf(fpt, "----- Mode -----\n");
	fprintf(fpt, "    0: 1\n");
	fprintf(fpt, "    1: CTFi /|CTFi|\n");
}

void
lllDataSingleCTFCompensation(llData* llOut, llData* llIn, lllDataSingleCTFCompensationInfo info, int mode)
{
    long ll, iR;
    double CTF;
    double F, Re, Im, phi;

	DEBUGPRINT1("----- lllDataSingleCTFCompensation : %d -----\n", mode);
	if(llIn->RValueSet) {
		llDataRValueSet(llIn, 0);
	}
    for(ll=0; ll<llIn->llMax; ll++) {
        for(iR = 0; iR<llIn->LL[ll].nR; iR++) {
            F   = llIn->LL[ll].data[iR].F;
            phi = llIn->LL[ll].data[iR].PHI;
			CTF = 1.0;
			if(0 < F) {
				switch(mode) {
					case 0: {
#ifdef DEBUG
						if(ll==0 && iR<1) {
							DEBUGPRINT("No Phase Correction");
						}
#endif
						CTF = 1.0;
						break;
					}
					case 1:  {
						if(info.flagllCTF) {
#ifdef DEBUG
							if(ll==0 && iR<1) {
								DEBUGPRINT2("CTF: R: %f CTF: %f\n", \
									llIn->LL[ll].data[iR].R, info.llCTF.LL[ll].data[iR].Re);
							}
#endif
					    	if(info.llCTF.LL[ll].data[iR].Re < 0) {
								CTF = -1;	
							} else {
								CTF =  1;	
							}
						} else { 
						 	CTF = ctfFunction(&info.CTF, llIn->LL[ll].data[iR].R, 0); 	
#ifdef DEBUG
							if(ll==0 && iR<1) {
								DEBUGPRINT2("CTF: R: %f CTF: %f\n", llIn->LL[ll].data[iR].R, CTF);
							}
#endif
							if(CTF<0) {
								CTF = -1;
							} else {
								CTF =  1;
							}
						}
						break;
					}
					default: {
                       	ERRORPRINT1("Not supported mode: %d\n", mode);
						break;
					}
				} 
                Re = CTF*F*cos(phi);
                Im = CTF*F*sin(phi);
            } else {
				Re = 0.0;
				Im = 0.0;
			}
#ifdef DEBUG
			if(ll==0 && iR<1) {
				DEBUGPRINT4("(%f, %f) <- (%f, %f) at (0, 0)\n", 
					Re, Im, 
					llIn->LL[ll].data[iR].Re, 
					llIn->LL[ll].data[iR].Im 
					);
			}
#endif
			llOut->LL[ll].data[iR].Re = Re;
            llOut->LL[ll].data[iR].Im = Im;
        }
    }
	llDataFandPHISet(llOut);
}
