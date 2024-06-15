/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataRescaling.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataRescaling.h 
#%Z% Attention
#%Z%
*/
#include "llData.h"

/* struct begin */

typedef struct lllDataRescalingInfo {
     llDataParaTypeReal delBR;
	 llDataParaTypeReal rScale;
} lllDataRescalingInfo;

/* struct end */

/* prototype begin */

extern void lllDataRescaling(llData* llOut, llData* llIn, lllDataRescalingInfo linfo, long mode);

/* prototype end */
