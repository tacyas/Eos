/*
# molvieDock : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : molvieDock
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
#include "molvieDockDefault.h"

/*
Example:
typedef struct lmolvieDockInfo {
	float a;
	int   b;
} lmolvieDockInfo;

typedef enum lmolvieDockMode {
	a=0,
	b=1
} lmolvieDockMode;
*/

int
main(int argc, char* argv[]) 
{
	molvieDockInfo info;

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
	glutKeyboardFunc(lmolvieDockKeyboard);
//	glutSpecialFunc(moveKeyboard);
	glutMouseFunc(lmolvieMouseMulti);
	glutMotionFunc(lmolvieMouseMotionMulti);
	glutPassiveMotionFunc(lmolvieMousePassiveMotionMulti);
	glutDisplayFunc(lmolvieDockDisplay);
	glutReshapeFunc(lmolvieReshapeNormal);

	glutMainLoop();

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
