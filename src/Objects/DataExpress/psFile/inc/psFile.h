#ifndef PS_FILE_H
#define PS_FILE_H
/*
* PostScript File IO utility Header File
*   Edited by Tac
*   1992.10
*/
#include "File.h"

/* constant begin */
#define MAX_STRING_LENGTH 256
                             
#define PS_FILE_STATUS_ERROR     (0)
#define PS_FILE_STATUS_OK        (1)
/* constant end */

/* struct begin */
typedef long   psParaTypeInteger;
typedef double psParaTypeReal;

typedef struct psInfo {
    psParaTypeInteger prologInfoNum;
    char**            prologInfo;
	char              label[MAX_STRING_LENGTH];
    psParaTypeInteger page;
    psParaTypeInteger status;
} psInfo;

typedef struct psPageInfo psPageInfo;

struct psPageInfo {
	psParaTypeInteger page;
	psParaTypeInteger byte;
	long start;
	long end;
	psPageInfo* next;
};

typedef struct psFile {
	FILE* fpt;
	psInfo info;
	long headEnd;
	psPageInfo* current;
	psPageInfo* top;
	psPageInfo* end;
	long byte;
} psFile;

/* struct end */

/* constant begin */
#define PROLOG_STRING_NUM    (11)

#define PROLOG_VERSION        (0)
#define PROLOG_TITLE          (1)
#define PROLOG_CREATOR        (2)
#define PROLOG_CREATION_DATE  (3)
#define PROLOG_FOR            (4)
#define PROLOG_BOUND_BOX      (5)
#define PROLOG_PAGES          (6)
#define PROLOG_DOC_FONTS      (7)
#define PROLOG_END_DOC        (8)
#define PROLOG_END_PRO        (9)

typedef enum psImageScaleMode {
    psImageScaleModeBottomLeft = 1,
    psImageScaleModeCenter     = 2
} psImageScaleMode;

#define PS_IMAGE_CENTRE_LINE_WIDTH  (0.1)
#define PS_IMAGE_CENTRE_MARK_LENGTH (0.01)

#define PS_IMAGE_SCALE_LINE_WIDTH0 (0.2)
#define PS_IMAGE_SCALE_LINE_WIDTH1 (0.1)
#define PS_IMAGE_SCALE_LINE_LENGTH0 (10.0)
#define PS_IMAGE_SCALE_LINE_LENGTH1 (5.0)
#define PS_IMAGE_SCALE_LINE_LENGTH2 (3.0)
#define PS_IMAGE_SCALE_LINE_LENGTH3 (2.0)
#define PS_IMAGE_SCALE_LINE_LENGTH4 (1.0)
#define PS_IMAGE_SCALE_LINE_LENGTH00 (-10.0)
#define PS_IMAGE_SCALE_LINE_LENGTH10 (-5.0)
#define PS_IMAGE_SCALE_LINE_LENGTH20 (-3.0)
#define PS_IMAGE_SCALE_LINE_LENGTH30 (-2.0)
#define PS_IMAGE_SCALE_LINE_LENGTH40 (-1.0)

#define psContourMode_DifferentLineWidthContour (0x01)
#define psContourMode_SameLineWidthContour      (0x02)

/* constant end */

/* struct begin */
typedef struct psImageInfo {
	/* For Image Space */
    psParaTypeReal scaleX;
    psParaTypeReal scaleY;
    psParaTypeReal translateX;
    psParaTypeReal translateY;
    psParaTypeReal angle;

	/* Image Size */
    psParaTypeInteger width;
    psParaTypeInteger height;
    psParaTypeInteger section;
	/* For Contour */
    psParaTypeInteger bps;
    psParaTypeInteger nContour;
    psParaTypeReal*   contourLevel;
	/* For Density Image */
    unsigned char*    image;
	/* For Contour */
    float*            floatImage;
	psParaTypeReal    contourLineColorChange;
	psParaTypeReal    contourLineWidthStart;
	psParaTypeReal    contourLineWidthStep;

	/* For 3D Contour */
	psParaTypeReal    eyeX;   /* Eye Position */
	psParaTypeReal    eyeY;
	psParaTypeReal    eyeZ;
	psParaTypeReal    pointX; /* Projection Surface Position */
	psParaTypeReal    pointY; /* Surface Normal: (position - eye)  */
	psParaTypeReal    pointZ;

	/* For Colour */
	psParaTypeInteger flagRGBColor;	
	psParaTypeInteger flagRGBGradientColor;	
	psParaTypeReal Red;
	psParaTypeReal Green;
	psParaTypeReal Blue;
	psParaTypeReal RedFirst;
	psParaTypeReal GreenFirst;
	psParaTypeReal BlueFirst;
	psParaTypeReal RedLast;
	psParaTypeReal GreenLast;
	psParaTypeReal BlueLast;
	psParaTypeInteger flagHSBColor;	
	psParaTypeInteger flagHSBGradientColor;	
	psParaTypeReal Hue;
	psParaTypeReal Saturation;
	psParaTypeReal Brightness;
	psParaTypeReal HueFirst;
	psParaTypeReal SaturationFirst;
	psParaTypeReal BrightnessFirst;
	psParaTypeReal HueLast;
	psParaTypeReal SaturationLast;
	psParaTypeReal BrightnessLast;

	/* For Line Colour */
	psParaTypeInteger flagLineRGBColor;	
	psParaTypeInteger flagLineRGBGradientColor;	
	psParaTypeReal LineRed;
	psParaTypeReal LineGreen;
	psParaTypeReal LineBlue;
	psParaTypeReal LineRedFirst;
	psParaTypeReal LineGreenFirst;
	psParaTypeReal LineBlueFirst;
	psParaTypeReal LineRedLast;
	psParaTypeReal LineGreenLast;
	psParaTypeReal LineBlueLast;
	psParaTypeInteger flagLineHSBColor;	
	psParaTypeInteger flagLineHSBGradientColor;	
	psParaTypeReal LineHue;
	psParaTypeReal LineSaturation;
	psParaTypeReal LineBrightness;
	psParaTypeReal LineHueFirst;
	psParaTypeReal LineSaturationFirst;
	psParaTypeReal LineBrightnessFirst;
	psParaTypeReal LineHueLast;
	psParaTypeReal LineSaturationLast;
	psParaTypeReal LineBrightnessLast;

	/* For Circle */
	psParaTypeReal CircleRadius;
    long              dummy;
} psImageInfo;
/* struct end */

