/*
# lCommonLineCalculation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lCommonLineCalculation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/

#undef DEBUG
#include "genUtil.h"
#include "lCommonLineCalculation.h"


void
lCommonLineCalculation(lCommonLineCalculationInfo* linfo, int i, int mode);

double
lCommonLineCalculation1(lCommonLineCalculationInfo* linfo, int i, int mode);

void
lCommonLineCalculation(lCommonLineCalculationInfo* linfo, int i, int mode)
{
	double   xa, ya, xb, yb;
    double   Squarexa, Squareya;
    double   Squarexb, Squareyb;
    double   SquareRoota, SquareRootb;
    double   Xa, Ya, Xb, Yb;
    Matrix3D matrix1;
    Matrix3D matrix2;

    matrix3DRotationAntiSetFollowingEulerAngle(matrix1,
                                           linfo->I1RotationalMode[i],
                                           linfo->I1Angle1[i],
                                           linfo->I1Angle2[i],
                                           linfo->I1Angle3[i],
                                           MATRIX_3D_MODE_INITIALIZE);

    matrix3DRotationAntiSetFollowingEulerAngle(matrix2,
                                           linfo->I2RotationalMode[i],
                                           linfo->I2Angle1[i],
                                           linfo->I2Angle2[i],
                                           linfo->I2Angle3[i],
                                           MATRIX_3D_MODE_INITIALIZE);

     ya = ((matrix2[1][0]*matrix2[0][1]-matrix2[0][0]*matrix2[1][1])*(matrix2[0][0]*matrix1[0][2]-matrix1[0][0]*matrix2[0][2]))
         -((matrix2[0][0]*matrix2[1][2]-matrix2[1][0]*matrix2[0][2])*(matrix1[0][0]*matrix2[0][1]-matrix2[0][0]*matrix1[0][1]));

     xa = ((matrix2[0][0]*matrix2[1][2]-matrix2[1][0]*matrix2[0][2])*(matrix1[1][0]*matrix2[0][1]-matrix2[0][0]*matrix1[1][1]))
         -((matrix2[1][0]*matrix2[0][1]-matrix2[0][0]*matrix2[1][1])*(matrix2[0][0]*matrix1[1][2]-matrix1[1][0]*matrix2[0][2]));

     Squarexa = SQR(xa);
     Squareya = SQR(ya);

     SquareRoota = SQRT(Squarexa+Squareya);

     if(SquareRoota == 0){
		Xa = 1;
        Ya = 0;
        linfo->flag[i] = 1;
     }
     else{
        Xa = xa/SquareRoota;
        Ya = ya/SquareRoota;
        if(Ya < 0){
			Ya *= -1;
            Xa *= -1;
        }
        if(Xa == -1){
            Xa *= -1;
        }
		linfo->flag[i] = 0;
     }

     xb = ((matrix1[0][0]*matrix1[1][2]-matrix1[1][0]*matrix1[0][2])*(matrix2[1][0]*matrix1[0][1]-matrix1[0][0]*matrix2[1][1]))
         -((matrix1[1][0]*matrix1[0][1]-matrix1[0][0]*matrix1[1][1])*(matrix1[0][0]*matrix2[1][2]-matrix2[1][0]*matrix1[0][2]));

     yb = ((matrix1[1][0]*matrix1[0][1]-matrix1[0][0]*matrix1[1][1])*(matrix1[0][0]*matrix2[0][2]-matrix2[0][0]*matrix1[0][2]))
         -((matrix1[0][0]*matrix1[1][2]-matrix1[1][0]*matrix1[0][2])*(matrix2[0][0]*matrix1[0][1]-matrix1[0][0]*matrix2[0][1]));

     Squarexb = SQR(xb);
     Squareyb = SQR(yb);

     SquareRootb = SQRT(Squarexb+Squareyb);

     if(SquareRootb == 0 && linfo->flag[i] == 1){
		yb = (matrix1[0][0]*matrix2[0][1]-matrix2[0][0]*matrix1[0][1])/(matrix2[1][0]*matrix2[0][1]-matrix2[0][0]*matrix2[1][1]);
        xb = (matrix1[0][0]*matrix2[1][1]-matrix2[1][0]*matrix1[0][1])/(matrix2[0][0]*matrix2[1][1]-matrix2[1][0]*matrix2[0][1]);

        Squarexb = SQR(xb);
        Squareyb = SQR(yb);

        SquareRootb = SQRT(Squarexb+Squareyb);

        Xb = xb/SquareRootb;
        Yb = yb/SquareRootb;

        if(Yb < 0){
			Yb *= -1;
            Xb *= -1;
        }
        if(Xb == -1){
            Xb *= -1;
        }
     }
	 else{
	    Xb = xb/SquareRootb;
        Yb = yb/SquareRootb;
        if(Yb < 0){
            Yb *= -1;
            Xb *= -1;
        }
        if(Xa == -1){
            Xa *= -1;
        }
     }

     linfo->CLAngleOnI2AgainstI1[i] = atan2(Ya, Xa);
     linfo->CLAngleOnI1AgainstI2[i] = atan2(Yb, Xb);
}

double
lCommonLineCalculation1(lCommonLineCalculationInfo* linfo, int i, int mode)
{
	floatVector x1v, n1v;
	floatVector x2v, n2v;
	floatVector common1V;
	floatVector common2V;
	Matrix3D Matrix1, InverseMatrix1;
	Matrix3D Matrix2, InverseMatrix2;
	float commonAngle1, commonAngle2;
	double value;

	floatVectorInit(&x1v, 4);
	floatVectorInit(&x2v, 4);
	floatVectorInit(&n1v, 4);
	floatVectorInit(&n2v, 4);
	floatVectorInit(&common1V, 4);
	floatVectorInit(&common2V, 4);

	n1v.data[0] = n2v.data[0] = 0.0;
	n1v.data[1] = n2v.data[1] = 0.0;
	n1v.data[2] = n2v.data[2] = 1.0;
	n1v.data[3] = n2v.data[3] = 1.0;

	matrix3DRotationAntiSetFollowingEulerAngle(Matrix1,
											   linfo->I1RotationalMode[i],
											   -linfo->I1Angle1[i],
											   -linfo->I1Angle2[i],
											   -linfo->I1Angle3[i],
											   MATRIX_3D_MODE_INITIALIZE);

	matrix3DRotationAntiSetFollowingEulerAngle(Matrix2,
											   linfo->I2RotationalMode[i],
											   -linfo->I2Angle1[i],
											   -linfo->I2Angle2[i],
											   -linfo->I2Angle3[i],
											   MATRIX_3D_MODE_INITIALIZE);
	
	matrix3DMultiplyVector(&n1v, Matrix1);
	matrix3DMultiplyVector(&n2v, Matrix2);

	DEBUGPRINT4("I1 %d: Angle(%g,%g,%g)\n",i, linfo->I1Angle1[i]*DEGREE, linfo->I1Angle2[i]*DEGREE, linfo->I1Angle3[i]*DEGREE);
	DEBUGPRINT4("I2 %d: Angle(%g,%g,%g)\n",i, linfo->I2Angle1[i]*DEGREE, linfo->I2Angle2[i]*DEGREE, linfo->I2Angle3[i]*DEGREE);
	DEBUGPRINT4("Normal 3D for I1 %d: (%g,%g,%g)\n",i, n1v.data[0],n1v.data[1],n1v.data[2]);
	DEBUGPRINT4("Normal 3D for I2 %d: (%g,%g,%g)\n",i, n2v.data[0],n2v.data[1],n2v.data[2]);

	common1V.data[0] = common2V.data[0] = (n1v.data[1]*n2v.data[2])-(n1v.data[2]*n2v.data[1]);
	common1V.data[1] = common2V.data[1] = (n1v.data[2]*n2v.data[0])-(n1v.data[0]*n2v.data[2]);
	common1V.data[2] = common2V.data[2] = (n1v.data[0]*n2v.data[1])-(n1v.data[1]*n2v.data[0]);
	common1V.data[3] = common2V.data[3] = 1.0;

	value = SQR(common1V.data[0])+SQR(common1V.data[1])+SQR(common1V.data[2]);
	if(value < 1.0e-8) { /* Both surfaces are parallel. */
		linfo->flag[i] = 1;
	} else{
		linfo->flag[i] = 0;

		value = sqrt(value);
		common1V.data[0] /= value;
		common1V.data[1] /= value;
		common1V.data[2] /= value;
		common2V.data[0] /= value;
		common2V.data[1] /= value;
		common2V.data[2] /= value;
		DEBUGPRINT5("CommonLine 3D %d: length: %g (%g,%g,%g)\n",i, value, common1V.data[0],common1V.data[1],common1V.data[2]);
		DEBUGPRINT5("CommonLine 3D %d: length: %g (%g,%g,%g)\n",i, value, common2V.data[0],common2V.data[1],common2V.data[2]);
		value = SQR(value);
	}

	if(linfo->flag[i] == 0) {
		matrix3DRotationSetFollowingEulerAngle(InverseMatrix1,
										   linfo->I1RotationalMode[i],
										   -linfo->I1Angle1[i],
										   -linfo->I1Angle2[i],
										   -linfo->I1Angle3[i],
										   MATRIX_3D_MODE_INITIALIZE);

		matrix3DRotationSetFollowingEulerAngle(InverseMatrix2,
										   linfo->I2RotationalMode[i],
										   -linfo->I2Angle1[i],
										   -linfo->I2Angle2[i],
										   -linfo->I2Angle3[i],
										   MATRIX_3D_MODE_INITIALIZE);

		matrix3DMultiplyVector(&common1V, InverseMatrix1);
		matrix3DMultiplyVector(&common2V, InverseMatrix2);

		commonAngle1 = atan2f(common1V.data[1], common1V.data[0]);
		if(commonAngle1 < 0){
			commonAngle1 += 2*M_PI;
		}

		commonAngle2 = atan2f(common2V.data[1], common2V.data[0]);
		if(commonAngle2 < 0){
			commonAngle2 += 2*M_PI;
		}

		DEBUGPRINT4("x-y plane on I1 against I2 %d: (%g,%g,%g)\n",i, common1V.data[0],common1V.data[1],common1V.data[2]);
		DEBUGPRINT4("x-y plane on I2 against I1 %d: (%g,%g,%g)\n",i, common2V.data[0],common2V.data[1],common2V.data[2]);

#ifdef DEBUG
		{
		double data = fabs(SQR(common1V.data[0])+SQR(common1V.data[1])-1);	
		if(1e-4<data) {
			fprintf(stderr, "Something wrong!! The common line is not on the x-y plane!! : %d %g V1 (%g,%g,%g)\n", i, sqrt(data),common1V.data[0],common1V.data[1],common1V.data[2]);
			fprintf(stderr, "Something wrong!! The common line is not on the x-y plane!! : %d %g V2 (%g,%g,%g)\n", i, sqrt(data),common2V.data[0],common2V.data[1],common2V.data[2]);
		}
		}
#endif
		linfo->CLAngleOnI1AgainstI2[i] = commonAngle1;
		linfo->CLAngleOnI2AgainstI1[i] = commonAngle2;
		DEBUGPRINT2("AngleonI1agaistI2 %d: %g\n",i, commonAngle1*DEGREE);
		DEBUGPRINT2("AngleonI2agaistI1 %d: %g\n",i, commonAngle2*DEGREE);
	} else {
		linfo->CLAngleOnI2AgainstI1[i] = 0;
		linfo->CLAngleOnI1AgainstI2[i] = 0;
	}

	floatVectorFree(&x1v);
	floatVectorFree(&x2v);
	floatVectorFree(&n1v);
	floatVectorFree(&n2v);
	floatVectorFree(&common1V);
	floatVectorFree(&common2V);
	return(value);
}

