/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfZeroPoint ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfZeroPoint 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfZeroPoint ver%I%; Date:%D% %Z%";

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mrcImage.h"
#define DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "ctfInfo.h"
#include "ctfZeroPoint.h"

float
ctfZeroPoint(ctfInfo* info, ctfInfoZeroPoint* infoZeroPoint, long mode)
{
	float countN;
	float R, Rfinal;
	float ctf, formerCtf;

	if(0>=infoZeroPoint->dR) {
		fprintf(stderr, "dR is zero!\n");
		return -1;
	}
	countN = 0;
	Rfinal = -1;
	formerCtf  = ctfFunction(info, 0, 0); 
	for(R=0; R<infoZeroPoint->RMax; R+=infoZeroPoint->dR) {
		ctf = ctfFunction(info, R+infoZeroPoint->dR, 0);
		if(ctf==0){
			countN++;
		} else if(ctf*formerCtf<0) {
			countN++;		
		}
		if(infoZeroPoint->N==countN){
			/*
				modified by tac because wrong 
					Rfinal =  R - infoZeroPoint->dR/2.0;
			*/
			if(0!=fabs(formerCtf-ctf)) {
				Rfinal = (R*(0-ctf) + (R+infoZeroPoint->dR)*(formerCtf-0))/(formerCtf-ctf);
			} else {
				Rfinal = R + infoZeroPoint->dR/2.0;
			} 
			break;
		}
		formerCtf = ctf;
	}
	if(infoZeroPoint->N==countN) {
		return Rfinal;
	} else {
		return -1;
	}
}
