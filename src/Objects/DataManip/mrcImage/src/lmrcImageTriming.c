/*
# lmrcImageShaving : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageTriming
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "./lmrcImageTriming.h"
void 
lmrcImageTriming(mrcImage* dst, mrcImage* src, int neighbor, int times, int mode)
{
	int i;
	mrcImageParaTypeReal x, y, z;
	double data;
	double data1, data2, data3, data4, data5, data6, data7, data8;
	mrcImage* tmp;

	dst->Header = src->Header;
	mrcInit(dst, NULL);

	tmp = src;
	for(i=0; i<times; i++) {
		for(x=0; x<src->HeaderN.x; x++) {
		for(y=0; y<src->HeaderN.y; y++) {
		for(z=0; z<src->HeaderN.z; z++) {
			mrcPixelDataGet(tmp, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);		
			if(fabs(data-1.0)<1e-6) { /* On Object */ 
				switch(neighbor) {
					case 8: 
						mrcPixelDataGet(tmp, x-1, y-1, z, &data5, mrcPixelRePart, mrcPixelHowNearest);		
						mrcPixelDataGet(tmp, x+1, y-1, z, &data6, mrcPixelRePart, mrcPixelHowNearest);		
						mrcPixelDataGet(tmp, x-1, y+1, z, &data7, mrcPixelRePart, mrcPixelHowNearest);		
						mrcPixelDataGet(tmp, x+1, y+1, z, &data8, mrcPixelRePart, mrcPixelHowNearest);		
					case 4:
						mrcPixelDataGet(tmp, x-1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);		
						mrcPixelDataGet(tmp, x+1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);		
						mrcPixelDataGet(tmp, x, y-1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);		
						mrcPixelDataGet(tmp, x, y+1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);		
						break;
					default: 
						fprintf(stderr, "Not supported Neighbor: %d\n", neighbor);	
						return;
				}
				switch(neighbor) {
					case 4: {
						if(fabs(data1)<1e-6 
						 ||fabs(data2)<1e-6 
						 ||fabs(data3)<1e-6 
						 ||fabs(data4)<1e-6) {
							mrcPixelDataSet(dst, x, y, z,  0.0, mrcPixelRePart);
						} else {
							mrcPixelDataSet(dst, x, y, z, data, mrcPixelRePart);
						}
						break;
					}
					case 8: {
						if(fabs(data1)<1e-6 
						 ||fabs(data2)<1e-6 
						 ||fabs(data3)<1e-6 
						 ||fabs(data4)<1e-6 
						 ||fabs(data5)<1e-6 
						 ||fabs(data6)<1e-6 
						 ||fabs(data7)<1e-6 
						 ||fabs(data8)<1e-6) {
							mrcPixelDataSet(dst, x, y, z,  0.0, mrcPixelRePart);
						} else {
							mrcPixelDataSet(dst, x, y, z, data, mrcPixelRePart);
						}
						break;
					}
				}
			}
		}
		}
		}
		tmp = dst;
	}
}

