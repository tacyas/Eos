#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct infoDataList {
	mrcImage 			datXSection;	
	mrcImage 			datYSection;	
	mrcImage 			datXProj;	
	mrcImage 			datYProj;	
	double*             datHistgram;
	mrcImageInformation info;
	int 				flagLength;
} infoDataList;

extern void lmrcImageInfo(infoDataList* data, mrcImage* img, mrcImageInfoInfo* info);
extern void outputMrcImageInfo(FILE* fpt, infoDataList* data, mrcImage* img, mrcImageInfoInfo* info);

int
main(int argc, char* argv[])
{
    mrcImage img;
	mrcImageInfoInfo  info;
	infoDataList data;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	data.flagLength = info.Length;
#ifdef DEBUG
	mrcFileRead(&img, info.In, "from Main Routine", 1);
#else
    mrcFileRead(&img, info.In, "from Main Routine", 0);
#endif
    
    lmrcImageInfo(&data, &img, &info);
    outputMrcImageInfo(info.fptOut, &data, &img, &info);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "The -I option uses -rmax or -m options\n");
	fprintf(stderr, "-m 0: mean of all density\n");
	fprintf(stderr, "   1: mean of sphere surface density at rmax\n");
	fprintf(stderr, "   2: mean of cylinder surface density at rmax\n");
	fprintf(stderr, "   3: mean of edge pixels \n");
	fprintf(stderr, "   4: mean of Centre\n");
	fprintf(stderr, "   5: mean of Sparse \n");
	fprintf(stderr, "   6: mean of 2DEdge\n");
	fprintf(stderr, "   7: RMS of all pixels \n");
	fprintf(stderr, "   8: sd of all axes\n");
	fprintf(stderr, "  %02d: mean of high value area\n", meanOfHighValueArea);
	fprintf(stderr, "  %02d: mean of low value area\n",  meanOfLowValueArea);
}

void
lmrcImageInfo(infoDataList* data, mrcImage* img, mrcImageInfoInfo* info)
{
    if(info->flagX) {
		lmrcImageXSection(&(data->datXSection), img, info->X);
	}
    if(info->flagY) {
		lmrcImageYSection(&(data->datYSection), img, info->Y);
    }
    if(info->xProjection) {
		lmrcImageXProjection(&(data->datXProj), img);
    }
    if(info->yProjection) {
		lmrcImageYProjection(&(data->datYProj), img);
    }
    if(info->flagH) {
		lmrcImageHistgram(&(data->datHistgram), info->H, img);
    }
    if(info->flagH2) {
		lmrcImageHistgram2(&(data->datHistgram), info->H2, img);
    }
    if(info->flagH3) {
		lmrcImageHistgram3(&(data->datHistgram), info->H3, img);
    }
    if(info->flagH4) {
		lmrcImageHistgram4(&(data->datHistgram), info->H4, img);
    }
    if(info->flagH5) {
		lmrcImageHistgram5(&(data->datHistgram), info->H5, info->Low, info->High, img);
    }
    if(info->flagH6) {
		lmrcImageHistgram6(&(data->datHistgram), info->H6, info->Low, info->High, img);
    }
    if(info->Info) {
		data->info.rmax     = info->rmax;
		data->info.flagrmax = info->flagrmax;
		data->info.mode     = info->mode;
        data->info.thresHigh = info->Thres;
        data->info.thresLow  = info->Thres;
		lmrcImageInformation(&(data->info), img);
	}
}

