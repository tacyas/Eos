/*
# array2mrc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : array2mrc
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
#include "Array.h"
#include "mrcImage.h"
#include "larray2mrc.h"

int
main(int argc, char* argv[]) 
{
	array2mrcInfo  info;
	larray2mrcInfo linfo;
	Array array;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.mrcMode   = info.mm;
    if(info.flaglm) {
	    linfo.mrcLengthX = info.lm;
	    linfo.mrcLengthY = info.lm;
	    linfo.mrcLengthZ = info.lm;
    } else {
	    linfo.mrcLengthX = info.lmx;
	    linfo.mrcLengthY = info.lmy;
	    linfo.mrcLengthZ = info.lmz;
    }
    linfo.ax = info.ax;
    linfo.ay = info.ay;
    linfo.az = info.az;

	DEBUGPRINT("Program Start\n");
		
	arrayReadFromFile(info.fptIn, &array, "in main");
	if(3<array.dim){
		fprintf(stderr, "This dimension can not use this program : %d!!\n", array.dim);
		exit(1);
	}
	larray2mrc(&out, array, &linfo, info.mode);


	mrcFileWrite(&out, info.Out, "in main", 0);

	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-- Attension --\n");
	fprintf(stderr, "Array format : left-hand\n");
	fprintf(stderr, "mrc   format : right-hand\n");
	fprintf(stderr, "---------------\n");
	arrayFormatInfoPrint(stderr, 0);
}


