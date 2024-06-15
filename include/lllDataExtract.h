#ifndef LLLDATA_EXTRACT_H
#define LLLDATA_EXTRACT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#include "genUtil.h"
#include "llData.h"

/* struct begin */
typedef struct lllDataExtractInfo {
	int n;
	int l;
} lllDataExtractInfo;
/* struct end */

/* prototype begin */

extern void lllDataExtract(llData* out, llData* in, lllDataExtractInfo* info, int mode);

/* prototype end */

#endif /* LLLDATA_EXTRACT_H */
