/*
# mrcImageDivideInfoForTomography : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageDivideInfoForTomography
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

/*
Example:
typedef struct lmrcImageDivideInfoForTomographyInfo {
	float a;
	int   b;
} lmrcImageDivideInfoForTomographyInfo;

typedef enum lmrcImageDivideInfoForTomographyMode {
	a=0,
	b=1
} lmrcImageDivideInfoForTomographyMode;
*/

int
main(int argc, char* argv[]) 
{
	int sizeX,sizeY,positionX,positionY,numberX,numberY;
	int number,length;
	char *BaseName;
	mrcImageDivideInfoForTomographyInfo info;
	mrcImage mrc;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	mrcFileRead(&mrc, info.In, "in main", 0);
	sizeX = mrc.HeaderN.x/info.divide;
	sizeY = mrc.HeaderN.y/info.divide;
	if(info.cut > sizeX || info.cut > sizeY){
		fprintf(stderr,"divide size is big");
		exit(1);
	}
	number    = 0;
	length    = strlen(info.In);
	BaseName  = MemoryAllocate(char,length+1,"in mrcImageDivideInfoForTomography");
	BaseName  = info.In;
	while(length != 0){
		if( BaseName[length] == '.' ){
			BaseName[length] = NULL;
			break;
		}
	length--;
	}
	
	if( 0 == info.mode || 1 == info.mode){
		positionX = info.cut;
		positionY = info.cut;
		fprintf(stderr,"%s PixselSize = %4d * %4d\n",BaseName,mrc.HeaderN.x,mrc.HeaderN.y);
		fprintf(stderr,"DivideSize = %4d * %4d\n",sizeX,sizeY);
		if( info.mode == 1){
			info.divide = info.divide * 2 - 1;
		}
		
		for(numberY = 0 ; numberY < info.divide ; numberY++){
			for(numberX = 0 ; numberX < info.divide ; numberX++){
				fprintf(info.fptOut,"%s-%04d.roi Rect",BaseName,number);
				fprintf(info.fptOut," %4d %4d",positionX,positionY);
				positionX += sizeX;
				fprintf(info.fptOut," %4d %4d",positionX,positionY);
				positionY += sizeY;
				fprintf(info.fptOut," %4d %4d",positionX,positionY);
				positionX -= sizeX;
				fprintf(info.fptOut," %4d %4d\n",positionX,positionY);
				if( info.mode == 0){
					positionX += sizeX; positionY -= sizeY;
				}
				else if( info.mode == 1){
					positionX += sizeX/2; positionY -= sizeY;
				}
	
				if( numberX == 0){
					positionX -= info.cut;
				}
				else if( numberX == (info.divide - 2)){
					positionX -= info.cut;
				}
				number++;
			}
			positionX = info.cut; 
			if( info.mode == 0 ){
				positionY += sizeY;
			}
			else if( info.mode == 1 ){
				positionY += sizeY/2;
			}
			
			if( numberY == 0){
				positionY -= info.cut;
			}
			else if( numberY == (info.divide - 2)){
				positionY -= info.cut;
			}
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
