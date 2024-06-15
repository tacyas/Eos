/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% crystalUtil ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : crystalUtil 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%crystalUtil ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include "genUtil.h"
#include "../inc/Crystal.h"

void
crystalCellLengthSet(CrystalInfo* C, char axis, CrystalParaTypeReal length, int mode)
{
	switch(axis) {
		case 'a': {
			C->CellLength.a = length;
			break;
		}
		case 'b': {
			C->CellLength.b = length;
			break;
		}
		case 'c': {
			C->CellLength.c = length;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Axis: %c\n", axis);
			exit(EXIT_FAILURE);
			break;
		}
	}	
	crystalAxisSetUsingCellLength(C, axis, mode);
}

void
crystalAxisSet(CrystalInfo* C, char axis, 
	CrystalParaTypeReal x, 
	CrystalParaTypeReal y, 
	CrystalParaTypeReal z, int mode)
{

	switch(axis) {
		case 'a': {
			C->aAxis.x = x;
			C->aAxis.y = y;
			C->aAxis.z = z;
			break;
		}
		case 'b': {
			C->bAxis.x = x;
			C->bAxis.y = y;
			C->bAxis.z = z;
			break;
		}
		case 'c': {
			C->cAxis.x = x;
			C->cAxis.y = y;
			C->cAxis.z = z;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Axis: %c\n", axis);
			exit(EXIT_FAILURE);
			break;
		}
	}	
	crystalCellLengthSetUsingAxis(C, axis, mode);
}

void
crystalCellLengthSetUsingAxis(CrystalInfo* C, char axis, int mode)
{
	double length;

	switch(axis) {
		case 'a': {
			length = SQR(C->aAxis.x)+SQR(C->aAxis.y)+SQR(C->aAxis.z);
			break;
		}
		case 'b': {
			length = SQR(C->bAxis.x)+SQR(C->bAxis.y)+SQR(C->bAxis.z);
			break;
		}
		case 'c': {
			length = SQR(C->cAxis.x)+SQR(C->cAxis.y)+SQR(C->cAxis.z);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Axis: %c\n", axis);
			exit(EXIT_FAILURE);
			break;
		}
	}	
	if(0<length) {
		length = sqrt(length);
	} else {
		length = 0;
	}
	switch(axis) {
		case 'a': {
			C->CellLength.a = length;
			break;
		}
		case 'b': {
			C->CellLength.b = length;
			break;
		}
		case 'c': {
			C->CellLength.c = length;
			break;
		}
	}	
}

void
crystalAxisSetUsingCellLength(CrystalInfo* C, char axis, int mode)
{
	double length;

	switch(axis) {
		case 'a': {
			length = SQR(C->aAxis.x)+SQR(C->aAxis.y)+SQR(C->aAxis.z);
			break;
		}
		case 'b': {
			length = SQR(C->bAxis.x)+SQR(C->bAxis.y)+SQR(C->bAxis.z);
			break;
		}
		case 'c': {
			length = SQR(C->cAxis.x)+SQR(C->cAxis.y)+SQR(C->cAxis.z);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Axis: %c\n", axis);
			exit(EXIT_FAILURE);
			break;
		}
	}		
	if(0<length) {
		length = sqrt(length);
	} else {
		fprintf(stderr, "No information of %c-Axis direction : in crystalAxisSetUsingCellLength\n", axis);
		exit(EXIT_FAILURE);
	}
	switch(axis) {
		case 'a': {
			C->aAxis.x = C->aAxis.x/length*C->CellLength.a;	
			C->aAxis.y = C->aAxis.y/length*C->CellLength.a;	
			C->aAxis.z = C->aAxis.z/length*C->CellLength.a;	
			break;
		}
		case 'b': {
			C->bAxis.x = C->bAxis.x/length*C->CellLength.b;		
			C->bAxis.y = C->bAxis.y/length*C->CellLength.b;	
			C->bAxis.z = C->bAxis.z/length*C->CellLength.b;	
			break;
		}
		case 'c': {
			C->cAxis.x = C->cAxis.x/length*C->CellLength.c;		
			C->cAxis.y = C->cAxis.y/length*C->CellLength.c;	
			C->cAxis.z = C->cAxis.z/length*C->CellLength.c;	
			break;
		}
	}		
}

void
crystalSpaceGroupPrint(FILE* fpt, int mode)
{
	int i;

	i=0;
	while(NULL!=CrystalSpaceGroupString[i]) {
		fprintf(fpt, "%5d %s\n", i, CrystalSpaceGroupString[i]);	
		i++;
	}
}


double
crystalInfoGetLatticeVolume(CrystalInfo* info, int mode)
{
    double V;
    V = info->aAxis.x*(info->bAxis.y*info->cAxis.z - info->cAxis.y*info->bAxis.z)
      + info->aAxis.y*(info->bAxis.z*info->cAxis.x - info->cAxis.z*info->bAxis.x)
      + info->aAxis.z*(info->bAxis.x*info->cAxis.y - info->cAxis.x*info->bAxis.y);
    return V;
}

void
crystalInfoGetReciprocalLattice(CrystalInfo* info, int mode) 
{
    double V;

    switch(mode) {
        case 0: // Real -> Reciprocal
            V = crystalInfoGetLatticeVolume(info, 0); 
            info->aReciprocalAxis.x = (info->bAxis.y*info->cAxis.z - info->cAxis.y*info->bAxis.z)/V; 
            info->aReciprocalAxis.y = (info->bAxis.z*info->cAxis.x - info->cAxis.z*info->bAxis.x)/V; 
            info->aReciprocalAxis.z = (info->bAxis.x*info->cAxis.y - info->cAxis.x*info->bAxis.y)/V;
            info->bReciprocalAxis.x = (info->cAxis.y*info->aAxis.z - info->aAxis.y*info->cAxis.z)/V; 
            info->bReciprocalAxis.y = (info->cAxis.z*info->aAxis.x - info->aAxis.z*info->cAxis.x)/V; 
            info->bReciprocalAxis.z = (info->cAxis.x*info->aAxis.y - info->aAxis.x*info->cAxis.y)/V; 
            info->cReciprocalAxis.x = (info->aAxis.y*info->bAxis.z - info->bAxis.y*info->aAxis.z)/V;  
            info->cReciprocalAxis.y = (info->aAxis.z*info->bAxis.x - info->bAxis.z*info->aAxis.x)/V;  
            info->cReciprocalAxis.z = (info->aAxis.x*info->bAxis.y - info->bAxis.x*info->aAxis.y)/V;  
            break;
        case 1: // Reciprocal -> Real
            break;
        default:
            break;

    }
}
