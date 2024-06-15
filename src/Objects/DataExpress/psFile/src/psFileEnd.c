/*
# psFileEnd.c  1.1
# The latest update : 06/15/96 at 14:37:37
#
#@(#) psFileEnd ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : psFileEnd 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)psFileEnd ver1.1; Date:96/06/15 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "psFile.h"

static void __psEnd(FILE* fpt, psParaTypeInteger mode);

void
psFileEnd(psFile* ps)
{
	__psEnd(ps->fpt, 0);	
}

void
__psEnd(FILE* fpt, psParaTypeInteger mode)
{
    fprintf(fpt, "%%%%Trailer\n");
}
