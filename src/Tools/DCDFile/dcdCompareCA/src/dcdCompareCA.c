/*
# dcdCompareCA : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdCompareCA
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
typedef struct ldcdCompareCAInfo {
	float a;
	int   b;
} ldcdCompareCAInfo;

typedef enum ldcdCompareCAMode {
	a=0,
	b=1
} ldcdCompareCAMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdCompareCAInfo info;
 DCD coordinate;
 
	   char mode1[3];
       char mode2[3];
	   char mode3[3];
 
	init0(&info);
    argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	   strcpy(mode1,"r");
	   strcpy(mode2,"w");
	   strcpy(mode3,"a");
	coordinate.Open(info,mode3);
	coordinate.AtomAtomDistanceGet();
	coordinate.DistanceWrite();
	coordinate.Close();

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
