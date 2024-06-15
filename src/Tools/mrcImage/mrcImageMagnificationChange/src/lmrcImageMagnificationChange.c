/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMagnificationChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMagnificationChange
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMagnificationChange ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

/* type definition */
typedef struct mrcImageROIInfo {
    float blx;
    float bly;
    float brx;
    float bry;
    float trx;
    float try;
    float tlx;
    float tly;
    
    long flagWidthBeforeExpansion;
    float WidthBeforeExpansion;
    
    long flagHeightBeforeExpansion;
    float HeightBeforeExpansion;
    
    long flagAngle;
    float Angle;
    
    long flagWidthAfterExpansion;
    float WidthAfterExpansion;
    
    long flagHeightAfterExpansion;
    float HeightAfterExpansion;
    
    long flagmode;
    long mode;
    
} mrcImageROInotChangeHeaderLengthInfo;

/* prototype */
extern double bilinearInterpolation(double* image,
                       unsigned long nx, unsigned long ny,
                       double x, double y);

extern double cubicConvolutionInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y);
extern double polyNominalInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y);
extern void polyInitMatrix(double matrix[6][6], int m, int n);
extern void polyInitVector(double vec[6], int m, int n, double* image, int nx, int ny);
extern int polySolveMatrix(double matrix[6][6], double vec[6], double coefficient[6]);
extern void lmrcImageROInotChangeHeaderLength(mrcImage* out, mrcImage* in, mrcImageROInotChangeHeaderLengthInfo* info);


void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageMagnificationChangeInfo info;
/* variables */
	mrcImage in;
	mrcImage out;
	mrcImage tmpin;
	mrcImage tmpout;
	mrcImageROInotChangeHeaderLengthInfo roiinfo;
	mrcRefHeader header;
	int z;
  
/* initialization  */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in, info.In, "main routine", 0);
	roiinfo.blx = roiinfo.tlx = 0;
	roiinfo.brx = roiinfo.trx = in.HeaderN.x - 1 ;
	roiinfo.bly = roiinfo.bry = 0;
	roiinfo.tly = roiinfo.try = in.HeaderN.y - 1 ;
	roiinfo.flagWidthBeforeExpansion = 0;
	roiinfo.flagHeightBeforeExpansion = 0;
	roiinfo.flagAngle = 0;
	if (info.mode%16==0){
	  roiinfo.flagWidthAfterExpansion = 1;
	  roiinfo.WidthAfterExpansion = floor(in.HeaderN.x * info.Ratio +0.5);
	}else{
	  roiinfo.flagWidthAfterExpansion = 1;
	  roiinfo.WidthAfterExpansion = in.HeaderN.x;
	}
	roiinfo.flagHeightAfterExpansion = 1;
	roiinfo.HeightAfterExpansion = floor(in.HeaderN.y * info.Ratio +0.5);
	roiinfo.mode = 2;

/* begin */
	if (info.mode/16){
	  out.Header=in.Header;
	  out.HeaderN.x=roiinfo.WidthAfterExpansion;
	  out.HeaderN.y=roiinfo.HeightAfterExpansion;
	  mrcInit(&out,NULL);
	  lmrcRefHeaderGet(&header ,&in);
	  lmrcRefHeaderSet(&out ,&header);	
	  for (z=1 ;z<in.HeaderN.z ;z++){
	    lmrc3DZ1ImgGet(&tmpin ,&in ,z);
	    lmrcImageROInotChangeHeaderLength(&tmpout ,&tmpin ,&roiinfo);
	    lmrc3DZ1ImgPut(&out ,&tmpout ,z);
	    mrcImageFree(&tmpin ,0);
	    mrcImageFree(&tmpout ,0);
	  }
	} else {
	  lmrcImageROInotChangeHeaderLength(&out ,&in ,&roiinfo);
	}
	mrcFileWrite(&out, info.Out, "main routine", 0);
       	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"---- mode ----\n");
fprintf(stdout,"0:Both axis\n");
fprintf(stdout,"1:y axis only\n");
fprintf(stdout,"+16:ref image\n");
}

