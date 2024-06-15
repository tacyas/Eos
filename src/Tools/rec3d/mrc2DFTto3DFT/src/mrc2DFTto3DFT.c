/*
# mrc2DFTto3DFT : $Revision$
# $Date$
# Created by $Author$
# Usage : mrc2DFTto3DFT
# Attention
#   $Loccker$
#  	$State$
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lmrcFFTCentralSection.h"
//#include "Class.h"

/*
Example:
typedef struct lmrc2DFTto3DFTInfo {
	float a;
	int   b;
} lmrc2DFTto3DFTInfo;

typedef enum lmrc2DFTto3DFTMode {
	a=0,
	b=1
} lmrc2DFTto3DFTMode;
*/

int
main(int argc, char* argv[])
{
    mrc2DFTto3DFTInfo info;
    lmrcFFTCentralSectionInfo linfo;
    char file2d[1024], file3d[256], buf[256];
    char filename[1024];
    char s[1024];
    double probability;
    mrcImage temp3d, in ,count, Sigma;
    mrcImage* Inlist;
    mrcImage Out;
		//書き込み　mrcImage Sigma;
    int num, ref,i=0;
    int size;
    clock_t start,end;
    FILE* fp;

    start = clock();

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    DEBUGPRINT("Program Start\n");

    mrcFileRead(&temp3d, info.temp3d, "in main", 0);

    int c=0;
    linfo.TransX = 0.0;
    linfo.TransY = 0.0;
    linfo.InterpMode = info.InterpMode;

    Out.Header = temp3d.Header;
    count.Header = temp3d.Header;
    mrcInit(&Out, NULL);
    mrcInit(&count, NULL);

    DEBUGPRINT1("inFlieList: %d\n", info.flagIn);
    Inlist = memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
    i=0;
    rewind(info.fptInList);
    while(NULL!=fgets(s, 1024, info.fptInList)) {
        sscanf(s, "%s %4s %lf %lf %lf %s %d %lf", file2d, linfo.EulerMode, &linfo.Rot1, &linfo.Rot2, &linfo.Rot3, file3d, &num, &probability);
        DEBUGPRINT2("Num %d/%d\n", i, info.flagIn);
        mrcFileRead(&Inlist[i], file2d, "in main", 0);
	DEBUGPRINT1("filename: %s\n", file2d);
	//DEBUGPRINT1("Num %d\n", num);
	DEBUGPRINT1("prob %lf\n", probability);
 
	linfo.flagWeight = 1;
	linfo.weight = probability ;
        lmrcImageFFTCentralSectionPut(&Out, &count, &temp3d, &Inlist[i], &linfo, &c, info.mode);
	i++;
    }

    lmrcImageFFTRhoFilter(&Out, &count, &linfo, info.mode);
    mrcFileWrite(&Out, info.Out, "in main", 0);


		/*書き込み
		lmrcImageFFTSigmaCalc(&Sigma, &Out, &count, &temp3d, &Inlist[i-1], probability, &linfo, &c, info.mode);
		 */




    //////    mrcFileWrite(&Sigma, info.Out, "in main", 0);


    free(Inlist);
    end = clock();
    DEBUGPRINT1("time %f\n",(double)(end-start)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
