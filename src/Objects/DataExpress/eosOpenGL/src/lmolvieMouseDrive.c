/*
# lmolvieMouseDrive : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieMouseDrive 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<math.h>
#include "lmolvie.h"

static int startx = 0;
static int starty = 0;
static int endx = 0;
static int endy = 0;
static int pressedButton = -1;

void
lmolvieMouseDrive(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION

	switch(state) {
		case  GLUT_DOWN: {
			pressedButton = button;
			startx = x;
			starty = y;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					setDriveAccelerator(1);
					break;
				}	
				case GLUT_MIDDLE_BUTTON: {
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
					setDriveAccelerator(2);
					break;
				}	
			}
			break;
		}
		case GLUT_UP: {
			endx = x;
			endy = y;
			pressedButton = -1;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					setDriveAccelerator(0);
					break;
				}	
				case GLUT_MIDDLE_BUTTON: {
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
					setDriveAccelerator(0);
					break;
				}	
			}
			break;
		}
	}	
#endif	
	if(glutGetWindow() != 0){
		glutPostRedisplay();
	}
}


void
lmolvieMouseMotionDrive(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	delx = x - startx;
	dely = y - starty;

	switch(pressedButton) {
		case GLUT_LEFT_BUTTON: {
			myCameraEyeRotateX(dely/M_PI/40);
			myCameraEyeRotateY(-delx/M_PI/40);
			startx = x;
			starty = y;
			break;
		}
		case GLUT_MIDDLE_BUTTON: {
			myCameraEyeRotateX(dely/M_PI/40);
			myCameraEyeRotateY(-delx/M_PI/40);
			startx = x;
			starty = y;
			break;		

		}
		case GLUT_RIGHT_BUTTON: {
			myCameraRotateY(delx/M_PI/20);	
			myCameraRotateX(dely/M_PI/20);	
			startx =  x;
			starty =  y;
			break;
		}
	}
#endif
	if(glutGetWindow() != 0){
		glutPostRedisplay();
	}
}


void
lmolvieMousePassiveMotionDrive(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
	if(glutGetWindow() != 0){
		glutPostRedisplay();
	}
}


