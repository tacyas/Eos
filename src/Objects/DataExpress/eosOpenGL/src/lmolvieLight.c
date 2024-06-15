/*
# lmolvieLight : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieLight 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdlib.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"

static GLfloat light0Pos[]      = {0.0, 0.0, -2.0, 0};
static GLfloat light0Diffuse[]  = {1.0, 1.0, 1.0, 1.0};
static GLfloat light0Specular[] = {1.0, 1.0, 1.0, 1.0};

static GLfloat light1Pos[]      = {100.0, 100.0, 1000.0, 1.0}; 
static GLfloat light1Diffuse[]  = {0.5, 0.5, 0.5, 1.0}; 
static GLfloat light1Specular[] = {0.3, 0.3, 0.3, 1.0}; 

static GLfloat lightAmbient[]   = {0.1, 0.1, 0.1, 1.0};


void
lmolvieLightSet(void)
{
	cameraInfo *cameraPos;
	
	cameraPos = getMyCamera();
	
	light0Pos[0] = cameraPos->Eye[0] * 2;
	light0Pos[1] = cameraPos->Eye[1] * 2;
	light0Pos[2] = cameraPos->Eye[2];
	
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);

	glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);      
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1Diffuse); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

GLfloat* 
get_LightPos(int index)
{
	switch(index) {
		case 0: {
			return light0Pos; 
		}
		case 1: {
			return light1Pos;	
		}
	}
	return NULL;
}
