/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% Vector.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : Vector.h 
#%Z% Attention
#%Z%
*/

#ifndef VECTOR_H
#define VECTOR_H

/* struct begin */
typedef struct floatVector {
	unsigned long size;
	float*        data;
} floatVector;

typedef struct intVector {
	unsigned long size;
	int*        data;
} intVector;

typedef struct doubleVector {
	unsigned long size;
	double*        data;
} doubleVector;

/* struct end */

extern floatVector* floatVectorInit(floatVector* v, long size);
extern floatVector* floatVectorFree(floatVector* v);

extern intVector* intVectorInit(intVector* v, long size);
extern intVector* intVectorFree(intVector* v);


extern floatVector* floatVectorAdd(floatVector* v, floatVector* u, floatVector* w);
extern floatVector* floatVectorMinus(floatVector* v, floatVector* u, floatVector* w);

extern double floatVectorScalarProduct(floatVector* x, floatVector* y);
extern double lfloatVectorLength(floatVector* x);

extern void lVectorSplineTableMake(floatVector* x, floatVector* y, floatVector* z);

extern double lVectorSpline(double t, floatVector* x, floatVector* y, floatVector* z);

extern void lVectorSplineTable2DMake(floatVector* p, floatVector* x, floatVector* y, floatVector* a, floatVector* b);
extern void lVectorSpline2D(double t, double* px, double* py, 
floatVector* p, floatVector* x, floatVector* y,
floatVector* a, floatVector* b);

extern doubleVector* doubleVectorInit(doubleVector* v, long size);
extern doubleVector* doubleVectorFree(doubleVector* v);
extern doubleVector* doubleVectorAdd(doubleVector* v, doubleVector* u, doubleVector* w);
extern doubleVector* doubleVectorMinus(doubleVector* v, doubleVector* u, doubleVector* w);

extern double doubleVectorScalarProduct(doubleVector* x, doubleVector* y);
extern double ldoubleVectorLength(doubleVector* x);

extern void ldoubleVectorSplineTableMake(doubleVector* x, doubleVector* y, doubleVector* z);

extern double ldoubleVectorSpline(double t, doubleVector* x, doubleVector* y, doubleVector* z);

extern void ldoubleVectorSplineTable2DMake(doubleVector* p, doubleVector* x, doubleVector* y, doubleVector* a, doubleVector* b);
extern void ldoubleVectorSpline2D(double t, double* px, double* py, 
doubleVector* p, doubleVector* x, doubleVector* y,
doubleVector* a, doubleVector* b);
/* prototype begin */

#endif /* VECTOR_H */