#include <string.h>
#include "./eosTclNewCommandCreate.hh"


int
eosTclNewInstanceCommand(ClientData cd, Tcl_Interp* interp,
						int argc, char* argv[])
{
	Tcl_CmdInfo cinfo;

	if(argc != 2) {
		Tcl_WrongNumArgs(interp, 1, argv, "option ?arg ...?");
		return TCL_ERROR;
	}

	if(Tcl_GetCommandInfo(interp, argv[1], &cinf)) {
		Tcl_AppendResult(interp,
			": a tcl/tk command with that name already exists.",
			NULL);
		return TCL_ERROR;
	}

	ClientData temp;

	temp = cs->NewCommand();

	eosTclCommandArgStruct *as = new eosTclCommandArgStruct;
	as->Pointer = (void*)temp;
	as->Interp = interp;

	Tcl_CreateCommand(interp, argv[1],
		reinterpret_cast<eosTclCommandType>(command),
		(ClientData)as,
		(Tcl_CmdDeleteProc*)eostclGenericDeleteObject);
	Tcl_SetResult(interp, argv[1], TCL_VORATILE);

	return TCL_OK;
}

void
eosTclDeleteCommandStruct(ClientData cd)
{
	eosTclCommandStruct *cs = (eosTclCommandStruct *)cd;
	delete cs;
}

void
eosTclNewCommmandCreate(
	Tcl_Interp* interp,
	const char* commandName;
	ClientData (*NewCommand)(),
	int (*CommandFunction)(ClientData cd,
						   Tcl_Interp* interp,
						   int argc, char* argv[]))
{
	eosTclCommandStruct *cs = new eosTclCommandStruct;
	cs->NewCommand = NewCommand;
	cs->CommandFunction = CommandFunction;
	Tcl_CreateCommand(interp, (char*)cname, 
		reinterpret_cast<eosTclCommandType>(
			eosTclNewInstanceCommand),
		(ClientData *)cs,
		(Tcl_CmdDeleteProc *)eosTclDeleteCommandStruct);
}

eosTclCommand::eosTclCommand()
{
	this->Interp = NULL;
	this->StringCommand = NULL;
}

eosTclCommand::~eosTclCommand()
{
	if(this->StringCommand) {
		delete [] this->StringCommand;
	}
}

eosTclCommand::SetStringCommand(const char* arg)
{
	if(this->StringCommand) {
		delete [] this->StringCommand;
	}
	this->StringCommand = strdup(arg);
}
