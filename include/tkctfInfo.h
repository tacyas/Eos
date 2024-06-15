/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% tkctfInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : tkctfInfo 
#%Z% Attention
#%Z%
*/

#include <tk.h>
#include "ctfInfo.h"

/* struct begin */
typedef struct tkctfInfo {
	int    flagR;
	float* R;
	int    nR;
	ctfInfo ctf;
} tkctfInfo;
/* struct end */

/* prototype begin */
#ifdef __cplusplus
extern "C" {
#endif

extern int tkctfInfoCmdSet(Tcl_Interp* interp);
extern int tkctfInfoFileCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);
extern int tkctfInfoSetCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);
extern int tkctfInfoGetCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);
extern int tkctfInfoCalculateCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);
extern int tkctfInfoCalculate2DCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);
extern int tkctfInfoEvaluateCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);

#ifdef __cplusplus
};
#endif
/* prototype end */
