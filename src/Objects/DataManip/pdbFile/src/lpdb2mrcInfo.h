#ifndef PDB_2_MRC_INFO
#define PDB_2_MRC_INFO

/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lpdb2mrcInfo.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lpdb2mrcInfo.h 
#%Z% Attention
#%Z%
*/

/* struct begin */

typedef enum lpdb2mrcDensityMode {
	lpdb2mrcDensityModeSameGaussian=0,
	lpdb2mrcDensityModeWentzelAtomModel=1
} lpdb2mrcDensityMode;


typedef struct lpdb2mrcInfo {
	pdbFileParaTypeReal sx;
	pdbFileParaTypeReal sy;
	pdbFileParaTypeReal sz;
	pdbFileParaTypeReal dx;
	pdbFileParaTypeReal dy;
	pdbFileParaTypeReal dz;
	pdbFileParaTypeInteger nx;
	pdbFileParaTypeInteger ny;
	pdbFileParaTypeInteger nz;
	pdbFileParaTypeReal Weight;
	pdbFileParaTypeReal Sigma;

	pdbFileParaTypeInteger flagNegativeStain;
	pdbFileParaTypeReal    stainThickness;

	lpdb2mrcDensityMode DensityMode;
} lpdb2mrcInfo;

typedef lpdb2mrcInfo lpdb2mrc2dInfo;
typedef lpdb2mrcInfo lpdb2mrc3dInfo;

/* struct end */

/* prototype begin */
/*
	If mode := 0
		Everytime, initialize.
			:= 1
		Once initialize and not initialize
*/
extern void lpdb2mrc2d(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc2dInfo* info, char axis, long mode);
extern void lpdb2mrc3d(mrcImage* mrc, pdbFile* pdb,  lpdb2mrc2dInfo* info, long mode);
extern void lpdb2mrc3dUsage(FILE* fpt);
/* prototype end */

#endif /* PDB_FILE_H */
