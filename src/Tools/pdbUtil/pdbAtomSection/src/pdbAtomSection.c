/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbAtomSection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbAtomSection
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbAtomSection ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include "mrcImage.h"
#include "pdbFile.h"
#include "Memory.h"
#include "psFile.h"
#include "eosString.h"
#include "Vector.h"

#undef DEBUG
#define    MYMAX(a,b) (((a)>(b)) ? (a):(b))
#define    MYMIN(a,b) (((a)<(b)) ? (a):(b))
#define ONEAAFLAG (1)
#define THREEAAFLAG (2)
#define CHAINFLAG (4)
#define SEQFLAG (8)
#define ANYATOM (16)
#define MORE_DRAW_RATE (1.0/6)
#define GLOBAL_DECLARATION
#include "../inc/config.h"

typedef struct FLAGS{
	int  mode;
	float radius;
	float linew;
	float fontsize;
	float shiftx;
	float shifty;
	float shiftz;
} FLAGS;

extern void lpdbAtomSection(FILE*,pdbFile*,FILE*,float,float,float,float,float,FLAGS);

void
main(int argc, char* argv[]) 
{
	long status;
	pdbAtomSectionInfo info;
	pdbFile in;
	FLAGS flagsIn;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	flagsIn.mode=info.flagMode;
	flagsIn.radius=info.radius;
	flagsIn.linew=info.clinewidth;
	flagsIn.fontsize=info.fontsize;
	flagsIn.shiftx = info.shiftx;
	flagsIn.shifty = info.shifty;
	flagsIn.shiftz = info.shiftz;

	pdbFileRead(info.fptIn, &in); 
    lpdbAtomSection(info.fptOut, &in, info.fptInFlags,info.zmin, info.zmax, info.distance,
				  info.scale,info.plinewidth,flagsIn);
	exit(EXIT_SUCCESS);
}

