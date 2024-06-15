/*
# lAllCommonLineCalculation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lAllCommonLineCalculation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

int
lAllCommonLineCalculation(
	lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, 
	lCommonLineCalculationInfo* CommonLineInfo, 
	int N, 																/* File Number */
	PlaneRotationAngle* planerotationAngle, 
	CommonLineData* Workcommonlinedata, 
	int j, 
	int mode)
{                       
	int num, l, CommonLineNum;

    if(mode == 0){
		num = 0;
	    for(l=0; l<linfo->filenum; l++){
		    if(l != N){
		        strcpy(CommonLineInfo->I1RotationalMode[num], "ZONS");
	            strcpy(CommonLineInfo->I2RotationalMode[num], "ZONS");
	            CommonLineInfo->I1Angle1[num] = planerotationAngle[j].phi;
	            CommonLineInfo->I1Angle2[num] = planerotationAngle[j].theta;
	            CommonLineInfo->I1Angle3[num] = 0;
	            CommonLineInfo->I2Angle1[num] = linfo->angle[l].phi;
	            CommonLineInfo->I2Angle2[num] = linfo->angle[l].theta;
	            CommonLineInfo->I2Angle3[num] = 0;
	            num++;
			}   
		}   
	} else if(mode == 1){
	    num = 0; 
        for(l=0; l<linfo->filenum; l++){
	        if(l != N){
	            strcpy(CommonLineInfo->I1RotationalMode[num], "ZONS");
                strcpy(CommonLineInfo->I2RotationalMode[num], "ZONS");
                CommonLineInfo->I1Angle1[num] = linfo->angle[N].phi;
                CommonLineInfo->I1Angle2[num] = linfo->angle[N].theta;
                CommonLineInfo->I1Angle3[num] = 0;
                CommonLineInfo->I2Angle1[num] = linfo->angle[l].phi;
                CommonLineInfo->I2Angle2[num] = linfo->angle[l].theta;
                CommonLineInfo->I2Angle3[num] = 0;
                num++;
			}   
		}   
	}
    num = 0;
    CommonLineNum = 0;
    for(l=0; l<linfo->filenum; l++){
	    if(l != N){
	        lCommonLineCalculation1(CommonLineInfo, num, 0);
            Workcommonlinedata[num].angleRef   = CommonLineInfo->CLAngleOnI1AgainstI2[num];
            Workcommonlinedata[num].angleOther = CommonLineInfo->CLAngleOnI2AgainstI1[num];
            Workcommonlinedata[num].flag       = CommonLineInfo->flag[num];
            Workcommonlinedata[num].num        = l;
            if(CommonLineInfo->flag[num] == 0){
	            CommonLineNum++;
            }
            num++;
		}
	}
    return(CommonLineNum);
}
