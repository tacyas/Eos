
#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataCompare.h"

void 
lllDataCompare(lllDataIntensityInformation* data,
			   lllDataCompareInfo* linfo,
			   int mode)
{
	int i1, i2;
	int ll=0;
	double nlOrigin=0;
	double nlNotOrigin=0;
	
	/* (n, l) = (0, 0) Reflection */
	for(i1=0; i1<linfo->FilamentNumber; i1++) {			
		DEBUGPRINT2("#%d (n,l)=(0,0) %15.6f\n", i1, data[i1].onedata[0].I);
		nlOrigin += data[i1].onedata[0].I;
	}
	linfo->OriginReflection = nlOrigin/linfo->FilamentNumber;
	DEBUGPRINT2("total (n,l)=(0,0) %15.6f : avg total %15.6f \n", nlOrigin, linfo->OriginReflection);

	/* Not (n, l) = (0, 0) Reflection */
	for(i1=0; i1<linfo->FilamentNumber; i1++) {			
		for(i2=1; i2<data[i1].llMax; i2++) {			
			nlNotOrigin += data[i1].onedata[i2].I;
			ll++; 
			DEBUGPRINT3("#%d  ll=%d  (n,l)NOT(0,0) %15.6f\n", i1, i2, data[i1].onedata[i2].I);
		}
	}
	linfo->OtherReflection = nlNotOrigin/ll;
	DEBUGPRINT3("total not (n,l)=(0,0) %15.6f : avg total %15.6f (ll=%d)\n",
				nlNotOrigin, linfo->OtherReflection, ll);
	
	/* Ratio */
	linfo->ratio = linfo->OriginReflection/linfo->OtherReflection;
	DEBUGPRINT1("ratio %15.6f \n", linfo->ratio);

}

