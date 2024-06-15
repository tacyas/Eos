#include "Memory.h"
#include "./NeuralNet.h"
#include "./lmrcNeuralNet.h"

double
lmrcImageNeuralNetParticleLearning(
	int pattern,
	double*** weight,
	mrcImage* in,
	NeuralNetInfo* linfo,
	int mode)
{

	int       i,j;
	double**  cell;
	int       counter;
	int       index;
	float     x,y,z;
	double    error;

	cell = (double**)memoryAllocate(sizeof(double*)*(linfo->numOfLayer), "in  lmrcImageNeuralNetParticleLearning");
	for(i=0; i<linfo->numOfLayer; i++) {	
		cell[i] = (double*)memoryAllocate(sizeof(double)*(linfo->numOfCellOfLayer[i]+2), "in lmrcImageNeuralNetParticleLearning");
	}

	/*
		cell[l][n] : the value of the n'th cell in the l'th layer 	
			
			l		..... n .......
						  |
						cell[l][n]
	*/

	// Get A Sample Image
	index = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in, x, y, z, &cell[0][index], mrcPixelRePart, mrcPixelHowNearest);
		cell[0][index] = neuralNetSigmoidalFunction((cell[0][index] - in->HeaderAMean)/(in->HeaderAMax - in->HeaderAMin)*4);
		DEBUGPRINT4("x=%lf , y=%lf , cell[0][%d]=%f\n", x, y, index, cell[0][index]);
		index++;
	}
	}
	}
	cell[0][linfo->numOfCellOfLayer[0]]   = linfo->bias[0];
	cell[0][linfo->numOfCellOfLayer[0]+1] = in->HeaderAMean;
    linfo->numOfCellOfLayer[0] = index+1;

	counter = 0;
	if(pattern==1) {
		DEBUGPRINT("positive start\n");			
	} else if(pattern==0) {
		DEBUGPRINT("negative start\n");			
	}	

	neuralNetOutputLayerCalculation(cell, weight, linfo, mode); 	
    neuralNetBackPropagation(cell, weight, pattern, linfo, mode);
	neuralNetOutputLayerCalculation(cell, weight, linfo, mode); 	
	
	// Calc. Error 
	error = 0;
    for(j=0 ; j<linfo->numOfCellOfLayer[linfo->numOfLayer-1] ; j++) {
		error += SQR(pattern - cell[linfo->numOfLayer-1][j]);
	}
	fprintf(stderr, "error=%f\n",error);

	for(i=0; i<linfo->numOfLayer; i++) {	
		free(cell[i]);
	}
	free(cell);
	return error;
}

