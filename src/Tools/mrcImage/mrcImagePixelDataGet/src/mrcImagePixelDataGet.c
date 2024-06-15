/*
# mrcImagePixelDataGet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImagePixelDataGet
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

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "eosPoint.h"

#ifdef  CUDA
#include "eosCuda.h"
#endif


/*
Example:
typedef struct lmrcImagePixelDataGetInfo {
	float a;
	int   b;
} lmrcImagePixelDataGetInfo;

typedef enum lmrcImagePixelDataGetMode {
	a=0,
	b=1
} lmrcImagePixelDataGetMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImagePixelDataGetInfo info;
	mrcImage in;
	double data;
	float* dataArray;
	mrcImageParaTypeRealCoord* inCoord;
	int nPixel, i;		
	eosPoint p;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
#ifdef CUDA
	if(info.flagcudaDeviceID) {
		DEBUGPRINT("eosCudaInit --> start\n");
		eosCudaInit(info.cudaDeviceID);
		DEBUGPRINT("eosCudaInit --> end\n");
	}
#endif 

	mrcFileRead(&in, info.In, "in main", 0); 

	if(info.flagInCoord) {
		eosPointRead(info.fptInCoord, &p, 0);
		nPixel=0;
		p.current = p.top;
		while(p.current!=NULL) {
			nPixel++;
			p.current = p.current->next;
		}
		dataArray = memoryAllocate(sizeof(float)*nPixel, "in mrcPixelsDataGet");
		inCoord = memoryAllocate(sizeof(mrcImageParaTypeRealCoord)*nPixel, "in mrcPixelsDataGet"); 

		i = 0;
		p.current = p.top;
		while(p.current!=NULL) {
			inCoord[i].x = p.current->p.coord.data[0]; 
			inCoord[i].y = p.current->p.coord.data[1]; 
			inCoord[i].z = p.current->p.coord.data[2]; 
			i++;
			p.current = p.current->next;
		}
		mrcPixelsDataGet(dataArray, inCoord, nPixel, &in, mrcPixelRePart, info.mode);
		for(i=0; i<nPixel; i++) {
			if((info.outMode&0x1)!=0) {
				fprintf(info.fptOut, "%f %f %f ", inCoord[i].x, inCoord[i].y, inCoord[i].z);
			}
			fprintf(info.fptOut, "%f\n", dataArray[i]);
		}
	} else {
		mrcPixelDataGet(&in, info.x, info.y, info.z, &data, mrcPixelRePart, info.mode);
		if((info.outMode&0x1)!=0) {
			fprintf(info.fptOut, "%f %f %f ", info.x, info.y, info.z);
		}
		fprintf(info.fptOut, "%lf\n", data);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m InterpolationMode ; refer to mrcImageROI \n");
	fprintf(stderr, "-om outputMode\n");
	fprintf(stderr, " +1 : with coordinates\n");


}
