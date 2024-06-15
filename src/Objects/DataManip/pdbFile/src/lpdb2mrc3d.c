/*
# lpdb2mrc3d.c  1.2
# The latest update : 03/20/98 at 14:26:13
#
#@(#) lpdb2mrc3d ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : lpdb2mrc3d 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lpdb2mrc3d ver1.2; Date:98/03/20 @(#)";
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/pdbFile.h"
#include "mrcImage.h"
#include "lpdb2mrcInfo.h"
/*
mode: 0
      1 : No initialize
*/

static void __lpdb2mrc3dSameGaussian(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc3dInfo* info, long mode);
static void __lpdb2mrc3dWentzelAtomModel(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc3dInfo* info, long mode);

void
lpdb2mrc3dUsage(FILE* fpt)
{
	fprintf(fpt, "%d: Same Gaussian \n", lpdb2mrcDensityModeSameGaussian);
	fprintf(fpt, "%d: WentzelAtomModel\n", lpdb2mrcDensityModeWentzelAtomModel);
}

void
lpdb2mrc3d(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc3dInfo* info, long mode)
{
	static long flagFirst=0;
    pdbFileParaTypeReal sx, sy, sz;
	pdbFileParaTypeReal ex, ey, ez;
	pdbFileParaTypeReal dx, dy, dz;
    double data, w;
	float x, y, z;
	float dstx, dsty, dstz;
	float sigmax, sigmay, sigmaz;
	float dstx0, dsty0, dstz0;
	float dstdx, dstdy, dstdz;
	float srcx, srcy, srcz;

	if((mode&1)==0) { /* Initialization */
		if(flagFirst==0) {
	    	mrc->HeaderN.x = info->nx;
   			mrc->HeaderN.y = info->ny;
	    	mrc->HeaderN.z = info->nz;
   	 		mrc->HeaderMode = 	mrcFloatImage;
	    	mrc->HeaderLength.x = info->dx;
   			mrc->HeaderLength.y = info->dy;
    		mrc->HeaderLength.z = info->dz; 
			mrc->HeaderStartN.x = info->sx/info->dx;
			mrc->HeaderStartN.y = info->sy/info->dy;
			mrc->HeaderStartN.z = info->sz/info->dz;
    		mrcInit(mrc, NULL);
		}
	} else { /* No Initialization */

	}

	switch(info->DensityMode) {
		case lpdb2mrcDensityModeSameGaussian: {
			__lpdb2mrc3dSameGaussian(mrc, pdb, info, mode);
			break;
		}
		case lpdb2mrcDensityModeWentzelAtomModel: {
			__lpdb2mrc3dWentzelAtomModel(mrc, pdb, info, mode);
			break;
		}
		default: {
			fprintf(stdout, "Not supported density mode: %d So we use same gaussian mode\n", info->DensityMode);
			__lpdb2mrc3dSameGaussian(mrc, pdb, info, mode);
			break;
		}
	}
    mrcStatDataSet(mrc, 0);
	flagFirst++;
	DEBUGPRINT1("%d\n", flagFirst);
}

void
__lpdb2mrc3dSameGaussian(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc3dInfo* info, long mode)
{
    pdbFileParaTypeReal sx, sy, sz;
	pdbFileParaTypeReal ex, ey, ez;
	pdbFileParaTypeReal dx, dy, dz;
    double data, w;
	float x, y, z;
	float dstx, dsty, dstz;
	float sigmax, sigmay, sigmaz;
	float dstx0, dsty0, dstz0;
	float dstdx, dstdy, dstdz;
	float srcx, srcy, srcz;

    sx = info->sx;
    sy = info->sy;
    sz = info->sz;
    dx = info->dx;
    dy = info->dy;
    dz = info->dz;
    ex = sx+info->nx*dx;
    ey = sy+info->ny*dy;
    ez = sz+info->nz*dz;
    w  = info->Weight;
   	sigmax = info->Sigma/dx; 
   	sigmay = info->Sigma/dy; 
   	sigmaz = info->Sigma/dz; 
	DEBUGPRINT3("Sigma: %f %f %f\n", sigmax, sigmay, sigmaz);
    pdbFileTop(pdb);
	while(1) {
		if(pdbFileIsAtom(pdb)) {
			pdbFileCoordGet(pdb, &x, &y, &z);
			if(0.0==info->Sigma) {
	    		if( sx <= x && x < ex
  	 		  	  &&sy <= y && y < ey
  	 		  	  &&sz <= z && z < ez) {
				  	/*
					dstx = (x-sx)/dx;
					dsty = (y-sy)/dy;
					dstz = (z-sz)/dz;
					*/
       				mrcImageDataGetbyAU(mrc, 
							x, 
							y, 
							z, 
							&data,  mrcPixelRePart, mrcPixelHowNearest);
           			data += w;
               		mrcImageDataSetbyAU(mrc, 
							x, 
							y, 
							z, 
							data, mrcPixelRePart);
				}
			} else {
				dstx = (x-sx)/dx;
				dsty = (y-sy)/dy;
				dstz = (z-sz)/dz;
				for(dstx0 = dstx - 3*sigmax; dstx0 <= dstx + 3*sigmax; dstx0++) {
					for(dsty0 = dsty - 3*sigmay; dsty0 <= dsty + 3*sigmay; dsty0++) {
						for(dstz0 = dstz - 3*sigmaz; dstz0 <= dstz + 3*sigmaz; dstz0++) {
							if( -0.5 <=dstx0 && dstx0 < mrc->HeaderN.x-0.5
							 && -0.5 <=dsty0 && dsty0 < mrc->HeaderN.y-0.5
							 && -0.5 <=dstz0 && dstz0 < mrc->HeaderN.z-0.5) {
       							mrcImageDataGetbyAU(mrc, 
									dstx0*dx + sx, 
									dsty0*dy + sy, 
									dstz0*dz + sz, 
									&data,  mrcPixelRePart, mrcPixelHowNearest);
           						data += w*exp(-SQR((dstx0-dstx)/sigmax)/2.0
								              -SQR((dsty0-dsty)/sigmay)/2.0
											  -SQR((dstz0-dstz)/sigmaz)/2.0);
               					mrcImageDataSetbyAU(mrc, 
									dstx0*dx + sx, 
									dsty0*dy + sy, 
									dstz0*dz + sz, 
									data, mrcPixelRePart);
							}
						}
					}
				}
			}
        }
        if(pdbFileEnd(pdb)) {
			break;
		} else {
			pdbFileNext(pdb);
		}
	}
}

