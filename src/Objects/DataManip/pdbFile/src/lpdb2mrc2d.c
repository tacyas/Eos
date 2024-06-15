/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lpdb2mrc2d ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lpdb2mrc2d 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "@(#)lpdb2mrc2d ver1.2; Date:97/01/23 @(#)";
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/pdbFile.h"
#include "mrcImage.h"
#include "lpdb2mrcInfo.h"

void
lpdb2mrc2d(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc2dInfo* info, char axis, long mode)
{
	static long flagFirst=0;
    pdbFileParaTypeReal sx, sy, ex, ey, dx, dy;
    pdbFileParaTypeReal orgx, orgy;
    pdbFileParaTypeReal tmpx, tmpy;
    pdbFileParaTypeReal prjx, prjy;
    double data, w, sig;
	float x, y, z;

	if(flagFirst==0 || mode==0) {
	    mrc->HeaderN.x = info->nx;
   		mrc->HeaderN.y = info->ny;
	    mrc->HeaderN.z = 1;
   	 	mrc->HeaderMode = 	mrcFloatImage;
	    mrc->HeaderLength.x = info->dx;
   		mrc->HeaderLength.y = info->dy;
    	mrc->HeaderLength.z = 0.0; 
    	mrcInit(mrc, NULL);
		DEBUGPRINT("First try in lprb2mrc2d\n");
	}

    sx = info->sx;
    sy = info->sy;
    dx = info->dx;
    dy = info->dy;
    ex = sx+info->nx*dx;
    ey = sy+info->ny*dy;
    w  = info->Weight;
	sig= info->Sigma;

   	DEBUGPRINT1("Times: %d\n", flagFirst); 
   	DEBUGPRINT1("Sigma: %f\n", sig); 
   	DEBUGPRINT5("s: %f %f, e: %f %f, w: %f\n", sx, sy, ex, ey, w); 
    pdbFileTop(pdb);
	while(1) {
		if(pdbFileIsAtom(pdb)) {
			pdbFileCoordGet(pdb, &x, &y, &z);
			switch(axis) {
				case 'z': {
					prjx = x;
					prjy = y;
					break;
				}
				case 'y': {
					prjx = z;
					prjy = x;
					break;
				}
				case 'x': {
					prjx = y;
					prjy = z;
					break;
				}
				default: {
					fprintf(stderr, "Not supported axis: %c\n", axis);
					exit(EXIT_FAILURE);
					break;
				}
			}	
			orgx = (prjx-sx)/dx;
			orgy = (prjy-sy)/dy;
			if(0==sig) {
				if( -0.5<=orgx && orgx<mrc->HeaderN.x-0.5
				  &&-0.5<=orgy && orgy<mrc->HeaderN.y-0.5) {
       	   	    	mrcPixelDataGet(mrc, orgx, orgy, 0.0, &data,  mrcPixelRePart, mrcPixelHowNearest);
           			data += w;
           		    mrcPixelDataSet(mrc, orgx, orgy, 0.0, data, mrcPixelRePart);
				}
			} else {
				double minx, maxx, miny, maxy;
				minx=MAX(floor(orgx-3.0*sig/dx + 0.5), 0);
				maxx=MIN(floor(orgx+3.0*sig/dx + 0.5), mrc->HeaderN.x-1);
				miny=MAX(floor(orgy-3.0*sig/dy + 0.5), 0);
				maxy=MIN(floor(orgy+3.0*sig/dy + 0.5), mrc->HeaderN.y-1);
   				DEBUGPRINT4("min(%f,%f), max(%f,%f)\n", minx, miny, maxx, maxy); 
				for(tmpx=minx; tmpx<=maxx; tmpx++) {
					for(tmpy=miny; tmpy<=maxy; tmpy++) {
						if(SQR((tmpx-orgx)/(3.0*sig/dx)) + SQR((tmpy-orgy)/(3.0*sig/dy)) <= 1) {
       	        			mrcPixelDataGet(mrc, tmpx, tmpy, 0.0, &data,  
								mrcPixelRePart, mrcPixelHowNearest);
           			    	data += w*exp(-(SQR((orgx-tmpx)*dx)+SQR((orgy-tmpy)*dy))/(sig*sig)/2.0);
           	   	 			mrcPixelDataSet(mrc, tmpx, tmpy, 0.0, data, mrcPixelRePart);
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
    };
	
    mrcStatDataSet(mrc, 0);
	flagFirst++;
}

