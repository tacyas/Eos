#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

/* constant begin */
#define ARRAY_MAX_DIMENSION (5)
#define ARRAY_MIN_DIMENSION (1)

#define ARRAY_SEPARATOR " \t\n,"
/* constant end */

/* struct begin */
typedef unsigned long arrayParaTypeInteger;
typedef float         arrayParaTypeReal;

typedef struct Array {
	arrayParaTypeInteger dim;
	arrayParaTypeInteger n[ARRAY_MAX_DIMENSION];
	arrayParaTypeReal*   A;
} Array;
/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */ 
extern void arrayInit(Array* a, char* message);
extern void arrayFree(Array* a, char* message);
extern void arrayReadFromFile(FILE* fpt, Array* a, char* message);
extern void arrayWriteToFile(FILE* fpt, Array* a, char* message);

// mode: 0 
//  memoryAllocate u, C, lambda, ave;	
//       0<
//  Not Allocate
extern void arrayPCA(Array* u, Array* C, Array* lambda, Array* X, Array* ave, int mode);
extern void arrayPCATransform(Array* XX, Array* X, Array* ave, Array* u, int mode);
extern void arrayPCAPrint(FILE* fpt, Array* u, Array* lambda, int mode);

/* arrayInfo.c */
extern void arrayFormatInfoPrint(FILE* fpt, int mode);

#define arrayDataGet1(a,i0)             ((a).A[(i0)])
#define arrayDataGet2(a,i0,i1)          ((a).A[(i0) \
										+(i1)*(a).n[0]])
#define arrayDataGet3(a,i0,i1,i2)       ((a).A[i0 \
										+(i1)*(a).n[0] \
										+(i2)*(a).n[0]*(a).n[1]])
#define arrayDataGet4(a,i0,i1,i2,i3)    ((a).A[i0 \
										+(i1)*(a).n[0] \
										+(i2)*(a).n[0]*(a).n[1] \
										+(i3)*(a).n[0]*(a).n[1]*(a).n[2]])
#define arrayDataGet5(a,i0,i1,i2,i3,i4) ((a).A[i0 \
										+(i1)*(a).n[0] \
										+(i2)*(a).n[0]*(a).n[1] \
										+(i3)*(a).n[0]*(a).n[1]*(ai).n[2] \
										+(i4)*(a).n[0]*(a).n[1]*(a).n[2]*(a).n[3]])

#define arrayDataSet1(a,i0,data)        (a).A[(i0)]=(data)
#define arrayDataSet2(a,i0,i1,data)     (a).A[(i0) \
									 	+(i1)*(a).n[0]]=(data)
#define arrayDataSet3(a,i0,i1,i2,data)  (a).A[i0 \
										+(i1)*(a).n[0] \
										+(i2)*(a).n[0]*(a).n[1]]=(data)
#define arrayDataSet4(a,i0,i1,i2,i3,data)    (a).A[i0 \
										+(i1)*(a).n[0] \
										+(i2)*(a).n[0]*(a).n[1] \
										+(i3)*(a).n[0]*(a).n[1]*(a).n[2]]=(data)
#define arrayDataSet5(a,i0,i1,i2,i3,i4,data)    (a).A[i0 \
										+(i1)*(a).n[0] \
										+(i2)*(a).n[0]*(a).n[1] \
										+(i3)*(a).n[0]*(a).n[1]*(a).n[2] \
										+(i4)*(a).n[0]*(a).n[1]*(a).n[2]*(a).n[3]]=(data)

/* prototype end */
#ifdef __cplusplus
};
#endif

#endif /* ARRAY_H */
