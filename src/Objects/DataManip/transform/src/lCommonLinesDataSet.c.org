/*
# lCommonLinesDataSet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lCommonLinesDataSet 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

int
lCommonLinesDataSet(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, CommonLineData* Workcommonlinedata, CommonLineData* commonlinedata, int mode)
{
	int i, l, PlaneRotationNum;

    PlaneRotationNum = 0;
    l = 0;
    for(i=0; i<linfo->filenum-1; i++){
	    if(Workcommonlinedata[i].flag == 0){
	        commonlinedata[l].angleRef   = Workcommonlinedata[i].angleRef;
            commonlinedata[l].angleOther = Workcommonlinedata[i].angleOther;
            commonlinedata[l].num        = Workcommonlinedata[i].num;
            l++;
        }
        else if(Workcommonlinedata[i].flag == 1){
            PlaneRotationNum++;
        }
        else{
            fprintf(stderr, "error : CommonLineCalculation is fault !!\n");
            exit(1);
        }
	}
    return(PlaneRotationNum);
}
