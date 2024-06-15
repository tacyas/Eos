#ifndef MATRIX_3D_H
#define MATRIX_3D_H
/*
# Matrix3D.h  1.13
# The latest update : 10/01/97 at 02:34:25
#
#@(#) Matrix3D.h ver 1.13
#@(#) Created by 
#@(#)
#@(#) Usage : Matrix3D.h 
#t@(#) Attention
#@(#)
*/
/* constant begin */
#define MATRIX_3D_WIDTH  4 
#define MATRIX_3D_HEIGHT 4

#define MATRIX_3D_MODE_NOT_INITIALIZE 0
#define MATRIX_3D_MODE_INITIALIZE 1

#define MATRIX_3D_NEGLECT_VALUE 1e-6 

/* constant end */

/* struct begin */
typedef float matrix3DParaTypeReal;
typedef matrix3DParaTypeReal Matrix3D[MATRIX_3D_WIDTH][MATRIX_3D_HEIGHT];

typedef char  matrix3DEulerAngleMode;

typedef struct EulerAngleInfo {
	char   EAMode[5];
	double Rot1;
	double Rot2;
	double Rot3;
} EulerAngleInfo;

/* struct end */

/*
	Matrix3D: Attention Arrays Order

	[0][0] [1][0] [2][0] [3][0]
	[0][1] [1][1] [2][1] [3][1]
	[0][2] [1][2] [2][2] [3][2]
	[0][3] [1][3] [2][3] [3][3]
*/

#include "Vector.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void matrix3DInit(Matrix3D Matrix);

/* matrix3DUtil.c */
#include "Array.h"
extern void matrix3DCopy(Matrix3D dst, Matrix3D src);

extern void matrix3DFromRotationMatrix(Matrix3D dst, Array a);
extern void matrix3DInverse(Matrix3D mat);

extern void matrix3DMultiply(Matrix3D A, Matrix3D B);     /* A = A*B */
extern void matrix3DMultiplyInv(Matrix3D A, Matrix3D B);  /* B = A*B */

extern void matrix3DMultiplyVector(floatVector* v, Matrix3D A);
extern void matrix3DMultiplyVectors(floatVector* vs, int n, Matrix3D A);

extern void matrix3DFileFormat(FILE* fpt);
extern void matrix3DFileRead(FILE* fpt, Matrix3D Matrix);
extern void matrix3DFileWrite(FILE* fpt, Matrix3D Matrix);


extern void matrix3DRotationSet(Matrix3D Matrix, char mode, matrix3DParaTypeReal rot, long Mode);
extern void matrix3DTranslationSet(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode);
extern void matrix3DRotationSetXYZ(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode);
extern void matrix3DRotationSetZYX(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode);
extern void matrix3DRotationSetZXY(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode);
extern void matrix3DRotationSetYXZ(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode);

/*
 *
*/
extern void matrix3DRotationSetFollowingEulerAngle(Matrix3D Matrix, const char Mode[4], matrix3DParaTypeReal rot1, matrix3DParaTypeReal rot2, matrix3DParaTypeReal rot3, long mode);
extern void matrix3DRotationAntiSetFollowingEulerAngle(Matrix3D Matrix, const char Mode[4], matrix3DParaTypeReal rot1, matrix3DParaTypeReal rot2, matrix3DParaTypeReal rot3, long mode);
extern void matrix3DEulerAngleGetFromMatrix3D(Matrix3D Matrix, const char Mode[4], matrix3DParaTypeReal* rot1, matrix3DParaTypeReal* rot2, matrix3DParaTypeReal* rot3, long mode);

/*
*/
extern void matrix3DScale(Matrix3D, double ratio);

/* prototype end */

#ifdef __cplusplus
};
#endif

/*** Definitions ***/
/* struct begin */
typedef struct {float x, y, z, w;} Quat; /* Quaternion */
typedef matrix3DParaTypeReal HMatrix3D[4][4];
typedef Quat EulerAngles;    /* (x,y,z)=ang 1,2,3, w=order code  */
/* struct end */
/* constant begin */
enum QuatPart {X, Y, Z, W};
/* constant end */

/* by Ken Shoemake, 1993 */
/*** Order type constants, constructors, extractors ***/
    /* There are 24 possible conventions, designated by:       */
    /*	  o EulAxI = axis used initially                   : 3 */
    /*	  o EulPar = parity of axis permutation            : 2 */
    /*	  o EulRep = repetition of initial axis as last	   : 2 */
    /*	  o EulFrm = frame from which axes are taken	   : 2 */
    /* Axes I,J,K will be a permutation of X,Y,Z.              */
    /* Axis H will be either I or K, depending on EulRep.      */
    /* Frame S takes axes from initial static frame.	       */
    /* If ord = (AxI=X, Par=Even, Rep=No, Frm=S), then	       */
    /* {a,b,c,ord} means Rz(c)Ry(b)Rx(a), where Rz(c)v	       */
    /* rotates v around Z by c radians.			               */

