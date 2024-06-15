/*
# mrcImage3DPad2 : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage3DPad2
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

/*
Example:
typedef struct lmrcImage3DPad2Info {
	float a;
	int   b;
} lmrcImage3DPad2Info;

typedef enum lmrcImage3DPad2Mode {
	a=0,
	b=1
} lmrcImage3DPad2Mode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage3DPad2Info info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
