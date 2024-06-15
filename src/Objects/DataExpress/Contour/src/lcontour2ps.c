/*
# lcontour2ps.c  1.1
# The latest update : 05/25/96 at 14:54:18
#
#@(#) lcontour2ps ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : lcontour2ps 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lcontour2ps ver1.1; Date:96/06/15 @(#)";
#include <stdio.h>
#include <math.h>

#include "psFile.h"
#include "../inc/Contour.h"

#define MAX_POINTS (1024)

void
lcontour2ps(FILE* fpt, contourLinesSet* lsset)
{
    short i, j;
    contourALine* last;

    lsset->current = lsset->top;
    while(lsset->current!=NULL) {
        lsset->current->current = lsset->current->top;
        j = 0;
        while(lsset->current->current!=NULL) {
            lsset->current->current->current = lsset->current->current->top;
            i = 0;
            fprintf(fpt, "newpath\n%f %f moveto\n", 
                         (float)lsset->current->current->current->p0.x, 
                         (float)lsset->current->current->current->p0.y);
            while(lsset->current->current->current!=NULL) {
                fprintf(fpt, "%f %f lineto\n", 
                         (float)lsset->current->current->current->p0.x,
                         (float)lsset->current->current->current->p0.y);
                i++;
                last = lsset->current->current->current;
                lsset->current->current->current = lsset->current->current->current->next;
            }
            if(fabs(last->p1.x-lsset->current->current->top->p0.x)<CONTOUR_ACCURACY
             &&fabs(last->p1.y-lsset->current->current->top->p0.y)<CONTOUR_ACCURACY
             &&fabs(last->p1.z-lsset->current->current->top->p0.z)<CONTOUR_ACCURACY)  {
                fprintf(fpt, "closepath\n");
            }
            fprintf(fpt, "stroke\n");
            j++;
            lsset->current->current = lsset->current->current->next;
        }
        lsset->current = lsset->current->next;
    }
}
