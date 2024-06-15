/*
# smolet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : smolet
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

static smoletInfo info;

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
	fprintf(stderr, "New wish commands of smolet \n");
	fprintf(stderr, "mrcInfoSet [z|min|max] value\n");
	fprintf(stderr, "mrcInfoSet [log|pow] \n");
	fprintf(stderr, "mrcInfoGet [Nx|Ny|Nz|Max|Min|Mean|Hist]\n");
}

extern "C" int Vtkcommontcl_Init(Tcl_Interp *interp);
extern "C" int Vtkfilteringtcl_Init(Tcl_Interp *interp);
extern "C" int Vtkimagingtcl_Init(Tcl_Interp *interp);
extern "C" int Vtkgraphicstcl_Init(Tcl_Interp *interp);
extern "C" int Vtkiotcl_Init(Tcl_Interp *interp);

#ifdef VTK_USE_RENDERING
extern "C" int Vtkrenderingtcl_Init(Tcl_Interp *interp);
#if defined(VTK_DISABLE_TK_INIT) && !defined(VTK_USE_COCOA)
extern "C" int Vtktkrenderwidget_Init(Tcl_Interp *interp);
extern "C" int Vtktkimageviewerwidget_Init(Tcl_Interp *interp);
#endif
#endif

#ifdef VTK_USE_PATENTED
extern "C" int Vtkpatentedtcl_Init(Tcl_Interp *interp);
#endif

#ifdef VTK_USE_HYBRID
extern "C" int Vtkhybridtcl_Init(Tcl_Interp *interp);
#endif

#ifdef VTK_USE_PARALLEL
extern "C" int Vtkparalleltcl_Init(Tcl_Interp *interp);
#endif

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

	//if (Vtktcl_SafeInit(interp) == TCL_ERROR) {
	//	return TCL_ERROR;
	//}

  /* init the core vtk stuff */
	if (Vtkcommontcl_Init(interp) == TCL_ERROR)
	{
	return TCL_ERROR;
	}
	if (Vtkfilteringtcl_Init(interp) == TCL_ERROR)
	{
	return TCL_ERROR;
	}
	if (Vtkimagingtcl_Init(interp) == TCL_ERROR)
	{
	return TCL_ERROR;
	}
	if (Vtkgraphicstcl_Init(interp) == TCL_ERROR)
	{
	return TCL_ERROR;
	}
	if (Vtkiotcl_Init(interp) == TCL_ERROR)
	{
	return TCL_ERROR;
	}

#ifdef VTK_USE_RENDERING
	if (Vtkrenderingtcl_Init(interp) == TCL_ERROR)
	{
	return TCL_ERROR;
	}
#if defined(VTK_DISABLE_TK_INIT) && !defined(VTK_USE_COCOA)
	// Need to init here because rendering did not when this option is on
	if (Vtktkrenderwidget_Init(interp) == TCL_ERROR)
	  {
	  return TCL_ERROR;
	  }
	if (Vtktkimageviewerwidget_Init(interp) == TCL_ERROR)
	  {
  	  return TCL_ERROR;
	  }
#endif
#endif

#ifdef VTK_USE_PATENTED
	if (Vtkpatentedtcl_Init(interp) == TCL_ERROR)
	{
		return TCL_ERROR;
	}
#endif

#ifdef VTK_USE_HYBRID
	if (Vtkhybridtcl_Init(interp) == TCL_ERROR)
	{
		fprintf(stderr, "hybrid\n");
		return TCL_ERROR;
	}
#endif

#ifdef VTK_USE_PARALLEL
	if (Vtkparalleltcl_Init(interp) == TCL_ERROR)
	{
		fprintf(stderr, "parallel\n");
		return TCL_ERROR;
	}
#endif


/* append path to VTK packages to auto_path */
     static char script[] =
	    "foreach dir [list { ~/Eos/bin/wish/smolet } { ~/Eos/lib } "
		" [file join [file dirname [file dirname [info nameofexecutable]]] Wrapping Tcl]"
		" [file join [file dirname [file dirname [info nameofexecutable]]] lib vtk tcl]"
		" ] {\n"
		"  if {[file isdirectory $dir]} {\n"
		"    lappend auto_path $dir\n"
		"  }\n"
		"}\n"
		"rename package package.orig\n"
		"proc package {args} {\n"
		"  if {[catch {set package_res [eval package.orig $args]} catch_res]} {\n"
		"    global errorInfo env\n"
		"    if {[lindex $args 0] == \"require\"} {\n"
		"      set expecting {can\'t find package vtk}\n"
		"      if {![string compare -length [string length $expecting] $catch_res $expecting]} {\n"
		"        set msg {The Tcl interpreter was probably not able to find the"
		" VTK packages.  Please check that your TCLLIBPATH environment variable"
		" includes the path to your VTK Tcl directory.  You might find it under"
		" your VTK binary directory in Wrapping/Tcl, or under your"
		" site-specific {CMAKE_INSTALL_PREFIX}/lib/vtk/tcl directory.}\n"
		"        if {[info exists env(TCLLIBPATH)]} {\n"
		"          append msg \"  The TCLLIBPATH current value is: $env(TCLLIBPATH).\"\n"
		"        }\n"
		"        set errorInfo \"$msg  The TCLLIBPATH variable is a set of"
		" space separated paths (hence, path containing spaces should be"
		" surrounded by quotes first). Windows users should use forward"
		" (Unix-style) slashes \'/\' instead of the usual backward slashes. "
   	 	" More informations can be found in the Wrapping/Tcl/README source"
	    " file (also available online at"
		" http://www.vtk.org/cgi-bin/cvsweb.cgi/~checkout~/VTK/Wrapping/Tcl/README).\n"
		"$errorInfo\"\n"
		"      }\n"
		"    }\n"
		"  error $catch_res $errorInfo\n"
		"  }\n"
		"  return $package_res\n"
		"}\n";

  Tcl_Eval(interp, script);
 	/*
	*    * Specify a user-specific startup file to invoke if the application
	*       * is run interactively.  Typically the startup file is "~/.apprc"
	*          * where "app" is the name of the application.  If this line is deleted
	*             * then no user-specific startup file will be run under any conditions.
	*                */

	//vtkTclCreateNew(interp, (char*)"vtkmrcImageReader", vtkmrcImageReaderNewCommand, vtkmrcImageReaderCommand);

	Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);

	//Tcl_CreateCommand(interp, "mrcInfoSet", tkmrcInfoSetCmd, (ClientData)Tk_MainWindow(interp), NULL);
	//Tcl_CreateCommand(interp, "mrcInfoGet", tkmrcInfoGetCmd, (ClientData)Tk_MainWindow(interp), NULL);
	//Tk_CreatePhotoImageFormat(&tkImgFmtMRC);

	if(info.flagIn) {
		Tcl_SetVar(interp, "BaseName",  info.In, TCL_GLOBAL_ONLY);
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

