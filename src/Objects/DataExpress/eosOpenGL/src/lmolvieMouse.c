/*
# lmolvieMouse : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieMouse 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<math.h>
#include "lmolvie.h"

void
lmolvieMouse(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION
	//fprintf(stdout,"lmolvieMouse::%d,%d\n",x,y);
	operationMode operation;

	operation=operationModeGet();
	fprintf(stdout,"Operation::%d\n",operation);

	if(operation==0){
		lmolvieMouseNormal(button, state, x, y);
	}
	else if(operation==1){
		lmolvieMouseDrive(button, state, x, y);
	}
	else if(operation==2){
		lmolvieMouseParallel(button, state, x, y);
	}
	else if(operation==3){
		lmolvieMouseNormal(button, state, x, y);
	}
/*	else if(operation==4){
		myKeyboard4(pushkey, x, y);
	}
	else if(operation==5){
		myKeyboard5(pushkey, x, y);
	}*/

#endif
	if(glutGetWindow() != 0){
	fprintf(stdout,"lmolvieMouse:glutPostRedisplay::%d\n",glutGetWindow());

		glutPostRedisplay();
	}

}


void
lmolvieMouseMotion(int x, int y)
{
#ifdef MOTION_FUNCTION
	fprintf(stdout,"lmolvieMouseMotion\n");
	operationMode operation;

	operation=operationModeGet();

	if(operation==0){
		lmolvieMouseMotionNormal(x, y);
	}
	else if(operation==1){
		lmolvieMouseMotionDrive(x, y);
	}
	else if(operation==2){
		lmolvieMouseMotionParallel(x, y);
	}
	else if(operation==3){
		lmolvieMouseMotionNormal(x, y);
	}
/*	else if(operation==4){
		myKeyboard4(pushkey, x, y);
	}
	else if(operation==5){
		myKeyboard5(pushkey, x, y);
	}*/

#endif
	if(glutGetWindow() != 0){
		fprintf(stdout,"lmolvieMouseMotion:glutPostRedisplay::%d\n",glutGetWindow());
		glutPostRedisplay();
	}
}


void
lmolvieMousePassiveMotion(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION

	operationMode operation;
fprintf(stdout,"lmolvieMousePassiveMotion\n");
	operation=operationModeGet();
fprintf(stdout,"lmolvieMousePassiveMotion::operation::\n");
	if(operation==0){
		lmolvieMousePassiveMotionNormal(x, y);
	}
	else if(operation==1){
		lmolvieMousePassiveMotionDrive(x, y);
	}
	else if(operation==2){
		lmolvieMousePassiveMotionParallel(x, y);
	}
	else if(operation==3){
		lmolvieMousePassiveMotionNormal(x, y);
	}
/*	else if(operation==4){
		myKeyboard4(pushkey, x, y);
	}
	else if(operation==5){
		myKeyboard5(pushkey, x, y);
	}*/

#endif
	if(glutGetWindow() != 0){
	fprintf(stdout,"lmolvieMousePassiveMotion:glutPostRedisplay::%d\n",glutGetWindow());
		glutPostRedisplay();
	}
}
/******************************************************************/


