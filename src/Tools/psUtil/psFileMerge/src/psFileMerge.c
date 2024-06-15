/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileMerge ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileMerge
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileMerge ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "Memory.h"
#include "psFile.h"
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"

extern void lpsFileMerge(FILE* ps1, FILE* ps2, FILE* psOut);

int
main(int argc, char* argv[]) 
{
	long status;
	psFileMergeInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
        
	lpsFileMerge(info.fptIn1,info.fptIn2,info.fptOut);
	fprintf(stderr,"Succeed for Ending 2");

	return EXIT_SUCCESS;
}

void
lpsFileMerge(FILE* ps1fpt, FILE* ps2fpt, FILE* psOutfpt)
{
	psFile ps1,ps2;
	psFile psOut;
	char* buffer;
	char message[4096];

	memoryClear(&ps1, sizeof(psFile), 0);	
	memoryClear(&ps2, sizeof(psFile), 0);	
	memoryClear(&psOut, sizeof(psFile), 0);	

	psOut.fpt=psOutfpt;
	psOut.info.page=0;
	psFileRead(&ps1,ps1fpt,0);
	psFileRead(&ps2,ps2fpt,1);
	DEBUGPRINT("Succeed for reading ps file\n");
	fseek(ps1fpt,0L,SEEK_SET);
	buffer = (char*)memoryAllocate(sizeof(char)*ps1.headEnd, "Header");
	fread(buffer,ps1.headEnd,1,ps1fpt);
	fwrite(buffer,ps1.headEnd,1,psOutfpt);
	free(buffer);
	DEBUGPRINT("Succeed for writing head\n");
	ps1.current=ps1.top;
	ps2.current=ps2.top;
	while(NULL!=ps1.current && NULL!=ps2.current){
	        DEBUGPRINT1("Starting page %ld\n",psOut.info.page);
		psFilePageStart(&psOut,1);
		#ifdef DEBUG
			fprintf(stderr,"Succeed for starting page %ld\n",psOut.info.page);
			fprintf(stderr,"ps1 start: %ld; end:%ld\n",ps1.current->start,ps1.current->end);
		#endif
		sprintf(message, "%s %d", "file1", psOut.info.page);
		fseek(ps1fpt,ps1.current->start,SEEK_SET);
		buffer = (char*)memoryAllocate(sizeof(char)*(ps1.current->end-ps1.current->start +2 ), message);
		fread(buffer,(ps1.current->end-ps1.current->start),1,ps1fpt);
		fwrite(buffer,(ps1.current->end-ps1.current->start),1,psOutfpt);
		free(buffer);
		#ifdef DEBUG
			fprintf(stderr,"ps2 start: %ld; end:%ld\n",ps2.current->start,ps2.current->end);
		#endif
		sprintf(message, "%s %d", "file2", psOut.info.page);
		fseek(ps2fpt,ps2.current->start,SEEK_SET);
		buffer = (char*)memoryAllocate(sizeof(char)*(ps2.current->end-ps2.current->start +2 ), message);
		fread(buffer,(ps2.current->end-ps2.current->start),1,ps2fpt);
		fwrite(buffer,(ps2.current->end-ps2.current->start),1,psOutfpt);
		free(buffer);
		psFilePageEnd(&psOut,0);
		psOut.info.page++;
		#ifdef DEBUG
			fprintf(stderr,"Succeed for writing page %ld\n",psOut.info.page);
		#endif

		ps1.current=ps1.current->next;
		ps2.current=ps2.current->next;
	        #ifdef DEBUG
	                fprintf(stderr,"Ending page %ld\n",psOut.info.page);
		#endif

	}
	fprintf(stderr,"Ending ");
	psFileEnd(&psOut);
	fprintf(stderr,"Succeed for Ending ");
}
void
additionalUsage()
{
}