/* constant begin */
#define PS_PLOT_MODE_AXIS (0x000000ff)
#define PS_PLOT_MODE_AXIS_X_AXIS_POS (0x00000001) /* 0: Down 1: Up */
#define PS_PLOT_MODE_AXIS_Y_AXIS_POS (0x00000002) /* 0: Left 1: Write */
#define PS_PLOT_MODE_AXIS (0x000000ff)

#define PS_LINE_CIRCLE_MODE (0)
#define PS_FILL_WHITE_CIRCLE_MODE (1)
#define PS_FILL_BLACK_CIRCLE_MODE (2)

#define PS_PLOT_SCALE_X_AXIS_Y_POSITION_DOWN ( -5.0)
#define PS_PLOT_SCALE_X_AXIS_Y_POSITION_UP   (105.0)
#define PS_PLOT_SCALE_X_AXIS_LENGTH     (1.0)
/* constant end */

/* struct begin */
typedef struct psPlotInfo {
    psParaTypeReal scaleX;
    psParaTypeReal scaleY;
    psParaTypeReal translateX;
    psParaTypeReal translateY;

    psParaTypeReal dX;
    psParaTypeReal dXValue;
    psParaTypeReal minX;
    psParaTypeReal centreX;
    psParaTypeReal maxX;
    char*          labelX;

    psParaTypeReal dY;
    psParaTypeReal dYValue;
    psParaTypeReal minY;
    psParaTypeReal centreY;
    psParaTypeReal maxY;
    char*          labelY;

    psParaTypeInteger nData;
    psParaTypeReal *data;
} psPlotInfo;
/* struct end */

#ifdef __cplusplus
extern "C" {
#endif 

/* prototype begin */

/* in psFileInit.c */
extern void psFileInit(psFile* ps, psParaTypeInteger mode);

/* in psFilePage.c */
extern void psFilePageStart(psFile* ps, psParaTypeInteger mode);
extern void psFilePageEnd(psFile* ps, psParaTypeInteger mode);

/* in psFileEnd.c */
extern void psFileEnd(psFile* ps);

/* in psFileImage.c */
extern void psFileImage            (psFile* ps, psImageInfo im, psParaTypeInteger mode);
extern void psFileImageByCircles   (psFile* ps, psImageInfo im, psParaTypeInteger mode);
extern void psFileImageCentre      (psFile* ps, psImageInfo im, psParaTypeInteger mode);
extern void psFileImageScale       (psFile* ps, psImageInfo im, psParaTypeInteger mode);
extern void psFileImageSpaceSet    (psFile* ps, psImageInfo im, psParaTypeInteger mode);
extern void psFileImageSpaceRotateSet    (psFile* ps, psImageInfo im, psParaTypeInteger mode);
extern void psFileImageSpaceRestore(psFile* ps, psImageInfo im, psParaTypeInteger mode);
extern void psFileImageSpaceRotateRestore(psFile* ps, psImageInfo im, psParaTypeInteger mode);

/* in psFileLine.c */
extern void psFileLineWidthSet     (psFile* ps, float lineWidth);
extern void psFileLineDraw(psFile* ps, float x1,float y1,float x2,float y2);
extern void psFileDendgramLineDraw(psFile* ps, float width,float height1, float height2, float x, float y);

/* in psFileString.c */
extern void psFileStringStatusSet(psFile* ps, char* fontname, double fontsize);
extern void psFileStringDefaultStatusSet(psFile* ps);
extern void psFileString (psFile* ps, char* message, double x, double y, psParaTypeInteger mode);

/* in psFileContour.c */
extern void psFileContour(psFile* ps, psImageInfo im, psParaTypeInteger mode);
/* in psFileCircle.c */
extern void psFileCircleCreate(psFile* ps, float cx, float cy, float r, long mode);



/* in psFileRead.c */
extern void psFileRead(psFile* ps, FILE* fpt, long mode);


/* in psFileUtil.c */
extern long psFileIsStartPage(psFile* ps, char* s);
extern long psFileIsEndPage(psFile* ps, char* s);

/* prototype end */

#ifdef __cplusplus
};
#endif
#endif /* PS_FILE_H */