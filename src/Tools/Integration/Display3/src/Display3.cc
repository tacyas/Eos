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

static Display3Info info;

static void vtkTkAppInitEnableMSVCDebugHook();

int
main(int argc, char** argv)
{
	ios::sync_with_stdio();
	vtkTkAppInitEnableMSVCDebugHook();

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	Tk_Main(argc, argv, Tcl_AppInit);
}

void
additionalUsage()
{
	fprintf(stderr, "New wish commands of Display3\n");
	fprintf(stderr, "mrcInfoSet [z|min|max] value\n");
	fprintf(stderr, "mrcInfoSet [log|pow] \n");
	fprintf(stderr, "mrcInfoGet [Nx|Ny|Nz|Max|Min|Mean|Hist]\n");
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
	sprintf(ContourValue, "%15g", info.Contour);
	Tcl_SetVar(interp, "CONTOUR", strdup(ContourValue), TCL_GLOBAL_ONLY);

	Tcl_CreateCommand(interp, "mrcInfoSet", tkmrcInfoSetCmd, (ClientData)Tk_MainWindow(interp), NULL);
	Tcl_CreateCommand(interp, "mrcInfoGet", tkmrcInfoGetCmd, (ClientData)Tk_MainWindow(interp), NULL);
	Tk_CreatePhotoImageFormat(&tkImgFmtMRC);

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

		sprintf(s, "%ld", info.flagIn2);
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

