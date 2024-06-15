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
#include "./lmolvie.h"
#include "./lmolvieProteinStatus.h"
//#include "./Draw.h"
#include "pdbFile.h"
//#include "./DSN6.h"
//#include "Contour.h"
#include "DisplayListNumber.h"

//extern Dsn6     densIn;
//extern pdbFile* pdbIn;

static GLboolean needDisplayListMakingAtom=GL_TRUE;
static GLboolean needDisplayListMakingStick=GL_TRUE;
static GLboolean needDisplayListMakingAtomSerial=GL_TRUE;
static GLboolean needDisplayListMakingResidue=GL_TRUE;
static GLboolean needDisplayListMakingTemp=GL_TRUE;
static GLboolean needDisplayListMakingStickTemp=GL_TRUE;
static GLboolean needDisplayListMakingStickResidue=GL_TRUE;
static GLboolean needDisplayListMakingSurface=GL_TRUE;
static GLboolean needDisplayListMakingDistanceFromTarget=GL_TRUE;
static GLboolean needDisplayListMakingWireFrame=GL_TRUE;
static GLboolean needDisplayListMakingChain=GL_TRUE;

//static GLuint check_switch=0;
//static GLdouble check_x, check_y, check_z;

static GLuint camera_centre_tag=1;

static GLuint multipdbload=0;

//void setCheckSwitch(int check){
//	check_switch=check;/*0:no, 1:check, 2:draw*/
//}

