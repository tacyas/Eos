/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMorphology ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageMorphology 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageMorphology ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include <stdio.h>
#include "./lmrcImageMorphology.h"

void
lmrcImageMorphologyStructuringElementSet(lmrcImageMorphologyInfo* linfo, int mode)
{
    DEBUGPRINT1(" lmrcImageMorphologyStructuringElementSet: %d\n", linfo->mode);
	switch(linfo->mode) {
		case 0: {
			lmrcImageMorphologyStructuringElement2DCross(&linfo->SE, mode);
			break;
		}
		case 1: {
			lmrcImageMorphologyStructuringElement2DSquare(&linfo->SE, mode);
			break;
		}
		case 2: {
			lmrcImageMorphologyStructuringElement2DDisk(&linfo->SE, linfo->radius, linfo->n, mode);
			break;
		}
		case 3: {
			lmrcImageMorphologyStructuringElement3DCross(&linfo->SE, mode);
			break;
		}
		case 4: {
			lmrcImageMorphologyStructuringElement3DCubic(&linfo->SE, mode);
			break;
		}
		case 5: {
			lmrcImageMorphologyStructuringElement3DSphere(&linfo->SE, linfo->radius, linfo->n, mode);
			break;
		}
		case 6: {
			lmrcImageMorphologyStructuringElement2DRectangle(&linfo->SE, linfo->nx, linfo->ny, mode);
			break;
		}
		case 7: {
			lmrcImageMorphologyStructuringElement3DCuboid(&linfo->SE, linfo->nx, linfo->ny, linfo->nz, mode);
			break;
		}
		case 8: {
			lmrcImageMorphologyStructuringElement3DCylinder(&linfo->SE, linfo->radius, linfo->nx, linfo->ny, linfo->nz, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageMorphologyStructuringElementSet: %d", linfo->mode);
			exit(EXIT_FAILURE);
		}
	}
}
	

void
lmrcImageMorphologyStructuringElementSetInfoPrint(FILE* fpt)
{
	fprintf(fpt, "0: 2D Cross3x3:  4-neighbour\n");
	fprintf(fpt, "1: 2D Square3x3: 8-neighbour\n");
	fprintf(fpt, "2: 2D Disk , need (radius, n(squre size))\n");
	fprintf(fpt, "3: 3D Cross3x3x3:   6-neighbour\n");
	fprintf(fpt, "4: 3D Cubic3x3x3: 26-neighbour\n");
	fprintf(fpt, "5: 3D Sphere, need (radius, n(cubic size))\n");
	fprintf(fpt, "6: 2D Rectangle, need nx, ny\n");
	fprintf(fpt, "7: 3D Cuboid, need nx, ny, nz\n");
	fprintf(fpt, "8: 3D Cylindar, need r, nx, ny, nz\n");

	fprintf(fpt, "-----\n");
	fprintf(fpt, "Dilation: Max for image : Or  for binary image \n");
	fprintf(fpt, "Erosion:  Min for image : And for binary image \n");
}


void
lmrcImageMorphologyStructuringElement2DCross(mrcImage* out, int mode)
{
	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = 3;
	out->HeaderN.y = 3;
	out->HeaderN.z = 1;
	out->HeaderStartN.x = -1;
	out->HeaderStartN.y = -1;
	out->HeaderStartN.z = 0;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);
	mrcPixelDataSet(out, 0, 2, 0, 0, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 2, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 2, 2, 0, 0, mrcPixelRePart); 
	mrcPixelDataSet(out, 0, 1, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 1, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 2, 1, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 0, 0, 0, 0, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 0, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 2, 0, 0, 0, mrcPixelRePart); 
}

void
lmrcImageMorphologyStructuringElement2DSquare(mrcImage* out, int mode)
{
	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = 3;
	out->HeaderN.y = 3;
	out->HeaderN.z = 1;
	out->HeaderStartN.x = -1;
	out->HeaderStartN.y = -1;
	out->HeaderStartN.z = 0;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);
	mrcPixelDataSet(out, 0, 2, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 2, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 2, 2, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 0, 1, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 1, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 2, 1, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 0, 0, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 0, 0, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 2, 0, 0, 1, mrcPixelRePart); 
}


