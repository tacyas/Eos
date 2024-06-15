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
#include <string.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
#include "./molvieProjectionDefault.h"

extern int mainwindow, parallelwindow;

void
lmolvieProjectionKeyboard(unsigned char pushkey,
		int x,
		int y)	/*parallel mode*/
{
	char degreeX[5];
	char degreeY[5];
	char degreeZ[5];
	if(pushkey!='w' && pushkey!='e'){
		fprintf(stdout, "%c:", pushkey);
	}

	switch(pushkey) {
		case 'q': {
			fprintf(stdout, "quit.\n");
			exit(EXIT_FAILURE);
			break;
		}

		case 's': {
			fprintf(stdout, "save PPM.\n");
			glutSetWindow(parallelwindow);
			savePPM();
			glutSetWindow(mainwindow);
			break;
		}

		case 'l': {
			glutSetWindow(parallelwindow);
			put_texture();
			glutSetWindow(mainwindow);
			loadPPM();
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
		case 'b': {
			fprintf(stdout, "texture translate.\n");
			texture_translate_z(0.5);
			break;
		}
		case 'n': {
			fprintf(stdout, "texture translate.\n");
			texture_translate_z(-0.5);
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
		
		
		case 'S': {
			scaleBarSwitch();
			break;
		}

		case 'p': {
			static int i=0;
			if(i==0){	
				fprintf(stdout, "start.\n");
				glutInitWindowSize(SUBWIN_WIDTH, SUBWIN_HEIGHT);  
				glutInitWindowPosition(SUBWIN_POSX, SUBWIN_POSY); 
				parallelwindow=glutCreateWindow(SUBWIN_NAME);
				lmolvieInitParallel();
				glutIdleFunc(lmolvieIdleNormal);
				glutDisplayFunc(lmolvieDisplayParallel);
				glutReshapeFunc(lmolvieReshapeParallel);
				glutSetWindow(mainwindow);
//				put_texture(); //Here!!
				i=1;
			}
			break;
		}
		//Rotate Outputs X Y Z
		case 'R':{
				fprintf(stdout,"Rotate XYZ %d %d %d\n",getSpin_x(0),getSpin_y(0),getSpin_z(0));
				break;
		}
		case 'X':{
				fprintf(stdout,"Please input RotateX.\n");
				fgets(degreeX,sizeof(degreeX),stdin);
				degreeX[5 - 1] = '\0'; 
				proteinRotateX(-atoi(degreeX), 0);	
				fprintf(stdout,"Rotate X: %s\n",degreeX);
				break;
		}		
		case 'Y':{
				fprintf(stdout,"Please input RotateY.\n");
				fgets(degreeY,sizeof(degreeY),stdin);
				degreeY[5 - 1] = '\0'; 
				proteinRotateY(-atoi(degreeY), 0);
				fprintf(stdout,"Rotate Y: %d\n",degreeY);
				break;
		}
		case 'Z':{
				fprintf(stdout,"Please input RotateZ.\n");
				fgets(degreeZ,sizeof(degreeZ),stdin);
				degreeX[5 - 1] = '\0'; 
				proteinRotateZ(-atoi(degreeZ), 0);
				fprintf(stdout,"Rotate Z: %s\n",degreeZ);
				break;
		}
		
		default: {
			fprintf(stdout, "\n");
			break;
		}
	}

	glutSetWindow(parallelwindow);
	glutPostRedisplay();
	glutSetWindow(mainwindow);	
	glutPostRedisplay();
}
