/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% hf2000SpecimenPosition ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : hf2000SpecimenPosition
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%hf2000SpecimenPosition ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <tk.h>
#include <blt.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "hf2000.h"

/*
Example:
typedef struct lhf2000SpecimenPositionInfo {
	float a;
	int   b;
} lhf2000SpecimenPositionInfo;

typedef enum lhf2000SpecimenPositionMode {
	a=0,
	b=1
} lhf2000SpecimenPositionMode;
*/

#include "lhf2000SpecimenPosition.h"

hf2000Info hf2000;
hf2000SpecimenPositionInfo  info;
lhf2000SpecimenPositionInfo linfo;

void
main(int argc, char* argv[]) 
{
	extern int Tcl_AppInit _ANSI_ARGS_((Tcl_Interp *interp));

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	hf2000.deviceName = info.tty;
	
	if(info.flagHost) {
		hf2000.hostname = info.Host;
		hf2000.port     = info.Port;
		hf2000.flagClient = 1;
	} else {
		hf2000Init(&hf2000);	
	}

	
	if(info.flagposX && info.flagposY) {
		linfo.x = info.posX;
		linfo.y = info.posY;
		linfo.ix = floor(linfo.x*10 + 0.5);
		linfo.iy = floor(linfo.y*10 + 0.5);
		lhf2000SpecimenPositionSet(&hf2000, &linfo, 0);
	} else {
		lhf2000SpecimenPositionGet(&hf2000, &linfo, 0);
		fprintf(info.fptOut, "Position: %+5d %+5d %+10.1f %+10.1f\n", 
			linfo.ix, linfo.iy, linfo.x, linfo.y);
	}
	if(info.flagInteractive) {
		Tk_Main(argc, argv, Tcl_AppInit);
	}
	exit(EXIT_SUCCESS);
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
	extern int Blt_Init      _ANSI_ARGS_((Tcl_Interp *interp));
	extern int Blt_SafeInit  _ANSI_ARGS_((Tcl_Interp *interp));
	extern int tkhf2000Cmd(ClientData clientData, Tcl_Interp* interp,
 int argc, char* argv[]);
	if(TCL_ERROR==Tcl_Init(interp)) {
		fprintf(stderr, "Tcl_Init Error\n");
		return TCL_ERROR;
	}
	if(TCL_ERROR==Tk_Init(interp)) {
		fprintf(stderr, "Tk_Init Error\n");
		return TCL_ERROR;
	}
	if(TCL_ERROR==Blt_Init(interp)) {
		fprintf(stderr, "Blt_Init Error\n");
		return TCL_ERROR;
	}
	Tcl_StaticPackage(interp, "BLT", Blt_Init, Blt_SafeInit);

	Tcl_CreateCommand(interp, "hf2000", tkhf2000Cmd, (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);

	sprintf(s, "%d", info.Interactive);
	Tcl_SetVar(interp, "Iteractive", s, 0);
	return TCL_OK;
}

