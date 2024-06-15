#include "./PropertyTcl.hh"

int
PropertyTclInit(Tcl_Interp *interp, const char) 
{
	PropertyTclState* statePtr;
	
	statePtr = (PropertyTclState*)Tcl_Alloc(sizeof(PropertyTclState));
	Tcl_InitHashTable(&statePtr->hash, TCL_STRING_KEYS);
	statePtr->uid = 0;

	Tcl_CreateObjCommand(interp, "Property", PropertyTclNewInstance, (ClientData)statePtr, PropertyTclCleanUp);

	return TCL_OK;
}

void
PropertyTclCleanUp(ClientData data)
{
	PropertyTclState* statePtr = (PropertyTclState*)data;
	PropertyTclInfo* propPtr;
	Tcl_HashEntry* entryPtr;
	Tcl_HashSearch search;

	entryPtr = Tcl_FirstHasEntry(&statePtr->hash, &search);
	while(entryPtr != NULL) {
		propPtr = Tcl_GetHashValue(entryPtr);
		PropertyDelete(propPtr, entryPtr);
		entryPtr = Tcl_FirstHashEntry(&statePtr->hash, &search);
	}
	Tcl_Free((char*)statePtr);
}

int
PropertyTclCommand(ClinetData data, Tcl_Interp* interp, int objc, int Tcl_Obj* CONST objv[])
{
	PropertyTclState* statePtr = (PropertyTclState*)data;
	PropertyTclInfo*  propPtr;
	Tcl_HashEntry*  entryPtr;
	Tcl_Obj* valueObjPtr;

	char *subCmds[] = {
		"New", "Delete",
		"GetAtomMode", "SetAtomMode",
		NULL
	}
	enum subCmdsCode {
		NewCode, DeleteCode,
		GetAtomModeCode, SetAtomModeCode
	};

	int result, index;

	if(objc == 1 || 4 < objc) {
		Tcl_WrongNumArgs(interp, 1, objv, "Option ?arg ...?");
		return TCL_ERROR;
	}
	if(Tcl_GetIndexFromObj(interp, objv[1], subCmds, "option", 0, &index) != TCL_OK) {
		return TCL_ERROR;
	}

	if(3<=objc) {
		entryPtr = Tcl_FileHashEntry(&statePtr->hash, Tcl_GetString(objv[2]));
		if(entryPtr==NULL) {
			Tcl_AppendResult(interp, "Unknown: Property: ", 
				Tcl_GetString(objv[2]), NULL);
			return TCL_ERROR;
		}
		propPtr = (PropertyTclInfo*)Tcl_GetHashValue(entryPtr);
	}
	
	switch(index) {
		case NewCode: {
			switch(objc) {
				case 2: {
					return PropertyTclCreate(interp, statePtr);
				}
				default: {
	 				Tcl_WrongNumArgs(interp, 1, objv, "option ?arg ...?");
					return TCL_ERROR;
				}
			}
			break;
		}
		case DeleteCode: {
			switch(objc) {
				case 3: {
					return PropertyTclDelete(propPtr, entryPtr);
				}
				default: {
	 				Tcl_WrongNumArgs(interp, 1, objv, "option ?arg ...?");
					return TCL_ERROR;
				}
			}
			break;
		}
		case GetAtomModeCode: {
			switch(objc) {
				case 3: {
				}
			}
		}
		case SetAtomModeCode: {
			switch(objc) {
			}
		}
	}
}


int
PropertyTclCreate(Tcl_Interp* interp, PropertyTclState* statePtr)
{
	Tcl_HashEntry* entryPtr;

	PropertyTclInfo
}
