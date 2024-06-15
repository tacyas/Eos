/*
# lmolvieTexture : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieTexture 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<stdio.h>
#include<stdlib.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvieProteinStatus.h"

static int n;
static int m;

static float __s=1.0;
static float texture_x=0.0, texture_y=0.0, texture_z = 0.0;

GLubyte *image;
//static GLubyte image[256][256][3];

void texture_scale_change(double scale)
{
	fprintf(stdout, "%f %f\n", scale, __s);
	__s+=scale;
}

void texture_translate_x(double x)
{
	texture_x+=x;
}

void texture_translate_y(double y)
{
	texture_y+=y;
}

void texture_translate_z(double z)
{
	texture_z+=z;
}

void texture()
{
	pdbCenter pdbCenter;

	pdbCenter=getpdbCenter(0);

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(pdbCenter.xCenter+texture_x, pdbCenter.yCenter+texture_y, -pdbCenter.zCenter + texture_z);
	glScalef(__s, __s, __s);
	glBegin(GL_QUADS);
/*		glTexCoord2f(1.0, 1.0);
		glVertex3f(pdbCenter.xCenter-(float)n/2.0, pdbCenter.yCenter-(float)m/2.0, pdbCenter.zMax);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(pdbCenter.xCenter-(float)n/2.0, pdbCenter.yCenter+(float)m/2.0, pdbCenter.zMax);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(pdbCenter.xCenter+(float)n/2.0, pdbCenter.yCenter+(float)m/2.0, pdbCenter.zMax);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(pdbCenter.xCenter+(float)n/2.0, pdbCenter.yCenter-(float)m/2.0, pdbCenter.zMax);*/
		glTexCoord2f(1.0, 1.0);
		glVertex3f(pdbCenter.xCenter+(float)n/2.0, pdbCenter.yCenter-(float)m/2.0, pdbCenter.zMax);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(pdbCenter.xCenter+(float)n/2.0, pdbCenter.yCenter+(float)m/2.0, pdbCenter.zMax);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(pdbCenter.xCenter-(float)n/2.0, pdbCenter.yCenter+(float)m/2.0, pdbCenter.zMax);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(pdbCenter.xCenter-(float)n/2.0, pdbCenter.yCenter-(float)m/2.0, pdbCenter.zMax);
	glEnd();
	glPopMatrix();
}

void put_texture()
{
	FILE *fd;
	int k, nm;
	char c;
	int i;
	char b[100];
	float s;
	int red, green, blue;

	fprintf(stdout, "enter file name\n");
	scanf("%s", b);
	fd = fopen(b, "r");
	fscanf(fd, "%[^\n]", b);
	if(b[0]!='P' || b[1]!='6'){
		fprintf(stdout, "%s is not a PPM file!\n", b);
		exit(0);
	}
	fscanf(fd, "%c", &c);
	while(c=='#'){
		fscanf(fd, "%[^\n]", b);
		fscanf(fd, "%c", &c);
	}
	fgets(b, 100, fd);
	ungetc(c, fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);
	nm=n*m;
	fprintf(stdout, "%d, %d, %d, %d\n", n, m, k, nm);
	image = (GLubyte*)malloc(3*sizeof(GLubyte)*nm);
	s=255./k;

/*	for(i=0; i<nm; i++){
		fscanf(fd, "%d %d %d", &red, &green, &blue);
		image[3*nm-3*i-3]=red;
		image[3*nm-3*i-2]=green;
		image[3*nm-3*i-1]=blue;
	}*/


	fscanf(fd, "%d %d", &red, &blue);
	
	fread(image, (nm * 3), 1, fd);

	glPixelTransferf(GL_RED_SCALE, s);
	glPixelTransferf(GL_GREEN_SCALE, s);
	glPixelTransferf(GL_BLUE_SCALE, s);
	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, n, m, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
