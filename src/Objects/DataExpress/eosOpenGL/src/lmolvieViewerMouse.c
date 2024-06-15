/*
# lmolvieMouseNormal : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieMouseNormal 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<math.h>
#include "./lmolvie.h"

static int startx = 0;
static int starty = 0;
static int endx = 0;
static int endy = 0;
static int pressedButton = -1;

void
lmolvieViewerMouse(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION

	fprintf(stdout, "M %d, %d, %d, %d\n", button, state, x, y);

	switch(state) {
		case  GLUT_DOWN: {
			pressedButton = button;
			startx = x;
			starty = y;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					break;
				}
				case GLUT_MIDDLE_BUTTON: {
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
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
					break;
				}	
				case GLUT_MIDDLE_BUTTON: {
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
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
lmolvieViewerMouseMotion(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	fprintf(stdout, "Mo %d, %d\n", x, y);

	delx = x - startx;
	dely = y - starty;

	switch(pressedButton) {
		case GLUT_LEFT_BUTTON: {
			myCameraRotateY(delx/M_PI/20);	
			myCameraRotateX(dely/M_PI/20);	
			startx =  x;
			starty =  y;
			break;
		}
		case GLUT_MIDDLE_BUTTON: {
			break;		

		}
		case GLUT_RIGHT_BUTTON: {
			myCameraEyeRotateX(dely/M_PI/40);
			myCameraEyeRotateY(-delx/M_PI/40);
			startx = x;
			starty = y;
			break;
		}
	}
#endif
	if(glutGetWindow() != 0){
	glutPostRedisplay();
	}
}


void
lmolvieViewerMousePassiveMotion(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif

	fprintf(stdout, "PM %d, %d\n", x, y);
	if(glutGetWindow() != 0){
	glutPostRedisplay();
	}
}
