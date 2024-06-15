/*
# density_sphere : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : density_sphere 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<stdio.h>
#include "mrcImage.h"
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"

void density_sphere(mrcImage* dens, double vox[150][150][150], double dens_max)
{
	int vox_x, vox_y, vox_z;

	for(vox_x=0; vox_x<dens->HeaderN.x; vox_x++){
		for(vox_y=0; vox_y<dens->HeaderN.y; vox_y++){
			for(vox_z=0; vox_z<dens->HeaderN.z; vox_z++){
				if(vox[vox_x][vox_y][vox_z] > 1.0){
					fprintf(stdout, "%d %d %d\n", vox_x, vox_y, vox_z);
					glPushMatrix();
					glTranslatef(vox_x, vox_y, vox_z);
					glutSolidSphere(vox[vox_x][vox_y][vox_z]/dens_max, 10, 10);
					glPopMatrix();
				}
			}
		}
	}
}
