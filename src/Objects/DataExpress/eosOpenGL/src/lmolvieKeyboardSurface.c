/*
# lmolvieKeyboardNormal : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieKeyboardNormal 
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

extern int mainwindow, parallelwindow;

void
lmolvieKeyboardSurface(unsigned char pushkey,
		int x,
		int y)	/*surface mode*/
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
			operationModeSet(0);
			fprintf(stdout, "(ModeChange) Normal mode\n");
			break;
		}
		case 'd': {
			operationModeSet(1);
			setDriveMyCamera();
			setCameraCentreTag(0);
			fprintf(stdout, "(ModeChange) Drive mode\n");
			break;
		}
/*		case 'l': {
			resetMyCamera();
			operationModeSet(2);
			setCameraCentreTag(0);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
			glutInitWindowSize(256, 256);  
			glutInitWindowPosition(610, 0); 
			parallelwindow=glutCreateWindow("picture");
			parallelInit();
			glutIdleFunc(myIdle);
			glutDisplayFunc(parallelDisplay);
//			glutDisplayFunc(myDisplay);
			glutReshapeFunc(parallelReshape);

			glutSetWindow(mainwindow);
			glutPostRedisplay();//main ni naranai

//			glutCreateSubWindow(1, 600, 0, 500, 500);
			fprintf(stdout, "(ModeChange) Parallel mode\n");
			break;
		}*/
		case '0': {
			displayModeSet(0, 0);
			fprintf(stdout, "(DisplayModeChange) NoneAtom mode\n");
			break;
		}
		case '1': {
			displayModeSet(0, 1);
			fprintf(stdout, "(DisplayModeChange) Atom mode\n");
			break;
		}
		case '5': {
			displayModeSet(0, 2);
			fprintf(stdout, "(DisplayModeChange) CStickNumber mode\n");
			break;
		}
		case '2': {
			displayModeSet(0, 3);
			fprintf(stdout, "(DisplayModeChange) Number mode\n");
			break;
		}
		case '3': {
			displayModeSet(0, 4);
			fprintf(stdout, "(DisplayModeChange) AminoAcid mode\n");
			break;
		}
		case '4': {
			displayModeSet(0, 5);
			fprintf(stdout, "(DisplayModeChange) Temperature mode\n");
			break;
		}
		case '7': {
			displayModeSet(0, 6);
			fprintf(stdout, "(DisplayModeChange) CStickTemperature mode\n");
			break;
		}
		case '6': {
			displayModeSet(0, 7);
			fprintf(stdout, "(DisplayModeChange) CStickAminoAcid mode\n");
			break;
		}
		case 'v': {
			//lmolvieVoice();
			fprintf(stdout, "voice!\n");
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
		case 'y': {
			fprintf(stdout, "Density +0.1\n");
			incrementDensity(0.1);
			reset_needDisplayListMakingSurface();
			break;
		}
		case 'h': {
			fprintf(stdout, "Density -0.1\n");
			incrementDensity(-0.1);
			reset_needDisplayListMakingSurface();
			break;
		}
		case 'u': {
			fprintf(stdout, "Density +1.0\n");
			incrementDensity(1.0);
			reset_needDisplayListMakingSurface();
			break;
		}
		case 'j': {
			fprintf(stdout, "Density -1.0\n");
			incrementDensity(-1.0);
			reset_needDisplayListMakingSurface();
			break;
		}
		case 'i': {
			fprintf(stdout, "Density +10.0\n");
			incrementDensity(10.0);
			reset_needDisplayListMakingSurface();
			break;
		}
		case 'k': {
			fprintf(stdout, "Density -10.0\n");
			incrementDensity(-10.0);
			reset_needDisplayListMakingSurface();
			break;
		}
		case 'F': {
			setCameraCentreTag(-1);
		}		

		default: {
			fprintf(stdout, "\n");
			break;
		}
	}	

}
