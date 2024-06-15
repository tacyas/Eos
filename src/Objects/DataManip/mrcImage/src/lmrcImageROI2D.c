/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageROI2D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageROI2D 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageROI2D ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"
#include "./lmrcImageROI2D.h"

void
lmrcImageSingleROI(mrcImage* out, mrcImage* in, lmrcImageSingleROIInfo* linfo, int mode)
{
    mrcImageParaTypeReal  x,  y;
    mrcImageParaTypeReal sx, sy;
    mrcImageParaTypeReal vx, vxx, vxy, vy, vyx, vyy;
	double wx, wy, hx, hy;
    mrcImageParaTypeReal magH, magW;
    double data;

    switch(linfo->Shape) {
        case Rect: {
            linfo->centerx = (linfo->blx + linfo->trx)/2.0;
            linfo->centery = (linfo->bly + linfo->try)/2.0;
            if(!linfo->flagWidth) {
                linfo->width   = sqrt(SQR(linfo->brx - linfo->blx)
                                     +SQR(linfo->bry - linfo->bly)) + 1;
            } 
            if(!linfo->flagHeight) {
                linfo->height  = sqrt(SQR(linfo->tlx - linfo->blx)
                                     +SQR(linfo->tly - linfo->bly)) + 1;
            }
            break;
        }
        case TiltRect: {
            linfo->centerx = (linfo->blx + linfo->trx)/2.0;
            linfo->centery = (linfo->bly + linfo->try)/2.0;
			linfo->minx = MIN(MIN(MIN(linfo->brx, linfo->blx), linfo->trx), linfo->tlx) ;
			linfo->miny = MIN(MIN(MIN(linfo->bry, linfo->bly), linfo->try), linfo->tly) ;
			linfo->maxx = MAX(MAX(MAX(linfo->brx, linfo->blx), linfo->trx), linfo->tlx) ;
			linfo->maxy = MAX(MAX(MAX(linfo->bry, linfo->bly), linfo->try), linfo->tly);  
            if(!linfo->flagWidth) {
                linfo->width  = linfo->maxx - linfo->minx + 1;
            } 
            if(!linfo->flagHeight) {
                linfo->height = linfo->maxy - linfo->miny + 1;
			}
			break;
		}
        case Rect2: {
            break;
        }
        case Circle: {
            linfo->width   =  2*linfo->radius;
            linfo->height  =  2*linfo->radius;
            break;
        }
		case Line: {
			if(!linfo->flagWidth) {
				linfo->width = 1;	
			}
			linfo->centerx = (linfo->startx + linfo->endx)/2.0; 
			linfo->centery = (linfo->starty + linfo->endy)/2.0; 
			break;
		}
        default: {
            fprintf(stderr, "Not Supproted ROI Info: %d\n", linfo->Shape);
            exit(EXIT_FAILURE);
        }
    }


    switch(linfo->Shape) {
        case Rect:
        case TiltRect:
        case Rect2: 
		case Circle: {
			double w,h;
			if(linfo->Shape==Rect) {
            	vxx = linfo->brx - linfo->blx;
            	vxy = linfo->bry - linfo->bly;
            	vx  = sqrt(SQR(vxx) + SQR(vxy));
            	vxx = vxx/vx;
            	vxy = vxy/vx;
            	vyx = -vxy;
            	vyy =  vxx;
			} else {
				vxx = 1;
				vxy = 0;
				vyx = 0;
				vyy = 1;
			}
			if(1==linfo->flagRotation) {
				/*
					/wx\    /cos -sin\ /vxx\
				    |  | =  |        | |   |
					\wy/    \sin  cos/ \vxy/
				*/
				wx = cos(linfo->angle)*vxx - sin(linfo->angle)*vxy;
				wy = sin(linfo->angle)*vxx + cos(linfo->angle)*vxy;
				hx = -wy;
				hy =  wx;
			} else {
				wx = vxx;
				wy = vxy;
				hx = vyx;
				hy = vyy;
			}

			if(linfo->Shape==TiltRect) {
				w = sqrt(SQR(linfo->brx - linfo->blx) 
                        +SQR(linfo->bry - linfo->bly)) + 1;
                h = sqrt(SQR(linfo->tlx - linfo->blx)
                        +SQR(linfo->tly - linfo->bly)) + 1;
			} else {
				w = (linfo->width -1)/2.0;
				h = (linfo->height-1)/2.0;
				DEBUGPRINT2("Center   : %f %f\n",  linfo->centerx, linfo->centery);
				DEBUGPRINT2("WIDTH    : %f %f\n",  linfo->width,   linfo->height);
				DEBUGPRINT2("BLbefore : %f %f\n",  linfo->blx, linfo->bly);
            	linfo->blx   = linfo->centerx - w*wx - h*hx;
            	linfo->bly   = linfo->centery - w*wy - h*hy;
            	linfo->brx   = linfo->centerx + w*wx - h*hx;
            	linfo->bry   = linfo->centery + w*wy - h*hy;
            	linfo->trx   = linfo->centerx + w*wx + h*hx;
            	linfo->try   = linfo->centery + w*wy + h*hy;
            	linfo->tlx   = linfo->centerx - w*wx + h*hx;
            	linfo->tly   = linfo->centery - w*wy + h*hy;
				DEBUGPRINT2("BLafter: %f %f\n",  linfo->blx, linfo->bly);
			}
            break;
        }
		case Line: {
			double length;
			double length2;

			vxx = linfo->endx - linfo->startx;
			vxy = linfo->endy = linfo->startx;
			length   = sqrt(SQR(vxx)+SQR(vxy)); 
			vxx = vxx/length;
			vxy = vxy/length;
			if(1==linfo->flagRotation) {
				double vrotx;
				double vroty;

				vrotx = cos(linfo->angle)*vxx - sin(linfo->angle)*vxy;
				vroty = sin(linfo->angle)*vxx + cos(linfo->angle)*vxy;
				vxx = vrotx;
				vxy = vroty;
			}
			length2  = length/2.0; 
			linfo->startx = linfo->centerx - vxx*length2; 
			linfo->starty = linfo->centery - vxy*length2; 
			linfo->endx   = linfo->centerx + vxx*length2; 
			linfo->endy   = linfo->centery + vxy*length2; 
			break;
		}
		default: {
            fprintf(stderr, "Not Supproted ROI Info: %d\n", linfo->Shape);
            exit(EXIT_FAILURE);
			break;
		}
    }


	if(!(linfo->flagMagnifiedHeight) && linfo->flagLayerLine) {
		linfo->flagMagnifiedHeight = 1;	
		linfo->magnifiedHeight     = (linfo->truePitch/linfo->Ly)*linfo->dY;
	}

    out->Header = in->Header;

	switch(linfo->Shape) {
		TiltRect: {
			linfo->minx = MIN(MIN(MIN(linfo->brx, linfo->blx), linfo->trx), linfo->tlx) ;
			linfo->miny = MIN(MIN(MIN(linfo->bry, linfo->bly), linfo->try), linfo->tly) ;
			linfo->maxx = MAX(MAX(MAX(linfo->brx, linfo->blx), linfo->trx), linfo->tlx) ;
			linfo->maxy = MAX(MAX(MAX(linfo->bry, linfo->bly), linfo->try), linfo->tly);  
            if(!linfo->flagWidth) {
                linfo->width  = linfo->maxx - linfo->minx + 1;
            } 
            if(!linfo->flagHeight) {
                linfo->height = linfo->maxy - linfo->miny + 1;
			}
			break;
		}
		default: {
			break;
		}
	}

	switch(linfo->Shape) {
		default: {
			if(linfo->flagMagnifiedWidth) {
    			out->HeaderN.x = floor(linfo->magnifiedWidth + 0.5);
				if(linfo->flagMagnifiedHeight) {
					out->HeaderN.y = floor(linfo->magnifiedHeight + 0.5);
				} else {
    				out->HeaderN.y = floor(linfo->height*linfo->magnifiedWidth /linfo->width + 0.5);
				}
			} else {
				if(linfo->flagMagnifiedHeight) {
					out->HeaderN.x = floor(linfo->width *linfo->magnifiedHeight/linfo->height + 0.5);
					out->HeaderN.y = floor(linfo->magnifiedHeight + 0.5);
				} else {
    				out->HeaderN.x = floor(linfo->width  + 0.5);
    				out->HeaderN.y = floor(linfo->height + 0.5);
				}
			}
			magW = floor(linfo->width +0.5)/out->HeaderN.x;
			magH = floor(linfo->height+0.5)/out->HeaderN.y;
			break;
		}
	}

	out->HeaderLength.x = in->HeaderLength.x*magW;
	out->HeaderLength.y = in->HeaderLength.y*magH;
    out->HeaderMode = linfo->mode;
    mrcInit(out, NULL);
	DEBUGPRINT2("magW: %f magH: %f\n", magW, magH);
	vxx = wx*magW;	
	vxy = wy*magW;	
	vyx = hx*magH;
	vyy = hy*magH;	

    switch(linfo->Shape) {
        case Rect:
        case Rect2: {
            for(y=0; y<out->HeaderN.y; y++) {
            for(x=0; x<out->HeaderN.x; x++) {
            	sx = linfo->blx + vxx*x + vyx*y;
                sy = linfo->bly + vxy*x + vyy*y;
				if(1==linfo->flagNonPeriodic) {
					if(-0.5<=sx && sx<in->HeaderN.x-0.5
					 &&-0.5<=sy && sy<in->HeaderN.y-0.5) {
                    	mrcPixelDataGet(in,  sx, sy, 0.0, &data, mrcPixelRePart, mode);
					} else {
						data = 0.0;
					}
				} else {
                	mrcPixelDataGet(in,  sx, sy, 0.0, &data, mrcPixelRePart, mode);
				}	
                mrcPixelDataSet(out,  x,  y, 0.0,  data, mrcPixelRePart);
            }
            }
            break;
        }
        case TiltRect: {
			double sum, ave;
			double px, py, uxx, uxy, uyx, uyy, ux, uy;
			double t, s;
			int n;

			DEBUGPRINT4("br: %g %g bl: %g %g \n", linfo->brx, linfo->bry, linfo->blx, linfo->bly);
			uxx = linfo->brx - linfo->blx;
			uxy = linfo->bry - linfo->bly;
			ux = SQR(uxx)+SQR(uxy);
			DEBUGPRINT4("tl: %g %g bl: %g %g \n", linfo->tlx, linfo->tly, linfo->blx, linfo->bly);
			uyx = linfo->tlx - linfo->blx;
			uyy = linfo->tly - linfo->bly;
			uy = SQR(uyx)+SQR(uyy);

			sum = 0;
			n = 0;
            for(y=0; y<out->HeaderN.y; y++) {
            for(x=0; x<out->HeaderN.x; x++) {
            	sx = linfo->minx + x; 
                sy = linfo->miny + y;
				px = sx - linfo->blx; 
				py = sy - linfo->bly; 

				t = (px*uxx + py*uxy)/ux;
				s = (px*uyx + py*uyy)/uy;

				DEBUGPRINT4("bl: %g %g br: %g %g\n", linfo->blx, linfo->bly, linfo->brx, linfo->bry);
				DEBUGPRINT4("bl: %g %g tl: %g %g\n", linfo->blx, linfo->bly, linfo->tlx, linfo->tly);
				DEBUGPRINT4("ux: %g %g uy: %g %g\n", uxx, uxy, uyx, uyy);
				DEBUGPRINT4("px: %g py: %g t: %g s: %g\n", px, py, t, s);
				if(-0.5<=sx && sx<in->HeaderN.x-0.5
				&& -0.5<=sy && sy<in->HeaderN.y-0.5
				&& 0 <= t  && t <= 1 
				&& 0 <= s  && s <= 1 ) {
                	mrcPixelDataGet(in,  sx, sy, 0.0, &data, mrcPixelRePart, mode);
            		mrcPixelDataSet(out,  x,  y, 0.0,  data, mrcPixelRePart);
					sum += data;
					n++;
				}
            }
            }
			ave = sum/n;
			
            for(y=0; y<out->HeaderN.y; y++) {
            for(x=0; x<out->HeaderN.x; x++) {
            	sx = linfo->minx + x; 
                sy = linfo->miny + y;
				px = sx - linfo->blx; 
				py = sy - linfo->bly; 

				t = (px*uxx + py*uxy)/ux;
				s = (px*uyx + py*uyy)/uy;

				if(-0.5<=sx && sx<in->HeaderN.x-0.5
				&& -0.5<=sy && sy<in->HeaderN.y-0.5
				&& ( t < 0  || 1 < t  
				   ||s < 0  || 1 < s) ) {
            		mrcPixelDataSet(out,  x,  y, 0.0, ave, mrcPixelRePart);
				}
            }
            }

            break;
        }
        case Circle: {
            for(x=0; x<out->HeaderN.x; x++) {
                for(y=0; y<out->HeaderN.y; y++) {
                    sx = linfo->blx + x*vxx + y*vyx;
                    sy = linfo->bly + x*vxy + y*vyy;
                    if(SQR(sx-linfo->centerx)+SQR(sy-linfo->centery)<=SQR(linfo->radius)) {
                        mrcPixelDataGet(in,  sx, sy, 0.0, &data, mrcPixelRePart, mode);
                        mrcPixelDataSet(out,  x,  y, 0.0,  data, mrcPixelRePart);
                    } else {
                        data = 0.0;
                        mrcPixelDataSet(out,  x,  y, 0.0,  data, mrcPixelRePart);
                    }
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not Supproted ROI Info: %d\n", linfo->Shape);
            exit(EXIT_FAILURE);
        }
    }
}

void
lmrcImageROIsInformationGet(FILE* fpt, lmrcImageROIsInfo* linfo)
{
    char  s[1024];
    char* shape;
    int i;
    File f;

    f.fpt = fpt;
    linfo->numROI = fileLineNumberGet(&f, "#");
    linfo->ROI    = (lmrcImageSingleROIInfo*)memoryAllocate(sizeof(lmrcImageSingleROIInfo)*linfo->numROI, "in lmrcImageROIsInformationGet");

    fseek(fpt, 0L, SEEK_SET);

    for(i=0; NULL!=stringGetFromFile(s, "", fpt, stdout, 3); i++) {
        if(s[0] != '#') {
            linfo->ROI[i].FileName = stringGetNthWord(s, 1, " ,\t\n");
            shape = stringGetNthWord(s, 2, " ,\t\n");
            SSWITCH(shape)
                SCASE("Rect") {
                    linfo->ROI[i].Shape = Rect;
                    linfo->ROI[i].blx   = stringGetNthRealData(s, 3, " ,\t\n");;
                    linfo->ROI[i].bly   = stringGetNthRealData(s, 4, " ,\t\n");;
                    linfo->ROI[i].brx   = stringGetNthRealData(s, 5, " ,\t\n");;
                    linfo->ROI[i].bry   = stringGetNthRealData(s, 6, " ,\t\n");;
                    linfo->ROI[i].trx   = stringGetNthRealData(s, 7, " ,\t\n");;
                    linfo->ROI[i].try   = stringGetNthRealData(s, 8, " ,\t\n");;
                    linfo->ROI[i].tlx   = stringGetNthRealData(s, 9, " ,\t\n");;
                    linfo->ROI[i].tly   = stringGetNthRealData(s, 10, " ,\t\n");;
                    SBREAK;
                }
                SCASE("TiltRect") {
                    linfo->ROI[i].Shape = TiltRect;
                    linfo->ROI[i].blx   = stringGetNthRealData(s, 3, " ,\t\n");;
                    linfo->ROI[i].bly   = stringGetNthRealData(s, 4, " ,\t\n");;
                    linfo->ROI[i].brx   = stringGetNthRealData(s, 5, " ,\t\n");;
                    linfo->ROI[i].bry   = stringGetNthRealData(s, 6, " ,\t\n");;
                    linfo->ROI[i].trx   = stringGetNthRealData(s, 7, " ,\t\n");;
                    linfo->ROI[i].try   = stringGetNthRealData(s, 8, " ,\t\n");;
                    linfo->ROI[i].tlx   = stringGetNthRealData(s, 9, " ,\t\n");;
                    linfo->ROI[i].tly   = stringGetNthRealData(s, 10, " ,\t\n");;
                    SBREAK;
                }
                SCASE("Rect2") {
                    linfo->ROI[i].Shape = Rect2;
                    linfo->ROI[i].centerx = stringGetNthRealData(s, 3, " ,\t\n");;
                    linfo->ROI[i].centery = stringGetNthRealData(s, 4, " ,\t\n");;
                    linfo->ROI[i].width   = stringGetNthRealData(s, 5, " ,\t\n");;
                    linfo->ROI[i].height  = stringGetNthRealData(s, 6, " ,\t\n");;
                    SBREAK;
                }
                SCASE("Circle") {
                    linfo->ROI[i].Shape = Circle;
                    linfo->ROI[i].centerx = stringGetNthRealData(s, 3, " ,\t\n");;
                    linfo->ROI[i].centery = stringGetNthRealData(s, 4, " ,\t\n");;
                    linfo->ROI[i].radius  = stringGetNthRealData(s, 5, " ,\t\n");;
                    SBREAK;
                }
                SCASE("Line") {
                    linfo->ROI[i].Shape = Line;
                    linfo->ROI[i].startx = stringGetNthRealData(s, 3, " ,\t\n");;
                    linfo->ROI[i].starty = stringGetNthRealData(s, 4, " ,\t\n");;
                    linfo->ROI[i].endx = stringGetNthRealData(s, 5, " ,\t\n");;
                    linfo->ROI[i].endy = stringGetNthRealData(s, 6, " ,\t\n");;
                    SBREAK;
                }
                SDEFAULT {
                    fprintf(stderr, "Not Supproted ROI Info: %s\n", s);
                    exit(EXIT_FAILURE);
                }
            SSWITCHEND;
        } else {
            i--;
        }
    }
}

void
lmrcImageROIsUsage(FILE* fpt)
{
	fprintf(stderr, "Shape: OutFileName Rect       blx bly brx bry trx try tlx tly\n");
	fprintf(stderr, "Shape: OutFileName TiltRect   blx bly brx bry trx try tlx tly\n");
	fprintf(stderr, "Shape: OutFileName Rect2      centerx centery width height \n");
	fprintf(stderr, "Shape: OutFileName Circle     centerx centery radius \n");
	fprintf(stderr, "Shape: OutFileName Line       startx starty endx endy\n");
}
