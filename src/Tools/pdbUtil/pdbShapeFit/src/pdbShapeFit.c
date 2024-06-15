/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbShapeFit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbShapeFit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbShapeFit ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#undef  DEBUG2
#include "genUtil.h"
#include "mrcImage.h"
#include "pdbFile.h"
#include "lmrcImageContourSurface.h"
#include "lpdbSurface.h"

typedef float lpdbShapeReal;
typedef int   lpdbShapeInteger;

typedef struct lpdbShapeFitArea {
	lpdbShapeReal min;		
	lpdbShapeReal max;		
	lpdbShapeReal d;		
	lpdbShapeInteger n;		
} lpdbShapeFitArea;

typedef struct lpdbShapeFitInfo {
	lpdbShapeFitArea x;
	lpdbShapeFitArea y;
	lpdbShapeFitArea z;
	lpdbShapeFitArea phi;
	lpdbShapeFitArea psi;
	lpdbShapeFitArea theta;
	char*            EulerAngle;
	int              Centre;
	lmrcImageContourSurfaceInfo contourInfo;
	lmrcImageContourSurfaceMode contourMode;
	lpdbSurfaceInfo             surfaceInfo;
	lpdbSurfaceMode             surfaceMode;
	/* Output */
	FILE*            fptLog;
	mrcImage         fitParam;
    double maxScore; 
	double maxScoreXY;
	double maxScorePsiTheta;
	double maxX;
	double maxY;
	double maxZ;
	double maxPhi;
	double maxPsi;
	double maxTheta;
} lpdbShapeFitInfo;

typedef enum lpdbShapeFitMode {
   lpdbShapeFitModeShape = 0 
} lpdbShapeFitMode;

void lpdbShapeFitInfoSet(lpdbShapeFitInfo* linfo, pdbShapeFitInfo info);
void lpdbShapeFit(pdbFile* outPDB, pdbFile* inPDB, mrcImage* in3D, lpdbShapeFitInfo* linfo, lpdbShapeFitMode lmode);

int
main(int argc, char* argv[]) 
{
	pdbShapeFitInfo info;
	lpdbShapeFitInfo linfo;
	lpdbShapeFitMode lmode;
	pdbFile inPDB;
	pdbFile outPDB;
	mrcImage inMRC;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	lpdbShapeFitInfoSet(&linfo, info);
	lmode = info.mode;

	pdbFileRead(info.fptInPDB, &inPDB);
	mrcFileRead(&inMRC, info.InMRC, "in main", 0);

	lpdbShapeFit(&outPDB, &inPDB, &inMRC, &linfo, lmode);

	if(info.flagOutMRC) {
		mrcFileWrite(&linfo.fitParam, info.OutMRC, "in main", 0);
	}
	if(info.flagOutPDB) {
		pdbFileWrite(info.fptOutPDB, &outPDB);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr,"    -ipdb   : Filename : An atomic model to be fitted (PDB) \n");
	fprintf(stderr,"    -imrc   : Filename : 3-D density map (mrc-formated) \n");
	fprintf(stderr,"    -omrc   : Filename : fitting score map (MRC) \n");
	fprintf(stderr,"                         z=0: a max-score map of an phi-z plane which includes a max score point.\n");
	fprintf(stderr,"                              The max score mean a maximum score in all x-y-psi-theta plane with specific values of phi and z.\n");
	fprintf(stderr,"                         z=1: a max-score map of an psi-theta plane which includes a max score point.\n");
	fprintf(stderr,"                              The max score mean a maximum score in all x-y plane with specific values of psi, theta, phi and z.\n");
	fprintf(stderr,"                         z=2: a score map of an x-y plane which includes a max score point.\n");
	fprintf(stderr,"    -otxt   : Filename : fitting results (Text)\n");
	fprintf(stderr,"    -opdb   : Filename : An atomic model with a maximum score after fitting \n");
	fprintf(stderr,"    -x|y|zmin   : Initial value of z (should <= zmax)\n");
	fprintf(stderr,"    -x|y|zmax   : Final   value of z\n");
	fprintf(stderr,"    -x|y|zd     : Delta z for fitting (should !=0)\n");
	fprintf(stderr,"    -phi|psi|thetamin : Initial value of phi (should <= phimax; initial value of phi is 0)\n");
	fprintf(stderr,"    -phi|psi|thetamax : Final value of phi  (should !=0)\n");
	fprintf(stderr,"    -phi|psi|thetad   : Delta phi for fitting (should >0)\n");
	fprintf(stderr,"    -C      : Contour level of map file\n");
	fprintf(stderr,"    -Inverse: Protein has high density on the image\n");
	fprintf(stderr,"    -Centre : Filament-axis in an inPDBFile is along the line of x=0, y=0\n");
	fprintf(stderr,"    -EA     : Euler Angle Set : ZOYS: z -> y -> x \n");
	fprintf(stderr,"    -c      : Not used now\n");
	fprintf(stderr,"    -m   %d : Count the atom number inside the contour.\n", lmrcImageContourSurfaceModeSimple);
}

