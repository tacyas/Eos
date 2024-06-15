/* # %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataFit ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#undef DEBUG
#include "genUtil.h"

#include "../inc/llData.h"
#include "lllDataFit.h"
#include "File.h"
#include "Memory.h"
#include "mrcImage.h"


#ifdef PVM
#include "ctfInfo.h"
#include "llDataPVM.h"
#include "PVM.h"

void 
lllDataFitServerStart(lllDataFitPVMInfo* linfo, FILE* fpt, int numTask)
{
	int my_tid;
	char* arg[] = { (char*) 0 };

    /* PVM Start */
	pvm_catchout(stdout);
    my_tid = pvm_mytid();

	pvm_catchout(stdout);
    if(NULL!=fpt) {
        linfo->tids = pvmServerStart("llDataFitServer", arg, fpt, &numTask, 0);
    } else {
        linfo->tids = pvmServerStart("llDataFitServer", arg, NULL,            &numTask, 0);
    }
    linfo->numTask = numTask;
}

void 
lllDataFitServerEnd(lllDataFitPVMInfo linfo)
{
	int i;

	for(i=0; i<linfo.numTask; i++) {
		pvm_kill(linfo.tids[i]);
	}
	pvm_exit();
}

void
lllDataFitPVMStart(llData* llref, llData* llp, llDataFittedParam* p, int tid, long mode)
{
	int msgtag;
	int info;


	DEBUGPRINT("lllDataFitPVMStart Start");
	/* Send */
	llDataSendByPVM(llref, tid, 0);
	llDataSendByPVM(llp,   tid, 0);

	lllDataFittedParamSendByPVM(p, tid, 0);

	msgtag = 0;
	pvm_initsend(PvmDataDefault);
	pvm_pklong(&mode, 1, 1);
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("lllDataFitPVMStart:");
	}
}

void
lllDataFitPVMEnd(llData* llref, llData* llp, llDataFittedParam* p, int tid, long mode) 
{
	DEBUGPRINT("lllDataFitPVMEnd Start");
	lllDataFittedParamRecieveByPVM(p, tid, 1);
	fflush(stdout);
	fflush(stderr);
}

void
lllDataFitPVMServer()
{
	llData 				llref;
	llData 				llp;
	llDataFittedParam 	p;
	long mode;
	int  tid;
	int msgtag;
	int bufid;
	int info;

	while(1) {
		DEBUGPRINT("lllDataFitPVMServer Start\n");

		memoryClear(&llref, sizeof(llData), 0);	
		memoryClear(&llp,   sizeof(llData), 0);	
		memoryClear(&p, sizeof(llDataFittedParam), 0);	

		tid = pvm_parent();

		/* Recieve */
		llDataRecieveByPVM(&llref, 	 tid, 0);
		llDataRecieveByPVM(&llp, 	 tid, 0);
		lllDataFittedParamRecieveByPVM(&p, tid, 0);
		msgtag = 0; bufid = pvm_recv(tid, msgtag);
		if(bufid<0) {
			fprintf(stderr, "Cannot recieve mode\n"); pvm_perror("lllDataFitPVMServer:");
		}
		info = pvm_upklong(&mode, 1, 1);
		if(info<0) {
			fprintf(stderr, "Cannot recieve mode\n"); pvm_perror("lllDataFitPVMServer:");
		}

		/* Calc */
		DEBUGPRINT1("lllDataFitPVMServer Fit Start: %d\n", mode);
		lllDataFit(&llref, &llp, &p, mode);
		DEBUGPRINT("lllDataFitPVMServer Fit End \n");
		fflush(stderr);	
		fflush(stdout);	

		/* Send */
		DEBUGPRINT("lllDataFitPVMServer Send Results\n");
		lllDataFittedParamSendByPVM(&p, tid, 0);
		DEBUGPRINT("lllDataFitPVMServer Send End\n");

		/* Memory Free */
		llDataFree(&llref);
		llDataFree(&llp);
		lllDataFittedParameterFree(&p);
	}
}

