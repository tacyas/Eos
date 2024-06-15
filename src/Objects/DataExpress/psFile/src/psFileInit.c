/*
# psFileInit.c  1.1
# The latest update : 06/15/96 at 14:37:41
#
#@(#) psFileInit ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : psFileInit 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)psFileInit ver1.1; Date:96/06/15 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "psFile.h"
#include "Memory.h"

static char* psPrologStringList[] = {
    "%%!%s\n",
    "%%%%Title: %s\n",
    "%%%%Creator: %s\n",
    "%%%%CreationDate: %s\n",
    "%%%%For: %s\n",
    "%%%%BoundingBox: %s\n",
    "%%%%Pages: %s\n",
    "%%%%DocumentsFonts: %s\n",
    "%%%%EndDocuments\n",
    "%%%%EndProlog\n",
    "%%%%EndComments\n", 
    NULL
};

static char* psPrologDefaultString[] = {
    "PS-Adobe-2.0",
    "",
    "",
    "",
    "",
    "atend",
    "atend",
    "atend",
    "",
    "",
    "",
    NULL
};
/*
* PostScript Initialize routine
*/

static void __psInit(psInfo* info, psParaTypeInteger mode);
static void __psInitFile(FILE* fpt, psInfo info, psParaTypeInteger mode);
void
psFileInit(psFile* ps, psParaTypeInteger mode)
{
	__psInit(&ps->info, mode);
	__psInitFile(ps->fpt, ps->info, mode);
}
void 
__psInit(psInfo* info, psParaTypeInteger mode)
{
    int i;
    time_t t;

    i=0;
    while(NULL!=psPrologStringList[i]) {
        i++;
    }
    info->prologInfoNum = i;
    info->prologInfo = (char**)memoryAllocate(sizeof(char*)*info->prologInfoNum, "in psInit (psInfo)");
    info->status = PS_FILE_STATUS_OK;
    for(i=0; i<info->prologInfoNum; i++) {
        info->prologInfo[i] = psPrologDefaultString[i];
    }
    info->prologInfo[PROLOG_CREATOR] = getenv("USER");
    info->prologInfo[PROLOG_FOR]     = getenv("USER");
    time(&t);
    info->prologInfo[PROLOG_CREATION_DATE] = ctime(&t);
    info->prologInfo[PROLOG_CREATION_DATE][24] = '\0';
}

void
__psInitFile(FILE* fpt, psInfo info, psParaTypeInteger mode)
{   
    int i;

    if(NULL==fpt) {
        fprintf(stderr, "File Pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<info.prologInfoNum; i++) {
        if(NULL==info.prologInfo[i]) {
            fprintf(fpt, psPrologStringList[i]);
        } else {
            fprintf(fpt, psPrologStringList[i], info.prologInfo[i]);
        }
    }
    fprintf(fpt, "/mt  {moveto} def\n");
    fprintf(fpt, "/rmt {rmoveto} def\n");
    fprintf(fpt, "/lt  {lineto} def\n");
    fprintf(fpt, "/rlt {rlineto} def\n");
    fprintf(fpt, "/str {stroke} def\n");
}
