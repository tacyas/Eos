/*
# lmrcSinogramFETsmoothParameterMatching : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETsmoothParameterMatching 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdlib.h>
#include <string.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "File.h"
#include "../inc/mrcImage.h"
#include "lmrcSinogramFET.h"
#include "lmrcSinogramFETsmoothParameterMatching.h"
										
static int __countListLength(FILE* list,int mode);

void 
lmrcSinogramFETsmoothParameterMatching(lmrcSinogramFETsmoothParameterMatchingInfo info, int mode)
{
	int i,j,k;
	double data, dataSTD, ans;
	mrcImage cFile;
	mrcImage cFET, stdFET, cFETsm;
	int n;
	char s[512];
	//fprintf(stdout,"in function\n"); 
	lmrcSinogramFETInfo linfoS;
	linfoS.flagsm = 0; 
	lmrcSinogramFET(info.InSTD, &stdFET, linfoS, 0);
	info.listLength = __countListLength(info.InList,0);
	fseek(info.InList, 0L, SEEK_SET);
	//fprintf(stdout,"before while\n");
	while(NULL!=stringGetFromFile(s,"",info.InList,stdout,1)){
		fprintf(stdout,"%s\n",s);
		mrcFileRead(&cFile, s, "in lmrcSinogramFETsmoothParameterMatching",0);
		lmrcSinogramFET(&cFile, &cFET, linfoS, 0);
		for(k=1; k<60; k=k+2){
			fprintf(stdout,"%d, ",k);
			sinogramFETsmoothing(&cFET, &cFETsm, k, 0);
			for(i=1; i<stdFET.HeaderN.x ;i++){
				ans=0.0;
				for(j=0; j<stdFET.HeaderN.y ;j++){
					mrcPixelDataGet(&cFETsm,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&stdFET,i,j,0,&dataSTD, mrcPixelRePart, mrcPixelHowNearest);
					ans += pow((data-dataSTD),2);
					//if(i==5) fprintf(stderr,"data: %f\tdataSTD: %f\tans: %f\n",data,dataSTD,ans);
				}
				ans = pow(ans,0.5);
				fprintf(stdout,"%15.11f ",ans);
				//getchar();
			}
			fprintf(stdout,"\n");
		}
	}
}

int
__countListLength(FILE* list,int mode)
{
    long ans=0;
    char s[512];

    fseek(list, 0L, SEEK_SET);
    while(NULL!=stringGetFromFile(s,"",list,stdout,1))
        ans++;
    return(ans);
}

