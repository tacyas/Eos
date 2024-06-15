/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileImage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileImage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/psFile.h"

void
psFileImageSpaceSet(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
    fprintf(ps->fpt, "gsave\n");
    fprintf(ps->fpt, "%f %f scale\n", im.scaleX, im.scaleY);
    fprintf(ps->fpt, "%f %f translate\n", im.translateX, im.translateY);
}

void
psFileImageSpaceRotateSet(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
    fprintf(ps->fpt, "gsave\n");
    fprintf(ps->fpt, "%f rotate\n", im.angle);
}

void
psFileImageSpaceRotateRestore(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
    fprintf(ps->fpt, "grestore\n");
}

void
psFileImageSpaceRestore(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
    fprintf(ps->fpt, "grestore\n");
}

extern void __psFileImage1(psFile* ps, psImageInfo im, psParaTypeInteger mode);

void
psFileImage(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
    long i;
    psImageInfo tmp;

    tmp=im;
    tmp.height = 1;
    tmp.scaleX = tmp.scaleY = 1.0;
    for(i=0; i<im.height; i++) {
        tmp.translateY = im.translateY+i*tmp.height;
        tmp.image      = im.image+(tmp.width*tmp.height)*i;
        __psFileImage1(ps, tmp, 0);
    }
}

