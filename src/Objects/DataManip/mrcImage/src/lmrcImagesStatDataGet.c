/*
# lmrcImagesStatDataGet.c  1.1
# The latest update : 01/23/97 at 10:36:47
#
#@(#) lmrcImagesStatDataGet ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : lmrcImagesStatDataGet 
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)lmrcImagesStatDataGet ver1.1; Date:97/01/23 @(#)";
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lmrcImagesStatDataGet.h"

static int compare_double(const void* a, const void* b)
{
    return *(double*)a - *(double*)b;
}

void
lmrcImagesStatDataGet(lmrcImagesStatDataGetInfo* linfo, mrcImage* srcs, int n, long mode)
{
	int i;
	mrcImageParaTypeReal x, y, z;
	double data;
	double avg, sqravg;
	
	linfo->numImage = n;

	linfo->Avg.Header = srcs[0].Header;
	mrcInit(&(linfo->Avg), NULL);

    if(linfo->flagMedian || linfo->flagTrimmedAvg) {
        double* dd;
        int icen, flag;
        int imin, imax;
        int nn;
        icen = n/2;
        flag = n%2;
        imin = linfo->TrimmedRange*n;
        imax = n -1 - linfo->TrimmedRange*n;
        nn = imax - imin + 1;
        dd = memoryAllocate(sizeof(double)*n, "in lmrcImagesStatDataGet");

	    linfo->Median.Header = srcs[0].Header;
	    mrcInit(&(linfo->Median), NULL);
	    linfo->TrimmedAvg.Header = srcs[0].Header;
	    mrcInit(&(linfo->TrimmedAvg), NULL);

		for(x=0; x<linfo->Median.HeaderN.x; x++) {
			for(y=0; y<linfo->Median.HeaderN.y; y++) {
				for(z=0; z<linfo->Median.HeaderN.z; z++) {
                    for(i=0; i<n; i++) {
					    mrcPixelDataGet(&srcs[i], x, y, z, &dd[i], mrcPixelRePart, mrcPixelHowNearest);
				    }
                    qsort(dd, n, sizeof(double), compare_double);
                    if(flag) {
                        data = dd[icen];
                    } else {
                        data = (dd[icen-1] + dd[icen])/2.0;
                    }
					mrcPixelDataSet(&linfo->Median, x, y, z, data, mrcPixelRePart);
                    data = 0;
                    for(i=imin; i<=imax; i++) {
                       data+=dd[i]; 
                    }
                    if(nn>0) {
                        data /= nn;
                    } else {
                        fprintf(stderr, "Cannot calculate trimmed average due to too small number\n");
                        exit(EXIT_FAILURE);
                    }
					mrcPixelDataSet(&linfo->TrimmedAvg, x, y, z, data, mrcPixelRePart);
                }
			}
		}
        memoryFree(dd);
    }

	linfo->SQRAvg.Header = srcs[0].Header;
	mrcInit(&(linfo->SQRAvg), NULL);

	if(linfo->flagVar) {
		DEBUGPRINT("Variance\n");
		if(linfo->numImage<2) {
			fprintf(stderr, "Cannot Calculate Variance: %d\n", linfo->numImage);
			exit(EXIT_FAILURE);
		}
		linfo->Var.Header = srcs[0].Header;
		mrcInit(&(linfo->Var), NULL);
	}
	if(linfo->flagSD) {
		if(linfo->numImage<2) {
			fprintf(stderr, "Cannot Calculate SD, %d\n", linfo->numImage);
			exit(EXIT_FAILURE);
		}
		linfo->SD.Header = srcs[0].Header;
		mrcInit(&(linfo->SD), NULL);
	}
	if(linfo->flagSE) {
		if(linfo->numImage<2) {
			fprintf(stderr, "Cannot Calculate SE ,%d\n", linfo->numImage);
			exit(EXIT_FAILURE);
		}
		linfo->SE.Header = srcs[0].Header;
		mrcInit(&(linfo->SE), NULL);
	}
	if(linfo->flagSN) {
		if(linfo->numImage<2) {
			fprintf(stderr, "Cannot Calculate t-value, %d\n", linfo->numImage);
			exit(EXIT_FAILURE);
		}
		linfo->SN.Header = srcs[0].Header;
		mrcInit(&(linfo->SN), NULL);
	}
	if(linfo->flagt) {
		if(linfo->numImage<3) {
			fprintf(stderr, "Cannot Calculate t-value, %d\n", linfo->numImage);
			exit(EXIT_FAILURE);
		}
		linfo->t.Header = srcs[0].Header;
		mrcInit(&(linfo->t), NULL);
	}

	for(x=0; x<linfo->Avg.HeaderN.x; x++) {
		for(y=0; y<linfo->Avg.HeaderN.y; y++) {
			for(z=0; z<linfo->Avg.HeaderN.z; z++) {
				mrcPixelDataSet(&linfo->Avg,    x, y, z, 0.0, mrcPixelRePart);
				mrcPixelDataSet(&linfo->SQRAvg, x, y, z, 0.0, mrcPixelRePart);
			}
		}
	}

	for(x=0; x<linfo->Avg.HeaderN.x; x++) {
		for(y=0; y<linfo->Avg.HeaderN.y; y++) {
			for(z=0; z<linfo->Avg.HeaderN.z; z++) {
				mrcPixelDataSet(&linfo->Avg,    x, y, z, 0.0, mrcPixelRePart);
				mrcPixelDataSet(&linfo->SQRAvg, x, y, z, 0.0, mrcPixelRePart);
			}
		}
	}

	for(i=0; i<n; i++) {
		if(  srcs[i].HeaderN.x!=linfo->Avg.HeaderN.x
		  || srcs[i].HeaderN.y!=linfo->Avg.HeaderN.y
		  || srcs[i].HeaderN.z!=linfo->Avg.HeaderN.z) {
			fprintf(stderr, "Image Size is different (%d): in lmrcImagesStatDataGet\n", i);
		}
		for(x=0; x<linfo->Avg.HeaderN.x; x++) {
			for(y=0; y<linfo->Avg.HeaderN.y; y++) {
				for(z=0; z<linfo->Avg.HeaderN.z; z++) {
					mrcPixelDataGet(&(srcs[i]),     x, y, z, &data,   mrcPixelRePart, mrcPixelHowNearest);

					mrcPixelDataGet(&linfo->Avg,    x, y, z, &avg,    mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&linfo->SQRAvg, x, y, z, &sqravg, mrcPixelRePart, mrcPixelHowNearest);

					mrcPixelDataSet(&linfo->Avg,    x, y, z, avg+data,         mrcPixelRePart);
					mrcPixelDataSet(&linfo->SQRAvg, x, y, z, sqravg+SQR(data), mrcPixelRePart);
				}
			}
		}	
	}

	for(x=0; x<linfo->Avg.HeaderN.x; x++) {
		for(y=0; y<linfo->Avg.HeaderN.y; y++) {
			for(z=0; z<linfo->Avg.HeaderN.z; z++) {
				mrcPixelDataGet(&linfo->Avg,    x, y, z, &avg,    mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&linfo->SQRAvg, x, y, z, &sqravg, mrcPixelRePart, mrcPixelHowNearest);

				mrcPixelDataSet(&linfo->Avg,    x, y, z, avg/n,    mrcPixelRePart);
				mrcPixelDataSet(&linfo->SQRAvg, x, y, z, sqravg/n, mrcPixelRePart);
			}
		}
	}	

	if(linfo->flagVar) {
		for(x=0; x<linfo->Avg.HeaderN.x; x++) {
			for(y=0; y<linfo->Avg.HeaderN.y; y++) {
				for(z=0; z<linfo->Avg.HeaderN.z; z++) {
					mrcPixelDataGet(&linfo->Avg,    x, y, z, &avg,    mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&linfo->SQRAvg, x, y, z, &sqravg, mrcPixelRePart, mrcPixelHowNearest);

					mrcPixelDataSet(&linfo->Var, x, y, z, (sqravg-SQR(avg))*(linfo->numImage)/(linfo->numImage-1), mrcPixelRePart);
					DEBUGPRINT3("avg: %f sqravg: %f : %f\n", avg, sqravg, (sqravg-SQR(avg))*n/(n-1));
				}
			}
		}	
	}
	if(linfo->flagSD) {
		for(x=0; x<linfo->Avg.HeaderN.x; x++) {
			for(y=0; y<linfo->Avg.HeaderN.y; y++) {
				for(z=0; z<linfo->Avg.HeaderN.z; z++) {
					mrcPixelDataGet(&linfo->Avg,    x, y, z, &avg,    mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&linfo->SQRAvg, x, y, z, &sqravg, mrcPixelRePart, mrcPixelHowNearest);

					mrcPixelDataSet(&linfo->SD, x, y, z, sqrt((sqravg-SQR(avg))*(linfo->numImage)/(linfo->numImage-1)), mrcPixelRePart);
				}
			}
		}	
	}
	if(linfo->flagSE) {
		for(x=0; x<linfo->Avg.HeaderN.x; x++) {
			for(y=0; y<linfo->Avg.HeaderN.y; y++) {
				for(z=0; z<linfo->Avg.HeaderN.z; z++) {
					mrcPixelDataGet(&linfo->Avg,    x, y, z, &avg,    mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&linfo->SQRAvg, x, y, z, &sqravg, mrcPixelRePart, mrcPixelHowNearest);

					mrcPixelDataSet(&linfo->SE, x, y, z, sqrt((sqravg-SQR(avg))*(linfo->numImage)/(linfo->numImage-1)/linfo->numImage), mrcPixelRePart);
				}
			}
		}
	}
	if(linfo->flagSN) {
		for(x=0; x<linfo->Avg.HeaderN.x; x++) {
			for(y=0; y<linfo->Avg.HeaderN.y; y++) {
				for(z=0; z<linfo->Avg.HeaderN.z; z++) {
					mrcPixelDataGet(&linfo->Avg,    x, y, z, &avg,    mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&linfo->SQRAvg, x, y, z, &sqravg, mrcPixelRePart, mrcPixelHowNearest);

					mrcPixelDataSet(&linfo->SN, x, y, z, avg/sqrt((sqravg-SQR(avg))*(linfo->numImage)/(linfo->numImage-1)), mrcPixelRePart);
				}
			}
		}	
	}
	if(linfo->flagt) {
		for(x=0; x<linfo->Avg.HeaderN.x; x++) {
			for(y=0; y<linfo->Avg.HeaderN.y; y++) {
				for(z=0; z<linfo->Avg.HeaderN.z; z++) {
					mrcPixelDataGet(&linfo->Avg,    x, y, z, &avg,    mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&linfo->SQRAvg, x, y, z, &sqravg, mrcPixelRePart, mrcPixelHowNearest);

					mrcPixelDataSet(&linfo->t, x, y, z, avg/sqrt((sqravg-SQR(avg))/(n-2)), mrcPixelRePart);
				}
			}
		}
	}
}
