/*
# lmolvieViewerSpecial : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieViewerSpecial 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"

void
lmolvieViewerSpecial(int pushkey,
		int x,
		int y)
{
	fprintf(stdout, "%d:\n", pushkey);

	glutPostRedisplay();
}
