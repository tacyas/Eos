/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImagePrint ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImagePrint
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImagePrint ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
    
#include "../inc/config.h"
#include "lmrcImagePrint.h"
#define DEBUG
#include "genUtil.h"
#include "Memory.h"

extern void lmrcImagePrint(mrcImage* img, mrcImage* mrc, mrcImagePrintInfo* info);

int
main(int argc, char* argv[])
{
    mrcImage img1;
    mrcImage img2;
	mrcImagePrintInfo  info;
	mrcImagePSFilePrintInfo psInfo;
	unsigned long mod;
	long i;
   	char message[1024];
	double offset; 
	float scale;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	DEBUGPRINT("Program Start\n");
	if(info.flagEnlarge && info.Enlarge < 1.0) {
		usage(argv[0]);
	}
    mrcFileRead(&img1, info.In, "from Main Routine", 0);
    mrcStatDataSet(&img1, 0);

    lmrcImagePrint(&img2, &img1, &info);

    sprintf(message, "%s: N(%d,%d),Length(%7.2g,%7.2g), data(%7.2g,%7.2g,%7.2g), print(%7.2g-%7.2g), by %s",
            info.In,
            (int)img1.HeaderN.x, (int)img1.HeaderN.y,
            img1.HeaderLength.x, img1.HeaderLength.y,
            img1.HeaderAMax,     img1.HeaderAMin,     img1.HeaderAMean,
            img2.HeaderAMax,     img2.HeaderAMin,
			__sccs_id);

	if(info.flagAutoContour && (info.flagcontourLevel == 0)) {
		info.flagcontourLevel = info.AutoContour;
		info.contourLevel     = (float*)memoryAllocate(sizeof(float)*info.flagcontourLevel, "in main");
		offset = img2.HeaderAMean;
		for(i=0; i<info.flagcontourLevel; i++) {
			info.contourLevel[i] = (i+1)*(img2.HeaderAMax - offset)/(info.flagcontourLevel+ 1) + offset;
		}
	}
	if(info.flagPeakContour && (info.flagcontourLevel == 0)) {
		info.flagcontourLevel = info.PeakContour;
		info.contourLevel     = (float*)memoryAllocate(sizeof(float)*info.flagcontourLevel, "in main");
		offset = (img2.HeaderAMax + img2.HeaderAMean)/2.0;
		for(i=0; i<info.flagcontourLevel; i++) {
			info.contourLevel[i] = i*(img2.HeaderAMax - offset)/(info.flagcontourLevel)     + offset;
		}
	}
	if(info.flagAutoContour2 && (info.flagcontourLevel == 0)) {
		info.flagcontourLevel = info.AutoContour2;
		info.contourLevel     = (float*)memoryAllocate(sizeof(float)*info.flagcontourLevel, "in main");
		offset = img2.HeaderAMin;
		for(i=0; i<info.flagcontourLevel; i++) {
			info.contourLevel[i] = (i+1)*(img2.HeaderAMax - offset)/(info.flagcontourLevel+ 1) + offset;
		}
	}

	if(info.flagYexpand) {
		img2.HeaderLength.y  = img2.HeaderLength.y*info.Yexpand;
		info.Scale          *= info.Yexpand;
	}

	if(info.flagAbScale) {
		if(IsImage(&img2, "", 0)) { 
			scale = img2.HeaderLength.y*info.AbScale;
		} else {
			scale = 1.0/(img2.HeaderLength.y*img2.HeaderN.y)*info.AbScale; 
		}	
	} else {
		scale = info.Scale;
	}

	/* RGB Mode */
	DEBUGPRINT3("R: %d G: %d B: %d\n", info.flagRed, info.flagGreen, info.flagBlue);
	if(info.flagRed && info.flagGreen && info.flagBlue) { /* RGB Mode */
		psInfo.psInfo.flagRGBColor = 1;	
		psInfo.psInfo.Red   = info.Red;
		psInfo.psInfo.Green = info.Green;
		psInfo.psInfo.Blue  = info.Blue;
	} else {
		psInfo.psInfo.flagRGBColor = 0;	
	}
	if(info.flagRedFirst && info.flagGreenFirst && info.flagBlueFirst) { /* RGB Gradient Mode */
		psInfo.psInfo.flagRGBGradientColor = 1;	
		psInfo.psInfo.RedFirst   = info.RedFirst;
		psInfo.psInfo.GreenFirst = info.GreenFirst;
		psInfo.psInfo.BlueFirst  = info.BlueFirst;
		psInfo.psInfo.RedLast    = info.RedLast;
		psInfo.psInfo.GreenLast  = info.GreenLast;
		psInfo.psInfo.BlueLast   = info.BlueLast;
	} else {
		psInfo.psInfo.flagRGBGradientColor = 0;	
	}
	
	/* HSB Mode */
	if(info.flagHue && info.flagSaturation && info.flagBrightness) { /* HSB Mode */
		psInfo.psInfo.flagHSBColor = 1;	
		psInfo.psInfo.Hue        = info.Hue;
		psInfo.psInfo.Saturation = info.Saturation;
		psInfo.psInfo.Brightness = info.Brightness;
	} else {
		psInfo.psInfo.flagHSBColor = 0;	
	}
	if(info.flagHueFirst && info.flagSaturationFirst && info.flagBrightnessFirst) { /* HSB Gradient Mode */
		psInfo.psInfo.flagHSBGradientColor = 1;	
		psInfo.psInfo.HueFirst        = info.HueFirst;
		psInfo.psInfo.SaturationFirst = info.SaturationFirst;
		psInfo.psInfo.BrightnessFirst = info.BrightnessFirst;
		psInfo.psInfo.HueLast         = info.HueFirst;
		psInfo.psInfo.SaturationLast  = info.SaturationFirst;
		psInfo.psInfo.BrightnessLast  = info.BrightnessFirst;
	} else {
		psInfo.psInfo.flagHSBGradientColor = 0;	
	}

	/* RGB Mode */
	if(info.flagLineRed && info.flagLineGreen && info.flagLineBlue) { /* RGB Mode */
		psInfo.psInfo.flagLineRGBColor = 1;	
		psInfo.psInfo.LineRed   = info.LineRed;
		psInfo.psInfo.LineGreen = info.LineGreen;
		psInfo.psInfo.LineBlue  = info.LineBlue;
	} else {
		psInfo.psInfo.flagLineRGBColor = 0;	
	}
	if(info.flagLineRedFirst && info.flagLineGreenFirst && info.flagLineBlueFirst) { /* RGB Gradient Mode */
		psInfo.psInfo.flagLineRGBGradientColor = 1;	
		psInfo.psInfo.LineRedFirst   = info.LineRedFirst;
		psInfo.psInfo.LineGreenFirst = info.LineGreenFirst;
		psInfo.psInfo.LineBlueFirst  = info.LineBlueFirst;
		psInfo.psInfo.LineRedLast    = info.LineRedLast;
		psInfo.psInfo.LineGreenLast  = info.LineGreenLast;
		psInfo.psInfo.LineBlueLast   = info.LineBlueLast;
	} else {
		psInfo.psInfo.flagLineRGBGradientColor = 0;	
	}
	
	/* HSB Mode */
	if(info.flagLineHue && info.flagLineSaturation && info.flagLineBrightness) { /* HSB Mode */
		psInfo.psInfo.flagLineHSBColor = 1;	
		psInfo.psInfo.LineHue        = info.LineHue;
		psInfo.psInfo.LineSaturation = info.LineSaturation;
		psInfo.psInfo.LineBrightness = info.LineBrightness;
	} else {
		psInfo.psInfo.flagLineHSBColor = 0;	
	}
	if(info.flagLineHueFirst && info.flagLineSaturationFirst && info.flagLineBrightnessFirst) { /* HSB Gradient Mode */
		psInfo.psInfo.flagLineHSBGradientColor = 1;	
		psInfo.psInfo.LineHueFirst        = info.LineHueFirst;
		psInfo.psInfo.LineSaturationFirst = info.LineSaturationFirst;
		psInfo.psInfo.LineBrightnessFirst = info.LineBrightnessFirst;
		psInfo.psInfo.LineHueLast         = info.LineHueFirst;
		psInfo.psInfo.LineSaturationLast  = info.LineSaturationFirst;
		psInfo.psInfo.LineBrightnessLast  = info.LineBrightnessFirst;
	} else {
		psInfo.psInfo.flagLineHSBGradientColor = 0;	
	}
			
	mod = info.mode&0xff000000;	
	if(0==mod) {
		psInfo.scale = scale;	
		psInfo.contourLineColorChange = info.LineColorChange;
		psInfo.contourLineWidthStart  = info.LineWidthStart;	
		psInfo.contourLineWidthStep   = info.LineWidthStep;	
		psInfo.whichSection = info.section;
		psInfo.centre = info.Centre;
		psInfo.untwistAngle = info.untwist*RADIAN;
		psInfo.circleRadius = info.CircleRadius;
		mrcImagePSFilePrint   (info.fptOut, &img2, message, psInfo, info.flagcontourLevel, info.contourLevel, info.mode);
	} else {
    	mrcImageASCIIFilePrint(info.fptOut, &img2, message, scale, info.flagcontourLevel, info.contourLevel, info.mode);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_ImageDensity, mrcImagePrintMode_ImageDensity_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_Contour, mrcImagePrintMode_Contour_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_Contour2, mrcImagePrintMode_Contour2_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_ImageCircle, mrcImagePrintMode_ImageCircle_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_Scale, mrcImagePrintMode_Scale_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_Centre, mrcImagePrintMode_Centre_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_ASCII_Amp, mrcImagePrintMode_ASCII_Amp_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_ASCII_LogAmp, mrcImagePrintMode_ASCII_LogAmp_String);
	fprintf(stderr, "\t\t%6d: %s\n", mrcImagePrintMode_ASCII_Phase, mrcImagePrintMode_ASCII_Phase_String);
	fprintf(stderr, "----- Attention !! -----\n");
	fprintf(stderr, "\t\t\t\t-C  option is stronger than -AC and -PC\n");
	fprintf(stderr, "\t\t\t\t-PC option is stronger than -AC\n");
	fprintf(stderr, "\t\t\t\t\t-AC: (i+1)*(max-maen)  /(AC+1) + mean \n");
	fprintf(stderr, "\t\t\t\t\t-PC: (i  )*(max+mean)/2)/AC     + (max+mean)/2\n");
	fprintf(stderr, "----- Attention 2!! -----\n");
	fprintf(stderr, "\t\t\t\t-AS option is stronger than -S option\n");
	fprintf(stderr, "\t\t\t\tThe default value of -AS option is ignored.\n");
	fprintf(stderr, "\t\t\t\tThe default value of -S option is used.\n");
	fprintf(stderr, "\t\t\t\tBoth options are applied to y-axis.\n");
}

