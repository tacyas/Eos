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
lmolvieMrcViewerKeyboard(unsigned char pushkey,
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
			reset_needDisplayListMakingSurfaceM();
			break;
		}
		case 'h': {
			fprintf(stdout, "Density -0.1\n");
			incrementDensity(-0.1);
			reset_needDisplayListMakingSurfaceM();
			break;
		}
		case 'u': {
			fprintf(stdout, "Density +1.0\n");
			incrementDensity(1.0);
			reset_needDisplayListMakingSurfaceM();
			break;
		}
		case 'j': {
			fprintf(stdout, "Density -1.0\n");
			incrementDensity(-1.0);
			reset_needDisplayListMakingSurfaceM();
			break;
		}
		case 'i': {
			fprintf(stdout, "Density +10.0\n");
			incrementDensity(10.0);
			reset_needDisplayListMakingSurfaceM();
			break;
		}
		case 'k': {
			fprintf(stdout, "Density -10.0\n");
			incrementDensity(-10.0);
			reset_needDisplayListMakingSurfaceM();
			break;
		}
		case 'F': {
			setCameraCentreTagM(-1);
		}		

		default: {
			fprintf(stdout, "\n");
			break;
		}
	}	
	glutPostRedisplay();

}