void setCameraCentreTagD(int tag){
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

void  setMultiPDBloadD(int load){
	multipdbload=load;
}

void lmolvieDockDisplay(void)
{
	cameraInfo* camera;
//	int i;
	elementSwitch key;
	displayMode display;
//	char *changemode;
//	float Hz=784;
	int spin_x, spin_y;
	operationMode operation;
	pdbCenter pdbCenter[5];
	GLfloat multi_move_x[5], multi_move_y[5], multi_move_z[5];
	int multiProteinChange;
	contourLinesSet contour;
//	static int textureFlag=0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera=getMyCamera();
	display=displayModeGet(0);
	operation=operationModeGet();
	pdbCenter[0]=getpdbCenter(0);
	multi_move_x[0]=getMultiMoveX(0);
	multi_move_y[0]=getMultiMoveY(0);
	multiProteinChange=get_multiProteinChange();

	gluLookAt(camera->Eye[0], camera->Eye[1], camera->Eye[2], camera->Centre[0], camera->Centre[1], camera->Centre[2], camera->Up[0], camera->Up[1], camera->Up[2]);

	key=get_elementSwitch(0);

	spin_x=getSpin_x(0);
	spin_y=getSpin_y(0);

	glPushMatrix();
	glPushMatrix();
	glTranslatef(multi_move_x[0], multi_move_y[0], 0);
	glTranslatef(camera->Centre[0], camera->Centre[1], camera->Centre[2]);
	glRotated(spin_x, 1.0, 0.0, 0.0);
	glRotated(spin_y, 0.0, 1.0, 0.0);
	glTranslatef(-camera->Centre[0], -camera->Centre[1], -camera->Centre[2]);

	if(display==1){
		if(needDisplayListMakingAtom==GL_TRUE){
			needDisplayListMakingAtom=myDisplayListMakeAtom();
		}
		if(key.elementC==1){
			glPushMatrix();
			glCallList(drawatomc);
			glCallList(drawatomca);
			glPopMatrix();
		}
		else if(key.elementC==2){
			glPushMatrix();
			glCallList(drawatomca);
			glPopMatrix();
		}

		if(key.elementO==1){
			glPushMatrix();
			glCallList(drawatomo);
			glPopMatrix();
		}

		if(key.elementN==1){
			glPushMatrix();
			glCallList(drawatomn);
			glPopMatrix();
		}

		if(key.elementS==1){
			glPushMatrix();
			glCallList(drawatoms);
			glPopMatrix();
		}

		if(key.elementP==1){
			glPushMatrix();
			glCallList(drawatomp);
			glPopMatrix();
		}

		if(key.elementH==1){
			glPushMatrix();
			glCallList(drawatomh);
			glPopMatrix();
		}
		if(key.elementFE==1){
			glPushMatrix();
			glCallList(drawatomfe);
			glPopMatrix();
		}
	}

	else if(display==2){
		if(needDisplayListMakingStick==GL_TRUE){
			needDisplayListMakingStick=myDisplayListMakeStick();
		}
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(drawstick);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	else if(display==3){
		if(needDisplayListMakingAtomSerial==GL_TRUE){
			needDisplayListMakingAtomSerial=myDisplayListMakeAtomSerial();
		}
		glPushMatrix();
		glCallList(drawatomserial);
		glPopMatrix();
	}

	else if(display==4){
		if(needDisplayListMakingResidue==GL_TRUE){
			needDisplayListMakingResidue=myDisplayListMakeResidue();
		}
		glPushMatrix();
		glCallList(drawresidue);
		glPopMatrix();
	}

	else if(display==5){
		if(needDisplayListMakingTemp==GL_TRUE){
			needDisplayListMakingTemp=myDisplayListMakeTemp();
		}
		glPushMatrix();
		glCallList(drawtemp);
		glPopMatrix();
	}

	else if(display==6){
		if(needDisplayListMakingStickTemp==GL_TRUE){
			needDisplayListMakingStickTemp=myDisplayListMakeStickTemp();
		}
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(drawsticktemp);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	else if(display==7){
		if(needDisplayListMakingStickResidue==GL_TRUE){
			needDisplayListMakingStickResidue=myDisplayListMakeStickResidue();
		}
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(drawstickresidue);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

/*	else if(display==8){
		if(needDisplayListMakingDistanceFromTarget==GL_TRUE){
			needDisplayListMakingDistanceFromTarget=myDisplayListMakeDistanceFromTarget();
		}
		glPushMatrix();
		glCallList(drawdistancefromtarget);
		glPopMatrix();
	}*/

	else if(display==9){
		if(needDisplayListMakingWireFrame==GL_TRUE){
			needDisplayListMakingWireFrame=myDisplayListMakeWireFrame();
		}
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(drawwireframe);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

/*	else if(display==10){
		if(needDisplayListMakingChain==GL_TRUE){
			needDisplayListMakingChain=myDisplayListMakeChain();
		}
		glPushMatrix();
		glCallList(drawchain);
		glPopMatrix();
	}*/

	glPopMatrix();

/*//	if(check_switch==1){
//		check_x=camera->Centre[0];
//		check_y=camera->Centre[1];
//		check_z=camera->Centre[2];

//		setTarget(check_x, check_y, check_z);//voice.c

//		check_switch=2;
//	}
	if(check_switch==2){
		glPushMatrix();
		glTranslatef(check_x, check_y, check_z);
		glDisable(GL_LIGHTING);
		glutWireSphere(2.0, 10, 10);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}*/

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

	if(multipdbload>=1){
		glPushMatrix();
		pdbCenter[1]=getpdbCenter(1);
		multi_move_x[1]=getMultiMoveX(1);
		multi_move_y[1]=getMultiMoveY(1);
		spin_x=getSpin_x(1);
		spin_y=getSpin_y(1);
		glPushMatrix();
		glTranslatef(pdbCenter[0].xCenter-pdbCenter[1].xCenter+multi_move_x[1], pdbCenter[0].yCenter-pdbCenter[1].yCenter+multi_move_y[1], pdbCenter[0].zCenter-pdbCenter[1].zCenter);
		glTranslatef(pdbCenter[1].xCenter, pdbCenter[1].yCenter, pdbCenter[1].zCenter);
		glRotated(spin_x, 1.0, 0.0, 0.0);
		glRotated(spin_y, 0.0, 1.0, 0.0);
		glTranslatef(-pdbCenter[1].xCenter, -pdbCenter[1].yCenter, -pdbCenter[1].zCenter);

		glPushMatrix();
		fprintf(stdout, "takimoto\n");
		displayMultiPDB1();
		glPopMatrix();

		glPopMatrix();
		glPopMatrix();
	}

/*	if(multipdbload>=2){
		pdbCenter[2]=getpdbCenter(2);
		multi_move_x[2]=getMultiMoveX(2);
		multi_move_y[2]=getMultiMoveY(2);
		spin_x=getSpin_x(2);
		spin_y=getSpin_y(2);
		glPushMatrix();
		glTranslatef(pdbCenter[0].xCenter-pdbCenter[2].xCenter+multi_move_x[2], pdbCenter[0].yCenter-pdbCenter[2].yCenter+multi_move_y[2], pdbCenter[0].zCenter-pdbCenter[2].zCenter);
		glTranslatef(pdbCenter[2].xCenter, pdbCenter[2].yCenter, pdbCenter[2].zCenter);
		glRotated(spin_x, 1.0, 0.0, 0.0);
		glRotated(spin_y, 0.0, 1.0, 0.0);
		glTranslatef(-pdbCenter[2].xCenter, -pdbCenter[2].yCenter, -pdbCenter[2].zCenter);

		glPushMatrix();
		displayMultiPDB2();
		glPopMatrix();

		glPopMatrix();
	}

	if(multipdbload>=3){
		pdbCenter[3]=getpdbCenter(3);
		multi_move_x[3]=getMultiMoveX(3);
		multi_move_y[3]=getMultiMoveY(3);
		spin_x=getSpin_x(3);
		spin_y=getSpin_y(3);
		glPushMatrix();
		glTranslatef(pdbCenter[0].xCenter-pdbCenter[3].xCenter+multi_move_x[3], pdbCenter[0].yCenter-pdbCenter[3].yCenter+multi_move_y[3], pdbCenter[0].zCenter-pdbCenter[3].zCenter);
		glTranslatef(pdbCenter[3].xCenter, pdbCenter[3].yCenter, pdbCenter[3].zCenter);
		glRotated(spin_x, 1.0, 0.0, 0.0);
		glRotated(spin_y, 0.0, 1.0, 0.0);
		glTranslatef(-pdbCenter[3].xCenter, -pdbCenter[3].yCenter, -pdbCenter[3].zCenter);

		glPushMatrix();
		displayMultiPDB3();
		glPopMatrix();

		glPopMatrix();
	}

	if(multipdbload>=4){
		pdbCenter[4]=getpdbCenter(4);
		multi_move_x[4]=getMultiMoveX(4);
		multi_move_y[4]=getMultiMoveY(4);
		spin_x=getSpin_x(4);
		spin_y=getSpin_y(4);
		glPushMatrix();
		glTranslatef(pdbCenter[0].xCenter-pdbCenter[4].xCenter+multi_move_x[4], pdbCenter[0].yCenter-pdbCenter[4].yCenter+multi_move_y[4], pdbCenter[0].zCenter-pdbCenter[4].zCenter);
		glTranslatef(pdbCenter[4].xCenter, pdbCenter[4].yCenter, pdbCenter[4].zCenter);
		glRotated(spin_x, 1.0, 0.0, 0.0);
		glRotated(spin_y, 0.0, 1.0, 0.0);
		glTranslatef(-pdbCenter[4].xCenter, -pdbCenter[4].yCenter, -pdbCenter[4].zCenter);

		glPushMatrix();
		displayMultiPDB4();
		glPopMatrix();

		glPopMatrix();
	}*/

	glPopMatrix();

	glutSwapBuffers();
}
