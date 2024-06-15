/*
# vtkAdditionalCommandForEos.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : vtkAdditionalCommandForEos.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <tcl.h>
#ifdef __cplusplus
extern "C" {
#endif

int
vtkAdditionalCommandForEos(Tcl_Interp* interp);

#ifdef __cplusplus
};
#endif

extern int Vtktcl_SafeInit(Tcl_Interp *interp);
