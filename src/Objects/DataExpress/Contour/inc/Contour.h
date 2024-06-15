#ifndef CONTOUR_H
#define CONTOUR_H
/*
    contour.h
*/
#include  "genUtil.h"

#ifndef MINFLOAT
#define MINFLOAT (1e-31)
#endif

#include "mrcImage.h"
/* constant begin */
#define CONTOUR_ACCURACY  (MINFLOAT)
/* constant end */

/* struct begin */
typedef long   contourParaTypeInteger;
typedef double contourParaTypeReal;

typedef struct contourParaElement {
    contourParaTypeInteger n;
    contourParaTypeReal    Min;
    contourParaTypeReal    Max;
    contourParaTypeReal    d;
} contourParaElement;

typedef struct contourImage {
    contourParaTypeReal* image;
    contourParaTypeReal* image2;
    contourParaElement   x;
    contourParaElement   y;
    contourParaElement   z;
    contourParaElement   w;
    contourParaElement   h;
    contourParaTypeReal  section;
} contourImage;

typedef struct contourPoint {
    contourParaTypeReal    x;
    contourParaTypeReal    y;
    contourParaTypeReal    z;
} contourPoint;

typedef struct contourALine contourALine;
struct contourALine {
    contourALine* before;
    contourPoint p0;
    contourPoint p1;
    contourPoint p2;
    contourALine* next;
};

typedef struct contourLine contourLine;
struct contourLine {
    contourALine* top;
    contourALine* current;
    contourParaTypeInteger n;
    contourLine*  next;
};

typedef struct contourLines contourLines;
struct contourLines {
    contourLine*  top;
    contourLine*  current;
    contourParaTypeInteger n;
    contourLines* next;
};

typedef struct contourLinesSet contourLinesSet;
struct contourLinesSet {
    contourLines*  top;
    contourLines*  current;
    contourParaTypeInteger n;
    contourLinesSet* next;
};

typedef struct contourArgs {
    contourParaTypeReal f00;  /* For 2D Contour*/
    contourParaTypeReal f01;
    contourParaTypeReal f11;
    contourParaTypeReal f10;
    contourParaTypeReal f000; /* For 3D Contour */
    contourParaTypeReal f001;
    contourParaTypeReal f010;
    contourParaTypeReal f011;
    contourParaTypeReal f100;
    contourParaTypeReal f101;
    contourParaTypeReal f110;
    contourParaTypeReal f111;
    contourParaTypeReal x;
    contourParaTypeReal y;
    contourParaTypeReal z;
    contourParaTypeReal dx;
    contourParaTypeReal dy;
    contourParaTypeReal dz;
} contourArgs;

typedef enum contourFlag {
    contourFlagXSection,
    contourFlagYSection,
    contourFlagZSection,
    contourFlag3D
} contourFlag;
/* struct end */

/* prototype begin */
/* search contour lines in a boxel */
extern void createContourALine(contourLine* ls, contourArgs c);

/* create contour lines in order */
extern void createContourLine (contourLines*  ls, contourLine* l);

/* craete contourLines at each section */
extern void createContourLines(contourLines* ls, contourImage image);

/* create contourLines at all sections */
extern void createContour(contourLinesSet* lsset, contourImage image, contourParaTypeReal level, contourFlag flag);

extern void appendContourLine0(contourLine* l, contourParaTypeReal xc1, contourParaTypeReal yc1, contourParaTypeReal xc2, contourParaTypeReal yc2, contourParaTypeReal z);
extern void appendContourLine1(contourLine* l, contourLine* als);

extern void lmrc2contour(contourLinesSet* c, mrcImage* m, contourParaTypeReal l, contourFlag f, long mode); 
/* prototype end */

#endif /* CONTOUR_H */
