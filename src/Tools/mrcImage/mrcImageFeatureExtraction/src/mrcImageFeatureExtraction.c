/*
# mrcImageFeatureExtraction : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFeatureExtraction
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageFeatureExtraction.h"

int
main(int argc, char* argv[]) 
{
	mrcImageFeatureExtractionInfo info;
	lmrcImageFeatureExtractionInfo linfo;

	mrcImage in;
    mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in,  info.In , "in main" ,0);

	linfo.co_r = info.co_r;
	linfo.co_theta = info.co_theta;
	linfo.rl_theta = info.rl_theta;
	linfo.rl_dev = info.rl_dev;
	linfo.mode = info.mode;
	lmrcImageFeatureExtraction(&in, &out, linfo, info.mode);
	mrcFileWrite(&out, info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n----- Additional Usage -----\n");
	fprintf(stderr, "Feature list\n0  :densityhistgram average\n1  :densityhistgram variance\n2  :densityhistgram skewness\n3  :densityhistgram kurtosis\n4  :densityhistgram contrast\n5  :densityhistgram energy\n6  :densityhistgram entropy\n7  :co-occurrence anguler second moment\n8  :co-occurrence contrast\n9  :co-occurrence correlation\n10  :co-occurrence sum of square: variance\n11 :co-occurrence inverse difference moment\n12 :co-occurrence sum average\n13 :co-occurrence sum variance\n14 :co-occurrence sum entropy\n15 :co-occurrence entropy\n16 :co-occurrence difference variance\n17 :co-occurrence difference entropy\n18 :co-occurrence information measure of correlation 1\n19 :co-occurrence information measure of correlation 2\n20 :co-occurrence maximal correlation coefficient\n");
	fprintf(stderr, "21 :difference statistics contrast\n22 :difference statistics anguler second moment\n23 :difference statistics entropy\n24 :difference statistics mean\n25 :runlength short runs emphasis\n26 :runlength long runs emphasis\n27 :runlength gray level nonuniformity\n28 :runlength run length nonuniformity\n29 :runlength run percentage\n\n");
}
