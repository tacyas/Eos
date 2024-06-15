/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc2viff ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc2viff
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrc2viff ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "mrcImage.h"
#include "khorosData.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrc2viffInfo info;
	mrcImage mrc;
	kobject viff = NULL;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	mrcFileRead(&mrc, info.In, "in main", 0);

	if ((viff= kpds_open_output_object(info.Out)) == KOBJECT_INVALID) {
    	kerror("main","mrc2viff","Failed to open output object.");
   		kexit(KEXIT_FAILURE);
   	}

	if(!lmrc2viff(&mrc, viff)) {
		kexit(KEXIT_FAILURE);
	}
    if (!kpds_set_attribute(viff, KPDS_HISTORY, kpds_history_string())) {
		kerror("igauss_func", "main", "Unable to set history on the destination object");
		kexit(KEXIT_FAILURE);
	}
	kpds_close_object(viff);

	exit(EXIT_SUCCESS);
}

void 
additionalUsage() {
}

