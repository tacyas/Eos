/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFilePage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFilePage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFilePage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "psFile.h"

static char __psLabel[MAX_STRING_LENGTH];
static psParaTypeInteger __psPage;

static void __psPageStart(FILE* fpt, char* label, psParaTypeInteger page, psParaTypeInteger mode);
static void __psPageEnd(FILE* fpt, psParaTypeInteger mode);

void 
psFilePageStart(psFile* ps, psParaTypeInteger mode)
{
	__psPageStart(ps->fpt, ps->info.label, ps->info.page, mode);
}
void
psFilePageEnd(psFile* ps, psParaTypeInteger mode)
{
	__psPageEnd(ps->fpt, mode);
}

void
__psPageStart(FILE* fpt, char* label, psParaTypeInteger page, psParaTypeInteger mode)
{

    strcpy(__psLabel, label);
    __psPage = page;
    fprintf(fpt, "%%%%Page: %s %d\n", __psLabel, (int)__psPage);
    fprintf(fpt, "gsave\n");
	if(0==mode){
	    fprintf(fpt, "%f %f translate\n", 72.0/2.54, 72.0/2.54);
	}
}

void
__psPageEnd(FILE* fpt, psParaTypeInteger mode)
{
    fprintf(fpt, "grestore\n");
    fprintf(fpt, "showpage\n");
    fprintf(fpt, "%%%%EndPage: %s %d\n", __psLabel, (int)__psPage);
}
