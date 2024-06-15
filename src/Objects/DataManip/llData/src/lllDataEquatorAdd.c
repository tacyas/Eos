
#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataEquatorAdd.h"

void lllDataEquatorAdd(llData* out, llData* in, int mode)
{
	int l, l00;
	int R;
	double Re, Im;

	/* Set llMax and initialize header area */
	*out = *in;
	out->llMax = 1;
	llDataHeaderInit(out);

	l00 = llDataLayerNumberGet(in, 0, 0);
	out->LL[0] = in->LL[l00];
	llDataDataInit(out);
	llDataRRSet(out);
	lllDataClear(out);

	/* Merge */
	for(l=0; l<in->llMax; l++) {
		DEBUGPRINT1("ll Number=%d\n",l);
		if(in->LL[l].nl==0) {
			DEBUGPRINT1("at l=0 in ll Number=%d\n",l);
			for(R=0; R<out->LL[0].nR; R++) {
				DEBUGPRINT1("at l=0 R=%d\n",R);
				llDataValueGet(in, l, out->LL[0].data[R].RR, &Re, &Im);
				out->LL[0].data[R].Re += Re;
				out->LL[0].data[R].Im += Im;
				DEBUGPRINT2("Re=%15.6f:Im=%15.6f\n",Re,Im);
			}
		}
	}
	llDataFandPHISet(out);
}
