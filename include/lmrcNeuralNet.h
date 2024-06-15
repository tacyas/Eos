#ifndef LMRCNEURALNET_H
#define LMRCNEURALNET_H

#include "./NeuralNet.h"
#include "mrcImage.h"

double lmrcImageNeuralNetParticleLearning(
	int pattern,
	double*** weight,
	mrcImage* in,
	NeuralNetInfo* linfo,
	int mode);

#endif
