#ifndef EOS_TCL_NEW_COMMAND_CREATE_HH
#define EOS_TCL_NEW_COMMAND_CREATE_HH

#include <tcl.h>

class eosTclCommand
{
public:	
	char* StringCommand;
	Tcl_Interp *Interp;
protected:
	eosTclCommand();
	~eosTclCommand();
};

struct eosTclCommandStruct {
	ClientData (*NewCommand)(void);
	int        (*CommandFunction)(ClientData cd, Tcl_Interp* interp, int argc, char *argv[]);
};

extern int  eosTclNewInstanceCommand(ClientData cd, Tcl_Interp* interp, int argc, char* argv[]);
extern void eosTclDeleteCommandStruct(ClientData cd);
extern void eosTclNewCommmandCreate(
	Tcl_Interp* interp,
	const char* commandName,
	ClientData (*NewCommand)(),
	int (*CommandFunction)(ClientData cd,
						   Tcl_Interp* interp,
						   int argc, char* argv[]));

#endif
