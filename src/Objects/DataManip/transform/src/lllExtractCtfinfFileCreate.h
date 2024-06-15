#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#define UNDEBUG
#include "genUtil.h"
#include "ctfInfo.h"
#include "ctfZeroPoint.h"

/* struct begin */
typedef struct infoDataList {
	float FirstZero;
	long flagFirstZero;
	char* Out;
	FILE* fptOut;
} infoDataList;
/* struct end */

/* prototype begin */
extern void llExtractCtfinfFileCreateI(infoDataList* linfo,
									   ctfInfo* CTFInfo,
								       ctfInfoZeroPoint* CTFInfoZeroPoint);

extern void llExtractCtfinfFileCreateII(infoDataList* linfo,
										ctfInfo* CTFInfo);


/* prototype end */
