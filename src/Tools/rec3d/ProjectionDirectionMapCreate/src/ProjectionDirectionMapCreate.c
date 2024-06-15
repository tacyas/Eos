/*
# ProjectionDirectionMapCreate : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : ProjectionDirectionMapCreate
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "Matrix3D.h"
#define WORDLEN 1024

typedef struct lProjectionDirectionMapCreateInfo {
	int LineNum;
	char** FileName;
	char** RotationalMode;
	float* Phi;
	float* Theta;
	float* Psi;
	double* x;
	double* y;
	double* x2;
	double* y2;
	int numP;
	int numM;
	int OutputMode;
	int mode;
} lProjectionDirectionMapCreateInfo;

/*
typedef enum lProjectionDirectionMapCreateMode {
	a=0,
	b=1
} lProjectionDirectionMapCreateMode;
*/

void
__InputDataFileListRead(lProjectionDirectionMapCreateInfo* linfo, FILE* fpt, int mode);

void
__RotationalModeChange(lProjectionDirectionMapCreateInfo* linfo, int mode);

void
lProjectionDirectionMapCreate(lProjectionDirectionMapCreateInfo* linfo, int mode);

void
__OutputFileWrite(lProjectionDirectionMapCreateInfo* linf, FILE* fpt, int mode);

int
main(int argc, char* argv[]) 
{
	ProjectionDirectionMapCreateInfo  info;
	lProjectionDirectionMapCreateInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	if(info.flagOut == 1) linfo.OutputMode = 0;
	if(info.flagPs  == 1) linfo.OutputMode = 1;
	linfo.mode = info.mode;

	fprintf(stderr, "%d\n",linfo.mode);

	__InputDataFileListRead(&linfo, info.fptIn, 0);
	switch(info.Rmode){
		case 0 :
		break;
		case 1 :
			__RotationalModeChange(&linfo, 0);
		break;
	}
	lProjectionDirectionMapCreate(&linfo, 0);
	switch(linfo.OutputMode){
		case 0 :
			__OutputFileWrite(&linfo, info.fptOut, 0);
			break;
		case 1 :
			fprintf(stderr, "Not supported this mode");
			exit(1);
			break;
	}

	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Rotational Mode -----\n");
	fprintf(stderr, "Final rotation of projection is only Z .\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- input file format -----\n");
	fprintf(stderr, "filename rotationalmode angle angle angle\n");
	fprintf(stderr, "   .             .        .     .     .  \n");
	fprintf(stderr, "   .             .        .     .     .  \n");
	fprintf(stderr, "   .             .        .     .     .  \n");
	fprintf(stderr, "   .             .        .     .     .  \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "-m : 0 : Not separate plus and minus of theta. Create one line data\n");
	fprintf(stderr, "     1 :     separate plus and minus of theta. Create one line data\n");
	fprintf(stderr, "     2 :     separate plus and minus of theta. Create two line data\n");
	fprintf(stderr, "     3 : Mollweide expressionn");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "-Rm : 0 : Not change rotational mode\n");
	fprintf(stderr, "      1 :     Change rotational mode to ZONS\n");
	fprintf(stderr, "\n");
}

void
__InputDataFileListRead(lProjectionDirectionMapCreateInfo* linfo, FILE* fpt, int mode)
{
	int i;
	char *s;

	fseek(fpt, 0L, SEEK_SET);
	s = MemoryAllocate(char, WORDLEN, "in __InputDataFileListRead");
	linfo->LineNum = 0;
	while(fgets(s, WORDLEN-1, fpt) != NULL){
		linfo->LineNum++;
	}
	fseek(fpt, 0L, SEEK_SET);

	linfo->FileName       = MemoryAllocate(char*, linfo->LineNum, "in __InputDataFileListRead");
	linfo->RotationalMode = MemoryAllocate(char*, linfo->LineNum, "in __InputDataFileListRead");
	for(i=0; i<linfo->LineNum; i++){
		linfo->FileName[i]       = MemoryAllocate(char, 256, "in __InputDataFileListRead");
		linfo->RotationalMode[i] = MemoryAllocate(char, 5,   "in __InputDataFileListRead");
	}
	linfo->Phi   = MemoryAllocate(float, linfo->LineNum, "in __InputDataFileListRead");
	linfo->Theta = MemoryAllocate(float, linfo->LineNum, "in __InputDataFileListRead");
	linfo->Psi   = MemoryAllocate(float, linfo->LineNum, "in __InputDataFileListRead");

	for(i=0; i<linfo->LineNum; i++){
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(linfo->FileName[i],       stringGetNthWord(s, 1, " ,\t"), 255);
		stringCopy(linfo->RotationalMode[i], stringGetNthWord(s, 2, " ,\t"),   5);
		linfo->Phi[i]   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		linfo->Theta[i] = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
		linfo->Psi[i]   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
	}
	free(s);
}

