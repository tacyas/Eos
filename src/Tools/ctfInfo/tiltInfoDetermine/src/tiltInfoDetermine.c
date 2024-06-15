/*
# tiltInfoDetermine : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : tiltInfoDetermine
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
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"
#include "nr2.h"
#include "Memory.h"
#include "mrcImage.h"
#include "File.h"
#include "eosString.h"
#include "lmrcImageROI2D.h"
#include "lmrcImageMontage.h"

/*
Example:
typedef struct ltiltInfoDetermineInfo {
	float a;
	int   b;
} ltiltInfoDetermineInfo;

typedef enum ltiltInfoDetermineMode {
	a=0,
	b=1
} ltiltInfoDetermineMode;
*/

int
main(int argc, char* argv[]) 
{
	tiltInfoDetermineInfo info;
	lmrcImageROIsInfo linfo;
	float *x,*y,*defocus;
	float a,b,abdev;
	int   i,j,k,n;
	int   ndata = 225;
	char xbuf[256],ybuf[256],buf[256];
	char **fileName;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	DEBUGPRINT("Program Start\n");
	if(info.flagIn) {
		lmrcImageROIsInformationGet(info.fptIn, &linfo);
	} else {
		fprintf(stderr, "No information to extract ROIs\n");
		exit(EXIT_FAILURE);
	}
	ndata = linfo.numROI;
	for( i= 0 ; i < ndata ; i++){
		j = 0;
		while( linfo.ROI[i].FileName[j] != NULL){
			if( linfo.ROI[i].FileName[j] == '.'){
				linfo.ROI[i].FileName[j] = NULL;
				break;
			}
			j++;
		}
	}
	x = vector(1, ndata);
	y = vector(1, ndata);
	
	n = 0;
	while( fgets(buf, 256, info.fptdefocus) != NULL){
		n++;
	}
	defocus = (float*)memoryAllocate(sizeof(float)*n, "in main (rois)");
	fileName = (char**)memoryAllocate(sizeof(char*)*n, "in main (rois)");
	for(i = 0 ; i < n ; i++){
		fileName[i] = (char*)memoryAllocate(sizeof(char)*256, "in main (rois)");
	}
	fseek(info.fptdefocus, 0L, SEEK_SET);
	i = 0;
	while( fgets(buf, 256, info.fptdefocus) != NULL){
	     sscanf(buf,"%s %f\n",fileName[i],&defocus[i]);
		 i++;
	}

	k = 1;
	for(i = 0 ; i < ndata ; i++){
		for( j = 0 ; j < n ; j++){
			if(strcmp(linfo.ROI[i].FileName,fileName[j]) == 0){
				x[k] = (float)((linfo.ROI[i].try + linfo.ROI[i].bry)/2*info.mag);
				y[k] = defocus[j];
				fprintf(info.fptOut,"x: %f y: %f\n",x[k],y[k]);
				break;
			}
		}
		k++;
	}
	medfit(x, y, ndata, &a, &b, &abdev);
	//fprintf(stdout,"a= %5.2f b= %5.2f abdev= %5.2f\n",a,b,abdev);
	fprintf(info.fptOut,"a= %5.2f b= %5.2f abdev= %5.2f\n",a,b,abdev);
	fprintf(stdout,"TiltAngle= %f\n",atan(b)*180/M_PI);
	fprintf(info.fptOut,"TiltAngle= %f\n",atan(b)*180/M_PI);
	free_vector(y, 1, ndata);
	free_vector(x, 1, ndata);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
