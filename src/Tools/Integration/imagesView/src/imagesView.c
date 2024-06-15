/*
	Display2: Integration Tool on Eos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include <tcl.h>
#include "mrcImage.h"
#include <tk.h>
#include <blt.h>
#include "../inc/config.h"
#include "tkImgFmtMRC.h"
#include "tkctfInfo.h"

static imagesViewInfo info;

extern int Blt_Init      _ANSI_ARGS_((Tcl_Interp *interp));
extern int Blt_SafeInit  _ANSI_ARGS_((Tcl_Interp *interp));
extern int Tcl_AppInit _ANSI_ARGS_((Tcl_Interp *interp)); 

int
main(int argc, char** argv)
{
	extern int Tcl_AppInit _ANSI_ARGS_((Tcl_Interp *interp));

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	Tk_Main(argc, argv, Tcl_AppInit);

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "Additional Usage\n");
	fprintf(stderr, "This command for viewing images with a suffix\n");
}

int
Tcl_AppInit(Tcl_Interp *interp) 
{
	char s[1024];

	if(TCL_ERROR==Tcl_Init(interp)) {
		fprintf(stderr, "Tcl_Init Error\n");
		return TCL_ERROR;
	}
	if(TCL_ERROR==Tk_Init(interp)) {
		fprintf(stderr, "Tk_Init Error\n");
		return TCL_ERROR;
	}
	/* BLT */
	if(TCL_ERROR==Blt_Init(interp)) {
		fprintf(stderr, "Blt_Init Error\n");
		return TCL_ERROR;
	}
	Tcl_StaticPackage(interp, "BLT", Blt_Init, Blt_SafeInit);

	/* MRC Set */
	tkmrcInfoCmdSet(interp);	
	tkctfInfoCmdSet(interp);	

	/* Gloval Valuable for Wish */
	if(info.flagIn) {
		Tcl_SetVar(interp, "fileNameIn", info.In, 0);
	}
	Tcl_SetVar(interp, "LogFile", info.Out, 0);

	return TCL_OK;
}