void 
lpdbShapeFitInfoSet(lpdbShapeFitInfo* linfo, pdbShapeFitInfo info)
{
	linfo->x.min = info.xmin;
	linfo->x.max = info.xmax;
	linfo->x.d   = info.xDelta;
	linfo->y.min = info.ymin;
	linfo->y.max = info.ymax;
	linfo->y.d   = info.yDelta;
	linfo->z.min = info.zmin;
	linfo->z.max = info.zmax;
	linfo->z.d   = info.zDelta;
	linfo->phi.min = info.phimin;
	linfo->phi.max = info.phimax;
	linfo->phi.d   = info.phiDelta;
	linfo->psi.min = info.psimin;
	linfo->psi.max = info.psimax;
	linfo->psi.d   = info.psiDelta;
	linfo->theta.min = info.thetamin;
	linfo->theta.max = info.thetamax;
	linfo->theta.d   = info.thetaDelta;

	linfo->x.n = fabs((linfo->x.min - linfo->x.max)/linfo->x.d) + 1;
	linfo->y.n = fabs((linfo->y.min - linfo->y.max)/linfo->y.d) + 1;
	linfo->z.n = fabs((linfo->z.min - linfo->z.max)/linfo->z.d) + 1;
	linfo->phi.n   = fabs((linfo->phi.min   - linfo->phi.max)  /linfo->phi.d)   + 1;
	linfo->psi.n   = fabs((linfo->psi.min   - linfo->psi.max)  /linfo->psi.d)   + 1;
	linfo->theta.n = fabs((linfo->theta.min - linfo->theta.max)/linfo->theta.d) + 1;

	linfo->EulerAngle = info.EulerAngle;

	linfo->fptLog = info.fptOutTxt;

	/* fitting Score map */
	mrcDefaultHeaderValueSet(&linfo->fitParam);
	linfo->fitParam.HeaderN.x = MAX(linfo->phi.n, MAX(linfo->psi.n, linfo->theta.n));   
	linfo->fitParam.HeaderN.y = MAX(linfo->z.n,   MAX(linfo->x.n,   linfo->y.n));;   
	if(linfo->psi.n==1 && linfo->theta.n==1 && linfo->x.n==1 && linfo->y.n==1) {
		linfo->fitParam.HeaderN.z = 1;
	} else {
		linfo->fitParam.HeaderN.z = 3;
	}
	linfo->fitParam.HeaderLength.x = linfo->phi.d; 
	linfo->fitParam.HeaderLength.y = linfo->z.d; 
	linfo->fitParam.HeaderLength.z = 1; 
	linfo->fitParam.HeaderMode = mrcFloatImage;
	mrcInit(&linfo->fitParam, NULL);

	/* Centre */
	linfo->Centre = info.Centre;

	/* Set infomaiton for contourSurface of mrcImage */
	linfo->contourInfo.Contour = info.Contour; 
	linfo->contourMode         = info.ContourMode; 

	/* Set information for surface of PDB */
	linfo->surfaceMode = info.surfaceMode;
	linfo->surfaceInfo.order = info.order;
	linfo->surfaceInfo.refine = info.refine;
	linfo->surfaceInfo.size = info.size;
	linfo->surfaceInfo.weight = info.weight;
	linfo->surfaceInfo.mergin = info.mergin;
	linfo->surfaceInfo.thresHold = info.thresHold;
}

