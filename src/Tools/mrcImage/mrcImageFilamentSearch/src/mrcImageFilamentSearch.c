/*
# mrcImageFilamentSearch : $Revision: 1.3 $  
# $Date: 2002/02/16 06:53:15 $ 
# Created by $Author: tacyas $
# Usage : mrcImageFilamentSearch
# Attention
#   $Loccker$
#  	$State: Exp $ 
#
*/
/* $Log: mrcImageFilamentSearch.c,v $
/* Revision 1.3  2002/02/16 06:53:15  tacyas
/* Daily update
/* */

static char __sccs_id[] = "%Z%mrcImageFilamentSearch ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"

typedef struct lmrcImageFilamentSearchInfo {
	mrcImage Cor;
	mrcImage Angle;
	mrcImage Theta;
} lmrcImageFilamentSearchInfo;

/*
typedef enum lmrcImageFilamentSearchMode {
	a=0,
	b=1
} lmrcImageFilamentSearchMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage In;
	mrcImage Ref;
	mrcImageFilamentSearchInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&In, info.In, "In: in main", 0);
	mrcFileRead(&Ref, info.Ref, "Ref: in main", 0);

	mrcFileWrite(&Out, info.Out, "Out: in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

