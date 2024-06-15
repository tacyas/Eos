#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/ltlgData.h"
#undef DEBUG
#include "genUtil.h"
#include "eosString.h"

void
ltlgDataWeightModifyFromFile(ltlgData* ltlg, FILE* fpt, long mode)
{
	char s[1024];
	ltlgDataLLDataInfo w;

	if(NULL==fpt) {
		fprintf(stderr, "File Not Opened in ltlgDataWeightModify\n");
		exit(EXIT_FAILURE);
	}
	while(NULL!=stringGetFromFile(s, "", fpt, stdout, 3)) {
		if(0==stringLength(s)) {
			return;
		} else {
			w.NN = stringGetNthIntegerData(s, 1, " \t,");
			w.NL = stringGetNthIntegerData(s, 2, " \t,");
			w.WT = stringGetNthRealData(s, 3, " \t,");
		}
		DEBUGPRINT3("%d %d %f\n", w.NN, w.NL, w.WT);
		ltlgDataWeightModify(ltlg, w, 0);
	}
}

void
ltlgDataWeightModify(ltlgData* ltlg, ltlgDataLLDataInfo Weight, long mode)
{
    ltlgDataParaTypeInteger ll, r;
	
	switch(mode) {
		case 0 :{
		    for(ll=0; ll<ltlg->ll.Max; ll++) {
		        if(Weight.NL==ltlg->llInfo[ll].NL
				 &&Weight.NN==ltlg->llInfo[ll].NN) {
		            ltlg->llInfo[ll].WT = Weight.WT;
		            for(r=0; r<ltlg->r.n; r++) {
		                ltlg->ltlg[ll][r].Re *= Weight.WT;
		                ltlg->ltlg[ll][r].Im *= Weight.WT;
		            }
		        }
		    }
			break;
		}
		case 1 :{
		    for(ll=0; ll<ltlg->ll.Max; ll++) {
		        if(Weight.NL==ltlg->llInfo[ll].NL
				&& 0!=ltlg->llInfo[ll].WT) {
		            ltlg->llInfo[ll].WT = Weight.WT;
		            for(r=0; r<ltlg->r.n; r++) {
		                ltlg->ltlg[ll][r].Re *= Weight.WT;
		                ltlg->ltlg[ll][r].Im *= Weight.WT;
		            }
		        }
		    }
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode (%ld) in ltlgDataWeightModify\n", mode);
		}
	}
}

void
ltlgDataWeightOfNEqualLOnly(ltlgData* ltlg)
{
    ltlgDataParaTypeInteger ll, r;

    for(ll=0; ll<ltlg->ll.Max; ll++) {
        if(ltlg->llInfo[ll].NN!=ltlg->llInfo[ll].NL) {
            ltlg->llInfo[ll].WT = 0.0;
            for(r=0; r<ltlg->r.n; r++) {
                ltlg->ltlg[ll][r].Re = 0.0;
                ltlg->ltlg[ll][r].Im = 0.0;
            }
        }
    }
}