void
__RotationalModeChange(lProjectionDirectionMapCreateInfo* linfo, int mode)
{
	int i, j;
	Matrix3D Matrix;
	matrix3DParaTypeReal x, y, z;

	for(i=0; i<linfo->LineNum; i++){
		matrix3DRotationSetFollowingEulerAngle(Matrix,
										       linfo->RotationalMode[i],
											   linfo->Phi[i],
											   linfo->Theta[i],
											   linfo->Psi[i],
											   MATRIX_3D_MODE_INITIALIZE);
		matrix3DEulerAngleGetFromMatrix3D(Matrix, "ZONS", &x, &y, &z, 0);
		linfo->Phi[i]   = x;
		linfo->Theta[i] = y;
		linfo->Psi[i]   = z;
		fprintf(stderr, "%f %f %f\n",linfo->Phi[i]*DEGREE, linfo->Theta[i]*DEGREE, linfo->Psi[i]*DEGREE);
	}
}

void
lProjectionDirectionMapCreate(lProjectionDirectionMapCreateInfo* linfo, int mode)
{
	int    i, j, k;
	double radius;
	int flag;

	linfo->x = MemoryAllocate(double, linfo->LineNum, "in lProjectionDirectionMapCreate");
	linfo->y = MemoryAllocate(double, linfo->LineNum, "in lProjectionDirectionMapCreate");
	j = 0;
	k = 0;
	for(i=0; i<linfo->LineNum; i++){
		flag = 0;
		switch(linfo->mode){
			case 0 :
				radius  = linfo->Theta[i]*DEGREE;
				if(radius < 0)   radius += 360;
				if(radius > 180) radius -= 180;
				if(radius > 90)   radius = 180 - radius;
				
				radius = 90 - radius;

				linfo->x[i] = radius*cos((double)linfo->Phi[i]);
				linfo->y[i] = radius*sin((double)linfo->Phi[i]);
			break;
			case 1:
				if(linfo->Theta[i]*DEGREE < 0) radius = linfo->Theta[i]*DEGREE + 360;
				else                           radius = linfo->Theta[i]*DEGREE;
				
				if(radius > 180) radius -= 180;
				if(radius > 90){
					radius = 180 - radius;
					flag = 1;
				}
				
				radius = 90 - radius;
				
				if(flag == 0){
					linfo->x[i] = radius*cos((double)(linfo->Phi[i]/2));
					linfo->y[i] = radius*sin((double)(linfo->Phi[i]/2));
				}
				else{
					linfo->x[i] = radius*cos((double)(linfo->Phi[i]/2+M_PI));
					linfo->y[i] = radius*sin((double)(linfo->Phi[i]/2+M_PI));
				}
			break;
			case 2 :
				linfo->x2 = MemoryAllocate(double, linfo->LineNum, "in lProjectionDirectionMapCreate");
				linfo->y2 = MemoryAllocate(double, linfo->LineNum, "in lProjectionDirectionMapCreate");
				if(linfo->Theta[i]*DEGREE < 0) radius = linfo->Theta[i]*DEGREE + 360;
				else                           radius = linfo->Theta[i]*DEGREE;
				
				if(radius > 180) radius -= 180;
				if(radius > 90){
					radius = 180 - radius;
					flag = 1;
				}
				
				radius = 90 - radius;
				
				if(flag == 0){
					linfo->x[j] = radius*cos((double)(linfo->Phi[i]));
					linfo->y[j] = radius*sin((double)(linfo->Phi[i]));
					j++;
				}
				else{
					linfo->x2[k] = radius*cos((double)(linfo->Phi[i]));
					linfo->y2[k] = radius*sin((double)(linfo->Phi[i]));
					k++;
				}
			break;
			case 3 :
			break;
		}
	}
	switch(linfo->mode){
		case 2 :
			linfo->numP = j;
			linfo->numM = k;
		break;
	}
}

void
__OutputFileWrite(lProjectionDirectionMapCreateInfo* linfo, FILE* fpt, int mode)
{
	int i;
	int max;

	switch(linfo->mode){
		case 0 :
		case 1 :
			for(i=0; i<linfo->LineNum; i++){
				fprintf(fpt, "%6.2f,%6.2f\n", linfo->x[i], linfo->y[i]);
			}
		break;
		case 2 :
			if(linfo->numP > linfo->numM){
				max = linfo->numP;
				for(i=0; i<max; i++){
					if(i > linfo->numM){
						fprintf(fpt, "%6.2f,%6.2f\n",linfo->x[i], linfo->y[i]);
					}
					else{
						fprintf(fpt, "%6.2f,%6.2f \t %6.2f,%6.2f\n",linfo->x[i], linfo->y[i], linfo->x2[i], linfo->y2[i]);
					}
				}
			}
			else{
				max = linfo->numM;
				for(i=0; i<max; i++){
					if(i > linfo->numP){
						fprintf(fpt, "              \t %6.2f,%6.2f\n",linfo->x2[i], linfo->y2[i]);
					}
					else{
						fprintf(fpt, "%6.2f,%6.2f \t %6.2f,%6.2f\n",linfo->x[i], linfo->y[i], linfo->x2[i], linfo->y2[i]);
					}
				}
			}
		break;
		case 3 :
			for(i=0; i<linfo->LineNum; i++){
				fprintf(fpt, "%7.2f,%7.2f\n", linfo->x[i], linfo->y[i]);
			}
		break;
	}
}
