/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAbnormalValueRemove ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAbnormalValueRemove
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageAbnormalValueRemove ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Random.h"
#include "mrcImage.h"

typedef struct lmrcImageAbnormalValueRemoveInfo {
	float cutValueOverSigma; 
	int   flagUnsigned;
	float UnsignedMax;
	float UnsignedHalf;
    double Threshold;
    mrcImageInformation ImageInfo;
    FILE* paramOut;
} lmrcImageAbnormalValueRemoveInfo;

typedef enum lmrcImageAbnormalValueRemoveMode {
	lmrcImageAbnormalValueModeDefault = 0,
	lmrcImageAbnormalValueModeNear    = 1,  
	lmrcImageAbnormalValueModeRandom  = 2,  
	lmrcImageAbnormalValueModeMean    = 3 
} lmrcImageAbnormalValueRemoveMode;

typedef enum lmrcImageAbnormalValueRemoveAreaPattern {
	lmrcImageAbnormalValueModeAllArea       = 0,
	lmrcImageAbnormalValueModeHighValueArea = 1,  
	lmrcImageAbnormalValueModeLowValueArea  = 2  
} lmrcImageAbnormalValueRemoveAreaPattern;

extern void
lmrcImageAbnormalValueRemove(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveAreaPattern pattern,
							 lmrcImageAbnormalValueRemoveMode mode);

extern void
lmrcImageAbnormalValueRemoveAllArea(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveMode mode);

extern void
lmrcImageAbnormalValueRemoveHighValueArea(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveMode mode);

extern void
lmrcImageAbnormalValueRemoveLowValueArea(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveMode mode);

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage out;
	mrcImageAbnormalValueRemoveInfo info;
	lmrcImageAbnormalValueRemoveInfo linfo;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.cutValueOverSigma = info.cutValue;
	linfo.flagUnsigned = info.flagUnsignedMax;
	linfo.UnsignedMax = info.UnsignedMax;
	linfo.UnsignedHalf= info.UnsignedHalf;
	linfo.Threshold = info.Threshold;

    linfo.paramOut = info.fptOutParams;

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	out.Header = in.Header;
	out.HeaderMode = mrcFloatImage; 
	mrcInit(&out, NULL);
	
	lmrcImageAbnormalValueRemove(&out, &in, &linfo, info.Pattern, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- Mode: \n");
	fprintf(stderr, "    %d: Random Value \n", lmrcImageAbnormalValueModeDefault);
	fprintf(stderr, "    %d: Near Value \n", lmrcImageAbnormalValueModeNear);
	fprintf(stderr, "    %d: Random Value using SD and mean within Normal Area\n", lmrcImageAbnormalValueModeRandom);
	fprintf(stderr, "    %d: Mean Value using SD and mean within Normal Area\n", lmrcImageAbnormalValueModeMean);
    fprintf(stderr, "----- Area Pattern \n");
	fprintf(stderr, "    %d: All area\n", lmrcImageAbnormalValueModeAllArea);
	fprintf(stderr, "    %d: HIgh value area\n", lmrcImageAbnormalValueModeHighValueArea);  
	fprintf(stderr, "    %d: Low  value area\n", lmrcImageAbnormalValueModeLowValueArea);
}

