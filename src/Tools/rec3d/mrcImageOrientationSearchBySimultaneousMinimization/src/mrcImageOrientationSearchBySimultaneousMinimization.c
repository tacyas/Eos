/*
# mrcImageOrientationSearchBySimultaneousMinimization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageOrientationSearchBySimultaneousMinimization
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <time.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "eosString.h"
#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"
#include "lmrcImageSinogramFFT.h"

/*
typedef enum lmrcImageOrientationSearchBySimultaneousMinimizationMode {
	a=0,
	b=1
} lmrcImageOrientationSearchBySimultaneousMinimizationMode;
*/

void
lmrcImageOrientationSearchBySimultaneousMinimization(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode);


void
__ResultFileWrite(char* filename, lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode);

void
__LogFileWrite(FILE* fptLog, lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int original, int n, int count, double Lmin, double differential, int mode);

void
__RandomChoiceAboutAllImages(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int* randomNn, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageOrientationSearchBySimultaneousMinimizationInfo  info;
	lmrcImageOrientationSearchBySimultaneousMinimizationInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.filenum = info.flagIn;

	linfo.angle = MemoryAllocate(EulerAngle, linfo.filenum, "in main");
	for(i=0; i<linfo.filenum; i++){
		linfo.angle[i].filename = MemoryAllocate(char, WORDLEN, "in main");
		strcpy(linfo.angle[i].filename, info.In[i]);
	}
	linfo.dtheta            = info.dtheta*RADIAN;
	linfo.dpsi              = info.dpsi*RADIAN;
	linfo.initialrandomdata = info.ird; 
	linfo.MaxCount          = (int)info.MC;
	linfo.mode              = (int)info.mode;
	linfo.modeinitialdata   = (int)info.mid;
	linfo.ModeStartPoint    = (int)info.msp;
	linfo.ModeAngularArea   = (int)info.maa;
	linfo.ModeL             = (int)info.modeL;
	linfo.ModeThresholdAngular = (int)info.modeTA; 
	linfo.ModeFix           = (int)info.modeF;
	
	linfo.FileNameHeader = MemoryAllocate(char, WORDLEN, "in main");
	strcpy(linfo.FileNameHeader, info.FileNameHeader);

	linfo.OutFileName = MemoryAllocate(char, WORDLEN, "in main");
	strcpy(linfo.OutFileName, info.Out);

	switch(info.ms){
		case 0 : 
			srand((unsigned)time(NULL));
		break;
		case 1 : 
			srand(linfo.initialrandomdata);
		break;
	}	

	if(linfo.modeinitialdata == 1){
		lInitialDataFileRead(&linfo, info.fptInInitial, 0);
	}

	lmrcImageOrientationSearchBySimultaneousMinimization(&linfo, 0);

	__ResultFileWrite(info.Out, &linfo, 0);
	
	DEBUGPRINT("Program End\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeSelection -----\n");
	fprintf(stderr, "-ms : 0 : random\n");
	fprintf(stderr, "    : 1 : myself (-ird)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Mode --------------\n");
	fprintf(stderr, "-m : 0 : input data --> sinogram\n");
	fprintf(stderr, "   : 1 :            --> sinogramFT\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Angle -------------\n");
	fprintf(stderr, "-dt    : DEGREE\n");
	fprintf(stderr, "-dp    : DEGREE\n");
	fprintf(stderr, "-pdt   : DEGREE\n");
	fprintf(stderr, "-pdp   : DEGREE\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeOfInitialData -------------\n");
	fprintf(stderr, "-mid : 0 : There is not initial data\n");
	fprintf(stderr, "       1 : There is     initial data (-iid)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeOfLcalculation -------------\n");
	fprintf(stderr, "-mL : 0 : differential of length\n");
	fprintf(stderr, "      1 : differential of phase\n");
	fprintf(stderr, "      2 : addition to derivation1D (multiply)\n");
	fprintf(stderr, "      3 : addition to derivation1D (difference)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeOfThresholdAngularWeight -------------\n");
	fprintf(stderr, "-mTA : 0 : 1.0e-4\n");
	fprintf(stderr, "       1 : 1 degree\n");
	fprintf(stderr, "       2 : dpsi\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeOfStartPoint -------------\n");
	fprintf(stderr, "-msp : 0 : origin\n");
	fprintf(stderr, "       1 : initial data (-iid)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeOfAngularArea -------------\n");
	fprintf(stderr, "-maa : 0 : all area\n");
	fprintf(stderr, "       1 : aroud previous delta (-pdt -pdp)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeOfCalculationArea -------------\n");
	fprintf(stderr, "-mca : 0 : all area\n");
	fprintf(stderr, "       1 : cut under -tca(1/angstrom)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- ModeOfFix -------------\n");
	fprintf(stderr, "-mf : 0 : don't fix one plane\n");
	fprintf(stderr, "      1 :       fix one plane (first file is fixed)\n");
	fprintf(stderr, "\n");
}

