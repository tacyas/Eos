/*
# angleMatchTest_k : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : angleMatchTest_k
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
#include "eosString.h"
#include "File.h"

#include "genUtil.h"

/*
Example:
typedef struct langleMatchTest_kInfo {
	float a;
	int   b;
} langleMatchTest_kInfo;

typedef enum langleMatchTest_kMode {
	a=0,
	b=1
} langleMatchTest_kMode;
*/

int
main(int argc, char* argv[]) 
{
	angleMatchTest_kInfo info;
	int out1,out2,out3,out11,out22,out33,outsum=0,outsumm=0;
	double pi,e1a,e2a,e1b,e2b,e1r,e2r,er,x1,x2,y1,y2,z1,z2,x,y,z,dis,dislmt,erlmt;
	char s1[256],s2[256];
	double pc1,pc2;
	int count=0;
	double ss;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	ss = (double)info.SS;
	pi=3.1415193/180;
	x1=1.0; y1=0.0;
	x2 = cos(ss*pi); y2 = sin(ss*pi);
	x = x1-x2; y = y1-y2; x=pow(x,2); y=pow(y,2);
	dislmt = pow((x+y),0.5); dislmt = dislmt*0.8;
	erlmt = 8;	
	fseek(info.fptIn1, 0L, SEEK_SET); 
	fseek(info.fptIn2, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s1,"",info.fptIn1,stdout,1)){
		stringGetFromFile(s2,"",info.fptIn2,stdout,1);
		e1a = (double)stringGetNthRealData(s1, 3, " ,\t");
		e1b = (double)stringGetNthRealData(s1, 4, " ,\t");
		e1r = (double)stringGetNthRealData(s1, 5, " ,\t");
		e2a = (double)stringGetNthRealData(s2, 3, " ,\t");
		e2b = (double)stringGetNthRealData(s2, 4, " ,\t");
		e2r = (double)stringGetNthRealData(s2, 5, " ,\t");
		x1=sin(e1b*pi); y1=x1*sin(e1a*pi); x1=x1*cos(e1a*pi); z1=cos(e1b*pi);
		x2=sin(e2b*pi); y2=x2*sin(e2a*pi); x2=x2*cos(e2a*pi); z2=cos(e2b*pi);
		x=x1-x2; y=y1-y2; z=z1-z2;
		x=pow(x,2); y=pow(y,2); z=pow(z,2);
		dis = pow((x+y+z),0.5);
		if(dis<dislmt) out1=1;
		else out1=0;

		if(dis<dislmt*2.0) out11=1;
		else out11=0;

		er = fabs(e1r-e2r-360.0);
		if(er>180.0) er=fabs(er-360);
		
		if(er<erlmt) out2=1;
		else out2=0;

		if(er<2*erlmt) out22=1;
		else out22=0;

		if((out1+out2)==2) out3=1;
		else out3=0;

		if((out11+out22)==2) out33=1;
		else out33=0;

		outsum+=out3;
		outsumm+=out33;
		count++;
		fprintf(info.fptOut,"%f\t%f\t%d\t%d\t%d\t%d\n",dis,er,out1,out2,out11,out22);
	}
	pc1=(outsum*100.0)/(double)count;
	pc2=(outsumm*100.0)/(double)count;
	fprintf(info.fptOut,"dislmt\t%f\toutsum\t%d\t%f\toutsum2\t%d\t%f",dislmt,outsum,pc1,outsumm,pc2);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>>>> InputFileFormat\n");
	fprintf(stderr, "filename MODE Rot1 Rot2 Rot3\n");
	fprintf(stderr, "....\n");
	fprintf(stderr, ">>>>> Algorithm \n");
	fprintf(stderr, "1. Calc each unit directional vector\n");
	fprintf(stderr, "   (sin(Rot2)*cos(Rot1), sin(Rot2)*sin(Rot1), cos(Rot2))\n");
}
