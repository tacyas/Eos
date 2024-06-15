
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "llData.h"
#define UNDEBUG
#include "genUtil.h"

void 
lllDataIntensityInformationGet(llData* in, lllDataIntensityInformation* data, int mode)
{
	int l, R;
	double Fintegral;
	double Peak;

	for(l=0; l<in->llMax; l++) {
		data->onedata[l].LL = l;
		data->onedata[l].n  = in->LL[l].nn;
		data->onedata[l].l  = in->LL[l].nl;
		
		Fintegral = 0.0;
		Peak = in->LL[l].data[0].F;
		for(R=0; R<in->LL[l].nR; R++) {
			Fintegral  +=  in->LL[l].data[R].F;
				if (Peak <= in->LL[l].data[R].F){
					Peak = in->LL[l].data[R].F;
				}
		}
		data->onedata[l].I    = Fintegral;
		data->onedata[l].Peak = Peak;
		DEBUGPRINT5("ll Number=%d: (n,l)=(%d, %d): Fintegral = %15.6f: Peak = %15.6f\n",
					data->onedata[l].LL, data->onedata[l].n, data->onedata[l].l,
					data->onedata[l].I, data->onedata[l].Peak);
	}
}


