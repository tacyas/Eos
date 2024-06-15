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

static Display2Info info;

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
	fprintf(stderr, "New wish commands of Display2\n");
	fprintf(stderr, "mrcInfoSet [z|min|max] value\n");
	fprintf(stderr, "mrcInfoSet [log|pow] \n");
	fprintf(stderr, "mrcInfoGet [Nx|Ny|Nz|Max|Min|Mean|Hist]\n");
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
	if(info.flagThresHigh) {
		sprintf(s, "%g", info.ThresHigh);
		Tcl_SetVar(interp, "thresHigh", s, 0);
	}
	if(info.flagThresLow) {
		sprintf(s, "%g", info.ThresLow);
		Tcl_SetVar(interp, "thresLow", s, 0);
	}
	if(info.flagZoom) {
		sprintf(s, "%g", info.Zoom);
		Tcl_SetVar(interp, "Zoom", s, 0);
	}
	if(info.Inverse) {
		sprintf(s, "%ld", info.Inverse);
		Tcl_SetVar(interp, "Inverse", s, 0);
	}
	Tcl_SetVar(interp, "defaultFile", info.Default, 0);
	Tcl_SetVar(interp, "LogFile", info.Out, 0);
	Tcl_SetVar(interp, "fileNameTemplate", info.Template, 0);

	return TCL_OK;
}

