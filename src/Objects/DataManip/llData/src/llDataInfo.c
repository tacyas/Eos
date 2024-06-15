#include <stdlib.h>
#include "../inc/llData.h"
#include "genUtil.h"
/*
	llDataInfoPrint(
		FILE*   fpt,	File Pointer to be output
		llData* ll,     LayerLineData Pointer to be treated
		long    index,	Which Layer Line Data: -1, All Layer Line Data 
		long    mode	What infomation do you want?
		);  

		mode:   1	:	Total Layer Line Infomation	
				2	:	Information of Each Layer Line	
				4	:	Data of Each Layer Line
				8	:
*/

#define PLOT_SCALE (50.0)
extern void _llDataInfoPrintMode1(FILE* fpt, llData* ll);
extern void _llDataInfoPrintMode2(FILE* fpt, llData* ll, long l);
extern void _llDataInfoPrintMode4(FILE* fpt, llData* ll, long l);
extern void _llDataInfoPrintMode8(FILE* fpt, llData* ll, long l);

void
llDataInfoPrintUsage(FILE* fpt)
{
	fprintf(fpt, "----- mode -----\n");
	fprintf(fpt, "1	: Total Layer Line Infomation\n");	
	fprintf(fpt, "2	: Information of Each Layer Line\n");
	fprintf(fpt, "4	: Data of Each Layer Line\n");
}

void
llDataInfoPrint(FILE* fpt, llData* ll, long index, long mode)
{
	long l;

	if(mode&0x0001) {
		_llDataInfoPrintMode1(fpt, ll);
	}
	if(index==-1) {
		for(l=0; l<ll->llMax; l++) {
			if(mode&0x0002) {
				_llDataInfoPrintMode2(fpt, ll, l);
			}
			if(mode&0x0004) {
				_llDataInfoPrintMode4(fpt, ll, l);
			}
		}			
	} else {
		if(mode&0x0002) {
			_llDataInfoPrintMode2(fpt, ll, index);
		}
		if(mode&0x0004) {
			_llDataInfoPrintMode4(fpt, ll, index);
		}
	}
    if(mode&0x008) {
        _llDataInfoPrintMode8(fpt, ll, index);
    }
}

void
_llDataInfoPrintMode1(FILE* fpt, llData* ll)
{
	fprintf(fpt, "Total Layer Number : %d\n", (int)ll->llMax); 
}

void
_llDataInfoPrintMode2(FILE* fpt, llData* ll, long l)
{
	fprintf(fpt, "Comment: %s\n", ll->LL[l].Head);
	if(ll->LL[l].Side==NearSide) {
		fprintf(fpt, "Side: NEAR\n");
	} else if(ll->LL[l].Side==NearSide) {
		fprintf(fpt, "Side: NEAR\n");
	} else if(ll->LL[l].Side==AverageSide) {
		fprintf(fpt, "Side: AVG \n");
	} else {
		fprintf(fpt, "Not Supported Side\n");
    }
	fprintf(fpt, "l:  %d\n", (int)ll->LL[l].nl);
	fprintf(fpt, "n:  %d\n", (int)ll->LL[l].nn);
	fprintf(fpt, "w:  %f\n", ll->LL[l].Weight);
	fprintf(fpt, "nR: %d\n", ll->LL[l].nR);
	fprintf(fpt, "Rmin: %f\n", ll->LL[l].RMin);
	fprintf(fpt, "Rmax: %f\n", ll->LL[l].RMax);
	fprintf(fpt, "dR:   %f\n", ll->LL[l].delBR);
}

void
_llDataInfoPrintMode4(FILE* fpt, llData* ll, long l)
{
	long  r, i;
	float FMax, FMin;
	
	FMin = FMax = ll->LL[l].data[0].F;
	for(r=0; r<ll->LL[l].nR; r++) {
		if(FMax<ll->LL[l].data[r].F) {
			FMax = ll->LL[l].data[r].F;
		}
		if(FMin>ll->LL[l].data[r].F) {
			FMin= ll->LL[l].data[r].F;
		}
	}					
	for(r=0; r<ll->LL[l].nR; r++) {
		fprintf(fpt, LLDataFormat0, ll->LL[l].data[r].RR, 
									ll->LL[l].data[r].F, 
									ll->LL[l].data[r].PHI*DEGREE);
		fprintf(fpt, " |");
		for(i=0; i<(ll->LL[l].data[r].F-FMin)/(FMax-FMin)*PLOT_SCALE; i++) {
			fprintf(fpt, " ");
		}
		fprintf(fpt, "*");
		if(i<PLOT_SCALE) {
			for(i+=1; i<PLOT_SCALE; i++) {
				fprintf(fpt, " ");
			}
			fprintf(fpt, "|");
		}
		fprintf(fpt, "\n");
	}
}

void
_llDataInfoPrintMode8(FILE* fpt, llData* ll, long l)
{
	long  r;
	float FMax, FMin;
	
	FMin = FMax = ll->LL[l].data[0].F;
	for(r=0; r<ll->LL[l].nR; r++) {
		if(FMax<ll->LL[l].data[r].F) {
			FMax = ll->LL[l].data[r].F;
		}
		if(FMin>ll->LL[l].data[r].F) {
			FMin= ll->LL[l].data[r].F;
		}
	}					
	for(r=0; r<ll->LL[l].nR; r++) {
		fprintf(fpt, LLDataFormat1, ll->LL[l].data[r].RR, 
									ll->LL[l].data[r].F, 
									ll->LL[l].data[r].PHI*DEGREE);
    	fprintf(fpt, "\n");
	}
}
