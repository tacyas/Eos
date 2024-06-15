/*
# lmolvieKeyboard : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieKeyboard 
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

static int keyx = 0;
static int keyy = 0;

void lmolvieKeyboard(unsigned char pushkey, int x, int y)	
{
#ifdef KEYBOARD_FUNCTION 

	operationMode operation;

	keyx = x;
	keyy = y;

	operation=operationModeGet();

	if(operation==0){
		lmolvieKeyboardNormal(pushkey, x, y);
	}
	else if(operation==1){
		lmolvieKeyboardDrive(pushkey, x, y);
	}
	else if(operation==2){
		lmolvieKeyboardParallel(pushkey, x, y);
	}
	else if(operation==3){
		lmolvieKeyboardSurface(pushkey, x, y);
	}
	else if(operation==4){
		lmolvieKeyboardMulti(pushkey, x, y);
	}
/*	else if(operation==5){
		myKeyboard5(pushkey, x, y);
	}*/

#endif
/*	if(operation==2){
		glutSetWindow(parallelwindow);
		glutPostRedisplay();
		glutSetWindow(mainwindow);	
	}*/
	if(glutGetWindow() != 0){
	fprintf(stdout,"glutPostRedisplay\n");
		glutPostRedisplay();
	}
	
}

