/*
# obj3Don2DImageView : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : obj3Don2DImageView
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

/*
Example:
typedef struct lobj3Don2DImageViewInfo {
	float a;
	int   b;
} lobj3Don2DImageViewInfo;

typedef enum lobj3Don2DImageViewMode {
	a=0,
	b=1
} lobj3Don2DImageViewMode;
*/

#include <tk.h>
#include "../inc/config.h"
#include "vtkmrcImageReader.hh"
#include "vtkmrcImageWriter.hh"
#include "tkImgFmtMRC.h"
#include "String.h"
#include "vtkSystemIncludes.h"
#include "vtkToolkits.h"
#include "vtkDebugLeaksManager.h"

#ifdef __cplusplus
   extern "C" {
#endif

	       extern int Blt_Init  _ANSI_ARGS_((Tcl_Interp *interp));

#ifdef __cplusplus
		       };
#endif

extern int Vtktcl_SafeInit(Tcl_Interp *interp);

static  obj3DOn2DImageViewInfo info;

int
main(int argc, char* argv[]) 
{
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

  	Tk_Main(argc, argv, Tcl_AppInit);

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
	char ContourValue[20];

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

	if (Vtktcl_SafeInit(interp) == TCL_ERROR) {
		return TCL_ERROR;
	}

	vtkTclCreateNew(interp, (char*)"vtkmrcImageReader", vtkmrcImageReaderNewCommand, vtkmrcImageReaderCommand);

	Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);
	Tcl_CreateCommand(interp, "mrcInfoSet", tkmrcInfoSetCmd, (ClientData)Tk_MainWindow(interp), NULL);
	Tcl_CreateCommand(interp, "mrcInfoGet", tkmrcInfoGetCmd, (ClientData)Tk_MainWindow(interp), NULL);
	Tk_CreatePhotoImageFormat(&tkImgFmtMRC);

	if(info.flagIn) {
		char s[1024];
		Tcl_SetVar2(interp, "fileNameIn", "num", "1", TCL_GLOBAL_ONLY);
		sprintf(s, "%d,fileName", 0);
		Tcl_SetVar2(interp, "fileNameIn", s, info.In, TCL_GLOBAL_ONLY);
	}
    return TCL_OK;
}

#if defined(_MSC_VER) && defined(_DEBUG)
# include <crtdbg.h>
static int vtkTkAppInitDebugReport(int, char* message, int*)
{
	fprintf(stderr, message);
	exit(1);
	return 0;
}

void vtkTkAppInitEnableMSVCDebugHook()
{
	if(getenv("DART_TEST_FROM_DART")) {
		_CrtSetReportHook(vtkTkAppInitDebugReport);
	}
}
#else
void vtkTkAppInitEnableMSVCDebugHook()
{
}
#endif

 
