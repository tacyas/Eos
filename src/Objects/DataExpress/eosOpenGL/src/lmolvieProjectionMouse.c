/*
# lmolvieMouseParallel : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieMouseParallel 
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

extern int mainwindow, parallelwindow;

void
lmolvieProjectionMouse(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION

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

	glutSetWindow(parallelwindow);
	glutPostRedisplay();
	glutSetWindow(mainwindow);	
	glutPostRedisplay();
}


void
lmolvieProjectionMouseMotion(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	delx = x - startx;
	dely = y - starty;

	switch(pressedButton) {
		case GLUT_LEFT_BUTTON: {
			proteinRotateY(-delx, 0);	
			proteinRotateX(-dely, 0);	
			startx =  x;
			starty =  y;
			break;
		}
		case GLUT_MIDDLE_BUTTON: {
			myCameraTranslateX(delx/5.0);
			myCameraTranslateY(dely/5.0);
			startx =  x;
			starty =  y;
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

	glutSetWindow(parallelwindow);
	glutPostRedisplay();
	glutSetWindow(mainwindow);
	glutPostRedisplay();
}


void
lmolvieProjectionMousePassiveMotion(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
	glutSetWindow(parallelwindow);
	glutPostRedisplay();
	glutSetWindow(mainwindow);
	glutPostRedisplay();
}
