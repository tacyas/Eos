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
lmolvieKeyboardNormal(unsigned char pushkey,
		int x,
		int y)
	
{
#ifdef KEYBOARD_FUNCTION 

	if(pushkey!='w' && pushkey!='e'){
		fprintf(stdout, "%c:", pushkey);
	}

	switch(pushkey) {
		case 'q': {
			fprintf(stdout, "quit.\n");
			exit(EXIT_FAILURE);
			break;
		}

		case 'd': {
			operationModeSet(1);
			setDriveMyCamera();
			setCameraCentreTag(0);
			fprintf(stdout, "(ModeChange) Drive mode\n");
			break;
		}

		case 'l': {
			if(mainwindow != NULL ){
			resetMyCamera();
			operationModeSet(2);
			setCameraCentreTag(0);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
			glutInitWindowSize(256, 256);  
			glutInitWindowPosition(610, 0); 
			parallelwindow=glutCreateWindow("picture");
			lmolvieInitParallel();
			glutIdleFunc(lmolvieIdleNormal);
			glutDisplayFunc(lmolvieDisplayParallel);
			glutReshapeFunc(lmolvieReshapeParallel);	
				glutSetWindow(mainwindow);
				glutPostRedisplay();/*main ni naranai*/
			}
			else
			{
			operationModeSet(2);
			setCameraCentreTag(0);
			setCameraCentreTag(0);
			lmolvieInitParallel();
			glutIdleFunc(lmolvieIdleNormal);
			glutDisplayFunc(lmolvieDisplayParallel);
			glutReshapeFunc(lmolvieReshapeParallel);

			}
	
			


/*			char mrcFileName[100];

//			operationModeSet(3);
			fprintf(stdout, "(ModeChange) Surface mode\n");
			fprintf(stdout, "Input mrcFile:");
			scanf("%s", mrcFileName);

			lmolvieMRCread(mrcFileName);*/



			fprintf(stdout, "(ModeChange) Parallel mode\n");
			break;
		}
		case 't': {
			char mrcFileName[100];

			operationModeSet(3);
			fprintf(stdout, "(ModeChange) Surface mode\n");
			fprintf(stdout, "Input mrcFile:");
			scanf("%s", mrcFileName);

			lmolvieMRCread(mrcFileName);

			break;
		}
/*		case 'm': {
			operationModeSet(4);
			resetMyCamera();
			fprintf(stdout, "(ModeChange) MultiProtein mode\n");
			break;
		}
		case 'C': {
			operationModeSet(5);
			setCoasterCamera();
			fprintf(stdout, "(ModeChange) Coaster mode\n");
			break;
		}*/

		case 'c': {
			put_elementSwitch(0, pushkey);
			break;
		}
		case 'o': {
			put_elementSwitch(0, pushkey);
			break;
		}
		case 'n': {
			put_elementSwitch(0, pushkey);
			break;
		}
		case 's': {
			put_elementSwitch(0, pushkey);
			break;
		}
		case 'p': {
			put_elementSwitch(0, pushkey);
			break;
		}
		case 'h': {
			put_elementSwitch(0, pushkey);
			break;
		}
		case 'f': {
			put_elementSwitch(0, pushkey);
			break;
		}
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
		case '8': {
			displayModeSet(0, 8);
			fprintf(stdout, "(DisplayModeChange) DistanceFromTarget mode\n");
			break;
		}
		case '9': {
			displayModeSet(0, 9);
			fprintf(stdout, "(DisplayModeChange) WireFrame mode\n");
			break;
		}
		case '!': {
			displayModeSet(0, 10);
			fprintf(stdout, "(DisplayModeChange) Chain mode\n");
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
		case 'F': {
			setCameraCentreTag(-1);
		}
/*		case 'Z': {
			loadDSN6();
		}
		case 'b': {
			saveStatus();
		}
		case 'g': {
			loadStatus();
		}*/
		default: {
			fprintf(stdout, "\n");
			break;
		}
	}	

#endif
	//glutPostRedisplay();
}
