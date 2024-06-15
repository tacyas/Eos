/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc2bild ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrc2bild 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrc2bild ver%I%; Date:%D% %Z%";

#include <float.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/bildFile.h"

void
lmrc2bildUsage(FILE* fpt)
{
	fprintf(fpt, "%d: Arrows\n", lmrc2bildModeArrows);
	fprintf(fpt, "%d: Spheres\n", lmrc2bildModeSpheres);
}

void
lmrc2bild(FILE* fpt, mrcImage* in, lmrc2bildInfo linfo, int mode)
{
	switch(mode) {
		case lmrc2bildModeArrows: {
			lmrc2bildArrows(fpt, in, linfo, mode);
			break;
		}
		case lmrc2bildModeSpheres: {
			lmrc2bildSpheres(fpt, in, linfo, mode);
			break;
		}
	}
}


void
lmrc2bildArrows(FILE* fpt, mrcImage* in, lmrc2bildInfo linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal startx, starty, startz;
	mrcImageParaTypeReal endx, endy, endz;
	double d0, d1, d2, d;
	int skipX, skipY, skipZ;
  double min, max;
  mrcImage size;
  double r, g, b, half, center;
  double minx, miny, minz;
  double maxx, maxy, maxz;
  double cenx, ceny, cenz;
  double RR;
  int    inR;

  size.Header = in[0].Header;
  mrcInit(&size, NULL);

	fprintf(fpt, ".color %g %g %g\n", linfo.color[0], linfo.color[1], linfo.color[2]);

	if(linfo.flagSkip) {
		skipX = linfo.skipX;
		skipY = linfo.skipY;
		skipZ = linfo.skipZ;
	} else {
		skipX = 1;
		skipY = 1;
		skipZ = 1;
	}
  min = FLT_MAX;
  max = FLT_MIN;
	for(z=0; z<in[0].HeaderN.z; z+=skipZ) {
	for(y=0; y<in[0].HeaderN.y; y+=skipY) {
	for(x=0; x<in[0].HeaderN.x; x+=skipX) {
		mrcPixelDataGet(&in[0], x, y, z, &d0, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&in[1], x, y, z, &d1, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&in[2], x, y, z, &d2, mrcPixelRePart, mrcPixelHowNearest);
    d = sqrt(d0*d0 + d1*d1 + d2*d2);
		mrcPixelDataSet(&size, x, y, z, d, mrcPixelRePart);
    if(d<min) min = d;
    if(max<d) max = d;
  }
  }
  }
  if(!linfo.flagRainbowThresLow) {
    linfo.RainbowThresLow = min;
  }
  if(!linfo.flagRainbowThresHigh) {
    linfo.RainbowThresHigh = max;
  }
  if(!linfo.flagRainbowRangeLow) {
    linfo.RainbowRangeLow = min;
  }
  if(!linfo.flagRainbowRangeHigh) {
    linfo.RainbowRangeHigh = max;
  }

  half   = (linfo.RainbowThresHigh - linfo.RainbowThresLow)/2;
  center = (linfo.RainbowThresLow + linfo.RainbowThresHigh)/2;

    if(linfo.flagRangeX) {
        minx = linfo.RangeXMin;
        maxx = linfo.RangeXMax;
    } else {
        minx = 0;
        maxx = in[0].HeaderN.x + skipX;
    }
    if(linfo.flagRangeY) {
        miny = linfo.RangeYMin;
        maxy = linfo.RangeYMax;
    } else {
        miny = 0;
        maxy = in[0].HeaderN.y + skipY;
    }
    if(linfo.flagRangeZ) {
        minz = linfo.RangeZMin;
        maxz = linfo.RangeZMax;
    } else {
        minz = 0;
        maxz = in[0].HeaderN.z + skipZ;
    }

    DEBUGPRINT3("skip: %d %d %d\n", skipX, skipY, skipZ);
    DEBUGPRINT2("x: %f %f\n", minx, maxx);
    DEBUGPRINT2("y: %f %f\n", miny, maxy);
    DEBUGPRINT2("z: %f %f\n", minz, maxz);

	for(z=minz; z<maxz; z+=skipZ) {
	for(y=miny; y<maxy; y+=skipY) {
	for(x=minx; x<maxx; x+=skipX) {
        if(linfo.flagRangeR) {
            RR = sqrt(SQR(x-linfo.RangeRCX)+SQR(y-linfo.RangeRCY)+SQR(z-linfo.RangeRCZ));
            if(RR<=linfo.RangeRR) {
                inR = 1;
            } else {
                inR = 0;
            }
        } else {
            inR = 1;
        }
        if(inR) {
			mrcPixelDataGet(&in[0], x, y, z, &d0, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&in[1], x, y, z, &d1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&in[2], x, y, z, &d2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&size,  x, y, z, &d,  mrcPixelRePart, mrcPixelHowNearest);
			if(d0==0 && d1==0 && d2==0) {
			} else {
				startx = (x+in[0].HeaderStartN.x)*in[0].HeaderLength.x; 
				starty = (y+in[0].HeaderStartN.y)*in[0].HeaderLength.y; 
				startz = (z+in[0].HeaderStartN.z)*in[0].HeaderLength.z; 
				endx   = startx + d0*in[0].HeaderLength.x*linfo.zoom;
				endy   = starty + d1*in[1].HeaderLength.y*linfo.zoom;
				endz   = startz + d2*in[2].HeaderLength.z*linfo.zoom;

            if(linfo.flagRainbow) {
                switch(linfo.RainbowMode) {
                    case 0: {
                        if(d < linfo.RainbowThresLow) {
                            r = 0; g = 0; b = 1;
                        } else if(linfo.RainbowThresLow <= d && d < center) {
                            r = 0;
                            g = (d - linfo.RainbowThresLow)/half*(+1) ; 
                            b = (d - linfo.RainbowThresLow)/half*(-1) + 1; 
                        } else if(center <= d && d < linfo.RainbowThresHigh) {
                            r = (d - linfo.RainbowThresLow)/half*(+1) - 1;  
                            g = (d - linfo.RainbowThresLow)/half*(-1) + 2;
                            b = 0;
                        } else {
                            r = 1; g = 0; b = 0;
                        }
                        break;
                    }
                }  
            }
            if(linfo.RainbowRangeLow <= d && d <= linfo.RainbowRangeHigh) {
                if(linfo.flagRainbow) {
                    fprintf(fpt, ".color %f %f %f\n", r, g, b);
                }
				fprintf(fpt, ".arrow %g %g %g %g %g %g %g %g %g\n", startx, starty, startz,
																	endx,   endy,   endz,
																	linfo.r1, linfo.r2, linfo.rho);
            }
		    }
        }
	}
	}
	}
}