void
lmrcImageOrientationSearchBySimultaneousMinimization(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode)
{
	int                 i, j, n, l, J, count, N;
	int                 CommonLineNum, ll;
	int*                randomNn;
	PlaneRotationAngle* planerotationAngle;
	double              random;
	double              L, Lmin;
	double              LminSum;
	CommonLineData*     commonlinedata;
	CommonLineData*     Workcommonlinedata;
	CommonLineData*     commonlinedataWithPlaneRotation;
	float               phiMin, thetaMin, psiMin;
	float               RefAngle, OtherAngle;
	float               differential;
	lCommonLineCalculationInfo CommonLineInfo;
	mrcImage            refOneLineFT;
	mrcImage            otherOneLineFT;
	mrcImage            refOneLineSino;
	mrcImage            otherOneLineSino;
	char*               filenameR;
	char*               filenameLog;
	FILE*               fptLog;
	int                 PlaneRotationNum;
	int*                PlaneRotationFileNum;
	int                 flag;
	double              delU;
	mrcImage*           InputSinoImages;
	mrcImage*           InputFTImages;

	switch(linfo->mode){
		case 0 :
			InputSinoImages = MemoryAllocate(mrcImage, linfo->filenum, "in lmrcImageOrientationsearchBySimultaneousMinimization");
			for(i=0; i<linfo->filenum; i++){
				mrcFileRead(&InputSinoImages[i], linfo->angle[i].filename, "Read InputSinoImages", 0);
			}
			switch(linfo->ModeL){
				case 2 :
				case 3 :
				break;
				default :
					InputFTImages   = MemoryAllocate(mrcImage, linfo->filenum, "in lmrcImageOrientationsearchBySimultaneousMinimization");
					for(i=0; i<linfo->filenum; i++){
						lmrcImageSinogramFFT(&InputFTImages[i], &InputSinoImages[i], 0);
					}
					delU = 1/InputFTImages[0].HeaderLength.x/InputFTImages[0].HeaderN.x;
				break;
			}
		break;
		case 1 :
			switch(linfo->ModeL){
				case 2 :
				case 3 :
					fprintf(stderr,"This mode do not support ! : -mL=%d \n", linfo->ModeL);
					fprintf(stderr,"You must change -m to 0\n");
					exit(1);
				break;
			}
			InputFTImages = MemoryAllocate(mrcImage, linfo->filenum, "in lmrcImageOrientationsearchBySimultaneousMinimization");
			for(i=0; i<linfo->filenum; i++){
				mrcFileRead(&InputFTImages[i], linfo->angle[i].filename, "Read InputFTImages", 0);
			}
			delU = 1/InputFTImages[0].HeaderLength.x/InputFTImages[0].HeaderN.x;
		break;
	}

	filenameR = MemoryAllocate(char, WORDLEN, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	filenameLog = MemoryAllocate(char, WORDLEN, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	sprintf(filenameLog, "%s.Log", linfo->FileNameHeader);

	J = lJcalculation(linfo, 0);
	planerotationAngle = MemoryAllocate(PlaneRotationAngle, J, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	lPlaneRotationAngleSet(linfo, planerotationAngle, 0);

	switch(linfo->ModeFix){
		case 0 :
			switch(linfo->modeinitialdata){
				case 0 :
					for(i=0; i<linfo->filenum; i++){
						random = (double)rand()/RAND_MAX*2*M_PI;
						linfo->angle[i].psi   = random;
						random = (double)rand()/RAND_MAX*M_PI;
						linfo->angle[i].theta = random;
						random = (double)rand()/RAND_MAX*2*M_PI;
						linfo->angle[i].phi   = random;
					}
					sprintf(filenameR, "%s-initial.result", linfo->FileNameHeader);
					__ResultFileWrite(filenameR, linfo, 0);
				break;
				case 1 :
					fprintf(stdout, "Already input initial data !!\n");
				break;
			}
		break;
		case 1 :
			switch(linfo->modeinitialdata){
				case 0 :
					linfo->angle[0].psi   = 0.0;
					linfo->angle[0].theta = 0.0;
					linfo->angle[0].phi   = 0.0;
					for(i=1; i<linfo->filenum; i++){
						random = (double)rand()/RAND_MAX*2*M_PI;
						linfo->angle[i].psi   = random;
						random = (double)rand()/RAND_MAX*M_PI;
						linfo->angle[i].theta = random;
						random = (double)rand()/RAND_MAX*2*M_PI;
						linfo->angle[i].phi   = random;
					}
					sprintf(filenameR, "%s-initial.result", linfo->FileNameHeader);
					__ResultFileWrite(filenameR, linfo, 0);
				break;
				case 1 :
					if(fabsf(linfo->angle[0].phi) > 1e-5 && fabsf(linfo->angle[0].theta) > 1e-5 && fabsf(linfo->angle[0].psi) > 1e-5){
						fprintf(stderr, "angle of first file miss !! : phi=%f theta=%f psi=%f [radian]\n", 
								linfo->angle[0].phi, linfo->angle[0].theta, linfo->angle[0].psi);
						exit(1);
					}
					fprintf(stdout, "Already input initial data !!\n");
				break;
			}
		break;
	}

	randomNn = MemoryAllocate(int, linfo->filenum, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	Workcommonlinedata = MemoryAllocate(CommonLineData, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	
	CommonLineInfo.I1RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.I2RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	for(i=0; i<linfo->filenum-1; i++){
		CommonLineInfo.I1RotationalMode[i] = MemoryAllocate(char, 5, "in lmrcImageOrientationSearchBySimultaneousMinimization");
		CommonLineInfo.I2RotationalMode[i] = MemoryAllocate(char, 5, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	}
	CommonLineInfo.I1Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.I1Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.I1Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.I2Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.I2Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.I2Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.CLAngleOnI1AgainstI2  = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.CLAngleOnI2AgainstI1  = MemoryAllocate(float, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	CommonLineInfo.flag     = MemoryAllocate(int  , linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
	
	if((fptLog = fopen(filenameLog, "a")) == NULL){
		fprintf(stderr, "file not open\n");
		exit(1);
	}
	count = 0;
	do{
		differential = 0;
		LminSum      = 0; 
		__RandomChoiceAboutAllImages(linfo, randomNn, 0);
		for(n=0; n<linfo->filenum; n++){
		if(0 == randomNn[n] && linfo->ModeFix == 1){
			/*first file is skipped */
		} else{
			CommonLineNum    = lAllCommonLineCalculation(linfo, &CommonLineInfo, randomNn[n], planerotationAngle, Workcommonlinedata, 0, 1);
			commonlinedata   = MemoryAllocate(CommonLineData, CommonLineNum, "in lmrcImageOrientationSearchBySimultaneousMinimization");
			PlaneRotationNum = lCommonLinesDataSet(linfo, Workcommonlinedata, commonlinedata, 0);
			if(PlaneRotationNum == 0){
				lAngularWeightCalculation(linfo, commonlinedata, CommonLineNum, 0);
				L   = 0;
				for(l=0; l<linfo->filenum-1; l++){
					RefAngle   = commonlinedata[l].angleRef   + linfo->angle[randomNn[n]].psi;
					OtherAngle = commonlinedata[l].angleOther + linfo->angle[commonlinedata[l].num].psi;
					RefAngle   = fmod(RefAngle, 2*M_PI);
					OtherAngle = fmod(OtherAngle, 2*M_PI);
					//lmrcImageOneLineFTCreate(linfo, &InputFTImages[randomNn[n]], &InputFTImages[commonlinedata[l].num], &refOneLineFT, &otherOneLineFT, RefAngle, OtherAngle, 0);
					
					switch(linfo->ModeL){
						case 0 :
						case 1 :
							lmrcImageFTOneLineGet(&refOneLineFT,   &InputFTImages[randomNn[n]],           RefAngle,   0);
							lmrcImageFTOneLineGet(&otherOneLineFT, &InputFTImages[commonlinedata[l].num], OtherAngle, 0);
						break;
						case 2 :
						case 3 :
							lmrcImageOneLineGet(&refOneLineSino,   &InputSinoImages[randomNn[n]],           RefAngle,   0);
							lmrcImageOneLineGet(&otherOneLineSino, &InputSinoImages[commonlinedata[l].num], OtherAngle, 0);
						break;
					}

					L += lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, &refOneLineSino, &otherOneLineSino, commonlinedata, delU, l, 0);

					switch(linfo->ModeL){
						case 0 :
						case 1 :
							mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
			        		mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
						break;
						case 2 :
						case 3 :
							mrcImageFree(&refOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
			        		mrcImageFree(&otherOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
						break;
					}
				}
			} else{
				PlaneRotationFileNum = MemoryAllocate(int, PlaneRotationNum, "in lmrcImageOrientationSearchBySimultaneousMinimization");
				l = 0;
				for(i=0; i<linfo->filenum-1; i++){
					if(Workcommonlinedata[i].flag == 1){
						PlaneRotationFileNum[l] = Workcommonlinedata[i].num;
						l++;
					}
				}
				switch(linfo->ModeL){
					case 0 :
					case 1 :
						commonlinedataWithPlaneRotation = MemoryAllocate(CommonLineData, CommonLineNum+(PlaneRotationNum*InputFTImages[0].HeaderN.y), 
					             		                                "in lmrcImageOrientationSearchBySimultaneousMinimizaton");
						lCommonLineDataSetInPlaneRotation(linfo, commonlinedata, commonlinedataWithPlaneRotation, PlaneRotationNum, 
				                       		            CommonLineNum, randomNn[n], PlaneRotationFileNum, &InputFTImages[randomNn[n]], 1);
						lAngularWeightCalculation(linfo, commonlinedataWithPlaneRotation, CommonLineNum+(PlaneRotationNum*InputFTImages[0].HeaderN.y), 0);
						N = PlaneRotationNum*InputFTImages[0].HeaderN.y;
					break;
					case 2 :
					case 3 :
						commonlinedataWithPlaneRotation = MemoryAllocate(CommonLineData, CommonLineNum+(PlaneRotationNum*InputSinoImages[0].HeaderN.y), 
					             		                                "in lmrcImageOrientationSearchBySimultaneousMinimizaton");
						lCommonLineDataSetInPlaneRotation(linfo, commonlinedata, commonlinedataWithPlaneRotation, PlaneRotationNum, 
				                       		            CommonLineNum, randomNn[n], PlaneRotationFileNum, &InputSinoImages[randomNn[n]], 1);
						lAngularWeightCalculation(linfo, commonlinedataWithPlaneRotation, CommonLineNum+(PlaneRotationNum*InputSinoImages[0].HeaderN.y), 0);
					break;
				}
				L = 0;
				for(l=0; l<CommonLineNum+N; l++){
					flag = 0;
					for(ll=0; ll<PlaneRotationNum; ll++){
						if(PlaneRotationFileNum[ll] == commonlinedataWithPlaneRotation[l].num){
							switch(linfo->ModeL){
								case 0 :
								case 1 :
									lmrcImageFTOneLineGet(&refOneLineFT,   &InputFTImages[randomNn[n]],                    commonlinedataWithPlaneRotation[l].angleRef,   0);
                            		lmrcImageFTOneLineGet(&otherOneLineFT, &InputFTImages[PlaneRotationFileNum[ll]], commonlinedataWithPlaneRotation[l].angleOther, 0);
								break;
								case 2 :
								case 3 :
									lmrcImageFTOneLineGet(&refOneLineSino,   &InputSinoImages[randomNn[n]],                    commonlinedataWithPlaneRotation[l].angleRef,   0);
                            		lmrcImageFTOneLineGet(&otherOneLineSino, &InputSinoImages[PlaneRotationFileNum[ll]], commonlinedataWithPlaneRotation[l].angleOther, 0);
								break;
							}
                            flag = 1;
                        }
                    }
                    if(flag == 0){
                        //lmrcImageOneLineFTCreate(linfo, &InputFTImages[randomNn[n]], &InputFTImages[commonlinedataWithPlaneRotation[l].num], &refOneLineFT, &otherOneLineFT,
						//						 commonlinedataWithPlaneRotation[l].angleRef, commonlinedataWithPlaneRotation[l].angleOther, 0);

						switch(linfo->ModeL){
							case 0 :
							case 1 :
								lmrcImageFTOneLineGet(&refOneLineFT,   &InputFTImages[randomNn[n]],                            commonlinedataWithPlaneRotation[l].angleRef,   0);
								lmrcImageFTOneLineGet(&otherOneLineFT, &InputFTImages[commonlinedataWithPlaneRotation[l].num], commonlinedataWithPlaneRotation[l].angleOther, 0);
							break;
							case 2 :
							case 3 :
								lmrcImageOneLineGet(&refOneLineSino,   &InputSinoImages[randomNn[n]],                            
													  commonlinedataWithPlaneRotation[l].angleRef,   0);
								lmrcImageOneLineGet(&otherOneLineSino, &InputSinoImages[commonlinedataWithPlaneRotation[l].num], 
													  commonlinedataWithPlaneRotation[l].angleOther, 0);
							break;
						}

                    }
					L += lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, &refOneLineSino, &otherOneLineSino, commonlinedataWithPlaneRotation, delU, l, 0);
					switch(linfo->ModeL){
						case 0 :
						case 1 :
							mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
			        		mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
						break;
						case 2 :
						case 3 :
							mrcImageFree(&refOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
			        		mrcImageFree(&otherOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
						break;
					}
				
				}
				free(commonlinedataWithPlaneRotation);
				free(PlaneRotationFileNum);
			}
			free(commonlinedata);
			Lmin     = L;
			psiMin   = linfo->angle[randomNn[n]].psi;
			thetaMin = linfo->angle[randomNn[n]].theta;
			phiMin   = linfo->angle[randomNn[n]].phi;
			__LogFileWrite(fptLog, linfo, randomNn[n], n, count, Lmin, 0, 0);

			/* all L calculation */
			for(j=0; j<J; j++){
				CommonLineNum = lAllCommonLineCalculation(linfo, &CommonLineInfo, randomNn[n], planerotationAngle, Workcommonlinedata, j, 0);
				commonlinedata = MemoryAllocate(CommonLineData, CommonLineNum, "in lmrcImageOrientationSearchBySimultaneousMinimization");
				PlaneRotationNum = lCommonLinesDataSet(linfo, Workcommonlinedata, commonlinedata, 0);
				fprintf(stderr, "count=%d n=%d j=%d >>>>>>> CommonLineNum = %d PlaneRotationNum = %d\n", count, n, j, CommonLineNum, PlaneRotationNum);
				if(PlaneRotationNum == 0){
					lAngularWeightCalculation(linfo, commonlinedata, CommonLineNum, 0);
					for(i=(int)(PSIMIN/linfo->dpsi + 0.5); i*linfo->dpsi<PSIMAX; i++){
						L   = 0;
						for(l=0; l<linfo->filenum-1; l++){
							RefAngle   = commonlinedata[l].angleRef   + (i*linfo->dpsi);
							OtherAngle = commonlinedata[l].angleOther + linfo->angle[commonlinedata[l].num].psi;
							RefAngle   = fmod(RefAngle, 2*M_PI);
							OtherAngle = fmod(OtherAngle, 2*M_PI);
							//lmrcImageOneLineFTCreate(linfo, &InputFTImages[randomNn[n]], &InputFTImages[commonlinedata[l].num], 
							// 						 &refOneLineFT, &otherOneLineFT, RefAngle, OtherAngle, 0);

							switch(linfo->ModeL){
								case 0 :
								case 1 :
									lmrcImageFTOneLineGet(&refOneLineFT,   &InputFTImages[randomNn[n]],           RefAngle,   0);
									lmrcImageFTOneLineGet(&otherOneLineFT, &InputFTImages[commonlinedata[l].num], OtherAngle, 0);
								break;
								case 2 :
								case 3 :
									lmrcImageOneLineGet(&refOneLineSino,   &InputSinoImages[randomNn[n]],              RefAngle, 0);
									lmrcImageOneLineGet(&otherOneLineSino, &InputSinoImages[commonlinedata[l].num], OtherAngle, 0);
								break;
							}
							
							L += lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, &refOneLineSino, &otherOneLineSino, commonlinedata, delU, l, 0);

							switch(linfo->ModeL){
								case 0 :
								case 1 :
									mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
			       			 		mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
								break;
								case 2 :
								case 3 :
									mrcImageFree(&refOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
					        		mrcImageFree(&otherOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
								break;
							}
						}
						DEBUGPRINT4("Lmin = %f : (%f, %f, %f)\n", L, planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE);
						if(L < Lmin){
							psiMin   = i*linfo->dpsi;
							thetaMin = planerotationAngle[j].theta;
							phiMin   = planerotationAngle[j].phi;
							Lmin     = L;
						}
					}
				}
				else{
					PlaneRotationFileNum = MemoryAllocate(int, PlaneRotationNum, "in lmrcImageOrientationSearchBySimultaneousMinimization");
					l = 0;
					for(i=0; i<linfo->filenum-1; i++){
						if(Workcommonlinedata[i].flag == 1){
							PlaneRotationFileNum[l] = Workcommonlinedata[i].num;
							l++;
						}
					}
					switch(linfo->ModeL){
						case 0 :
						case 1 :
							N = PlaneRotationNum*InputFTImages[0].HeaderN.y;
						break;
						case 2 :
						case 3 :
							N = PlaneRotationNum*InputSinoImages[0].HeaderN.y;
						break;
					}
					commonlinedataWithPlaneRotation = MemoryAllocate(CommonLineData, CommonLineNum+N, "in lmrcImageOrientationSearchBySimultaneousMinimizaton");

					for(i=(int)(PSIMIN/linfo->dpsi + 0.5); i*linfo->dpsi<PSIMAX; i++){
						switch(linfo->ModeL){
							case 0 :
							case 1 :
								lCommonLineDataSetInPlaneRotation(linfo, commonlinedata, commonlinedataWithPlaneRotation, PlaneRotationNum, 
						       		                              CommonLineNum, i, PlaneRotationFileNum, &InputFTImages[randomNn[n]], 0);
							break;
							case 2 :
							case 3 :
								lCommonLineDataSetInPlaneRotation(linfo, commonlinedata, commonlinedataWithPlaneRotation, PlaneRotationNum, 
						       		                              CommonLineNum, i, PlaneRotationFileNum, &InputSinoImages[randomNn[n]], 0);
							break;
						}
						lAngularWeightCalculation(linfo, commonlinedataWithPlaneRotation, CommonLineNum+N, 0);
						L = 0;
						for(l=0; l<CommonLineNum+N; l++){
							//lmrcImageOneLineFTCreate(linfo, &InputFTImages[randomNn[n]], &InputFTImages[commonlinedataWithPlaneRotation[l].num], &refOneLineFT, &otherOneLineFT,
							//						 commonlinedataWithPlaneRotation[l].angleRef, commonlinedataWithPlaneRotation[l].angleOther,0);

							switch(linfo->ModeL){
								case 0 :
								case 1 :
									lmrcImageFTOneLineGet(&refOneLineFT,   &InputFTImages[randomNn[n]],                            
														  commonlinedataWithPlaneRotation[l].angleRef,   0);
									lmrcImageFTOneLineGet(&otherOneLineFT, &InputFTImages[commonlinedataWithPlaneRotation[l].num], 
														  commonlinedataWithPlaneRotation[l].angleOther, 0);
								break;
								case 2 :
								case 3 :
									lmrcImageOneLineGet(&refOneLineSino,   &InputSinoImages[randomNn[n]],                            
														commonlinedataWithPlaneRotation[l].angleRef,   0);
									lmrcImageOneLineGet(&otherOneLineSino, &InputSinoImages[commonlinedataWithPlaneRotation[l].num], 
														commonlinedataWithPlaneRotation[l].angleOther, 0);
								break;
							}

							L += lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, &refOneLineSino, &otherOneLineSino, commonlinedataWithPlaneRotation, delU, l, 0);

							switch(linfo->ModeL){
								case 0 :
								case 1 :
									mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
			       			 		mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
								break;
								case 2 :
								case 3 :
									mrcImageFree(&refOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
					        		mrcImageFree(&otherOneLineSino, "in lmrcImageOrientationSearchBySimultaneousMinimization");
								break;
							}
						}
						DEBUGPRINT4("Lmin = %f : (%f, %f, %f)\n", L, planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE);
						if(L < Lmin){
							psiMin   = i*linfo->dpsi;
							thetaMin = planerotationAngle[j].theta;
							phiMin   = planerotationAngle[j].phi;
							Lmin     = L;
						}
					}
					free(commonlinedataWithPlaneRotation);
					free(PlaneRotationFileNum);
				}
				free(commonlinedata);
			}
			LminSum += Lmin;
			differential += SQR(MIN(fabs(psiMin   - linfo->angle[randomNn[n]].psi),   2*M_PI - fabs(psiMin   - linfo->angle[randomNn[n]].psi)))
			               +SQR(MIN(fabs(thetaMin - linfo->angle[randomNn[n]].theta),   M_PI - fabs(thetaMin - linfo->angle[randomNn[n]].theta)))
			               +SQR(MIN(fabs(phiMin   - linfo->angle[randomNn[n]].phi),   2*M_PI - fabs(phiMin   - linfo->angle[randomNn[n]].phi)));

			linfo->angle[randomNn[n]].psi   = psiMin;
			linfo->angle[randomNn[n]].theta = thetaMin;
			linfo->angle[randomNn[n]].phi   = phiMin;
			
			__LogFileWrite(fptLog, linfo, randomNn[n], n, count, Lmin, differential, 1);
		}
		}
		fprintf(fptLog, "differential: %f\n", differential);
		LminSum /= linfo->filenum;
		fprintf(fptLog, "LminAve = %f\n\n", LminSum);
		sprintf(filenameR,"%s-%d.result",linfo->FileNameHeader, count);
		__ResultFileWrite(filenameR, linfo, 0);
		count++;
	}while(1e-6 < differential && count < linfo->MaxCount);
	fprintf(fptLog, "%s %f", linfo->OutFileName, LminSum);
	fclose(fptLog);
}

void
__ResultFileWrite(char* filename, lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode)
{
	FILE* fpt;
	int   i;

	if((fpt = fopen(filename, "w")) == NULL){
		fprintf(stderr, "file not open\n");
		exit(1);
	}

	for(i=0; i<linfo->filenum; i++){
		fprintf(fpt, "%s ZONS %4.1f %4.1f %4.1f\n", linfo->angle[i].filename, linfo->angle[i].phi*DEGREE, 
		                                      linfo->angle[i].theta*DEGREE, linfo->angle[i].psi*DEGREE);
	}
	fclose(fpt);
}

void
__LogFileWrite(FILE* fptLog, lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int original, int n, int count, double Lmin, double differential, int mode)
{
	switch(mode){
		case 0 :{
			fprintf(fptLog, "count: %2d n: %2d original: %2d InitialLmin: %4.3f ", count, n, original, Lmin);
			break;
		}
		case 1 :{
			fprintf(fptLog, "FinalLmin: %4.3f \n", Lmin);
			break;
		}
	}
	fflush(fptLog);
}

void
__RandomChoiceAboutAllImages(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int* randomNn, int mode)
{
	int i, j, counter, flag;
	int random;

	for(i=0; i<linfo->filenum; i++){
		randomNn[i] = 0;
	}
	
	for(i=0; i<linfo->filenum; i++){
		random = (int)((double)rand()/RAND_MAX*(linfo->filenum-i)); 
		j = 0;
		counter = 0;
		flag = 0;
		if(random == 0){
			while(flag != 1){
				if(randomNn[j] == 0){
					flag = 1;
				}
				else{
					j++;
				}
			}
			j++;
		}
		else{
			while(flag != 1){
				if(randomNn[j] == 0){
					if(counter == random){
						flag = 1;
					}
					else{
						counter++;
					}
				}
				j++;
			}
		}
		randomNn[j-1] = i+1;
	}
	for(i=0; i<linfo->filenum; i++){
		randomNn[i] -= 1;
	}
}

