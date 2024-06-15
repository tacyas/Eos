/*
# lmolvieProteinStatus.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieProteinStatus.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "pdbFile.h"

typedef struct pdbCenter{
	GLfloat xCenter;
	GLfloat yCenter;
	GLfloat zCenter;
	GLfloat xMax;
	GLfloat xMin;
	GLfloat xWidth;
	GLfloat yMax;
	GLfloat yMin;
	GLfloat yWidth;
	GLfloat zMax;
	GLfloat zMin;
	GLfloat zWidth;
}pdbCenter;

typedef struct elementSwitch{
	GLint elementC;
	GLint elementO;
	GLint elementN;
	GLint elementS;
	GLint elementP;
	GLint elementH;
	GLint elementFE;
}elementSwitch;

typedef struct ProteinStatus {
	pdbCenter __pdbCenter;
	elementSwitch __elementSwitch;
	GLint spin_x;
	GLint spin_y;
	GLint spin_z;
	GLfloat move_x;
	GLfloat move_y;
//	GLfloat move_z;
} ProteinStatus;

extern void lmolvieDisplayNormal(void);
extern pdbCenter getpdbCenter(int returnID);
extern void putpdbCenter(pdbFile* putpdbfile);
extern void proteinInit();
extern elementSwitch get_elementSwitch(int ID);
extern void put_elementSwitch(int ID, char atom);
extern int getSpin_x(int pdbID);
extern int getSpin_y(int pdbID);
extern int getSpin_z(int pdbID);
extern void proteinRotateX(int pan, int pdbID);
extern void proteinRotateY(int pan, int pdbID);
extern void proteinRotateZ(int pan, int pdbID);
extern int getMultiMoveX(int pdbID);
extern int getMultiMoveY(int pdbID);
extern void MultiMoveX(GLint move);
extern void MultiMoveY(GLint move);
extern void saveproteinStatus(ProteinStatus saveprotein);
extern void texture();
