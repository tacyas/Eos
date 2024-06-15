/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataAxisSearch.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lllDataAxisSearch.h 
#%Z% Attention
#%Z%
*/

#ifndef LLLDATA_AXIS_SEARCH_H 
#define LLLDATA_AXIS_SEARCH_H

#include "llData.h"
#include "lllDataFit.h"

/* constant begin */  
#define lllDataAxisSearchModeSearchProcess                (0xf0)
#define lllDataAxisSearchModeSearchProcessPrint           (0x10)
#define lllDataAxisSearchModeSearchProcessSameLLStructure (0x20)

#define lllDataAxisSearchModeSearchAndAverage   (0x0f)
#define lllDataAxisSearchModeNoSearch           (0x01)
#define lllDataAxisSearchModeQ2Search           (0x02)
/* constant end */

/* prototype begin */
extern void lllDataAxisSearch(llData* ll1, llData* ll2, llDataFittedParam* p, long mode);
extern void lllDataAxisSearchWithFile(llData* ll1, llData* ll2, llDataFittedParam* p, char* paramFileName, long mode);

extern void lllDataAxisSearch2(llData* ll1, llData* ll2, llDataFittedParam* p, long mode);

extern void lllDataAxisSearchAndAverage(llData* avg, llData* nea, llData* far, llDataFittedParam* p, long mode);
/* prototype end */

#endif /* LLLDATA_AXIS_SEARCH_H */
