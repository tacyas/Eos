#include <stdlib.h>
#include "psFile.h"
#include "../inc/llData.h"
/*
	llDataInfoPrint(
		FILE*   fpt,	File Pointer to be output
		llData* ll,     LayerLineData Pointer to be treated
		long    mode	What infomation do you want?
		);  

*/

#define PLOT_SCALE (50.0)

void
lllDataInfoPrint(FILE* fpt, llData* ll, long mode)
{
	long   l, count;
    psFile ps;



    psFileInit(&ps, 0);
    psFilePageStart(&ps, 0);

    for(l=0; l<ll->llMax; l++) {
        if(ll->LL[l].Weight != 0.0) {
            
        }
    }
    psFilePageEnd(&ps, 0);
    psFileEnd(&ps);
    
}

void
lllDataInfoPrint2(FILE* fpt, llData* nea, llData* far, long mode)
{
	long   l;
    psFile ps;

    psFileInit(&ps, 0);
    psFilePageStart(&ps, 0);



    psFilePageEnd(&ps, 0);
    psFileEnd(&ps);
}