void
lmrcImageROInotChangeHeaderLength(mrcImage* out, mrcImage* in, mrcImageROInotChangeHeaderLengthInfo* info)
{
    double* tmpImage;
    int ix, iy;
    double xdx, xdy;
    double ydx, ydy;
    double x, y;
	double cx, cy;    				/* Centre of source image */
	double dwdx, dwdy, dhdx, dhdy;  /* Differentiation of source image */
	double tdwdx, tdwdy, tdhdx, tdhdy;  /* Temporaty differentiation of source image */
	double angle;
    double width, height; 			/* Size of source image */ 
    double max, min, mean;
	double data;

	width  = sqrt(SQR(info->brx - info->blx) + SQR(info->bry - info->bly));
	height = sqrt(SQR(info->tlx - info->blx) + SQR(info->tly - info->bly));
	if(width<0.5 || height<0.5) {
		fprintf(stderr, "ROI Area is zero(%f, %f)\n", width, height);
		exit(EXIT_FAILURE);
	}
	if(info->flagWidthBeforeExpansion || info->flagHeightBeforeExpansion) {
		cx = (info->blx + info->trx)/2.0;
		cy = (info->bly + info->try)/2.0;
		dwdx = (info->brx - info->blx)/width;
		dwdy = (info->bry - info->bly)/width;
		dhdx = (info->tlx - info->blx)/height;
		dhdy = (info->tly - info->bly)/height;
		if(info->flagAngle) {
			angle = info->Angle*DEGREE;
			tdwdx = cos(angle)*dwdx - sin(angle)*dwdy;
			tdwdy = sin(angle)*dwdx + cos(angle)*dwdy;
			dwdx = tdwdx;
			dwdy = tdwdy;
			tdhdx = cos(angle)*dhdx - sin(angle)*dhdy;
			tdhdy = sin(angle)*dhdx + cos(angle)*dhdy;
			dhdx = tdhdx;
			dhdy = tdhdy;
		}
		if(info->flagWidthBeforeExpansion) {
			width = info->WidthBeforeExpansion;
		} 
		if(info->flagHeightBeforeExpansion) {
			height = info->HeightBeforeExpansion;
		} 
		info->blx = cx - dwdx*width/2.0 - dhdx*height/2.0;
		info->bly = cy - dwdy*width/2.0 - dhdy*height/2.0;
		info->brx = cx + dwdx*width/2.0 - dhdx*height/2.0;
		info->bry = cy + dwdy*width/2.0 - dhdy*height/2.0;
		info->trx = cx + dwdx*width/2.0 + dhdx*height/2.0;
		info->try = cy + dwdy*width/2.0 + dhdy*height/2.0;
		info->tlx = cx - dwdx*width/2.0 + dhdx*height/2.0;
		info->tly = cy - dwdy*width/2.0 + dhdy*height/2.0;
	}

    /* Definition of Expansion Rate */
    switch(info->flagHeightAfterExpansion) {
		case 0:
			switch(info->flagWidthAfterExpansion) {
				case 0:
					info->HeightAfterExpansion = floor(height+1.0);
                    info->WidthAfterExpansion  = floor(width +1.0);
					break;
				case 1:
					info->HeightAfterExpansion = floor((height+1.0)*info->WidthAfterExpansion/(width+1.0));
					info->WidthAfterExpansion  = info->WidthAfterExpansion;
					break;
				default:
					fprintf(stderr, "Not Supported flag: flagWidthAfterExpansion\n");
					exit(EXIT_FAILURE);
					break;
			}
			break;
		case 1:	
			switch(info->flagWidthAfterExpansion) {
				case 0:
					info->HeightAfterExpansion = info->HeightAfterExpansion;
					info->WidthAfterExpansion  = floor((width+1.0)*info->HeightAfterExpansion/(height+1.0));
					break;
               case 1:
					info->HeightAfterExpansion = info->HeightAfterExpansion;
					info->WidthAfterExpansion  = info->WidthAfterExpansion;
					break;
				default:
					fprintf(stderr, "Not Supported flag: flagWidthAfterExpansion\n");
					exit(EXIT_FAILURE);
					break;
			}
			break;
		default:
			fprintf(stderr, "Not Supported flag: flagHeightAfterExpansion\n");
			exit(EXIT_FAILURE);
			break;
	}

	out->Header = in->Header;
    out->HeaderN.x = info->WidthAfterExpansion;
    out->HeaderN.y = info->HeightAfterExpansion;
    out->HeaderN.z = 1;
    out->HeaderMode = mrcFloatImage;
    mrcInit(out, NULL);

    xdx = (info->brx - info->blx)/(info->WidthAfterExpansion -1.0);
    xdy = (info->bry - info->bly)/(info->WidthAfterExpansion -1.0);
    ydx = (info->tlx - info->blx)/(info->HeightAfterExpansion-1.0);
    ydy = (info->tly - info->bly)/(info->HeightAfterExpansion-1.0);

	switch(info->mode) {
		case 0: {
			break;
		}
		default: {
    		if(NULL==(tmpImage = (double*)malloc(sizeof(double)*in->HeaderN.x*in->HeaderN.y*in->HeaderN.z))) {
		        fprintf(stderr, "Not Allocate Memory in lmrcImageROI\n");
				exit(EXIT_FAILURE);
    		}
		    for(ix=0; ix<in->HeaderN.x; ix++) {
       			for(iy=0; iy<in->HeaderN.y; iy++) {
       			    mrcPixelDataGet(in,
						   (mrcImageParaTypeReal)ix, 
						   (mrcImageParaTypeReal)iy, 
						   0.0, 
						   &(tmpImage[ix+iy*in->HeaderN.x]), 
						   mrcPixelRePart, mrcPixelHowNearest);
        		}
    		}
			break;
		}
	}
	DEBUGPRINT2("%ld %ld\n", in->HeaderN.x, in->HeaderN.y);
	DEBUGPRINT2("%f %f\n", info->HeightAfterExpansion, info->HeightBeforeExpansion);
	DEBUGPRINT2("%f %f\n", width, height);
	DEBUGPRINT1("Mode: %d\n", info->mode);
	DEBUGPRINT1("out->HeaderMode: %d\n", out->HeaderMode);
    switch(info->mode) {
        case 0: {
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					mrcPixelDataGet(in, 
									(mrcImageParaTypeReal)x, 
									(mrcImageParaTypeReal)y, 
									0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
									data,
									mrcPixelRePart);
                }
            }
            break;
        }
        case 1: {
			DEBUGPRINT("LinearInterpolation\n");
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
                        			bilinearInterpolation(tmpImage,
                                		in->HeaderN.x, in->HeaderN.y,
										x, y),
									mrcPixelRePart);
                }
            }
            break;
        }
        case 2: {
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					DEBUGPRINT2("%d %d\n", ix, iy);
					DEBUGPRINT2("%f %f\n", x, y);
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
                        			cubicConvolutionInterpolation(tmpImage, 
                                		in->HeaderN.x, in->HeaderN.y,
                                		x, y),
									mrcPixelRePart);
                }
            }
            break;
        }
        case 3: {
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
                        			polyNominalInterpolation(tmpImage, 
                                		in->HeaderN.x, in->HeaderN.y,
                                		x, y),
									mrcPixelRePart);
                }
            }
            break;                              
        }
        default: {
            fprintf(stderr, "Not Supported Mode : %ld\n", info->mode);
            break;
        }
    }
	DEBUGPRINT("End lmrcImageROI\n");
	mrcStatDataSet(out, 0);
}