/* constant begin */
#define EulFrmS	     0
#define EulFrmR	     1
#define EulFrm(ord)  ((unsigned)(ord)&1)
#define EulRepNo     0
#define EulRepYes    1
#define EulRep(ord)  (((unsigned)(ord)>>1)&1)
#define EulParEven   0
#define EulParOdd    1
#define EulPar(ord)  (((unsigned)(ord)>>2)&1)
#define EulSafe	     "\000\001\002\000"
#define EulNext	     "\001\002\000\001"
/* constant end */

/* prototype begin */
#define EulAxI(ord)  ((int)(EulSafe[(((unsigned)(ord)>>3)&3)]))
#define EulAxJ(ord)  ((int)(EulNext[EulAxI(ord)+(EulPar(ord)==EulParOdd)]))
#define EulAxK(ord)  ((int)(EulNext[EulAxI(ord)+(EulPar(ord)!=EulParOdd)]))
#define EulAxH(ord)  ((EulRep(ord)==EulRepNo)?EulAxK(ord):EulAxI(ord))
    /* EulGetOrd unpacks all useful information about order simultaneously. */
#define EulGetOrd(ord,i,j,k,h,n,s,f) {unsigned o=ord;f=o&1;o>>=1;s=o&1;o>>=1;\
    n=o&1;o>>=1;i=EulSafe[o&3];j=EulNext[i+n];k=EulNext[i+1-n];h=s?k:i;}
    /* EulOrd creates an order value between 0 and 23 from 4-tuple choices. */
#define EulOrd(i,p,r,f)	   (((((((i)<<1)+(p))<<1)+(r))<<1)+(f))
    /* Static axes */
#define EulOrdXYZs    EulOrd(X,EulParEven,EulRepNo,EulFrmS)
#define EulOrdXYXs    EulOrd(X,EulParEven,EulRepYes,EulFrmS)
#define EulOrdXZYs    EulOrd(X,EulParOdd,EulRepNo,EulFrmS)
#define EulOrdXZXs    EulOrd(X,EulParOdd,EulRepYes,EulFrmS)
#define EulOrdYZXs    EulOrd(Y,EulParEven,EulRepNo,EulFrmS)
#define EulOrdYZYs    EulOrd(Y,EulParEven,EulRepYes,EulFrmS)
#define EulOrdYXZs    EulOrd(Y,EulParOdd,EulRepNo,EulFrmS)
#define EulOrdYXYs    EulOrd(Y,EulParOdd,EulRepYes,EulFrmS)
#define EulOrdZXYs    EulOrd(Z,EulParEven,EulRepNo,EulFrmS)
#define EulOrdZXZs    EulOrd(Z,EulParEven,EulRepYes,EulFrmS)
#define EulOrdZYXs    EulOrd(Z,EulParOdd,EulRepNo,EulFrmS)
#define EulOrdZYZs    EulOrd(Z,EulParOdd,EulRepYes,EulFrmS)
    /* Rotating axes */
#define EulOrdZYXr    EulOrd(X,EulParEven,EulRepNo,EulFrmR)
#define EulOrdXYXr    EulOrd(X,EulParEven,EulRepYes,EulFrmR)
#define EulOrdYZXr    EulOrd(X,EulParOdd,EulRepNo,EulFrmR)
#define EulOrdXZXr    EulOrd(X,EulParOdd,EulRepYes,EulFrmR)
#define EulOrdXZYr    EulOrd(Y,EulParEven,EulRepNo,EulFrmR)
#define EulOrdYZYr    EulOrd(Y,EulParEven,EulRepYes,EulFrmR)
#define EulOrdZXYr    EulOrd(Y,EulParOdd,EulRepNo,EulFrmR)
#define EulOrdYXYr    EulOrd(Y,EulParOdd,EulRepYes,EulFrmR)
#define EulOrdYXZr    EulOrd(Z,EulParEven,EulRepNo,EulFrmR)
#define EulOrdZXZr    EulOrd(Z,EulParEven,EulRepYes,EulFrmR)
#define EulOrdXYZr    EulOrd(Z,EulParOdd,EulRepNo,EulFrmR)
#define EulOrdZYZr    EulOrd(Z,EulParOdd,EulRepYes,EulFrmR)

EulerAngles Eul_(float ai, float aj, float ah, int order);
Quat Eul_ToQuat(EulerAngles ea);
void Eul_ToHMatrix(EulerAngles ea, HMatrix3D M);
EulerAngles Eul_FromHMatrix(HMatrix3D M, int order);
EulerAngles Eul_FromQuat(Quat q, int order);
/* prototype end */

#endif /* MATRIX_3D_H */