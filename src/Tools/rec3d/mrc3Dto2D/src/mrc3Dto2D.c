/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc3Dto2D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc3Dto2D
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrc3Dto2D ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Matrix3D.h"
#include "Vector.h"
#include "mrcImage.h"
#include "lmrc3Dto2D.h"
#include "eosPThread.h"


int
main(int argc, char* argv[]) 
{
	mrc3Dto2DInfo info;
	lmrc3Dto2DInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead (&in, info.In, "in main", 0);
	/* Rot1 */
	linfo.Rot1Start = info.Rot1Start*RADIAN;
	linfo.Rot1End   = info.Rot1End*RADIAN;
	linfo.Rot1Delta = info.Rot1Delta*RADIAN;
	linfo.nRot1     = MAX(1,(int)(fabs((linfo.Rot1End - linfo.Rot1Start)/linfo.Rot1Delta)+0.5)+1);
	/* Rot2 */
	linfo.Rot2Start = info.Rot2Start*RADIAN;
	linfo.Rot2End   = info.Rot2End*RADIAN;
	linfo.Rot2Delta = info.Rot2Delta*RADIAN;
	linfo.nRot2     = MAX(1,(int)(fabs((linfo.Rot2End - linfo.Rot2Start)/linfo.Rot2Delta)+0.5)+1);
	/* Rot3 */
	linfo.Rot3Start = info.Rot3Start*RADIAN;
	linfo.Rot3End   = info.Rot3End*RADIAN;
	linfo.Rot3Delta = info.Rot3Delta*RADIAN;
	linfo.nRot3     = MAX(1,(int)(fabs((linfo.Rot3End - linfo.Rot3Start)/linfo.Rot3Delta)+0.5)+1);
	/* EulerAngleMode */
	linfo.EulerAngleMode[0] = info.EulerMode[0];
	linfo.EulerAngleMode[1] = info.EulerMode[1];
	linfo.EulerAngleMode[2] = info.EulerMode[2];
	linfo.EulerAngleMode[3] = info.EulerMode[3];
	linfo.EulerAngleMode[4] = '\0';
	/* */
	linfo.InterpolationMode  = info.InterpolationMode; 
	linfo.AreaMode = info.AreaMode;

	/* filelist*/
	if(info.flagfilenamePrefix) {
		linfo.flagFileList = 1;
		linfo.filenamePrefix = info.filenamePrefix;
		linfo.filenameSuffix = info.filenameSuffix;
		linfo.filenameNumberFormat = info.filenameFormat;
	} else {
		linfo.flagFileList = 0;
	}	

	/* pthread */
	__eosPThread__    = info.flagpthreadMax;	
	__eosPThreadNum__ = info.pthreadMax;	


	lmrcImage3Dto2D(&out, &in, &linfo, info.mode);

	if(info.flagfilenamePrefix) {
		DEBUGPRINT("FileLIST OUT: NO ACTION\n");
	} 

	if(info.flagOut) {
		DEBUGPRINT("OUT: mrcFileWrite\n");
		mrcFileWrite(&out, info.Out, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- Attention !!!!   -----\n");
	fprintf(stderr, "-m 0: \n");
	fprintf(stderr, "-m 1: Reduced Rotation Angle. If nRot3 = 1 and the axis of Rot2 is perpendicular to the 2D-image plane as z-axis, \n");
	fprintf(stderr, "      you can reduce the number of projection images.\n");
}
