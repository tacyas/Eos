/*
# lmrcImageSplit : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageSplit 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <string.h>
#include "Memory.h"
#include "./lmrcImageSplit.h"

void
lmrcImageSplit(mrcImage* in, lmrcImageSplitInfo* linfo, int mode)
{
	mrcImageParaTypeIntegerCoord N;
	mrcImageParaTypeIntegerCoord n;
	mrcImageParaTypeIntegerCoord Size;
	int i;

	Size = linfo->Size;
	if(0<linfo->Size.x) {
		N.x = in->HeaderN.x/linfo->Size.x; 
	} else {
		N.x = 1;
		Size.x = in->HeaderN.x;
	}
	if(0<linfo->Size.y) {
		N.y = in->HeaderN.y/linfo->Size.y; 
	} else {
		N.y = 1;
		Size.y = in->HeaderN.y;
	}
	if(0<linfo->Size.z) {
		N.z = in->HeaderN.z/linfo->Size.z; 
	} else {
		N.z = 1;
		Size.z = in->HeaderN.z;
	}

	linfo->N = N.x*N.y*N.z;
	linfo->FileName = (char**)memoryAllocate(sizeof(char*)*linfo->N, "in lmrcImageSplit");	
	linfo->Out      = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo->N, "in lmrcImageSplit");	
	for(i=0; i<linfo->N; i++) {
		linfo->Out[i].Header        = in->Header; 
		linfo->Out[i].Header.Cont.N = Size; 
		mrcInit(&linfo->Out[i], NULL);
	}

	i = 0;
	for(n.z=0; n.z<N.z; n.z++) {
	for(n.y=0; n.y<N.y; n.y++) {
	for(n.x=0; n.x<N.x; n.x++) {
		char suffix[1024];
		char filename[1024];
		int  ix, iy, iz;
		mrcImageParaTypeReal x, y, z;
		int  offsetx, offsety, offsetz;
		double data;

		if(linfo->suffix!=NULL || linfo->filename!=NULL) { 
			sprintf(suffix, linfo->suffix, n.x, n.y, n.z);
			sprintf(filename, "%s.%s", linfo->filename, suffix);
			linfo->FileName[i] = strdup(filename);
		}

		offsetx = n.x*Size.x;
		offsety = n.y*Size.y;
		offsetz = n.z*Size.z;

		for(ix=0; ix<Size.x; ix++) {
			x = ix + offsetx;
		for(iy=0; iy<Size.y; iy++) {
			y = iy + offsety;
		for(iz=0; iz<Size.z; iz++) {
			z = iz + offsetz;

			mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataSet(linfo->Out+i, ix, iy, iz, data, mrcPixelRePart);
		}
		}
		}

		i++;
	}
	}
	}
}