void
lllDataFitWithFilePVMStart(llData* llref, llData* llp, llDataFittedParam* p, char* filename, int tid, long mode)
{
	char filename2[1024];

	sprintf(filename2, "%s.anti", filename);

	p->flagFitFile     = 1;	
	p->fitFileName     = filename;
	p->fitFileNameAnti = filename2;
	
	lllDataFitPVMStart(llref, llp, p, tid, mode);
}

void
lllDataFitWithFilePVMEnd(llData* llref, llData* llp, llDataFittedParam* p, char* filename, int tid, long mode)
{
	lllDataFitPVMEnd(llref, llp, p, tid, mode);
}

void
lllDataFittedParamSendByPVM(llDataFittedParam* p, int tid, int mode)
{
	int msgtag;
	int info;
	lllDataParamToFitSendByPVM(&(p->Para), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->PPara), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->QPara), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->Q2Para), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->RPara), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->PParaInv), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->QParaInv), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->Q2ParaInv), tid, mode);
	lllDataParamToFitSendByPVM2(&(p->RParaInv), tid, mode);

	pvm_initsend(PvmDataDefault);
	pvm_pkint  (&(p->flagFitFile),  1, 1);
	msgtag = 0; info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("lllDataFittedParamSendByPVM");
	}

	if(p->flagFitFile) {
		DEBUGPRINT("flagFitFile Send\n")
		pvm_initsend(PvmDataDefault);
		pvm_pkbyte(p->fitFileName, 1024, 1);
		pvm_pkbyte(p->fitFileNameAnti, 1024, 1);
		msgtag = 0; info = pvm_send(tid, msgtag);
		if(info<0) {
			pvm_perror("lllDataFittedParamSendByPVM");
		}
	}
}

void
lllDataFittedParamRecieveByPVM(llDataFittedParam* p, int tid, int mode)
{
	char s[1024];
	int msgtag;

	lllDataParamToFitRecieveByPVM(&(p->Para), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->PPara), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->QPara), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->Q2Para), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->RPara), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->PParaInv), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->QParaInv), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->Q2ParaInv), tid, mode);
	lllDataParamToFitRecieveByPVM2(&(p->RParaInv), tid, mode);

	msgtag = 0; pvm_recv(tid, msgtag);
	pvm_upkint  (&(p->flagFitFile),  1, 1);

	if(p->flagFitFile) {
		DEBUGPRINT("flagFitFile Recieve\n")
		msgtag = 0; pvm_recv(tid, msgtag);
		if(0==mode) {
			p->fitFileName     = (char*)memoryAllocate(sizeof(char)*1024, "in lllDataFitPVMFittedParamRecieve"); 
			p->fitFileNameAnti = (char*)memoryAllocate(sizeof(char)*1024, "in lllDataFitPVMFittedParamRecieve kk"); 
		}
		pvm_upkbyte(p->fitFileName, 1024, 1);
		pvm_upkbyte(p->fitFileNameAnti, 1024, 1);
	}
}

void
lllDataParamToFitSendByPVM(llDataParamToFit* p, int tid, int mode)
{
	int msgtag;
	int info;
	int nitem;

	lllDataParaTypeRegionSendByPVM(&(p->Omega), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->x), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->z), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->r), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->phi), tid, mode);
	
	pvm_initsend(PvmDataDefault);
	pvm_pkint  ((int*)&(p->Pole),    1, 1);
	pvm_pkfloat(&(p->R),     1, 1);
	pvm_pkint  (&(p->flagResolution), 1, 1);
	pvm_pkfloat(&(p->Resolution),     1, 1);

	pvm_pkint  (&(p->flagCTF), 1, 1);
	pvm_pkint  (&(p->flagllCTF), 1, 1);
	pvm_pkint  (&(p->flagLLTable), 1, 1);
	msgtag = 0; info = pvm_send(tid, msgtag);

	if(info<0) {
		pvm_perror("lllDataParamToFitSendByPVM");
	}


	DEBUGPRINT3("lllDataParamToFitRecieveByPVM: flag d CTF. %d llCTF. %d LLTable %d\n", p->flagCTF, p->flagllCTF, p->flagLLTable);
	if(p->flagCTF) {
		ctfInfoSendByPVM(&(p->CTF), tid, 0);

		pvm_initsend(PvmDataDefault);
		pvm_pkint  (&(p->ctfCompensationMode), 1, 1);
		pvm_pkfloat(&(p->ctfCutOff), 1, 1);
		msgtag = 0; info = pvm_send(tid, msgtag);
		if(info<0) {
			pvm_perror("lllDataParamToFitSendByPVM");
		}
	}

	if(p->flagllCTF) {
		llDataSendByPVM(&(p->llCTF), tid, 0);
	}

	if(p->flagLLTable) {
		pvm_initsend(PvmDataDefault);
		pvm_pkint(p->llTable, p->flagLLTable, 1);
		msgtag = 0; info = pvm_send(tid, msgtag);
		if(info<0) {
			pvm_perror("lllDataParamToFitSendByPVM");
		}
	}
}

