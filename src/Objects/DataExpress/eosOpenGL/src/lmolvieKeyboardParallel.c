/*
# lmolvieKeyboardParallel : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieKeyboardParallel 
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

int mainwindow, parallelwindow;

void
lmolvieKeyboardParallel(unsigned char pushkey,
		int x,
		int y)	/*parallel mode*/
{
	if(pushkey!='w' && pushkey!='e'){
		fprintf(stdout, "%c:", pushkey);
	}

	switch(pushkey) {
		case 'q': {
			fprintf(stdout, "quit.\n");
			exit(EXIT_FAILURE);
			break;
		}

		case 'n': {
			glutDestroyWindow(parallelwindow);
			operationModeSet(0);
			setCameraCentreTag(2);
			fprintf(stdout, "(ModeChange) Normal mode\n");
			break;
		}

		case 's': {
			fprintf(stdout, "save BITMAP.\n");
//			glutCreateSubWindow(2, 100, 100, 20, 20);
//			saveBitmap();
			if(glutGetWindow() != 0){
				glutSetWindow(parallelwindow);
				savePPM();
				glutSetWindow(mainwindow);
			}
	
			
			break;
		}

		case 'l': {
//			glutSetWindow(parallelwindow);
//			glutCreateSubWindow(2, 100, 100, 20, 20);
//			loadBitmap();
//			loadPPM();

//			operationModeSet(2);
/*			glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
			glutInitWindowSize(200, 200);  
			glutInitWindowPosition(610, 210); 
			parallelwindow=glutCreateWindow("load");
			parallelInit();
			glutIdleFunc(myIdle);
//			glutKeyboardFunc(myKeyboard);
//			glutSpecialFunc(moveKeyboard);
//			glutMouseFunc(myMouse);
//			glutMotionFunc(myMouseMotion);
//			glutPassiveMotionFunc(myMousePassiveMotion);
			glutDisplayFunc(loadBitmap);
			glutReshapeFunc(parallelReshape);

			glutSetWindow(mainwindow);
			glutPostRedisplay();/*main ni naranai*/

//			glutCreateSubWindow(1, 600, 0, 500, 500);
			fprintf(stdout, "(ModeChange) Parallel mode\n");
			break;
		}

		case 'r': {
			resetMyCamera();
			fprintf(stdout, "camera reset.\n");
			break;
		}

		case 'w': {
			//myCameraRotateX(1.0/M_PI);
			moveMyCamera(1.0);
			break;
		}
		case 'e': {
			//myCameraRotateX(1.0/M_PI);
			moveMyCamera(-1.0);
			break;
		}

		case 'u': {
			fprintf(stdout, "texture scale up.\n");
			texture_scale_change(0.01);
			break;
		}
		case 'd': {
			fprintf(stdout, "texture scale down.\n");
			texture_scale_change(-0.01);
			break;
		}

		case 'g': {
			fprintf(stdout, "texture translate.\n");
			texture_translate_x(0.5);
			break;
		}
		case 'j': {
			fprintf(stdout, "texture translate.\n");
			texture_translate_x(-0.5);
			break;
		}
		case 'y': {
			fprintf(stdout, "texture translate.\n");
			texture_translate_y(0.5);
			break;
		}
		case 'h': {
			fprintf(stdout, "texture translate.\n");
			texture_translate_y(-0.5);
			break;
		}

		case 'i': {
			fprintf(stdout, "scale up.\n");
			scale_change(0.01);
			break;
		}
		case 'k': {
			fprintf(stdout, "scale down.\n");
			scale_change(-0.01);
			break;
		}

		default: {
			fprintf(stdout, "\n");
			break;
		}
	}
	if(glutGetWindow() != 0){
		glutSetWindow(parallelwindow);
		glutPostRedisplay();
		glutSetWindow(mainwindow);
	}
	
		
}
