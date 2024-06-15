/*
# vtkAdditionalCommandForEos : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : vtkAdditionalCommandForEos 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "./vtkAdditionalCommandForEos.hh"
//#include "./eosInteractorMyStyleTcl.cc"
//#include "./eosInteractorStyleStereoTcl.cc"
//#include "./eosStereoRendererTcl.cc"
//#include "eosStereoModeOn.hh"
#include "vtkmrcImageReader.hh"
#include "tkImgFmtMRC.h"

#define DEBUG
#include "genUtil.h"

int
vtkAdditionalCommandForEos(Tcl_Interp* interp)
{
  //vtkTclCreateNew(interp, (char*)"eosInteractorMyStyle", eosInteractorMyStyleNewCommand, eosInteractorMyStyleCommand); 
  //vtkTclCreateNew(interp, (char*)"eosInteractorStyleStereo", eosInteractorStyleStereoNewCommand, eosInteractorStyleStereoCommand);

 // Tcl_CreateCommand(interp, (char*)"eosStereoRenderer", eosStereoRendererNewCommand, Tk_MainWindow(interp), NULL);
  
  vtkTclCreateNew(interp, (char*)"vtkmrcImageReader", vtkmrcImageReaderNewCommand, vtkmrcImageReaderCommand);
  Tk_CreatePhotoImageFormat(&tkImgFmtMRC);
  DEBUGPRINT("in vtkAdditionalCommandForEos\n");
  return TCL_OK;
}

#include <stdio.h>
#include <stdlib.h>

#include "tk.h"

#include "vtkToolkits.h"

#ifdef __cplusplus
extern "C" {
#endif
extern int Vtkcommontcl_Init(Tcl_Interp *interp);
extern int Vtkiotcl_Init(Tcl_Interp *interp);
extern int Vtkfilteringtcl_Init(Tcl_Interp *interp);
extern int Vtkgraphicstcl_Init(Tcl_Interp *interp);
extern int Vtkrenderingtcl_Init(Tcl_Interp *interp);
extern int Vtktkrenderwidget_Init(Tcl_Interp *interp);
extern int Vtkimagingtcl_Init(Tcl_Interp *interp);
extern int Vtktkimagewindowwidget_Init(Tcl_Interp *interp);
extern int Vtktkimageviewerwidget_Init(Tcl_Interp *interp);
extern int Vtkpatentedtcl_Init(Tcl_Interp *interp);
extern int Vtkcontribtcl_Init(Tcl_Interp *interp);
extern int Vtklocaltcl_Init(Tcl_Interp *interp);
extern int Vtkparalleltcl_Init(Tcl_Interp *interp);

#ifdef __cplusplus
};
#endif

void help()
{
}

#define VTK_TCL_PACKAGE_DIR_BUILD "/net/pc20/workPC20/Eos/lib"
#define VTK_TCL_INSTALL_DIR       "/net/pc20/workPC20/Eos/util/I386LINUX/lib/vtk/tcl"

int Vtktcl_Init(Tcl_Interp *interp)
{
  static char script[] =
    "foreach dir [list {" "~/Eos/lib" "} {" "~/Eos/util/I386LINUX/lib/vtk/tcl" "}"
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

  /* init the core vtk stuff */
  if (Vtkcommontcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }

  if (Vtkfilteringtcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }

  if (Vtkiotcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }

  if (Vtkgraphicstcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }

  if (Vtktkrenderwidget_Init(interp) == TCL_ERROR) 
  	{
	return TCL_ERROR;
    }

  if (Vtkrenderingtcl_Init(interp) == TCL_ERROR) 
  	{
	return TCL_ERROR;
    }

  if (Vtkimagingtcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }
	/*
  if (Vtktkimagewindowwidget_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }
	*/
  if (Vtktkimageviewerwidget_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }

#ifdef PARALLEL
  if (Vtkpatentedtcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }
	
  if (Vtkcontribtcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }

  if (Vtklocaltcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }
  if (Vtkparalleltcl_Init(interp) == TCL_ERROR)
    {
    return TCL_ERROR;
    }
#endif

  vtkAdditionalCommandForEos(interp);
  Tcl_Eval(interp, script);

  return TCL_OK;
}

int Vtktcl_SafeInit(Tcl_Interp *interp)
{
  return Vtktcl_Init(interp);
}



