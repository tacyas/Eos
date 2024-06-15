/*
# drawWireFrame : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : drawWireFrame 
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

typedef enum atomname{
	N=0,
	CA,
	C,
	O,
	CB,
	CG,
	CD,
	CE,
	NZ
}atomname;

typedef struct atomCoord {
	float x;
	float y;
	float z;
} atomCoord;

void DrawLYS(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[9];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD ", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE ", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " NZ ", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawARG(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[11];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD ", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " NE ", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CZ ", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " NH1", 4)==0){/*NZ*/
		atom[9].x=__atomCoord.x;
		atom[9].y=__atomCoord.y;
		atom[9].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " NH2", 4)==0){/*NZ*/
		atom[10].x=__atomCoord.x;
		atom[10].y=__atomCoord.y;
		atom[10].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glVertex3f(atom[9].x, atom[9].y, atom[9].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glVertex3f(atom[10].x, atom[10].y, atom[10].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawASP(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[8];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OD1", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OD2", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawGLU(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[9];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD ", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OE1", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OE2", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawALA(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[5];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawVAL(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[7];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG1", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG2", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawPHE(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[11];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD1", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD2", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE1", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE2", 4)==0){/*NZ*/
		atom[9].x=__atomCoord.x;
		atom[9].y=__atomCoord.y;
		atom[9].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CZ ", 4)==0){/*NZ*/
		atom[10].x=__atomCoord.x;
		atom[10].y=__atomCoord.y;
		atom[10].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glVertex3f(atom[10].x, atom[10].y, atom[10].z);
		glVertex3f(atom[9].x, atom[9].y, atom[9].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawPRO(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[7];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD ", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawMET(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[8];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " SD ", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE ", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawILE(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[8];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG1", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG2", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD1", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawLEU(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[8];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD1", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD2", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);

		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawSER(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[6];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawTHR(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[7];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OG1", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG2", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawTYR(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[12];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD1", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD2", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE1", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE2", 4)==0){/*NZ*/
		atom[9].x=__atomCoord.x;
		atom[9].y=__atomCoord.y;
		atom[9].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CZ ", 4)==0){/*NZ*/
		atom[10].x=__atomCoord.x;
		atom[10].y=__atomCoord.y;
		atom[10].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OH ", 4)==0){/*NZ*/
		atom[11].x=__atomCoord.x;
		atom[11].y=__atomCoord.y;
		atom[11].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glVertex3f(atom[10].x, atom[10].y, atom[10].z);
		glVertex3f(atom[9].x, atom[9].y, atom[9].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[10].x, atom[10].y, atom[10].z);
		glVertex3f(atom[11].x, atom[11].y, atom[11].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawHIS(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[10];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " ND1", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD2", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE1", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " NE2", 4)==0){/*NZ*/
		atom[9].x=__atomCoord.x;
		atom[9].y=__atomCoord.y;
		atom[9].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glVertex3f(atom[9].x, atom[9].y, atom[9].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawCYS(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[6];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " SG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawASN(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[8];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OD1", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " ND2", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawGLN(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[9];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD ", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " OE1", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " NE2", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawTRP(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[14];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CB ", 4)==0){/*CB*/
		atom[4].x=__atomCoord.x;
		atom[4].y=__atomCoord.y;
		atom[4].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CG ", 4)==0){/*CG*/
		atom[5].x=__atomCoord.x;
		atom[5].y=__atomCoord.y;
		atom[5].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD1", 4)==0){/*CD*/
		atom[6].x=__atomCoord.x;
		atom[6].y=__atomCoord.y;
		atom[6].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CD2", 4)==0){/*CE*/
		atom[7].x=__atomCoord.x;
		atom[7].y=__atomCoord.y;
		atom[7].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " NE1", 4)==0){/*NZ*/
		atom[8].x=__atomCoord.x;
		atom[8].y=__atomCoord.y;
		atom[8].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE2", 4)==0){/*NZ*/
		atom[9].x=__atomCoord.x;
		atom[9].y=__atomCoord.y;
		atom[9].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CE3", 4)==0){/*NZ*/
		atom[10].x=__atomCoord.x;
		atom[10].y=__atomCoord.y;
		atom[10].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CZ2", 4)==0){/*NZ*/
		atom[11].x=__atomCoord.x;
		atom[11].y=__atomCoord.y;
		atom[11].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CZ3", 4)==0){/*NZ*/
		atom[12].x=__atomCoord.x;
		atom[12].y=__atomCoord.y;
		atom[12].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CH2", 4)==0){/*NZ*/
		atom[13].x=__atomCoord.x;
		atom[13].y=__atomCoord.y;
		atom[13].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[4].x, atom[4].y, atom[4].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glVertex3f(atom[6].x, atom[6].y, atom[6].z);
		glVertex3f(atom[8].x, atom[8].y, atom[8].z);
		glVertex3f(atom[9].x, atom[9].y, atom[9].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glVertex3f(atom[5].x, atom[5].y, atom[5].z);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[9].x, atom[9].y, atom[9].z);
		glVertex3f(atom[11].x, atom[11].y, atom[11].z);
		glVertex3f(atom[13].x, atom[13].y, atom[13].z);
		glVertex3f(atom[12].x, atom[12].y, atom[12].z);
		glVertex3f(atom[10].x, atom[10].y, atom[10].z);
		glVertex3f(atom[7].x, atom[7].y, atom[7].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawGLY(pdbCoord __atomCoord, char __atomName[4+1])
{
	static atomCoord atom[4];
	int DrawKey=0;

//	fprintf(stdout, "%s", __atomName);

	if(strncmp(__atomName, " N  ", 4)==0){/*N*/
		atom[0].x=__atomCoord.x;
		atom[0].y=__atomCoord.y;
		atom[0].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " CA ", 4)==0){/*CA*/
		atom[1].x=__atomCoord.x;
		atom[1].y=__atomCoord.y;
		atom[1].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " C  ", 4)==0){/*C*/
		atom[2].x=__atomCoord.x;
		atom[2].y=__atomCoord.y;
		atom[2].z=__atomCoord.z;
	}
	if(strncmp(__atomName, " O  ", 4)==0){/*O*/
		atom[3].x=__atomCoord.x;
		atom[3].y=__atomCoord.y;
		atom[3].z=__atomCoord.z;
		DrawKey=1;
	}

	if(DrawKey==1){
		glBegin(GL_LINE_STRIP);
		glVertex3f(atom[0].x, atom[0].y, atom[0].z);
		glVertex3f(atom[1].x, atom[1].y, atom[1].z);
		glVertex3f(atom[2].x, atom[2].y, atom[2].z);
		glVertex3f(atom[3].x, atom[3].y, atom[3].z);
		glEnd();
		DrawKey=0;
	}
}

void DrawWireFrame(pdbFile* pdb)
{
	char residue[3]="AAA";
	atomCoord n, c;
	int cKey=0;

	pdb->PDB=pdb->top;
//	residue=pdb->PDB->ResidueName;
	while(NULL!=pdb->PDB){
		if(strncmp(pdb->PDB->ResidueName, residue, 3)!=0){
//			residue=pdb->PDB->ResidueName;
		}

		glColor3f(0.5, 0.5, 0.5);

		glPushMatrix();
		if(strncmp(pdb->PDB->ResidueName, "LYS", 3)==0){
			glColor3f(0.2, 0.0, 0.6);
			DrawLYS(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "ARG", 3)==0){
			glColor3f(0.2, 0.0, 0.6);
			DrawARG(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "ASP", 3)==0){
			glColor3f(0.6, 0.0, 0.0);
			DrawASP(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "GLU", 3)==0){
			glColor3f(0.6, 0.0, 0.0);
			DrawGLU(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "ALA", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawALA(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "VAL", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawVAL(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "PHE", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawPHE(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "PRO", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawPRO(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "MET", 3)==0){
			glColor3f(0.7, 0.7, 0.0);
			DrawMET(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "ILE", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawILE(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "LEU", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawLEU(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "SER", 3)==0){
			glColor3f(0.4, 0.6, 0.3);
			DrawSER(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "THR", 3)==0){
			glColor3f(0.4, 0.6, 0.3);
			DrawTHR(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "TYR", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawTYR(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "HIS", 3)==0){
			glColor3f(0.2, 0.0, 0.6);
			DrawHIS(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "CYS", 3)==0){
			glColor3f(0.7, 0.7, 0.0);
			DrawCYS(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "ASN", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawASN(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "GLN", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawGLN(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "TRP", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawTRP(pdb->PDB->Coord, pdb->PDB->AtomName);
		}
		else if(strncmp(pdb->PDB->ResidueName, "GLY", 3)==0){
			glColor3f(0.5, 0.5, 0.5);
			DrawGLY(pdb->PDB->Coord, pdb->PDB->AtomName);
		}

		if(strncmp(pdb->PDB->AtomName, " C  ", 4)==0){
			c.x=pdb->PDB->Coord.x;
			c.y=pdb->PDB->Coord.y;
			c.z=pdb->PDB->Coord.z;
			cKey=1;
		}
		if(cKey==1){
			if(strncmp(pdb->PDB->AtomName, " N  ", 4)==0){
				n.x=pdb->PDB->Coord.x;
				n.y=pdb->PDB->Coord.y;
				n.z=pdb->PDB->Coord.z;

				glBegin(GL_LINE_STRIP);
				glVertex3f(c.x, c.y, c.z);
				glVertex3f(n.x, n.y, n.z);
				glEnd();

				cKey=0;
			}
		}

		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}
