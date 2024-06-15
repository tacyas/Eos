/*
# dcdAtomDistanceDistribution : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdAtomDistanceDistribution
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
#include "DCDFile.h"

/*
Example:
typedef struct ldcdAtomDistanceDistributionInfo {
	float a;
	int   b;
} ldcdAtomDistanceDistributionInfo;

typedef enum ldcdAtomDistanceDistributionMode {
	a=0,
	b=1
} ldcdAtomDistanceDistributionMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdAtomDistanceDistributionInfo info;
 DCD coordinate;

 char mode1[3];
 char mode2[3];
 char mode3[3];
// int  serectAtom;
int i;
        init0(&info);
     argCheck(&info, argc, argv);
     init1(&info);

	DEBUGPRINT("Program Start\n");

 strcpy(mode1,"r");
 strcpy(mode2,"w");
 strcpy(mode3,"a");

 coordinate.HeaderRead(info.In);
 coordinate.Open(info.In,mode1);
 coordinate.DistanceDistribution();
 coordinate.Close();
 coordinate.Open(info.Out,mode3);
 coordinate.DistanceDistributionWrite();
 if(info.flagOutMRC) {
   coordinate.DistanceDistributionWriteToMRC(info.OutMRC);
 }
// coordinate.Write();
 coordinate.Close();
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
