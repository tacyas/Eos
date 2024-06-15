/*
# mrcImageROItoPCAoutputImage : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageROItoPCAoutputImage
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <time.h>
#include "File.h"

#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImageROItoPCAoutputImage.h"
#include "mrcImage.h"
#define PCselectionFile "PCselection.txt" 

/*
typedef struct lmrcImageROItoPCAoutputImageInfo {
//	float a;
//	int   b;
} lmrcImageROItoPCAoutputImageInfo;
*/
/*
Example:
typedef enum lmrcImageROItoPCAoutputImageMode {
	a=0,
	b=1
} lmrcImageROItoPCAoutputImageMode;
*/
FILE *fp_in;

void lmrcImageROItoPCAoutputImage(mrcImage* Out, int nOut, mrcImage* In, int nIn, int *nPC, int PC[100],int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageROItoPCAoutputImageInfo info;
	mrcImage* In;
	mrcImage* Out;
	int nPC=0;
	int PC[100];
	int i;


	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	if((fp_in=fopen(PCselectionFile,"r"))==NULL){ 
		printf("No PCselectionFile\n");
	}

	In  = (mrcImage*)MemoryAllocate(mrcImage, info.flagInList, "in main");
	for(i=0; i<info.flagInList; i++) {
		mrcFileRead(&In[i], info.InList[i], "in main", 0);
		if(i%100==0)
			DEBUGPRINT1("mrcFileRead  %d th Read\n",i);
	}
	for(i=0;i<100;i++)
		PC[i]=NULL;

	while(fscanf(fp_in,"%d",&PC[nPC])!=EOF){
		nPC++;
	}

	for(i=0;i<100;i++){
		if(i>nPC)
			PC[i]=0;
	}	

	Out = (mrcImage*)MemoryAllocate(mrcImage, info.flagOutList, "in main");
	
	lmrcImageROItoPCAoutputImage(Out, info.flagOutList, In, info.flagInList, &nPC, PC, 0);

	for(i=0; i<info.flagOutList; i++) {
		mrcFileWrite(&Out[i], info.OutList[i], "in main", 0);
		if(i%100==0)
			DEBUGPRINT1("mrcFileWrite  %d th Write\n",i);
	}

//	fclose(fp_in);
//	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageROItoPCAoutputImage(mrcImage* Out, int nOut, mrcImage* In, int nIn, int *nPC, int PC[100], int mode)
{
	int i,count,n;
	int x,y,z;
//	int x,y,z;
	double data;

	for(i=0; i<nOut; i++) {
		Out[i].HeaderN.x = *nPC;
		Out[i].HeaderN.y = 1;
		Out[i].HeaderN.z = 1;
		Out[i].HeaderLength.x = In->HeaderLength.x;
		Out[i].HeaderLength.y = In->HeaderLength.y;
		Out[i].HeaderLength.z = In->HeaderLength.z;
		Out[i].HeaderMode =  In->HeaderMode;
		mrcInit(&Out[i], NULL);
	}

	for(i=0; i<nIn; i++){
		n=0;
		count=0;
		for(z=0;z<In->HeaderN.z;z++){
		for(y=0;y<In->HeaderN.y;y++){
		for(x=0;x<In->HeaderN.x;x++){
			if(PC[n]==count+1){
				mrcPixelDataGet(&In[i], x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(&Out[i], n, 0, 0, data, mrcPixelRePart);
				n++;
			}	
			count++;
		}
		}
		}
	}	

}

