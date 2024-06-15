/*
# molvieViewer : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : molvieViewer
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
#include "molvieViewerDefault.h"

/*
Example:
typedef struct lmolvieViewerInfo {
	float a;
	int   b;
} lmolvieViewerInfo;

typedef enum lmolvieViewerMode {
	a=0,
	b=1
} lmolvieViewerMode;
*/

int
main(int argc, char* argv[]) 
{
	molvieViewerInfo info;

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

	glutCreateWindow(WIN_NAME);

	lmolvieInitNormal();

	glutIdleFunc(lmolvieViewerIdle);
	glutKeyboardFunc(lmolvieViewerKeyboard);
	glutSpecialFunc(lmolvieViewerSpecial);
	glutMouseFunc(lmolvieViewerMouse);
	glutMotionFunc(lmolvieViewerMouseMotion);
	glutPassiveMotionFunc(lmolvieViewerMousePassiveMotion);
	glutDisplayFunc(lmolvieViewerDisplay);
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
