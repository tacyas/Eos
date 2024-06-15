#include "../inc/mrcImage.h"

void
lmrcImageToIntImage(mrcImage* dst, mrcImage* src, mrcImageParaTypeInteger mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;

	if(src->HeaderAMin==src->HeaderAMax) {
		mrcStatDataSet(src, 0);
	}
	dst->Header = src->Header;
	dst->HeaderMode = mode;
	mrcInit(dst, NULL);
	for(x=0; x<dst->HeaderN.x; x++) {
		for(y=0; y<dst->HeaderN.y; y++) {
			for(z=0; z<dst->HeaderN.z; z++) {
				mrcPixelDataGet(src, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(src->HeaderAMin<src->HeaderAMax) {
					if(data<src->HeaderAMin) {
						data = src->HeaderAMin;
					}
					if(src->HeaderAMax<data) {
						data = src->HeaderAMax;
					}
					data = (data - src->HeaderAMin)/(src->HeaderAMax - src->HeaderAMin); 
				} else if(src->HeaderAMin>src->HeaderAMax) {
					if(data<src->HeaderAMax) {
						data = src->HeaderAMax;
					}
					if(src->HeaderAMin<data) {
						data = src->HeaderAMin;
					}
					data = (src->HeaderAMin - data)/(src->HeaderAMin - src->HeaderAMax); 
				} else {
					data = 0;
					//fprintf(stderr, "Not supported in lmrcImageToIntImage \n");
				}
				switch(dst->HeaderMode) {
					case mrcCharImage: {
						mrcPixelDataSet(dst, x, y, z, data*255.0, mrcPixelRePart);
						break;
					}
					case mrcShortImage: {
						mrcPixelDataSet(dst, x, y, z, data*65535.0, mrcPixelRePart);
						break;
					}
					case mrcLongImage: {
						mrcPixelDataSet(dst, x, y, z, data*(65536.0*65536-1.0), mrcPixelRePart);
						break;
					}
					default: {
						fprintf(stderr, "Not supported mode : %ld \n", dst->HeaderMode);
						break;
					}
				}
			}
		}
	}
	mrcStatDataSet(dst, 0);
}
