/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lhf2000LenzCurrent ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lhf2000LenzCurrent 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%lhf2000LenzCurrent ver%I%; Date:%D% %Z%";

#include "../inc/hf2000.h"
#include "lhf2000LenzCurrent.h"
#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <tcl.h>
#include <tk.h>

extern hf2000LenzCurrent lhf2000LenzCurrentGet0(hf2000Info* hf2000, char* s, int mode);

#define CurrentConstantC1    1365.0 
#define CurrentConstantC2 1397760.0 
#define CurrentConstantC3    1360.0 
#define CurrentConstantOBJ 698880.0 
#define CurrentConstantI1 1398860.0 
#define CurrentConstantI2    1365.0 
#define CurrentConstantP1    1365.0 
#define CurrentConstantP2     910.0 

#define VoltageConstantC1   30000  
#define VoltageConstantC2   30000 
#define VoltageConstantC3   30068 
#define VoltageConstantOBJ  60000 
#define VoltageConstantI1   30000 
#define VoltageConstantI2   30000 
#define VoltageConstantP1   30000 
#define VoltageConstantP2   30000 

void
lhf2000LenzCurrentGet(hf2000Info* hf2000, lhf2000LenzCurrentInfo* linfo, int mode) 
{
	DEBUGPRINT("lhf2000LenzCurrentGet\n")
	linfo->C1  = lhf2000LenzCurrentGet0(hf2000, "C1", 0);
	linfo->C2  = lhf2000LenzCurrentGet0(hf2000, "C2", 0);
	linfo->C3  = lhf2000LenzCurrentGet0(hf2000, "C3", 0);
	linfo->OBJ = lhf2000LenzCurrentGet0(hf2000, "OBJ", 0);
	linfo->I1  = lhf2000LenzCurrentGet0(hf2000, "I1", 0);
	linfo->I2  = lhf2000LenzCurrentGet0(hf2000, "I2", 0);
	linfo->P1  = lhf2000LenzCurrentGet0(hf2000, "P1", 0);
	linfo->P2  = lhf2000LenzCurrentGet0(hf2000, "P2", 0);
}

hf2000LenzCurrent
lhf2000LenzCurrentGet0(hf2000Info* hf2000, char* s, int mode) 
{
	hf2000LenzCurrent C;
	char send[1024];
	char recieve[1024];

	DEBUGPRINT("lhf2000LenzCurrentGet\n")
	SSWITCH(s) 
		SCASE("C1") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_C1Get]);
		}
		SCASE("C2") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_C2Get]);
		}
		SCASE("C3") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_C3Get]);
		}
		SCASE("OBJ") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_OBJGet]);
		}
		SCASE("I1") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_I1Get]);
		}
		SCASE("I2") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_I2Get]);
		}
		SCASE("P1") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_P1Get]);
		}
		SCASE("P2") {
			sprintf(send, "%s",  __hf2000CommandList[HF2000CMD_P2Get]);
		}
		SDEFAULT {
			fprintf(stderr, "Not supported Lenz");
			C.D = -1;	
			return C;
		}
	SSWITCHEND;
	hf2000Write(hf2000, send); DEBUGPRINT1("%s\n", send);
	hf2000Read (hf2000, recieve);
	if(0!=strncmp(recieve, send, 3)) {
		fprintf(stderr, "Command Error: %s <- %s\n", recieve,  send); fflush(stderr);
		C = lhf2000LenzCurrentGet0(hf2000, s, mode);
		return C;
	} else {
	}
	SSWITCH(s) 
		SCASE("C1") {
			sscanf(recieve+3, "%3x", &(C.D));
			C.A = C.D/CurrentConstantC1*VoltageConstantC1/VoltageConstantC1; 
		}
		SCASE("C2") {
			sscanf(recieve+3, "%6x", &(C.D));
			C.A = C.D/CurrentConstantC2*VoltageConstantC2/VoltageConstantC2; 
		}
		SCASE("C3") {
			sscanf(recieve+3, "%3x", &(C.D));
			C.A = C.D/CurrentConstantC3*VoltageConstantC3/VoltageConstantC3; 
		}
		SCASE("OBJ") {
			sscanf(recieve+3, "%6x", &(C.D));
			C.A = C.D/CurrentConstantOBJ*VoltageConstantOBJ/VoltageConstantOBJ; 
		}
		SCASE("I1") {
			sscanf(recieve+3, "%6x", &(C.D));
			C.A = C.D/CurrentConstantI1*VoltageConstantI1/VoltageConstantI1; 
		}
		SCASE("I2") {
			sscanf(recieve+3, "%3x", &(C.D));
			C.A = C.D/CurrentConstantI2*VoltageConstantI2/VoltageConstantI2; 
		}
		SCASE("P1") {
			sscanf(recieve+3, "%3x", &(C.D));
			C.A = C.D/CurrentConstantP1*VoltageConstantP1/VoltageConstantP1; 
		}
		SCASE("P2") {
			sscanf(recieve+3, "%3x", &(C.D));
			C.A = C.D/CurrentConstantP2*VoltageConstantP2/VoltageConstantP2; 
		}
		SDEFAULT {
			fprintf(stderr, "Not supported Lenz");
			C.D = -1;	
			return C;
		}
	SSWITCHEND;
	return C;
}

