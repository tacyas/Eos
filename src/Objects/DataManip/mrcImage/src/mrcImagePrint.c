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
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "lmrcImagePrint.h"
#include "../inc/mrcImage.h"
#include "genUtil.h"
#include "Memory.h"
#include "psFile.h"
#include "Contour.h"

void
mrcInfoPrint(FILE* fpt, mrcImage* mrc, mrcImageParaTypeInteger mode)
{
    int i;
	char ModeName[100];

    fprintf(fpt, "N            : (%10d, %10d, %10d)\n", mrc->HeaderN.x, mrc->HeaderN.y, mrc->HeaderN.z);
	switch(mrc->HeaderMode){
		case 0:{
			sprintf(ModeName, "%s", "mrcCharImage");
			break;
		}
		case 2:{
			sprintf(ModeName, "%s", "mrcFloatImage");
			break;
		}
		case 3:{
			sprintf(ModeName, "%s", "mrcComplexShortFT");
			break;
		}
		case 4:{
			sprintf(ModeName, "%s", "mrcComplexFloatFT");
			break;
		}
		case mrcShortImage:{
			sprintf(ModeName, "%s", "mrcShortImage");
			break;
		}
		case mrcUShortImage:{
			sprintf(ModeName, "%s", "mrcUShortImage");
			break;
		}
		case mrcFloatRadonImage:{
			sprintf(ModeName, "%s", "mrcFloatRadonImage");
			break;
		}
		case mrcFloatRadonFT:{
			sprintf(ModeName, "%s", "mrcFloatRadonFT");
			break;
		}
		case 101:{
			sprintf(ModeName, "%s", "mrcLongImage");
		}
		break;
		case 102:{
			sprintf(ModeName, "%s", "mrcDoubleImage");
		}
		break;
		case 103:{
			sprintf(ModeName, "%s", "mrcComplexLongFT");
		}
		break;
		case 104:{
			sprintf(ModeName, "%s", "mrcComplexDoubleFT");
		}
		break;
		case 1003:{
			sprintf(ModeName, "%s", "mrcComplexShortFFT");
		}
		break;
		case 1004:{
			sprintf(ModeName, "%s", "mrcComplexFloatFFT");
		}
		break;
		case 1103:{
			sprintf(ModeName, "%s", "mrcComplexLongFFT");
		}
		break;
		case 1104:{
			sprintf(ModeName, "%s", "mrcComplexDoubleFFT");
		}
		break;
		default:{
			sprintf(ModeName, "%s", "mrcNotSuppotedMode");
		}
		break;
	}
	fprintf(fpt, "Mode         :  %10d  %s         \n", mrc->HeaderMode, ModeName);
    fprintf(fpt, "StartN       : (%10d, %10d, %10d)\n", mrc->HeaderStartN.x, mrc->HeaderStartN.y, mrc->HeaderStartN.z);
    fprintf(fpt, "M            : (%10u, %10u, %10u)\n", mrc->HeaderM.x, mrc->HeaderM.y, mrc->HeaderM.z);
    fprintf(fpt, "Length       : (%10.3f, %10.3f, %10.3f)\n", mrc->HeaderLength.x, mrc->HeaderLength.y, mrc->HeaderLength.z);
    fprintf(fpt, "A,B,G        : (%10.2f, %10.2f, %10.2f)\n", mrc->HeaderAlpha, mrc->HeaderBeta, mrc->HeaderGamma);
    fprintf(fpt, "C,R,S        : (%10d, %10d, %10d)\n", mrc->HeaderMAPC, mrc->HeaderMAPR, mrc->HeaderMAPS);
    fprintf(fpt, "Min,Max,Mean : (%10.3g, %10.3g, %10.3g)\n", mrc->HeaderAMin, mrc->HeaderAMax,  mrc->HeaderAMean);
    fprintf(fpt, "ISPG         :  %10d\n", mrc->HeaderISPG);
    fprintf(fpt, "NSYMBT       :  %10d\n", mrc->HeaderNSYMBT);
    fprintf(fpt, "EXTRA        :  ");
    for(i=0; i<MRC_MAX_EXTRA; i++) {
        fprintf(fpt, "%2d: %-10.2g\t", i, mrc->HeaderEXTRA[i]);
    }
    fprintf(fpt, "\n");
    fprintf(fpt, "XORIGIN      : (%10.2g, %10.2g)\n", mrc->HeaderOriginX, mrc->HeaderOriginY);
    fprintf(fpt, "XORIGIN      : (%10.2g, %10.2g)\n", mrc->HeaderOriginX, mrc->HeaderOriginY);
    fprintf(fpt, "LABEL        :  %10d\n", mrc->HeaderLabelN);
    if(mrc->HeaderLabelN<=MRC_MAX_LABEL_N) {
        for(i=0; i<mrc->HeaderLabelN; i++) {
            fprintf(fpt, "%2d)%80s\n", i, mrc->HeaderLabel[i]);
        }
    }
	fprintf(fpt, "Tailer Number: %d\n", mrc->numTailer);
	switch(mode&0x10) {
		case 0x10: {
			for(i=0; i<mrc->numTailer; i++) {
				fprintf(fpt, "Tailer: ");
				fprintf(fpt, "%d ", i);
				fprintf(fpt, "%d ", mrc->Tailer[i].Cont.Mode);
				fprintf(fpt, "%c%c%c%c ", mrc->Tailer[i].Cont.EulerAngleMode[0],
										  mrc->Tailer[i].Cont.EulerAngleMode[1],
										  mrc->Tailer[i].Cont.EulerAngleMode[2],
										  mrc->Tailer[i].Cont.EulerAngleMode[3]);
				fprintf(fpt, "%15.6g %15.6g %15.6g\n", mrc->Tailer[i].Cont.Rot1*DEGREE,
											   		   mrc->Tailer[i].Cont.Rot2*DEGREE,
													   mrc->Tailer[i].Cont.Rot3*DEGREE);
			}
			break;
		}
		default: {
			for(i=0; i<mrc->numTailer; i++) {
				fprintf(fpt, "%d) \n", i);
				fprintf(fpt, "Mode %d\n", mrc->Tailer[i].Cont.Mode);
				fprintf(fpt, "EulerAngle Mode: %c%c%c%c\n", mrc->Tailer[i].Cont.EulerAngleMode[0],
															mrc->Tailer[i].Cont.EulerAngleMode[1],
															mrc->Tailer[i].Cont.EulerAngleMode[2],
															mrc->Tailer[i].Cont.EulerAngleMode[3]);
				fprintf(fpt, "%15.6g %15.6g %15.6g\n", mrc->Tailer[i].Cont.Rot1*DEGREE,
											   		   mrc->Tailer[i].Cont.Rot2*DEGREE,
													   mrc->Tailer[i].Cont.Rot3*DEGREE);
			}
			break;
		}
	}
}

