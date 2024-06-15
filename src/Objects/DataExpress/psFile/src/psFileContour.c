/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileContour ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileContour 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileContour ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genUtil.h"
#include "Contour.h"
#include "Memory.h"
#include "../inc/psFile.h"


extern void __psContour(FILE* fpt, psImageInfo im, psParaTypeInteger mode);

void
psFileContour(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
	psImageInfo imSpace;

	imSpace.translateX = 0;
	imSpace.translateY = 0;
	imSpace.scaleX     = imSpace.scaleY     = 1.0;
	psFileImageSpaceSet(ps, imSpace, mode);
	
	__psContour(ps->fpt, im, mode);

	psFileImageSpaceRestore(ps, imSpace, mode);
}

void
__psContour(FILE* fpt, psImageInfo im, psParaTypeInteger mode)
{
    contourLine* al;
    contourArgs arg;
    contourParaTypeInteger iw, ih, i;
    extern contourFlag flagContour;

    al = (contourLine*)memoryAllocate(sizeof(contourLine)*im.nContour, "in psContour(al)");
    arg.dx = arg.dy = 1;
    arg.z  = 0.0;
    flagContour = contourFlagZSection;
    for(i=0; i<im.nContour; i++) {
        al[i].current = al[i].top = NULL;
        for(iw=0; iw<im.width-1; iw++) {
            for(ih=0; ih<im.height-1; ih++) {
                arg.f00 = im.floatImage[(iw  ) +  ih   *im.width] - im.contourLevel[i];
                arg.f01 = im.floatImage[(iw  ) + (ih+1)*im.width] - im.contourLevel[i];
                arg.f11 = im.floatImage[(iw+1) + (ih+1)*im.width] - im.contourLevel[i];
                arg.f10 = im.floatImage[(iw+1) +  ih   *im.width] - im.contourLevel[i];
                arg.x   = iw; arg.y = ih;
                createContourALine(&(al[i]), arg);
            }
        }
        al[i].current = al[i].top;
        if(0!=(psContourMode_SameLineWidthContour&mode)) {
            fprintf(fpt, "%f setlinewidth\n", im.contourLineWidthStart);
        }
        if(0!=(psContourMode_DifferentLineWidthContour&mode)) {
            fprintf(fpt, "%f setlinewidth\n", im.contourLineWidthStart+im.contourLineWidthStep*i);
        }

		if(im.flagLineRGBColor==1) {
			if(im.contourLevel[i]<im.contourLineColorChange) {
				fprintf(fpt, "%f %f %f setrgbcolor\n", MIN(1,im.LineRed+0.5), MIN(1,im.LineGreen+0.5), MIN(1,im.LineBlue+0.5));
			} else {
				fprintf(fpt, "%f %f %f setrgbcolor\n", im.LineRed, im.LineGreen, im.LineBlue);
			}
		} else if(im.flagLineRGBGradientColor==1) {
			if(im.nContour<2) {
				fprintf(fpt, "%f %f %f setrgbcolor\n", im.LineRedFirst, im.LineGreenFirst, im.LineBlueFirst); 
			}
			fprintf(fpt, "%f %f %f setrgbcolor\n", 
				(i*im.LineRedLast   +(im.nContour-1-i)*im.LineRedFirst  )/(im.nContour-1),
				(i*im.LineGreenLast +(im.nContour-1-i)*im.LineGreenFirst)/(im.nContour-1),
				(i*im.LineBlueLast  +(im.nContour-1-i)*im.LineBlueFirst )/(im.nContour-1));
		} else if(im.flagLineHSBColor==1) {
			if(im.contourLevel[i]<im.contourLineColorChange) {
				fprintf(fpt, "%f %f %f sethsbcolor\n", im.LineHue, im.LineSaturation, im.LineBrightness);
			} else {
				fprintf(fpt, "%f %f %f sethsbcolor\n", im.LineHue, im.LineSaturation/2, im.LineBrightness);
			}
		} else if(im.flagLineHSBGradientColor==1) {
			if(im.nContour<2) {
				fprintf(fpt, "%f %f %f sethsbcolor\n", im.LineHueFirst, im.LineSaturationFirst, im.LineBrightnessFirst); 
			}
			fprintf(fpt, "%f %f %f sethsbcolor\n", 
				(i*im.LineHueLast        +(im.nContour-1-i)*im.LineHueFirst       )/(im.nContour-1), 
				(i*im.LineSaturationLast +(im.nContour-1-i)*im.LineSaturationFirst)/(im.nContour-1), 
				(i*im.LineBrightnessLast +(im.nContour-1-i)*im.LineBrightnessFirst)/(im.nContour-1));
		} else {
			if(im.contourLevel[i]<im.contourLineColorChange) {
				fprintf(fpt, "0.5 setgray\n");
			} else {
				fprintf(fpt, "0   setgray\n");
			}
		}
        while(al[i].current!=NULL) { /* Attention: pixel position */
        	fprintf(fpt, "%7.1f %7.1f mt %7.1f %7.1f lt str\n", 
                          al[i].current->p0.x, al[i].current->p0.y,
                          al[i].current->p1.x, al[i].current->p1.y);
            al[i].current = al[i].current->next;
        }
		fprintf(fpt, "0 setgray\n");
		
    }
	memoryFree(al);
}

