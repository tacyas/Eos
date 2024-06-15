/*
# molvieFlight : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : molvieFlight
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
#include "molvieFlightDefault.h"

/*
Example:
typedef struct lmolvieFlightInfo {
	float a;
	int   b;
} lmolvieFlightInfo;

typedef enum lmolvieFlightMode {
	a=0,
	b=1
} lmolvieFlightMode;
*/

int
main(int argc, char* argv[]) 
{
	molvieFlightInfo info;

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

	setDriveMyCamera();

	glutIdleFunc(lmolvieFlightIdle);
	glutKeyboardFunc(lmolvieFlightKeyboard);
//	glutSpecialFunc(moveKeyboard);
	glutMouseFunc(lmolvieMouseDrive);
	glutMotionFunc(lmolvieMouseMotionDrive);
	glutPassiveMotionFunc(lmolvieMousePassiveMotionDrive);
	glutDisplayFunc(lmolvieFlightDisplay);
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