void
mrcImagePSFilePrint(FILE* fpt, mrcImage* mrc, char* message, mrcImagePSFilePrintInfo info, long nContour, float* level, long mode)
{
	mrcImage tmpmrc;
    long ix, iy, iz, X, Y, Z;
	long nx, ny, nz;
	double lx, ly, lz;
    psFile ps;
    psImageInfo im;
    long scaleMode, i;
    double data;
    double xscale;
    char message0[MAX_STRING_LENGTH];
    char message1[MAX_STRING_LENGTH];
    char message2[MAX_STRING_LENGTH];
	time_t timer;
	struct tm* tmptr;
	double scale;
	double angle;

	/* Default Value Set */
	im = info.psInfo;
	/* Section */
	if('z'==info.whichSection) {
		nx = mrc->HeaderN.x;
		ny = mrc->HeaderN.y;
		nz = mrc->HeaderN.z;
		lx = mrc->HeaderLength.x;
		ly = mrc->HeaderLength.y;
		lz = mrc->HeaderLength.z;
	} else if('y'==info.whichSection) {
		nx = mrc->HeaderN.z;
		ny = mrc->HeaderN.x;
		nz = mrc->HeaderN.y;
		lx = mrc->HeaderLength.z;
		ly = mrc->HeaderLength.x;
		lz = mrc->HeaderLength.y;
		tmpmrc = *mrc;
		mrc->HeaderN.x = nx; 
		mrc->HeaderN.y = ny; 
		mrc->HeaderN.z = nz; 
		mrc->HeaderLength.x = lx; 
		mrc->HeaderLength.y = ly; 
		mrc->HeaderLength.z = lz; 
		mrcInit(mrc, NULL);
		if(IsImage(mrc, "", 0)) {
			for(ix=0; ix<nx; ix++) {
			for(iy=0; iy<ny; iy++) {
			for(iz=0; iz<nz; iz++) {
            	mrcPixelDataGet(&tmpmrc, 
					(float)iy, (float)iz, (float)ix, 
					&data, mrcPixelMag, mrcPixelHowNearest);
            	mrcPixelDataSet(mrc, 
					(float)ix, (float)iy, (float)iz, 
					data, mrcPixelMag);
				
			}
			}
			}
		} else if(IsFT(mrc, "", 0)) {
			for(ix=-nx/2.0; ix<nx/2.0; ix++) {
			for(iy=0.0;     iy<=ny/2.0; iy++) {
			for(iz=-nz/2.0; iz<nz/2.0; iz++) {
            	mrcPixelDataGet(&tmpmrc, 
					(float)iy, (float)iz, (float)ix, 
					&data, mrcPixelMag, mrcPixelHowNearest);
            	mrcPixelDataSet(mrc, 
					(float)ix, (float)iy, (float)iz, 
					data, mrcPixelMag);
				
			}
			}
			}
		} 
	} else if('x'==info.whichSection) {
		nx = mrc->HeaderN.y;
		ny = mrc->HeaderN.z;
		nz = mrc->HeaderN.x;
		lx = mrc->HeaderLength.y;
		ly = mrc->HeaderLength.z;
		lz = mrc->HeaderLength.x;
		tmpmrc = *mrc;
		mrc->HeaderN.x = nx; 
		mrc->HeaderN.y = ny; 
		mrc->HeaderN.z = nz; 
		mrc->HeaderLength.x = lx; 
		mrc->HeaderLength.y = ly; 
		mrc->HeaderLength.z = lz; 
		mrcInit(mrc, NULL);
		if(IsImage(mrc, "", 0)) {
			for(ix=0; ix<nx; ix++) {
			for(iy=0; iy<ny; iy++) {
			for(iz=0; iz<nz; iz++) {
            	mrcPixelDataGet(&tmpmrc, 
					(float)iz, (float)ix, (float)iy, 
					&data, mrcPixelMag, mrcPixelHowNearest);
            	mrcPixelDataSet(mrc, 
					(float)ix, (float)iy, (float)iz, 
					data, mrcPixelMag);
				
			}
			}
			}
		} else if(IsFT(mrc, "", 0)) {
			for(ix=-nx/2.0; ix<nx/2.0; ix++) {
			for(iy=-ny/2.0; iy<ny/2.0; iy++) {
			for(iz=0.0;     iz<=nz/2.0; iz++) {
            	mrcPixelDataGet(&tmpmrc, 
					(float)iz, (float)ix, (float)iy, 
					&data, mrcPixelMag, mrcPixelHowNearest);
            	mrcPixelDataSet(mrc, 
					(float)ix, (float)iy, (float)iz, 
					data, mrcPixelMag);
				
			}
			}
			}
		} 
	}

	scale = info.scale;
	info.untwistAngle = info.untwistAngle*lz;
	ps.fpt = fpt;
    psFileInit(&ps, 0);
    im.image     =(unsigned char*)memoryAllocate(sizeof(unsigned char*)*nx*ny, "in mrcImagePSFilePrint");
    im.floatImage=(float*)        memoryAllocate(sizeof(float*)*nx*ny,         "in mrcImagePSFilePrint");
    for(iz=0, Z = -mrc->HeaderN.z/2.0; iz<nz; iz++, Z++) {
        if(0!=(mrcImagePrintMode_ImageDensity&mode)||0!=(mrcImagePrintMode_ImageCircle&mode)) { 
			/* Set Image Density/Circle Data Array */
            if(!IsFT(mrc, "in mrcImagePSFilePrint", 0)) {
                for(ix=0; ix<nx; ix++) {
                    for(iy=0; iy<ny; iy++) {
                        mrcPixelDataGet(mrc, (float)ix, (float)iy, (float)iz, &data, mrcPixelMag, mrcPixelHowNearest);
                        if(mrc->HeaderAMin<=mrc->HeaderAMax) {
                            if(data>=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data<=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            im.image[ix+iy*nx] = (unsigned char)((data - mrc->HeaderAMin)/(mrc->HeaderAMax - mrc->HeaderAMin)*255.0);
                        } else { /* Inverse Image */
                            if(data<=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data>=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            im.image[ix+iy*nx] = (unsigned char)((mrc->HeaderAMin - data)/(mrc->HeaderAMin - mrc->HeaderAMax)*255.0);
                        }
                    }
                }
            } else {
                for(X=-mrc->HeaderN.x/2.0, ix=0; X<mrc->HeaderN.x/2.0; X++, ix++) {
                    for(Y=-mrc->HeaderN.y/2.0, iy=0; Y<mrc->HeaderN.y/2.0; Y++, iy++) {
                        mrcPixelDataGet(mrc, (float)X, (float)Y, (float)Z, &data, mrcPixelMag, mrcPixelHowNearest);
                        if(mrc->HeaderAMin<=mrc->HeaderAMax) {
                            if(data>=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data<=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            im.image[ix+iy*mrc->HeaderN.x] = (unsigned char)((data - mrc->HeaderAMin)/(mrc->HeaderAMax - mrc->HeaderAMin)*255.0);
                        } else { /* Inverse Image */
                            if(data<=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data>=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            im.image[ix+iy*mrc->HeaderN.x] = (unsigned char)((mrc->HeaderAMin - data)/(mrc->HeaderAMin - mrc->HeaderAMax)*255.0);
                        }
                    }
                }
            }
        }
        if((0!=(mrcImagePrintMode_Contour&mode))||(0!=(mrcImagePrintMode_Contour2&mode))) {
			im.contourLineColorChange = info.contourLineColorChange;
			im.contourLineWidthStart = info.contourLineWidthStart/scale;
			im.contourLineWidthStep  = info.contourLineWidthStep/scale;

            if(!IsFT(mrc, "in mrcImagePSFilePrint", 0)) {
                for(ix=0; ix<mrc->HeaderN.x; ix++) {
                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
                        mrcPixelDataGet(mrc, (float)ix, (float)iy, (float)iz, &data, mrcPixelMag, mrcPixelHowNearest);
                        im.floatImage[ix+iy*mrc->HeaderN.x] = (float)(data);
                    }
                }
            } else {
                for(X=-mrc->HeaderN.x/2.0, ix=0; X<mrc->HeaderN.x/2.0; X++, ix++) {
                    for(Y=-mrc->HeaderN.y/2.0, iy=0; Y<mrc->HeaderN.y/2.0; Y++, iy++) {
                        mrcPixelDataGet(mrc, (float)X, (float)Y, (float)Z, &data, mrcPixelMag, mrcPixelHowNearest);
                        im.floatImage[ix+iy*mrc->HeaderN.x] = (float)(data);
                    }
                }
            }
        }
        im.width  = mrc->HeaderN.x;
        im.height = mrc->HeaderN.y;
        im.bps = 8;

		sprintf(ps.info.label, "%ld", iz);
        psFilePageStart(&ps, 0);
        /* Set Scale Mode */
        if(IsFT(mrc, "in mrcImagePSFilePrint", 0)) {
            xscale = (1.0/(mrc->HeaderN.x*mrc->HeaderLength.x))/(1.0/(mrc->HeaderN.y*mrc->HeaderLength.y));
            scaleMode = 2;
        } else {
            xscale = mrc->HeaderLength.x/mrc->HeaderLength.y;
            scaleMode = 1;
        }
	
        im.scaleX     = 1.0;  im.scaleY     = 1.0;
        im.translateX = 20.0; im.translateY = 40.0;
        psFileImageSpaceSet(&ps, im, 0); /* point scale world */
            sprintf(message0, "Scale:%10.2f [mm/pixel] %10.2f [mm/A] Width/Height:%10.2f Section:%ld (%10.2f [A])", scale, scale/mrc->HeaderLength.x, xscale, iz, iz*mrc->HeaderLength.z);
			
			timer = time(NULL);
			tmptr = localtime(&timer);
            sprintf(message1, "Date:%s", asctime(tmptr));

            psFileString(&ps, message,  0, -20, 0);
            psFileString(&ps, message0, 0, -30, 0);
            psFileString(&ps, message1, 0, -40, 0);
            if(  0!=(mrcImagePrintMode_Contour&mode)
              || 0!=(mrcImagePrintMode_Contour2&mode)) {
				for(i=0; i<nContour; i++) {
					sprintf(message2+14*i, "%13.4e ", level[i]);
				}
            	psFileString(&ps, message2, 0, -50, 0);
			}
			if(info.centre) {
				/*  To adjust centre, strange values are added.  
					This is because origin of printer is unknown.
				*/ 
            	im.translateX = (297/sqrt(2) -35 - 30/72*25.4 - im.width *xscale*scale)/2.0/25.4*72;  
				im.translateY = (297         -16 - 50/72*25.4 - im.height       *scale)/2.0/25.4*72;
        		im.scaleX     = 1.0;  
				im.scaleY     = 1.0;
            	psFileImageSpaceSet(&ps, im, 0);
			} else {
            	im.translateX = 0.0;
				im.translateY = 0.0;
        		im.scaleX     = 1.0;  
				im.scaleY     = 1.0;
            	psFileImageSpaceSet(&ps, im, 0);
			}
	            im.scaleX = 72/25.4*xscale*scale; im.scaleY = 72/25.4*scale;
	            im.translateX = 0.0;              im.translateY = 0.0;
	            psFileImageSpaceSet(&ps, im, 0); /* mm world */
					/* Untwist World */
					angle = info.untwistAngle*iz;
					im.angle =  angle*DEGREE;
					/* Set Untwist World */
	            	im.scaleX = 1.0; im.scaleY = 1.0;
	            	im.translateX = 1.0*(
									-im.width /2.0*(+cos(angle))
									-im.height/2.0*(-sin(angle))
									+im.width/2.0);
	            	im.translateY = 1.0*(
									-im.width /2.0*(+sin(angle))
									-im.height/2.0*(+cos(angle))
									+im.height/2.0);
	            	psFileImageSpaceSet(&ps, im, 0);
	            	psFileImageSpaceRotateSet(&ps, im, 0); 
		                if(0!=(mrcImagePrintMode_ImageDensity&mode)) {
		                    psFileImage(&ps, im, scaleMode);
		                }
		                if(0!=(mrcImagePrintMode_ImageCircle&mode)) {
							im.CircleRadius = info.circleRadius;
		                    psFileImageByCircles(&ps, im, scaleMode);
		                }
		                if(0!=(mrcImagePrintMode_Contour&mode)) {
		                    im.nContour = nContour;
		                    im.contourLevel = (double*)memoryAllocate(sizeof(double)*im.nContour, "in mrcImagePrintPSFile");
		                    for(i=0; i<im.nContour; i++) {
		                        im.contourLevel[i] = level[i];
		                    }
		                    psFileContour(&ps, im, psContourMode_DifferentLineWidthContour);
		                }
		                if(0!=(mrcImagePrintMode_Contour2&mode)) {
		                    im.nContour = nContour;
		                    im.contourLevel = (double*)memoryAllocate(sizeof(double)*im.nContour, "in mrcImagePrintPSFile");
		                    for(i=0; i<im.nContour; i++) {
		                        im.contourLevel[i] = level[i];
		                    }
		                    psFileContour(&ps, im, psContourMode_SameLineWidthContour);
		                }
		
		                if(0!=(mrcImagePrintMode_Scale&mode)) {
		                    psFileImageScale(&ps, im, scaleMode);
		                }
		                if(0!=(mrcImagePrintMode_Centre&mode)) {
		                    psFileImageCentre(&ps, im, 0);
		                }
		
					/* Restore from Untwist World */
	            	psFileImageSpaceRotateRestore(&ps, im, 0); /* mm world */
	            	psFileImageSpaceRestore(&ps, im, 0); /* mm world */
	           	psFileImageSpaceRestore(&ps, im, 0); /* mm world */
            psFileImageSpaceRestore(&ps, im, 0);
        psFileImageSpaceRestore(&ps, im, 0);

        psFilePageEnd(&ps, 0);
    }
    psFileEnd(&ps);

	*mrc = tmpmrc;
}

void
mrcImageASCIIFilePrint(FILE* fpt, mrcImage* mrc, char* message, float scale, long nContour, float* level, long mode)
{
    long ix, iy, iz, X, Y, Z;
    double data;
    double xscale;

	xscale = 1.0;
    for(iz=0, Z = -mrc->HeaderN.z/2.0; iz<mrc->HeaderN.z; iz++, Z++) {
        fprintf(fpt, "%s\n", message);
        fprintf(fpt, "Scale:%10.2f XScale/YScale:%10.2f Section:%ld (%10.2f)\n", scale, xscale, iz, iz*mrc->HeaderLength.z);
        if(0!=(mrcImagePrintMode_ASCII_Amp&mode)) { 
			if(!IsFT(mrc, "in mrcImageASCIIFilePrint", 0)) {
                for(iy=mrc->HeaderN.y - 1; iy >= 0; iy--) {
					fprintf(fpt, "%10.2f|", iy*mrc->HeaderLength.y);
                    for(ix=0; ix<mrc->HeaderN.x; ix++) {
                        mrcPixelDataGet(mrc, (float)ix, (float)iy, (float)iz, &data, mrcPixelMag, mrcPixelHowNearest);
                        if(mrc->HeaderAMin<=mrc->HeaderAMax) {
                            if(data>=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data<=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%X", (unsigned char)((data - mrc->HeaderAMin)/(mrc->HeaderAMax - mrc->HeaderAMin)*15.0));
                        } else { /* Inverse Image */
                            if(data<=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data>=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%X", (unsigned char)((mrc->HeaderAMin - data)/(mrc->HeaderAMin - mrc->HeaderAMax)*15.0));
                        }
                    }
					fprintf(fpt, "|\n");
                }
            } else {
                for(Y=mrc->HeaderN.y/2 - 1; Y>=0.0; Y--) {
					fprintf(fpt, "%10.5f|", Y/mrc->HeaderLength.y/mrc->HeaderN.y);
                    for(X=-mrc->HeaderN.x/2.0; X<mrc->HeaderN.x/2.0; X++) {
                        mrcPixelDataGet(mrc, (float)X, (float)Y, (float)Z, &data, mrcPixelMag, mrcPixelHowNearest);
                        if(mrc->HeaderAMin<=mrc->HeaderAMax) {
                            if(data>=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data<=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%X", (unsigned char)((data - mrc->HeaderAMin)/(mrc->HeaderAMax - mrc->HeaderAMin)*15.0));
                        } else { /* Inverse Image */
                            if(data<=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data>=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%X", (unsigned char)((mrc->HeaderAMin - data)/(mrc->HeaderAMin - mrc->HeaderAMax)*15.0));
                        }
                    }
					fprintf(fpt, "|\n");
                }
            }
		}
        if(0!=(mrcImagePrintMode_ASCII_LogAmp&mode)) { 
			if(mrc->HeaderAMin == 0.0) {
				mrc->HeaderAMin = 1e-6;
			}
			if(mrc->HeaderAMax == 0.0) {
				mrc->HeaderAMax = 1e-6;
			}	
            if(!IsFT(mrc, "in mrcImageASCIIFilePrint", 0)) {
                for(iy=mrc->HeaderN.y - 1; iy >= 0; iy--) {
					fprintf(fpt, "%10.2f|", iy*mrc->HeaderLength.y);
                    for(ix=0; ix<mrc->HeaderN.x; ix++) {
                        mrcPixelDataGet(mrc, (float)ix, (float)iy, (float)iz, &data, mrcPixelMag, mrcPixelHowNearest);

                        if(mrc->HeaderAMin<=mrc->HeaderAMax) {
                            if(data>=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data<=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%1X", (unsigned char)(log10(data/mrc->HeaderAMin)/log10(mrc->HeaderAMax/mrc->HeaderAMin)*15.0));
                        } else { /* Inverse Image */
                            if(data<=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data>=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%1X", (unsigned char)(log10(mrc->HeaderAMin/data)/log10(mrc->HeaderAMin/mrc->HeaderAMax)*15.0));
                        }
                    }
					fprintf(fpt, "|\n");
                }
            } else {
                for(Y=mrc->HeaderN.y/2 - 1; Y>=0.0; Y--) {
					fprintf(fpt, "%10.5f|", Y/mrc->HeaderLength.y/mrc->HeaderN.y);
                    for(X=-mrc->HeaderN.x/2.0; X<mrc->HeaderN.x/2.0; X++) {
                        mrcPixelDataGet(mrc, (float)X, (float)Y, (float)Z, &data, mrcPixelMag, mrcPixelHowNearest);
                        if(mrc->HeaderAMin<=mrc->HeaderAMax) {
                            if(data>=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data<=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%1X", (unsigned char)(log10(data/mrc->HeaderAMin)/log10(mrc->HeaderAMax/mrc->HeaderAMin)*15.0));
                        } else { /* Inverse Image */
                            if(data<=mrc->HeaderAMax) {
                                data = mrc->HeaderAMax;
                            } else if(data>=mrc->HeaderAMin) {
                                data = mrc->HeaderAMin;
                            }
                            fprintf(fpt, "%1X", (unsigned char)(log10(mrc->HeaderAMin/data)/log10(mrc->HeaderAMin/mrc->HeaderAMax)*15.0));
                        }
                    }
					fprintf(fpt, "|\n");
                }
            }
		}		
        if(0!=(mrcImagePrintMode_ASCII_Phase&mode)) {
			if(mrc->HeaderAMin == 0.0) {
				mrc->HeaderAMin = 1e-6;
			}
			if(mrc->HeaderAMax == 0.0) {
				mrc->HeaderAMax = 1e-6;
			}	
            if(!IsFT(mrc, "in mrcImageASCIIFilePrint", 0)) {
				fprintf(fpt, "All phase of Image is zero!!\n");
            } else {
                for(Y=mrc->HeaderN.y/2 - 1; Y>=0.0; Y--) {
					fprintf(fpt, "%10.5f|", Y/mrc->HeaderLength.y/mrc->HeaderN.y);
                    for(X=-mrc->HeaderN.x/2.0; X<mrc->HeaderN.x/2.0; X++) {
                        mrcPixelDataGet(mrc, (float)X, (float)Y, (float)Z, &data, mrcPixelPhase, mrcPixelHowNearest);
						if(data<0) {
							data += (2*M_PI);
						}
                        fprintf(fpt, "%1X", (unsigned char)(data/(2*M_PI)*15.0));
                    }
					fprintf(fpt, "|\n");
                }
            }
		}	
		fprintf(fpt, "Section:%ld (%10.2f) End\n", iz, iz*mrc->HeaderLength.z);
    }
}
