/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileContour3D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileContour3D
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileContour3D ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genUtil.h"
#include "Contour.h"
#include "Memory.h"
#include "../inc/psFile.h"


extern void __psContour3D(FILE* fpt, psImageInfo im, psParaTypeInteger mode);

void
psFileContour3D(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
	__psContour3D(ps->fpt, im, mode);
}

void
__psContour3D(FILE* fpt, psImageInfo im, psParaTypeInteger mode)
{
    contourLine* al;
    contourArgs arg;
    contourParaTypeInteger iw, ih, is, i;
    extern contourFlag flagContour;

    al = (contourLine*)memoryAllocate(sizeof(contourLine)*im.nContour, "in psContour(al)");
    arg.dx = arg.dy = 1;
    arg.z  = 0.0;
    flagContour = contourFlagZSection;
    for(i=0; i<im.nContour; i++) {
        al[i].current = al[i].top = NULL;
        for(iw=0; iw<im.width-1; iw++) {
            for(ih=0; ih<im.height-1; ih++) {
            	for(is=0; is<im.section-1; is++) {
					/* x-y plane */
    				flagContour = contourFlagZSection;
	                arg.f00 = im.floatImage[(iw  ) 
										  +  ih   *im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
					arg.f01 = im.floatImage[(iw  ) 
										  + (ih+1)*im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
					arg.f11 = im.floatImage[(iw+1)
										  + (ih+1)*im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
                	arg.f10 = im.floatImage[(iw+1)
										  +  ih   *im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
                	arg.x = iw; 
					arg.y = ih;
					arg.z = is;
                	createContourALine(&(al[i]), arg);
					/* y-z plane */
    				flagContour = contourFlagXSection;
	                arg.f00 = im.floatImage[(iw  ) 
										  +  ih   *im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
					arg.f01 = im.floatImage[(iw  ) 
										  + (ih+1)*im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
					arg.f11 = im.floatImage[(iw+1)
										  + (ih+1)*im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
                	arg.f10 = im.floatImage[(iw+1)
										  +  ih   *im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
                	arg.x = ih; 
					arg.y = is;
					arg.z = iw;
                	createContourALine(&(al[i]), arg);
					/*  z-x plane */
    				flagContour = contourFlagYSection;
	                arg.f00 = im.floatImage[(iw  ) 
										  +  ih   *im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
					arg.f01 = im.floatImage[(iw  ) 
										  + (ih+1)*im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
					arg.f11 = im.floatImage[(iw+1)
										  + (ih+1)*im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
                	arg.f10 = im.floatImage[(iw+1)
										  +  ih   *im.width
										  +  is   *im.width*im.height
										  ] - im.contourLevel[i];
                	arg.x = is; 
					arg.y = iw;
					arg.z = ih;
                	createContourALine(&(al[i]), arg);
				}
            }
        }
        al[i].current = al[i].top;
        if(0!=(psContourMode_SameLineWidthContour&mode)) {
            fprintf(fpt, "%f setlinewidth\n", im.contourLineWidthStart);
        }
        if(0!=(psContourMode_DifferentLineWidthContour&mode)) {
            fprintf(fpt, "%f setlinewidth\n", im.contourLineWidthStart+im.contourLineWidthStep*i);
        }
        while(al[i].current!=NULL) { /* Attention: pixel position + 0.5 */
             fprintf(fpt, "%7.1f %7.1f mt %7.1f %7.1f lt str\n", 
                          al[i].current->p0.x+0.5, al[i].current->p0.y+0.5,
                          al[i].current->p1.x+0.5, al[i].current->p1.y+0.5);
             al[i].current = al[i].current->next;
        }
    }
	memoryFree(al);
}