void
outputMrcImageInfo(FILE* fpt, infoDataList* dat, mrcImage* img, mrcImageInfoInfo* info)
{
    int i, ix, iy, j;	double data;
	double dens;
		
    if(info->flagX) {
        for(iy=0; iy<img->HeaderN.y; iy++) {
            fprintf(fpt, "%5d %15.6g", iy, mrcPixelDataGet(&(dat->datXSection), 
															0.0,
															(mrcImageParaTypeReal)iy,
															0.0,
															&data,
															mrcPixelRePart,
															mrcPixelHowNearest));
			if(dat->flagLength) {
				fprintf(fpt, " %15.6g", iy*img->HeaderLength.y);
			}
			fprintf(fpt, "\n");
        }
    }

    if(info->flagY) {
        for(ix=0; ix<img->HeaderN.x; ix++) {
            fprintf(fpt, "%5d %15.6g", ix, mrcPixelDataGet(&(dat->datYSection), 
															(mrcImageParaTypeReal)ix,
															0.0,
															0.0,
															&data,
															mrcPixelRePart,
															mrcPixelHowNearest));

			if(dat->flagLength) {
				fprintf(fpt, " %15.6g", iy*img->HeaderLength.x);
			}
			fprintf(fpt, "\n");
        }
    }

    if(info->xProjection) {
        for(ix=0; ix<img->HeaderN.x; ix++) {
            fprintf(fpt, "%5d %15.6g", ix, mrcPixelDataGet(&(dat->datXProj), 
															(mrcImageParaTypeReal)ix,
															0.0,
															0.0,
															&data,
															mrcPixelRePart,
															mrcPixelHowNearest));

			if(dat->flagLength) {
				fprintf(fpt, " %15.6g", iy*img->HeaderLength.x);
			}
			fprintf(fpt, "\n");
        }
    }

    if(info->yProjection) {
        for(iy=0; iy<img->HeaderN.y; iy++) {
            fprintf(fpt, "%5d %15.6g", iy, mrcPixelDataGet(&(dat->datYProj),
															0.0,
															(mrcImageParaTypeReal)iy,
															0.0,
															&data,
															mrcPixelRePart,
															mrcPixelHowNearest));
			if(dat->flagLength) {
				fprintf(fpt, " %15.6g", iy*img->HeaderLength.y);
			}
			fprintf(fpt, "\n");
		}
    }
    if(info->flagH) {
        for(i=0; i<info->H; i++) {
			DEBUGPRINT2("MAX: %g, MIN: %g\n", img->HeaderAMax, img->HeaderAMin);
            dens = (img->HeaderAMax-img->HeaderAMin)/(info->H-1)*i+img->HeaderAMin, 
            fprintf(fpt, "%15.6g %15.6g |", 
                          dens, 
                          dat->datHistgram[i]);
			for(j=0; j<dat->datHistgram[i]*16; j++) {
				fprintf(fpt, " ");
			}
			fprintf(fpt, "*\n");
		}
	}
    if(info->flagH5) {
        for(i=0; i<info->H5; i++) {
			DEBUGPRINT2("MAX: %g, MIN: %g\n", img->HeaderAMax, img->HeaderAMin);
            dens = (info->High-info->Low)/(info->H5-1)*i+info->Low, 
            fprintf(fpt, "%15.6g %15.6g |", 
                          dens, 
                          dat->datHistgram[i]);
			for(j=0; j<dat->datHistgram[i]*16; j++) {
				fprintf(fpt, " ");
			}
			fprintf(fpt, "*\n");
		}
	}
    if(info->flagH2) {
		unsigned long n;
	
		n = (unsigned long)((img->HeaderAMax - img->HeaderAMin)/info->H2 + 1); 
        for(i=0; i<n; i++) {
            dens = img->HeaderAMin + i*info->H2;
            fprintf(fpt, "%15.6g %15.6g |", 
                          dens, 
                          dat->datHistgram[i]);
			
			for(j=0; j<dat->datHistgram[i]*16; j++) {
				fprintf(fpt, " ");
			}
			fprintf(fpt, "*\n");
        }
   	} 
    if(info->flagH6) {
		unsigned long n;
	
		n = (unsigned long)((info->High - info->Low)/info->H6 + 1); 
        for(i=0; i<n; i++) {
            dens = info->Low + i*info->H6;
            fprintf(fpt, "%15.6g %15.6g \n", 
                          dens, 
                          dat->datHistgram[i]);
			
        }
   	} 
    if(info->flagH3) {
        for(i=0; i<info->H; i++) {
			DEBUGPRINT2("MAX: %g, MIN: %g\n", img->HeaderAMax, img->HeaderAMin);
            dens = (img->HeaderAMax-img->HeaderAMin)/(info->H3-1)*i+img->HeaderAMin, 
            fprintf(fpt, "%15.6g %15.6g \n", 
                          dens, 
                          dat->datHistgram[i]);
		}
	}
    if(info->flagH4) {
		unsigned long n;
	
		n = (unsigned long)((img->HeaderAMax - img->HeaderAMin)/info->H4 + 1); 
        for(i=0; i<n; i++) {
            dens = img->HeaderAMin + i*info->H4;
            fprintf(fpt, "%15.6g %15.6g \n", 
                          dens, 
                          dat->datHistgram[i]);
			
        }
   	} 
    if(info->Info) {
		switch(info->mode){
			case meanOfAll: // 0
			case meanOfCentre: // 4 
			case meanOfSparse: // 5 
			case meanOf2DEdgeY:{ // 6 
				DEBUGPRINT3("SizeCheck: int %d: mrcImageParaTypeIntegerCoord: %d = 3x%d \n", 
								sizeof(int), sizeof(mrcImageParaTypeIntegerCoord), sizeof(mrcImageParaTypeInteger));
				DEBUGPRINT3("SizeCheck: info:%d Coord%d Coord.x:%d\n", 
								sizeof(dat->info), sizeof(dat->info.minCoord), sizeof(dat->info.minCoord.x));
   	    		fprintf(fpt, "Min: %15.6g (%d, %d, %d)\n", dat->info.min, 
								(int)dat->info.minCoord.x, (int)dat->info.minCoord.y, (int)dat->info.minCoord.z);
   	     		fprintf(fpt, "Max: %15.6g (%d, %d, %d)\n", dat->info.max, 
								(int)dat->info.maxCoord.x, (int)dat->info.maxCoord.y, (int)dat->info.maxCoord.z);
   	     		fprintf(fpt, "Mean: %15.6g\n", dat->info.mean);
   	    		fprintf(fpt, "SD:  %15.6g\n", dat->info.sd);
   	     		fprintf(fpt, "SE:  %15.6g\n", dat->info.se);
   	     		fprintf(fpt, "Sum: %15.6g\n", dat->info.mean*img->HeaderN.x*img->HeaderN.y*img->HeaderN.z);
				break;
			}
			case meanOfCylinderSurface:{ //2 
   	     		fprintf(fpt, "Mean:%15.6g\n", dat->info.meanOfCylinderSurface);
   	     		fprintf(fpt, "SD:%15.6g\n", dat->info.sdOfCylinderSurface);
   	     		fprintf(fpt, "SE:%15.6g\n", dat->info.seOfCylinderSurface);
				break;
			}
			case meanOfSphereSurface:{ // 1
   	     		fprintf(fpt, "Mean:%15.6g\n", dat->info.meanOfSphereSurface);
   	     		fprintf(fpt, "SD:%15.6g\n", dat->info.sdOfSphereSurface);
   	     		fprintf(fpt, "SE:%15.6g\n", dat->info.seOfSphereSurface);
				break;
			}
			case meanOfEdge:{ // 3
   	     		fprintf(fpt, "Mean: %15.6g\n", dat->info.meanOfEdge);
   	     		fprintf(fpt, "SD:   %15.6g\n", dat->info.sdOfEdge);
   	     		fprintf(fpt, "SE:   %15.6g\n", dat->info.seOfEdge);
				break;
			}
			case RMSofAllPixels:{ // 7
   	     		fprintf(fpt, "RMS: %15.6g\n", dat->info.RMS);
				break;
			}
			case sdOfAllAxis:{ // 8
   	     		fprintf(fpt, "aveOfAllAxis: %15.6g %15.6g %15.6g\n", dat->info.aveOfAllAxis.x , dat->info.aveOfAllAxis.y, dat->info.aveOfAllAxis.z);
   	     		fprintf(fpt, "sdOfAllAxis: %15.6g %15.6g %15.6g\n", dat->info.sdOfAllAxis.x , dat->info.sdOfAllAxis.y, dat->info.sdOfAllAxis.z);
				break;
			}
			case meanOfHighValueArea:{ // 8
   	     		fprintf(fpt, "meanOfHighValueArea(mean,sd,se):     %15.6g %15.6g %15.6g\n", dat->info.meanOfHighValueArea, dat->info.sdOfHighValueArea,     dat->info.seOfHighValueArea);
   	     		fprintf(fpt, "meanOfHighValueArea(min,median,max): %15.6g %15.6g %15.6g\n", dat->info.minOfHighValueArea,  dat->info.medianOfHighValueArea, dat->info.maxOfHighValueArea);
   	     		fprintf(fpt, "meanOfHighValueArea(thres,thresRate): %15.6g %15.6g \n", dat->info.thresOfHighValueArea,  dat->info.thresHigh);
				break;
			}
			case meanOfLowValueArea:{ // 8
   	     		fprintf(fpt, "meanOfLowValueArea(mean,sd,se):     %15.6g %15.6g %15.6g\n", dat->info.meanOfLowValueArea, dat->info.sdOfLowValueArea,     dat->info.seOfLowValueArea);
   	     		fprintf(fpt, "meanOfLowValueArea(min,median,max): %15.6g %15.6g %15.6g\n", dat->info.minOfLowValueArea,  dat->info.medianOfLowValueArea, dat->info.maxOfLowValueArea);
   	     		fprintf(fpt, "meanOfLowValueArea(thres,thresRate): %15.6g %15.6g \n", dat->info.thresOfLowValueArea,  dat->info.thresLow);
				break;
			}
			default:{
				fprintf(stderr, "Not supported mode :%ld", info->mode);
				exit(EXIT_FAILURE);
			}

		}
   	} 
}
