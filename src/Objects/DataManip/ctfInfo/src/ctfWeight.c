#include <stdio.h>
/*
# ctfWeight.c  1.1
# The latest update : 04/25/96 at 21:26:44
#
#@(#) ctfWeight ver 1.1
#@(#) Created by tacyas
#@(#)
#@(#) Usage : ctfWeightForCorrection 
#@(#) Attention
#@(#)     Mode 
#@(#)        0: weight = 1.0;
#@(#)        1: weight = CTF/|CTF|;
#@(#)        2: weight = CTF;
#@(#)        3: weight = 1/CTF;
#@(#)        4: weight = CTF/{SQR(CTF)+SQR(WhiteNoise)};
#@(#)        5: weight = SQR(CTF);
#@(#)
*/
static char __sccs_id[] = "@(#)ctfWeightForCorrection ver1.1; Date:96/04/25 @(#)";

#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include "mrcImage.h"
#define DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "../inc/ctfInfo.h"

void
ctfWeightForCorrectionUsage(FILE* fpt)
{
	fprintf(fpt, "mode 0: No Correction\n");
	fprintf(fpt, "mode 1: x ctf/|ctf|, phase flipping\n");
	fprintf(fpt, "mode 2: x ctf,       phase flipping and ctf-multiplying\n");
	fprintf(fpt, "mode 3: x 1/ctf    (0.1<|ctf|       phase flipping and ctf-divided\n");
	fprintf(fpt, "mode 4: x ctf/(SQR(ctf)+SQR(NS))    phase-flipping + Winner Filtering \n");	
	fprintf(fpt, "mode 5: x SQR(ctf) x ctf/|ctf|      phase-flipping + ctf-Weighted\n");
	fprintf(fpt, "mode 6: x 1/|ctf|  (0.1<|ctf|)      No phase-flipping + ctf-divided\n");
	fprintf(fpt, "mode 7: x |ctf|/(SQR(ctf)+SQR(NS))  No phase flipping + Winner Filtering \n");
	fprintf(fpt, "mode 8: x  ctf /(SQR(ctf)+SQR(NS*exp(a*R)))  phase flipping + Winner Filtering + NS-raising \n");
	fprintf(fpt, "mode 9: x |ctf|/(SQR(ctf)+SQR(NS*exp(a*R)))  No phase flipping + Winner Filtering + NS-raising \n");
}

