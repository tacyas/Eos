/*
# lPlaneRotationAngleSet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lPlaneRotationAngleSet 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

void
lPlaneRotationAngleSet(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, PlaneRotationAngle* planerotationAngle, int mode)
{
	int    j;
    float  ntheta, nphi;
    float  dphi;

    j = 0;
    for(ntheta=THETAMIN; ntheta<=THETAMAX; ntheta+=linfo->dtheta){
		if(ntheta == 0 || ntheta == THETAMAX){
		    dphi = 2*M_PI;
	    }   
	    else{
	        dphi = linfo->dtheta/sin(ntheta);
	    }   
	    for(nphi=PHIMIN; nphi<PHIMAX; nphi+=dphi){
	        planerotationAngle[j].phi   = nphi;
	        planerotationAngle[j].theta = ntheta;
	        j++;
	    }   
	}   
}   
