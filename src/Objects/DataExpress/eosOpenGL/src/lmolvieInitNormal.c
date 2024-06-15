/*
# lmolvieInitNormal : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieInitNormal 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"

void
lmolvieInitNormal(void)
{
	lmolvieLightSet();

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glShadeModel(GL_SMOOTH);
//	glShadeModel(GL_FLAT);

	glDepthFunc(GL_LEQUAL);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