float 
ctfWeightForCorrection2D(ctfInfo* CTFInfo, float X /* A-1 */, float Y /* A-1 */, long mode)
{
	float ctf, weight, R, W;

	DEBUGPRINT1("mode %ld\n", mode);

	if(X==0.0 && Y==0.0) {
		weight = 1.0;
	} 
	switch(mode) {
		case 0: {
			break;
				}	
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7: 
		case 8: 
		case 9: {
			ctf = ctfFunction2D(CTFInfo, X, Y, 0);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode : %ld in ctfWeightForCorrection2D\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}

	switch(mode) {
		case 0: { /* No Correction*/
			weight = 1.0;
			break;
		}
		case 1: { /* Only Phase */
			if(0==ctf) {
				weight = 0.0;
			} else {
				weight = ctf/fabs(ctf);
			}
			break;
		}
		case 2: { /* x CTF */
			if(0==ctf) {
				weight = 0.0;
			} else {
				weight = ctf;
			}
			break;
		}
		case 3: { /* x 1/CTF */
			DEBUGPRINT("in 1/ctf\n");
			if(fabs(ctf)<=0.10) {    /* 1/ctf is less than 10 times */ 
				weight = 0.0;
			} else {
				weight = 1/ctf;
			}
			break;
		}
		case 4: { /* Winer filter : constant s/n  */
			DEBUGPRINT("in Winner\n");
			DEBUGPRINT1("WhiteNoise: %15.6f\n", CTFInfo->WhiteNoise);
			weight = ctf/(SQR(ctf) + SQR(CTFInfo->WhiteNoise));
			break;
		}
		case 5: { /* x |CTF|^2 */
			DEBUGPRINT("in SQR(ctf)\n");
			if(0==ctf) {
				weight = 0.0;
			} else {
				weight = SQR(ctf)*ctf/fabs(ctf);
			}
			break;
		}	
		case 6: { /* 1/ |CTF|*/
			DEBUGPRINT("in SQR(ctf)\n");
			if(fabs(ctf)<0.1) {
				weight = 0.0;
			} else {
				weight = 1.0/fabs(ctf);
			}
			break;
		}	
		case 7: { /* Winer filter : constant s/n  */
			DEBUGPRINT("in Winner\n");
			DEBUGPRINT1("WhiteNoise: %15.6f\n", CTFInfo->WhiteNoise);
			weight = fabs(ctf)/(SQR(ctf) + SQR(CTFInfo->WhiteNoise));
			break;
		}
		case 8: { /* Winer filter : s/n dumping */
			R = sqrt(SQR(X)+SQR(Y));
			W = CTFInfo->WhiteNoise*exp(CTFInfo->WhiteNoiseRaising * R);
			DEBUGPRINT("in Winner\n");
			DEBUGPRINT3("WhiteNoise: %15.6f %15.6f %15.6f\n", CTFInfo->WhiteNoise, CTFInfo->WhiteNoiseRaising, W);
			weight = ctf/(SQR(ctf) + SQR(W));
			break;
		}
		case 9: { /* Winer filter : s/n dumping */
			R = sqrt(SQR(X)+SQR(Y));
			W = CTFInfo->WhiteNoise*exp(CTFInfo->WhiteNoiseRaising*R);
			DEBUGPRINT("in Winner\n");
			DEBUGPRINT3("WhiteNoise: %15.6f %15.6f %15.6f\n", CTFInfo->WhiteNoise, CTFInfo->WhiteNoiseRaising, W);
			weight = fabs(ctf)/(SQR(ctf) + SQR(W));
			break;
		}
	}
	return weight;
}

float
ctfWeightForCorrection(ctfInfo* CTFInfo, float R /* A-1 */, long mode)
{
	float ctf, weight;
	
	DEBUGPRINT1("mode %ld\n", mode);

	if(R==0.0) {
		weight = 1.0;
	}
	switch(mode) {
		case 0: {
			weight = 1.0;
			break;
		}
		case 1: {
			ctf = ctfFunction(CTFInfo, R, 0);
			if(0==ctf) {
				weight = 0.0;
			} else {
				weight = ctf/fabs(ctf);
			}
			break;
		}
		case 2: {
			ctf = ctfFunction(CTFInfo, R, 0);
			if(0==ctf) {
				weight = 0.0;
			} else {
				weight = ctf;
			}
			break;
		}
		case 3: {
			DEBUGPRINT("in 1/ctf\n");
			ctf = ctfFunction(CTFInfo, R, 0);
			if(fabs(ctf)<=0.10) {    /* 1/ctf is less than 10 times */ 
				weight = 0.0;
			} else {
				weight = 1/ctf;
			}
			break;
		}
		case 4: { /* Winer filter : constant s/n  */
			DEBUGPRINT("in Winner\n");
			DEBUGPRINT1("WhiteNoise: %15.6f\n", CTFInfo->WhiteNoise);
			ctf = ctfFunction(CTFInfo, R, 0);
			weight = ctf/(SQR(ctf) + SQR(CTFInfo->WhiteNoise));
			break;
		}
		case 5: {
			DEBUGPRINT("in SQR(ctf)\n");
			ctf = ctfFunction(CTFInfo, R, 0);
			if(0==ctf) {
				weight = 0.0;
			} else {
				weight = SQR(ctf)*ctf/fabs(ctf);
			}
			break;
		}
		case 6: {
			DEBUGPRINT("in 1/fabs(ctf)\n");
			ctf = ctfFunction(CTFInfo, R, 0);
			if(0==ctf) {
				weight = 0.0;
			} else {
				weight = 1.0/fabs(ctf);
			}
			break;
		}
		case 7: { /* Winer filter : constant s/n  */
			DEBUGPRINT("in Winner\n");
			DEBUGPRINT1("WhiteNoise: %15.6f\n", CTFInfo->WhiteNoise);
			ctf = ctfFunction(CTFInfo, R, 0);
			weight = fabs(ctf)/(SQR(ctf) + SQR(CTFInfo->WhiteNoise));
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode : %ld in ctfWeightForCorrection\n", mode);
			exit(EXIT_FAILURE);
		}
	}
	return weight;
}
