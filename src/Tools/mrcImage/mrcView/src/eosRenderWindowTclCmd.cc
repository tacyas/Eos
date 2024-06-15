#include <stdio.h>
#include <tcl.h>
#include <Tk.h>
#include "vtk.h"
int RenderWindowTcl_Init

int RenderWindowTcl_Init(Tcl_Interp *interp)
{
  Tcl_CreateCommand(interp, "StereoMode", StereoModeCmd,
		    (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  return TCL_OK;
}
int StereoModeCmd(ClientData cilentData, Tcl_Interp *interp,
			  int argc,char *argv[])
{
  int stereofrag = 0;

  if(argc > 2){
    interp->result="Usage:StereoMode OnOffFlag";
    return TCL_ERROR;
  }

  if(argc == 2){
    error = Tcl_GetInt(interp, argv[1], &stereoflag);
    if(error != TCL_OK){
	return error;
    }
  }

}

int Tcl_AppInit(Tcl_Interp *interp)
{
  if(Tcl_Init(interp) == TCL_ERROR){
    fprintf(stderr,"Tcl_Init Error\n");
    return TCL_ERROR;
  }
  RenderWindowTcl_Init(interp);
  Tcl_SetVar(interp, "tcl_rcFileName","~/.mytcl",TCL_GLOBAL_ONLY);
  return TCL_OK;
}

main(int argc,char *argv[])
{
  Tcl_Main(argc,argv,Tcl_AppInit);
  exit(0);
}
  
