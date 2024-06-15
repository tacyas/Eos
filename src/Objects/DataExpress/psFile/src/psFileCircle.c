/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileCircle ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileCircle 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileCircle ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>

#include "../inc/psFile.h"

void
psFileCircleCreate(psFile* ps, float cx, float cy, float r, long mode)
{
	int circleCol;

	switch(mode){
		case PS_LINE_CIRCLE_MODE:
			fprintf(ps->fpt, "newpath %15.6f %15.6f %15.6f %15.6f %15.6f arc stroke\n", cx, cy, r, 0.0, 360.0);
			break;
		case PS_FILL_WHITE_CIRCLE_MODE:
		case PS_FILL_BLACK_CIRCLE_MODE:
			if(PS_FILL_WHITE_CIRCLE_MODE==mode){
				circleCol=1;
			}else{
				circleCol=0;
			}
			fprintf(ps->fpt, "gsave\n");
			fprintf(ps->fpt, "newpath %15.6f %15.6f %15.6f %15.6f %15.6f arc closepath\n", cx, cy, r, 0.0, 360.0);
			fprintf(ps->fpt, "%d setgray\nfill\ngrestore\n",circleCol);
			break;
		default:
			fprintf(stderr,"Not supported mode (%ld) in psFIleCircleCreate\n",mode);
			break;
	}
	return;
}
