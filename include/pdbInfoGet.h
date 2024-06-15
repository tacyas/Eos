/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbInfoGet.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbInfoGet.h 
#%Z% Attention
#%Z%
*/

#ifndef PDB_INFO_GET_H
#define PDB_INFO_GET_H

#include "pdbFile.h"

/* struct begin */ 
typedef enum pdbInfoCenterMode {
        pdbInfoCenterModeCa = 0,
        pdbInfoCenterModeAll = 1
} pdbInfoCenterMode;
        
typedef struct pdbInfoData {
	double cx;	
	double cy;	
	double cz;	

    pdbInfoCenterMode centermode;
  	double distance;	
	double distancex;	
	double distancey;	
	double distancez;	
} pdbInfoData;

/* struct end */

/* prototype begin */
extern void pdbInfoGet(pdbFile* pdb, pdbInfoData* info, long mode);
/* prototype end */


#endif /* PDB_INFO_GET_H */
