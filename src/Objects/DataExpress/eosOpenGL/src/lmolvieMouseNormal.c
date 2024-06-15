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
lmolvieMouseNormal(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION
	fprintf(stdout,"lmolvieMouseNormal::%d,%d\n", x, y );
	fprintf(stdout,"state;;%d\n", state);
	switch(state) {
	
		case  GLUT_DOWN: {
			pressedButton = button;
			fprintf(stdout, "GLUT_Down\n");
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
			fprintf(stdout, "GLUT_UP\n");
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
}


void
lmolvieMouseMotionNormal(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	delx = x - startx;
	dely = y - starty;
	fprintf(stdout,"lmolvieMouseMotionNormal:::");
	fprintf(stdout,"pressedButton:%d,startX,Y::%d,%d\n",pressedButton,delx,dely);
	//fprintf(stdout,"pressedButton:%d",pressedButton );
	switch(pressedButton) {
		case GLUT_LEFT_BUTTON: {
			fprintf(stdout,"GLUT_LEFT_BUTOON_MOTION_ROTATE\n");
			myCameraRotateY(delx/M_PI/20);	
			myCameraRotateX(dely/M_PI/20);	
			fprintf(stdout,"GLUT_LEFT_BUTOON_MOTION_neko\n");
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
}


void
lmolvieMousePassiveMotionNormal(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
}


