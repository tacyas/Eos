/*
# psFileString.c  1.1
# The latest update : 06/07/96 at 16:27:37
#
#@(#) psFileString ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : psFileString 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)psFileString ver1.1; Date:96/06/15 @(#)";
#include <stdio.h>

#include "psFile.h"

static int __psStringStatusMode = 0;
static char __psStringDefaultStatus[] = "/Helvetica findfont 8 scalefont setfont";

void
psFileStringStatusSet(psFile* ps, char* fontname, double fontsize)
{
	__psStringStatusMode = 1;
    fprintf(ps->fpt, "%s findfont %f scalefont setfont\n", fontname, fontsize);
}

void
psFileStringDefaultStatusSet(psFile* ps)
{
    fprintf(ps->fpt, "%s\n", __psStringDefaultStatus);
}

void
psFileString(psFile* ps, char* message, double x, double y, long mode)
{
	if(__psStringStatusMode==0) {
		psFileStringDefaultStatusSet(ps);
	} 
    fprintf(ps->fpt, "%f %f mt \n(%s) show\n", x, y, message);
}
