/*
# savePPM : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : savePPM 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<stdio.h>
#include<stdlib.h>
#include "../inc/eosOpenGL.h"

void savePPM(void)
{
	int pix_i, pix_j, pix_k;
	int PIXSIZE_X, PIXSIZE_Y;
	FILE *ppmf;
//	GLubyte piximage[PIXSIZE_Y][PIXSIZE_X][3];
	GLubyte piximage[256][256][3];

//	glReadPixels(0, 0, PIXSIZE_X, PIXSIZE_Y, GL_RGB, GL_UNSIGNED_BYTE, piximage);
	glReadPixels(0, 0, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, piximage);

	ppmf=fopen("output.ppm", "w");
	fprintf(ppmf, "P6\n");
//	fprintf(ppmf, "%d %d\n", PIXSIZE_X, PIXSIZE_Y);
	fprintf(ppmf, "%d %d\n", 256, 256);
	fclose(ppmf);
	ppmf=fopen("output.ppm", "ab");
	fputc(50, ppmf);
	fputc(53, ppmf);
	fputc(53, ppmf);
	fputc(10, ppmf);

//	for(pix_j=0;pix_j<PIXSIZE_Y;pix_j++)
//		for(pix_i=0;pix_i<PIXSIZE_X;pix_i++)
//			for(pix_k=0;pix_k<3;pix_k++)
//				fputc(piximage[PIXSIZE_Y-1-pix_j][pix_i][pix_k],ppmf);
	for(pix_j=0; pix_j<256; pix_j++)
		for(pix_i=0; pix_i<256; pix_i++)
			for(pix_k=0; pix_k<3; pix_k++)
				fputc(piximage[256-1-pix_j][pix_i][pix_k], ppmf);
	fclose(ppmf);
}