double 
bilinearInterpolation(double* image,
                       unsigned long nx, unsigned long ny,
                       double x, double y)
{
    double dat;

    dat = 0.0;
    dat += ((1-(x-(int)x))*(1-(y-(int)y))*image[(int)x   + nx*((int)y  )]);
    dat += ((1-(x-(int)x))*(   y-(int)y) *image[(int)x   + nx*((int)y+1)]);
    dat += (   (x-(int)x) *(1-(y-(int)y))*image[(int)x+1 + nx*((int)y  )]);
    dat += (   (x-(int)x) *(   y-(int)y) *image[(int)x+1 + nx*((int)y+1)]);
    return(dat);
}

double
cubicConvolutionInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y)
{
    double dat;
    long int xl, yl;
    long int xmin, xmax, ymin, ymax;
    double dx, dy;


    if((int)(x-3.0)<0) {
        xmin = 0;
    } else {
        xmin = (int)(x-3.0);
    }
    if((int)(x+3.0)>nx-1) {
        xmax = nx-1;
    } else {
        xmax = (int)(x+3.0);
    }

    if((int)(y-3.0)<0) {
        ymin = 0;
    } else {
        ymin = (int)(y-3.0);
    }
    if((int)(y+3.0)>ny-1) {
        ymax = ny-1;
    } else {
        ymax = (int)(y+3.0);
    }

    dat = 0.0;
    for(xl=xmin; xl<=xmax; xl++) {
        for(yl=ymin; yl<=ymax; yl++) {
            dx = fabs(x-xl);
            dy = fabs(y-yl);
            if(dx>=2.0||dy>=2.0) {
                dat += 0.0;
            } else if(dx>=1.0&&dy>=1.0) {
                dat += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
                       *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
                       *(image[xl+yl*nx]));
            } else if(dx>=1.0&&dy<1.0) {
                dat += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
                       *(1.0-2.0*dy*dy+dy*dy*dy)
                       *(image[xl+yl*nx]));
            } else if(dx<1.0&&dy>=1.0) {
                dat += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
                       *(1.0-2.0*dx*dx+dx*dx*dx)
                       *(image[xl+yl*nx]));
            } else if(dx<1.0&&dy<1.0) {
                dat += ((1.0-2.0*dx*dx+dx*dx*dx)
                       *(1.0-2.0*dy*dy+dy*dy*dy)
                       *(image[xl+yl*nx]));
            } else {
                fprintf(stderr, "That's stupid!\n!");
            }
        }
    }
    return(dat);
}


