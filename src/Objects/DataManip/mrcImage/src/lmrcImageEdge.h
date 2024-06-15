/*
# lmrcImageEdge.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageEdge.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "mrcImage.h"


int lmrcImageIsEdge(mrcImage* bin, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, int neighbor, int mode);
void lmrcImageEdgeCalc(mrcImage* out, mrcImage* in, int neighbor, int mode);
void lmrcImageSurfaceCalc(mrcImage* out, mrcImage* in, int neighbor, int mode);

