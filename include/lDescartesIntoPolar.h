#ifndef __L_DESCARTES_INTO_PLAR_H
#define __L_DESCARTES_INTO_PLAR_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lDecartesIntoPolar.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lDecartesIntoPolar.h 
#%Z% Attention
#%Z%
*/

/* struct begin */
typedef struct DescartesCoord {
	double x;	
	double y;	
	double z;	
} DescartesCoord;

typedef struct PolarCoord {
	double r;	
	double theta;	
	double phi;	
} PolarCoord;

typedef struct lDescartesIntoPolarInfo {
	DescartesCoord centre;
	DescartesCoord xaxis;
	DescartesCoord yaxis;
	DescartesCoord zaxis;
	DescartesCoord xaxisInv;
	DescartesCoord yaxisInv;
	DescartesCoord zaxisInv;
} lDescartesIntoPolarInfo;
/* struct end */

/* prototype begin */ 
extern void lDescartesAxisCalc(lDescartesIntoPolarInfo* linfo, int mode);
extern PolarCoord lDescartesCoordIntoPolarCoord(DescartesCoord p, lDescartesIntoPolarInfo info, int mode);
extern DescartesCoord lPolarCoordIntoDescartesCoord(PolarCoord p, lDescartesIntoPolarInfo info, int mode);
/* prototype end */

#endif /* __L_DESCARTES_INTO_PLAR_H */
