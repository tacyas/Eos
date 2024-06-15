/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ll2ltlg ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ll2ltlg
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ll2ltlg ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "File.h"
#include "llData.h"
#include "ltlgData.h"
#include "lll2ltlg.h"

int
main(int argc, char* argv[]) 
{
    llData   in;
	ltlgData out;
	ltlgDataParaTypeInteger status;
     ll2ltlgInfo  info;
    lll2ltlgInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	memoryClear(&in, sizeof(in), (char)0);			
	memoryClear(&out, sizeof(out), (char)0);			

	linfo.flagIn = info.flagIn;
	linfo.In = info.In;
	linfo.fptIn = info.fptIn;
	linfo.Out = info.Out;
	linfo.fptOut = info.fptOut;
	linfo.flagconfigFile = info.flagconfigFile;
	linfo.configFile= info.configFile;
	linfo.fptconfigFile = info.fptconfigFile;
	linfo.flagTitle = info.flagTitle;
	linfo.Title = info.Title;
	linfo.flagllMax = info.flagllMax;
	linfo.llMax = info.llMax;
	linfo.flagdelRInv = info.flagdelRInv;
	linfo.delRInv = info.delRInv;
	linfo.flagRMaxInv = info.flagRMaxInv;
	linfo.RMaxInv = info.RMaxInv;
	linfo.flagdelr = info.flagdelr;
	linfo.delr = info.delr;
	linfo.flagrMax = info.flagrMax;
	linfo.rMax = info.rMax;
	linfo.mode = info.mode;

	DEBUGPRINT("llDataFileRead");
	if(linfo.flagconfigFile) {
		ll2ltlgConfigFileRead(&linfo, linfo.fptconfigFile);
	}

    llDataFileRead(linfo.fptIn, &in, 0);
	DEBUGPRINT("lll2ltlg");

    lll2ltlg(&out, &in, &linfo);
	DEBUGPRINT("ltlgDataFileWrite");

    ltlgDataFileWrite(linfo.fptOut, &out, 0, &status);
}

void
additionalUsage(void)
{
	fprintf(stderr, ">> controlFile Format : replaced by other options which are definitely shown.\n\n");
	fprintf(stderr, "Title  [char*%d]\n", CommentLength);
	fprintf(stderr, "InFile [char*%d]\n", CommentLength);
	fprintf(stderr, "OutFile[char*%d]\n", CommentLength);
	fprintf(stderr, "InveseOfllDataSamplingSize[Angstrom] llMax llDataMuxiumResolution[Angstrom]\n");
	fprintf(stderr, "ltlgDataSamplingSize[Angstrom] ltlgDataMaximumRadius[Angstrom]\n");
	fprintf(stderr, "IList(mode)\n");
}

