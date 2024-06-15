#ifndef MRC_FFT_INFO_H
#define MRC_FFT_INFO_H

#include "mrcImage.h"
#include "Vector.h"

/* struct begin */

typedef struct mrcFSInfo {
	double F00;	
	double Max;
	double MaxExceptForF00;
} mrcFSInfo;

/* struct end */

/* prototype begin */

extern floatVector* lmrcFSInfoYAxisMagAverage(mrcImage* fft);
extern void lmrcFSInfoYAxisProjection(mrcImage* out, mrcImage* in, long mode);
extern void lmrcFSInfoXFiltering(mrcImage* out, mrcImage* in, float RMaxX, long mode);
extern void lmrcFSInfo(mrcFSInfo* linfo, mrcImage* fft);
extern floatVector** lmrcFSInfoScatteringAngularDistributionDivisionAverage(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger N, int mode);
extern floatVector** lmrcFSInfoScatteringAngularDistributionDivisionAverageDelR(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger N, mrcImageParaTypeReal delR, int mode);


extern double lmrcImageFSInfoScatteringAugularDistribution3DShell(mrcImage* fft, double minR, double maxR, mrcPixelDataHowToGet mode ); 
/* prototype end */

#endif
