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

void
lmolvieViewerKeyboard(unsigned char pushkey,
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
			setCameraCentreTagV(-1);
		}
/*
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
	glutPostRedisplay();
}
