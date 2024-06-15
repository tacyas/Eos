/*
# lInitialDataFileRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lInitialDataFileRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

void
lInitialDataFileRead(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, FILE* fpt, int mode)
{
	int   i, num;
    char* s;

    s = MemoryAllocate(char, WORDLEN, "in lInitialDataFileRead");

    fseek(fpt, 0L, SEEK_SET);
    num = 0;
    while(fgets(s, WORDLEN-1, fpt) != NULL){
	    num++;
    }
    fprintf(stdout, "num = %d\n", num);
    fseek(fpt, 0L, SEEK_SET);
    for(i=0; i<num; i++){
	    stringGetFromFile(s, "", fpt, stdout, 3);
        linfo->angle[i].phi   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
        linfo->angle[i].theta = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
        linfo->angle[i].psi   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
    }
    free(s);
    fclose(fpt);
}
