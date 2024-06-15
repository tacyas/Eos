/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lhf2000LenzCurrent.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lhf2000LenzCurrent.h 
#%Z% Attention
#%Z%
*/

#include "hf2000.h"

/* struct begin */
typedef struct hf2000LenzCurrent {
	hf2000ParaTypeInteger D;
	hf2000ParaTypeReal    A;
} hf2000LenzCurrent;

typedef struct lhf2000LenzCurrentInfo {
	hf2000LenzCurrent C1;
	hf2000LenzCurrent C2;
	hf2000LenzCurrent C3;
	hf2000LenzCurrent OBJ;
	hf2000LenzCurrent I1;
	hf2000LenzCurrent I2;
	hf2000LenzCurrent P1;
	hf2000LenzCurrent P2;
} lhf2000LenzCurrentInfo;
/* struct end */

/* prototype begin */
extern void  lhf2000LenzCurrentGet(hf2000Info* hf2000, lhf2000LenzCurrentInfo* linfo, int mode);
extern hf2000LenzCurrent lhf2000LenzCurrentGet0(hf2000Info* hf2000, char* s, int mode);
/* prototype end */
