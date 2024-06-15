/*
# lmolvieReshapeParallel : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieReshapeParallel 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <math.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
//#include "./proteinStatus.h"

//static pdbCenter __pdbCenter;

void
lmolvieReshapeParallel(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

//	__pdbCenter=getpdbCenter(0);

//	gluPerspective(45, (double)width/height, 1, 500);
//	glOrtho(__pdbCenter.xMin, __pdbCenter.xMax, __pdbCenter.yMin, __pdbCenter.yMax, 1, 500);
	glOrtho(-128, 128, -128, 128, 1, 1000);
	glViewport(0, 0, width, height);
}
