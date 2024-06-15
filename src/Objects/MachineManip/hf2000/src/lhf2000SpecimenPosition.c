/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lhf2000SepecimenPosition ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lhf2000SepecimenPosition 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lhf2000SepecimenPosition ver%I%; Date:%D% %Z%";
#include "../inc/hf2000.h"
#include "lhf2000SpecimenPosition.h"
#undef DEBUG
#include "genUtil.h"
#include "eosString.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <tcl.h>
#include <tk.h>

void
lhf2000SpecimenPositionGet(hf2000Info* hf2000, lhf2000SpecimenPositionInfo* linfo, int mode) 
{
	char send[1024];
	char recieve[1024];

	DEBUGPRINT("lhf2000SpecimenPositionGet\n")
	sprintf(send, "%s", __hf2000CommandList[HF2000CMD_PositionGet]);
	hf2000Write(hf2000, send); DEBUGPRINT1("%s\n", send);
	hf2000Read (hf2000, recieve);
	if(0!=strncmp(recieve, send, 2)) {
		fprintf(stderr, "Command Error: %s <- %s\n", recieve,  send); fflush(stderr);
		lhf2000SpecimenPositionGet(hf2000, linfo, mode);
		return;
	} else {
	}
	linfo->ix = stringGetNthIntegerData(recieve+2, 1, ",");
	linfo->iy = stringGetNthIntegerData(recieve+2, 2, ",");
	linfo->x = ((float)linfo->ix)/10.0;
	linfo->y = ((float)linfo->iy)/10.0;
	DEBUGPRINT4("PositionGet: %d %d -> %f %f\n", 
		linfo->ix, linfo->iy,
	    linfo->x,  linfo->y);
}

void
lhf2000SpecimenPositionStop(hf2000Info* hf2000, lhf2000SpecimenPositionInfo* linfo, int mode) 
{
	char send[1024];
	char recieve[1024];

	DEBUGPRINT("lhf2000SpecimenPositionStop\n")
	sprintf(send, "%s", __hf2000CommandList[HF2000CMD_PositionStop]);
	hf2000Write(hf2000, send); DEBUGPRINT1("%s\n", send);
	hf2000Read (hf2000, recieve);
	if(0!=strncmp(recieve, send, 2)) {
		fprintf(stderr, "Command Error: %s <- %s\n", recieve,  send); fflush(stderr);
		lhf2000SpecimenPositionStop(hf2000, linfo, mode);
		return;
	} else {
	}
}

void
lhf2000SpecimenPositionSet(hf2000Info* hf2000,  lhf2000SpecimenPositionInfo* linfo, int mode) 
{

	char send[1024];
	char recieve[1024];
	char ans[1024];
	int iter = 0;
	int flag;
	int ix, iy;

	DEBUGPRINT("lhf2000SpecimenPositionSet\n")
	flag = 0;

	/* Check Motor */
	sprintf(send, "%s", __hf2000CommandList[HF2000CMD_PositionMotorInfo]);
	sprintf(ans,  "%s", __hf2000CommandList[HF2000CMD_PositionMotorInfo]);
	hf2000Write(hf2000, send); DEBUGPRINT1("Write %s\n", send);
	hf2000Read (hf2000, recieve); DEBUGPRINT1("Read %s\n", recieve);
	if(0!=strncmp(recieve, ans, 2)) {
		fprintf(stderr, "Set Error: %s <- %s\n", recieve, ans);
		lhf2000SpecimenPositionSet(hf2000, linfo, mode);
		return;
	} else {
		SSWITCH(recieve+strlen(ans)) 
			SCASE("=p") { /* Now Moving */
				lhf2000SpecimenPositionStop(hf2000, linfo, mode);
				SBREAK;
			}
			SCASE("o") { /* Command Complete */
				SBREAK;
			}
			SDEFAULT {
				fprintf(stderr, "Something wrong: Illegal return value: %s\n", recieve);
				SBREAK;
			}	
		SSWITCHEND;
	}
	/* Set Position */
	ix = linfo->ix;
	iy = linfo->iy;
	sprintf(send, "%s%d,%d", __hf2000CommandList[HF2000CMD_PositionSet], ix, iy);
	sprintf(ans,  "%s",     __hf2000CommandList[HF2000CMD_PositionSet]);
	hf2000Write(hf2000, send); DEBUGPRINT1("Write %s\n", send);
	hf2000Read (hf2000, recieve); DEBUGPRINT1("Read %s\n", recieve);
	if(0!=strncmp(recieve, ans, 2)) {
		fprintf(stderr, "Set Error: %s <- %s\n", recieve, ans);
		lhf2000SpecimenPositionSet(hf2000, linfo, mode);
		return;
	} else {
		SSWITCH(recieve+strlen(ans)) 
			SCASE("q") { /* Message OK */
				SBREAK;
			}
			SCASE("=p") { /* Now Moving */
				SBREAK;
			}
			SCASE("c") { /* Command Complete */
				lhf2000SpecimenPositionSet(hf2000, linfo, mode);
				return;
				SBREAK;
			}
			SDEFAULT {
				fprintf(stderr, "Something wrong: Illegal return value: %s\n", recieve);
				SBREAK;
			}	
		SSWITCHEND;
	}
	
	/* Start moving */ 
	sprintf(ans,  "%s", __hf2000CommandList[HF2000CMD_PositionMove]);
	sprintf(send, "%s", __hf2000CommandList[HF2000CMD_PositionMove]);
	hf2000Write(hf2000, send); DEBUGPRINT1("Write %s\n", send);
	hf2000Read (hf2000, recieve); DEBUGPRINT1("Read %s\n", recieve);
	flag = 0;
	if(0!=strncmp(ans, recieve, strlen(ans))) {
		fprintf(stderr, "Something wrong: Illegal return value: %s\n", recieve);
		lhf2000SpecimenPositionSet(hf2000, linfo, mode);
		return;
	} else {
		SSWITCH(recieve+strlen(ans)) 
			SCASE("q") { /* Message OK */
				SBREAK;
			}
			SCASE("c") { /* Command Error */
				fprintf(stderr, "Command Error\n");
				lhf2000SpecimenPositionGet(hf2000, linfo, mode);
				return;
				SBREAK;
			}
			SCASE("=p") { /* Now Moving */
				SBREAK;
			}
			SCASE("o") { /* Command Complete */
				SBREAK;
			}
			SDEFAULT {
				fprintf(stderr, "Something wrong: Illegal return value: %s\n", recieve);
				SBREAK;
			}	
		SSWITCHEND;
	}
	while(1) {
		lhf2000SpecimenPositionGet(hf2000, linfo, mode);
		if(ix==linfo->ix
		 &&iy==linfo->iy) {
		 	break;
		}
	}
}

