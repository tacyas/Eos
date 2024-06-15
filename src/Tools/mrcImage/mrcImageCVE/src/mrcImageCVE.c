/*
# mrcImageCVE.c  1.1
# The latest update : 04/30/96 at 21:39:25
#
#@(#) mrcImageCVE ver 1.1
#@(#) Created by Isao Sakane April 25, 1996
#@(#)
#@(#) Usage : mrcImageCVE
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageCVE ver1.1; Date:96/04/30 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

void
main(int argc, char* argv[]) 
{
    long status;
    mrcImageCVEInfo info;
    mrcImage dst, src;
    lmrcImageCVEInfo linfo;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

    linfo.sx = info.sx;
    linfo.sy = info.sy;
    linfo.sz = info.sz;

    mrcFileRead(&src, info.In, "in main", 0);
    lmrcImageCVE(&dst, &src, &linfo);
    mrcStatDataSet(&dst, 0);
    mrcFileWrite(&dst, info.Out, "in main", 0);

    exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
