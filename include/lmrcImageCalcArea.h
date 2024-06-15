/*
# lmrcImageCalcArea.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageCalcArea.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/

#ifndef __LMRC_IMAGE_CALC_AREA_H
#define __LMRC_IMAGE_CALC_AREA_H

#include "mrcImage.h"
void lmrcImageCalcArea(mrcImage* area, mrcImage* label, mrcImage* in, int neighbor, int mode);

void lmrcImageCalcDensityWeightedArea(mrcImage* densityWeightedArea, mrcImage* label, mrcImage* in, mrcImage* inDensity, int neighbor, int mode);


#endif // __LMRC_IMAGE_CALC_AREA_H