void 
lmrcImagePrint(mrcImage* img, mrcImage* mrc, mrcImagePrintInfo* info)
{
	long x, nx, ix;
	long y, ny, iy;
	long z, nz, iz;
    double dat;
	mrcImageInformation mrcinfo;
	mrcImageParaTypeReal dstx, dsty, srcx, srcy;

	mrcinfo.mode = meanOfAll;

	/* x */	
    if(info->flagxMin && info->flagxMax) {
        if(IsFT(mrc, "", 0)) {
            fprintf(stderr, "Sorry: -x Option is not implemented for FT for a moment\n");
            usage("mrcImagePrint");
        } else {
			DEBUGPRINT2("%d %d\n", info->xMin, info->xMax);
		}
    } else {
        if(IsImage(mrc, "", 0)) {
            info->xMin = 0;
            info->xMax = mrc->HeaderN.x - 1;
        } else if(IsFT(mrc, "", 0)) {
            info->yMin = -img->HeaderN.y/2;
            info->yMax =  img->HeaderN.y/2;
        }
    }
    nx = info->xMax - info->xMin + 1;

	/* y */	
    if(info->flagyMin && info->flagyMax) {
        if(IsFT(mrc, "", 0)) {
            fprintf(stderr, "Sorry: -y Option is not implemented for FT for a moment\n");
            usage("mrcImagePrint");
        } else {
			DEBUGPRINT2("%d %d\n", info->yMin, info->yMax);
		}
    } else {
        if(IsImage(mrc, "", 0)) {
            info->yMin = 0;
            info->yMax = mrc->HeaderN.y - 1;
        } else if(IsFT(mrc, "", 0)) {
            info->yMin = -img->HeaderN.y/2;
            info->yMax =  img->HeaderN.y/2;
        }
    }
    ny = info->yMax - info->yMin + 1;

	/* z */	
    if(info->flagzMin && info->flagzMax) {
        if(IsFT(mrc, "", 0)) {
            fprintf(stderr, "Sorry: -z Option is not implemented for FT for a moment\n");
            usage("mrcImagePrint");
        } else {
			DEBUGPRINT2("%d %d\n", info->zMin, info->zMax);
		}
    } else {
        if(IsImage(mrc, "", 0)) {
            info->zMin = 0;
            info->zMax = mrc->HeaderN.z - 1;
        } else if(IsFT(mrc, "", 0)) {
            info->zMin = -img->HeaderN.z/2;
            info->zMax =  img->HeaderN.z/2;
        }
    }
    nz = info->zMax - info->zMin + 1;

    if(nx<=0) {
        fprintf(stderr, "x Option value is wrong.\n");
        usage("mrcImagePrint");
    }
    if(ny<=0) {
        fprintf(stderr, "y Option value is wrong.\n");
        usage("mrcImagePrint");
    }
    if(nz<=0) {
        fprintf(stderr, "z Option value is wrong.\n");
        usage("mrcImagePrint");
    }
    DEBUGPRINT3("n: %d %d %d\n", nx, ny, nz);  
    if(0==info->flagEnlarge) {
        img->Header = mrc->Header;
  		if(IsImage(mrc, "", 0)) {
			DEBUGPRINT1("%d\n",nz);
        	img->HeaderN.x = nx;
        	img->HeaderN.y = ny;
        	img->HeaderN.z = nz;
   		}
    } else {
  		if(IsImage(mrc, "", 0)) {
        	fprintf(stderr, "-Enlarge is used in the case of FT\n");
        	usage("mrcImagePrint");
		} else if(IsFT(mrc, "", 0)) {
        	img->Header = mrc->Header;
			if('x'==info->section) { 
   	    	 	img->HeaderN.y = mrc->HeaderN.y/info->Enlarge;
   		   		img->HeaderN.z = mrc->HeaderN.z/info->Enlarge;
			}else if('y'==info->section) { 
   	    	 	img->HeaderN.z = mrc->HeaderN.z/info->Enlarge;
   		   		img->HeaderN.x = mrc->HeaderN.x/info->Enlarge;
			}else if('z'==info->section) { 
   		   		img->HeaderN.x = mrc->HeaderN.x/info->Enlarge;
       		 	img->HeaderN.y = mrc->HeaderN.y/info->Enlarge;
			}
		}
	}

    if(img->HeaderN.x==0) {
        img->HeaderN.x = 1;
    }
    if(img->HeaderN.y==0) {
    	img->HeaderN.y = 1;
    }
    if(img->HeaderN.z==0) {
        img->HeaderN.z = 1;
    }
	/* Initialize */
    mrcInit(img, NULL);

    if(IsImage(img, "", 0)) {
        for(ix=0; ix < nx; ix++) {
			if('x'==info->section) {
				if(info->UpsideDown) {
					if(info->ReverseOrder) {	
						x = info->xMin + ix; 
					} else {
						x = info->xMax - ix;
					}
				} else {
					if(info->ReverseOrder) {	
						x = info->xMax - ix; 
					} else {
						x = info->xMin + ix;
					}
				}
			} else {
				x = info->xMin + ix;
			}
        	for(iy=0; iy < ny; iy++) {
				if('y'==info->section) {
					if(info->UpsideDown) {
						if(info->ReverseOrder) {	
							y = info->yMin + iy; 
						} else {
							y = info->yMax - iy;
						}
					} else {
						if(info->ReverseOrder) {	
							y = info->yMax - iy; 
						} else {
							y = info->yMin + iy;
						}
					}
				} else {
					y = info->yMin + iy;
				}
            	for(iz=0; iz<nz; iz++) { /* for(z=info->zMin; z <= info->zMax; z++) { */
					/* input : z, output: iz */ 
					if('z'==info->section) {
						if(info->UpsideDown) {
							if(info->ReverseOrder) {	
								z = info->zMin + iz; 
							} else {
								z = info->zMax - iz;
							}
						} else {
							if(info->ReverseOrder) {	
								z = info->zMax - iz; 
							} else {
								z = info->zMin + iz;
							}
						}
					} else {
						z = info->zMin + iz;
					}

					if(0==info->flagcx && 0==info->flagcy) {
						srcx = (long)(x + (mrc->HeaderN.x - img->HeaderN.x)/2.0 + 0.5);
						srcy = (long)(y + (mrc->HeaderN.y - img->HeaderN.y)/2.0 + 0.5);
					} else {
						srcx = ((long)(x + mrc->HeaderN.x/2.0 - info->cx + (mrc->HeaderN.x - img->HeaderN.x)/2.0 + mrc->HeaderN.x + 0.5))%mrc->HeaderN.x;
						srcy = ((long)(y + mrc->HeaderN.y/2.0 - info->cy + (mrc->HeaderN.y - img->HeaderN.y)/2.0 + mrc->HeaderN.y + 0.5))%mrc->HeaderN.y;
					}
					DEBUGPRINT4("(x,y) = (%d %d) <- (srcx, srcy) = (%f, %f)\n", x, y, srcx, srcy);
                	mrcPixelDataGet(mrc, 
                                       (mrcImageParaTypeReal)srcx, 
                                       (mrcImageParaTypeReal)srcy, 
                                       (mrcImageParaTypeReal)z,
                                        &dat,
                                        mrcPixelMag,
                                        mrcPixelHowNearest);

					dstx = x;
					dsty = y;
					if( dstx <  img->HeaderN.x && dsty < img->HeaderN.y
					  &&dstx >= 0              && dsty >= 0) {
						if(info->UpsideDown) {
	                   		mrcPixelDataSet(img, 
   	                                   (mrcImageParaTypeReal)img->HeaderN.x - 1 - dstx,
   	                                   (mrcImageParaTypeReal)dsty,
   	                                   (mrcImageParaTypeReal)iz,
   	                                    dat,
   									mrcPixelMag);
						} else {
	                   		mrcPixelDataSet(img, 
   	                                   (mrcImageParaTypeReal)dstx,
   	                                   (mrcImageParaTypeReal)dsty,
   	                                   (mrcImageParaTypeReal)iz,
   	                                    dat,
   									mrcPixelMag);
						}
					}
                } /* iz */
            } /* y */
        } /* x */
    } else if(IsFT(img, "", 0)) {
        for(x=0; x<=img->HeaderN.x/2.0; x++) {
        	for(y=-img->HeaderN.y/2.0; y<img->HeaderN.y/2.0; y++) {
            	for(z=-img->HeaderN.z/2.0; z<img->HeaderN.z/2.0; z++) {
                	mrcPixelDataGet(mrc, 
                                       (mrcImageParaTypeReal)x, 
                                       (mrcImageParaTypeReal)y, 
                                       (mrcImageParaTypeReal)z,
                                        &dat,
                                        mrcPixelRePart,
                                        mrcPixelHowNearest);
                    mrcPixelDataSet(img, 
                                       (mrcImageParaTypeReal)x, 
                                       (mrcImageParaTypeReal)y, 
                                       (mrcImageParaTypeReal)z,
                                        dat,
                                        mrcPixelRePart);
                    mrcPixelDataGet(mrc, 
                                       (mrcImageParaTypeReal)x, 
                                       (mrcImageParaTypeReal)y, 
                                       (mrcImageParaTypeReal)z,
                                        &dat,
                                        mrcPixelImPart,
                                        mrcPixelHowNearest);
                    mrcPixelDataSet(img, 
                                       (mrcImageParaTypeReal)x, 
                                       (mrcImageParaTypeReal)y, 
                                       (mrcImageParaTypeReal)z,
                                        dat,
                                        mrcPixelImPart);
                }
            }
        }
    } else {
        fprintf(stderr, "Not Supported Mode\n");
        exit(EXIT_FAILURE);
    }
	mrcStatDataSet(img, 0);
	if(info->Auto) {
		lmrcImageInformation(&mrcinfo, mrc);
		if(0==info->flagthresLow) {
			info->thresLow  = mrcinfo.mean - mrcinfo.sd;
		}
		if(0==info->flagthresHigh) {
			info->thresHigh = mrcinfo.mean + mrcinfo.sd;
		}
		DEBUGPRINT2("%f %f\n", info->thresLow, info->thresHigh);
	} else {
		if(0==info->flagthresLow) {
			info->thresLow = mrc->HeaderAMin;
		}
		if(0==info->flagthresHigh) {
			info->thresHigh = mrc->HeaderAMax;
		}
	}

    if(info->Inverse) {
        img->HeaderAMax = info->thresLow;
        img->HeaderAMin = info->thresHigh;
    } else {
		DEBUGPRINT("Not Inverse\n");
        img->HeaderAMax = info->thresHigh;
        img->HeaderAMin = info->thresLow;
		DEBUGPRINT2("%f %f\n", img->HeaderAMax, img->HeaderAMin);
		DEBUGPRINT2("%f %f\n", info->thresHigh, info->thresLow);
    }
}
