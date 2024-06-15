/*
# mrcImageCCDNoiseRemove : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageCCDNoiseRemove
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"
#include "File.h"

typedef struct lmrcImageCCDNoiseRemoveInfo {
	int type;
	int x;
	int y;
	int height;
	int width;
	struct lmrcImageCCDNoiseRemoveInfo *next;
} lmrcImageCCDNoiseRemoveInfo;

typedef enum lmrcImageCCDNoiseRemoveMode {
	CCDNoiseVLine = 0,
	CCDNoiseSquare = 1,
	ERROR = -1
} lmrcImageCCDNoiseRemoveMode;

void
lmrcImageCCDNoiseRemoveInfoFileFormatPrint(FILE* fpt, int mode);

void
lmrcImageAllCopy(mrcImage *out, mrcImage *in, int mode);

void
lmrcImageCCDNoiseRemoveInfoInit(lmrcImageCCDNoiseRemoveInfo **linfo);

void
lmrcImageCCDNoiseRemoveInfoFileRead(FILE* in, char* infilename, lmrcImageCCDNoiseRemoveInfo **linfo, lmrcImageCCDNoiseRemoveInfo *head, int mode);

void
lmrcImageCCDNoiseRemove(mrcImage* out, lmrcImageCCDNoiseRemoveInfo **linfo, int mode);

void
lmrcImageCCDNoiseRemoveVLine(mrcImage *out, lmrcImageCCDNoiseRemoveInfo **linfo, int mode);


int
main(int argc, char* argv[]) 
{
	mrcImageCCDNoiseRemoveInfo info;
	lmrcImageCCDNoiseRemoveInfo *linfo;
	lmrcImageCCDNoiseRemoveInfo *head;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "main", 0);
	
	out.Header = in.Header;
	mrcInit(&out,0);
	lmrcImageAllCopy(&out, &in, 0);
	
	lmrcImageCCDNoiseRemoveInfoInit(&linfo);
	head = linfo;
	
	lmrcImageCCDNoiseRemoveInfoFileRead(info.fptInNoise, info.InNoise, &linfo, head, info.mode);

	lmrcImageCCDNoiseRemove(&out, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "main", info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode: 0   	random values\n");
	fprintf(stderr, "mode: 1   	neighbor point's values\n");
	lmrcImageCCDNoiseRemoveInfoFileFormatPrint(stderr, 0);
}

/*

*/

void
lmrcImageCCDNoiseRemoveInfoFileFormatPrint(FILE* fpt, int mode)
{
	fprintf(fpt, ">>>>> CCD Noise Remove Format\n");
	fprintf(fpt, "VLine  x y height width     ; Vertical Line Noise Remove[pixel]\n");
	fprintf(fpt, "Square x y height width     ; Square Noise Remove[pixel] \n");
}

