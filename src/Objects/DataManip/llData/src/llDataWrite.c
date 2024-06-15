#include <stdio.h>
#include <math.h>
#include "llData.h"
#include "genUtil.h"

void
llDataFileWrite(FILE* fpt, llData* ll, llDataParaTypeInteger* status)
{
	int  headerFlag;
	llDataParaTypeInteger l;	
	llDataParaTypeInteger k, R;
	llDataParaTypeReal   phi;

	headerFlag = 0;
	if(NULL==fpt) {
		llDataError("File Pointer is NULL in llDataFileWrite");
		return;
	}
	for(l=0; l<ll->llMax; l++) {
		if(ll->LL[l].Side==NearSide) {
			fprintf(fpt, "LAYERLINE%4d NEAR", (int)l);
		} else if(ll->LL[l].Side==FarSide) {
			fprintf(fpt, "LAYERLINE%4d FAR ", (int)l);
		} else if(ll->LL[l].Side==AverageSide) {
			fprintf(fpt, "LAYERLINE%4d AVE ", (int)l);
		} else {
			llDataError("Not Suppoted Side in llDataFileWrite");
			return;
		}
		for(k=0; k<80; k++) {
			fprintf(fpt, ".");
		}
		fprintf(fpt, "%12.5e%5d%5d\n", ll->LL[l].Weight, (int)ll->LL[l].nn, (int)ll->LL[l].nl);
		for(R=0; R<ll->LL[l].nR; R++) {
			phi = NORMAL_PHASE(ll->LL[l].data[R].PHI);
			fprintf(fpt, LLDataFormat, ll->LL[l].data[R].RR, ll->LL[l].data[R].F, phi*DEGREE);
		}
		if(ll->LL[l].nR==0) {
			fprintf(fpt, LLDataFormat, 0.0, 0.0, 0.0);
		}
		fprintf(fpt, LLDataFormat, 0.0, 0.0, 0.0);
	}
}
