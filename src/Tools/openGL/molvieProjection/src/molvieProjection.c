/*
# molvieProjection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : molvieProjection
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "eosOpenGL.h"
#include "pdbFile.h"
#include "molvieProjectionDefault.h"

int mainwindow, parallelwindow;

/*
Example:
typedef struct lmolvieProjectionInfo {
	float a;
	int   b;
} lmolvieProjectionInfo;

typedef enum lmolvieProjectionMode {
	a=0,
	b=1
} lmolvieProjectionMode;
*/

int
main(int argc, char* argv[]) 
{
	molvieProjectionInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	info.fptIn=fopen(info.In, "r");
	if(NULL==info.fptIn){
		fprintf(stderr, "FileNotOpend: %s\n", info.In);
		exit(EXIT_FAILURE);
	}

	lmolviePDBread(info.fptIn);

	fclose(info.fptIn);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
	
	//メインウィンドウの設定
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);  

	glutInitWindowPosition(WIN_POSX, WIN_POSY); 

	mainwindow=glutCreateWindow(WIN_NAME);

	lmolvieInitNormal();

	glutIdleFunc(lmolvieViewerIdle);
	glutKeyboardFunc(lmolvieProjectionKeyboard);
//	glutSpecialFunc(moveKeyboard);
	glutMouseFunc(lmolvieProjectionMouse);
	glutMotionFunc(lmolvieProjectionMouseMotion);
	glutPassiveMotionFunc(lmolvieProjectionMousePassiveMotion);
	glutDisplayFunc(lmolvieViewerDisplay);
	glutReshapeFunc(lmolvieReshapeNormal);
				glutInitWindowSize(SUBWIN_WIDTH, SUBWIN_HEIGHT);  
				glutInitWindowPosition(SUBWIN_POSX, SUBWIN_POSY); 
				parallelwindow=glutCreateWindow(SUBWIN_NAME);
				lmolvieInitParallel();
				glutIdleFunc(lmolvieIdleNormal);
				glutDisplayFunc(lmolvieDisplayParallel);
				glutReshapeFunc(lmolvieReshapeParallel);

				glutSetWindow(mainwindow);

	glutMainLoop();

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
