/*
# lmolvieKeyboardDrive : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieKeyboardDrive 
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
lmolvieKeyboardDrive(unsigned char pushkey,
		int x,
		int y)	/*drive mode*/
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
			resetMyCamera();
			setCameraCentreTag(2);
			fprintf(stdout, "(ModeChange) Normal mode\n");
			break;
		}

		case 'c': {
			setCheckSwitch(1);
			fprintf(stdout, "check!\n");
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
		case 'v': {
			//lmolvieVoice();
			fprintf(stdout, "voice!\n");
			break;
		}

		case 'r': {
			resetDriveMyCamera();
			fprintf(stdout, "camera reset.\n");
			break;
		}

		case 'w': {
			//myCameraRotateX(1.0/M_PI);
			fprintf(stdout,"pushed w ! \n");
			moveDriveMyCamera(1.0);
			break;
		}
		case 'e': {
			//myCameraRotateX(1.0/M_PI);
			moveDriveMyCamera(-1.0);
			break;
		}
		case 's': {
			setSpeed();
			fprintf(stdout, "speed change.\n");
			break;
		}

		default: {
			fprintf(stdout, "\n");
			break;
		}
	}	

}
