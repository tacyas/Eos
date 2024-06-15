/*
# lJcalulation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lJcalulation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

int
lJcalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode)
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
	        j++;
	    }
    }
	return(j);
}
/*
int
lJcalculation2(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode)
{
	int    j;
    float  ntheta, nphi;
    float  dphi;
	float  thetaMax, thetaMin;
	float  phiMax, phiMin;

	switch(linfo->ModeAngularArea){
		case 0 :
			switch(linfo->ModeStartPoint){
				case 0 :
					thetaMax = THETAMAX;
					thetaMin = THETAMIN;
					phiMax   = PHIMAX;
					phiMin   = PHIMIN;
				break;
				case 1:
					thetaMax = ;
					thetaMin = ;
					phiMax   = ;
					phiMin   = ;
				break;
			}
		break;
		case 1 :
			switch(linfo->ModeStartPoint){
				case 0 :
					fprintf(stderr, "Not supported this mode ! : -maa=%d -msp=%d\n", linfo->ModeAngularArea, linfo->StartPoint);
					exit(1);
				break;
				case 1:
					thetaMax = ;
					thetaMin = ;
					phiMax   = ;
					phiMin   = ;
				break;
			}
		break;
	}

    j = 0;
	for(ntheta=THETAMIN; ntheta<=THETAMAX; ntheta+=linfo->dtheta){
        if(ntheta == 0 || ntheta == THETAMAX){
		    dphi = 2*M_PI;
	    }
	    else{
		    dphi = linfo->dtheta/sin(ntheta);
	    }
		for(nphi=PHIMIN; nphi<PHIMAX; nphi+=dphi){
	        j++;
	    }
    }
	return(j);
}
*/
