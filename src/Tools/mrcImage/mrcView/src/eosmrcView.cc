#include <stdio.h>
#include <stdlib.h>
#include <tk.h>

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

static Display3Info info;

int 
main(int argc, char** argv)
{
    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

    Tk_Main(argc, argv, Tcl_AppInit);
}

int
Tcl_AppInit(Tcl_Interp *interp)
{
    Tk_Window main;
    char ContourValue[20];

    main = Tk_MainWindow(interp);
    if(TCL_ERROR==Tcl_Init(interp)) {
        fprintf(stderr, "Tcl_Init Error\n");
        return TCL_ERROR;
    }
    if(TCL_ERROR==Tk_Init(interp)) {
        return TCL_ERROR;
    }

    if(TCL_ERROR==Blt_Init(interp)) {
        fprintf(stderr, "Blt_Init Error\n");
        return TCL_ERROR;
    }
  /* init the core vtk stuff */
    if (Vtkcommontcl_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }
    if (Vtkgraphicstcl_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }

    if (Vtktkrenderwidget_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }

    if (Vtkimagingtcl_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }
    if (Vtktkimagewindowwidget_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }
    if (Vtktkimageviewerwidget_Init(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }

#ifdef VTK_USE_PATENTED
  if (Vtkpatentedtcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }

#endif

    vtkTclCreateNew(interp, (char*)"eosRenderWindowTcl", eosRenderWindowTclNewComm
and, eosRenderWindowTclCommand);

    /*Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);
    sprintf(ContourValue, "%f", info.Contour);
    Tcl_SetVar(interp, "CONTOUR", ContourValue, TCL_GLOBAL_ONLY);
    */

    Tcl_CreateCommand(interp, "eosStereoWindowTcl",eosStereoCmd, (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
 

   if(info.flagIn) {
        char s[1024];
        Tcl_SetVar2(interp, "fileNameIn", "num", "1", TCL_GLOBAL_ONLY);
        sprintf(s, "%d,fileName", 0);
        Tcl_SetVar2(interp, "fileNameIn", s, info.In, TCL_GLOBAL_ONLY);
        sprintf(s, "%d,contour", 0);
        Tcl_SetVar2(interp, "fileNameIn", s, ContourValue, TCL_GLOBAL_ONLY);
    } else if(info.flagIn2) {
        int i;
        char s[1024];
        char s0[1024];

        sprintf(s, "%d", info.flagIn2);
        Tcl_SetVar2(interp, "fileNameIn", "num", s, TCL_GLOBAL_ONLY);
        fseek(info.fptIn2List, 0, SEEK_SET);
        for(i=0; i<info.flagIn2; i++) {
            sprintf(s, "%d,fileName", i);
            Tcl_SetVar2(interp, "fileNameIn", s, info.In2[i], TCL_GLOBAL_ONLY); 

            stringGetFromFile(s0, "", info.fptIn2List, stdout, 3);
            sprintf(s, "%d,contour", i);
            Tcl_SetVar2(interp, "fileNameIn", s, stringGetNthWord(s0, 2, " ,\t"), TCL_GLOBAL_ONLY);
        }
    }
   
   return TCL_OK;
}
