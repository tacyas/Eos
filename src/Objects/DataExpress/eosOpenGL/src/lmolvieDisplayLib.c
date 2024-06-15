/*
# lmolvieDisplayLib : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieDisplayLib 
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

static GLfloat color[3];

void __getColorRGB(GLfloat color[3], GLdouble index, GLdouble min, GLdouble max)
{
	color[0]=0;/*R*/
	color[1]=0;/*G*/
	color[2]=0;/*B*/
	if(index<=max/2){
		color[2]=-2*index/max+1;
	}
	if(max/4<=index && index<=max/2){
		color[1]=4*index/max-1;
	}
	else if(max/2<=index && index<=3*max/4){
		color[1]=-4*index/max+3;
	}
	if(max/2<=index){
		color[0]=2*index/max-1;
	}
}

void DrawAtomC(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.5, 0.5, 0.5);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " C", 2)==0){
			if(strncmp(pdb->PDB->AtomName, " CA ", 4)==0){
			}
			else{
				glutSolidSphere(0.8, 10, 10);
			}
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawAtomCA(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.4, 0.4, 0.4);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " C", 2)==0){
			if(strncmp(pdb->PDB->AtomName, " CA ", 4)==0){
				glutSolidSphere(0.8, 10, 10);
			}
			else{
			}
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawAtomO(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.6, 0.0, 0.0);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " O", 2)==0){
			glutSolidSphere(0.8, 10, 10);
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawAtomN(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.2, 0.0, 0.6);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " N", 2)==0){
			glutSolidSphere(0.8, 10, 10);
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawAtomS(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.7, 0.7, 0.0);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " S", 2)==0){
			glutSolidSphere(0.8, 10, 10);
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawAtomP(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.8, 0.5, 0.0);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " P", 2)==0){
			glutSolidSphere(0.8, 10, 10);
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawAtomH(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.9, 0.9, 0.9);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " H", 2)==0){
			glutSolidSphere(0.8, 10, 10);
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawAtomFE(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	glColor3f(0.4, 0.6, 0.3);
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->AtomName, " C", 2)==0){}
		else if(strncmp(pdb->PDB->AtomName, " O", 2)==0){}
		else if(strncmp(pdb->PDB->AtomName, " N", 2)==0){}
		else if(strncmp(pdb->PDB->AtomName, " S", 2)==0){}
		else if(strncmp(pdb->PDB->AtomName, " P", 2)==0){}
		else if(strncmp(pdb->PDB->AtomName, " H", 2)==0){}
		else{
			glutSolidSphere(0.8, 10, 10);
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawStick(pdbFile* pdb)
{
	GLint index=0;
        GLint min=0;
        GLint max;
	static char chain_ID='a';

        max=pdb->nAtom;
//	GLfloat color[3];

	pdb->PDB=pdb->top;
	glBegin(GL_LINE_STRIP);
	while(NULL!=pdb->PDB){
		if(strncmp(pdb->PDB->Record, "ENDMDL", 6)==0){
			glEnd();
			glBegin(GL_LINE_STRIP);
		}
		if(pdb->PDB->ChainIdentifier!=chain_ID){
			glEnd();
			glBegin(GL_LINE_STRIP);
		}

		if(strncmp(pdb->PDB->AtomName, " CA ", 4)==0){
			__getColorRGB(color, index, min, max);
//	fprintf(stdout, "%lf %lf %lf\n", color[0], color[1], color[2]);
			glColor3f(color[0], color[1], color[2]);
			glVertex3f(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		}
		if(strncmp(pdb->PDB->Record, "ATOM  ", 6)==0 || strncmp(pdb->PDB->Record, "HETATM", 6)==0){
			index++;
		}
		chain_ID=pdb->PDB->ChainIdentifier;
		pdb->PDB=pdb->PDB->next;
//		fprintf(stdout, "index=%d\n", index);
	}
	glEnd();
}

void DrawAtomSerial(pdbFile* pdb)
{
	GLint index=0;
        GLint min=0;
        GLint max;

        max=pdb->nAtom;
	pdb->PDB=pdb->top;
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		__getColorRGB(color, index, min, max);
		glColor3f(color[0], color[1], color[2]);
		glutSolidSphere(0.8, 10, 10);
		if(strncmp(pdb->PDB->Record, "ATOM  ", 6)==0 || strncmp(pdb->PDB->Record, "HETATM", 6)==0){
			index++;
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawResidue(pdbFile* pdb)
{
	pdb->PDB=pdb->top;
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(strncmp(pdb->PDB->ResidueName, "LYS", 3)==0 || strncmp(pdb->PDB->ResidueName, "ARG", 3)==0 || strncmp(pdb->PDB->ResidueName, "HIS", 3)==0){
			glColor3f(0.2, 0.0, 0.6);
			glutSolidSphere(0.8, 10, 10);
		}
		else if(strncmp(pdb->PDB->ResidueName, "ASP", 3)==0 || strncmp(pdb->PDB->ResidueName, "GLU", 3)==0){
			glColor3f(0.6, 0.0, 0.0);
			glutSolidSphere(0.8, 10, 10);
		}
		else if(strncmp(pdb->PDB->ResidueName, "SER", 3)==0 || strncmp(pdb->PDB->ResidueName, "THR", 3)==0){
			glColor3f(0.4, 0.6, 0.3);
			glutSolidSphere(0.8, 10, 10);
		}
		else if(strncmp(pdb->PDB->ResidueName, "CYS", 3)==0 || strncmp(pdb->PDB->ResidueName, "MET", 3)==0){
			glColor3f(0.7, 0.7, 0.0);
			glutSolidSphere(0.8, 10, 10);
		}
		else{
			glColor3f(0.5, 0.5, 0.5);
			glutSolidSphere(0.8, 10, 10);
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawTemp(pdbFile* pdb)
{
	GLdouble max, min;

	pdb->PDB=pdb->top;
	max=pdb->PDB->TemperatureFactor;
	min=pdb->PDB->TemperatureFactor;
	while(NULL!=pdb->PDB){
		if(pdb->PDB->TemperatureFactor > max){
			max=pdb->PDB->TemperatureFactor;
		}
		else if(min > pdb->PDB->TemperatureFactor){
			min=pdb->PDB->TemperatureFactor;
		}
		pdb->PDB=pdb->PDB->next;
	}

	pdb->PDB=pdb->top;
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		__getColorRGB(color, pdb->PDB->TemperatureFactor, min, max);
		glColor3f(color[0], color[1], color[2]);
		glutSolidSphere(0.8, 10, 10);
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}

void DrawStickTemp(pdbFile* pdb)
{
	GLdouble max, min;
	static char chain_ID='a';

	pdb->PDB=pdb->top;
	max=pdb->PDB->TemperatureFactor;
	min=pdb->PDB->TemperatureFactor;
	while(NULL!=pdb->PDB){
		if(pdb->PDB->TemperatureFactor > max){
			max=pdb->PDB->TemperatureFactor;
		}
		else if(min > pdb->PDB->TemperatureFactor){
			min=pdb->PDB->TemperatureFactor;
		}
		pdb->PDB=pdb->PDB->next;
	}

	pdb->PDB=pdb->top;
	glBegin(GL_LINE_STRIP);
	while(NULL!=pdb->PDB){
		if(strncmp(pdb->PDB->Record, "ENDMDL", 6)==0){
			glEnd();
			glBegin(GL_LINE_STRIP);
		}
		if(pdb->PDB->ChainIdentifier!=chain_ID){
			glEnd();
			glBegin(GL_LINE_STRIP);
		}

		if(strncmp(pdb->PDB->AtomName, " CA ", 4)==0){
			__getColorRGB(color, pdb->PDB->TemperatureFactor, min, max);
			glColor3f(color[0], color[1], color[2]);
			glVertex3f(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		}
		chain_ID=pdb->PDB->ChainIdentifier;
		pdb->PDB=pdb->PDB->next;
	}
	glEnd();
}

void DrawStickResidue(pdbFile* pdb)
{
	static char chain_ID='a';

	pdb->PDB=pdb->top;
	glBegin(GL_LINE_STRIP);
	while(NULL!=pdb->PDB){
		if(strncmp(pdb->PDB->Record, "ENDMDL", 6)==0){
			glEnd();
			glBegin(GL_LINE_STRIP);
		}
		if(pdb->PDB->ChainIdentifier!=chain_ID){
			glEnd();
			glBegin(GL_LINE_STRIP);
		}

		if(strncmp(pdb->PDB->AtomName, " CA ", 4)==0){
			if(strncmp(pdb->PDB->ResidueName, "LYS", 3)==0 || strncmp(pdb->PDB->ResidueName, "ARG", 3)==0 || strncmp(pdb->PDB->ResidueName, "HIS", 3)==0){
				glColor3f(0.2, 0.0, 0.6);
			}
			else if(strncmp(pdb->PDB->ResidueName, "ASP", 3)==0 || strncmp(pdb->PDB->ResidueName, "GLU", 3)==0){
				glColor3f(0.6, 0.0, 0.0);
			}
			else if(strncmp(pdb->PDB->ResidueName, "SER", 3)==0 || strncmp(pdb->PDB->ResidueName, "THR", 3)==0){
				glColor3f(0.4, 0.6, 0.3);
			}
			else if(strncmp(pdb->PDB->ResidueName, "CYS", 3)==0 || strncmp(pdb->PDB->ResidueName, "MET", 3)==0){
				glColor3f(0.7, 0.7, 0.0);
			}
			else{
				glColor3f(0.5, 0.5, 0.5);
			}
			glVertex3f(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		}
		chain_ID=pdb->PDB->ChainIdentifier;
		pdb->PDB=pdb->PDB->next;
	}
	glEnd();
}

/*`void DrawDistanceFromTarget(pdbFile* pdb)
{
	GLdouble max=0, min=0, distance;

	pdb->PDB=pdb->top;
	while(NULL!=pdb->PDB){
		distance=sqrt((check_x-pdb->PDB->Coord.x)*(check_x-pdb->PDB->Coord.x)+(check_y-pdb->PDB->Coord.y)*(check_y-pdb->PDB->Coord.y)+(check_z-pdb->PDB->Coord.z)*(check_z-pdb->PDB->Coord.z));

		if(max<distance){
			max=distance;
		}
		pdb->PDB=pdb->PDB->next;
	}

	pdb->PDB=pdb->top;
	while(NULL!=pdb->PDB){
		distance=sqrt((check_x-pdb->PDB->Coord.x)*(check_x-pdb->PDB->Coord.x)+(check_y-pdb->PDB->Coord.y)*(check_y-pdb->PDB->Coord.y)+(check_z-pdb->PDB->Coord.z)*(check_z-pdb->PDB->Coord.z));

		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		__getColorRGB(color, distance, min, max);
		glColor3f(color[0], color[1], color[2]);
		glutSolidSphere(0.8, 10, 10);
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}*/

void DrawChain(pdbFile* pdb)
{
	static GLint index=0;
	GLint true_index;
        GLint min=1;
        GLint max=0;
//	GLfloat color[3];
	static char chain_ID='a';

	pdb->PDB=pdb->top;
	while(NULL!=pdb->PDB){
		if(strcmp(pdb->PDB->Record, "ATOM  ") == 0 || strcmp(pdb->PDB->Record, "HETATM") == 0) {
			if(pdb->PDB->ChainIdentifier!=chain_ID){
				chain_ID=pdb->PDB->ChainIdentifier;
				max++;
			}
		}
		pdb->PDB=pdb->PDB->next;
	}

	fprintf(stdout, "%d\n", max);

	chain_ID='a';

//	max=pdb->nChain;
	pdb->PDB=pdb->top;
	while(NULL!=pdb->PDB){
		glPushMatrix();
		glTranslatef(pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
		if(index%2==0){
			true_index=(max+min)-index;
		}
		else{
			true_index=index;
		}
		__getColorRGB(color, true_index, min, max);
		glColor3f(color[0], color[1], color[2]);
		glutSolidSphere(0.8, 10, 10);
		if(strcmp(pdb->PDB->Record, "ATOM  ") == 0 || strcmp(pdb->PDB->Record, "HETATM") == 0){
			if(pdb->PDB->ChainIdentifier!=chain_ID){
				chain_ID=pdb->PDB->ChainIdentifier;
				index++;
			}
		}
		pdb->PDB=pdb->PDB->next;
		glPopMatrix();
	}
}
