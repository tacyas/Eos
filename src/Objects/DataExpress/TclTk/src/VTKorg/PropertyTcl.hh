#ifndef PROPERTY_TCL_HH
#define PROPERTY_TCL_HH

#include <tcl.h>
#include "Property.hh"

typedef struct PropertyTclInfo {
	int N;
	Tcl_Obj* objPtr;
	Tcl_Obj* cmdPtr;
} PropertyTclInfo;

typedef struct PropertyTclState {
	Tcl_HashTable hash;
	int           uid;
} PropertyTclState;

extern int PropertyTclInit(Tcl_Interp *interp); 

#endif
