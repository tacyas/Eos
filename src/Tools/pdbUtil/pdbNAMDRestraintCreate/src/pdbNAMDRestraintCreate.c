/*
# pdbNAMDRestraintCreate : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pdbNAMDRestraintCreate
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
#include "genUtil.h"
#include "pdbFile.h"

typedef struct lpdbNAMDRestraintCreateInfo {
	double kf;
	char*  segmentName;

} lpdbNAMDRestraintCreateInfo;
/*
typedef enum lpdbNAMDRestraintCreateMode {
	a=0,
	b=1
} lpdbNAMDRestraintCreateMode;
*/

extern double __lpdbNAMDRestraintCADistanceCalc(pdbFile* in, pdbFile* ref);

extern void lpdbNAMDRestraintCreate(FILE* out, pdbFile* in, pdbFile* ref, lpdbNAMDRestraintCreateInfo linfo, int mode);

extern void lpdbNAMDRestraintForceCreate(pdbFile* out, pdbFile* in, pdbFile* ref, lpdbNAMDRestraintCreateInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	pdbNAMDRestraintCreateInfo info;
	lpdbNAMDRestraintCreateInfo linfo;
	pdbFile in;
	pdbFile ref;
	pdbFile out;
	double averageDistance;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.kf = info.Kf;
	linfo.segmentName = strdup(info.SegName);

	pdbFileRead(info.fptIn, &in);
	pdbFileRead(info.fptRef, &ref);
	out.top = NULL;

	if(info.flagAutoKf) {
		averageDistance = __lpdbNAMDRestraintCADistanceCalc(&in, &ref);
		if(0<averageDistance) {
			linfo.kf = info.AutoKf / averageDistance;
			DEBUGPRINT3("kf %f := AutoKf %f / distance %f\n", linfo.kf, info.AutoKf, averageDistance);
		} else {
			fprintf(stderr, "in is the same as ref. kf = linfo.kf\n");	
		}
	}
	if(info.flagOut) {
		lpdbNAMDRestraintCreate(info.fptOut, &in, &ref, linfo, 0);
	}
	if(info.flagOut2) {
		lpdbNAMDRestraintForceCreate(&out, &in, &ref, linfo, 0); 
		pdbFileWrite(info.fptOut2, &out);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-autokf is prior to -kf.\n");
}

double
__lpdbNAMDRestraintCADistanceCalc(pdbFile* in, pdbFile* ref)
{
	double averageDistance;
	int count;
	
	averageDistance = 0;
	count = 0;
	pdbFileTop(in);
	pdbFileTop(ref);

	while(!pdbFileEnd(in) && !pdbFileEnd(ref)) {
		if(!pdbFileIsCA(in)) {
			pdbFileNextCA(in);
		}
		if(!pdbFileIsCA(ref)) {
			pdbFileNextCA(ref);
		}
		if(in->PDB->ResidueSequenceNumber==ref->PDB->ResidueSequenceNumber) {
			averageDistance += 
				( SQR(in->PDB->Coord.x - ref->PDB->Coord.x)
		        + SQR(in->PDB->Coord.y - ref->PDB->Coord.y)
				+ SQR(in->PDB->Coord.z - ref->PDB->Coord.z) );
			count++;	
		} else {
			fprintf(stderr, "Two Files have Different residue number\n");
			exit(EXIT_FAILURE);
		}
		pdbFileNextCA(in);
		pdbFileNextCA(ref);
	}
	if(0<averageDistance) {
		averageDistance /= count;
	} else {
		fprintf(stderr, "in is the same as ref. \n");	
		averageDistance = 0;
	}
	return averageDistance;
}
void 
lpdbNAMDRestraintCreate(FILE* out, pdbFile* in, pdbFile* ref, lpdbNAMDRestraintCreateInfo linfo, int mode)
{
	double averageDistance;
	int count;
	
	fprintf(out, "urestraint {\n");
	pdbFileTop(in);
	pdbFileTop(ref);

	while(!pdbFileEnd(in) && !pdbFileEnd(ref)) {
		if(!pdbFileIsCA(in)) {
			pdbFileNextCA(in);
		}
		if(!pdbFileIsCA(ref)) {
			pdbFileNextCA(ref);
		}
		if(in->PDB->ResidueSequenceNumber==ref->PDB->ResidueSequenceNumber) {
			fprintf(out, "    posi (%s,%d,ca) kf=%g ref=(%g,%g,%g)\n", 
					linfo.segmentName, in->PDB->ResidueSequenceNumber,
					linfo.kf,
					ref->PDB->Coord.x, ref->PDB->Coord.y, ref->PDB->Coord.z);
		} else {
			fprintf(stderr, "Two Files have Different residue number\n");
			exit(EXIT_FAILURE);
		}
		pdbFileNextCA(in);
		pdbFileNextCA(ref);
	}

	fprintf(out, "}\n");
}

void 
lpdbNAMDRestraintForceCreate(pdbFile* out, pdbFile* in, pdbFile* ref, lpdbNAMDRestraintCreateInfo linfo, int mode)
{
	pdbFileCopyAll(out, in);
	pdbFileTop(in);
	pdbFileTop(ref);
	pdbFileTop(out);
	
	while(1) {
		if(!pdbFileIsAtom(in)) {
			pdbFileNextAtom(in);
		}
		if(!pdbFileIsAtom(ref)) {
			pdbFileNextAtom(ref);
		}
		if(!pdbFileIsAtom(out)) {
			pdbFileNextAtom(out);
		}
		if(in->PDB->ResidueSequenceNumber==ref->PDB->ResidueSequenceNumber) {
			if(pdbFileIsCA(in) && pdbFileIsCA(ref)) {
				out->PDB->Coord.x = -linfo.kf * (in->PDB->Coord.x - ref->PDB->Coord.x); 
				out->PDB->Coord.y = -linfo.kf * (in->PDB->Coord.y - ref->PDB->Coord.y); 
				out->PDB->Coord.z = -linfo.kf * (in->PDB->Coord.z - ref->PDB->Coord.z); 
			} else {
				out->PDB->Coord.x = 0;
				out->PDB->Coord.y = 0;
				out->PDB->Coord.z = 0;
				out->PDB->Occupancy = 0;
			}
		} else {
			fprintf(stderr, "Two Files have Different residue number\n");
			exit(EXIT_FAILURE);
		}

		if(!pdbFileEnd(in) && !pdbFileEnd(ref)) {
			pdbFileNextAtom(in);
			pdbFileNextAtom(ref);
			pdbFileNextAtom(out);
		} else {
			break;
		}
	}
}

