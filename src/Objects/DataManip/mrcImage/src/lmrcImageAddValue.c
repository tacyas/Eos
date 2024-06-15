/*
# lmrcImageAddValue : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageAddValue 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#undef DEBUG
#include "genUtil.h"
#include "eosCuda.h"
#include "./lmrcImageAddValue.h"

void 
lmrcImageAddValue(mrcImage* out, mrcImage* in, float value, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	clock_t t1, t2;

	DEBUGPRINT("lmrcImageAddValue Start\n");
	DEBUGCOMMAND(t1=clock());
	if(IsImage(in, "in lmrcImageAddValue", 0)) {
	  out->Header = in->Header;
	  mrcInit(out, NULL);

	  if(__eosCuda__) {
#ifdef CUDA
	  	lmrcImageAddValueCuda(out->ImageFloatImage, in->ImageFloatImage, value, in->PixelPerImage, in->HeaderMode, mode);
#else
		fprintf(stderr, "Not supported CUDA\n");
		exit(EXIT_FAILURE);	
#endif
	  } else { 
	  	for(z=0; z<in->HeaderN.z; z++) {
	    for(y=0; y<in->HeaderN.y; y++) {
	    for(x=0; x<in->HeaderN.x; x++) {
		    mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
		    mrcPixelDataSet(out, x, y, z, data+value, mrcPixelRePart);
	    }
	    }
	    }
	  }
	  mrcStatDataSet(out, 0);
	} else {
		fprintf(stderr, "Not supported image mode: Not Image\n"); 
		exit(EXIT_FAILURE);
	}
	DEBUGCOMMAND(t2=clock());
	DEBUGPRINT1("%d", t2-t1);
	DEBUGPRINT("lmrcImageAddValue End\n");
}