void 
lpdbShapeFit(pdbFile* outPDB, pdbFile* inPDB, mrcImage* in3D, lpdbShapeFitInfo* info, lpdbShapeFitMode mode)
{
	lpdbShapeReal offsetx;
	lpdbShapeReal offsety;		
	lpdbShapeReal offsetz;		
	lpdbShapeReal X;		
	lpdbShapeReal Y;		
	lpdbShapeReal Z;		
	lpdbShapeReal x;		
	lpdbShapeReal y;		
	lpdbShapeReal z;		
	lpdbShapeReal phi;		
	lpdbShapeReal psi;		
	lpdbShapeReal theta;		
	lpdbShapeInteger ix;		
	lpdbShapeInteger iy;		
	lpdbShapeInteger iz;		
	lpdbShapeInteger iphi;		
	lpdbShapeInteger ipsi;		
	lpdbShapeInteger itheta;		
	double data;
	double score; 
	Matrix3D MatrixShift0; /* Shift to the mrc coord */ 
	Matrix3D MatrixShift1; /* Back to the original coord */
	Matrix3D MatrixRot;    /* Rotation */
	pdbFile  srcPDB;
	pdbFile  tmpPDB;
	mrcImage contour3D;
	mrcImage tmpParam;
	mrcImageParaTypeReal x0, y0;

	/* Set Offset Matrix */ 
	offsetx = (in3D->HeaderN.x-1) * in3D->HeaderLength.x/2.0;
	offsety = (in3D->HeaderN.y-1) * in3D->HeaderLength.y/2.0;
	offsetz = 0;
	matrix3DTranslationSet(MatrixShift0, -offsetx, -offsety, -offsetz, MATRIX_3D_MODE_INITIALIZE); /* */ 
	matrix3DTranslationSet(MatrixShift1,  offsetx,  offsety,  offsetz, MATRIX_3D_MODE_INITIALIZE); /* */ 

	/* Temporaray parameter file Create */
	tmpParam.Header = info->fitParam.Header;	
	mrcInit(&tmpParam, NULL);

	/* pdbFile Create */
	pdbFileNew(&srcPDB); srcPDB.top = NULL;
	pdbFileNew(&tmpPDB); tmpPDB.top = NULL;
	pdbFileNew( outPDB); outPDB->top = NULL;
	pdbFileCopyAll(&srcPDB, inPDB);

	/* Set Offset : Filament-axis move to (0, 0, any). */
	if(!info->Centre) {
		pdbTrans(&srcPDB, MatrixShift0); /* The filament axis moves to the (0, 0)  */
	}

DEBUGPRINT("ContourMap Create\n"); 
	fprintf(info->fptLog, "%6s Create Contour Surface of mrcImage\n", "REMARK");
	lmrcImageContourSurfaceCreate(&contour3D, in3D, info->contourInfo, info->contourMode);
#ifdef DEBUG2
	{ 
	mrcFileWrite(&contour3D, "/tmp/test.contour3D", "tmp", 0);
	}	
#endif

DEBUGPRINT("Define surface as Temperature factor\n");
	fprintf(info->fptLog, "%6s Create Surface of pdbFile \n", "REMARK");
	lpdbSurfaceAsTemperatureFactor(&srcPDB, &info->surfaceInfo, info->surfaceMode);
#ifdef DEBUG2
	{ FILE* fpt;
	fpt = fopen("/tmp/test.pdb", "w");		
	pdbFileWrite(fpt, &srcPDB);
	fclose(fpt);
	}
#endif

	/* Fitting Procedure */
DEBUGPRINT("Search in a z-phi-plane\n"); 
	info->maxScore = 0;
	for(z    =info->z.min,     iz=0;     z<=info->z.max;         z+=info->z.d,         iz++) {
		DEBUGPRINT2("%10.2f %5d\n", z, iz);
		fprintf(info->fptLog, "%6s %10.2f %5d\n", "START", z, iz);
	for(phi  =info->phi.min,   iphi=0;   phi<=info->phi.max;     phi+=info->phi.d,     iphi++) {

/* Search in a psi-theta plane */
	info->maxScorePsiTheta = 0.0;
	for(psi  =info->psi.min,   ipsi=0;   psi<=info->psi.max;     psi+=info->psi.d,     ipsi++) {
	for(theta=info->theta.min, itheta=0; theta<=info->theta.max; theta+=info->theta.d, itheta++) {

/* Search in an x-y plane */
	info->maxScoreXY       = 0.0;
	for(x    =info->x.min,     ix=0;     x<=info->x.max;         x+=info->x.d,         ix++) {
	for(y    =info->y.min,     iy=0;     y<=info->y.max;         y+=info->y.d,         iy++) {
		/* Create Matrix */	
		matrix3DRotationSetFollowingEulerAngle(MatrixRot, info->EulerAngle, phi*RADIAN, psi*RADIAN, theta*RADIAN, MATRIX_3D_MODE_INITIALIZE);
		matrix3DTranslationSet(MatrixRot,  x,  y,  z, MATRIX_3D_MODE_NOT_INITIALIZE);

		pdbFileCopyAll(&tmpPDB, &srcPDB);
		pdbTrans(&tmpPDB, MatrixRot);    /* Rotation */  
		pdbTrans(&tmpPDB, MatrixShift1); /* tranform into  map coord.  The filament axis moves to the centre of map */ 

		/* Calc Score */
		score = 0;
		pdbFileTop(&tmpPDB); 
		do {
			if(pdbFileIsAtom(&tmpPDB)) {	
				pdbFileCoordGet(&tmpPDB, &X, &Y, &Z);
				mrcImageDataGetbyAU(&contour3D, X, Y, Z, &data, mrcPixelMag, mrcPixelHowNearest);
				score += data*tmpPDB.PDB->TemperatureFactor;
			}
		} while(NULL!=pdbFileNextAtom(&tmpPDB));
#ifdef DEBUG2
		DEBUGPRINT7("ALL %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f\n", score, phi, z, psi, theta, x, y);
#endif
/* Score Evaluation I*/
	/* All Space (x, y, theta, psi, z, phi) */
		if(info->maxScore<score) { 
			info->maxScore = score;
			info->maxPhi = phi;
			info->maxPsi = psi;
			info->maxTheta = theta;
			info->maxX = x;
			DEBUGPRINT7("MAX %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f\n", score, phi, z, psi, theta, x, y);
			info->maxY = y;
			info->maxZ = z;
			fprintf(info->fptLog, "%6s %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f (phi,z,psi,theta,x,y)\n", 
					"MAX", 
			         phi, z, psi, theta, x, y);
		}
	/* All Space (x, y) and specific (theta, psi, z, phi) */
		if(info->maxScoreXY<score) { 
			info->maxScoreXY = score;
		}
	/* All Space (x, y, psi, theta) and specific (z, phi) */
		if(info->maxScorePsiTheta<score) { 
			info->maxScorePsiTheta = score;
		}

	/* Set scores of (x, y) at current plane (phi, z, psi, theta), temporarily */
		if(2<tmpParam.HeaderN.z) {
			mrcPixelDataSet(&tmpParam, ix, iy, 2.0, score, mrcPixelRePart);
		}
	} /* y */
	} /* x */
/* Score Evaluation II */
	/* If this x-y plane in specific (psi, theta, phi, z) has more socre points than other previous x-y planes */
		if(info->maxScore<=info->maxScoreXY 
		&& 2<tmpParam.HeaderN.z) {
			for(x0=0; x0<tmpParam.HeaderN.x; x0++) {
			for(y0=0; y0<tmpParam.HeaderN.y; y0++) {
				mrcPixelDataGet(&tmpParam,       x0, y0, 2.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(&info->fitParam, x0, y0, 2.0,  data, mrcPixelRePart);
			}
			}
		}
	/* Set a maximum score in all space (x, y) as the value at (psi, theta, phi, z). */
		if(1<tmpParam.HeaderN.z) {
			mrcPixelDataSet(&tmpParam, ipsi, itheta, 1.0, info->maxScoreXY, mrcPixelRePart);
		}
	} /* theta */
	} /* psi */
        /* If this psi-theta plane in specific (phi, z) has more socre points than other previous psi-theta planes */
		if(info->maxScore<=info->maxScorePsiTheta
		&& 1<tmpParam.HeaderN.z) {
			for(x0=0; x0<tmpParam.HeaderN.x; x0++) {
			for(y0=0; y0<tmpParam.HeaderN.y; y0++) {
				mrcPixelDataGet(&tmpParam,       x0, y0, 1.0, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(&info->fitParam, x0, y0, 1.0,  data, mrcPixelRePart);
			}
			}
		}
	/* Set a maximum score in all space (x, y, psi, theta) as the value at (phi, z) */
		mrcPixelDataSet(&(info->fitParam), iphi, iz, 0.0, info->maxScorePsiTheta, mrcPixelRePart);
	} /* phi */
	} /* z */

	/* Calc outPDB  */	
	matrix3DRotationSetFollowingEulerAngle(MatrixRot, info->EulerAngle, info->maxPhi*RADIAN, info->maxPsi*RADIAN, info->maxTheta*RADIAN, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(MatrixRot,  info->maxX,  info->maxY,  info->maxZ, MATRIX_3D_MODE_NOT_INITIALIZE);
	pdbFileCopyAll(outPDB, &srcPDB);
	pdbTrans(outPDB, MatrixRot);    /* Rotation */  
	pdbTrans(outPDB, MatrixShift1); /* tranform into  map coord.  The filament axis moves to the centre of map */ 
}

