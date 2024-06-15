#undef DEBUG
#include "genUtil.h"
#include <math.h>
#include <stdlib.h>
#include "../inc/llData.h"
#include "eosString.h"
#include "genUtil.h"

void
lllDataWeightSet(FILE* fpt, llData* ll1, llDataParaTypeReal w, long mode)
{
    int l, nn, ll;
    double weight;

    char s[GEN_UTIL_MAX_STRING_LENGTH];

	if(mode==0) {
    	for(l=0; l<ll1->llMax; l++) {
			ll1->LL[l].Weight = w;
		}
	}
	
    if(fpt==NULL) {
        return;
    }
    fseek(fpt, 0L, SEEK_SET);
    while(NULL!=stringGetFromFile(s, "", fpt, stderr, 1)) {
        nn = stringGetNthIntegerData(s, 1, " \t,");
        ll = stringGetNthIntegerData(s, 2, " \t,");
        weight = stringGetNthRealData(s, 3, " \t,");
        for(l=0; l<ll1->llMax; l++) {
			if(ll1->LL[l].nn==nn
			&& ll1->LL[l].nl==ll) {
				ll1->LL[l].Weight = weight;
				DEBUGPRINT3("%d %d %f\n", nn, ll, weight);
				break;
			}
		}
	}
}    
