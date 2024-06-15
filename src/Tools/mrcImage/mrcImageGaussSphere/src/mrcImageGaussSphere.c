/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageGaussSphere ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageGaussSphere
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageGaussSphere ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "genUtil.h"
#include "mrcImage.h"

typedef struct _lmrcImageGaussSphereInfo {
		float sigmax;
		float sigmay;
		float sigmaz;
		float sigma_range;
		float weight;
		float size;
		long mode;
		int flagWidth;
		float width;
		int flagHeight;
		float height;
		int flagSection;
		float section;
		
		Matrix3D AffineMatrix; 
}_lmrcImageGaussSphereInfo;

extern void lmrcImageGaussSphere(_lmrcImageGaussSphereInfo* info, mrcImage* out);

int
main(int argc, char* argv[]) 
{
	mrcImageGaussSphereInfo info;
	mrcImage out;
	_lmrcImageGaussSphereInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.sigmax       = info.sigmax/info.size;
	linfo.sigmay       = info.sigmay/info.size;
	linfo.sigmaz       = info.sigmaz/info.size;
	linfo.sigma_range  = info.sigma_range;
	linfo.weight 	   = info.weight;
	linfo.size 		   = info.size;
	linfo.mode         = info.mode;
	linfo.flagWidth    = info.flagWidth;
	linfo.width        = info.Width;
	linfo.flagHeight   = info.flagHeight;
	linfo.height       = info.Height;
	linfo.flagSection  = info.flagSection;
	linfo.section      = info.Section;

	matrix3DRotationSetFollowingEulerAngle(linfo.AffineMatrix, info.EA, info.Rot1*RADIAN, info.Rot2*RADIAN, info.Rot3*RADIAN, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(linfo.AffineMatrix, info.ShiftX, info.ShiftY, info.ShiftZ, MATRIX_3D_MODE_NOT_INITIALIZE);
	lmrcImageGaussSphere(&linfo, &out);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "Gauss Sphere is cutted at sigma_range*sigma \n");
	fprintf(stderr, "Gauss Sphere = weight * exp ( - ((x^2 / sigmax^2)+(y^2 / sigmay^2)+(z^2 / sigmaz^2)) \n");
	fprintf(stderr, "mrcImageFileSize is (sigma_range*sigmax*2) x (sigma_range*sigmay*2) x (sigma_range*sigmaz*2) \n");
	fprintf(stderr, "-----------------------------------------------------------------------------------\n");
	fprintf(stderr, "-EA: for rotation \n");
	fprintf(stderr, "-----------------------------------------------------------------------------------\n");
	fprintf(stderr, "mode 0 char \n");
	fprintf(stderr, "mode 2 float \n");
}

void
lmrcImageGaussSphere(_lmrcImageGaussSphereInfo* linfo, mrcImage* out)
{
	mrcImageParaTypeReal    x,    y,    z; /* Pixel */
	mrcImageParaTypeReal cenx, ceny, cenz;
	double data;
	floatVector v;
	Matrix3D    mat;

	floatVectorInit(&v, 4);
	matrix3DCopy(mat, linfo->AffineMatrix);
	matrix3DInverse(mat);	

	out->HeaderLength.x = linfo->size;
	out->HeaderLength.y = linfo->size;
	out->HeaderLength.z = linfo->size;

	out->HeaderN.x = linfo->sigmax * linfo->sigma_range * 2 + 1;
	out->HeaderN.y = linfo->sigmay * linfo->sigma_range * 2 + 1;
	out->HeaderN.z = linfo->sigmaz * linfo->sigma_range * 2 + 1;

	if(linfo->flagWidth) {
		out->HeaderN.x = linfo->width/out->HeaderLength.x;
	}
	if(linfo->flagHeight) {
		out->HeaderN.y = linfo->height/out->HeaderLength.y;
	}
	if(linfo->flagSection) {
		out->HeaderN.z = linfo->section/out->HeaderLength.z;
	}
	out->HeaderMode = linfo->mode;

	mrcInit(out, NULL);  /* Memory allocate */

	cenx = (out->HeaderN.x - 1)/2.0;
	ceny = (out->HeaderN.y - 1)/2.0;
	cenz = (out->HeaderN.z - 1)/2.0;

	v.data[3] = 1;
	for(z=0; z<out->HeaderN.z; z++){
	for(y=0; y<out->HeaderN.y; y++){
	for(x=0; x<out->HeaderN.x; x++){
		v.data[0] = x-cenx; 	
		v.data[1] = y-ceny; 	
		v.data[2] = z-cenz; 	
		matrix3DMultiplyVector(&v, mat);
		data = linfo->weight*exp(-(SQR(v.data[0])/(linfo->sigmax*linfo->sigmax)
								  +SQR(v.data[1])/(linfo->sigmay*linfo->sigmay)
							   	  +SQR(v.data[2])/(linfo->sigmaz*linfo->sigmaz)));
		mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
	}
	}
	}
}
