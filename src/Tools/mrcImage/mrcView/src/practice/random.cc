#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <tk.h>
#include <tcl.h>

#ifdef __cplusplus
    extern "C" {
#endif

extern int Blt_Init  _ANSI_ARGS_((Tcl_Interp *interp));
extern int VTK_Init(Tcl_Interp *interp);
extern "C" int Vtkcommontcl_Init(Tcl_Interp *interp);
extern "C" int Vtkgraphicstcl_Init(Tcl_Interp *interp);
extern "C" int Vtktkrenderwidget_Init(Tcl_Interp *interp);
extern "C" int Vtkimagingtcl_Init(Tcl_Interp *interp);
extern "C" int Vtktkimageviewerwidget_Init(Tcl_Interp *interp);
extern "C" int Vtktkimagewindowwidget_Init(Tcl_Interp *interp);

#ifdef VTK_USE_PATENTED
extern "C" Vtkpatentedtcl_Init(Tcl_Interp *interp);
#endif

#ifdef VTK_USE_CONTRIB
extern "C" Vtkcontribtcl_Init(Tcl_Interp *interp);
#endif

#ifdef __cplusplus
    };
#endif

int RandomCmd(ClientData clientData, Tcl_Interp *interp,
               int argc, char *argv[]);

int Random_Init(Tcl_Interp *interp){
  Tcl_CreateCommand(interp, "random", RandomCmd, (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

  Tcl_PkgProvide(interp, "random", "1.1");
  return TCL_OK;
}

int
RandomCmd(ClientData clientData,Tcl_Interp *interp, int argc,char *argv[])
{
  int rand, error;
  int limit = 0;
  
  if (argc > 2){
    interp->result = "Usage:random ?range?";
    return TCL_ERROR;
  }

  if (argc == 2){
    error=Tcl_GetInt(interp, argv[1], &limit);
    if(error!=TCL_OK){
      return error;
    }
  }

  rand = random();
  
  if(limit != 0){
    rand = rand %limit;
  }
  sprintf(interp->result, "%d", rand);
  return TCL_OK;
}


int
Tcl_AppInit(Tcl_Interp *interp){
  if(Tcl_Init(interp)==TCL_ERROR){
    return TCL_ERROR;
  }

  Random_Init(interp);

  Tcl_SetVar(interp, "tcl_rcFileName", "~/.mytcl", TCL_GLOBAL_ONLY);
  //  Tcl_Invoke(interp, "set", "foo", "$xyz [foo] {",NULL);
  return TCL_OK;
}
        
main(int argc, char *argv[]){
  Tk_Main(argc, argv, Tcl_AppInit);
  return 0;
}
