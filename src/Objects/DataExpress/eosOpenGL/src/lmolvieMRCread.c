/*
# lmolviePDBRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolviePDBRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mrcImage.h"

static mrcImage* mrcIn;

void lmolvieMRCread(char* filename)
{
	double data;

	mrcIn= (mrcImage*)malloc(sizeof(mrcImage));
	mrcFileRead(mrcIn, filename, "from main", 0);

	fprintf(stderr, "Size: %d %d %d\n", mrcIn->HeaderN.x, mrcIn->HeaderN.y, mrcIn->HeaderN.z);
	fprintf(stderr, "%f at (0,0,0)\n", mrcIn->ImageFloatImage[0+0*mrcIn->HeaderN.x+0*mrcIn->HeaderN.x*mrcIn->HeaderN.y]);
	mrcPixelDataGet(mrcIn, 1, 1, 1, &data, mrcPixelRePart, mrcPixelHowNearest);
	fprintf(stderr, "%f at (1, 1, 1)\n", data);
}

mrcImage* get_mrc(void)
{
	return mrcIn;
}
