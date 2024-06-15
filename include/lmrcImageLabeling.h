/*
# lmrcImageLabeling.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageLabeling.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "mrcImage.h"

void lmrcImageLabelingUsage(FILE* fpt);
void lmrcImageLabeling(mrcImage* label, mrcImage* in, int neighbor, int mode);
void lmrcImageLabelingOrder(mrcImage* label, int mode);
void lmrcImageLabeling2D(mrcImage* label, mrcImage* in, int neighbor, int mode);
void lmrcImageLabeling3D(mrcImage* label, mrcImage* in, int neighbor, int mode);
