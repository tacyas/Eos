#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "llData.h"
#include "eosString.h"
#include "genUtil.h"
#include "ctfInfo.h"
#define SECTION_MARK " \t,"
#include "File.h"

/* struct begin */  
typedef struct lllDataCTFCompensateInfo {
		long flagIn;
		char* In;
		FILE* fptIn;
		long flagIn1;
		char* In1;
		FILE* fptIn1;
		long flagIn2;
		FILE* fptIn2;
		long flagOut;
		char* Out;
		FILE* fptOut;
		long flagtruePitch;
		float truePitch;
		long flagmode;
		long mode;
		long flagconfigFile;
		FILE* fptconfigFile;
} lllDataCTFCompensateInfo;
/* struct end */

/* prototype begin */
extern void llDataCTFSet(llData* llInfo, FILE* fpt);
extern void llDataCTFSet2(llData* llInfo, FILE* fpt);

extern void configFileRead(FILE* fpt, lllDataCTFCompensateInfo* linfo);
extern void configFileUsage(FILE* fpt);

/* prototype end */
