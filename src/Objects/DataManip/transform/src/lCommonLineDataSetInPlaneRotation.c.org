/*
# lCommonLineDataSetInPlaneRotation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lCommonLineDataSetInPlaneRotation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

void
lCommonLineDataSetInPlaneRotation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, CommonLineData* commonlinedata,
								  CommonLineData* commonlinedataWithPlaneRotation, int PlaneRotationNum, int CommonLineNum, int i,
								  int* PlaneRotationFileNum, mrcImage* ref, int mode)
{
	int l, ll;

    if(mode == 0){
	    for(l=0; l<CommonLineNum; l++){
	        commonlinedataWithPlaneRotation[l].num        = commonlinedata[l].num;
            commonlinedataWithPlaneRotation[l].angleRef   = commonlinedata[l].angleRef   + (i*linfo->dpsi);
            commonlinedataWithPlaneRotation[l].angleOther = commonlinedata[l].angleOther + linfo->angle[commonlinedataWithPlaneRotation[l].num].psi;
        }
        for(ll=0; ll<PlaneRotationNum; ll++){
	        for(l=0; l<ref->HeaderN.y; l++){
	            commonlinedataWithPlaneRotation[l+CommonLineNum+ll*ref->HeaderN.y].angleRef   = l*ref->HeaderLength.y*RADIAN + (i*linfo->dpsi);
                commonlinedataWithPlaneRotation[l+CommonLineNum+ll*ref->HeaderN.y].angleOther = l*ref->HeaderLength.y*RADIAN + linfo->angle[PlaneRotationFileNum[ll]].psi;
                commonlinedataWithPlaneRotation[l+CommonLineNum+ll*ref->HeaderN.y].num        = PlaneRotationFileNum[ll];
            }
        }
	}
    else if(mode == 1){
	    for(l=0; l<CommonLineNum; l++){
	        commonlinedataWithPlaneRotation[l].num        = commonlinedata[l].num;
            commonlinedataWithPlaneRotation[l].angleRef   = commonlinedata[l].angleRef   + linfo->angle[i].psi;
            commonlinedataWithPlaneRotation[l].angleOther = commonlinedata[l].angleOther + linfo->angle[commonlinedataWithPlaneRotation[l].num].psi;
        }
        for(ll=0; ll<PlaneRotationNum; ll++){
	        for(l=0; l<ref->HeaderN.y; l++){
	            commonlinedataWithPlaneRotation[l+CommonLineNum+ll*ref->HeaderN.y].angleRef   = l*ref->HeaderLength.y*RADIAN + linfo->angle[i].psi;
                commonlinedataWithPlaneRotation[l+CommonLineNum+ll*ref->HeaderN.y].angleOther = l*ref->HeaderLength.y*RADIAN + linfo->angle[PlaneRotationFileNum[ll]].psi;
                commonlinedataWithPlaneRotation[l+CommonLineNum+ll*ref->HeaderN.y].num        = PlaneRotationFileNum[ll];
            }
        }
	}

    for(l=0; l<CommonLineNum+(PlaneRotationNum*ref->HeaderN.y); l++){
	    commonlinedataWithPlaneRotation[l].angleRef   = fmod(commonlinedataWithPlaneRotation[l].angleRef,   2*M_PI);
        commonlinedataWithPlaneRotation[l].angleOther = fmod(commonlinedataWithPlaneRotation[l].angleOther, 2*M_PI);
        if(commonlinedataWithPlaneRotation[l].angleRef > 2*M_PI-(M_PI/180/2) || commonlinedataWithPlaneRotation[l].angleRef < M_PI/180/2){
	        commonlinedataWithPlaneRotation[l].angleRef = 0.0;
        }
        if(commonlinedataWithPlaneRotation[l].angleOther > 2*M_PI-(M_PI/180/2) || commonlinedataWithPlaneRotation[l].angleOther < M_PI/180/2){
            commonlinedataWithPlaneRotation[l].angleOther = 0.0;
        }
    }
}
