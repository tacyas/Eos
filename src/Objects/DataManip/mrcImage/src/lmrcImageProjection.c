/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageProjection.o ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageProjection.o 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageProjection.o ver%I%; Date:%D% %Z%";

#include "lmrcImageProjection.h"

void
lmrcImageProjection( mrcImage* out, mrcImage* in,
				    lmrcImageProjectionInfo* linfo)
{
	mrcImageParaTypeReal x, y, z;
	double data, dataout;

	switch(linfo->mode) {
	case 0: { // along z-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.x;
	  out->HeaderN.y = in->HeaderN.y;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, x, y, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, x, y, 0.0, dataout+data, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	}
	case 1: { // along x-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.y;
	  out->HeaderN.y = in->HeaderN.z;
	  out->HeaderN.z = 1;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, y, z, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, y, z, 0.0, dataout+data, mrcPixelRePart);
	  }
	  }
	  }
	  break;
   	}
	case 2: { // along y-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.z;
	  out->HeaderN.y = in->HeaderN.x;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, z, x, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, z, x, 0.0, dataout+data, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	}
	case 3: { // to y-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.y;
	  out->HeaderN.y = 1.0;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, y, 0.0, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, y, 0.0, 0.0, dataout+data, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	}
	case 4: { // to x-axis
	  out->Header = in->Header;
	  out->HeaderN.y = 1.0;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, x, 0.0, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, x, 0.0, 0.0, dataout+data, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	} 
	case 5: { // to z-axis
	  out->Header = in->Header;
	  out->HeaderN.x = out->HeaderN.z;
	  out->HeaderN.y = 1.0;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, z, 0.0, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, z, 0.0, 0.0, dataout+data, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	} 
 	default: {
	  fprintf(stderr, "Not supported Mode: %ld\n", linfo->mode);
	}
  }
}


void
lmrcImageProjectionMIP( mrcImage* out, mrcImage* in,
				    lmrcImageProjectionInfo* linfo)
{
	mrcImageParaTypeReal x, y, z;
	double data, dataout;

	switch(linfo->mode) {
	case 0: { // along z-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.x;
	  out->HeaderN.y = in->HeaderN.y;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, x, y, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
            if(dataout<data) dataout = data;
			mrcPixelDataSet(out, x, y, 0.0, dataout, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	}
	case 1: { // along x-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.y;
	  out->HeaderN.y = in->HeaderN.z;
	  out->HeaderN.z = 1;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, y, z, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
            if(dataout<data) dataout = data;
			mrcPixelDataSet(out, y, z, 0.0, dataout, mrcPixelRePart);
	  }
	  }
	  }
	  break;
   	}
	case 2: { // along y-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.z;
	  out->HeaderN.y = in->HeaderN.x;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, z, x, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
            if(dataout<data) dataout = data;
			mrcPixelDataSet(out, z, x, 0.0, dataout, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	}
	case 3: { // to y-axis
	  out->Header = in->Header;
	  out->HeaderN.x = in->HeaderN.y;
	  out->HeaderN.y = 1.0;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, y, 0.0, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
            if(dataout<data) dataout = data;
			mrcPixelDataSet(out, y, 0.0, 0.0, dataout, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	}
	case 4: { // to x-axis
	  out->Header = in->Header;
	  out->HeaderN.y = 1.0;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, x, 0.0, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
            if(dataout<data) dataout = data;
			mrcPixelDataSet(out, x, 0.0, 0.0, dataout, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	} 
	case 5: { // to z-axis
	  out->Header = in->Header;
	  out->HeaderN.x = out->HeaderN.z;
	  out->HeaderN.y = 1.0;
	  out->HeaderN.z = 1.0;
	  mrcInit(out, NULL);
	  for(z=0; z<in->HeaderN.z; z++) {
	  for(y=0; y<in->HeaderN.y; y++) {
	  for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(out, z, 0.0, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
            if(dataout<data) dataout = data;
			mrcPixelDataSet(out, z, 0.0, 0.0, dataout, mrcPixelRePart);
	  }
	  }
	  }
	  break;
	} 
 	default: {
	  fprintf(stderr, "Not supported Mode: %ld\n", linfo->mode);
	}
  }
}


