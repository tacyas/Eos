/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfInfoPVM ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfInfoPVM 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfInfoPVM ver%I%; Date:%D% %Z%";

#include "../inc/ctfInfo.h"

#ifdef PVM
#undef DEBUG
#include <stdio.h>
#include "genUtil.h"
#include "pvm3.h"

void
ctfInfoSendByPVM(ctfInfo* ctf, int tid, long mode) 
{
	int msgtag;

	DEBUGPRINT("ctfInfoSendByPVM\n");
	pvm_initsend(PvmDataDefault);
	pvm_pkfloat(&(ctf->kV), 1, 1);
	pvm_pkfloat(&(ctf->defocus), 1, 1);
	pvm_pkfloat(&(ctf->Cc), 1, 1);
	pvm_pkfloat(&(ctf->Cs), 1, 1);
	pvm_pkfloat(&(ctf->Ain), 1, 1);
	pvm_pklong(&(ctf->flagWin), 1, 1);
	pvm_pkfloat(&(ctf->CutLow), 1, 1);
	pvm_pkfloat(&(ctf->CutHigh), 1, 1);
	pvm_pkfloat(&(ctf->I0), 1, 1);
	pvm_pkfloat(&(ctf->ratioOfAmpToPhase), 1, 1);
	pvm_pkfloat(&(ctf->BofMTF), 1, 1);

	pvm_pklong(&(ctf->flagWhiteNoise), 1, 1);
	pvm_pkfloat(&(ctf->WhiteNoise), 1, 1);

	pvm_pkfloat(&(ctf->MolecEnv), 1, 1);
	pvm_pkfloat(ctf->defocus2D, 2, 1);
	pvm_pkfloat(&(ctf->defocus0axis), 1, 1);

	pvm_pklong(&(ctf->mode), 1, 1);

	msgtag=0; pvm_send(tid, msgtag);
}

void
ctfInfoRecieveByPVM(ctfInfo* ctf, int tid, long mode) 
{
	int msgtag;

	DEBUGPRINT("ctfInfoRecieveByPVM\n");
	msgtag = 0; pvm_recv(tid, msgtag);
	pvm_upkfloat(&(ctf->kV), 1, 1);
	pvm_upkfloat(&(ctf->defocus), 1, 1);
	pvm_upkfloat(&(ctf->Cc), 1, 1);
	pvm_upkfloat(&(ctf->Cs), 1, 1);
	pvm_upkfloat(&(ctf->Ain), 1, 1);
	pvm_upklong(&(ctf->flagWin), 1, 1);
	pvm_upkfloat(&(ctf->CutLow), 1, 1);
	pvm_upkfloat(&(ctf->CutHigh), 1, 1);
	pvm_upkfloat(&(ctf->I0), 1, 1);
	pvm_upkfloat(&(ctf->ratioOfAmpToPhase), 1, 1);
	pvm_upkfloat(&(ctf->BofMTF), 1, 1);

	pvm_upklong(&(ctf->flagWhiteNoise), 1, 1);
	pvm_upkfloat(&(ctf->WhiteNoise), 1, 1);

	pvm_upkfloat(&(ctf->MolecEnv), 1, 1);
	pvm_upkfloat(ctf->defocus2D, 2, 1);
	pvm_upkfloat(&(ctf->defocus0axis), 1, 1);

	pvm_upklong(&(ctf->mode), 1, 1);

}

#endif
