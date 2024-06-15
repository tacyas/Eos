/*
# FETOrientationSearchByFeatureAlignment : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : FETOrientationSearchByFeatureAlignment
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
#include "lFETOrientationSearchByFeatureAlignment.h"

/*
Example:
typedef struct lFETOrientationSearchByFeatureAlignmentInfo {
	float a;
	int   b;
} lFETOrientationSearchByFeatureAlignmentInfo;

typedef enum lFETOrientationSearchByFeatureAlignmentMode {
	a=0,
	b=1
} lFETOrientationSearchByFeatureAlignmentMode;
*/

int
main(int argc, char* argv[]) 
{
	FETOrientationSearchByFeatureAlignmentInfo info;
	lFETOrientationSearchByFeatureAlignmentInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	if(info.flagInS == 0 && info.flagInF == 0){
		additionalUsage();
		exit(EXIT_FAILURE);
	}else if(info.flagInF){
		linfo.In = info.fptInF;
		linfo.flagInType = 1;
	}else{
		linfo.In = info.fptInS;
		linfo.flagInType = 0;
	}
	if(info.flagInS2 == 1 && info.flagInA == 0){
		additionalUsage();
		exit(EXIT_FAILURE);
	}
	if(info.flagOut){
		linfo.Out = info.fptOut;
	}else{
		linfo.Out = stdout;
	}
	linfo.flagOutA = info.flagOutA;
	if(info.flagOutA){
		linfo.OutA = info.fptOutA;
	}
	linfo.flagOut2D = info.flagOut2D;
	if(info.flagOut2D){
		linfo.Out2D = info.fptOut2D;
	}
	linfo.flagOutLOG = info.flagOutLOG;
	if(info.flagOutLOG){
		linfo.OutLOG = info.fptOutLOG;
	}else{
		linfo.OutLOG = stdout;
	}
	linfo.flagInA = info.flagInA;
	if(info.flagInA){
		linfo.InA = info.fptInA;
	}
	linfo.flagIn2 = info.flagInS2;
	if(info.flagInS2){
		linfo.In2 = info.fptInS2;
	}
	linfo.itmax = info.ITMAX;
	linfo.devmax = info.DEVMAX;
	linfo.mitmax = info.MITMAX;
	linfo.mdevmax = info.MDEVMAX;
	linfo.mode = info.mode;
	
	
	
	linfo.ldn = info.LDN;
	linfo.srl = info.SRL;
	fprintf(stdout,"in main1");
	lFETOrientationSearchByFeatureAlignment(linfo, 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Either -i or -I is essential option.\n");
	fprintf(stderr, "Input FETimages: smoothed image is recommend.\n");
	fprintf(stderr, "   when you don't have smoothed image, input sinograms is better.\n");
	//fprintf(stderr, "-ldn option : for when you cought \"Segmentation fault\" after PCA\n");
	fprintf(stderr, "-ia InputAngleList option is for using handover angledata \n");
	fprintf(stderr, "  input file is from -oa option of previous calculation.\n");
	
	fprintf(stderr, "-ldn option do not work\n");


	fprintf(stderr, "mode ABC\n");
	fprintf(stderr, "	A=0: calc single initial-set, output single angle-set\n");
	fprintf(stderr, "	A=1: calc multi initial-sets, output multi angle-sets\n");
	fprintf(stderr, "	A=2: calc multi initial-sets, output selected one angle-set\n");
	fprintf(stderr, "	B=0: \n");
	fprintf(stderr, "	C=0: 4 images selected by 90degree rule, consist initial-set, for A=0\n");
	fprintf(stderr, "	C=1: 1 image of image has largest radius consists initial-set, for A=0,1,2\n");
	fprintf(stderr, "	C=2: 2 images of image has largest radius consist initial-set, for A=1,2\n");
	fprintf(stderr, "	C=3: all images with random angles consist initial-set, for A=0,1,2\n");
	
	
	fprintf(stderr, "   \n");
	fprintf(stderr, "-itm, -dvm option is for mode A=0,2	-itm >= -dvm , -dvm <= 3\n");
	fprintf(stderr, "-mitm, -mdvm option is for mode A=1,2	-mitm >= -mdvm , -mdvm <= 3 , -mitm <= -itm\n");
	
}
