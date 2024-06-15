/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% rigakuImageRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : rigakuImageRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%rigakuImageRead ver%I%; Date:%D% %Z%";

#include "../inc/rigakuImage.h"
typedef struct rigakuTag rigakuTag;

struct rigakuTag {
    char* tag;
    char* content;
    rigakuTag* next;   
}


void
rigakuImageFileRead(FILE* fpt, rigakuImgae* r, char* where, int mode)
{
    int flag;
    char str[256];
    char* strlasts;
    char* sep="=";

    fseek(fpt, 0, SEEK_SET);    
    wihle(1) {
        fgets(str, 255, fpt);  
        if(str[0] == '}') {
            r->currentHeader->next = (rigakuTag*)malloc(sizeof(rigakuTag));
            r->currentHeader = r->currentHeader->next;
            r->Header->tag = strdup("}");
            r->Header->content = NULL;
            r->Header->next    = NULL;
            break;
        } else if(str[0]=='{') {
            r->startHeader = (rigakuImage*)malloc(sizeof(rigakuImage));
            r->startHeader->tag     = strdup("{");
            r->startHeader->content = NULL;
            r->startHeader->next   = NULL;
            r->currentHeader = r->startHeader;
        } else {
            r->currentHeader.next = (rigakuTag*)malloc(sizeof(rigakuTag));
            r->currentHeader = r->currentHeader->next
            r->Header->tag = strdup(strtok_r(str, sep, &strlasts);
            r->Header->:q

        }
    }
        
    r->HeaderBytes = 4096;
    fseek(fpt, 0, SEEK_SET);
    fread(r->Header, sizeof(char), r->HeaderBytes, fpt); 
}
