/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lpdbSurface ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lpdb2mrc3dSurface 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lpdb2mrc3dSurface ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "pdbInfoGet.h"
#include "./lpdbSurface.h"
#include "mrcImage.h"
#include "lmrcImageContourSurface.h"

extern void lpdbSurfaceAsTemperatureFactor0(pdbFile* pdb, lpdbSurfaceInfo* info);

void
lpdbSurfaceAsTemperatureFactor(pdbFile* pdb, lpdbSurfaceInfo* info, lpdbSurfaceMode mode)
{
	switch(mode) {
		case lpdbSurfaceModeSimple: {
			lpdbSurfaceAsTemperatureFactor0(pdb, info);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			break;
		}
	}
}

void
lpdbSurfaceAsTemperatureFactor0(pdbFile* pdb, lpdbSurfaceInfo* info)
{
	float  x,  y,  z;
	float sx, sy, sz;
	float dx, dy, dz;
	double data;
	double sum;
	double w;
	pdbInfoData linfo;
	mrcImage    mrc;
	mrcImage    contour;
	lpdb2mrcInfo linfomrc;
	lmrcImageContourSurfaceInfo linfocontour;

	DEBUGPRINT("lpdbSurfaceAsTemperatureFactor0\n");
	pdbInfoGet(pdb, &linfo, 0);

	linfomrc.sx = linfo.cx - linfo.distancex*info->mergin/2.0;
	linfomrc.sy = linfo.cy - linfo.distancey*info->mergin/2.0;
	linfomrc.sz = linfo.cz - linfo.distancez*info->mergin/2.0;
	linfomrc.dx = linfomrc.dy = linfomrc.dz = info->order/info->refine;
	linfomrc.nx = linfo.distancex*info->mergin/linfomrc.dx;
	linfomrc.ny = linfo.distancey*info->mergin/linfomrc.dy;
	linfomrc.nz = linfo.distancez*info->mergin/linfomrc.dz;
	linfomrc.Weight = info->weight;
	linfomrc.Sigma  = info->order;
	linfomrc.DensityMode = info->DensityMode;

	/* Density Create */ 
	DEBUGPRINT("Density Map Create\n");
	lpdb2mrc3d(&mrc, pdb, &linfomrc, 0);
#ifdef DEBUG
	mrcFileWrite(&mrc, "density.mrc", "in lpdbSurfaceAsTemperatureFactor0\n", 0);
#endif
	/* Surface Create */
	DEBUGPRINT("Surface Create\n");
    linfocontour.Contour = linfomrc.Weight*exp(-info->thresHold); 	
	lmrcImageContourSurfaceCreate(&contour, &mrc, linfocontour, lmrcImageContourSurfaceModeSimple);
#ifdef DEBUG
	mrcFileWrite(&contour, "surfacecontour.mrc", "in lpdbSurfaceAsTemperatureFactor0", 0);
#endif
	DEBUGPRINT("Set contour as Temperature factors\n");
	pdbFileTop(pdb);
	do {
		if(pdbFileIsAtom(pdb)) {
			pdbFileCoordGet(pdb, &x, &y, &z);
			sx = (x - linfomrc.sx)/linfomrc.dx; 
			sy = (y - linfomrc.sy)/linfomrc.dy; 
			sz = (z - linfomrc.sz)/linfomrc.dz; 
			sum = 0;
			for(dx=-info->size; dx<info->size+1; dx++) {
			for(dy=-info->size; dy<info->size+1; dy++) {
			for(dz=-info->size; dz<info->size+1; dz++) {
				mrcPixelDataGet(&contour, sx+dx, sy+dy, sz+dz, &data, mrcPixelRePart, mrcPixelHowNearest); 
				w = dx*dx
				  + dy*dy
				  + dz*dz; 
				sum += data*exp(-w/info->refine/info->refine);
			}
			}
			}
			if(sum>1) {
				sum = 1;
			}
			pdb->PDB->TemperatureFactor = 100*sum;
		}
	} while(NULL!=pdbFileNextAtom(pdb));
}

