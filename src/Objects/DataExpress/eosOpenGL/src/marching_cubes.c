#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "mrcImage.h"
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
#include "./lmolvieProteinStatus.h"

#define VOXCUBE 150
#define RADIUSX 3.0
#define RADIUSY 4.0
#define RADIUSZ 2.0
#define CENTERX 10.0
#define CENTERY 10.0
#define CENTERZ 10.0

static int i, j, k, judge[VOXCUBE][VOXCUBE][VOXCUBE];
static double vox[VOXCUBE][VOXCUBE][VOXCUBE];
static int vox_x, vox_y, vox_z, on=1, off=0;
static double value=20;
static double normal_x, normal_y, normal_z;
static double dens_max, dens_min;

typedef struct halfst {
	GLdouble half_x_00;
	GLdouble half_x_01;
	GLdouble half_x_10;
	GLdouble half_x_11;
	GLdouble half_y_00;
	GLdouble half_y_01;
	GLdouble half_y_10;
	GLdouble half_y_11;
	GLdouble half_z_00;
	GLdouble half_z_01;
	GLdouble half_z_10;
	GLdouble half_z_11;
} halfst;

void incrementDensity(double increment)
{
	value+=increment;
	if(value<0){
		value=0;
	}
	fprintf(stdout, "Density:%lf\n", value);
}

/*void euler(void)
{
	for(vox_x=0; vox_x<VOXCUBE; vox_x++){
		for(vox_y=0; vox_y<VOXCUBE; vox_y++){
			for(vox_z=0; vox_z<VOXCUBE; vox_z++){
				sq=((((double)vox_x-CENTERX)/RADIUSX)*(((double)vox_x-CENTERX)/RADIUSX))+((((double)vox_y-CENTERY)/RADIUSY)*(((double)vox_y-CENTERY)/RADIUSY))+((((double)vox_z-CENTERZ)/RADIUSZ)*(((double)vox_z-CENTERZ)/RADIUSZ));
				inverse=1.0;
				for(i=0; i<sq; i++){
					inverse*=2.71828;
				}
				vox[vox_x][vox_y][vox_z]=1.0/inverse;
			
				if(vox[vox_x][vox_y][vox_z]>=value){
					judge[vox_x][vox_y][vox_z]=on;
				}
				else{
					judge[vox_x][vox_y][vox_z]=off;
				}
			}
		}
	}
}*/

void density_map(mrcImage* dens)
{
	int ix, iy, iz;
	int n;

/*	vox=(double***)malloc((dens->HeaderN.x)*sizeof(double**));
	for(i=0; i<dens->HeaderN.x; i++){
		vox[i]=(double**)malloc((dens->HeaderN.y)*sizeof(double*));
		for(j=0; j<dens->HeaderN.y; j++){
			vox[i][j]=(double*)malloc((dens->HeaderN.z)*sizeof(double));
		}
	}

	judge=(int***)malloc((dens->HeaderN.x)*sizeof(int**));
	for(i=0; i<dens->HeaderN.x; i++){
		judge[i]=(int**)malloc((dens->HeaderN.y)*sizeof(int*));
		for(j=0; j<dens->HeaderN.y; j++){
			judge[i][j]=(int*)malloc((dens->HeaderN.z)*sizeof(int));
		}
	}*/

	dens_max = dens_min = dens->ImageFloatImage[0];
	for(ix=0; ix<dens->HeaderN.x; ix++) {
		for(iy=0; iy<dens->HeaderN.y; iy++) {
			for(iz=0; iz<dens->HeaderN.z; iz++) {
				n =  ix + iy*dens->HeaderN.x + iz*dens->HeaderN.x*dens->HeaderN.y;
				vox[ix][iy][iz]=dens->ImageFloatImage[n];
				if(dens_max < dens->ImageFloatImage[n]){
					dens_max = dens->ImageFloatImage[n];
				}
				if(dens_min > dens->ImageFloatImage[n]){
					dens_min = dens->ImageFloatImage[n];
				}

				if(vox[ix][iy][iz]>=value){
					judge[ix][iy][iz]=on;
				}
				else{
					judge[ix][iy][iz]=off;
				}
			}
		}
	}
	fprintf(stdout, "Density:%lf\n", value);
}

