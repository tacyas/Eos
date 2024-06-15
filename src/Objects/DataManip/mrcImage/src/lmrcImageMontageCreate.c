/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMontageCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageMontageCreate 
#%Z% Attention
#%Z%
*/
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lmrcImageMontage.h"
#include "lmrcImageEdgeAverage.h"

static char __sccs_id[] = "%Z%lmrcImageMontageCreate ver%I%; Date:%D% %Z%";

int
lmrcImageMontageCreate(mrcImage* out, mrcImage* in, int imageNum, lmrcImageMontageInfo linfo, int mode)
{
	int i;
	mrcImage tmp;	
	mrcImageParaTypeReal x,   y,  z;
	mrcImageParaTypeReal sx, sy, sz;
	double data;
	double* avg;
	double avgall;
	double  orgValue;
	lmrcImageEdgeAverageInfo* llinfo;
	lmrcImageEdgeAverageInfo  llinfotmp;
	mrcImageParaTypeInteger icenter = imageNum/2; /* Center */
	mrcImageParaTypeInteger icenterx;
	mrcImageParaTypeInteger icentery;

	icenterx = icenter%linfo.nx;
	icentery = icenter/linfo.nx;

	out->Header    = in[0].Header;
	out->HeaderN.x = linfo.PadInfo.Width *linfo.nx;
	out->HeaderN.y = linfo.PadInfo.Height*linfo.ny;
	out->HeaderN.z = 1;
	mrcInit(out, NULL);
	
	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			for(z=0; z<out->HeaderN.z; z++) {
				mrcPixelDataSet(out, x, y, z, linfo.PadInfo.Value, mrcPixelRePart);
			}
		}
	}

	if(linfo.flagEdgeAverage) {
		avg    = (double*)memoryAllocate(sizeof(double)*imageNum, "in lmrcImageMontageCreate");
		llinfo = (lmrcImageEdgeAverageInfo*)memoryAllocate(sizeof(lmrcImageEdgeAverageInfo)*imageNum, "in lmrcImageMontageCreate");
		for(i=0; i<imageNum; i++) {
			llinfo[i].width  = linfo.EdgeAverageWindow;
			llinfo[i].devide = 2;
			DEBUGPRINT1("#### Edge %d ####\n", i);
			lmrcImageEdgeAverage(&(in[i]), &(llinfo[i]), 0);
		}
		switch(imageNum) {
			case 9: {
		    /* 
		               Edge 2
					   d0 d1
		               -----
		           d1 |     | d1
		    Edge 3    |     |    Edge 1
		           d0 |     | d0
		               -----
					   d0 d1
		               Edge 0

		    shotID	
                        
                   6    7    8           

				   3    4    5				   

                   0    1    2

				llinfo[shotID].avg[Edge][Divide]
	
		    */
				avg[6] = sqrt((llinfo[6].avg[0][1]/(llinfo[3].avg[2][1]/(llinfo[3].avg[1][0]/llinfo[4].avg[3][0]))) 
				             *(llinfo[6].avg[1][0]/(llinfo[7].avg[3][0]/(llinfo[7].avg[0][0]/llinfo[4].avg[2][0]))));

				avg[7] = (llinfo[7].avg[0][0]/llinfo[4].avg[2][0]);

				avg[8] = sqrt((llinfo[8].avg[0][0]/(llinfo[5].avg[2][0]/(llinfo[5].avg[3][0]/llinfo[4].avg[1][0]))) 
				            * (llinfo[8].avg[3][0]/(llinfo[7].avg[1][0]/(llinfo[7].avg[0][0]/llinfo[4].avg[2][0]))));

				avg[3] = (llinfo[3].avg[1][0]/llinfo[4].avg[3][0]); 

				avg[4] = 1;                                               

				avg[5] = (llinfo[5].avg[3][0]/llinfo[4].avg[1][0]);


				avg[0] = sqrt((llinfo[0].avg[2][1]/(llinfo[3].avg[0][1]/(llinfo[3].avg[1][0]/llinfo[4].avg[3][0]))) 
                             *(llinfo[0].avg[1][1]/(llinfo[1].avg[3][1]/(llinfo[1].avg[2][0]/llinfo[4].avg[0][0]))));

				avg[1] = (llinfo[1].avg[2][0]/llinfo[4].avg[0][0]); 

				avg[2] = sqrt((llinfo[2].avg[2][0]/(llinfo[5].avg[0][0]/(llinfo[5].avg[3][0]/llinfo[4].avg[1][0])))
						     *(llinfo[2].avg[3][1]/(llinfo[1].avg[1][1]/(llinfo[1].avg[2][0]/llinfo[4].avg[0][0]))));

				DEBUGPRINT3("avg[7] %f = [7]avg[0][0] %f / [4].avg[2][0] %f\n", avg[7], llinfo[7].avg[0][0], llinfo[4].avg[2][0]);
				break;	
			}
			default: {
				fprintf(stderr, "Not supported imageNum for Edge-Averaging: %d\n", imageNum);
				exit(EXIT_FAILURE);
			}
		}

	}
	if(linfo.flagNoAverage) {
		avgall = 0;
		for(i=0; i<imageNum; i++) {
			avgall += in[i].HeaderAMean;
		}
		avgall /= imageNum; 
	}
	orgValue = linfo.PadInfo.Value; 

	for(i=0; i<imageNum; i++) {
		mrcStatDataSet(&(in[i]), 0);
		if(in[i].HeaderN.z>1) {
			fprintf(stderr, "Not supported: Nz=%f\n", in[i].HeaderN.z);
			exit(EXIT_FAILURE);
		}
		
		if(linfo.flagEdgeAverage) {
			linfo.PadInfo.Value = orgValue*(in[i].HeaderAMean/in[icenter].HeaderAMean)/avg[i];

			DEBUGPRINT2("##### Edge %d center %d####\n", i, icenter);
			DEBUGPRINT2("ImageAverage: center %f  current %f \n", in[icenter].HeaderAMean, in[i].HeaderAMean);
			DEBUGPRINT2("PadInfo : %f -> %f \n", orgValue, linfo.PadInfo.Value);
			DEBUGPRINT2("Edge: %f == %f \n", llinfo[icenter].avg[2][0]/in[icenter].HeaderAMean*orgValue, llinfo[i].avg[0][0]/in[i].HeaderAMean*linfo.PadInfo.Value);

		} else if(linfo.flagNoAverage) {
			DEBUGPRINT("No Avearge");
			linfo.PadInfo.Value = orgValue - (avgall - in[i].HeaderAMean);
		} else {
			/* No Action */;
		}
		lmrcImagePad(&tmp, &(in[i]), &(linfo.PadInfo), linfo.PadMode);

#ifdef DEBUG
		DEBUGPRINT1("##### Edge %d ####\n", i);
		llinfotmp = llinfo[i];
		lmrcImageEdgeAverage(&tmp, &llinfotmp, 0);
		mrcStatDataSet(&tmp, 0);
		DEBUGPRINT2("ImageAverage: original %f  current %f \n", in[i].HeaderAMean, tmp.HeaderAMean);
#endif

		sx = (i%linfo.nx)*tmp.HeaderN.x;
		sy = (i/linfo.nx)*tmp.HeaderN.y;
		DEBUGPRINT3("s(%f %f) %d\n", sx, sy, i);
		for(x=0; x<tmp.HeaderN.x; x++) {
			for(y=0; y<tmp.HeaderN.y; y++) {
				for(z=0; z<tmp.HeaderN.z; z++) {
					mrcPixelDataGet(&tmp,    x,    y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
					if(linfo.flagMaxValue) {
						if(linfo.MaxValue < data) {
							if(linfo.flagValueAssignedToMax) {
								data = linfo.ValueAssignedToMax;
							} else {
								data = linfo.PadInfo.Value;
							}
						}
					}
					mrcPixelDataSet( out, sx+x, sy+y, z,  data, mrcPixelRePart);
				}
			}
		}
		mrcImageFree(&tmp, "main");
	}
}