void
lmrcImageAbnormalValueRemove(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveAreaPattern pattern,
							 lmrcImageAbnormalValueRemoveMode mode)
{
    mrcImage tmp;
    mrcImageParaTypeReal x, y, z;
    double data, dst, tmpD;

	if(linfo->flagUnsigned){
		tmp.Header = in->Header;
		tmp.HeaderMode = mrcFloatImage;
		mrcInit(&tmp, NULL);
		for(z=0; z<in->HeaderN.z; z++) {
		for(y=0; y<in->HeaderN.y; y++) {
		for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in,   x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(linfo->UnsignedHalf <= data) {
				data -= linfo->UnsignedMax;
			}
		}
		}
		}
		mrcPixelDataSet(&tmp, x, y, z,  data, mrcPixelRePart);
		in = &tmp;
	}

    switch(pattern) {
        case lmrcImageAbnormalValueModeAllArea: {
            linfo->ImageInfo.mode = meanOfAll;
            lmrcImageInformation(&(linfo->ImageInfo), in);
            fprintf(linfo->paramOut, "AbnormalMode: AllArea\n");
            fprintf(linfo->paramOut, "ImageInformation(mean,sd):    %g %g\n", linfo->ImageInfo.mean, linfo->ImageInfo.sd);
            fprintf(linfo->paramOut, "CutValue:                     %g\n", linfo->cutValueOverSigma);
            fprintf(linfo->paramOut, "NormalArea(mean-sd,mean+sd):  %g %g\n", linfo->ImageInfo.mean-linfo->ImageInfo.sd, linfo->ImageInfo.mean+ linfo->ImageInfo.sd);
            lmrcImageAbnormalValueRemoveAllArea(out, in, linfo, mode); 
            break;
        }
        case lmrcImageAbnormalValueModeHighValueArea: {
            linfo->ImageInfo.mode = meanOfHighValueArea;
            linfo->ImageInfo.thresHigh = linfo->Threshold;
            lmrcImageInformation(&(linfo->ImageInfo), in);
            fprintf(linfo->paramOut, "AbnormalMode: HighValueArea\n");
            fprintf(linfo->paramOut, "ImageInformation(mean,sd):    %g %g\n", linfo->ImageInfo.meanOfHighValueArea, linfo->ImageInfo.sdOfHighValueArea);
            fprintf(linfo->paramOut, "CutValue:                     %g\n", linfo->cutValueOverSigma);
            fprintf(linfo->paramOut, "NormalArea(thres,mean+sd):  %g %g\n", linfo->ImageInfo.thresOfHighValueArea,
                                                                            linfo->ImageInfo.meanOfHighValueArea+linfo->cutValueOverSigma*linfo->ImageInfo.sdOfHighValueArea);
            lmrcImageAbnormalValueRemoveHighValueArea(out, in, linfo, mode); 
            break;
        }
        case lmrcImageAbnormalValueModeLowValueArea: {
            linfo->ImageInfo.mode = meanOfLowValueArea;
            linfo->ImageInfo.thresLow = linfo->Threshold;
            lmrcImageInformation(&(linfo->ImageInfo), in);
            fprintf(linfo->paramOut, "AbnormalMode: LowValueArea\n");
            fprintf(linfo->paramOut, "ImageInformation(mean,sd):    %g %g\n", linfo->ImageInfo.mean, linfo->ImageInfo.sd);
            fprintf(linfo->paramOut, "CutValue:                     %g\n", linfo->cutValueOverSigma);
            fprintf(linfo->paramOut, "NormalArea(mean-cutValue*sd,thres):  %g %g\n", linfo->ImageInfo.meanOfLowValueArea-linfo->cutValueOverSigma*linfo->ImageInfo.sdOfLowValueArea, 
                                                                                     linfo->ImageInfo.thresOfLowValueArea);
            lmrcImageAbnormalValueRemoveLowValueArea(out, in, linfo, mode); 
            break;
        }
        default: {
            fprintf(stderr, "Not supported pattern: %d\n", pattern);
            break;
        }
    }
}

