/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% khorosFilterGenerate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : khorosFilterGenerate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%khorosFilterGenerate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "eosString.h"
#include "mrcImage.h"
#include "khorosData.h"
#include "kapputils/kapputils.h"
#include "kdatafmt/viff.h"

typedef struct params {
	float x;	
	float y;	
	double w;	
} params;

void
main(int argc, char* argv[]) 
{
	kform *pane;
	long status;
	khorosFilterGenerateInfo info;
	kobject viff = NULL;
	mrcImage mrc;
	float x, y, z, w, h;
	long  n;
	char s[1024];
	params p;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
#ifdef 	KHOROS
	khorosInit(argc, argv);
#endif

	mrc.HeaderN.x = info.nx;
	mrc.HeaderN.y = info.ny;
	mrc.HeaderN.z = 1;
	mrc.HeaderMode = mrcFloatImage;
	mrcInit(&mrc, NULL);
	
	w = info.w/2;
	h = info.h/2;

	for(x=0; x<mrc.HeaderN.x; x++) {
		for(y=0; y<mrc.HeaderN.y; y++) {
			mrcPixelDataSet(&mrc, x, y, 0.0, 0.0, mrcPixelRePart);
		}
	}

	while(NULL!=stringGetFromFile(s, "", info.fptIn, stdout, 3)) {
		p.x = stringGetNthRealData(s, 1, " ,\t");						
		p.y = stringGetNthRealData(s, 2, " ,\t");						
		p.w = stringGetNthRealData(s, 3, " ,\t");						
		for(x=p.x-w; x<=p.x+w; x++) { 
			for(y=p.y-h; y<=p.y+h; y++) { 
				mrcPixelDataSet(&mrc, x, y, 0.0, p.w, mrcPixelRePart);
			}
		}
	}

    if ((viff= kpds_open_output_object(info.Out)) == KOBJECT_INVALID) {
        kerror("main","khorosFilterGenerate","Failed to open output object.");
        kexit(KEXIT_FAILURE);
    }
	
    if(!lmrc2viff(&mrc, viff)) {
        kerror("main","khorosFilterGenerate","Failed to mrc2viff.");
        kexit(KEXIT_FAILURE);
    }
	
    if (!kpds_set_attribute(viff, KPDS_HISTORY, kpds_history_string())) {
        kerror("khorosFilterGenerate", "main", "Unable to set history on the destination object");
        kexit(KEXIT_FAILURE);
    }

    if(!kpds_close_object(viff)) {
        kerror("khorosFilterGenerate", "main", "Unable to set history on the destination object");
        kexit(KEXIT_FAILURE);
	}

#ifdef KHOROS	
	kexit(KEXIT_SUCCESS);
#else 
	exit(EXIT_SUCCESS);
#endif
}

void
additionalUsage()
{
}

