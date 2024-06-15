/*
# lmolvieDisplayParallel : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieDisplayParallel 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./lmolvie.h"
#include "pdbFile.h"
#include "mrcImage.h"
#include "./lmolvieProteinStatus.h"

//pdbFile* pdbIn;
static GLuint drawatom=1;
static GLuint drawsurface2=200;

static GLboolean needDisplayListMakingAtom=GL_TRUE;
static GLboolean needDisplayListMakingSurface=GL_TRUE;
static GLboolean textureFlag=GL_TRUE;

static GLdouble scale=1.0;

static GLuint scaleBar = 0;

void DrawAtom(void)
{
	pdbFile* pdbIn;

	pdbIn=get_pdb();

	glNewList(drawatom, GL_COMPILE);
	pdbIn->PDB=pdbIn->top;
	glColor4f(0.0, 1.0, 1.0, 0.5);
	while(NULL!=pdbIn->PDB){
		glPushMatrix();
		glTranslatef(pdbIn->PDB->Coord.x, pdbIn->PDB->Coord.y, pdbIn->PDB->Coord.z);
		if(strncmp(pdbIn->PDB->AtomName, " C", 2)==0){glutSolidSphere(0.5, 10, 10);}
		else if(strncmp(pdbIn->PDB->AtomName, " O", 2)==0){glutSolidSphere(0.5, 10, 10);}
		else if(strncmp(pdbIn->PDB->AtomName, " N", 2)==0){glutSolidSphere(0.5, 10, 10);}
		else if(strncmp(pdbIn->PDB->AtomName, " S", 2)==0){glutSolidSphere(0.5, 10, 10);}
		else if(strncmp(pdbIn->PDB->AtomName, " P", 2)==0){glutSolidSphere(0.5, 10, 10);}
		else if(strncmp(pdbIn->PDB->AtomName, " H", 2)==0){glutSolidSphere(0.5, 10, 10);}
		else{glutSolidSphere(0.5, 10, 10);}/*vdw humei*/
		pdbIn->PDB=pdbIn->PDB->next;
		glPopMatrix();
	}
	glEndList();
}

void parallelDisplayListMakeAtom(void)
{
	DrawAtom();
	needDisplayListMakingAtom=GL_FALSE;
}

GLboolean parallelDisplayListMakeSurface(void)
{
	mrcImage *mrc;

	glNewList(drawsurface2, GL_COMPILE);
	mrc=get_mrc();
	marching_cubes_display(mrc);
	glEndList();
	return GL_FALSE;
}

void scale_change(GLdouble rate){
	scale+=rate;
}

void textureMake(void)
{
//	if(textureFlag==GL_TRUE){
//		put_texture();
//		textureFlag=GL_FALSE;
//	}

	put_texture();
}

void scaleBarSwitch()
{
	if(scaleBar < 3){
		scaleBar++;
	}
	else{
		scaleBar = 0;
	}
	switch(scaleBar){
		case 0: {
			fprintf(stdout, "No scale bar.\n");
			break;
		}
		case 1: {
			fprintf(stdout, "Scale bar:1nm.\n");
			break;
		}
		case 2: {
			fprintf(stdout, "Scale bar:5nm.\n");
			break;
		}
		case 3: {
			fprintf(stdout, "Scale bar:10nm.\n");
			break;
		}
	}
}

void lmolvieDisplayParallel(void)
{
	cameraInfo* camera;
	int spin_x, spin_y,spin_z;
	pdbCenter pdbCenter;
	static const GLfloat color[] = { 0.0, 1.0, 1.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	pdbCenter=getpdbCenter(0);
	camera=getMyCamera();
	gluLookAt(camera->Eye[0], camera->Eye[1], camera->Eye[2], camera->Centre[0], camera->Centre[1], camera->Centre[2], camera->Up[0], camera->Up[1], camera->Up[2]);

	if(needDisplayListMakingAtom==GL_TRUE){
		parallelDisplayListMakeAtom();
	}

//	if(needDisplayListMakingSurface==GL_TRUE){
//		needDisplayListMakingSurface=parallelDisplayListMakeSurface();
//	}

	spin_x=getSpin_x(0);
	spin_y=getSpin_y(0);
	spin_z=getSpin_z(0);
	glPushMatrix();
	glTranslatef(camera->Centre[0], camera->Centre[1], camera->Centre[2]);
	glScalef(scale, scale, scale);
	glPushMatrix();
	glRotated(spin_x, 1.0, 0.0, 0.0);
	glRotated(spin_y, 0.0, 1.0, 0.0);
	glRotated(spin_z, 0.0, 0.0, 1.0);
	glTranslatef(-camera->Centre[0], -camera->Centre[1], -camera->Centre[2]);

//	glDisable(GL_LIGHTING);

	glPushMatrix();
	glCallList(drawatom);
	glPopMatrix();

//	glPushMatrix();
//	glCallList(drawsurface2);
//	glPopMatrix();

	glPopMatrix();
//	if(textureFlag == GL_FALSE){
//		glTranslatef(-camera->Centre[0], -camera->Centre[1], -camera->Centre[2]);
//		texture();
//	}

//	if(textureFlag == GL_TRUE){
//		textureMake();
//		textureFlag = GL_FALSE;
//	}

	glPushMatrix();
	glTranslatef((pdbCenter.xWidth / 2), -(pdbCenter.yWidth / 2), 0);
	if(scaleBar == 1){
		glBegin(GL_QUADS);
		glVertex3f(-5, 1, 0);
		glVertex3f(-5, -1, 0);
		glVertex3f(5, -1, 0);
		glVertex3f(5, 1, 0);
		glEnd();
	}
	else if(scaleBar == 2){
		glBegin(GL_QUADS);
		glVertex3f(-25, 1, 0);
		glVertex3f(-25, -1, 0);
		glVertex3f(25, -1, 0);
		glVertex3f(25, 1, 0);
		glEnd();
	}
	else if(scaleBar == 3){
		glBegin(GL_QUADS);
		glVertex3f(-50, 1, 0);
		glVertex3f(-50, -1, 0);
		glVertex3f(50, -1, 0);
		glVertex3f(50, 1, 0);
		glEnd();
	}
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-camera->Centre[0], -camera->Centre[1], -(camera->Centre[2] + (pdbCenter.zWidth / 2)));
	texture();
	glPopMatrix();

	glPopMatrix();
//	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}