FLAGS*
getProperty(FILE* flags,char *idenNum,FLAGS defaultFlags){
	char s[MAX_STRING_LENGTH];
	char* word;
	FLAGS *tmp;

	tmp=(FLAGS*)memoryAllocate(sizeof(FLAGS),"in getProperty");
	if(flags==NULL){
		*tmp=defaultFlags;
		return tmp;
	}
	fseek(flags,0L,SEEK_SET);
	while(NULL!=stringGetFromFile(s, "", flags, stdout, 3)) {
		word=stringGetNthWord(s,1," ,");
		if(stringIsSame(idenNum,word,strlen(word))){
			tmp->mode=stringGetNthIntegerData(s,2," ,");
			tmp->radius=stringGetNthRealData(s,3," ,");
			tmp->linew=stringGetNthRealData(s,4," ,");
			tmp->fontsize=stringGetNthRealData(s,5," ,");
			return tmp;
		}
	}	
	*tmp=defaultFlags;
	return tmp;
}
void
sectionLineDraw(psFile* ps,pdbRecord* pdb1,pdbRecord* pdb2,FLAGS defaultFlags,
long iz,float distance,FILE* flags)
{
    float x1,y1,x2,y2;
	float rateSection;
	float rate1Cir;
	float rate2Cir;
	float rateStart;
	float rateEnd;
	float vectorLen;
	floatVector *startPoint;
	floatVector *endPoint;
	floatVector *startToEnd;
    char markerSeek[MAX_STRING_LENGTH];
	FLAGS *flag1,*flag2;

	memset(markerSeek,NULL,strlen(markerSeek));
	markerSeek[0]=pdb1->ChainIdentifier;
	sprintf(&markerSeek[1],"%ld",pdb1->ResidueSequenceNumber);
	flag1=getProperty(flags,markerSeek,defaultFlags);

	memset(markerSeek,NULL,strlen(markerSeek));
	markerSeek[0]=pdb2->ChainIdentifier;
	sprintf(&markerSeek[1],"%ld",pdb2->ResidueSequenceNumber);
	flag2=getProperty(flags,markerSeek,defaultFlags);

	startPoint=floatVectorInit(NULL,3);
	endPoint  =floatVectorInit(NULL,3);
	startToEnd=floatVectorInit(NULL,3);

	startPoint->data[0] = pdb1->Coord.x;
	startPoint->data[1] = pdb1->Coord.y;
	startPoint->data[2] = 0;

	endPoint->data[0]   = pdb2->Coord.x;
	endPoint->data[1]   = pdb2->Coord.y;
	endPoint->data[2]   = 0;
	startToEnd = floatVectorMinus(startToEnd,endPoint,startPoint);
	vectorLen=(float)lfloatVectorLength(startToEnd);
	rate1Cir=flag1->radius /vectorLen;
	rate2Cir=(vectorLen-(flag2->radius))/vectorLen;

	if(pdb2->Coord.z > (iz+1)*distance){
		rateSection=((iz+1)*distance-pdb1->Coord.z)/(pdb2->Coord.z-pdb1->Coord.z);
	}else if(pdb2->Coord.z < iz*distance){
		rateSection=(pdb1->Coord.z-iz*distance)/(pdb1->Coord.z-pdb2->Coord.z);
	}else{
		rateSection=1;
	}
	rateStart = MYMIN(rate1Cir,rateSection);
	rateEnd   = MYMIN(rateSection,rate2Cir);
	if(rateEnd>rateStart){
		x1=pdb1->Coord.x+rateStart*(pdb2->Coord.x-pdb1->Coord.x) + defaultFlags.shiftx;
		y1=pdb1->Coord.y+rateStart*(pdb2->Coord.y-pdb1->Coord.y) + defaultFlags.shifty;
		x2=pdb1->Coord.x+rateEnd*(pdb2->Coord.x-pdb1->Coord.x)   + defaultFlags.shiftx;
		y2=pdb1->Coord.y+rateEnd*(pdb2->Coord.y-pdb1->Coord.y)   + defaultFlags.shifty;
		psFileLineDraw(ps,x1,y1,x2,y2);
	}
}
void
pdbPeptideBond(pdbFile* in,pdbRecord* onePdbRecord,FLAGS defaultFlags,
float linew,psFile* ps,long iz, float distance,FILE* flags)
{
	pdbRecord* previous;
	pdbRecord* next;


	#ifdef DEBUG
   		fprintf(stderr,"%ld\n",pdbFileResidueSequenceNumberGet(in));
	#endif
	psFileLineWidthSet(ps,linew);
	while((previous=pdbFilePrev(in))!=NULL){
		if(pdbFileIsCA(in)&&pdbRecordIsNearby(*onePdbRecord,*previous)) {
			sectionLineDraw(ps,onePdbRecord,previous,defaultFlags,iz,distance,flags);
			break;
		}
	}
	in->PDB=onePdbRecord;
	while((next=pdbFileNext(in))!=NULL){
		if(pdbFileIsCA(in)&&pdbRecordIsNearby(*onePdbRecord,*next)) {
			sectionLineDraw(ps,onePdbRecord,next,defaultFlags,iz,distance,flags);
			break;
		}
	}
	in->PDB=onePdbRecord;

	#ifdef DEBUG
    	fprintf(stderr,"%ld\n\n\n",pdbFileResidueSequenceNumberGet(in));
	#endif
}

