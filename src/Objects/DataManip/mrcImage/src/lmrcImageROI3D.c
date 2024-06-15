
#include "lmrcImageROI3D.h"

void
lmrcImageROI3D( mrcImage* out,
				mrcImage* in,
				lmrcImageROI3DInfo* linfo)
{
	mrcImageParaTypeReal x,y,z;
	mrcImageParaTypeReal shiftx, shifty, shiftz;
	mrcImageParaTypeReal nx, ny, nz;
	double data=0;

	out->Header = in->Header;
	
	if(!linfo->flagx) {
		linfo->x1 = 0;
		linfo->x2 = in->HeaderN.x;
	}
	nx = linfo->x2 - linfo->x1;

	if(!linfo->flagy) {
		linfo->y1 = 0;
		linfo->y2 = in->HeaderN.y;
	}
	ny = linfo->y2 - linfo->y1;

	/* no use of flagz for compatibility */
	nz = linfo->z2 - linfo->z1;

	out->HeaderN.x = nx; 
	out->HeaderN.y = ny; 
	out->HeaderN.z = nz; 
	mrcInit(out, NULL);

	for(x=0; x<nx; x++) {
		for(y=0; y<ny; y++) {
			for(z=0; z<nz; z++) {
				shiftx = linfo->x1 + x;
				shifty = linfo->y1 + y;
				shiftz = linfo->z1 + z;
	        	mrcPixelDataGet(in , shiftx, shifty, shiftz, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, x, y, z     ,  data, mrcPixelRePart);
			}			
		}
	}

}

