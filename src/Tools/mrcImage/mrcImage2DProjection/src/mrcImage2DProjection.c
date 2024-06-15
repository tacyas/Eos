/*
# mrcImage2DProjection.c  1.3
# The latest update : 07/31/96 at 18:54:51
#
#@(#) mrcImage2DProjection ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImage2DProjection
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImage2DProjection ver1.3; Date:96/07/31 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImage2DProjectionInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	float tmp,rw,ra,Nx,Nz;
	int oNx,oNz;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* output datasize calculation */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	rw = RADIAN*fabs(info.Omega); 
	ra = RADIAN*fabs(info.Alpha);
	tmp = 1.0/cos(rw) - tan(rw)*sin(rw) ;
	tmp *= in.HeaderN.z;
	tmp -= in.HeaderN.x * sqrt(2.0) * sin(rw);
	Nz = 1.0/cos(ra) - tan(ra)*sin(ra);
	Nz *= tmp;
	Nz -= in.HeaderN.x * sin(ra);
	oNz = (int)(Nz / 2) * 2;
	if (oNz < 0){
	  fprintf(stderr,"Length of data along z axis is too short.");
	  exit(EXIT_FAILURE);
	}
	Nx = tmp * sin(ra) + in.HeaderN.x * cos(ra) ;
	oNx = (int)( (Nx + 1)/2 )* 2 ;

/* begin */      	
        lmrcRefFilamentProjction(&out ,&in ,info.Phi*RADIAN ,info.Omega*RADIAN ,info.Alpha*RADIAN ,oNx ,oNz);
        mrcFileWrite(&out ,info.Out ,"in main" ,0);
        exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}





