/*
# mrcSinogramFETreferredCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcSinogramFETreferredCorrelation
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
#include "lmrcSinogramFETreferredCorrelation.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrcSinogramFETreferredCorrelationInfo {
	float a;
	int   b;
} lmrcSinogramFETreferredCorrelationInfo;

typedef enum lmrcSinogramFETreferredCorrelationMode {
	a=0,
	b=1
} lmrcSinogramFETreferredCorrelationMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcSinogramFETreferredCorrelationInfo info;
	lmrcSinogramFETreferredCorrelationInfo linfo;
	mrcImage weight;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.In = info.fptIn;
	linfo.InE = info.fptInE;
	linfo.InR = info.fptInR;
	linfo.nm = info.NM;
	linfo.om = info.OM;
	linfo.tnum = info.TN;
	linfo.RR = info.RR;
	linfo.Out = info.fptOut;
	linfo.flagw = info.flagWEIGHT;
	if(info.flagWEIGHT){
		mrcFileRead(&weight, info.WEIGHT, "in main", 0);
		linfo.weight = &weight;
	}

	lmrcSinogramFETreferredCorrelation(linfo, 0);
	
	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "\nInput EulerAngleDataFile example\nfile1\tYOYS\t-30\t60\t0\n");
	fprintf(stderr,"file2\tYOYS\t-53.24\t10.000\t0\n...\n\n");
	fprintf(stderr,"normalizeMode 0 : normalize with average and SD of whole inputfile\n");
	fprintf(stderr,"                  references and datas will be normalize independently\n");
	fprintf(stderr,"              1 : for using normalized inputFETdata\n\n");
	fprintf(stderr,"outputListMode 0 : output anglelist  only top1 angle set\n");
	fprintf(stderr,"               1 :                   selected angle sets\n");
	fprintf(stderr,"               2 :                   top -tn angle sets\n");
	fprintf(stderr,"   option -tn,-refR are for outputListMode!=0\n");
	fprintf(stderr,"    -tn   : number of referenceMaps be considerd in selection\n");
	fprintf(stderr,"    -refR : step size when generate referenceMapSet from 3D image is recommend\n");

	
}
