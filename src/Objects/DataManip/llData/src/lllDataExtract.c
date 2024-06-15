
#define UNDEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataExtract.h"

void lllDataExtract(llData* out, llData* in, lllDataExtractInfo* info, int mode)
{
	int l, NL;
	int R;
	double Re, Im;

	/* Set llMax and initialize header area */
	*out = *in;
	out->llMax = 1;
	llDataHeaderInit(out);

	NL = llDataLayerNumberGet(in, info->n , info->l);
	out->LL[0] = in->LL[NL];
	llDataDataInit(out);
	llDataRRSet(out);
	lllDataClear(out);

	/* Extract */
	for(R=0; R<out->LL[0].nR; R++) {
		llDataValueGet(in, NL, out->LL[0].data[R].RR, &Re, &Im);
		out->LL[0].data[R].Re += Re;
		out->LL[0].data[R].Im += Im;
		DEBUGPRINT2("Re=%15.6f:Im=%15.6f\n",Re,Im);
	}
	llDataFandPHISet(out);

}
