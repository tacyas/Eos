/*
# lmolvieDisplayNormal : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieDisplayNormal 
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
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
#include "./lmolvieProteinStatus.h"
#include "pdbFile.h"
#include "./DisplayListNumber.h"

static GLboolean needDisplayListMakingSurface=GL_TRUE;

static GLuint camera_centre_tag=1;

void setCameraCentreTagM(int tag){
	camera_centre_tag*=tag;
	if(tag==0){
		camera_centre_tag=0;
	}

	if(camera_centre_tag==1){
		fprintf(stdout, "CameraCenter: OFF");
	}else if(camera_centre_tag==-1){
		fprintf(stdout, "CameraCenter: ON");
	}

	if(tag==2){
		camera_centre_tag=1;
	}
}

void reset_needDisplayListMakingSurfaceM(void)
{
	needDisplayListMakingSurface=GL_TRUE;
}

void lmolvieMrcViewerDisplay(void)
{
	cameraInfo* camera;
	int spin_x, spin_y;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera=getMyCamera();

	gluLookAt(camera->Eye[0], camera->Eye[1], camera->Eye[2], camera->Centre[0], camera->Centre[1], camera->Centre[2], camera->Up[0], camera->Up[1], camera->Up[2]);

	spin_x=getSpin_x(0);
	spin_y=getSpin_y(0);

	glPushMatrix();
	glTranslatef(camera->Centre[0], camera->Centre[1], camera->Centre[2]);
	glRotated(spin_x, 1.0, 0.0, 0.0);
	glRotated(spin_y, 0.0, 1.0, 0.0);
	glTranslatef(-camera->Centre[0], -camera->Centre[1], -camera->Centre[2]);

	if(needDisplayListMakingSurface==GL_TRUE){
		needDisplayListMakingSurface=myDisplayListMakeSurface();
	}
	glPushMatrix();
	glCallList(drawsurface);
	glPopMatrix();

	if(camera_centre_tag==-1){
		glBegin(GL_LINES);
		glVertex3f(camera->Centre[0]-1.0, camera->Centre[1], camera->Centre[2]);
		glVertex3f(camera->Centre[0]+1.0, camera->Centre[1], camera->Centre[2]);
		glVertex3f(camera->Centre[0], camera->Centre[1]-1.0, camera->Centre[2]);
		glVertex3f(camera->Centre[0], camera->Centre[1]+1.0, camera->Centre[2]);
		glVertex3f(camera->Centre[0], camera->Centre[1], camera->Centre[2]-1.0);
		glVertex3f(camera->Centre[0], camera->Centre[1], camera->Centre[2]+1.0);
		glEnd();
	}

	glPopMatrix();

	glutSwapBuffers();
}
