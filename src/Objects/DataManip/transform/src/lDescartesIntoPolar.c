/*
# %M% %Y% %I%
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lDescartesIntoPolar ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lDescartesIntoPolar 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lDescartesIntoPolar ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "lDescartesIntoPolar.h"

void
lDescartesAxisCalc(lDescartesIntoPolarInfo* info, int mode)
{
	double angle;
	double disx;
	double disy;
	double disz;
	double det;

	disx = sqrt(SQR(info->xaxis.x)+SQR(info->xaxis.y)+SQR(info->xaxis.z));
	disz = sqrt(SQR(info->zaxis.x)+SQR(info->zaxis.y)+SQR(info->zaxis.z));
	/* Check z and x */
	angle = info->xaxis.x*info->zaxis.x + info->xaxis.y*info->zaxis.y + info->xaxis.z*info->zaxis.z;
	angle = angle/disx/disz;
	angle = acos(angle);
	if(1e-6<fabs(angle-M_PI/2.0)) {
		fprintf(stderr, "angle is not PI/2: %g\n", angle);
	}
	/* z,x -> y */
	info->yaxis.x = info->zaxis.y*info->xaxis.z - info->xaxis.y*info->zaxis.z;	
	info->yaxis.y = info->zaxis.z*info->xaxis.x - info->xaxis.z*info->zaxis.x;	
	info->yaxis.z = info->zaxis.x*info->xaxis.y - info->xaxis.x*info->zaxis.y;	
	DEBUGPRINT3("YAXIS: %g %g %g\n", info->yaxis.x, info->yaxis.y, info->yaxis.z);
	disy = sqrt(SQR(info->yaxis.x)+SQR(info->yaxis.y)+SQR(info->yaxis.z));

	/* Normalization */
	info->xaxis.x /= disx;
	info->xaxis.y /= disx;
	info->xaxis.z /= disx;
	info->yaxis.x /= disy;
	info->yaxis.y /= disy;
	info->yaxis.z /= disy;
	info->zaxis.x /= disz;
	info->zaxis.y /= disz;
	info->zaxis.z /= disz;

	/* Inverse Matrix */
	det = info->xaxis.x*info->yaxis.y*info->zaxis.z
		 +info->yaxis.x*info->zaxis.y*info->xaxis.z
		 +info->zaxis.x*info->xaxis.y*info->yaxis.z
		 -info->zaxis.x*info->yaxis.y*info->xaxis.z
		 -info->yaxis.x*info->xaxis.y*info->zaxis.z
		 -info->xaxis.x*info->zaxis.y*info->yaxis.z;

	info->xaxisInv.x = (info->yaxis.y*info->zaxis.z - info->zaxis.y*info->yaxis.z)/det;		 
	info->xaxisInv.y = (info->yaxis.z*info->zaxis.x - info->zaxis.z*info->yaxis.x)/det;		 
	info->xaxisInv.z = (info->yaxis.x*info->zaxis.y - info->zaxis.x*info->yaxis.y)/det;		 
	info->yaxisInv.x = (info->zaxis.y*info->xaxis.z - info->xaxis.y*info->zaxis.z)/det;		 
	info->yaxisInv.y = (info->zaxis.z*info->xaxis.x - info->xaxis.z*info->zaxis.x)/det;		 
	info->yaxisInv.z = (info->zaxis.x*info->xaxis.y - info->xaxis.x*info->zaxis.y)/det;		 
	info->zaxisInv.x = (info->xaxis.y*info->yaxis.z - info->yaxis.y*info->xaxis.z)/det;		 
	info->zaxisInv.y = (info->xaxis.z*info->yaxis.x - info->yaxis.z*info->xaxis.x)/det;		 
	info->zaxisInv.z = (info->xaxis.x*info->yaxis.y - info->yaxis.x*info->xaxis.y)/det;		 

}

PolarCoord
lDescartesCoordIntoPolarCoord(DescartesCoord p, lDescartesIntoPolarInfo info, int mode)
{
	double x, y, z;
	double x1, y1, z1;
	double x2, y2, z2;
	PolarCoord dst;

	x = p.x - info.centre.x;
	y = p.y - info.centre.y;
	z = p.z - info.centre.z;

	x1 = x*info.xaxisInv.x + y*info.yaxisInv.x + z*info.zaxisInv.x; 
	y1 = x*info.xaxisInv.y + y*info.yaxisInv.y + z*info.zaxisInv.y; 
	z1 = x*info.xaxisInv.z + y*info.yaxisInv.z + z*info.zaxisInv.z; 

	dst.r = sqrt(SQR(x1) + SQR(y1) + SQR(z1));
	if(dst.r==0) {
		dst.theta = 0;	
	} else {
		dst.theta = acos(z1/dst.r);
	}
	if(SQR(x1) + SQR(y1) == 0) {
		dst.phi = 0.0;
	} else {
		dst.phi = atan2(y1, x1);
	}
	return dst;
}

DescartesCoord
lPolarCoordIntoDescartesCoord(PolarCoord p, lDescartesIntoPolarInfo info, int mode)
{
	double x, y, z;
	DescartesCoord dst;

	DEBUGPRINT3("lPolarCoordIntoDescartesCoord PolarCoord: %g %g %g\n", p.r, p.phi, p.theta);
	x = p.r*sin(p.theta)*cos(p.phi);
	y = p.r*sin(p.theta)*sin(p.phi);
	z = p.r*cos(p.theta);
	DEBUGPRINT3("lPolarCoordIntoDescartesCoord before axis-tranform: %g %g %g\n", x, y, z);
	DEBUGPRINT3("lPolarCoordIntoDescartesCoord : xaxis: %g %g %g\n", info.xaxis.x, info.xaxis.y, info.xaxis.z);
	DEBUGPRINT3("lPolarCoordIntoDescartesCoord : yaxis: %g %g %g\n", info.yaxis.x, info.yaxis.y, info.yaxis.z);
	DEBUGPRINT3("lPolarCoordIntoDescartesCoord : zaxis: %g %g %g\n", info.zaxis.x, info.zaxis.y, info.zaxis.z);
	dst.x = x*info.xaxis.x + y*info.yaxis.x + z*info.zaxis.x + info.centre.x; 
	dst.y = x*info.xaxis.y + y*info.yaxis.y + z*info.zaxis.y + info.centre.y; 
	dst.z = x*info.xaxis.z + y*info.yaxis.z + z*info.zaxis.z + info.centre.z; 

	return dst;
}
