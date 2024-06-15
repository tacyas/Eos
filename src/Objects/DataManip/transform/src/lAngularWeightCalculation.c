/*
# lAngularWeightCalculation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lAngularWeightCalculation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

int
cmp(const CommonLineData* a, const CommonLineData* b);

void
lAngularWeightCalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, CommonLineData* commonlinedata, int CommonLineNum, int mode)
{
	int i, j;
    int before, after;
    int count;
    float angleBefore, angleAfter;
	float* work;
	float  workAngle;
	float  threshold;
	int flag;

    /****************************************************/
    /* in Ultramicroscopy 63 (1996) 205-218 P.A.Penczek */
    /*                                                  */
    /*  p209 >> alfa = (beta12 - beta23)/2              */
    /*                                                  */
    /*  Here is alfa = (beta12 + beta23)/2              */
    /****************************************************/

	switch(linfo->ModeThresholdAngular){
		case 0 :
			threshold = 1.0e-4;
		break;
		case 1 :
			threshold = M_PI/180;
		break;
		case 2 :
			threshold = linfo->dpsi;
		break;
	}

	if(CommonLineNum > 2){
		work = MemoryAllocate(float, CommonLineNum, "in lAngularWeightCalculation");
		work[0] = commonlinedata[0].angleRef;
		count = 1;
		for(i=1; i<CommonLineNum; i++){
			flag = 0;
			for(j=0; j<count; j++){
				if(fabs(commonlinedata[i].angleRef - work[j]) < threshold){
					flag++;
				}
			}
			if(flag == 0){
				work[count] = commonlinedata[i].angleRef;
				count++;
			}
			else if(flag == 1){
			}
			else {
				fprintf(stderr, "error : in lAngularWeightCalculation\n");
			}
		}
		/*	
	    count = 0;
        for(i=0; i<CommonLineNum; i++){
	        //if(commonlinedata[0].angleRef != commonlinedata[i].angleRef){
	        if(fabs(commonlinedata[0].angleRef - commonlinedata[i].angleRef) >= threshold){
	            count++;
            }
        }
		*/

	    if(count == 1){
	        for(i=0; i<CommonLineNum; i++){
		        commonlinedata[i].angularweight = 2*M_PI/CommonLineNum;
	        }
	    }
	    else if(count == 2){
	        workAngle = commonlinedata[0].angleRef;
			j = 0;
	        for(i=1; i<CommonLineNum; i++){
		        if(fabs(commonlinedata[i].angleRef - workAngle) < threshold){
		            j++;
	            }
	        }
	        for(i=0; i<CommonLineNum; i++){
	            if(fabs(commonlinedata[i].angleRef - workAngle) < threshold){
	                commonlinedata[i].angularweight = M_PI/j;
	            }
	        	else{
	            	commonlinedata[i].angularweight = M_PI/(CommonLineNum - j);
	        	}
			}
		}
    	else{
		    qsort(commonlinedata, CommonLineNum, sizeof(CommonLineData), cmp);

    	    for(i=0; i<CommonLineNum; i++){
        	    after = i;
            	do{
		            after++;
    	            if(after > CommonLineNum-1){
        	            after -= CommonLineNum;
            	    }
	            }while(fabs(commonlinedata[i].angleRef - commonlinedata[after].angleRef) < threshold);
    	        before = i;
        	    do{
            	    before--;
                	if(before < 0){
		                before += CommonLineNum;
    	            }
        	    }while(fabs(commonlinedata[i].angleRef - commonlinedata[before].angleRef) < threshold);

            	if(after < i){
                	angleAfter = MIN(commonlinedata[after].angleRef + (2*M_PI - commonlinedata[i].angleRef),
	                                 commonlinedata[i].angleRef     - commonlinedata[after].angleRef);
    	        }
        	    else{
            	      angleAfter = MIN(          commonlinedata[after].angleRef - commonlinedata[i].angleRef,
                	                   2*M_PI - (commonlinedata[after].angleRef - commonlinedata[i].angleRef));
	            }
    	        if(before > i){
        	        angleBefore = MIN(commonlinedata[i].angleRef      + (2*M_PI - commonlinedata[before].angleRef),
            	                      commonlinedata[before].angleRef - commonlinedata[i].angleRef);
            	}
	            else{
					angleBefore = MIN(          commonlinedata[i].angleRef - commonlinedata[before].angleRef,
					                  2*M_PI - (commonlinedata[i].angleRef - commonlinedata[before].angleRef));
				}

            	if(angleAfter < threshold || angleBefore < threshold){
                	fprintf(stderr, "error : angleAfter or angleBefore is smaller than threshold !! >> after = %d, %f before = %d, %f threshold = %f\n",
                    	    after, commonlinedata[after].angleRef, before, commonlinedata[before].angleRef, threshold);
            	}

	            commonlinedata[i].angularweight  = (angleAfter + angleBefore)/2;
    	        if(after < i || before > i){
        	        commonlinedata[i].angularweight /= after-before+CommonLineNum-1;
	            }
    	        else{
        	        commonlinedata[i].angularweight /= after-before-1;
            	}
			}
		}
		free(work);
	}
    else if(CommonLineNum == 2){
	    commonlinedata[0].angularweight = M_PI;
        commonlinedata[1].angularweight = M_PI;
    }
    else if(CommonLineNum == 1){
        commonlinedata[0].angularweight = 2*M_PI;
    }
}

int
cmp(const CommonLineData* a, const CommonLineData* b)
{
	float differential;
    int   value;

    differential = a->angleRef - b->angleRef;
    if(differential == 0){
	    value = 0;
    }
    else if(differential > 0){
        value = 1;
    }
    else{
        value = -1;
    }
    return(value);
}
																
