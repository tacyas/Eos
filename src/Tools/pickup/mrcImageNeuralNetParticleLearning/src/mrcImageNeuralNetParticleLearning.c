/*
# mrcImageNeuralNetParticleLearning : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageNeuralNetParticleLearning
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

#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"
#include "eosString.h"

/*
#include "pickup.h"
*/

#include "NeuralNet.h"
#include "lmrcNeuralNet.h"

extern void ParticleLearningCycle(double*** weight , mrcImage* positive , mrcImage* negative , NeuralNetInfo* linfo , mrcImageNeuralNetParticleLearningInfo* info , int mode);
extern void OutputWeightImage(double*** weight , NeuralNetInfo* linfo , mrcImageNeuralNetParticleLearningInfo* info , int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageNeuralNetParticleLearningInfo info;
	NeuralNetInfo linfo;
	mrcImage*   weightImage;
	mrcImage*   positive;
	mrcImage* 	negative;
	double***   weight;
	int mode;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

  	// Information Set 		 	
	linfo.numOfLayer = info.flagOut + 1;		
	linfo.numOfCellOfLayer = (int*)memoryAllocate(sizeof(int)*linfo.numOfLayer, "in main");
	linfo.bias             = (int*)memoryAllocate(sizeof(int)*linfo.numOfLayer, "in main");
	fseek(info.fptOutList, 0L, SEEK_SET);
	for(i=1; i<linfo.numOfLayer; i++) {
		char s[1024];			
		fgets(s, 1023, info.fptOutList);
		linfo.numOfCellOfLayer[i] = stringGetNthIntegerData(s, 2, " ,\t");
		linfo.bias[i]             = stringGetNthIntegerData(s, 3, " ,\t");
	}
	linfo.numOfCellOfLayer[0] = 0;
	linfo.bias[0]             = info.Bias;
    linfo.numOfSeparation     = 3;

	//Get the memory of Learning Image
	positive = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInPositive, "in main for positive");
	for(i=0; i<info.flagInPositive; i++) {
		mrcFileRead(&positive[i], info.InPositive[i], "in main for positive", 0);
		if(0==linfo.numOfCellOfLayer[0]) {
			linfo.numOfCellOfLayer[0] = positive[i].PixelPerImage;
		} else if(linfo.numOfCellOfLayer[0] != positive[i].PixelPerImage){
			fprintf(stderr, "The size of image %d is different from image 0\n", i);  			
			exit(EXIT_FAILURE);
		}
	}
	
	negative = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInNegative, "in main for negative");
	for(i=0; i<info.flagInNegative; i++) {
		mrcFileRead(&negative[i], info.InNegative[i], "in main for negative", 0);
		if(linfo.numOfCellOfLayer[0] != negative[i].PixelPerImage){
			fprintf(stderr, "The size of image %d is different from image 0\n", i);  			
			exit(EXIT_FAILURE);
		}
	}
	//information set of Learning Image 
	linfo.numOfPositive = info.flagInPositive;
	linfo.numOfNegative = info.flagInNegative;
   	linfo.numOfCellOfLayer[0] = positive[0].HeaderN.x*positive[0].HeaderN.y;

	// main's caluclation
	neuralNetRandomToWeight(weight,&linfo);
	ParticleLearningCycle(weight,positive,negative,&linfo,&info,mode);
	OutputWeightImage(weight,&linfo,&info,mode);

	for(i=0; i<info.flagOut; i++) {
		mrcFileWrite(&weightImage[i], info.Out[i], "in main for weight", 0);
	}

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void
ParticleLearningCycle(double*** weight , mrcImage* positive , mrcImage* negative , NeuralNetInfo* linfo , mrcImageNeuralNetParticleLearningInfo* info , int mode)
{
	int    counter;
	int    k;
	double E;
	double error;


	//Learning Cycle	
	error = info->EPS*1e6;
	counter = 0;
    while(counter < info->MaxCounter &&  info->EPS < error) {
		error = 0;	
		linfo->Lambda              = info->Lambda;
		for(k=0;k<linfo->numOfPositive;k++) {
			E = lmrcImageNeuralNetParticleLearning(1, weight, &positive[k], linfo, mode);
			error += E;
		}

		linfo->Lambda              = -1.0*info->Lambda;
		for(k=0;k<linfo->numOfNegative;k++) {
			E = lmrcImageNeuralNetParticleLearning(0, weight, &negative[k], linfo, mode);
			error += E;
		}
		error = sqrt(error/(linfo->numOfPositive+linfo->numOfNegative));
		fprintf(stderr, "count: %4d error: %15.6f\n", counter, error);
		counter++;
	}
}	

void
OutputWeightImage(double*** weight , NeuralNetInfo* linfo , mrcImageNeuralNetParticleLearningInfo* info , int mode)
{
	mrcImage* weightImage;
	int i;
	int x,y;
	
	weightImage = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagOut, "in main for weight");
	for(i=0; i<linfo->numOfLayer-1; i++) {		
		weightImage[i].HeaderN.x = linfo->numOfCellOfLayer[i]; 
		weightImage[i].HeaderN.y = linfo->numOfCellOfLayer[i+1]; 
		weightImage[i].HeaderN.z = 1;
		weightImage[i].HeaderMode = mrcFloatImage;
		mrcInit(&weightImage[i], NULL);

		for(x=0; x<weightImage[i].HeaderN.x; x++) {
		for(y=0; y<weightImage[i].HeaderN.y; y++) {
			mrcPixelDataSet(&weightImage[i], x, y, 0, weight[i][x][y], mrcPixelRePart);
		}
		}
	}
}	
