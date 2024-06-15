#include <stdio.h>
#include <math.h>
#include "llData.h"
#define DEBUG
#include "genUtil.h"
#include "Memory.h"

#ifdef PVM
#include "pvm3.h" 
#include "llDataPVM.h" 

void
llDataSendByPVM(llData* ll, int tid, int mode) 
{
	int i;
	int msgtag;
	int info;
	
	/* llData Information Send */
	pvm_initsend(PvmDataDefault);
	pvm_pkint((int*)&(ll->mode), 1, 1);
	pvm_pkint(&(ll->llMax), 1, 1);
	pvm_pkint(&(ll->nRMax), 1, 1);
	pvm_pkfloat(&(ll->truePitch), 1, 1);
	pvm_pkfloat(&(ll->Weight), 1, 1);
	pvm_pkfloat(&(ll->rScale), 1, 1);
	pvm_pkint((int*)&(ll->Pole), 1, 1);
	pvm_pkfloat(&(ll->Side), 1, 1);
	pvm_pkint(&(ll->RRInfoSet), 1, 1);
	pvm_pkint(&(ll->FmaxSet), 1, 1);
	pvm_pkint(&(ll->RValueSet), 1, 1);
	pvm_pkint(&(ll->ZValueSet), 1, 1);
	msgtag = 1;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("llDataSendByPVM");
	}
	for(i=0; i<ll->llMax; i++) {
		 llDataOneLLSendByPVM(&(ll->LL[i]), tid, mode);
	}

}

void
llDataOneLLSendByPVM(oneLLData* LL, int tid, int mode)
{
	int msgtag;
	int info;

	/* oneLL Information Send */
	pvm_initsend(PvmDataDefault);
	pvm_pkbyte(LL->Head, DefaultStringLength, 1);
	pvm_pkfloat(&(LL->Weight), 1, 1);
	pvm_pkint  (&(LL->nn),    1, 1);
	pvm_pkint  (&(LL->nl),    1, 1);
	pvm_pkint  (&(LL->nm),    1, 1);
	pvm_pkint  (&(LL->Side),  1, 1);
	pvm_pkint  (&(LL->nR),    1, 1);
	pvm_pkfloat(&(LL->Z),     1, 1);
	pvm_pkint  (&(LL->iZ),    1, 1);
	pvm_pkfloat(&(LL->RMin),  1, 1);
	pvm_pkint  (&(LL->iRMin), 1, 1);
	pvm_pkfloat(&(LL->RMax),  1, 1);
	pvm_pkint  (&(LL->iRMax), 1, 1);
	pvm_pkfloat(&(LL->delBR), 1, 1);
	pvm_pkfloat(&(LL->Fmax),  1, 1);
	msgtag = 2;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("llDataSendByPVM");
	}

	/* oneLL Data Send */ 
	pvm_initsend(PvmDataDefault);
	pvm_pkfloat((float*)LL->data, LL->nR*sizeof(llComplex)/sizeof(llDataParaTypeReal), 1);
	msgtag = 3;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("llDataSendByPVM");
	}
}

void
llDataRecieveByPVM(llData* ll, int tid, int mode) 
{
	int bufid; /* ID of the new active recieve buffer */
	int i;
	int msgtag;

	msgtag = 1;
	bufid = pvm_recv(tid, msgtag);
	/* block the process until messages with msgtag has arrived from tid
	*/
	if(bufid < 0) {
		fprintf(stderr, "Error: \n");
		return;
	}
	pvm_upkint((int*)&(ll->mode), 1, 1);
	pvm_upkint(&(ll->llMax), 1, 1);
	pvm_upkint(&(ll->nRMax), 1, 1);
	pvm_upkfloat(&(ll->truePitch), 1, 1);
	pvm_upkfloat(&(ll->Weight), 1, 1);
	pvm_upkfloat(&(ll->rScale), 1, 1);
	pvm_upkint((int*)&(ll->Pole), 1, 1);
	pvm_upkfloat(&(ll->Side), 1, 1);
	pvm_upkint(&(ll->RRInfoSet), 1, 1);
	pvm_upkint(&(ll->FmaxSet), 1, 1);
	pvm_upkint(&(ll->RValueSet), 1, 1);
	pvm_upkint(&(ll->ZValueSet), 1, 1);
	
	if(0==mode) { 
		ll->LL = memoryAllocate(sizeof(oneLLData)*ll->llMax, "in llDataRecieveByPVM");
	}
	for(i=0; i<ll->llMax; i++) {
		llDataOneLLRecieveByPVM(&(ll->LL[i]), tid, mode);
	}
}

void
llDataOneLLRecieveByPVM(oneLLData* LL, int tid, int mode)
{
	int bufid; /* ID of the new active recieve buffer */
	int i;
	int msgtag;

	msgtag = 2;
	bufid = pvm_recv(tid, msgtag);
	if(bufid < 0) {
		fprintf(stderr, "Error: \n");
		return;
	}
	pvm_upkbyte (LL->Head, DefaultStringLength, 1);
	pvm_upkfloat(&(LL->Weight), 1, 1);
	pvm_upkint  (&(LL->nn), 1, 1);
	pvm_upkint  (&(LL->nl), 1, 1);
	pvm_upkint  (&(LL->nm), 1, 1);
	pvm_upkint  (&(LL->Side), 1, 1);
	pvm_upkint  (&(LL->nR), 1, 1);
	pvm_upkfloat(&(LL->Z), 1, 1);
	pvm_upkint  (&(LL->iZ), 1, 1);
	pvm_upkfloat(&(LL->RMin), 1, 1);
	pvm_upkint  (&(LL->iRMin), 1, 1);
	pvm_upkfloat(&(LL->RMax), 1, 1);
	pvm_upkint  (&(LL->iRMax), 1, 1);
	pvm_upkfloat(&(LL->delBR), 1, 1);
	pvm_upkfloat(&(LL->Fmax), 1, 1);
		
	if(0==mode) {
		LL->data = (llComplex*)memoryAllocate(sizeof(llComplex)*LL->nR, "in llDataRecieveByPVM");
	}
	msgtag = 3;
	bufid = pvm_recv(tid, msgtag);
	if(bufid < 0) {
		fprintf(stderr, "Error: \n");
		return;
	}
	pvm_upkfloat((float*)LL->data, LL->nR*sizeof(llComplex)/sizeof(llDataParaTypeReal), 1);
}

#endif
