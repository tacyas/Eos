#include<math.h>
#include "lmolvie.h"

static int startx = 0;
static int starty = 0;
static int endx = 0;
static int endy = 0;
static int pressedButton = -1;
static int multiProteinChange;

void
lmolvieMouseMulti(int button, int state, int x, int y)
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
	if(glutGetWindow() != 0){
		glutPostRedisplay();
	}
	
}


void
lmolvieMouseMotionMulti(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	delx = x - startx;
	dely = y - starty;

	multiProteinChange=get_multiProteinChange();

	switch(pressedButton) {
		case GLUT_LEFT_BUTTON: {
			proteinRotateY(delx, multiProteinChange);	
			proteinRotateX(dely, multiProteinChange);
			startx =  x;
			starty =  y;
			break;
		}
		case GLUT_MIDDLE_BUTTON: {
			myCameraRotateY(delx/M_PI/20);	
			myCameraRotateX(dely/M_PI/20);	
			startx =  x;
			starty =  y;
			break;		

		}
		case GLUT_RIGHT_BUTTON: {
			MultiMoveX(delx);
			MultiMoveY(dely);
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
lmolvieMousePassiveMotionMulti(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
	if(glutGetWindow() != 0){
		glutPostRedisplay();
	}	
}

