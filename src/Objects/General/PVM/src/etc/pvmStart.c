/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pvmStart ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pvmStart 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%pvmStart ver%I%; Date:%D% %Z%";

#ifdef PVM
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "String.h"
#include "File.h"
#include "../inc/PVM.h"
#include "pvm3.h"

int*
pvmServerStart(char* command, char* argv[], FILE* fptHostList, int* n, int mode)
{
	File   f;
	char   s[1024];
	int    numHost;
	char** hostList;
	int*   infos;
	int*   numTasks;
	int    numTask;
	int    nTask;
	int*   tids;
	int    iTask;
	int    i;
	int    info;

	nTask = *n;
	f.fpt = fptHostList;
	if(NULL==fptHostList) {
		DEBUGPRINT1("pvmServerStart: Any Host: %s\n", command);
		tids = (int*)memoryAllocate(sizeof(int)*nTask, "in main");
		numTask = pvm_spawn(command, argv, PvmTaskDefault|mode, NULL, nTask, tids);
		pvmServerStartError(numTask, tids, nTask);
	} else {
		DEBUGPRINT1("pvmServerStart: Specific Host: %s\n", command);
		nTask = 0;
		numHost  = fileLineNumberGet(&f, "");
		if(0==numHost) {
			fprintf(stderr, "No host\n");
			exit(EXIT_FAILURE);
		}
    	hostList = (char**)memoryAllocate(sizeof(char*)*numHost, "in main"); 
    	infos    = (int*)  memoryAllocate(sizeof(int)*numHost, "in main"); 
    	numTasks = (int*)  memoryAllocate(sizeof(int)*numHost, "in main"); 

    	fseek(f.fpt, 0L, SEEK_SET);
    	for(i=0; i<numHost; i++) {
    		stringGetFromFile(s, "Host", fptHostList, stdout, 3);
       	 	hostList[i] = stringGetNthWord(s, 1, " \t,#"); 
        	numTasks[i] = stringGetNthIntegerData(s, 2, " \t,#"); 
        	if(0==numTasks[i]) {
        		numTasks[i] = 0;
        	}
			DEBUGPRINT3("%d: %s %d\n", i, hostList[i], numTasks[i]);
        	nTask += numTasks[i]; 
    	}
    	info = pvm_addhosts(hostList, numHost, infos); 

		tids = (int*)memoryAllocate(sizeof(int)*nTask, "in pvmServerStart")	;

		iTask = 0;
    	for(i=0; i<numHost; i++) {
        	numTask = pvm_spawn(command, argv, PvmTaskHost|mode, hostList[i], numTasks[i], tids+iTask);
			pvmServerStartError(numTask, tids+iTask, numTasks[i]);
			iTask+= numTask;
    	}
	}
	*n = nTask;

	return tids;
}

void
pvmServerStartError(int numTask, int* tids, int nTask)
{
	int i;

    if(numTask==nTask) {
		return;
	} else {
    	fprintf(stderr, "Error:\n");
		if(numTask < 0) {
            switch(numTask) {
                case  PvmBadParam: {
                    fprintf(stderr, "PvmBadParam\n");
                    break;
                }
                case  PvmNoHost: {
                    fprintf(stderr, "PvmNoHost\n");
                    break;
                }
                case  PvmNoFile: {
                    fprintf(stderr, "PvmNoFile\n");
                    break;
                }
                case  PvmNoMem: {
                    fprintf(stderr, "PvmNoMem\n");
                    break;
                }
                case  PvmSysErr: {
                    fprintf(stderr, "PvmSysErr\n");
                    break;
                }
                case  PvmOutOfRes: {
                    fprintf(stderr, "PvmOutOfRes\n");
                    break;
                }
            }
		} 
		for(i=0; i<nTask; i++) {
    		fprintf(stderr, "%d: %x\n", i, tids[i]); 
            switch(tids[i]) {
                case  PvmBadParam: {
                    fprintf(stderr, "PvmBadParam\n");
                    break;
                }
                case  PvmNoHost: {
                    fprintf(stderr, "PvmNoHost\n");
                    break;
                }
                case  PvmNoFile: {
                    fprintf(stderr, "PvmNoFile\n");
                    break;
                }
                case  PvmNoMem: {
                    fprintf(stderr, "PvmNoMem\n");
                    break;
                }
                case  PvmSysErr: {
                    fprintf(stderr, "PvmSysErr\n");
                    break;
                }
                case  PvmOutOfRes: {
                    fprintf(stderr, "PvmOutOfRes\n");
                    break;
                }
            }
		}
		exit(EXIT_FAILURE);
	}
}

#endif