void
lmrcImageAllCopy(mrcImage *out, mrcImage *in, int mode)
{

	int x, y, z;
	double data;
	
	for(x = 0; x < in -> HeaderN.x; x++){
		for(y = 0; y < in -> HeaderN.y; y++){
			for(z = 0; z < in -> HeaderN.z; z++){
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
		}
	}
	
}

void
lmrcImageCCDNoiseRemoveInfoInit(lmrcImageCCDNoiseRemoveInfo **linfo)
{

	(*linfo) = (lmrcImageCCDNoiseRemoveInfo *)memoryAllocate(sizeof(lmrcImageCCDNoiseRemoveInfo), "in lmrcImageCCDNoiseRemoveInfoInit");
	(*linfo) -> type = -1;
	(*linfo) -> x = 0;
	(*linfo) -> y = 0;
	(*linfo) -> height = 0;
	(*linfo) -> width = 0;
	(*linfo) -> next = NULL;

}

void
lmrcImageCCDNoiseRemoveInfoFileRead(FILE* in, char* infilename,  lmrcImageCCDNoiseRemoveInfo **linfo, lmrcImageCCDNoiseRemoveInfo *head, int mode)
{

	lmrcImageCCDNoiseRemoveInfo *p;
	char *str;
	char line[256], type[30], X[30], Y[30], H[30], W[30];
	int x, y, height, width;
	
	
	in = fileOpen(infilename, "r");
	
	while(fgets(line, 30, in) != NULL){
		str = strtok(line, " ");
		strcpy(type, str);

		if((str = strtok(NULL, " ")) != NULL){
			strcpy(X, str);
			x = atoi(X);
		}
		
		if((str = strtok(NULL, " ")) != NULL){
			strcpy(Y, str);
			y = atoi(Y);
		}
		
		if((str = strtok(NULL, " ")) != NULL){
			strcpy(H, str);
			height = atoi(H);
		}

		if((str = strtok(NULL, " ")) != NULL){
			strcpy(W, str);
			width = atoi(W);
		}
		
		/*
		fprintf(stdout, "type = %s\n",type);
		fprintf(stdout, "x        = %5d\n", x);
		fprintf(stdout, "y        = %5d\n", y);
		fprintf(stdout, "height   = %5d\n", height);
		fprintf(stdout, "width    = %5d\n\n", width);
		*/

		while((*linfo) -> next != NULL){
			(*linfo) = (*linfo) -> next;
		}
		
		p = (lmrcImageCCDNoiseRemoveInfo *)memoryAllocate(sizeof(lmrcImageCCDNoiseRemoveInfo), "in lmrcImageCCDNoiseRemoveInfoRead");
	
		if(0 == strcmp(type, "VLine")){
			p -> type = CCDNoiseVLine;
		}
		else if(0 == strcmp(type, "Square")){
			p -> type = CCDNoiseSquare;
		}
		else{
			p -> type = ERROR;
		}

		p -> x = x;
		p -> y = y;
		p -> height = height;
		p -> width = width;
		p -> next = NULL;
		(*linfo) -> next = p;
	
	}

	(*linfo) = head;

    /*	
	(*linfo) = (*linfo) -> next;
	while((*linfo) != NULL){
		fprintf(stdout, "type = %d\n", (*linfo) -> type);
		fprintf(stdout, "x        = %5d\n", (*linfo) -> x);
		fprintf(stdout, "y        = %5d\n", (*linfo) -> y);
		fprintf(stdout, "height   = %5d\n", (*linfo) -> height);
		fprintf(stdout, "width    = %5d\n", (*linfo) -> width);
		(*linfo) = (*linfo) -> next;
		fprintf(stdout, "\n");
	}

	(*linfo) = head;
	*/

}

void
lmrcImageCCDNoiseRemove(mrcImage* out, lmrcImageCCDNoiseRemoveInfo **linfo, int mode)
{

	int Case_VLine   = 0;
	int Case_Square  = 0;
	int Case_Error   = 0;
	int Case_Default = 0;
	
	(*linfo) = (*linfo) -> next;
	while((*linfo) != NULL){
		switch((*linfo) -> type){

		case CCDNoiseVLine:
			Case_VLine++;
			lmrcImageCCDNoiseRemoveVLine(out, linfo, 0);
			break;

		case CCDNoiseSquare:
			Case_Square++;
			break;

		case ERROR:
			Case_Error++;
			break;

		default:
			Case_Default++;
			break;

		}

		(*linfo) = (*linfo) -> next;

	}

	fprintf(stdout, " VLine_carried_out = %2d\n", Case_VLine);
	fprintf(stdout, "Square_carried_out = %2d\n", Case_Square);
	fprintf(stdout, "      Error        = %2d\n", Case_Error);
	fprintf(stdout, "   not_carried_out = %2d\n", Case_Default);
		
}

void
lmrcImageCCDNoiseRemoveVLine(mrcImage *out, lmrcImageCCDNoiseRemoveInfo **linfo, int mode)
{

	int x, y, i;
	double data0, data1, data2, data3, dataAvg;

	x = ((*linfo) -> x);

	for(y = (*linfo) -> y; y < ((*linfo) -> y) + ((*linfo) -> height); y++){
		mrcPixelDataGet(out, x - 1, y, 0, &data0, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(out, x - 2, y, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(out, x + ((*linfo) -> width), y, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(out, x + ((*linfo) -> width) + 1, y, 0, &data3, mrcPixelRePart, mrcPixelHowNearest);
		dataAvg = (data0 + data1 + data2 + data3) / 4;

		for(i = 0; i < ((*linfo) -> width); i++){  
			mrcPixelDataSet(out, x + i, y, 0, dataAvg, mrcPixelRePart);
		}
		
	}	

}
