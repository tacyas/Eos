/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAutoFilamentExtract ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAutoFilamentExtract
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageAutoFilamentExtract ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#define UNDEBUG2
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageAutoFilamentExtractROIInfo {
	float blx;
	float bly;
	float brx;
	float bry;
	float trx;
	float try;
	float tlx;
	float tly;
	float* roiLine;
	float ddYmax;
	float ddYmin;
	char* InS;
	FILE* fptInS;
	float ROIx;
	float ROIy;
	int   T;
	char* OutF;
	FILE* fptOutF;
	char* OutE;
	FILE* fptOutE;
	int   finaly;
} lmrcImageAutoFilamentExtractROIInfo;

typedef struct lmrcImageAutoFilamentExtractInfo {
	mrcImageParaTypeInteger Height;
	mrcImageParaTypeInteger HeightRange;
	int dY;
	int maxdY;
	float RMaxX;
	float mag;
	float truePitch;
	float PixelSize;
	float calcdY;
	float deltadY;
	float calcHeightRange;
	char* In;
	FILE* fptIn;
	char* Out;
	FILE* fptOut;
	long mode;
} lmrcImageAutoFilamentExtractInfo;

typedef enum lmrcImageAutoFilamentExtractMode {
	MeridianReflection = 0,
	AllLayerLines = 1
} lmrcImageAutoFilamentExtractMode;

