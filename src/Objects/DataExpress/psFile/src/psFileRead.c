/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileRead ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "eosString.h"
#include "Memory.h"
#include "../inc/psFile.h"

void
psFileRead(psFile* ps, FILE* fpt, long mode)
{
	char s[MAX_STRING_LENGTH];
	long page;
	long old;

#ifdef DEBUG
		fprintf(stderr,"In psFile Read\n");
#endif
	ps->fpt = fpt;
	fseek(ps->fpt, 0L, SEEK_END);
	ps->byte = ftell(ps->fpt);
	fseek(ps->fpt, 0L, SEEK_SET);
	page = 0;
	old  = 0;
	while(NULL!=stringGetFromFile(s, "", ps->fpt, stdout, 3)) {
		if(psFileIsStartPage(ps, s)) {
			if(0==page) {
				ps->current = (psPageInfo*)memoryAllocate(sizeof(psPageInfo), "in psFileRead");
				ps->top     = ps->current;
				ps->headEnd=old;
			} else {
				ps->current->next = (psPageInfo*)memoryAllocate(sizeof(psPageInfo), "in psFileRead");
				ps->current = ps->current->next;
			}
			if(1==mode){
				stringGetFromFile(s, "", ps->fpt, stdout, 3);
			}
			ps->current->next = NULL;
			ps->current->start = ftell(ps->fpt);
#ifdef DEBUG
				fprintf(stderr,"page %ld start\n",page);
#endif
		} else if(psFileIsEndPage(ps, s)) {
			ps->current->end = old;
#ifdef DEBUG
				fprintf(stderr,"page %ld end\n",page);
#endif
			page++;
		}
		old = ftell(ps->fpt);
	}
}