void
lmrcImageAbnormalValueRemoveAllArea(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveMode mode)
{
	mrcImageInformation inInfo;
	mrcImage tmp;
	mrcImageParaTypeReal x, y, z;
	double data, dst, tmpD;

    inInfo = linfo->ImageInfo;
	switch(mode) {
		case lmrcImageAbnormalValueModeDefault: {
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < inInfo.mean - linfo->cutValueOverSigma*inInfo.sd 
				  ||      inInfo.mean + linfo->cutValueOverSigma*inInfo.sd < data) {
					dst = inInfo.mean + inInfo.sd*randomNormalGet(2);
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst<0) {
					            DEBUGPRINT1("data is negative: %lf\n", data);
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
			break;
		}
		case lmrcImageAbnormalValueModeRandom: {
			double sum, mean, SD;
			int n;
			sum = n = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.mean - linfo->cutValueOverSigma*inInfo.sd < data 
				 && data < inInfo.mean + linfo->cutValueOverSigma*inInfo.sd ) {
					sum += data;
					n++;
				}
			}
			}
			}
			if(0<n) {
				mean = sum/n;
			} else {
				fprintf(stderr, "No data within proper area\n");
			}
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.mean - linfo->cutValueOverSigma*inInfo.sd < data 
				 && data < inInfo.mean + linfo->cutValueOverSigma*inInfo.sd ) {
					sum += SQR(data - mean);
				}
			}
			}
			}
			SD = sqrt(sum/n);

			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < mean - linfo->cutValueOverSigma*inInfo.sd
				  ||      mean + linfo->cutValueOverSigma*inInfo.sd < data) {
					dst = mean + SD*randomNormalGet(2);
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst<0) {
					            DEBUGPRINT1("data is negative: %lf\n", data);
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
			break;
		}
		case lmrcImageAbnormalValueModeMean: {
			double sum, mean, SD;
			int n;
			sum = n = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.mean - linfo->cutValueOverSigma*inInfo.sd < data 
				 && data < inInfo.mean + linfo->cutValueOverSigma*inInfo.sd ) {
					sum += data;
					n++;
				}
			}
			}
			}
			if(0<n) {
				mean = sum/n;
			} else {
				fprintf(stderr, "No data within proper area\n");
			}

			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < mean - linfo->cutValueOverSigma*inInfo.sd
				  ||      mean + linfo->cutValueOverSigma*inInfo.sd < data) {
					dst = mean;
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(data<0) {
					            DEBUGPRINT1("data is negative: %lf\n", data);
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
			break;
		}
		case lmrcImageAbnormalValueModeNear: {
			mrcImageParaTypeReal ox, oy, oz;
			mrcImageParaTypeReal dx, dy, dz;
			mrcImageParaTypeReal min, max;
			mrcImageParaTypeReal minHalf, maxHalf;
			double sum; 
			mrcImageParaTypeInteger count;
			mrcImageParaTypeInteger flag;

			min = inInfo.mean - linfo->cutValueOverSigma*inInfo.sd;
			minHalf = inInfo.mean - linfo->cutValueOverSigma*inInfo.sd/2.0;
			max = inInfo.mean + linfo->cutValueOverSigma*inInfo.sd;
			maxHalf = inInfo.mean + linfo->cutValueOverSigma*inInfo.sd/2.0;

			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);

				if(data < min  || max < data) {
					DEBUGPRINT6("data %f out of range %f <-> %f at (%f, %f, %f) \n", data, min, max, x, y, z);
					flag  = 0;
					dx = dy = dz = 1;
					while(flag<4) {	
					 	count = 0;	
						sum = 0;
						for(oz=z-dz; oz<=z+dz; oz++) {
						for(oy=y-dy; oy<=y+dy; oy++) {
						for(ox=x-dx; ox<=x+dx; ox++) {
							if(SQR((ox-x)/dx)+SQR((oy-y)/dy)+SQR((oz-z)/dz)<=1) {
						    	mrcPixelDataGet(in, ox, oy, oz, &tmpD, mrcPixelRePart, mrcPixelHowNearest);
						    	if( min < tmpD && tmpD < max) {
									sum += tmpD;
							    	count++;
						  		}
							}
						}
						}
						}
						if(4<=count) {
							flag ++;
							dst = sum/count;  
							DEBUGPRINT5("data %f count %d at (%f, %f, %f) \n", dst, count, x, y, z);
							if(dst < minHalf || maxHalf < dst ) {
								DEBUGPRINT("wider range +1 because of wide abnormal value\n");
								dx++;
								dy++;
								dz++;
							} else {
								flag = 4;	
							}
						} else {
							DEBUGPRINT("wider range +1\n");
							flag=0;
							dx++;
							dy++;
							dz++;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
	return;	
}


void
lmrcImageAbnormalValueRemoveHighValueArea(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveMode mode)
{
	mrcImageInformation inInfo;
	mrcImage tmp;
	mrcImageParaTypeReal x, y, z;
	double data, dst, tmpD;

    inInfo = linfo->ImageInfo;
	switch(mode) {
		case lmrcImageAbnormalValueModeDefault: {
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.meanOfHighValueArea + linfo->cutValueOverSigma*inInfo.sdOfHighValueArea < data) {
					dst = inInfo.meanOfHighValueArea + inInfo.sdOfHighValueArea*randomNormalGet(2);
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst<0) {
								dst= 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
			break;
		}
		case lmrcImageAbnormalValueModeMean: {
            double sum, mean;
            int n;
            sum = 0;
            n = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if( inInfo.thresOfHighValueArea < data && 
                    data < inInfo.meanOfHighValueArea + linfo->cutValueOverSigma*inInfo.sdOfHighValueArea ) {
					sum += data;
				}
            }
            }
            }
            mean = sum/n;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.meanOfHighValueArea + linfo->cutValueOverSigma*inInfo.sdOfHighValueArea < data) {
					dst = mean;
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst <0) {
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
            }
            }
            }
            break;
        }
		case lmrcImageAbnormalValueModeNear: {
			mrcImageParaTypeReal ox, oy, oz;
			mrcImageParaTypeReal dx, dy, dz;
			mrcImageParaTypeReal min, max;
			mrcImageParaTypeReal minHalf, maxHalf;
			double sum; 
			mrcImageParaTypeInteger count;
			mrcImageParaTypeInteger flag;

			min = inInfo.thresOfHighValueArea;
			minHalf = (inInfo.meanOfHighValueArea + min)/2.0;
			max = inInfo.meanOfHighValueArea + linfo->cutValueOverSigma*inInfo.sdOfHighValueArea;
			maxHalf = inInfo.meanOfHighValueArea + linfo->cutValueOverSigma*inInfo.sdOfHighValueArea/2.0;

			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(max < data) {
					DEBUGPRINT6("data %f out of range %f <-> %f at (%f, %f, %f) \n", data, min, max, x, y, z);
					flag  = 0;
					dx = dy = dz = 1;
					while(flag<4) {	
					 	count = 0;	
						sum = 0;
						for(oz=z-dz; oz<=z+dz; oz++) {
						for(oy=y-dy; oy<=y+dy; oy++) {
						for(ox=x-dx; ox<=x+dx; ox++) {
							if(SQR((ox-x)/dx)+SQR((oy-y)/dy)+SQR((oz-z)/dz)<=1) {
						    	mrcPixelDataGet(in, ox, oy, oz, &tmpD, mrcPixelRePart, mrcPixelHowNearest);
						    	if(tmpD < max) {
									sum += tmpD;
							    	count++;
						  		}
							}
						}
						}
						}
						if(4<=count) {
							flag ++;
							dst = sum/count;  
							DEBUGPRINT5("data %f count %d at (%f, %f, %f) \n", data, count, x, y, z);
							if( maxHalf < data ) {
								DEBUGPRINT("wider range +1 because of wide abnormal value\n");
								dx++;
								dy++;
								dz++;
							} else {
								flag = 4;	
							}
						} else {
							DEBUGPRINT("wider range +1\n");
							flag=0;
							dx++;
							dy++;
							dz++;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
            break;
        }
		case lmrcImageAbnormalValueModeRandom: {
            double sum, mean, SD;
            int n;
            n=0;
            sum = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.thresOfHighValueArea < data 
                 &&data < inInfo.meanOfHighValueArea + linfo->cutValueOverSigma*inInfo.sdOfHighValueArea) {
                    sum += data;
                    n++;
				}
            }
            }
            }
            mean = sum/n;
            sum = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.thresOfHighValueArea < data 
                 &&data < inInfo.meanOfHighValueArea + linfo->cutValueOverSigma*inInfo.sdOfHighValueArea) {
                    sum += SQR(data-mean);
				}
            }
            }
            }
            SD = sqrt(sum/n);
            
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(mean + linfo->cutValueOverSigma*SD < data) {
					dst = mean + SD*randomNormalGet(2);
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst<0) {
					            DEBUGPRINT1("data is negative: %lf\n", data);
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
	return;	
}


