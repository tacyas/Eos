/*
# ctfDisplay : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : ctfDisplay
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

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "ctfInfo.h"
#include <tcl.h>
#include <tk.h>
#include <blt.h>

#include "tkImgFmtMRC.h"
#include "tkctfInfo.h"

/*
Example:
typedef struct lctfDisplayInfo {
	float a;
	int   b;
} lctfDisplayInfo;

typedef enum lctfDisplayMode {
	a=0,
	b=1
} lctfDisplayMode;
*/

static ctfDisplayInfo info;

extern int Blt_Init      _ANSI_ARGS_((Tcl_Interp *interp));
extern int Blt_SafeInit  _ANSI_ARGS_((Tcl_Interp *interp));
extern int Tcl_AppInit _ANSI_ARGS_((Tcl_Interp *interp));
extern int Tcl_AppInit _ANSI_ARGS_((Tcl_Interp *interp));

int
main(int argc, char* argv[]) 
{
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	Tk_Main(argc, argv, Tcl_AppInit);	
		
	return 0;	
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

int
Tcl_AppInit(Tcl_Interp *interp)
{
	char s[1024];

	DEBUGPRINT("Tcl_AppInit Start\n");
	if(TCL_ERROR==Tcl_Init(interp)) {
		fprintf(stderr, "Tcl_Init Error\n");
		return TCL_ERROR;
	}
	if(TCL_ERROR==Tk_Init(interp)) {
		fprintf(stderr, "Tk_Init Error\n");
		return TCL_ERROR;
	}
	/* BLT */
	if(TCL_OK!=Blt_Init(interp)) {
		fprintf(stderr, "Blt_Init Error\n");
		return TCL_ERROR;
	}
	//Tcl_StaticPackage(interp, "BLT", Blt_Init, Blt_SafeInit);

	/* MRC Set */
	tkmrcInfoCmdSet(interp);
	tkctfInfoCmdSet(interp);

	/* Gloval Valuable for Wish */
	if(info.flaginMRC) {
		Tcl_SetVar(interp, "inMRC", info.inMRC, 0);
	}
	if(info.flagoutCTF) {
		Tcl_SetVar(interp, "outCTF", info.outCTF, 0);
	}
	if(info.flagRmax) {
		sprintf(s, "%f", info.Rmax); 
		Tcl_SetVar(interp, "Rmax", s, 0);
	}
	if(info.flagImax) {
		sprintf(s, "%f", info.Imax); 
		Tcl_SetVar(interp, "Imax", s, 0);
	}
	if(info.flagImin) {
		sprintf(s, "%f", info.Imin); 
		Tcl_SetVar(interp, "Imin", s, 0);
	}
	if(info.AutoRange) {
		sprintf(s, "%ld", info.AutoRange); 
		Tcl_SetVar(interp, "flagAutoRange", s, 0);
	}
	if(info.Log) {
		if(!info.flagImin) {
			sprintf(s, "%f", info.Imax*1e-5); 	
			Tcl_SetVar(interp, "Imin", s, 0);
		}
		sprintf(s, "%ld", info.Log); 
		Tcl_SetVar(interp, "flagLog", s, 0);
	}

	DEBUGPRINT("Tcl_AppInit End\n");
	return TCL_OK;
}
