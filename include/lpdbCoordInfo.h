/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lpdbCoordInfo.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lpdbCoordInfo.h 
#%Z% Attention
#%Z%
*/

#include "pdbFile.h"

/* prototype begin */

extern int lpdbDistanceCheck(pdbFile* pdb, pdbCoord p, pdbFileParaTypeReal distance, int mode);
extern int lpdbDistanceNear(pdbFile* pdb, pdbCoord p, pdbFileParaTypeReal distance, int mode);
extern int lpdbDistanceFar(pdbFile* pdb, pdbCoord p, pdbFileParaTypeReal distance, int mode);

/* prototype end */