void
__psFileImage1(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
    long    	x, y;
	psImageInfo imSpace;

    psFileImageSpaceSet(ps, im, mode);

	imSpace.scaleX = imSpace.scaleY = 1.0;
	imSpace.translateX = imSpace.translateY = -0.5;
    psFileImageSpaceSet(ps, imSpace, mode);

	if(im.flagRGBColor) {
		fprintf(ps->fpt, "[/DeviceRGB] setcolorspace\n");
		fprintf(ps->fpt, "<<\n");
		fprintf(ps->fpt, "/ImageType 1\n");
		fprintf(ps->fpt, "/Width %d /Height %d\n", im.width, im.height);
		fprintf(ps->fpt, "/BitsPerComponent %d\n", im.bps);
		fprintf(ps->fpt, "/Decode [%f %f %f %f %f %f]\n", 0.0, im.Red, 0.0, im.Green, 0.0, im.Blue);
		/*
		fprintf(stderr, "/Decode [%f %f %f %f %f %f]\n", 0.0, im.Red, 0.0, im.Green, 0.0, im.Blue);
		*/
		fprintf(ps->fpt, "/ImageMatrix [%f %f %f %f %f %f]\n", 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
		fprintf(ps->fpt, "/DataSource currentfile /ASCIIHexDecode filter\n");
		fprintf(ps->fpt, ">>\n");
    	fprintf(ps->fpt, "image\n");
        for(y=0; y<im.height; y++) {
            for(x=0; x<im.width; x++) {
                fprintf(ps->fpt, "%02x%02x%02x", im.image[x+y*im.width], im.image[x+y*im.width], im.image[x+y*im.width]);
            }
            fprintf(ps->fpt, "\n");
        }
	} else if(im.flagRGBGradientColor) {
		fprintf(ps->fpt, "/DeviceRGB setcolorspace\n");
		fprintf(ps->fpt, "<<\n");
		fprintf(ps->fpt, "/ImageType 1\n");
		fprintf(ps->fpt, "/Width %d /Height %d\n", im.width, im.height);
		fprintf(ps->fpt, "/BitsPerComponent %d\n", im.bps);
		fprintf(ps->fpt, "/Decode [%f %f %f %f %f %f]\n", im.RedFirst, im.RedLast, im.GreenFirst, im.GreenLast, im.BlueFirst, im.BlueLast);
		fprintf(ps->fpt, "/ImageMatrix [%f %f %f %f %f %f]\n", 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
		fprintf(ps->fpt, "/DataSource currentfile /ASCIIHexDecode filter\n");
		fprintf(ps->fpt, ">>\n");
    	fprintf(ps->fpt, "image\n");
        for(y=0; y<im.height; y++) {
            for(x=0; x<im.width; x++) {
                fprintf(ps->fpt, "%02x%02x%02x", im.image[x+y*im.width], im.image[x+y*im.width], im.image[x+y*im.width]);
            }
            fprintf(ps->fpt, "\n");
        }
	} else if(im.flagHSBColor) {
		fprintf(stderr, "Not supported: HSBColor\n");
		exit(EXIT_FAILURE);
	} else if(im.flagHSBGradientColor) {
		fprintf(stderr, "Not supported: HSBGradientColor\n");
		exit(EXIT_FAILURE);
	} else {
    	fprintf(ps->fpt, "%ld %ld %ld\n", im.width, im.height, im.bps);
    	fprintf(ps->fpt, "[%f %f %f %f %f %f]\n", 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    	fprintf(ps->fpt, "{currentfile %ld string readhexstring pop} \n", im.width);
    	fprintf(ps->fpt, "image\n");
        for(y=0; y<im.height; y++) {
            for(x=0; x<im.width; x++) {
                fprintf(ps->fpt, "%02x", im.image[x+y*im.width]);
            }
            fprintf(ps->fpt, "\n");
        }
	}
    fprintf(ps->fpt, "\n");

    psFileImageSpaceRestore(ps, imSpace, mode);
    psFileImageSpaceRestore(ps, im, mode);
}

void
psFileImageByCircles(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
	long x, y;

    psFileImageSpaceSet(ps, im, mode);
	for(x=0; x<im.width; x++) { 
	for(y=0; y<im.height; y++) { 
		if(0<im.image[x+y*im.width]) {
			psFileCircleCreate(ps, x, y, im.image[x+y*im.width]/255.0*im.CircleRadius,  PS_FILL_BLACK_CIRCLE_MODE); 
		}
	}
	}
    psFileImageSpaceRestore(ps, im, mode);
}

void
psFileImageCentre(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
	psImageInfo imSpace;

	imSpace.scaleX = imSpace.scaleY = 1.0;
	imSpace.translateX = imSpace.translateY = -0.5;
    psFileImageSpaceSet(ps, imSpace, mode);

    fprintf(ps->fpt, "%f setlinewidth\n", PS_IMAGE_CENTRE_LINE_WIDTH);
    fprintf(ps->fpt, "%f %f mt\n%f %f rlt stroke\n%f %f mt %f %f rlt stroke\n",
		(float)im.width*(0.5-PS_IMAGE_CENTRE_MARK_LENGTH), 
		(float)im.height/2.0,                               
		(float)2.0*im.width*PS_IMAGE_CENTRE_MARK_LENGTH, 
		(float)0.0,
        (float)im.width/2.0,
		(float)im.height*(0.5-PS_IMAGE_CENTRE_MARK_LENGTH), 
		(float)0.0,                             
		(float)2.0*im.height*PS_IMAGE_CENTRE_MARK_LENGTH);

    psFileImageSpaceRestore(ps, imSpace, mode);
}

void
psFileImageScale(psFile* ps, psImageInfo im, psParaTypeInteger mode)
{
    long   x, y;
	FILE* fpt;
	psImageInfo imSpace;

	imSpace.scaleX = imSpace.scaleY = 1.0;
	imSpace.translateX = imSpace.translateY = -0.5;
    psFileImageSpaceSet(ps, imSpace, mode);

	fpt = ps->fpt;
    fprintf(fpt, "%f setlinewidth\n", PS_IMAGE_SCALE_LINE_WIDTH0);
    fprintf(fpt, "%ld %ld mt\n%ld %ld rlt\n%ld %ld rlt\n%ld %ld rlt\nclosepath stroke\n",
                  0L, 0L,        im.width, 0L,  0L, im.height, -im.width, 0L);
    fprintf(fpt, "%f setlinewidth\n", PS_IMAGE_SCALE_LINE_WIDTH1);
    if(mode==psImageScaleModeBottomLeft) {
        for(y=0; y<=(double)im.height; y++) {
            if(y%100==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+0.5,PS_IMAGE_SCALE_LINE_LENGTH00, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+0.5, PS_IMAGE_SCALE_LINE_LENGTH0, 0.0);
            } else if(y%50==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+0.5,PS_IMAGE_SCALE_LINE_LENGTH10, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+0.5, PS_IMAGE_SCALE_LINE_LENGTH1, 0.0);
            } else if(y%10==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+0.5,PS_IMAGE_SCALE_LINE_LENGTH20, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+0.5, PS_IMAGE_SCALE_LINE_LENGTH2, 0.0);
            } else if(y%5==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+0.5,PS_IMAGE_SCALE_LINE_LENGTH30, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+0.5, PS_IMAGE_SCALE_LINE_LENGTH3, 0.0);
            } else {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+0.5,PS_IMAGE_SCALE_LINE_LENGTH40, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+0.5, PS_IMAGE_SCALE_LINE_LENGTH4, 0.0);
            }
        }
        for(x=0; x<=(double)im.width; x++) {
            if(x%100==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH00);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH0);
            } else if(x%50==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH10);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH1);
            } else if(x%10==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH20);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH2);
            } else if(x%5==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH30);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH3);
            } else {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH40);          
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)x+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH4);
            }                                                      
        }
    } else if(mode==psImageScaleModeCenter) {
        for(y=0; y<=(double)im.height/2; y++) {
            if(y%100==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH00, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH0,  0.0);
            } else if(y%50==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH10, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH1,  0.0);
            } else if(y%10==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH20, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH2,  0.0);
            } else if(y%5==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH30, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH3,  0.0);
            } else {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH40, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH4,  0.0);
            }
        }
        for(y=-1; y>=-(double)im.height/2; y--) {
            if(y%100==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH00, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH0,  0.0);
            } else if(y%50==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH10, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH1,  0.0);
            } else if(y%10==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH20, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH2,  0.0);
            } else if(y%5==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH30, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH3,  0.0);
            } else {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", 0.0,              y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH40, 0.0);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", (double)im.width, y+(double)im.height/2+0.5, PS_IMAGE_SCALE_LINE_LENGTH4,  0.0);
            }
        }
        for(x=0; x<=(double)im.width/2; x++) {
            if(x%100==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH00);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH0);
            } else if(x%50==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH10);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH1);
            } else if(x%10==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH20);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH2);
            } else if(x%5==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH30);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH3);
            } else {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH40);          
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH4);
            }                                                      
        }
        for(x=-1; x>=-(double)im.width/2; x--) {
            if(x%100==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH00);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH0);
            } else if(x%50==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH10);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH1);
            } else if(x%10==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH20);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH2);
            } else if(x%5==0) {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH30);
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH3);
            } else {
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, 0.0,       0.0, PS_IMAGE_SCALE_LINE_LENGTH40);          
                fprintf(fpt, "%7.1f %7.1f mt %4.1f %4.1f rlt str\n", x+(double)im.width/2+0.5, (double)im.height, 0.0, PS_IMAGE_SCALE_LINE_LENGTH4);
            }                                                      
        }
    }
    psFileImageSpaceRestore(ps, imSpace, mode);
}

