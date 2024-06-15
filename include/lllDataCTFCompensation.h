/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataCTFCompensation.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lllDataMultiCTFCompensation.h 
#%Z% Attention
#%Z%
*/

#include "llData.h"
#include "lllDataFit.h"
#include "lllDataFitAndAverage.h"
#include "ctfInfo.h"

/* Multi CTF Compensation */

/* constant begin */
typedef enum lllDataMultiCTFCompensationCompensationMode {
	lllDataMultiCTFCompensationModeAbsCTFperSQRCTF = 0,
	lllDataMultiCTFCompensationModeCTFperSQRCTF    = 1
} lllDataMultiCTFCompensationCompensationMode;

typedef enum lllDataMultiCTFCompensationMode {
	lllDataMultiCTFCompensationModeOnlyAverage   = 0,
	lllDataMultiCTFCompensationModeCTFCompensate = 1
} lllDataMultiCTFCompensationMode;
/* constant end */

/* struct begin */

/* Single CTF Compensation */ 
typedef struct lllDataSingleCTFCompensationInfo {
	int     flagllCTF;
	llData  llCTF;
	ctfInfo CTF;
}  lllDataSingleCTFCompensationInfo;

/* struct end */

/* prototype begin */
extern void lllDataMultiCTFCompensation(llData* avg, llData* out, 
										llData* In,  llData ref,
										llDataFittedParam* paraFit,
										lllDataFitAndAverageInfo linfo, 
										lllDataMultiCTFCompensationMode mode);

extern void lllDataMultiCTFCompensationModePrint(FILE* fpt);

extern void lllDataSingleCTFCompensation(llData* out, llData* in, 
			lllDataSingleCTFCompensationInfo linfo,
			int mode);  

/* prototype end */
