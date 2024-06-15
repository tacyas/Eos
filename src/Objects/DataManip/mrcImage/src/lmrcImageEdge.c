/*
# lmrcImageEdge : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageEdge 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>

#undef DEBUG
#include "genUtil.h"
#include "./lmrcImageEdge.h"

void
lmrcImageSurfaceCalc(mrcImage* out, mrcImage* in, int neighbor, int mode)
{
	DEBUGPRINT(">>Start lmrcImageSurfaceCalc\n");
	lmrcImageEdgeCalc(out, in, neighbor, mode);
}

void
lmrcImageEdgeCalc(mrcImage* out, mrcImage* in, int neighbor, int mode)
{
	mrcImageParaTypeReal x, y, z;

	out->Header = in->Header;
	mrcInit(out, NULL);

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		if(lmrcImageIsEdge(in, x, y, z, neighbor, mode)) {
			mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart);
		} else {
			mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);
		}
	}
	}
	}
}


int 
lmrcImageIsEdge(mrcImage* bin, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, int neighbor, int mode)
{
	double data;
	double data1, data2, data3, data4, data5, data6, data7, data8;
	int flagCorner=0;
	int flagEdge=0;
	int flagSurface=0;
	
	mrcPixelDataGet(bin, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	

	if(fabs(data-1)<1e-6) { // 1
		if(bin->HeaderN.z<=1) { // 2D
			switch(neighbor) {
				case 4: {
					mrcPixelDataGet(bin, x-1, y-1, z, &data5, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data5)<1e-6) break;
					mrcPixelDataGet(bin, x-1, y+1, z, &data6, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data6)<1e-6) break;
					mrcPixelDataGet(bin, x+1, y-1, z, &data7, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data7)<1e-6) break;
					mrcPixelDataGet(bin, x+1, y+1, z, &data8, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data8)<1e-6) break;
				}
				case 8: {
					mrcPixelDataGet(bin, x-1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data1)<1e-6) break;
					mrcPixelDataGet(bin, x+1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data2)<1e-6) break;
					mrcPixelDataGet(bin, x, y-1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data3)<1e-6) break;
					mrcPixelDataGet(bin, x, y+1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data4)<1e-6) break;

					return 0;  // Inside 
				}
				default: {
					fprintf(stderr, "Not supported Neighbor: %d\n", neighbor);
					exit(EXIT_FAILURE);
				}
			}
			return 1;
		} else { // 3D
			switch(neighbor) {
				case  6: 
				case 18: 
				case 26: {
					// flagCorner 
					mrcPixelDataGet(bin, x-1, y-1, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					mrcPixelDataGet(bin, x+1, y-1, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					mrcPixelDataGet(bin, x-1, y+1, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					mrcPixelDataGet(bin, x+1, y+1, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					mrcPixelDataGet(bin, x-1, y-1, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					mrcPixelDataGet(bin, x+1, y-1, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					mrcPixelDataGet(bin, x-1, y+1, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					mrcPixelDataGet(bin, x+1, y+1, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagCorner=1; break; }
					break;
				}
				default: {
					fprintf(stderr, "Not supported Neighbor: %d\n", neighbor);
					exit(EXIT_FAILURE);
				}
			}
			if(flagCorner ==1 && neighbor!=26) {
				return 1;
			}
			switch(neighbor) {
				case 6:  
				case 18: 
				case 26: { 
					// flagEdge
					mrcPixelDataGet(bin, x, y-1, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x, y-1, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x, y+1, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x, y+1, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					//
					mrcPixelDataGet(bin, x-1, y, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x-1, y, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x+1, y, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x+1, y, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					//
					mrcPixelDataGet(bin, x-1, y-1, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x-1, y+1, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x+1, y-1, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					mrcPixelDataGet(bin, x+1, y+1, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagEdge=1; break; }
					break;
				}
				default: {
					fprintf(stderr, "Not supported Neighbor: %d\n", neighbor);
					exit(EXIT_FAILURE);
				}
			}
			if(flagEdge==1 && neighbor == 6) {
				return 1;
			}
			switch(neighbor) {
				case 6:  
				case 18:  
				case 26: { 
					// flagSurface
					mrcPixelDataGet(bin, x, y, z-1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagSurface=1; break; }
					mrcPixelDataGet(bin, x, y, z+1, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagSurface=1; break; }
					mrcPixelDataGet(bin, x, y-1, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagSurface=1; break; }
					mrcPixelDataGet(bin, x, y+1, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagSurface=1; break; }
					mrcPixelDataGet(bin, x-1, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagSurface=1; break; }
					mrcPixelDataGet(bin, x+1, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
					if(fabs(data)<1e-6) { flagSurface=1; break; }
					break;
				}
				default: {
					fprintf(stderr, "Not supported Neighbor: %d\n", neighbor);
					exit(EXIT_FAILURE);
				}
			}
			if(flagSurface==1) { // Surface
				return 1;  
			} else {
				DEBUGPRINT3("Inside %f %f %f\n", x, y, z);
				return 0; // Inside
			}
		}
	} else {
		return 0; // Not 1 
	}
}

