/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFitAndAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFitAndAverage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataFitAndAverage ver%I%; Date:%D% %Z%";

#include <unistd.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#ifdef PVM
#include "pvm3.h"
#include "PVM.h"
#endif
#include "lllDataFitAndAverage.h"
#include "lllDataCTFCompensation.h"

void 
lllDataFitAndAverage(llData* llAve, llData* llOut, 
                     llData* llIn,  llData llRef, 
					 llDataFittedParam* paraFit, 
					 lllDataFitAndAverageInfo info)
{
	int i, n, l;
	int count;
	int flag;
	FILE* log;

	log = info.fptLog;


	LOGPRINT2(log, "#", "lllDataFitAndAverage", "times: %d , n :%d", info.times, info.nFile);

    /* Fitting */
    fprintf(stdout, "---Fitting---\n");
	llDataFandPHISet(&(llRef));
    for(i=0; i<info.nFile; i++) {
		DEBUGPRINT2("%d: %f\n", i, llIn[i].Weight);
        paraFit[i].PPara.R         = 0.0;
        paraFit[i].PPara.phi.Value = 0.0;
        paraFit[i].PPara.z.Value   = 0.0;
        paraFit[i].PPara.r.Value   = 0.0;
        paraFit[i].PParaInv.R         = 0.0;
        paraFit[i].PParaInv.phi.Value = 0.0;
        paraFit[i].PParaInv.z.Value   = 0.0;
        paraFit[i].PParaInv.r.Value   = 0.0;
	}
	if(!info.flagPVM) {
    	for(i=0; i<info.nFile; i++) {
        	LOGPRINT3(log, "#", "lllDataFit", "times: %4d test: %4d %s", info.times, i, info.In[i]);
        	if(info.flagOutParam2) {
            	lllDataFitWithFile(&(llRef), &(llIn[i]), &(paraFit[i]), info.OutParam2[i], info.mode);
        	} else {
            	lllDataFit(&(llRef), &(llIn[i]), &(paraFit[i]), info.mode);
       		}
    	}
	} else {
#ifdef PVM
		int* which;
		int* task;
		int  startFile;
		int  endFile;
		int  flagEndFile;
		int  flagEnd;
		int  arrived;

		which = (int*)memoryAllocate(sizeof(int)*info.nFile, "in lllDataFitAndAverage"); 
		task  = (int*)memoryAllocate(sizeof(int)*info.vPVM.numTask, "in lllDataFitAndAverage"); 
		for(i=0; i<info.nFile; i++) {
			which[i] = -1;
		}
		memoryClear(task,  sizeof(int)*info.vPVM.numTask, 0);
        LOGPRINT1(log, "#", "lllDataFit", "times: %4d", info.times);
       
		startFile = 0; endFile = 0; flagEnd = 0;
		while(!flagEnd) {
			DEBUGPRINT1("endFile: %d\n", endFile);
			for(n=0; n<info.vPVM.numTask; n++) {  
				if(task[n] == 0 && startFile<info.nFile) { 
					/* If the server is free and this process has more works, */
					LOGPRINT3(log, "#", "lllDataFitStart", "times: %4d test: %4d %s", \
						info.times, startFile, info.In[startFile]);
        			if(info.flagOutParam2) {
            			lllDataFitWithFilePVMStart(
							&(llRef), 
							&(llIn[startFile]), 
							&(paraFit[startFile]), 
							info.OutParam2[startFile], 
							info.vPVM.tids[n], info.mode);
        			} else {
            			lllDataFitPVMStart(
							&(llRef), 
							&(llIn[startFile]), 
							&(paraFit[startFile]), 
							info.vPVM.tids[n], info.mode);
       				}
					task[n]          = 1;
					which[startFile] = n;
					startFile++;
    			}
			}
    		for(i=endFile, flagEndFile=1; i<info.nFile; i++) {
				DEBUGPRINT3("which[%d]=%d: tids: %x\n", i, which[i], info.vPVM.tids[which[i]]);
				if(0<=which[i]) { /* Now Calculating */ 
					arrived = pvm_probe(info.vPVM.tids[which[i]], -1); 	
					DEBUGPRINT3("which[%d]=%d: arrived: %d\n", i, which[i], arrived);
					if(0<arrived) {
        				if(info.flagOutParam2) {
            				lllDataFitWithFilePVMEnd(
								&(llRef), 
								&(llIn[i]), 
								&(paraFit[i]), 
								info.OutParam2[i], 
								info.vPVM.tids[which[i]], info.mode);
        				} else {
            				lllDataFitPVMEnd(
								&(llRef), 
								&(llIn[i]), 
								&(paraFit[i]), 
								info.vPVM.tids[which[i]], info.mode);
       					}
        				LOGPRINT3(log, "#", "lllDataFitEnd", "times: %4d test: %4d %s", \
							info.times, i, info.In[i]);
						
						task[which[i]] = 0;
						which[i]       = -2; /* End Mark */ 
						if(flagEndFile==1) {
							endFile = i + 1;
						}
					} else {
						flagEndFile = 0;
					}
				} else if(which[i] == -1) { /* Not yet start */
					flagEndFile = 1;
					break;
				} else if(which[i] == -2) { /* Already End */
					if(flagEndFile==1) {
						endFile = i + 1;;
					}
				}
			}
			if(endFile==info.nFile) {
				flagEnd = 1;
			} else {
				sleep(1);
			}
    	}
#else
		fprintf(stderr, "Not supported PVM on this machine\n");
		exit(EXIT_FAILURE);
#endif
	}

    /* Averaging */
	if(paraFit[0].Para.flagCTF) {
		DEBUGPRINT("CTF Compensation : in lllDataFitAndAverage");
		info.noise = info.noise/sqrt(info.nFile);
		lllDataMultiCTFCompensation(llAve, llOut, llIn, llRef, paraFit, info, lllDataMultiCTFCompensationModeCTFCompensate);
	} else {
		DEBUGPRINT("Averaging : in lllDataFitAndAverage"); 
		lllDataAverage(llAve, llOut, llIn, llRef, paraFit, info, 0);
	}
	return;
}