void
lllDataParamToFitSendByPVM2(llDataParamToFit* p, int tid, int mode)
{
	int msgtag;
	int info;
	int nitem;

	lllDataParaTypeRegionSendByPVM(&(p->Omega), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->x), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->z), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->r), tid, mode);
	lllDataParaTypeRegionSendByPVM(&(p->phi), tid, mode);
	
	pvm_initsend(PvmDataDefault);
	pvm_pkint  ((int*)&(p->Pole),    1, 1);
	pvm_pkfloat(&(p->R),     1, 1);
	pvm_pkint  (&(p->flagResolution), 1, 1);
	pvm_pkfloat(&(p->Resolution),     1, 1);

	pvm_pkint  (&(p->flagCTF), 1, 1);
	pvm_pkint  (&(p->flagllCTF), 1, 1);
	pvm_pkint  (&(p->flagLLTable), 1, 1);
	msgtag = 0; info = pvm_send(tid, msgtag);

	if(info<0) {
		pvm_perror("lllDataParamToFitSendByPVM");
	}

}

void
lllDataParamToFitRecieveByPVM(llDataParamToFit* p, int tid, int mode)
{
	int msgtag;
	int nitem;
	int flagCTF;
	int flagllCTF;
	int flagLLTable;
	
	flagCTF = p->flagCTF;
	flagllCTF =  p->flagllCTF;
	flagLLTable =  p->flagLLTable;

	lllDataParaTypeRegionRecieveByPVM(&(p->Omega), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->x), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->z), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->r), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->phi), tid, mode);
	
	msgtag = 0; pvm_recv(tid, msgtag);
	pvm_upkint  ((int*)&(p->Pole),  1, 1);
	pvm_upkfloat(&(p->R),     1, 1);
	pvm_upkint  (&(p->flagResolution), 1, 1);
	pvm_upkfloat(&(p->Resolution),     1, 1);

	pvm_upkint  (&(p->flagCTF), 1, 1);
	pvm_upkint  (&(p->flagllCTF), 1, 1);
	pvm_upkint  (&(p->flagLLTable), 1, 1);

	DEBUGPRINT4("lllDataParamToFitRecieveByPVM: phi %f %f %f %f\n", p->phi.Min, p->phi.Max, p->phi.Delta, p->phi.Value);
	DEBUGPRINT4("lllDataParamToFitRecieveByPVM: z   %f %f %f %f\n", p->z.Min, p->z.Max, p->z.Delta, p->z.Value);
	DEBUGPRINT3("lllDataParamToFitRecieveByPVM: flag d CTF. %d llCTF. %d LLTable %d\n", p->flagCTF, p->flagllCTF, p->flagLLTable);
	if(p->flagCTF) {
		if(flagCTF==0 && mode==0) {
			ctfInfoRecieveByPVM(&(p->CTF), tid, 0);
		} else {
			ctfInfoRecieveByPVM(&(p->CTF), tid, 1);
		}
		msgtag = 0; pvm_recv(tid, msgtag);
		pvm_upkint  (&(p->ctfCompensationMode), 1, 1);
		pvm_upkfloat(&(p->ctfCutOff), 1, 1);
	}

	if(p->flagllCTF) {
		if(flagllCTF==0 && mode==0) {
			llDataRecieveByPVM(&(p->llCTF), tid, 0);
		} else {
			llDataRecieveByPVM(&(p->llCTF), tid, 1);
		}
	}

	if(p->flagLLTable) {
		if(flagLLTable==0 && mode==0) {
			p->llTable = (llDataParaTypeInteger*)memoryAllocate(sizeof(llDataParaTypeInteger)*p->flagLLTable, "");
		}
		msgtag = 0; pvm_recv(tid, msgtag);
		pvm_upkint(p->llTable, p->flagLLTable, 1);
	}
}

