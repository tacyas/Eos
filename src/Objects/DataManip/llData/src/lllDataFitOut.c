/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFitOut ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFitOut 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataFitOut ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdlib.h>
#include "../inc/llData.h"
#include "lllDataFit.h"
#include "genUtil.h"

void
lllDataFitParamOutput(FILE* fpt, char* ref, char* dat, llDataFittedParam* para, long mode)
{
    llDataParaTypeInteger i, j;

	if(mode==0) {
            fprintf(fpt, "%s %s %15.6f %15.6f %15.6f %15.6f\n",
                                   ref,
                                   dat,
                                   para->Para.R*DEGREE,
                                   para->Para.phi.Value*DEGREE,  
                                   para->Para.z.Value,  
                                   para->Para.r.Value);
	}
    if(mode&PVALUE_MODE) {
            fprintf(fpt, "%s %s %15.6f %15.6f %15.6f %15.6f\n",
                                   ref,
                                   dat,
                                   para->PPara.R*DEGREE,
                                   para->PPara.phi.Value*DEGREE,  
                                   para->PPara.z.Value,  
                                   para->PPara.r.Value);
    }
	if(mode&QVALUE_MODE) {
            fprintf(fpt, "%s %s %15.6f %15.6f %15.6f %15.6f\n",
                                   ref,
                                   dat,
                                   para->QPara.R*DEGREE,
                                   para->QPara.phi.Value*DEGREE,  
                                   para->QPara.z.Value,  
                                   para->QPara.r.Value);
    }
	if(mode&RVALUE_MODE) {
            fprintf(fpt, "%s %s %15.6f %15.6f %15.6f %15.6f\n",
                                   ref,
                                   dat,
                                   para->RPara.R*PERCENT,
                                   para->RPara.phi.Value*DEGREE,  
                                   para->RPara.z.Value,
                                   para->RPara.r.Value);
    }
}

