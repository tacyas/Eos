/*
# lmrcImageConnectivityNumberCalc.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageConnectivityNumberCalc.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#ifndef MRC_CONNECTIVITY_NUMBER_CALC_H
#define MRC_CONNECTIVITY_NUMBER_CALC_H

#include <stdio.h>
#include "mrcImage.h"

#define NEIGHBORHOOD   (9)
#define NEIGHBORHOOD3D (27)
#define Z_LINE (3)

extern void lmrcImageConnectivityNumberCalc(mrcImage* in, mrcImage* out, int mode, int form,int invers);
extern void lmrcImageConnectivityNumberCalc_ver2D(mrcImage* in, mrcImage* out, int mode, int form,int invers);
extern void lmrcImageConnectivityNumberCalc_ver3D(mrcImage* in, mrcImage* out, int mode, int form);
extern void mrcNinePixelDataGet(mrcImage* in,mrcImage* out,mrcImageParaTypeReal x,mrcImageParaTypeReal y,mrcImageParaTypeReal z,double data[]);
extern void mrc27PixelDataGet(mrcImage* in, mrcImageParaTypeReal x,mrcImageParaTypeReal y,mrcImageParaTypeReal z,double data[]);

#endif
