/*
# lmrcFETnormalizeBySD : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcFETnormalizeBySD 
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
#include "lmrcFETnormalizeBySD.h"

static long __countListLength(FILE* list,int mode);

void
lmrcFETnormalizeBySD(lmrcFETnormalizeBySDInfo info, int mode)
{
	double* ave;
	double* sd;
	double data;
	int n;
	mrcImage cFile;
	int i,j,k;
	 
	char s[512];

	fseek(info.InSampleList, 0L, SEEK_SET);
	stringGetFromFile(s,"",info.InSampleList,stdout,1);
	mrcFileRead(&cFile, s, "in lmrcFETnormalizeBySD", 0);
	n=cFile.HeaderN.x;

	ave = (double*)memoryAllocate(sizeof(double)*n,"in lmrcFETnormalizeBySD");
	sd = (double*)memoryAllocate(sizeof(double)*n,"in lmrcFETnormalizeBySD");
	for(i=0;i<n;i++){
		ave[i]=0.0;
		sd[i]=0.0;
	}
	info.listLength = __countListLength(info.InList,0);
	
	if(info.flagReadSD){
		for(i=0;i<n;i++){
			mrcPixelDataGet(info.readSD,i,0,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			ave[i]=data;
			mrcPixelDataGet(info.readSD,i,1,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			sd[i]=data;
		}
	}else{
		calcSDofFET(info.InSampleList, n, ave, sd, 0);
	}
	if(info.flagWriteSD){
		DEBUGPRINT("in flagWriteSD\n");
		info.writeSD->Header = cFile.Header;
		info.writeSD->HeaderN.x=n;
		info.writeSD->HeaderN.y=2;
		info.writeSD->HeaderMode = mrcFloatImage;	
		DEBUGPRINT1("writeSDMode %d\n", info.writeSD);
		mrcInit(info.writeSD,NULL);
		for(i=0;i<n;i++){
			mrcPixelDataSet(info.writeSD,i,0,0,ave[i], mrcPixelRePart);
			mrcPixelDataSet(info.writeSD,i,1,0,sd[i], mrcPixelRePart);
		}
		DEBUGPRINT1("writeSDMode %d\n", info.writeSD);
		mrcStatDataSet(info.writeSD,0);
	}
			
	for(i=0;i<n;i++)
		fprintf(stdout,"%f  %f\n",ave[i],sd[i]);
	
	_normalizeBySDandDataWrite(info.InList, n, ave, sd, info, 0);
	
}

long
__countListLength(FILE* list,int mode)
{
	long ans=0;
	char s[512];
	
	fseek(list, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",list,stdout,1))
		ans++;
	return(ans);
}
	
void
_normalizeBySDandDataWrite(FILE* list, int n, double* ave, double* sd, lmrcFETnormalizeBySDInfo info, int mode)
{
	int i;
	mrcImage cFile;
	mrcImage nord;
	long l=0;
	char s[512];
	char ss[512];
	double data;
	
	fseek(list, 0L, SEEK_SET);
	stringGetFromFile(s,"",list,stdout,1);
	mrcFileRead(&cFile, s, "in normalizeBySDandDataWrite", 0);
	nord.Header = cFile.Header;
	mrcInit(&nord,NULL);

	if(info.flagOut){
		info.Out->Header = cFile.Header;
		info.Out->HeaderN.x = n;
		info.Out->HeaderN.y = info.listLength;
		mrcInit(info.Out,NULL);
	}
	
	fseek(list, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",list,stdout,1)){
		mrcFileRead(&cFile, s, "in normalizeBySDandDataWrite", 0);
		for(i=0;i<n;i++){
			mrcPixelDataGet(&cFile,i,0,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			data -= ave[i];
			data /= sd[i];
			mrcPixelDataSet(&nord,i,1,0,data, mrcPixelRePart);
			if(info.flagOut) mrcPixelDataSet(info.Out,i,l,0,data, mrcPixelRePart);
		}
		mrcStatDataSet(&nord,0);
		strcat(s,".nord");
		mrcFileWrite(&nord,s,"in normalizeBySDandDataWrite", 0);
		l++;
	}
	if(info.flagOut) mrcStatDataSet(info.Out,0);
}

void 
calcSDofFET(FILE* list, int n, double* ave, double* sd, int mode)
{
	int i;
	long count=0;
	mrcImage cFile;
	char s[512];
	double data;

	fseek(list, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",list,stdout,1)){
		count += 1;
	}
	fseek(list, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",list,stdout,1)){
		mrcFileRead(&cFile, s, "in lmrcFETnormalizeBySD", 0);
		for(i=0;i<n;i++){
			mrcPixelDataGet(&cFile,i,0,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			ave[i] += data/(double)count;
		}
	}
	fseek(list, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",list,stdout,1)){
		mrcFileRead(&cFile, s, "in lmrcFETnormalizeBySD", 0);
		for(i=0;i<n;i++){
			mrcPixelDataGet(&cFile,i,0,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			sd[i] += pow((data-ave[i]),2)/(double)count;
		}
	}
	for(i=0;i<n;i++)
		sd[i] = pow(sd[i],0.5);
}
	


