/*
# lFETsmallMapSetCreate_forSimultaneousMinimization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETsmallMapSetCreate_forSimultaneousMinimization 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */


#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "File.h"
#include "../../mrcImage/inc/mrcImage.h"
#include "lFETsmallMapSetCreate_forSimultaneousMinimization.h"
#define INX 360
#define INY 360
static int __countFileLines(FILE* in);

void
lFETsmallMapSetCreate_forSimultaneousMinimization(lFETsmallMapSetCreate_forSimultaneousMinimizationInfo info, int mode)
{
	int i,j,k,l,m,n;
	int x,y,z,az,dr;
	mrcImage in;
	mrcImage inter;
	char s[256];
	double cur, data;
	mrcImageInformation mrcInfo;
    
	x = INX/info.ss;
	y = x/2;
	z = __countFileLines(info.InML);
	fseek(info.InML, 0L, SEEK_SET);
	stringGetFromFile(s,"",info.InML,stdout,1);
	mrcFileRead(&in, s, "in lFETsmallMapSetCreate",0);
	info.Out->Header = in.Header; inter.Header = in.Header;
	info.Out->HeaderN.x = inter.HeaderN.x = x;
	info.Out->HeaderN.y = y; inter.HeaderN.y = x;
	info.Out->HeaderN.z = inter.HeaderN.z = z;
	mrcInit(info.Out,NULL); mrcInit(&inter,NULL);
	
	fseek(info.InML, 0L, SEEK_SET);
	az=0;
	while(NULL!=stringGetFromFile(s,"",info.InML,stdout,1)){
		mrcFileRead(&in, s, "in lFETsmallMapSetCreate",0);
		for(i=0,m=0;i<INX;i+=info.ss,m++){ for(j=0,n=0;j<INY;j+=info.ss,n++){
			mrcPixelDataGet(&in,i,j,0,&cur, mrcPixelRePart, mrcPixelHowNearest);
			for(k=i;k<i+info.ss;k++){ for(l=j;l<j+info.ss;l++){
				mrcPixelDataGet(&in,l,k,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				if(cur>data) cur = data;
			}}
			mrcPixelDataSet(&inter,m,n,az,cur, mrcPixelRePart);
		}}
		az++;
	}
	dr = (info.sr/info.ss) - 1;
	for(az=0;az<z;az++){
		for(i=0;i<x;i++){ for(j=0;j<y;j++){
			mrcPixelDataGet(&inter,i,j,az,&cur, mrcPixelRePart, mrcPixelHowNearest);
			for(k=i-dr;k<i+dr+1;k++){ for(l=j-dr;l<j+dr+1;l++){
				mrcPixelDataGet(&inter,k,l,az,&data, mrcPixelRePart, mrcPixelHowNearest);
				if(cur>data) cur = data;
			}}
			mrcPixelDataSet(info.Out,i,j,az,cur, mrcPixelRePart);
		}}
	}
	mrcStatDataSet(info.Out,0);
}


int __countFileLines(FILE* in)
{
    int i;
    char s[256];

    fseek(in, 0L, SEEK_SET);
    i=0;
    while(NULL!=stringGetFromFile(s,"",in,stdout,1)) i++;

    return i;
}
										
