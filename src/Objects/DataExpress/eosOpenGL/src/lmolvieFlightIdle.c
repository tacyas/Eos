/*
# lmolvieIdleNormal : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieIdleNormal 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "./lmolvie.h"
#include <stdio.h>

static int __accelerator=0;

void lmolvieFlightIdle(void)
{
#ifdef IDLE_FUNCTION
#endif
	if(__accelerator==1){
		moveDriveMyCamera(1.0);
	}
	else if(__accelerator==2){
		moveDriveMyCamera(-1.0);
	}
	if(glutGetWindow != 0){
	glutPostRedisplay();
	}
}

void setFlightDriveAccelerator(int accelerator)
{
	__accelerator=accelerator;
}