double
polyNominalInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y)
{
    int m, n;
    static double coefficient[6];
    static double matrix[6][6];
    static double vec[6];

    m = (int)floor(x);
    n = (int)floor(y);
    polyInitMatrix(matrix, m, n);
    polyInitVector(vec, m, n, image, nx, ny);
    if(polySolveMatrix(matrix, vec, coefficient)) {
        return coefficient[0]*x*x + coefficient[1]*x*y
             + coefficient[2]*y*y + coefficient[3]*x
             + coefficient[4]*y   + coefficient[5];
    } else {
        fprintf(stderr, "trace = 0 at (%f, %f)\n", x, y);
        return bilinearInterpolation(image, nx, ny,x, y);
    }
} 

void 
polyInitMatrix(double matrix[6][6], int m, int n)
{
    int  i,j;

    for(i=0; i<6; i++) {
        for(j=0; j<6; j++) {
            matrix[i][j] = 0.0;
        }
    }
    i=m-1;
    for(j=n;j<=n+1;j++) {
        matrix[0][0] += (double)(i*i*i*i);
        matrix[0][1] += (double)(i*i*i*j);
        matrix[0][2] += (double)(i*i*j*j);
        matrix[0][3] += (double)(i*i*i);
        matrix[0][4] += (double)(i*i*j);
        matrix[0][5] += (double)(i*i);
        matrix[1][1] += (double)(i*i*j*j);
        matrix[1][2] += (double)(i*j*j*j);
        matrix[1][3] += (double)(i*i*j);
        matrix[1][4] += (double)(i*j*j);
        matrix[1][5] += (double)(i*j);
        matrix[2][2] += (double)(j*j*j*j);
        matrix[2][3] += (double)(i*j*j);
        matrix[2][4] += (double)(j*j*j);
        matrix[2][5] += (double)(j*j);
        matrix[3][3] += (double)(i*i);
        matrix[3][4] += (double)(i*j);
        matrix[3][5] += (double)i;
        matrix[4][4] += (double)(j*j);
        matrix[4][5] += (double)j;
        matrix[5][5] += 1.0;
    }
    for(i=m;i<=m+1;i++) {
        for(j=n-1;j<=n+2;j++) {
            matrix[0][0] += (double)(i*i*i*i);
            matrix[0][1] += (double)(i*i*i*j);
            matrix[0][2] += (double)(i*i*j*j);
            matrix[0][3] += (double)(i*i*i);
            matrix[0][4] += (double)(i*i*j);
            matrix[0][5] += (double)(i*i);
            matrix[1][1] += (double)(i*i*j*j);
            matrix[1][2] += (double)(i*j*j*j);
            matrix[1][3] += (double)(i*i*j);
            matrix[1][4] += (double)(i*j*j);
            matrix[1][5] += (double)(i*j);
            matrix[2][2] += (double)(j*j*j*j);
            matrix[2][3] += (double)(i*j*j);
            matrix[2][4] += (double)(j*j*j);
            matrix[2][5] += (double)(j*j);
            matrix[3][3] += (double)(i*i);
            matrix[3][4] += (double)(i*j);
            matrix[3][5] += (double)i;
            matrix[4][4] += (double)(j*j);
            matrix[4][5] += (double)j;
            matrix[5][5] += 1.0;
        }
    }
    i=m+2;
    for(j=n;j<=n+1;j++) {
        matrix[0][0] += (double)(i*i*i*i);
        matrix[0][1] += (double)(i*i*i*j);
        matrix[0][2] += (double)(i*i*j*j);
        matrix[0][3] += (double)(i*i*i);
        matrix[0][4] += (double)(i*i*j);
        matrix[0][5] += (double)(i*i);
        matrix[1][1] += (double)(i*i*j*j);
        matrix[1][2] += (double)(i*j*j*j);
        matrix[1][3] += (double)(i*i*j);
        matrix[1][4] += (double)(i*j*j);
        matrix[1][5] += (double)(i*j);
        matrix[2][2] += (double)(j*j*j*j);
        matrix[2][3] += (double)(i*j*j);
        matrix[2][4] += (double)(j*j*j);
        matrix[2][5] += (double)(j*j);
        matrix[3][3] += (double)(i*i);
        matrix[3][4] += (double)(i*j);
        matrix[3][5] += (double)i;
        matrix[4][4] += (double)(j*j);
        matrix[4][5] += (double)j;
        matrix[5][5] += 1.0;
    }
    for(i=1;i<6;i++) {
        for(j=0;j<i;j++) {
            matrix[i][j] = matrix[j][i];
        }
    }
}