void
lmrc2bildSpheres(FILE* fpt, mrcImage* in, lmrc2bildInfo linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal startx, starty, startz;
	mrcImageParaTypeReal endx, endy, endz;
	double d0, d1, d2;

	int skipX, skipY, skipZ;
	fprintf(fpt, ".color %g %g %g\n", linfo.color[0], linfo.color[1], linfo.color[2]);


	if(linfo.flagSkip) {
		skipX = linfo.skipX;
		skipY = linfo.skipY;
		skipZ = linfo.skipZ;
	} else {
		skipX = 1;
		skipY = 1;
		skipZ = 1;
	}

	for(z=0; z<in[0].HeaderN.z; z+=skipZ) {
	for(y=0; y<in[0].HeaderN.y; y+=skipY) {
	for(x=0; x<in[0].HeaderN.x; x+=skipX) {
		mrcPixelDataGet(&in[0], x, y, z, &d0, mrcPixelRePart, mrcPixelHowNearest);
		if(d0==0 && d1==0 && d2==0) {
		} else {
			startx = (x+in[0].HeaderStartN.x)*in[0].HeaderLength.x; 
			starty = (y+in[0].HeaderStartN.y)*in[0].HeaderLength.y; 
			startz = (z+in[0].HeaderStartN.z)*in[0].HeaderLength.z; 
			fprintf(fpt, ".sphere %g %g %g %g\n", startx
										     , starty
											 , startz
											 ,d0*in[0].HeaderLength.x*linfo.zoom);
		}
	}
	}
	}
}

