/*
# molvie : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : molvie
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
#include "molvieDefault.h"

int mainwindow, parallelwindow;

int
main(int argc, char* argv[]) 
{
	molvieInfo info;
//	int mainwindow;
//	pdbFile* pdbIn;

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

	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);  

	glutInitWindowPosition(WIN_POSX, WIN_POSY); 

	mainwindow=glutCreateWindow(WIN_NAME);

	lmolvieInitNormal();

/*	pdbIn= (pdbFile*)malloc(sizeof(pdbFile));
	pdbFileRead(info.fptIn, pdbIn);

	fprintf(stdout, "atom:%d\n", pdbIn->nAtom);*/

	glutIdleFunc(lmolvieIdleNormal);
	glutKeyboardFunc(lmolvieKeyboard);
//	glutSpecialFunc(moveKeyboard);
	glutMouseFunc(lmolvieMouse);
	glutMotionFunc(lmolvieMouseMotion);
	glutPassiveMotionFunc(lmolvieMousePassiveMotion);
	glutDisplayFunc(lmolvieDisplayNormal);
	glutReshapeFunc(lmolvieReshapeNormal);

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
