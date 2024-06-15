#include "../inc/gifFile.h"

void
gifFileInit(gifFile* gif, long mode)
{
	gif->Header.sig[0] = 'G';
	gif->Header.sig[1] = 'I';
	gif->Header.sig[2] = 'F';
	gif->Header.ver[0] = '8';
	gif->Header.ver[1] = '9';
	gif->Header.ver[2] = 'a';

	gif->ScrDesc.scwidth  = 1024;
	gif->ScrDesc.scheight = 1024;
	gif->ScrDesc.flags    = 0;
	gif->ScrDesc.bgclr    = 0;
	gif->ScrDesc.pixasp   = 0;

	gif->Tailer        = ';';
}
