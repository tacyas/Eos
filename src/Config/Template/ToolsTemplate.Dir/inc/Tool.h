#ifndef TOOL_H
#define TOOL_H
/* 
* llExtract.h
*/

#include <stdio.h>
#include "llData.h"
#include "genUtil.h"

#define THIS_PROGRAM llExtract
#define THIS_ROUTINE lllExtract

#define OPTION_FLAG      '-'
#define OPTION_FLAG_POS  (0)
#define OPTION_POS       (1)
#define FILENAME_LENGTH  (1024)
#define DEFAULT_MODE     (0xffffffff)
#define TITLE_LENGTH     (80)
#define MAX_LEVEL        (100)
#define SectionMark      " ,"

#ifdef GLOBAL_DECLACATION
#else
#endif

typedef struct THIS_PROGRAM\
Info{
	long  flagRedirect;

    char  inFileName[FILENAME_LENGTH];
    FILE* fptIn;
	long flagInFile;
    char  outFileName[FILENAME_LENGTH];
    FILE* fptOut;
	long flagOutFile;

	long layer;
	long mode;
} THIS_PROGRAM\
Info;

/* in ../src/mrcImageROI.c */

/* util.c */

/* in init.c */
extern void init0(THIS_PROGRAM\
Info* info);
extern void init1(THIS_PROGRAM\
Info* info);
/* in argCheck.c */
extern void argCheck(THIS_PROGRAM\
Info* info, int argc, char* argv[]);
/* in usage.c */
extern void usage(char* thisProgram);


/* Interpolation Function in ../src/mrcImageROI.c */
extern double nearestNeighborInterpolation(double* image, 
                               unsigned long nx, unsigned long ny,
                               double x, double y);

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

#endif /* TOOL */
