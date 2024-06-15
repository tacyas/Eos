/*
# lmolvieInitParallel : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieInitParallel 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <math.h>
#include "../inc/eosOpenGL.h"
//#include "./rasmonyo.h"
#include "lmolvie.h"

void
lmolvieInitParallel(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);

	glDepthFunc(GL_LEQUAL);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
