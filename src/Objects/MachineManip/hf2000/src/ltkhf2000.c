/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ltkhf2000 ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ltkhf2000 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ltkhf2000 ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include "genUtil.h"

#include "../inc/hf2000.h"
#include "lhf2000SpecimenPosition.h"
#include "lhf2000LenzCurrent.h"
#include <tcl.h>
#include <tk.h>

int
hf2000_TclAppInit(Tcl_Interp *interp) 
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
	return TCL_OK;
}

int tkhf2000Cmd(ClientData clientData, Tcl_Interp *interp, int argc, char* argv[])
{
	char s[1024];
	extern hf2000Info __hf2000;

	if(argc<3) {
		return TCL_ERROR;
	}
	if(__hf2000.flagClient) {
		hf2000Init(&__hf2000);
	}
	SSWITCH(argv[1]) 
		SCASE("SpecimenPosition") {
			lhf2000SpecimenPositionInfo linfo;
			SSWITCH(argv[2]) 
				SCASE("Get") {
					lhf2000SpecimenPositionGet(&__hf2000, &linfo, 0);
					sprintf(s, "%+10.1f", linfo.x);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%+10.1f", linfo.y);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%+5d", linfo.ix);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%+5d", linfo.iy);
					Tcl_AppendElement(interp, s);
				}
				SCASE("Set") {
					linfo.x = atof(argv[3]);
					linfo.y = atof(argv[4]);
					linfo.ix  = linfo.x*10.0;
					linfo.iy  = linfo.y*10.0;
					lhf2000SpecimenPositionSet(&__hf2000, &linfo, 0);
				}
				SDEFAULT {
					fprintf(stderr, "Not supported Command: %s\n", argv[1]);
				}
			SSWITCHEND;
		}
		SCASE("LenzCurrent") {
			lhf2000LenzCurrentInfo linfo;
			SSWITCH(argv[2]) 
				SCASE("Get") {
					hf2000LenzCurrent C;
					C = lhf2000LenzCurrentGet0(&__hf2000, argv[3], 0);
					sprintf(s, "%6x",     C.D);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%d",      C.D);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%+15.6e", C.A);
					Tcl_AppendElement(interp, s);
				}
				SDEFAULT {
					fprintf(stderr, "Not supported Command: %s\n", argv[1]);
				}
			SSWITCHEND;
		}
		SCASE("RAW") {
			hf2000Write(&__hf2000, argv[2]);
			hf2000Read (&__hf2000, s);
			Tcl_AppendElement(interp, s);
		}
		SDEFAULT {
			fprintf(stderr, "Not supported Command: %s\n", argv[1]);
		}
	SSWITCHEND;
	if(__hf2000.flagClient) {
		hf2000Close(&__hf2000);
	}
	return 0;
}
