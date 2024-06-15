/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFilePageMerge ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFilePageMerge
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFilePageMerge ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include "Memory.h"
#define GLOBAL_DECLARATION
#include "psFile.h"
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"

extern void lpsFilePageMerge(FILE* ps1, FILE* psOut, int page);

void
main(int argc, char* argv[]) 
{
	long status;
	psFilePageMergeInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	DEBUGPRINT("start\n");
	lpsFilePageMerge(info.fptIn, info.fptOut, info.Page);
	exit(EXIT_SUCCESS);
}

void
lpsFilePageMerge(FILE* ps1fpt, FILE* psOutfpt, int page)
{
	psFile ps1;
	psFile psOut;
	char* buffer;
	int i;

	memoryClear(&ps1, sizeof(psFile), 0);	
	memoryClear(&psOut, sizeof(psFile), 0);	

	psOut.fpt=psOutfpt;
	psOut.info.page=0;
	psFileRead(&ps1,ps1fpt,0);

	fseek (ps1fpt,0L,SEEK_SET);
	buffer = (char*)memoryAllocate(sizeof(char)*ps1.headEnd, "Header");
	fread (buffer, ps1.headEnd, 1, ps1fpt);
	fwrite(buffer, ps1.headEnd, 1, psOutfpt);
	free(buffer);

	ps1.current=ps1.top;
	psFileInit(&psOut, 1);
	while(NULL!=ps1.current){
		psFilePageStart(&psOut, 1);
		for(i=0; i<page; i++) {
		    DEBUGPRINT1("%d ",i);    
			fseek (ps1fpt, ps1.current->start,                    SEEK_SET);
		    DEBUGPRINT("a ");    
			buffer = (char*)memoryAllocate(sizeof(char)*(ps1.current->end-ps1.current->start +2 ), "");
		    DEBUGPRINT1("start: %d ",ps1.current->end-ps1.current->start);    
			fread (buffer, (ps1.current->end-ps1.current->start), 1, ps1fpt);
		    DEBUGPRINT("b ");    
			fwrite(buffer, (ps1.current->end-ps1.current->start), 1, psOutfpt);
		    DEBUGPRINT("c ");    
			fwrite("grestore\n", sizeof("grestore\n"), 1, psOutfpt); 
		    DEBUGPRINT("d ");    
			free(buffer);
			DEBUGPRINT("e2 ");    
			ps1.current=ps1.current->next;
		    DEBUGPRINT("e ");    
			if(NULL==ps1.current) {
				break;
			}
		}
		DEBUGPRINT("f\n");    
		psFilePageEnd(&psOut,0);
		psOut.info.page++;
	}
	psFileEnd(&psOut);
}
void
additionalUsage()
{
}
