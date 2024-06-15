#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include <tk.h>
#include "../inc/config.h"
#include "vtkmrcImageReader.hh"
#include "vtkmrcImageWriter.hh"

#include "tkImgFmtMRC.h"
#include <blt.h>
#include "tkctfInfo.h"
#include "vtkAdditionalCommandForEos.hh"

static EosInfo info;

#ifdef __cplusplus
extern "C" {
#endif

extern int Blt_Init      _ANSI_ARGS_((Tcl_Interp *interp));
extern int Blt_SafeInit  _ANSI_ARGS_((Tcl_Interp *interp));
extern int Tcl_AppInit   _ANSI_ARGS_((Tcl_Interp *interp));

#ifdef __cplusplus
};
#endif


int
main(int argc, char** argv)
{

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	Tk_Main(argc, argv, Tcl_AppInit);

	return 0;
}

void
additionalUsage()
{

}

int
Tcl_AppInit(Tcl_Interp *interp) 
{
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
    if (Vtktcl_SafeInit(interp) == TCL_ERROR) {
        return TCL_ERROR;
    }

    tkmrcInfoCmdSet(interp);
	tkctfInfoCmdSet(interp);
	vtkAdditionalCommandForEos(interp);

//	vtkTclCreateNew(interp, (char*)"vtkmrcImageReader", vtkmrcImageReaderNewCommand, vtkmrcImageReaderCommand);
//	Tk_CreatePhotoImageFormat(&tkImgFmtMRC);

	return TCL_OK;
}

