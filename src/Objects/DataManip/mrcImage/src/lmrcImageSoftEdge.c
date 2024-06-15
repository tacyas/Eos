/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSoftEdge ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSoftEdge 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSoftEdge ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include <stdio.h>
#include <stdlib.h>

#include "./lmrcImageMorphology.h"
#include "./lmrcImageSoftEdge.h"

int
lmrcImageSoftEdge(mrcImage* out, mrcImage* in, lmrcImageSoftEdgeInfo linfo, int mode)
{
    mrcImageParaTypeReal x, y, z;
    mrcImageParaTypeReal offsetx, offsety, offsetz;
    double width, tmpWidth;
    double data, data0;
    double distance, near, nearx, neary, nearz;
    double xmin, ymin, zmin, xmax, ymax, zmax;
    double max;
    double dstData;
    mrcImage dilation, tmp; 
    lmrcImageMorphologyInfo minfo;
    int times;
    int flagNear;

    DEBUGPRINT("lmrcImageSoftEdge\n");
    out->Header = in->Header;
    mrcInit(out, NULL);

    max =  MAX(out->HeaderN.x, MAX(out->HeaderN.y, out->HeaderN.z));

    switch(linfo.envelop) {
        case lmrcImageSoftEdgeInfoEnvelopGaussian: 
            width = linfo.width*3.0; 
            break;
        case lmrcImageSoftEdgeInfoEnvelopCosine: 
            width = linfo.width*2;
            break;
        default:
            fprintf(stderr, "Not supported evelope: %d\n", linfo.envelop);
            exit(EXIT_FAILURE);
            break;
    }
/*
    minfo.mode = 5;
    minfo.n = width*2+1;
    minfo.radius = width;
*/

    minfo.mode = 4;
    minfo.n = 3;
    lmrcImageMorphologyStructuringElementSet(&minfo, 0);
    times = 0;
    tmp = *in;
    do { 
        lmrcImageDilation(&dilation, &tmp, minfo, 2);
        tmp = dilation;
        times++;
    } while(times<=width);
#ifdef DEBUG2
    mrcFileWrite(&dilation, "/tmp/test.dilation", "for test", 0); 
    mrcFileWrite(&minfo.SE, "/tmp/test.se", "for test", 0); 
#endif
    for(z=0; z<out->HeaderN.z; z++) {
	DEBUGPRINT1("%d\n", (int)z);
    for(y=0; y<out->HeaderN.y; y++) {
    for(x=0; x<out->HeaderN.x; x++) {
        mrcPixelDataGet(in, x, y, z, &data,  mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(&dilation, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
        if(0<data) {
            dstData = data;
        } else if(0<data0) {
            //DEBUGPRINT5("%f %f %f: %f %f\n", x, y, z, data0, data);
            near = max;
            dstData = 0;
            flagNear=0;
            for(tmpWidth=1; tmpWidth<=width; tmpWidth++) { 
                xmin = MAX(0, x-tmpWidth); xmax = MIN(x+tmpWidth, out->HeaderN.x - 1); 
                ymin = MAX(0, y-tmpWidth); ymax = MIN(y+tmpWidth, out->HeaderN.y - 1);
                zmin = MAX(0, z-tmpWidth); zmax = MIN(z+tmpWidth, out->HeaderN.z - 1);
                for(offsetz=zmin; offsetz<=zmax; offsetz++) {
                for(offsety=ymin; offsety<=ymax; offsety++) {
                for(offsetx=xmin; offsetx<=xmax; offsetx++) {
                    distance = sqrt(SQR(offsetx -x) + SQR(offsety - y) + SQR(offsetz - z));  
                    if(distance<width) { 
                        mrcPixelDataGet(in, offsetx, offsety, offsetz, &data, mrcPixelRePart, mrcPixelHowNearest);
                        if(0<data) {
                            if(distance < near) {
                                near = distance;
                                nearx = offsetx;
                                neary = offsety;
                                nearz = offsetz;
                                dstData = data;
                                flagNear++;
                            }
                        }
                    }
                }
                }
                }
                if(0<flagNear) {
                    break;
                }
            }
            if(0<dstData) {
                //DEBUGPRINT5("%f %f %f: %f %f\n", x, y, z, data0, data);
                switch(linfo.envelop) {
                    case lmrcImageSoftEdgeInfoEnvelopGaussian: 
                        dstData *= exp(-SQR(near/linfo.width)/2.0);
                        break;
                    case lmrcImageSoftEdgeInfoEnvelopCosine: 
                        if(near<linfo.width*2) {
                            dstData *= (cos(2*M_PI*near/4/linfo.width)+1)/2.0;
                        } else {
                            dstData = 0;
                        }
                        break;
                    default:
                        fprintf(stderr, "Not supported envelop:  %d\n", linfo.envelop);
                        exit(EXIT_FAILURE);
                        break;
                }
                //DEBUGPRINT6("%f %f %f: %f %f %f \n", x, y, z, dstData, data0, data);
            }
        } else {
            dstData = 0;
        }
        mrcPixelDataSet(out, x, y, z, dstData, mrcPixelRePart);
    }
    }
    }
    return  0;
}
