/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataDifferenceCalc.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataDifferenceCalc.h 
#%Z% Attention
#%Z%
*/
#include "llData.h"
#include "Vector.h"

/* struct begin */

typedef struct lllDataDifferenceCalcInfo {
	double A; /* test = A*ref */
} lllDataDifferenceCalcInfo;

/* struct end */

/* prototype begin */
/* 
	dst = 1/A * test(a) - ref(b) 
	
	mode: 0 : allocation of dst
		  1 : no allocation of dst
*/
extern double lllDataDifferenceCalcWithNormalizing(
	llData* dst, 
	llData* newa, 
	llData* a, 
	llData* b, 
	lllDataDifferenceCalcInfo* linfo, 
	int mode);

/* 
	dst = a - b 

	mode: 0 : allocation of dst
		  1 : no allocation of dst
*/

extern double lllDataDifferenceCalc(
	llData* dst, 
	llData* a, 
	llData* b, 
	int mode);

/* P-Value */
extern double lllDataDifferencePValueCalc(llData* a, llData* b, int mode);
extern double lllDataDifferencePValueCalc2(floatVector* fv, llData* a, llData* b, int mode);

/* R-Value */
extern double lllDataDifferenceRValueCalc(llData* a, llData* b, int mode);

/* prototype end */

