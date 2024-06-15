/*
# lmrcImage3DPad.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImage3DPad.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMGAGE3D_H 
#define LMRCIMGAGE3D_H  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* constant begin */

typedef enum lmrcImage3DPadShapeMode {
	lmrcImage3DPadShapeModeFilament=0,
	lmrcImage3DPadShapeModeSphere=1,
	lmrcImage3DPadShapeModeEllipsoid=2,
	lmrcImage3DPadShapeModeRectangle=3
} lmrcImage3DPadShapeMode;

/* constant end */

/* struct begin */

typedef struct lmrcImage3DPadInfo {
	int Nx;
	int Ny;
	int Nz;

	double w;

	int flagv;
	double v;

	lmrcImage3DPadShapeMode ShapeMode;

	int flagShell;
	float shell; // rmax*shell [pixel]

	// Filament-type: z-infinity
	// or 
	// Ideal Sphere
	int flagr;
	float rmax;

	// Ellipsoid
	float rxmax;
	float rymax;
	float rzmax;

	// Rectangle
	float xmax;
	float ymax;
	float zmax;

	int flagFloating;
} lmrcImage3DPadInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

/* General */
void lmrcImage3DPadUsage(FILE* fpt);
void lmrcImage3DPad(mrcImage* out ,mrcImage* in , lmrcImage3DPadInfo linfo, int mode );

/* FilamentType: no pad: z-axis*/
void lmrcImage3DPadfilament(mrcImage* out ,mrcImage* in, lmrcImage3DPadInfo linfo, int mode );
double lmrcImage3DPadfilamentCalcavr(mrcImage* in, double rmax, double delr);

/* Single Particle Type: Sphere-type */
double lmrcImage3DPadSphereCalcavr(mrcImage* in, double rmax, double delr);
void lmrcImage3DPadSphere(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode);

/* Single Particle Type: -type */
double lmrcImage3DPadEllipsoidCalcavr(mrcImage* in, double rxmax, double rymax, double rzmax, double delx, double dely, double delz);
void lmrcImage3DPadEllipsoid(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode);

/* Rectangle-type */
double lmrcImage3DPadRectangleCalcavr(mrcImage* in, double xmax, double ymax, double zmax, double delx, double dely, double delz);
void lmrcImage3DPadRectangle(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMGAGE3D_H */ 