void
__lpdb2mrc3dWentzelAtomModel(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc3dInfo* info, long mode)
{
    pdbFileParaTypeReal sx, sy, sz;
	pdbFileParaTypeReal ex, ey, ez;
	pdbFileParaTypeReal dx, dy, dz;
    double data, w;
	float x, y, z;
	float dstx, dsty, dstz;
	float sigmax, sigmay, sigmaz;
	float dstx0, dsty0, dstz0;
	float dstdx, dstdy, dstdz;
	float srcx, srcy, srcz;

	float firstx, firsty, firstz;
	float endx, endy, endz;
	float delx, dely, delz;
	float r, R, K, e, Ke, aH;
	int Z;

	aH = 0.0529e-9;
	K = 9.0e9;
	e = 1.6e-19;

	Ke = K*e;

    sx = info->sx;
    sy = info->sy;
    sz = info->sz;
    dx = info->dx;
    dy = info->dy;
    dz = info->dz;
    ex = sx+info->nx*dx;
    ey = sy+info->ny*dy;
    ez = sz+info->nz*dz;
    w  = info->Weight;
	if(0==info->Sigma) {
		info->Sigma = 1.0;
		sigmax = 1.0/dx;
		sigmay = 1.0/dy;
		sigmaz = 1.0/dz;
	} else {
   		sigmax = info->Sigma/dx; 
   		sigmay = info->Sigma/dy; 
   		sigmaz = info->Sigma/dz; 
	}
	DEBUGPRINT3("Sigma: %f %f %f\n", sigmax, sigmay, sigmaz);
	
    pdbFileTop(pdb);
	while(1) {
		if(pdbFileIsAtom(pdb)) {
			pdbFileCoordGet(pdb, &x, &y, &z);
			firstx = x - 3*info->Sigma;
			firsty = y - 3*info->Sigma;
			firstz = z - 3*info->Sigma;
			endx = x + 3*info->Sigma;
			endy = y + 3*info->Sigma;
			endz = z + 3*info->Sigma;
			for(dstx0 = firstx; dstx0 <= endx; dstx0+=0.2) {
			for(dsty0 = firsty; dsty0 <= endy; dsty0+=0.2) {
			for(dstz0 = firstz; dstz0 <= endz; dstz0+=0.2) {
				if( -0.5 <=(dstx0-sx)/dx && (dstx0-sx)/dx < mrc->HeaderN.x-0.5
				 && -0.5 <=(dsty0-sy)/dy && (dsty0-sy)/dy < mrc->HeaderN.y-0.5
				 && -0.5 <=(dstz0-sz)/dz && (dstz0-sz)/dz < mrc->HeaderN.z-0.5) {
					r = sqrt(SQR(dstx0-x)
							+SQR(dsty0-y)
							+SQR(dstz0-z))*1e-10;
					if(0.4*1e-10<r) {
       					mrcImageDataGetbyAU(mrc, 
							dstx0, dsty0, dstz0, 
							&data,  mrcPixelRePart, mrcPixelHowNearest);
						// Wentzel Atom Model 
						Z = pdbZValueGet(pdb);
						R = aH*pow(Z, -1.0/3.0);
						data += (Ke*Z/r)*exp(-r/R);
               			mrcImageDataSetbyAU(mrc, 
							dstx0, dsty0, dstz0, 
							data, mrcPixelRePart);
						//DEBUGPRINT2("%g %g\n", r, data);
					}
				}
			}
			}
			}
			//DEBUGPRINT1("x %g \n", x);
        }
        if(pdbFileEnd(pdb)) {
			break;
		} else {
			pdbFileNext(pdb);
		}
	}
#ifdef DEBUG
	mrcFileWrite(mrc, "/tmp/test.mrc", "test", 0);
#endif

}