void
lmrcImageMorphologyStructuringElementSphere(mrcImage* out, int r, int nx, int ny, int nz, int mode)
{
	int x, y, z;
	int rx, ry, rz;
	double rr, r2;
	double data;
    DEBUGPRINT("Sphere\n");
	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = nx;
	out->HeaderN.y = ny;
	out->HeaderN.z = nz;
	out->HeaderStartN.x = -nx/2;
	out->HeaderStartN.y = -ny/2;
	out->HeaderStartN.z = -nz/2;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);

	r2 = r*r;
	for(z=0; z<out->HeaderN.z; z++) {
		rz = z + out->HeaderStartN.z; 
	for(y=0; y<out->HeaderN.y; y++) {
		ry = y + out->HeaderStartN.y; 
	for(x=0; x<out->HeaderN.x; x++) {
		rx = x + out->HeaderStartN.x; 
		rr = rx*rx + ry*ry+ rz*rz; 	
		if(rr <= r2) {
			mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart);	
		} else {
			mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);	
		}
	}
	}
	}
}

void
lmrcImageMorphologyStructuringElement3DCylinder(mrcImage* out, int r, int nx, int ny, int nz, int mode)
{
	int x, y, z;
	int rx, ry, rz;
	double rr, r2;
	double data;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = nx;
	out->HeaderN.y = ny;
	out->HeaderN.z = nz;
	out->HeaderStartN.x = -nx/2;
	out->HeaderStartN.y = -ny/2;
	out->HeaderStartN.z = -nz/2;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);

	r2 = r*r;
	for(z=0; z<out->HeaderN.z; z++) {
		rz = z + out->HeaderStartN.z; 
	for(y=0; y<out->HeaderN.y; y++) {
		ry = y + out->HeaderStartN.y; 
	for(x=0; x<out->HeaderN.x; x++) {
		rx = x + out->HeaderStartN.x; 
		rr = rx*rx + ry*ry; 	
		if(rr <= r2) {
			mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart);	
		} else {
			mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);	
		}
	}
	}
	}
}

void
lmrcImageMorphologyStructuringElement2DDisk(mrcImage* out, int r, int n, int mode)
{
	lmrcImageMorphologyStructuringElementSphere(out, r, n, n, 1, mode);
}

void
lmrcImageMorphologyStructuringElement3DCross(mrcImage* out, int mode)
{
	float x, y, z;
	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = 3;
	out->HeaderN.y = 3;
	out->HeaderN.z = 3;
	out->HeaderStartN.x = -1;
	out->HeaderStartN.y = -1;
	out->HeaderStartN.z = 0;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);


	for(z=0; z<3; z++) {
	for(y=0; y<3; y++) {
	for(x=0; x<3; x++) {
		mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart); 
	}
	}
	}
	mrcPixelDataSet(out, 1, 1, 1, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1-1, 1, 1, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1+1, 1, 1, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 1-1, 1, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 1+1, 1, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 1, 1-1, 1, mrcPixelRePart); 
	mrcPixelDataSet(out, 1, 1, 1+1, 1, mrcPixelRePart); 
}

void
lmrcImageMorphologyStructuringElement3DCubic(mrcImage* out, int mode)
{
	float x, y, z;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = 3;
	out->HeaderN.y = 3;
	out->HeaderN.z = 3;
	out->HeaderStartN.x = -1;
	out->HeaderStartN.y = -1;
	out->HeaderStartN.z = 0;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);
	for(z=0; z<3; z++) {
	for(y=0; y<3; y++) {
	for(x=0; x<3; x++) {
		mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart); 
	}
	}
	}
}

void
lmrcImageMorphologyStructuringElement3DCuboid(mrcImage* out, int nx, int ny, int nz, int mode)
{
	float x, y, z;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = nx;
	out->HeaderN.y = ny;
	out->HeaderN.z = nz;
	out->HeaderStartN.x = -nx/2;
	out->HeaderStartN.y = -ny/2;
	out->HeaderStartN.z = -nz/2;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);
	for(z=0; z<nz; z++) {
	for(y=0; y<ny; y++) {
	for(x=0; x<nx; x++) {
		mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart); 
	}
	}
	}
}

void
lmrcImageMorphologyStructuringElement2DRectangle(mrcImage* out, int nx, int ny, int mode)
{
	float x, y, z;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = nx;
	out->HeaderN.y = ny;
	out->HeaderN.z = 1;
	out->HeaderStartN.x = -1;
	out->HeaderStartN.y = -1;
	out->HeaderStartN.z = 0;
	out->HeaderMode = mrcCharImage;
	mrcInit(out, NULL);
	for(y=0; y<ny; y++) {
	for(x=0; x<nx; x++) {
		mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart); 
	}
	}
}


void
lmrcImageMorphologyStructuringElement3DSphere(mrcImage* out, int r, int n, int mode)
{
	lmrcImageMorphologyStructuringElementSphere(out, r, n, n, n, mode);
}
