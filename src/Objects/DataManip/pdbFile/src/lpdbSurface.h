#ifndef LPDB_SURFACE_H 
#define LPDB_SURFACE_H 

/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lpdbSurface.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lpdbSurface.h 
#%Z% Attention
#%Z%
*/

#include "pdbFile.h"
#include "lpdb2mrcInfo.h"

/* struct begin */
typedef struct lpdbSurfaceInfo {
	double order;  /* Angstrom */
	int    refine; /* mesh size is equal to order/refine */ 
	int    size;   /* contour surface thickness is equal to order/refine*(2*size+1) */
	double mergin; /* Search Area */
	double weight; /* Weight Value */
	double thresHold; /* exp(-thresHold) */
	int    DensityMode;
} lpdbSurfaceInfo;

typedef enum lpdbSurfaceMode {
	lpdbSurfaceModeSimple=0
} lpdbSurfaceMode;
/* struct end */

/* prototype begin */
extern void lpdbSurfaceAsTemperatureFactor(pdbFile* pdb, lpdbSurfaceInfo* info, lpdbSurfaceMode mode); 
/* prototype end */
#endif /* LPDB_SURFACE_H */
