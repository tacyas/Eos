#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG  
#include "../inc/config.h"
#include "pdbFile.h"
#include "eosString.h"
#include "genUtil.h"
#ifdef CUDA
#include "eosCuda.h"
#endif

int
main(int argc, char* argv[])
{
    pdbTransInfo info;
    pdbFile pdb;
    
    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

#ifdef CUDA
	if(info.flagcudaDeviceID) {
		eosCudaInit(info.cudaDeviceID);
	}
#endif

    pdbFileRead(info.fptinFile, &pdb);

	DEBUGPRINT("MatrixArraySet\n");

	if(info.flagmatFile) {
		Matrix3D Matrix;

    	pdbMatrixFileRead(info.fptmatFile, Matrix);
		DEBUGPRINT3("Maatrix: %f %f %f \n", Matrix[0][0], Matrix[0][1], Matrix[0][2]);
    	pdbTrans(&pdb, Matrix);
	}
	if(info.flagRotMode) {
		pdbRotationFollowingEulerAngle(&pdb, info.RotMode, info.Rot1*RADIAN, info.Rot2*RADIAN, info.Rot3*RADIAN);
	}

    pdbFileWrite(info.fptoutFile, &pdb);
	return 0;
}

void
additionalUsage()
{
	pdbMatrixFileFormat(stderr);
	fprintf(stderr, "--- Attention ---\n");
	fprintf(stderr, "If both options of -M and -EA are set, \n");
	fprintf(stderr, "    first, translation and rotation by -M will be performed \n");
	fprintf(stderr, "    then,  rotation by -EA will be done.\n");
}

