
#include "lmrcImageSphere.h"

void
lmrcImageSphere(lmrcImageSphereInfo* linfo, mrcImage* out)
{
	mrcImageParaTypeReal    x,    y,    z; /* Pixel */
	mrcImageParaTypeReal cenx, ceny, cenz;
	double data;

	out->HeaderLength.x = linfo->size;
	out->HeaderLength.y = linfo->size;
	out->HeaderLength.z = linfo->size;

	out->HeaderN.x = linfo->r*2 + 1;
	out->HeaderN.y = linfo->r*2 + 1;
	out->HeaderN.z = linfo->r*2 + 1;

	out->HeaderMode = linfo->mode;

	mrcInit(out, NULL);  /* Memory allocate */

	cenx = (out->HeaderN.x - 1)/2.0;
	ceny = (out->HeaderN.y - 1)/2.0;
	cenz = (out->HeaderN.z - 1)/2.0;

	for(x=0; x<out->HeaderN.x; x++){
		for(y=0; y<out->HeaderN.y; y++){
			for(z=0; z<out->HeaderN.z; z++){
				if ((SQR(x-cenx)+SQR(y-ceny)+SQR(z-cenz))<=SQR(linfo->r)){
					data = linfo->w;
				}else{
					data = 0;
				}
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
		}
	}
}
