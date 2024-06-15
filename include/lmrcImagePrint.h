#ifndef MRC_IMAGE_PRINT_H
#define MRC_IMAGE_PRINT_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImagePrint.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrcImagePrint.h 
#%Z% Attention
#%Z%
*/

#include "mrcImage.h"
#include "psFile.h"

/* constant begin */
#define mrcImagePrintMode_ImageDensity        (0x00000001)
#define mrcImagePrintMode_ImageDensity_String "ImageDensity"
#define mrcImagePrintMode_Contour             (0x00000002)
#define mrcImagePrintMode_Contour_String      "Contour(DiffrentLineWidth)"
#define mrcImagePrintMode_Contour2            (0x00000004)
#define mrcImagePrintMode_Contour2_String     "Contour(SameLineWidth)"
#define mrcImagePrintMode_ImageCircle         (0x00000008)
#define mrcImagePrintMode_ImageCircle_String  "BlackCircles"
#define mrcImagePrintMode_Scale               (0x00000010)
#define mrcImagePrintMode_Scale_String        "Scale"
#define mrcImagePrintMode_Centre              (0x00000020)
#define mrcImagePrintMode_Centre_String       "Centre Mark"
#define mrcImagePrintMode_ASCII_Amp           (0x01000000)
#define mrcImagePrintMode_ASCII_Amp_String    "Amplitude by AsciiFile"
#define mrcImagePrintMode_ASCII_LogAmp        (0x02000000)
#define mrcImagePrintMode_ASCII_LogAmp_String "Log of Amplitude by AsciiFile"
#define mrcImagePrintMode_ASCII_Phase         (0x04000000)
#define mrcImagePrintMode_ASCII_Phase_String  "Phase by AsciiFile"
/* constant end */

/* struct begin */
typedef struct mrcImagePSFilePrintInfo  {
	mrcImageParaTypeReal scale;
	mrcImageParaTypeReal contourLineColorChange;
	mrcImageParaTypeReal contourLineWidthStart;
	mrcImageParaTypeReal contourLineWidthStep;
	long centre; /* 0: bottom right or 1:centre */	
	char whichSection; /* [x|y|z] */	
	double untwistAngle; /* untwist Image */
	psImageInfo psInfo;
	mrcImageParaTypeReal circleRadius;
} mrcImagePSFilePrintInfo;
/* struct end */

/* Utility Routines */
#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern void mrcInfoPrint(FILE* fpt, mrcImage* mrc, mrcImageParaTypeInteger mode);
extern void mrcImagePSFilePrint(FILE* fpt, mrcImage* mrc, char* message, mrcImagePSFilePrintInfo info, long nContour, float* level, long mode);
extern void mrcImageASCIIFilePrint(FILE* fpt, mrcImage* mrc, char* message, float scale, long nContour, float* level, long mode);
/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* MRC_IMAGE_H */

