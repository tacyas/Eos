/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageROI2D.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageROI2D.h 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_ROI2D_H 
#define  LMRC_IMAGE_ROI2D_H

#include "mrcImage.h"

/* struct begin */
typedef enum lmrcImageROIShape {
    Rect   =0,
    Rect2  =1,
    Circle =2,
	Line   =3,
	TiltRect = 4
} lmrcImageROIShape;

typedef struct lmrcImageSingleROIInfo {
    char* FileName;
    lmrcImageROIShape Shape;
    float centerx;     /* For All Shape */
    float centery;     
    float blx;         /* For Rect, TiltRect, Rect2, Circle */
    float bly;
    float brx;
    float bry;
    float trx;
    float try;
    float tlx;
    float tly;
	float startx;      /* For Line */
	float starty;
	float endx; 
	float endy;
	float minx;        /* For TiltRect */
	float miny;
	float maxx;
	float maxy;

	/* For Post Modification */
    int flagWidth;     /* For Rect, TiltRect, Rect2, Circle, Line */
    float width;
    int flagHeight;    /* For Rect, TiltRect, Rect2, Circle */
    float height; 

    float radius;
    int mode;

	int flagRotation;
	float angle;

	int flagMagnifiedWidth;
	float magnifiedWidth;

	int flagMagnifiedHeight;
	float magnifiedHeight;

	int flagNonPeriodic;
	/* For Layer Line Information */
	int flagLayerLine;
	float truePitch;
	float Ly;
	float dY;

	/* PadMode */
	int padMode;
} lmrcImageSingleROIInfo;

typedef struct lmrcImageROIsInfo {
    lmrcImageSingleROIInfo* ROI;
    int                numROI;
} lmrcImageROIsInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageROIsInformationGet(FILE* fpt, lmrcImageROIsInfo* linfo); 
extern void lmrcImageSingleROI(mrcImage* out, mrcImage* in, lmrcImageSingleROIInfo* linfo, int mode);
extern void lmrcImageROIsUsage(FILE* fpt);
/* prototype end */

#endif