void
lpdbAtomSection(FILE* out,pdbFile* in,FILE* flags,float zmin, float zmax, float distance,
				float scale, float plw,FLAGS defaultFlags)
{
    pdbFileParaTypeReal X,Y,Z;
	long   iz;
    psFile ps;
    psImageInfo im;
    double xscale;
	pdbRecord* onePdbRecord;
    char message0[MAX_STRING_LENGTH];
    char marker[MAX_STRING_LENGTH];
    char markerSeek[MAX_STRING_LENGTH];
	char resiNum[64];
	FLAGS* drawFlags;

	xscale=1.0;
	ps.fpt = out;
    psFileInit(&ps, 0);


	for(iz=zmin;iz<zmax;iz++){
		sprintf(ps.info.label, "%ld", iz);
        psFilePageStart(&ps, 0);
		psFileLineWidthSet(&ps,defaultFlags.linew);
		psFileStringDefaultStatusSet(&ps);
        im.scaleX     = 1.0;  im.scaleY     = 1.0;
        im.translateX = 20.0; im.translateY = 40.0;
        psFileImageSpaceSet(&ps, im, 0);
        sprintf(message0, "Scale:%10.2f XScale/YScale:%10.2f Section:%ld (%10.2f)", scale, xscale, iz, iz*distance);
        psFileString(&ps, message0, 0, -30, 0);
        im.scaleX = 72/25.4*scale; im.scaleY = 72/25.4*scale;
        im.translateX = 0.0;              im.translateY = 0.0;
        psFileImageSpaceSet(&ps, im, 0);

	    onePdbRecord=pdbFileTop(in);
		while(NULL!=onePdbRecord){
		  if(pdbFileIsCA(in) || defaultFlags.mode&ANYATOM  ) {
				pdbFileCoordGet(in,&X,&Y,&Z);
				X += defaultFlags.shiftx; 
				Y += defaultFlags.shifty; 
				Z += defaultFlags.shiftz; 
				if(Z<(iz+0.5+MORE_DRAW_RATE)*distance && Z>=(iz-0.5-MORE_DRAW_RATE)*distance){
					memset(marker,NULL,strlen(marker));
					memset(markerSeek,NULL,strlen(markerSeek));
					memset(resiNum,NULL,strlen(resiNum));
					markerSeek[0]=pdbFileChainIdentifierGet(in);
					sprintf(&markerSeek[1],"%ld",pdbFileResidueSequenceNumberGet(in));
					drawFlags=getProperty(flags,markerSeek,defaultFlags);
					pdbPeptideBond(in,onePdbRecord,defaultFlags,plw,&ps,iz,distance,flags);
					psFileCircleCreate(&ps, X, Y, (drawFlags->radius), PS_LINE_CIRCLE_MODE);

					#ifdef DEBUG
						fprintf(stderr,"flag mode %d\n",drawFlags->mode);
					#endif
					if(0!=drawFlags->mode){
						if(0!=(drawFlags->mode&CHAINFLAG)){
							marker[0]=pdbFileChainIdentifierGet(in);
							#ifdef DEBUG
								fprintf(stderr,"chain marker %s\n",marker);
							#endif
						}
						if(0!=(drawFlags->mode&SEQFLAG)){
							sprintf(resiNum,"%ld",pdbFileResidueSequenceNumberGet(in));
							strcat(marker,resiNum);
							#ifdef DEBUG
								fprintf(stderr,"sequence marker %s\n",marker);
							#endif
						}
						if(0!=(drawFlags->mode&THREEAAFLAG)){
							strcat(marker,pdbFileResidueNameGet(in,RESIDUE_THREECHAR_MODE));
						}else if(0!=(drawFlags->mode&ONEAAFLAG)){
							strcat(marker,pdbFileResidueNameGet(in,RESIDUE_ONECHAR_MODE));
						}

						#ifdef DEBUG
							fprintf(stderr,"marker %s\n",marker);
						#endif
						psFileStringStatusSet(&ps,"/Times-Roman",drawFlags->fontsize);
						psFileString(&ps,marker,(double)X,(double)Y,0);
					}/* if(0!=drawFlags->mode) */

				}/* in the section */                
					
			}/* IsCA */
			onePdbRecord=pdbFileNext(in);
		}
        psFileImageSpaceRestore(&ps, im, 0);
        psFileImageSpaceRestore(&ps, im, 0);

        psFilePageEnd(&ps, 0);
	}
    psFileEnd(&ps);
}
void
additionalUsage()
{
	fprintf(stderr,"\n\n\nformat for Flags File\n");

	fprintf(stderr,"one line of the file\n");
	fprintf(stderr,"chainIdertifier&sequenceNumber(R123) FlagMode circleRedius circlelinewidth fontsize\n");
	fprintf(stderr,"FlagMode\n");
	fprintf(stderr,"     0: display nothing\n");
	fprintf(stderr,"     1: one char amino acid name\n");
	fprintf(stderr,"     2: three char amino acid name\n");
	fprintf(stderr,"     4: chain identifier\n");
	fprintf(stderr,"     8: sequence number\n");
	fprintf(stderr,"    16: display any atom\n");
	fprintf(stderr,"     default: 13 (display R123T)\n");
}
