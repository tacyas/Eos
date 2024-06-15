/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileLineSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileLineSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileLineSet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/psFile.h"

void
psFileLineWidthSet(psFile* ps, float lineWidth)
{
    fprintf(ps->fpt, "%f setlinewidth\n", lineWidth);
}

void
psFileLineDraw(psFile* ps, float x1,float y1,float x2,float y2)
{
    fprintf(ps->fpt, "newpath\n%f %f moveto\n", x1,y1);
	fprintf(ps->fpt, "%f %f lineto\n",x2,y2);
	fprintf(ps->fpt, "stroke\n");
}

/*
          (x,y)            
        -------
height1 |     | height2
        |     |
        |

         width

y

^
|
|
------> x
*/
void
psFileDendgramLineDraw(psFile* ps, float width, float height1, float height2, float x, float y)
{
	fprintf(ps->fpt, "newpath\n");	
	fprintf(ps->fpt, "%f %f moveto\n", x-width/2.0, y-height1);  
	fprintf(ps->fpt, "%f %f lineto\n", x-width/2.0, y);  
	fprintf(ps->fpt, "%f %f lineto\n", x+width/2.0, y);  
	fprintf(ps->fpt, "%f %f lineto\n", x+width/2.0, y-height2);  
	fprintf(ps->fpt, "stroke\n");  
}

