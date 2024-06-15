/*
# loadPPM : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : loadPPM 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<stdio.h>
#include<stdlib.h>
#include "../inc/eosOpenGL.h"

static GLubyte piximage[163][116][3];

void loadPPM(void)
{
	int pix_i, pix_j, pix_k;
	int PIXSIZE_X, PIXSIZE_Y;
	FILE *ppmIn;
//	GLubyte piximage[PIXSIZE_Y][PIXSIZE_X][3];
//	GLubyte piximage[256][256][3];
	char *line;
	int i, j, c;
	GLubyte *taki;

	if(NULL==(ppmIn=fopen("takimotoyusuke.ppm","r"))){
		exit(1);
	}

	line=(char*)malloc(100*sizeof(char));

	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);

	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);

	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);

	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);

/*	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);
	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);
	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);
	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);
	fgets(line, 100, ppmIn);
	fprintf(stdout, "%s\n", line);*/

	fread(piximage, sizeof piximage, 1, ppmIn);

/*	for(i=0; i<256; i++){
		for(j=0; j<256; j++){
//			fread(&piximage[i][j][0], sizeof(GLubyte), 1, ppmIn);
//			fread(&piximage[i][j][1], sizeof(GLubyte), 1, ppmIn);
//			fread(&piximage[i][j][2], sizeof(GLubyte), 1, ppmIn);
			fread(taki, sizeof(GLubyte), 1, ppmIn);
			piximage[i][j][0]=(GLubyte)&taki;
			fread(taki, sizeof(GLubyte), 1, ppmIn);
			piximage[i][j][1]=(GLubyte)&taki;
			fread(taki, sizeof(GLubyte), 1, ppmIn);
			piximage[i][j][2]=(GLubyte)&taki;
		}
	}*/

/*	for(i=0; i<256; i++){
		for(j=0; j<256; j++){
			c=((((i&0x8)==0)^((j&0x8))==0))*255;
			piximage[i][j][0]=(GLubyte)c;
			piximage[i][j][1]=(GLubyte)c;
			piximage[i][j][2]=(GLubyte)c;
			piximage[i][j][3]=(GLubyte)255;
		}
	}*/

/* テクスチャ画像はバイト単位に詰め込まれている */
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
//	glGenTextures(1, &texName);
//	glBindTexture(GL_TEXTURE_2D, texName);
   /* テクスチャを拡大・縮小する方法の指定 */
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  /* テクスチャの割り当て */
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, piximage);
    
	fclose(ppmIn);

/*	glEnable(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, piximage);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/

//	textureTest(/*piximage*/);

//	textureOn();
}

void takimoto()
{
	glRasterPos2f(-71.9, -67.6);
	glDrawPixels(256, 256, GL_RGB, GL_UNSIGNED_BYTE, piximage);
}

void textureTest(void)
{
	GLubyte image[64][64][3];
	int i, j, r, c;
	for(i=0; i<64; i++)
	{
		for(j=0; j<64; j++)
		{
			c=((((i&0x8)==0)^((j&0x8))==0))*255;
			image[i][j][0]=(GLubyte)c;
			image[i][j][1]=(GLubyte)c;
			image[i][j][2]=(GLubyte)c;
		}
	}
/*	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");

	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);*/
	glEnable(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, piximage);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glutMainLoop();
//	colorcube();
}