extern void __lmrcImageAutoFilamentExtractParameterFromIn  (mrcImage* in,     mrcImageAutoFilamentExtractInfo* info,
														        		     lmrcImageAutoFilamentExtractInfo* linfo,
												                             lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractParameterFromOutE(mrcImage* in,     mrcImageAutoFilamentExtractInfo* info,
																             lmrcImageAutoFilamentExtractInfo* linfo,
												                             lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentROIParameter            (mrcImage* in, mrcImage* inS,
																	         mrcImageAutoFilamentExtractInfo* info,
																            lmrcImageAutoFilamentExtractInfo* linfo,
												                            lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractROI                              ( mrcImageAutoFilamentExtractInfo* info,
																	        lmrcImageAutoFilamentExtractInfo* linfo, 
												                            lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractUnbent                           ( mrcImageAutoFilamentExtractInfo* info,
																   	        lmrcImageAutoFilamentExtractInfo* linfo, 
															                lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractMeridian                         (lmrcImageAutoFilamentExtractInfo* linfo,
																            lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractAll                              (lmrcImageAutoFilamentExtractInfo* linfo,
																            lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractHeader           (mrcImage* in,   lmrcImageAutoFilamentExtractInfo* linfo,
														        	        lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractFFTInfoMeridian                  (lmrcImageAutoFilamentExtractInfo* linfo,
																            lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentExtractFFTInfoAll                       (lmrcImageAutoFilamentExtractInfo* linfo,
																            lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);
extern void __lmrcImageAutoFilamentFinalResult                             (lmrcImageAutoFilamentExtractInfo* linfo,
																            lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode);

int
main(int argc, char* argv[])
{
	mrcImageAutoFilamentExtractInfo info;
	lmrcImageAutoFilamentExtractROIInfo ROIinfo; 
	lmrcImageAutoFilamentExtractInfo linfo;
	mrcImage in;
	mrcImage inS;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	/* If final y has already discovered, final extracition program start */
	if(info.flagfinaly && info.flagOutF && !(info.flagIgnore)){
		__lmrcImageAutoFilamentExtractParameterFromOutE (&in,        &info, &linfo, &ROIinfo, 0);
		__lmrcImageAutoFilamentROIParameter             (&in, &inS,  &info, &linfo, &ROIinfo, 0);
		__lmrcImageAutoFilamentFinalResult              (                   &linfo, &ROIinfo, 0);
	exit(EXIT_SUCCESS);
	}

	/* Set Extraction or ROI parameter*/
	if((info.flagblx || info.flagroiLine || info.flagT) && info.flagInS){
		__lmrcImageAutoFilamentExtractParameterFromIn  (&in,        &info, &linfo, &ROIinfo, 0);
		__lmrcImageAutoFilamentROIParameter            (&in, &inS,  &info, &linfo, &ROIinfo, 0);
			if(info.flagblx && info.flagInS){
					__lmrcImageAutoFilamentExtractROI              (&info, &linfo, &ROIinfo, 0);
			}
			if(info.flagroiLine && info.flagInS){
					__lmrcImageAutoFilamentExtractUnbent           (&info, &linfo, &ROIinfo, 0);
			}
		__lmrcImageAutoFilamentExtractParameterFromOutE(&in,        &info, &linfo, &ROIinfo, 0);
	} else {
		__lmrcImageAutoFilamentExtractParameterFromIn  (&in,        &info, &linfo, &ROIinfo, 0);
		__lmrcImageAutoFilamentROIParameter            (&in, &inS,  &info, &linfo, &ROIinfo, 0);
	}

	/* Extraction */
	switch(info.mode){
		case MeridianReflection: {
			__lmrcImageAutoFilamentExtractMeridian                (&linfo,  &ROIinfo, 0);
			__lmrcImageAutoFilamentExtractHeader(&in,              &linfo,  &ROIinfo, 0);
			__lmrcImageAutoFilamentExtractFFTInfoMeridian         (&linfo,  &ROIinfo, 0);
			break;
			}
		case AllLayerLines: {
			__lmrcImageAutoFilamentExtractAll                     (&linfo,  &ROIinfo, 0);
			__lmrcImageAutoFilamentExtractHeader(&in,              &linfo,  &ROIinfo, 0);
			__lmrcImageAutoFilamentExtractFFTInfoAll              (&linfo,  &ROIinfo, 0);
			break;
			}
		default: {
			fprintf(stderr, "Not supported in lmrcImageAutoFilamentExtractMode: %d\n", (int)info.mode);
			exit(EXIT_FAILURE);
			}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "0 : Meridian Reflection \n");
	fprintf(stderr, "1 : All layer-lines\n");
	fprintf(stderr, "----- NOTE for Heigth Range-----\n");
	fprintf(stderr, "HR option is stranger than caliculated HR\n");
	fprintf(stderr, "----- NOTE for ROI-----\n");
	fprintf(stderr, "-rROI, -rUnbent, -iS, -ddYmax, -ddYmin and -T options are for ROI\n");
	fprintf(stderr, "----- NOTE for File for Extraction-----\n");
	fprintf(stderr, "-oE file use as extraction file.\n");
	fprintf(stderr, "----- NOTE for FINAL-----\n");
	fprintf(stderr, "-finaly and -oF is for final extraction\n");
	fprintf(stderr, "-truePitch, -Ly and -dY are for magnification change\n");
	fprintf(stderr, "-Ignore option ignore finaly\n");
	fprintf(stderr, "This extract do with magnification and header change\n");
}

void
__lmrcImageAutoFilamentExtractParameterFromIn (mrcImage* in,  mrcImageAutoFilamentExtractInfo* info,
											        		 lmrcImageAutoFilamentExtractInfo* linfo, 
												             lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	DEBUGPRINT("############ SET EXTRACT PARAMETER FROM IN ############\n");

	mrcHeaderRead(in, info->In, "in __lmrcImageAutoFilamentExtractParameter From In", 0);

	linfo->calcdY          = (in->HeaderN.y*info->PixelSize)/(info->truePitch*info->mag);
	linfo->deltadY         = linfo->calcdY - (int)linfo->calcdY;
	linfo->calcHeightRange = info->truePitch*2*linfo->deltadY/info->PixelSize;
	linfo->Height          = in->HeaderN.y;
	if (info->flagHeightRange){
				linfo->HeightRange = info->HeightRange;
	} else {
				linfo->HeightRange = 2*(int)(linfo->calcHeightRange/2);
	}
	linfo->dY              = (int)(linfo->calcdY);
	linfo->maxdY           = info->maxdY;
	linfo->RMaxX           = info->RMaxX;
	linfo->mag             = info->mag;
	linfo->truePitch       = info->truePitch;
	linfo->PixelSize       = info->PixelSize;
	linfo->In              = info->In;
	linfo->fptIn           = info->fptIn;
	linfo->Out             = info->Out;
	linfo->fptOut          = info->fptOut;
	linfo->mode            = info->mode;

	DEBUGPRINT3("calcdY=%15.6f deltadY=%15.6f dY=%d\n", linfo->calcdY, linfo->deltadY, linfo->dY);
	DEBUGPRINT2("calcHeightRange=%15.6f HeightRange=%d\n", linfo->calcHeightRange, (int)linfo->HeightRange);

	/* Is maxdY over the Y range? */ 
	if(((linfo->Height-linfo->HeightRange)/2)<=(linfo->dY*linfo->maxdY)){
		fprintf(stderr, "dY*maxdY %d value beyond min Ny/2 %d \n",
						  (int)(linfo->dY*linfo->maxdY), 
						  (int)((linfo->Height-linfo->HeightRange)/2));
		exit(EXIT_FAILURE);
	}
}

void
__lmrcImageAutoFilamentExtractParameterFromOutE (mrcImage* in,  mrcImageAutoFilamentExtractInfo* info,
											                   lmrcImageAutoFilamentExtractInfo* linfo, 
												               lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	DEBUGPRINT("############ SET EXTRACT PARAMETER FROM OutE ############\n");

	mrcHeaderRead(in, info->OutE, "in __lmrcImageAutoFilamentExtractParameter From OutE", 0);

	linfo->calcdY          = (in->HeaderN.y*info->PixelSize)/(info->truePitch*info->mag);
	linfo->deltadY         = linfo->calcdY - (int)linfo->calcdY;
	linfo->calcHeightRange = info->truePitch*2*linfo->deltadY/info->PixelSize;
	linfo->Height          = in->HeaderN.y;
	if (info->flagHeightRange){
				linfo->HeightRange = info->HeightRange;
	} else {
				linfo->HeightRange = 2*(int)(linfo->calcHeightRange/2);
	}
	linfo->dY              = (int)(linfo->calcdY);
	linfo->maxdY           = info->maxdY;
	linfo->RMaxX           = info->RMaxX;
	linfo->mag             = info->mag;
	linfo->truePitch       = info->truePitch;
	linfo->PixelSize       = info->PixelSize;
	linfo->In              = info->In;
	linfo->fptIn           = info->fptIn;
	linfo->Out             = info->Out;
	linfo->fptOut          = info->fptOut;
	linfo->mode            = info->mode;

	DEBUGPRINT3("calcdY=%15.6f deltadY=%15.6f dY=%d\n", linfo->calcdY, linfo->deltadY, linfo->dY);
	DEBUGPRINT2("calcHeightRange=%15.6f HeightRange=%d\n", linfo->calcHeightRange, (int)linfo->HeightRange);

	/* Is maxdY over the Y range? */ 
	if(((linfo->Height-linfo->HeightRange)/2)<=(linfo->dY*linfo->maxdY)){
		fprintf(stderr, "dY*maxdY %d value beyond min Ny/2 %d \n",
						  (int)(linfo->dY*linfo->maxdY), 
						  (int)((linfo->Height-linfo->HeightRange)/2));
		exit(EXIT_FAILURE);
	}
}

void
__lmrcImageAutoFilamentROIParameter     (mrcImage* in, mrcImage* inS,  
													   mrcImageAutoFilamentExtractInfo* info,
													  lmrcImageAutoFilamentExtractInfo* linfo,
												      lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	DEBUGPRINT("###########SET ROI PARAMETER###########\n");
	ROIinfo->blx          = info->blx;
	ROIinfo->bly          = info->bly;
	ROIinfo->brx          = info->brx;
	ROIinfo->bry          = info->bry;
	ROIinfo->trx          = info->trx;
	ROIinfo->try          = info->try;
	ROIinfo->tlx          = info->tlx;
	ROIinfo->tly          = info->tly;
	ROIinfo->roiLine      = info->roiLine;
	ROIinfo->ddYmax       = info->ddYmax;
	ROIinfo->ddYmin       = info->ddYmin;
	ROIinfo->T            = info->T;
	if (info->flagx){
		ROIinfo->ROIx     = info->x;
	} else {
		ROIinfo->ROIx     = in->HeaderN.x;
	}
	ROIinfo->ROIy         = in->HeaderN.y;
	ROIinfo->finaly       = info->finaly;
	ROIinfo->InS          = info->InS;
	ROIinfo->fptInS       = info->fptInS;
	ROIinfo->OutF         = info->OutF;
	ROIinfo->fptOutF      = info->fptOutF;
	ROIinfo->OutE         = info->OutE;
	ROIinfo->fptOutE      = info->fptOutE;
	mrcHeaderRead(in ,   linfo->In,  "in __lmrcImageAutoFilamentROIParameter In", 0);
	if (info->flagInS){
		mrcHeaderRead(inS, ROIinfo->InS, "in __lmrcImageAutoFilamentROIParameter InS", 0);
	}

	DEBUGPRINT2("Before: ROIx=%f ROIy=%f\n",ROIinfo->ROIx, ROIinfo->ROIy);
	DEBUGPRINT3("deltadY=%f ddYmin=%f ddYmax%f\n", linfo->deltadY, ROIinfo->ddYmin, ROIinfo->ddYmax);
	DEBUGPRINT3("dY=%d truePitch=%f mag=%f \n",(int)linfo->dY, info->truePitch, info->mag);

	if((info->flagfinaly && !(info->flagIgnore))){
			ROIinfo->ROIy = ROIinfo->finaly;
	} else {
		if(linfo->deltadY <= ROIinfo->ddYmin){
			ROIinfo->ROIy = (( (int)linfo->dY + ROIinfo->ddYmin) * info->truePitch * info->mag) / info->PixelSize;
			DEBUGPRINT1("deltadY<ddYmin:  ROIy=%f\n", ROIinfo->ROIy);
		}
		if(linfo->deltadY >= ROIinfo->ddYmax){
			ROIinfo->ROIy = (( 1 + (int)linfo->dY + ROIinfo->ddYmin) * info->truePitch * info->mag) / info->PixelSize;
			DEBUGPRINT1("deltadY>ddYmax:  ROIy=%f\n", ROIinfo->ROIy);
		}
	}
	DEBUGPRINT2("After: ROIx=%f ROIy=%f\n",ROIinfo->ROIx, ROIinfo->ROIy);
	
}

void 
__lmrcImageAutoFilamentExtractROI       (mrcImageAutoFilamentExtractInfo* info,
										lmrcImageAutoFilamentExtractInfo* linfo, 
										lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	int ROIx, ROIy;
	char commandROI[1000];
	char commandTRANSEPOSE[200];
	char FilenameInROI[100];
	char FilenameOutROI[100];
	char FilenameInTRANSEPOSE[100];
	char FilenameOutTRANSEPOSE[100];
	char commandRM[200];
	DEBUGPRINT("###########Extract AREA###########\n");
		ROIx = ((int)(ROIinfo->ROIx/2))*2 -1 ; /* change odd number */
		ROIy = ((int)(ROIinfo->ROIy/2))*2 -1 ;
		DEBUGPRINT2("ROIx= %d ROIy= %d\n", ROIx, ROIy);

		if(info->flagT){
			DEBUGPRINT("###########ROI and Transpose###########\n");
			sprintf (FilenameInROI , "%s",     ROIinfo->InS);
			sprintf (FilenameOutROI, "%s.temp",ROIinfo->OutE);
			sprintf (commandROI, "%s %s %s %s %s %s %f %f %f %f %f %f %f %f %s %d %s %d %s", 
									"mrcImageROI", "-i", FilenameInROI, "-o", FilenameOutROI,
									"-r", ROIinfo->blx, ROIinfo->bly, ROIinfo->brx, ROIinfo->bry, 
										  ROIinfo->trx, ROIinfo->try, ROIinfo->tlx, ROIinfo->tly,
									"-x", (int)ROIy,
									"-y", (int)ROIx, "-m 2\n"); 
			fprintf(stderr, commandROI);
			system (commandROI);

			sprintf (FilenameInTRANSEPOSE, "%s", FilenameOutROI);
			sprintf (FilenameOutTRANSEPOSE, "%s",     ROIinfo->OutE);
			sprintf (commandTRANSEPOSE, "%s %s %s %s %s %s %d \n", 
									"mrcImageTranspose", "-i", FilenameInTRANSEPOSE, 
														 "-o", FilenameOutTRANSEPOSE,
														 "-m", (int)ROIinfo->T);
			fprintf(stderr, commandTRANSEPOSE);
			system (commandTRANSEPOSE);

			sprintf (commandRM, "rm -f %s\n", FilenameOutROI);
			fprintf(stderr, commandRM);
			system (commandRM);


		} else {
			DEBUGPRINT("###########ROI ###########\n");
			sprintf (FilenameInROI , "%s", ROIinfo->InS);
			sprintf (FilenameOutROI, "%s", ROIinfo->OutE);
			sprintf (commandROI, "%s %s %s %s %s %s %f %f %f %f %f %f %f %f %s %d %s %d %s", 
									"mrcImageROI", "-i", FilenameInROI, "-o", FilenameOutROI,
									"-r", ROIinfo->blx, ROIinfo->bly, ROIinfo->brx, ROIinfo->bry, 
										  ROIinfo->trx, ROIinfo->try, ROIinfo->tlx, ROIinfo->tly,
									"-x", (int)ROIx,
									"-y", (int)ROIy, "-m 2\n"); 
			fprintf(stderr, commandROI);
			system (commandROI);
		}
}

void
__lmrcImageAutoFilamentExtractUnbent     (mrcImageAutoFilamentExtractInfo* info,
										 lmrcImageAutoFilamentExtractInfo* linfo, 
										 lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	int ROIx, ROIy;
	long i, n;
	char commandUNBENT[1000];
	char commandTRANSEPOSE[200];
	char FilenameInUNBENT[100];
	char FilenameOutUNBENT[100];
	char FilenameInTRANSEPOSE[100];
	char FilenameOutTRANSEPOSE[100];
	char commandRM[200];
	DEBUGPRINT("###########Extract AREA###########\n");
		ROIx = ((int)(ROIinfo->ROIx/2))*2 ; /* change even number */
		ROIy = ((int)(ROIinfo->ROIy/2))*2 ;
		n = info->flagroiLine;	
		DEBUGPRINT2("ROIx= %d ROIy= %d\n", ROIx, ROIy);
		
		if(info->flagT){
			DEBUGPRINT("###########Unbent and Transepose###########\n");
			sprintf (FilenameInUNBENT , "%s",     ROIinfo->InS);
			sprintf (FilenameOutUNBENT, "%s.temp",ROIinfo->OutE);
			sprintf (commandUNBENT, "%s %s %s %s %s %s %d %s %d %s ", 
									"mrcImageUnbentROI", "-i", FilenameInUNBENT, "-o", FilenameOutUNBENT,
									"-x", (int)ROIy,
									"-y", (int)ROIx, "-r");
			for(i=0; i<n; i++) {
				sprintf (commandUNBENT+strlen(commandUNBENT), "%f ", info->roiLine[i]);
			}
			fprintf(stderr, commandUNBENT);
			fprintf(stderr, "\n");
			system (commandUNBENT);

			sprintf (FilenameInTRANSEPOSE, "%s", FilenameOutUNBENT);
			sprintf (FilenameOutTRANSEPOSE, "%s",     ROIinfo->OutE);
			sprintf (commandTRANSEPOSE, "%s %s %s %s %s %s %d \n", 
									"mrcImageTranspose", "-i", FilenameInTRANSEPOSE, 
														  "-o", FilenameOutTRANSEPOSE,
														  "-m", (int)ROIinfo->T);
			fprintf(stderr, commandTRANSEPOSE);
			system (commandTRANSEPOSE);

			sprintf (commandRM, "rm -f %s\n", FilenameOutUNBENT);
			fprintf(stderr, commandRM);
			system (commandRM);

		} else {
			DEBUGPRINT("###########Unbent###########\n");
			sprintf (FilenameInUNBENT , "%s", ROIinfo->InS);
			sprintf (FilenameOutUNBENT, "%s", ROIinfo->OutE);
			sprintf (commandUNBENT, "%s %s %s %s %s %s %d %s %d %s ", 
									"mrcImageUnbentROI", "-i", FilenameInUNBENT, "-o", FilenameOutUNBENT,
									"-x", (int)ROIx,
									"-y", (int)ROIy, "-r");
			for(i=0; i<n; i++) {
				sprintf (commandUNBENT+strlen(commandUNBENT), "%f ", info->roiLine[i]);
			}
			fprintf(stderr, commandUNBENT);
			fprintf(stderr, "\n");
			system (commandUNBENT);
		}
}

void
__lmrcImageAutoFilamentExtractMeridian  (lmrcImageAutoFilamentExtractInfo* linfo,
										 lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	char commandROI[200];
	char commandPROJECT[200];
	char commandFFT[200];
	char FilenameInROI[100];
	char FilenameInPROJECT[100];
	char FilenameInFFT[100];
	char FilenameOutROI[100];
	char FilenameOutPROJECT[100];
	char FilenameOutFFT[100];
	char commandRM1[200];
	char commandRM2[200];
	int Height;
	int HeightRange;

	for(HeightRange=0; HeightRange<=linfo->HeightRange; HeightRange+=2) {	
		Height = linfo->Height -HeightRange;
		
		/* ROI */
		sprintf (FilenameInROI , "%s", ROIinfo->OutE);
		sprintf (FilenameOutROI, "%s.%d", FilenameInROI, Height);
		sprintf (commandROI, "%s %s %s %s %s %s %d %s",
							 "mrcImageROI", "-i", FilenameInROI, "-o", FilenameOutROI, "-y", Height-1, "-m 2\n"); 
		DEBUG2PRINT(commandROI);
		system (commandROI);

		/* PROJECTION */
		sprintf (FilenameInPROJECT , "%s", FilenameOutROI);
		sprintf (FilenameOutPROJECT, "%s.proj", FilenameInPROJECT);
		sprintf (commandPROJECT, "%s %s %s %s %s %s", 
								 "mrcImageProjection", "-i", FilenameInPROJECT, "-o", FilenameOutPROJECT, "-m 3\n"); 
		DEBUG2PRINT(commandPROJECT);
		system (commandPROJECT);

		/* FFT */
		sprintf (FilenameInFFT , "%s", FilenameOutPROJECT);
		sprintf (FilenameOutFFT, "%s.fft", FilenameInFFT);
		sprintf (commandFFT, "%s %s %s %s %s %s", 
							 "mrcImageFFT", "-i", FilenameInFFT, "-o", FilenameOutFFT, "\n"); 
		DEBUG2PRINT(commandFFT);
		system (commandFFT);

		sprintf (commandRM1, "rm -f %s\n", FilenameOutROI);
		fprintf(stderr, commandRM1);
		system (commandRM1);
		sprintf (commandRM2, "rm -f %s\n", FilenameOutPROJECT);
		fprintf(stderr, commandRM2);
		system (commandRM2);
	}
}

void
__lmrcImageAutoFilamentExtractAll(lmrcImageAutoFilamentExtractInfo* linfo,
								  lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	char commandROI[200];
	char commandFFT[200];
	char commandFFTFILTER[200];
	char commandPROJECT[200];
	char FilenameInROI[100];
	char FilenameInFFT[100];
	char FilenameInFFTFILTER[100];
	char FilenameInPROJECT[100];
	char FilenameOutROI[100];
	char FilenameOutFFT[100];
	char FilenameOutFFTFILTER[100];
	char FilenameOutPROJECT[100];
	char commandRM1[200];
	char commandRM2[200];
	char commandRM3[200];
	int Height;
	int HeightRange;

	for(HeightRange=0; HeightRange<=linfo->HeightRange; HeightRange+=2) {	
		Height = linfo->Height -HeightRange;
		
		/* ROI */
		sprintf (FilenameInROI , "%s", ROIinfo->OutE);
		sprintf (FilenameOutROI, "%s.%d", FilenameInROI, Height);
		sprintf (commandROI, "%s %s %s %s %s %s %d %s", 
							 "mrcImageROI", "-i", FilenameInROI, "-o", FilenameOutROI, "-y", Height-1, "-m 2\n"); 
		DEBUG2PRINT(commandROI);
		system (commandROI);

		/* FFT */
		sprintf (FilenameInFFT , "%s", FilenameOutROI);
		sprintf (FilenameOutFFT, "%s.fft", FilenameInFFT);
		sprintf (commandFFT, "%s %s %s %s %s %s", 
							 "mrcImageFFT", "-i", FilenameInFFT, "-o", FilenameOutFFT, "\n"); 
		DEBUG2PRINT(commandFFT);
		system (commandFFT);

		/* FILTER X */
		sprintf (FilenameInFFTFILTER , "%s", FilenameOutFFT);
		sprintf (FilenameOutFFTFILTER, "%s.fil", FilenameInFFTFILTER);
		sprintf (commandFFTFILTER, "%s %s %s %s %s %s %f %s",
								   "mrcFFTXFiltering", "-i", FilenameInFFTFILTER, "-o", FilenameOutFFTFILTER, 
								   "-RMaxX", linfo->RMaxX, "\n"); 
		DEBUG2PRINT(commandFFTFILTER);
		system (commandFFTFILTER);

		/* PROJECTION */
		sprintf (FilenameInPROJECT , "%s", FilenameOutFFTFILTER);
		sprintf (FilenameOutPROJECT, "%s.proj", FilenameInPROJECT);
		sprintf (commandPROJECT, "%s %s %s %s %s %s", 
								 "mrcFFTProjection", "-i", FilenameInPROJECT, "-o", FilenameOutPROJECT, "\n");
		DEBUG2PRINT(commandPROJECT);
		system (commandPROJECT);

		sprintf (commandRM1, "rm -f %s\n", FilenameOutROI);
		fprintf(stderr, commandRM1);
		system (commandRM1);
		sprintf (commandRM2, "rm -f %s\n", FilenameOutFFT);
		fprintf(stderr, commandRM2);
		system (commandRM2);
		sprintf (commandRM3, "rm -f %s\n", FilenameOutFFTFILTER);
		fprintf(stderr, commandRM3);
		system (commandRM3);

	}
}

void
__lmrcImageAutoFilamentExtractHeader(mrcImage* in, lmrcImageAutoFilamentExtractInfo* linfo,
												   lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	int l;

	/* 1 line */ 
	fprintf(linfo->fptOut, "%s  ", linfo->In);
	fprintf(linfo->fptOut, "PixelRange %d to %d dY= %d     ", 
							(int)(linfo->Height - linfo->HeightRange), 
							(int)linfo->Height,
							(int)linfo->dY);
	switch(linfo->mode){
		case MeridianReflection: {
				fprintf (linfo->fptOut, "MeridianReflection ");
			break;
			}
		case AllLayerLines: {
				fprintf (linfo->fptOut, "AllLayerLinesRefLection ");
			break;
			}
		default: {
			fprintf(stderr, "Not supported in lmrcImageAutoFilamentExtractMode: %d\n", (int)linfo->mode);
			exit(EXIT_FAILURE);
			}
	}
	fprintf(linfo->fptOut, "CaliculatedCenter= %d\n", 
							(int)(linfo->truePitch * linfo->dY * linfo->mag / linfo->PixelSize));
	/* 2 line */ 
	fprintf(linfo->fptOut, "calcdY=%15.6f deltadY=%15.6f calcHeightRange=%15.6f HeightRange= %d\n", 
							linfo->calcdY, linfo->deltadY, linfo->calcHeightRange, (int)linfo->HeightRange);
	/* 3 line */ 
	fprintf(linfo->fptOut, "x= %d  y= %d    ddYmin= %f ddYmax %f\n", 
							(int)in->HeaderN.x, (int)in->HeaderN.y, ROIinfo->ddYmin, ROIinfo->ddYmax);
	/* 4 line */ 
	fprintf(linfo->fptOut, "Pixel");
	for(l=1; l<=linfo->maxdY; l++) {	
		fprintf(linfo->fptOut, "%15d",l);
	}
	fprintf(linfo->fptOut, "\n");
							
}
void
__lmrcImageAutoFilamentExtractFFTInfoMeridian(lmrcImageAutoFilamentExtractInfo* linfo,
								  			  lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	char FilenameInFFTINFO[100];
	char commandRM[200];
	mrcImage inFFT;
	int Height;
	int HeightRange;
	double data;
	mrcImageParaTypeReal X;

	for(HeightRange=0; HeightRange<=linfo->HeightRange; HeightRange+=2) {	
		Height = linfo->Height -HeightRange;
		sprintf (FilenameInFFTINFO, "%s.%d.proj.fft", ROIinfo->OutE, Height);

		DEBUGPRINT1("%s\n",FilenameInFFTINFO); 
		fprintf(linfo->fptOut, "%d", Height);

		mrcFileRead(&inFFT, FilenameInFFTINFO, "in FFTINFO", 0);
			for(X=linfo->dY; X<=linfo->maxdY*linfo->dY; X+=linfo->dY) {	
				mrcPixelDataGet(&inFFT, X, 0, 0, &data, mrcPixelMag, mrcPixelHowNearest);
				fprintf(linfo->fptOut, "%15f",data);
			}
		fprintf(linfo->fptOut, "\n");

		sprintf (commandRM, "rm -f %s\n", FilenameInFFTINFO);
		fprintf(stderr, commandRM);
		system (commandRM);
	}
}

void
__lmrcImageAutoFilamentExtractFFTInfoAll(lmrcImageAutoFilamentExtractInfo* linfo,
								  	     lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	char FilenameInFFTINFO[100];
	char commandRM[200];
	mrcImage inFFT;
	int Height;
	int HeightRange;
	double data;
	mrcImageParaTypeReal Y;

	for(HeightRange=0; HeightRange<=linfo->HeightRange; HeightRange+=2) {	
		Height = linfo->Height -HeightRange;
		sprintf (FilenameInFFTINFO, "%s.%d.fft.fil.proj", ROIinfo->OutE, Height);

		DEBUGPRINT1("%s\n",FilenameInFFTINFO); 
		fprintf(linfo->fptOut, "%d", Height);

		mrcFileRead(&inFFT, FilenameInFFTINFO, "in FFTINFO", 0);
			for(Y=linfo->dY; Y<=linfo->maxdY*linfo->dY; Y+=linfo->dY) {	
				mrcPixelDataGet(&inFFT, 0, -Y, 0, &data, mrcPixelMag, mrcPixelHowNearest);
				fprintf(linfo->fptOut, "%15f",data);
			}
		fprintf(linfo->fptOut, "\n");

		sprintf (commandRM, "rm -f %s\n", FilenameInFFTINFO);
		fprintf(stderr, commandRM);
		system (commandRM);
	}
}

void
__lmrcImageAutoFilamentFinalResult (lmrcImageAutoFilamentExtractInfo* linfo,
									lmrcImageAutoFilamentExtractROIInfo* ROIinfo, long mode)
{
	char commandFinalROI[200];
	char commandMagnificationChange[200];
	char commandHeaderChange[200];
	char FilenameInROI[100];
	char FilenameOutROI[100];
	char FilenameInMag[100];
	char FilenameOutMag[100];
	char FilenameInHead[100];
	char FilenameOutHead[100];
	int ROIy;

	DEBUGPRINT("############Final Result############\n");
	ROIy = ((int)(ROIinfo->ROIy/2))*2 -1 ;

	sprintf (FilenameInROI , "%s", ROIinfo->OutE);
	sprintf (FilenameOutROI, "%s.final", FilenameInROI);
	sprintf (commandFinalROI, "%s %s %s %s %s  %s %d %s", 
				"mrcImageROI", "-i", FilenameInROI, "-o", FilenameOutROI, 
				"-y", ROIy, "-m 2\n");
	fprintf(stderr, commandFinalROI);
	system (commandFinalROI);

	sprintf (FilenameInMag , "%s", FilenameOutROI);
	sprintf (FilenameOutMag, "%s.mag", ROIinfo->OutF);
	sprintf (commandMagnificationChange, "%s %s %s %s %s  %s %d %s %f %s %d %s", 
				"mrcImageROI", "-i", FilenameInMag, "-o", FilenameOutMag, 
				"-truePitch", (int)linfo->truePitch, "-Ly", linfo->PixelSize, "-dY", (int)linfo->dY, "-m 2\n"); 
	fprintf(stderr, commandMagnificationChange);
	system (commandMagnificationChange);

	sprintf (FilenameInHead , "%s", FilenameOutMag);
	sprintf (FilenameOutHead, "%s", ROIinfo->OutF);
	sprintf (commandHeaderChange, "%s %s %s %s %s  %s %f %s %f \n", 
				"mrcImageHeaderChange", "-i", FilenameInHead, "-o", FilenameOutHead, 
				"-x", linfo->PixelSize, "-y", linfo->PixelSize); 
	fprintf(stderr, commandHeaderChange);
	system (commandHeaderChange);
}