double half_x(int half_x_y, int half_x_z){
	if(half_x_y==0 && half_x_z==0){
		if(i==0){
			if(vox[vox_x+1-i][vox_y+j][vox_z+k]>vox[vox_x+i][vox_y+j][vox_z+k]){
				return (double)vox_x+((value-vox[vox_x+i][vox_y+j][vox_z+k])/(vox[vox_x+1-i][vox_y+j][vox_z+k]-vox[vox_x+i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_x+1.0-((value-vox[vox_x+1-i][vox_y+j][vox_z+k])/(vox[vox_x+i][vox_y+j][vox_z+k]-vox[vox_x+1-i][vox_y+j][vox_z+k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+j][vox_z+k]>vox[vox_x+i][vox_y+j][vox_z+k]){
				return (double)vox_x+1.0-((value-vox[vox_x+i][vox_y+j][vox_z+k])/(vox[vox_x+1-i][vox_y+j][vox_z+k]-vox[vox_x+i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_x+((value-vox[vox_x+1-i][vox_y+j][vox_z+k])/(vox[vox_x+i][vox_y+j][vox_z+k]-vox[vox_x+1-i][vox_y+j][vox_z+k]));
			}
		}
	}
	else if(half_x_y==1 && half_x_z==0){
		if(i==0){
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+k]>vox[vox_x+i][vox_y+1-j][vox_z+k]){
				return (double)vox_x+((value-vox[vox_x+i][vox_y+1-j][vox_z+k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+k]-vox[vox_x+i][vox_y+1-j][vox_z+k]));
			}
			else{
				return (double)vox_x+1.0-((value-vox[vox_x+1-i][vox_y+1-j][vox_z+k])/(vox[vox_x+i][vox_y+1-j][vox_z+k]-vox[vox_x+1-i][vox_y+1-j][vox_z+k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+k]>vox[vox_x+i][vox_y+1-j][vox_z+k]){
				return (double)vox_x+1.0-((value-vox[vox_x+i][vox_y+1-j][vox_z+k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+k]-vox[vox_x+i][vox_y+1-j][vox_z+k]));
			}
			else{
				return (double)vox_x+((value-vox[vox_x+1-i][vox_y+1-j][vox_z+k])/(vox[vox_x+i][vox_y+1-j][vox_z+k]-vox[vox_x+1-i][vox_y+1-j][vox_z+k]));
			}
		}
	}
	else if(half_x_y==0 && half_x_z==1){
		if(i==0){
			if(vox[vox_x+1-i][vox_y+j][vox_z+1-k]>vox[vox_x+i][vox_y+j][vox_z+1-k]){
				return (double)vox_x+((value-vox[vox_x+i][vox_y+j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+j][vox_z+1-k]-vox[vox_x+i][vox_y+j][vox_z+1-k]));
			}
			else{
				return (double)vox_x+1.0-((value-vox[vox_x+1-i][vox_y+j][vox_z+1-k])/(vox[vox_x+i][vox_y+j][vox_z+1-k]-vox[vox_x+1-i][vox_y+j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+j][vox_z+1-k]>vox[vox_x+i][vox_y+j][vox_z+1-k]){
				return (double)vox_x+1.0-((value-vox[vox_x+i][vox_y+j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+j][vox_z+1-k]-vox[vox_x+i][vox_y+j][vox_z+1-k]));
			}
			else{
				return (double)vox_x+((value-vox[vox_x+1-i][vox_y+j][vox_z+1-k])/(vox[vox_x+i][vox_y+j][vox_z+1-k]-vox[vox_x+1-i][vox_y+j][vox_z+1-k]));
			}
		}
	}
	else{
		if(i==0){
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]>vox[vox_x+i][vox_y+1-j][vox_z+1-k]){
				return (double)vox_x+((value-vox[vox_x+i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]-vox[vox_x+i][vox_y+1-j][vox_z+1-k]));
			}
			else{
				return (double)vox_x+1.0-((value-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+i][vox_y+1-j][vox_z+1-k]-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]>vox[vox_x+i][vox_y+1-j][vox_z+1-k]){
				return (double)vox_x+1.0-((value-vox[vox_x+i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]-vox[vox_x+i][vox_y+1-j][vox_z+1-k]));
			}
			else{
				return (double)vox_x+((value-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+i][vox_y+1-j][vox_z+1-k]-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]));
			}
		}
	}
}

double half_y(int half_y_x, int half_y_z){
	if(half_y_x==0 && half_y_z==0){
		if(j==0){
			if(vox[vox_x+i][vox_y+1-j][vox_z+k]>vox[vox_x+i][vox_y+j][vox_z+k]){
				return (double)vox_y+((value-vox[vox_x+i][vox_y+j][vox_z+k])/(vox[vox_x+i][vox_y+1-j][vox_z+k]-vox[vox_x+i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_y+1.0-((value-vox[vox_x+i][vox_y+1-j][vox_z+k])/(vox[vox_x+i][vox_y+j][vox_z+k]-vox[vox_x+i][vox_y+1-j][vox_z+k]));
			}
		}
		else{
			if(vox[vox_x+i][vox_y+1-j][vox_z+k]>vox[vox_x+i][vox_y+j][vox_z+k]){
				return (double)vox_y+1.0-((value-vox[vox_x+i][vox_y+j][vox_z+k])/(vox[vox_x+i][vox_y+1-j][vox_z+k]-vox[vox_x+i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_y+((value-vox[vox_x+i][vox_y+1-j][vox_z+k])/(vox[vox_x+i][vox_y+j][vox_z+k]-vox[vox_x+i][vox_y+1-j][vox_z+k]));
			}
		}
	}
	else if(half_y_x==1 && half_y_z==0){
		if(j==0){
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+k]>vox[vox_x+1-i][vox_y+j][vox_z+k]){
				return (double)vox_y+((value-vox[vox_x+1-i][vox_y+j][vox_z+k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+k]-vox[vox_x+1-i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_y+1.0-((value-vox[vox_x+1-i][vox_y+1-j][vox_z+k])/(vox[vox_x+1-i][vox_y+j][vox_z+k]-vox[vox_x+1-i][vox_y+1-j][vox_z+k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+k]>vox[vox_x+1-i][vox_y+j][vox_z+k]){
				return (double)vox_y+1.0-((value-vox[vox_x+1-i][vox_y+j][vox_z+k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+k]-vox[vox_x+1-i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_y+((value-vox[vox_x+1-i][vox_y+1-j][vox_z+k])/(vox[vox_x+1-i][vox_y+j][vox_z+k]-vox[vox_x+1-i][vox_y+1-j][vox_z+k]));
			}
		}
	}
	else if(half_y_x==0 && half_y_z==1){
		if(j==0){
			if(vox[vox_x+i][vox_y+1-j][vox_z+1-k]>vox[vox_x+i][vox_y+j][vox_z+1-k]){
				return (double)vox_y+((value-vox[vox_x+i][vox_y+j][vox_z+1-k])/(vox[vox_x+i][vox_y+1-j][vox_z+1-k]-vox[vox_x+i][vox_y+j][vox_z+1-k]));
			}
			else{
				return (double)vox_y+1.0-((value-vox[vox_x+i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+i][vox_y+j][vox_z+1-k]-vox[vox_x+i][vox_y+1-j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+i][vox_y+1-j][vox_z+1-k]>vox[vox_x+i][vox_y+j][vox_z+1-k]){
				return (double)vox_y+1.0-((value-vox[vox_x+i][vox_y+j][vox_z+1-k])/(vox[vox_x+i][vox_y+1-j][vox_z+1-k]-vox[vox_x+i][vox_y+j][vox_z+1-k]));
			}
			else{
				return (double)vox_y+((value-vox[vox_x+i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+i][vox_y+j][vox_z+1-k]-vox[vox_x+i][vox_y+1-j][vox_z+1-k]));
			}
		}
	}
	else{
		if(j==0){
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]>vox[vox_x+1-i][vox_y+j][vox_z+1-k]){
				return (double)vox_y+((value-vox[vox_x+1-i][vox_y+j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]-vox[vox_x+1-i][vox_y+j][vox_z+1-k]));
			}
			else{
				return (double)vox_y+1.0-((value-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+j][vox_z+1-k]-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]>vox[vox_x+1-i][vox_y+j][vox_z+1-k]){
				return (double)vox_y+1.0-((value-vox[vox_x+1-i][vox_y+j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]-vox[vox_x+1-i][vox_y+j][vox_z+1-k]));
			}
			else{
				return (double)vox_y+((value-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+j][vox_z+1-k]-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]));
			}
		}
	}
}

double half_z(int half_z_x, int half_z_y){
	if(half_z_x==0 && half_z_y==0){
		if(k==0){
			if(vox[vox_x+i][vox_y+j][vox_z+1-k]>vox[vox_x+i][vox_y+j][vox_z+k]){
				return (double)vox_z+((value-vox[vox_x+i][vox_y+j][vox_z+k])/(vox[vox_x+i][vox_y+j][vox_z+1-k]-vox[vox_x+i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_z+1.0-((value-vox[vox_x+i][vox_y+j][vox_z+1-k])/(vox[vox_x+i][vox_y+j][vox_z+k]-vox[vox_x+i][vox_y+j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+i][vox_y+j][vox_z+1-k]>vox[vox_x+i][vox_y+j][vox_z+k]){
				return (double)vox_z+1.0-((value-vox[vox_x+i][vox_y+j][vox_z+k])/(vox[vox_x+i][vox_y+j][vox_z+1-k]-vox[vox_x+i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_z+((value-vox[vox_x+i][vox_y+j][vox_z+1-k])/(vox[vox_x+i][vox_y+j][vox_z+k]-vox[vox_x+i][vox_y+j][vox_z+1-k]));
			}
		}
	}
	else if(half_z_x==1 && half_z_y==0){
		if(k==0){
			if(vox[vox_x+1-i][vox_y+j][vox_z+1-k]>vox[vox_x+1-i][vox_y+j][vox_z+k]){
				return (double)vox_z+((value-vox[vox_x+1-i][vox_y+j][vox_z+k])/(vox[vox_x+1-i][vox_y+j][vox_z+1-k]-vox[vox_x+1-i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_z+1.0-((value-vox[vox_x+1-i][vox_y+j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+j][vox_z+k]-vox[vox_x+1-i][vox_y+j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+j][vox_z+1-k]>vox[vox_x+1-i][vox_y+j][vox_z+k]){
				return (double)vox_z+1.0-((value-vox[vox_x+1-i][vox_y+j][vox_z+k])/(vox[vox_x+1-i][vox_y+j][vox_z+1-k]-vox[vox_x+1-i][vox_y+j][vox_z+k]));
			}
			else{
				return (double)vox_z+((value-vox[vox_x+1-i][vox_y+j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+j][vox_z+k]-vox[vox_x+1-i][vox_y+j][vox_z+1-k]));
			}
		}
	}
	else if(half_z_x==0 && half_z_y==1){
		if(k==0){
			if(vox[vox_x+i][vox_y+1-j][vox_z+1-k]>vox[vox_x+i][vox_y+1-j][vox_z+k]){
				return (double)vox_z+((value-vox[vox_x+i][vox_y+1-j][vox_z+k])/(vox[vox_x+i][vox_y+1-j][vox_z+1-k]-vox[vox_x+i][vox_y+1-j][vox_z+k]));
			}
			else{
				return (double)vox_z+1.0-((value-vox[vox_x+i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+i][vox_y+1-j][vox_z+k]-vox[vox_x+i][vox_y+1-j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+i][vox_y+1-j][vox_z+1-k]>vox[vox_x+i][vox_y+1-j][vox_z+k]){
				return (double)vox_z+1.0-((value-vox[vox_x+i][vox_y+1-j][vox_z+k])/(vox[vox_x+i][vox_y+1-j][vox_z+1-k]-vox[vox_x+i][vox_y+1-j][vox_z+k]));
			}
			else{
				return (double)vox_z+((value-vox[vox_x+i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+i][vox_y+1-j][vox_z+k]-vox[vox_x+i][vox_y+1-j][vox_z+1-k]));
			}
		}
	}
	else{
		if(k==0){
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]>vox[vox_x+1-i][vox_y+1-j][vox_z+k]){
				return (double)vox_z+((value-vox[vox_x+1-i][vox_y+1-j][vox_z+k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]-vox[vox_x+1-i][vox_y+1-j][vox_z+k]));
			}
			else{
				return (double)vox_z+1.0-((value-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+k]-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]));
			}
		}
		else{
			if(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]>vox[vox_x+1-i][vox_y+1-j][vox_z+k]){
				return (double)vox_z+1.0-((value-vox[vox_x+1-i][vox_y+1-j][vox_z+k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]-vox[vox_x+1-i][vox_y+1-j][vox_z+k]));
			}
			else{
				return (double)vox_z+((value-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k])/(vox[vox_x+1-i][vox_y+1-j][vox_z+k]-vox[vox_x+1-i][vox_y+1-j][vox_z+1-k]));
			}
		}
	}
}

void calcNormal(double x, double y, double z, double ax, double ay, double az, double bx, double by, double bz)
{
	double outerProduct_x, outerProduct_y, outerProduct_z, length_ab;

	outerProduct_x=((ay-y)*(bz-z)-(az-z)*(by-y));
	outerProduct_y=((az-z)*(bx-x)-(ax-x)*(bz-z));
	outerProduct_z=((ax-x)*(by-y)-(ay-y)*(bx-x));
	length_ab=sqrt((outerProduct_x*outerProduct_x)+(outerProduct_y*outerProduct_y)+(outerProduct_z*outerProduct_z));

	normal_x=outerProduct_x/length_ab;
	normal_y=outerProduct_y/length_ab;
	normal_z=outerProduct_z/length_ab;
}
	
void marching1(int on2){
	halfst half;

	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			for(k=0; k<2; k++){
				half.half_x_00=half_x(0,0);
				half.half_x_01=half_x(0,1);
				half.half_x_10=half_x(1,0);
				half.half_x_11=half_x(1,1);
				half.half_y_00=half_y(0,0);
				half.half_y_01=half_y(0,1);
				half.half_y_10=half_y(1,0);
				half.half_y_11=half_y(1,1);
				half.half_z_00=half_z(0,0);
				half.half_z_01=half_z(0,1);
				half.half_z_10=half_z(1,0);
				half.half_z_11=half_z(1,1);

				if(judge[vox_x+i][vox_y+j][vox_z+k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal(half.half_x_00, (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half.half_y_00, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half.half_z_00);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half.half_x_00, (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half.half_y_00, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half.half_z_00);

					calcNormal(half.half_x_00, (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half.half_z_00, (double)vox_x+(double)i, half.half_y_00, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half.half_x_00, (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half.half_z_00);
					glVertex3f((double)vox_x+(double)i, half.half_y_00, (double)vox_z+(double)k);/*r*/

					glEnd();
				}
			}
		}
	}
}

void marching2(int on2){
	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			for(k=0; k<2; k++){
				if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+j][vox_z+k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+1-j][vox_z+k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glEnd();
				}/*3*/
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);

					/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);

					/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);

					/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}/*4*/
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);

					/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(-normal_x, -normal_y, -normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();
				}/*5*/
			}
		}
	}
}

void marching3(int on2){
	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			for(k=0; k<2; k++){
				if(judge[vox_x+1-i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+j][vox_z+1-k]==on2 && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+1-i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+1-j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+1-j][vox_z+k]==on2 && judge[vox_x+i][vox_y+j][vox_z+1-k]==on2 && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glEnd();
				}/*6*/
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+1-j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+j][vox_z+1-k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}/*7*/
				else if(judge[vox_x+1-i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+1-j][vox_z+k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);

					/*r*/
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+1-j][vox_z+k]==on2 && judge[vox_x+i][vox_y+j][vox_z+1-k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);

					/*r*/
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+1-i][vox_y+j][vox_z+k]==on2 && judge[vox_x+i][vox_y+j][vox_z+1-k]==on2 && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on2){
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);

					/*r*/
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}/*8*/
			}
		}
	}
}

void marching4(void){
	for(i=0; i<2; i++){
		for(j=0; j<2; j++){
			for(k=0; k<2; k++){
				if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glEnd();
				}/*9*/
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}/*10*/
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glEnd();
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glEnd();
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glEnd();
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glEnd();
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glEnd();
				}/*11*/
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();
				}/*12*/
				else if(judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glEnd();
				}
				else if(judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glEnd();
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glEnd();
				}/*13*/
				else if(judge[vox_x+i][vox_y+j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLES);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);

					/*r*/
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f(half_x(1,0), (double)vox_y+1.0-(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f((double)vox_x+(double)i, half_y(0,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+(double)j, half_z(1,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}/*14*/
				else if(judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+1-i][vox_y+j][vox_z+k]==on && judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on && judge[vox_x+1-i][vox_y+j][vox_z+1-k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+1.0-(double)j, half_z(0,1));
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k);
					calcNormal(half_x(0,0), (double)vox_y+(double)j, (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,1), (double)vox_z+1.0-(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}
				else if(judge[vox_x+i][vox_y+1-j][vox_z+k]==on && judge[vox_x+i][vox_y+j][vox_z+1-k]==on && judge[vox_x+i][vox_y+1-j][vox_z+1-k]==on && judge[vox_x+1-i][vox_y+1-j][vox_z+k]==on){
					glBegin(GL_TRIANGLE_STRIP);
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					calcNormal(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();

					glBegin(GL_TRIANGLE_STRIP);/*r*/
					calcNormal((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), (double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+(double)i, half_y(0,0), (double)vox_z+(double)k);
					glVertex3f((double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0));
					glVertex3f((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, (double)vox_x+(double)i, (double)vox_y+(double)j, half_z(0,0), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k);
					calcNormal((double)vox_x+1.0-(double)i, half_y(1,0), (double)vox_z+(double)k, half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, (double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1));
					calcNormal((double)vox_x+1.0-(double)i, (double)vox_y+1.0-(double)j, half_z(1,1), half_x(0,1), (double)vox_y+(double)j, (double)vox_z+1.0-(double)k, half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glNormal3f(normal_x, normal_y, normal_z);
					glVertex3f(half_x(1,1), (double)vox_y+1.0-(double)j, (double)vox_z+1.0-(double)k);
					glEnd();
				}/*15*/
			}
		}
	}
}

void marching_cubes(mrcImage* dens)
{
	for(vox_x=0; vox_x<dens->HeaderN.x; vox_x++){
		for(vox_y=0; vox_y<dens->HeaderN.y; vox_y++){
			for(vox_z=0; vox_z<dens->HeaderN.z; vox_z++){
				if(judge[vox_x][vox_y][vox_z]+judge[vox_x+1][vox_y][vox_z]+judge[vox_x][vox_y+1][vox_z]+judge[vox_x+1][vox_y+1][vox_z]+judge[vox_x][vox_y][vox_z+1]+judge[vox_x+1][vox_y][vox_z+1]+judge[vox_x][vox_y+1][vox_z+1]+judge[vox_x+1][vox_y+1][vox_z+1]==1){
					marching1(1);
				}

				if(judge[vox_x][vox_y][vox_z]+judge[vox_x+1][vox_y][vox_z]+judge[vox_x][vox_y+1][vox_z]+judge[vox_x+1][vox_y+1][vox_z]+judge[vox_x][vox_y][vox_z+1]+judge[vox_x+1][vox_y][vox_z+1]+judge[vox_x][vox_y+1][vox_z+1]+judge[vox_x+1][vox_y+1][vox_z+1]==7){
					marching1(0);
				}

				else if(judge[vox_x][vox_y][vox_z]+judge[vox_x+1][vox_y][vox_z]+judge[vox_x][vox_y+1][vox_z]+judge[vox_x+1][vox_y+1][vox_z]+judge[vox_x][vox_y][vox_z+1]+judge[vox_x+1][vox_y][vox_z+1]+judge[vox_x][vox_y+1][vox_z+1]+judge[vox_x+1][vox_y+1][vox_z+1]==2){
					marching2(1);
				}

				else if(judge[vox_x][vox_y][vox_z]+judge[vox_x+1][vox_y][vox_z]+judge[vox_x][vox_y+1][vox_z]+judge[vox_x+1][vox_y+1][vox_z]+judge[vox_x][vox_y][vox_z+1]+judge[vox_x+1][vox_y][vox_z+1]+judge[vox_x][vox_y+1][vox_z+1]+judge[vox_x+1][vox_y+1][vox_z+1]==6){
					marching2(0);
				}

				else if(judge[vox_x][vox_y][vox_z]+judge[vox_x+1][vox_y][vox_z]+judge[vox_x][vox_y+1][vox_z]+judge[vox_x+1][vox_y+1][vox_z]+judge[vox_x][vox_y][vox_z+1]+judge[vox_x+1][vox_y][vox_z+1]+judge[vox_x][vox_y+1][vox_z+1]+judge[vox_x+1][vox_y+1][vox_z+1]==3){
					marching3(1);
				}

				else if(judge[vox_x][vox_y][vox_z]+judge[vox_x+1][vox_y][vox_z]+judge[vox_x][vox_y+1][vox_z]+judge[vox_x+1][vox_y+1][vox_z]+judge[vox_x][vox_y][vox_z+1]+judge[vox_x+1][vox_y][vox_z+1]+judge[vox_x][vox_y+1][vox_z+1]+judge[vox_x+1][vox_y+1][vox_z+1]==5){
					marching3(0);
				}

				else if(judge[vox_x][vox_y][vox_z]+judge[vox_x+1][vox_y][vox_z]+judge[vox_x][vox_y+1][vox_z]+judge[vox_x+1][vox_y+1][vox_z]+judge[vox_x][vox_y][vox_z+1]+judge[vox_x+1][vox_y][vox_z+1]+judge[vox_x][vox_y+1][vox_z+1]+judge[vox_x+1][vox_y+1][vox_z+1]==4){
					marching4();
				}
			}
		}
	}
}

void marching_cubes_display(mrcImage* dens)
{
	float scale;
	pdbCenter pdbCenter;

	density_map(dens);
	pdbCenter=getpdbCenter(0);
	scale=(pdbCenter.xMax-pdbCenter.xMin)/(float)dens->HeaderN.x;

	glColor4f(0.7, 0.7, 0.7, 0.2);

	glPushMatrix();
//	glScalef(scale, scale, scale);
	glScalef(dens->HeaderLength.x, dens->HeaderLength.y, dens->HeaderLength.z);
	glTranslatef(pdbCenter.xCenter/dens->HeaderLength.x-dens->HeaderN.x/2, 
                     pdbCenter.yCenter/dens->HeaderLength.y-dens->HeaderN.y/2, 
 		     pdbCenter.zCenter/dens->HeaderLength.z-dens->HeaderN.z/2);
	on=1;
	off=0;

	marching_cubes(dens);
//	density_sphere2(dens);
	glPopMatrix();
}

void density_sphere2(mrcImage* dens)
{
	for(vox_x=0; vox_x<dens->HeaderN.x; vox_x++){
		for(vox_y=0; vox_y<dens->HeaderN.y; vox_y++){
			for(vox_z=0; vox_z<dens->HeaderN.z; vox_z++){
				glPushMatrix();
				glTranslatef(vox_x, vox_y, vox_z);
				glutSolidSphere(vox[vox_x][vox_y][vox_z]/dens_max, 10, 10);
				glPopMatrix();
			}
		}
	}
}