void
lmrcImageAbnormalValueRemoveLowValueArea(mrcImage* out, 
							 mrcImage* in, 
							 lmrcImageAbnormalValueRemoveInfo* linfo,
							 lmrcImageAbnormalValueRemoveMode mode)
{
	mrcImageInformation inInfo;
	mrcImage tmp;
	mrcImageParaTypeReal x, y, z;
	double data, dst, tmpD;

    inInfo = linfo->ImageInfo;
	switch(mode) {
		case lmrcImageAbnormalValueModeDefault: {
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < inInfo.meanOfLowValueArea - linfo->cutValueOverSigma*inInfo.sdOfLowValueArea) {
					dst = inInfo.meanOfLowValueArea + inInfo.sdOfLowValueArea*randomNormalGet(2);
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst<0) {
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
			break;
		}
		case lmrcImageAbnormalValueModeMean: {
            double sum, mean;
            int n;
            n = 0;
            sum = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(inInfo.meanOfLowValueArea - linfo->cutValueOverSigma*inInfo.sdOfLowValueArea < data
                   && data < inInfo.thresOfLowValueArea ) {
                    sum += data; 
                    n++;
				}
			}
			}
			}
            mean = sum/n;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < inInfo.meanOfLowValueArea - linfo->cutValueOverSigma*inInfo.sdOfLowValueArea) {
					dst = mean;
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst<0) {
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
            break;
        }
		case lmrcImageAbnormalValueModeNear: {
			mrcImageParaTypeReal ox, oy, oz;
			mrcImageParaTypeReal dx, dy, dz;
			mrcImageParaTypeReal min, max;
			mrcImageParaTypeReal minHalf, maxHalf;
			double sum; 
			mrcImageParaTypeInteger count;
			mrcImageParaTypeInteger flag;

			min = inInfo.meanOfLowValueArea - linfo->cutValueOverSigma*inInfo.sdOfLowValueArea;
			minHalf = (inInfo.meanOfLowValueArea + min)/2.0;
			max = inInfo.thresOfLowValueArea;
			maxHalf = (inInfo.meanOfLowValueArea + max)/2.0;

			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < min) {
					DEBUGPRINT6("data %f out of range %f <-> %f at (%f, %f, %f) \n", data, min, max, x, y, z);
					flag  = 0;
					dx = dy = dz = 1;
					while(flag<4) {	
					 	count = 0;	
						sum = 0;
						for(oz=z-dz; oz<=z+dz; oz++) {
						for(oy=y-dy; oy<=y+dy; oy++) {
						for(ox=x-dx; ox<=x+dx; ox++) {
							if(SQR((ox-x)/dx)+SQR((oy-y)/dy)+SQR((oz-z)/dz)<=1) {
						    	mrcPixelDataGet(in, ox, oy, oz, &data, mrcPixelRePart, mrcPixelHowNearest);
						    	if( min < data && data < max) {
									sum += data;
							    	count++;
						  		}
							}
						}
						}
						}
						if(4<=count) {
							flag ++;
							data = sum/count;  
							DEBUGPRINT5("data %f count %d at (%f, %f, %f) \n", data, count, x, y, z);
							if(data<minHalf) {
								DEBUGPRINT("wider range +1 because of wide abnormal value\n");
								dx++;
								dy++;
								dz++;
							} else {
								flag = 4;	
							}

						} else {
							DEBUGPRINT("wider range +1\n");
							flag=0;
							dx++;
							dy++;
							dz++;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
				mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
            break;
        }
		case lmrcImageAbnormalValueModeRandom: {
            double sum, mean, SD;
            int n;
            n=0;
            sum = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < inInfo.thresOfLowValueArea 
                 &&inInfo.meanOfLowValueArea - linfo->cutValueOverSigma*inInfo.sdOfLowValueArea < data) {
                    sum += data;
                    n++;
				}
            }
            }
            }
            mean = sum/n;
            sum = 0;
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < inInfo.thresOfLowValueArea 
                 &&inInfo.meanOfLowValueArea - linfo->cutValueOverSigma*inInfo.sdOfLowValueArea  <data) {
                    sum += SQR(data-mean);
				}
            }
            }
            }
            SD = sqrt(sum/n);
            
			for(z=0; z<in->HeaderN.z; z++) {
			for(y=0; y<in->HeaderN.y; y++) {
			for(x=0; x<in->HeaderN.x; x++) {
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data < mean - linfo->cutValueOverSigma*SD) {
					dst = mean + SD*randomNormalGet(2);
					switch(out->HeaderMode) {
						case mrcCharImage:
						case mrcShortImage:
						case mrcLongImage: {
							if(dst<0) {
					            DEBUGPRINT1("data is negative: %lf\n", data);
								dst = 0;
							}
							break;
						}
					}
                    fprintf(linfo->paramOut,"AbnormalValue: %f -> %f at %f %f %f\n", data, dst, x, y, z); 
				} else {
                    dst = data;
                }
	            mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart);
			}
			}
			}
            break;
        }
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	return;	
}


