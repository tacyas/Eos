/*
# lmolvieReshapeNormal : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieReshapeNormal 
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

void
lmolvieReshapeNormal(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (double)width/height, 0.1, 500);
//	glOrtho(20, -20, 20, -20, 1, 500);

	glViewport(0, 0, width, height);
}
