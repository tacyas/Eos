#include <stdlib.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
#include "pdbFile.h"

static pdbFile* pdbIn1;

//static GLuint pdbcount=1;

static GLuint drawatomc=16;
static GLuint drawatomca=17;
static GLuint drawatomo=18;
static GLuint drawatomn=19;
static GLuint drawatoms=20;
static GLuint drawatomp=21;
static GLuint drawatomh=22;
static GLuint drawatomfe=23;
static GLuint drawstick=24;
static GLuint drawatomserial=25;
static GLuint drawresidue=26;
static GLuint drawtemp=27;
static GLuint drawsticktemp=28;
static GLuint drawstickresidue=29;
static GLuint drawsurface=30;

static GLboolean needDisplayListMakingAtom=GL_TRUE;
static GLboolean needDisplayListMakingAtomSerial=GL_TRUE;
static GLboolean needDisplayListMakingResidue=GL_TRUE;
static GLboolean needDisplayListMakingTemp=GL_TRUE;
static GLboolean needDisplayListMakingStickTemp=GL_TRUE;
static GLboolean needDisplayListMakingStickResidue=GL_TRUE;
static GLboolean needDisplayListMakingSurface=GL_TRUE;

void loadPDB1()
{
/*	pdbIn1=(pdbFile**)malloc(5*sizeof(pdbFile*));
	for(i=0; i<5; i++){
		pdbIn1[i]= (pdbFile*)malloc(sizeof(pdbFile));}*/
//	pdbIn1=(pdbFile*)malloc(sizeof(pdbFile));

	pdbIn1 = (pdbFile*)malloc(sizeof(pdbFile));

	newPDBload(pdbIn1);
	putpdbCenter(pdbIn1);
	proteinInit();

	setMultiPDBloadD(1);
}

void myDisplayListMakeAtom1(void)
{
	glNewList(drawatomc, GL_COMPILE);
	DrawAtomC(pdbIn1);
	glEndList();
	glNewList(drawatomca, GL_COMPILE);
	DrawAtomCA(pdbIn1);
	glEndList();
	glNewList(drawatomo, GL_COMPILE);
	DrawAtomO(pdbIn1);
	glEndList();
	glNewList(drawatomn, GL_COMPILE);
	DrawAtomN(pdbIn1);
	glEndList();
	glNewList(drawatoms, GL_COMPILE);
	DrawAtomS(pdbIn1);
	glEndList();
	glNewList(drawatomp, GL_COMPILE);
	DrawAtomP(pdbIn1);
	glEndList();
	glNewList(drawatomh, GL_COMPILE);
	DrawAtomH(pdbIn1);
	glEndList();
	glNewList(drawatomfe, GL_COMPILE);
	DrawAtomFE(pdbIn1);
	glEndList();
	glNewList(drawstick, GL_COMPILE);
	DrawStick(pdbIn1);
	glEndList();
	needDisplayListMakingAtom=GL_FALSE;
}

void myDisplayListMakeAtomSerial1(void)
{
	glNewList(drawatomserial, GL_COMPILE);
  	DrawAtomSerial(pdbIn1);
	glEndList();
	needDisplayListMakingAtomSerial=GL_FALSE;
}

void myDisplayListMakeResidue1(void)
{
	glNewList(drawresidue, GL_COMPILE);
	DrawResidue(pdbIn1);
	glEndList();
	needDisplayListMakingResidue=GL_FALSE;
}

void myDisplayListMakeTemp1(void)
{
	glNewList(drawtemp, GL_COMPILE);
	DrawTemp(pdbIn1);
	glEndList();
	needDisplayListMakingTemp=GL_FALSE;
}

void myDisplayListMakeStickTemp1(void)
{
	glNewList(drawsticktemp, GL_COMPILE);
	DrawStickTemp(pdbIn1);
	glEndList();
	needDisplayListMakingStickTemp=GL_FALSE;
}

void myDisplayListMakeStickResidue1(void)
{
	glNewList(drawstickresidue, GL_COMPILE);
	DrawStickResidue(pdbIn1);
	glEndList();
	needDisplayListMakingStickResidue=GL_FALSE;
}

/*void myDisplayListMakeSurface1(void)
{
	glNewList(drawsurface, GL_COMPILE);
	dsn6frompdb2marching();
	glEndList();
	needDisplayListMakingSurface=GL_FALSE;
}

void reset_needDisplayListMakingSurface1(void)
{
	needDisplayListMakingSurface=GL_TRUE;
}*/

void displayMultiPDB1(){
//	pdbCenter __pdbCenter;
	displayMode display;

//	__pdbCenter=getpdbCenter(0);
	display=displayModeGet(1);

	if(needDisplayListMakingAtom==GL_TRUE){
		myDisplayListMakeAtom1();
	}

	glPushMatrix();

//	glTranslatef(0, 0, __pdbCenter.zCenter);
//	glRotated(spin_x, 1.0, 0.0, 0.0);
//	glRotated(spin_y, 0.0, 1.0, 0.0);

	if(display==1){
		glPushMatrix();
		glCallList(drawatomc);
		glCallList(drawatomca);
		glCallList(drawatomo);
		glCallList(drawatomn);
		glCallList(drawatoms);
		glCallList(drawatomp);
		glCallList(drawatomh);
		glCallList(drawatomfe);
		glPopMatrix();
	}

	else if(display==2){
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(drawstick);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	else if(display==3){
		if(needDisplayListMakingAtomSerial==GL_TRUE){
			myDisplayListMakeAtomSerial1();
		}
		glPushMatrix();
		glCallList(drawatomserial);
		glPopMatrix();
	}

	else if(display==4){
		if(needDisplayListMakingResidue==GL_TRUE){
			myDisplayListMakeResidue1();
		}
		glPushMatrix();
		glCallList(drawresidue);
		glPopMatrix();
	}

	else if(display==5){
		if(needDisplayListMakingTemp==GL_TRUE){
			myDisplayListMakeTemp1();
		}
		glPushMatrix();
		glCallList(drawtemp);
		glPopMatrix();
	}

	else if(display==6){
		if(needDisplayListMakingStickTemp==GL_TRUE){
			myDisplayListMakeStickTemp1();
		}
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(drawsticktemp);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	else if(display==7){
		if(needDisplayListMakingStickResidue==GL_TRUE){
			myDisplayListMakeStickResidue1();
		}
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glCallList(drawstickresidue);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	glPopMatrix();
}