void
lllDataParamToFitRecieveByPVM2(llDataParamToFit* p, int tid, int mode)
{
	int msgtag;
	int nitem;
	int flagCTF;
	int flagllCTF;
	int flagLLTable;
	
	flagCTF = p->flagCTF;
	flagllCTF =  p->flagllCTF;
	flagLLTable =  p->flagLLTable;

	lllDataParaTypeRegionRecieveByPVM(&(p->Omega), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->x), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->z), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->r), tid, mode);
	lllDataParaTypeRegionRecieveByPVM(&(p->phi), tid, mode);
	
	msgtag = 0; pvm_recv(tid, msgtag);
	pvm_upkint  ((int*)&(p->Pole),  1, 1);
	pvm_upkfloat(&(p->R),     1, 1);
	pvm_upkint  (&(p->flagResolution), 1, 1);
	pvm_upkfloat(&(p->Resolution),     1, 1);

	pvm_upkint  (&(p->flagCTF), 1, 1);
	pvm_upkint  (&(p->flagllCTF), 1, 1);
	pvm_upkint  (&(p->flagLLTable), 1, 1);

}

void
lllDataParaTypeRegionSendByPVM(llDataParaTypeRegion* r, int tid, int mode)
{
	int msgtag;
	int info;

	pvm_initsend(PvmDataDefault);
	pvm_pkfloat(&(r->Min), 1, 1);
	pvm_pkfloat(&(r->Max), 1, 1);
	pvm_pkfloat(&(r->Delta), 1, 1);
	pvm_pkfloat(&(r->Value), 1, 1);

	msgtag = 0; info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("lllDataParaTypeRegionSendByPVM");
	}
}

void
lllDataParaTypeRegionRecieveByPVM(llDataParaTypeRegion* r, int tid, int mode)
{
	int msgtag;
	int info;
	int bufid;
	int bytes;
	int tids;
	
	DEBUGPRINT("lllDataParaTypeRegionRecieveByPVM Start\n");
	msgtag = 0; 
	/*
	bufid = 0; 
	while(bufid <= 0) {
		bufid = pvm_probe(tid, msgtag);
		if(0<bufid) {
			break;
		} else if(bufid<0) {
			pvm_perror("lllDataParaTypeRegionRecieveByPVM");
			exit(EXIT_FAILURE);
		} 
	}
	*/
	bufid = pvm_recv(tid, msgtag);
	if(bufid < 0) {
		pvm_perror("lllDataParaTypeRegionRecieveByPVM");
	}
	info = pvm_bufinfo(bufid, &bytes, &msgtag, &tids);
	if(info<0) {
		pvm_perror("lllDataParaTypeRegionRecieveByPVM");
	}
	DEBUGPRINT4("bufinfo: %d %d %d %d\n", bufid, bytes, msgtag, tids);
	
	info = pvm_upkfloat(&(r->Min), 1, 1);
	if(info < 0) {
		DEBUGPRINT("lllDataParaTypeRegionRecieveByPVM: Error");
		pvm_perror("lllDataParaTypeRegionRecieveByPVM");
	}

	info = pvm_upkfloat(&(r->Max), 1, 1);
	if(info < 0) {
		pvm_perror("lllDataParaTypeRegionRecieveByPVM");
	}

	info = pvm_upkfloat(&(r->Delta), 1, 1);
	if(info < 0) {
		pvm_perror("lllDataParaTypeRegionRecieveByPVM");
	}

	info = pvm_upkfloat(&(r->Value), 1, 1);
	if(info < 0) {
		pvm_perror("lllDataParaTypeRegionRecieveByPVM");
	}
}

#endif

