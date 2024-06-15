/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataRead ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "llData.h"
#undef DEBUG
#include "genUtil.h"

extern void _llDataFileRead0(FILE* fpt, llData* ll, llDataParaTypeInteger* status);

void
llDataFileReadFollowingAttributes(FILE* fpt, llData* ll, llDataAttributes* attr, llDataParaTypeInteger* status)
{
	llData lltmp;
	llDataParaTypeInteger l, ltmp;	
	llDataParaTypeInteger R;
	llDataParaTypeReal    Fmax;
	double re, im;

	llDataFileRead(fpt, &lltmp, status);

	for(l=0; l<ll->llMax; l++) {
		ltmp = llDataLayerNumberGet(&lltmp, ll->LL[l].nn, ll->LL[l].nl);
		if(0<=ltmp) {
			for(R=0; R<ll->LL[l].nR; R++) {
				llDataValueGet(&lltmp, ltmp, ll->LL[l].data[R].RR, &re, &im);
				ll->LL[l].data[R].Re  = re; 
				ll->LL[l].data[R].Im  = im;
			}
		} else {
			for(R=0; R<ll->LL[l].nR; R++) {
				ll->LL[l].data[R].Re  = 0.0; 
				ll->LL[l].data[R].Im  = 0.0;
			}
		}
	}
	llDataFandPHISet(ll);
	llDataFree(&lltmp);
}

void
llDataFileReadFollowingllData(FILE* fpt, llData* ll, llData* Ref, llDataParaTypeInteger* status)
{
	llData lltmp;
	int l1, l2, iR;
	double re, im;

	llDataFileRead(fpt, &lltmp, status);
	llDataInitWithReference(ll, Ref);
	
	for(l1=0; l1<ll->llMax; l1++) {
		for(l2=0; l2<lltmp.llMax; l2++) {
			if(ll->LL[l1].nn == lltmp.LL[l2].nn
			 &&ll->LL[l1].nl == lltmp.LL[l2].nl) {
				for(iR=0; iR<ll->LL[l1].nR; iR++) {
					llDataValueGet(&lltmp, l2, ll->LL[l1].data[iR].RR, &re, &im);
					ll->LL[l1].data[iR].Re = re;
					ll->LL[l1].data[iR].Im = im;
				}
			}
		}
	}
	llDataFandPHISet(ll);
	llDataFree(&lltmp);
}

void
llDataFileRead(FILE* fpt, llData* ll, llDataParaTypeInteger* status)
{
	char s[DefaultStringLength];
	llDataParaTypeInteger l;	
	llDataParaTypeInteger R;
	llDataParaTypeReal    Fmax;

	if(NULL==fpt) {
		llDataError("File Pointer is NULL in llDataFileRead");
		return;
	}
	_llDataFileRead0(fpt, ll, status);

	fseek(fpt, 0L, SEEK_SET);
	for(l=0; l<ll->llMax; l++) {
		/* read a header of each layer line */
		if(EOF==fgets(ll->LL[l].Head, DefaultStringLength, fpt)) {
			break;
		}
		if(ll->LL[l].Head[SidePosition]=='N') {
			ll->LL[l].Side = NearSide;
		} else if(ll->LL[l].Head[SidePosition]=='F') {
			ll->LL[l].Side = FarSide;
		} else if(ll->LL[l].Head[SidePosition]=='A') {
			ll->LL[l].Side = AverageSide;
		} else {
			break;
		}
		ll->LL[l].Weight = atof(ll->LL[l].Head + WeightPosition);
		ll->LL[l].nn 	 = atoi(ll->LL[l].Head + NNPosition);
		ll->LL[l].nl	 = atoi(ll->LL[l].Head + NLPosition); 

		/* read data */
		Fmax = 0;
		for(R=0; R<ll->LL[l].nR; R++) {
			if(EOF==fgets(s, DefaultStringLength, fpt)) {
				break;	
			}
			ll->LL[l].data[R].RR  = atof(s + RRPosition);
			ll->LL[l].data[R].F	  = atof(s + FPosition); 
			ll->LL[l].data[R].PHI = atof(s + PHIPosition)*RADIAN; 
			if(Fmax<ll->LL[l].data[R].F) {
				Fmax = ll->LL[l].data[R].F;
			}
			ll->LL[l].data[R].Re  = ll->LL[l].data[R].F*cos(ll->LL[l].data[R].PHI);
			ll->LL[l].data[R].Im  = ll->LL[l].data[R].F*sin(ll->LL[l].data[R].PHI);
			/*
			DEBUGPRINT4("%f %f %f %f\n",
				ll->LL[l].data[R].F,
				ll->LL[l].data[R].PHI,
				ll->LL[l].data[R].Re,
				ll->LL[l].data[R].Im);
			*/
		}

		/* Set Layer Information */
		ll->LL[l].Fmax = Fmax;
		DEBUGPRINT4("%d: %f %f %f in llDataRead\n", l, ll->LL[l].RMin, ll->LL[l].RMax, ll->LL[l].delBR);
		/* read tailer */
		if(ll->LL[l].nR==0) {
			fgets(s, DefaultStringLength, fpt);
		}
		fgets(s, DefaultStringLength, fpt);
	}
	llDataRRInfoSet(ll);	
}

void 
_llDataFileRead0(FILE* fpt, llData* ll, llDataParaTypeInteger* status)
{
	char s[DefaultStringLength];
	llDataParaTypeInteger l;	
	llDataParaTypeInteger R, RMax;
	float RR, oldRR;
	
	if(NULL==fpt) {
		llDataError("File Pointer is NULL in _llDataFileRead0");
		return;
	}

	fseek(fpt, 0L, SEEK_SET);
	RMax = 0;
	l = 0;
	while(1) {	
		if(EOF==fgets(s, DefaultStringLength, fpt)) {
			fprintf(stderr, "Not supported Side in llData File: %c\n", s[SidePosition]);
			break;
		}
		if(s[SidePosition]=='N' || s[SidePosition]=='F' || s[SidePosition]=='A') {
			;
		} else {
			break;
		}

		R = 0;
		while(1) {	
			if(EOF==fgets(s, DefaultStringLength, fpt)) {
				break;
			}
			RR  = atof(s + RRPosition);
			if(RR == 0.0 && R != 0) {
				R++;
				break;
			}
			R++;
		}
		if(RMax<R) {
			RMax = R;
		}

		l++;
	}
	ll->llMax = l;
    ll->nRMax = RMax;
	llDataHeaderInit(ll);

	fseek(fpt, 0L, SEEK_SET);
	for(l=0; l<ll->llMax; l++) {	
		/* header read */	
		if(EOF==fgets(s, DefaultStringLength, fpt)) {
			ll->LL[l].nR = 0;
			break;
		}
		if(s[SidePosition]!='N' && s[SidePosition]!='F' && s[SidePosition]!='A') {
			fprintf(stderr, "Not supported Side in llData File: %c\n", s[SidePosition]);
			exit(EXIT_FAILURE);
		}
		R = 0;
		while(1) {
			if(EOF==fgets(s, DefaultStringLength, fpt)) {
				break;
			}
			RR  = atof(s + RRPosition);
			if(RR == 0.0 && R != 0) {
				if(oldRR==RR) {
					R = 0;
				}
				break;
			}
			oldRR = RR;
			R++;
		}
		ll->LL[l].nR = R;
		DEBUGPRINT2("in llDataRead0: ll:%d nR%d\n", l, ll->LL[l].nR);
	}
	llDataDataInit(ll);
    ll->Weight = 1.0;
	ll->rScale = 1.0;
}