void 
polyInitVector(double vec[6], int m, int n, double* image, int nx, int ny)
{
    int  i,j;
    int  value;
    int  offset;
    char buf_upper,buf_lower;

    for(i=0;i<6;i++) {
         vec[i] = 0.0;
    }
    i=m-1;
    for(j=n;j<=n+1;j++) {
         value = image[i+j*nx];
         vec[0] += (double)(i*i*value);
         vec[1] += (double)(i*j*value);
         vec[2] += (double)(j*j*value);
         vec[3] += (double)(i*value);
         vec[4] += (double)(j*value);
         vec[5] += (double)(value);
    }
    for(i=m;i<=m+1;i++) {
        for(j=n-1;j<=n+2;j++) {
            value = image[i+j*nx];
            vec[0] += (double)(i*i*value);
            vec[1] += (double)(i*j*value);
            vec[2] += (double)(j*j*value);
            vec[3] += (double)(i*value);
            vec[4] += (double)(j*value);
            vec[5] += (double)(value);
        }
    }
    i=m+2;
    for(j=n;j<=n+1;j++) {
        value = image[i+j*nx];
        vec[0] += (double)(i*i*value);
        vec[1] += (double)(i*j*value);
        vec[2] += (double)(j*j*value);
        vec[3] += (double)(i*value);
        vec[4] += (double)(j*value);
        vec[5] += (double)(value);
    }
}


int 
polySolveMatrix(double matrix[6][6], double vec[6], double coefficient[6])
{
    int  i, j, k;

    for(i=0;i<6;i++) {
        if(matrix[i][i]==0) {
            return 0;
        }
        for(j=i+1;j<6;j++) {
             matrix[i][j] /= matrix[i][i];
        }
        vec[i] /= matrix[i][i];
        for(k=0;k<6;k++) {
            if(k!=i) {
                for(j=i+1;j<6;j++) {
                       matrix[k][j] -= matrix[k][i]*matrix[i][j];
                }
                vec[k] -= matrix[k][i]*vec[i];
            }
        }
    }
    for(i=0;i<6;i++) {
        coefficient[i] = vec[i];
    }
    return 1;
}
