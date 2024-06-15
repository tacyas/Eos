/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataAxisSearchAndAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataAxisSearchAndAverage 
#%Z% Attention
#%Z%	Mode: 0: Search and Average  
#%Z%	Mode: 1: No Search and Average following Parameter  
#%Z%
*/

static char __sccs_id[] = "%Z%lllDataAxisSearchAndAverage ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "lllDataAxisSearch.h"

void
lllDataAxisSearchAndAverage(llData* avg, llData* nea, llData* far, llDataFittedParam* param, long mode)
{
	llData neaShift;
	llData farShift;
	
	DEBUGPRINT("FitAndAverage\n")
	if(param->Para.flagLLTable) {
		DEBUGPRINT("Already LLTable");
	} else if(mode&lllDataAxisSearchModeSearchProcessSameLLStructure) {
		DEBUGPRINT("Same Structure : LLTable");
		param->Para.llTable = llDataTableBetweenTwollDataCreate(nea, far, 1);
	} else {
		DEBUGPRINT("Same Structure : LLTable");
		param->Para.llTable = llDataTableBetweenTwollDataCreate(nea, far, 0);
	}
	param->Para.flagLLTable = nea->llMax;

	switch(lllDataAxisSearchModeSearchAndAverage&mode) {
		case 0: {
			lllDataAxisSearch(nea, far, param, (lllDataAxisSearchModeSearchProcess&mode)|QVALUE_MODE); 
			break;
		}
		case lllDataAxisSearchModeNoSearch: {
			break;
		}
		case lllDataAxisSearchModeQ2Search: {
			lllDataAxisSearch(nea, far, param, (lllDataAxisSearchModeSearchProcess&mode)|Q2VALUE_MODE); 
			break;
		}
		default: {
			ERRORPRINT1("Not supported mode in lllDataAxisSearchAndAverage: %ld", lllDataAxisSearchModeSearchAndAverage&mode);
		}
	}
	llDataInitWithReference(&neaShift, nea);
	llDataInitWithReference(&farShift, far);

	lllDataPhaseShiftIntra(&neaShift, nea, param);
	lllDataPhaseShiftIntra(&farShift, far, param);

	lllDataAdd2(avg, &neaShift, &farShift);
	lllDataDevidedByReal(avg, 2.0);

	llDataFree(&neaShift);
	llDataFree(&farShift);
}

