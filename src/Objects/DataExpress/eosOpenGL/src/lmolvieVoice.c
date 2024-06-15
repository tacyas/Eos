/*
# lmolvieVoice : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieVoice 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <math.h>
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
//#include "pdbFile.h"

//extern pdbFile* pdbIn;

static GLdouble target_x=0.0, target_y=0.0, target_z=0.0;

/*
void lmolvieVoice(void)
{
	cameraInfo* camera;
	float distance, course, amplitude, Hz;

	float shift_Centre_x, shift_Centre_y, shift_Centre_z, shift_target_x, shift_target_y, shift_target_z;
	float costheta, innerProduct, length_p, length_v;

//	pdbFile* pdbIn;

//	pdbIn=get_pdb();
	camera=getMyCamera();

///pdbIn->PDB=pdbIn->top;
///while(NULL!=pdbIn->PDB){
///	if(strncmp(pdbIn->PDB->Record, "ATOM  ", 6)==0 || strncmp(pdbIn->PDB->Record, "HETATM", 6)==0){
///		distance=sqrt((camera->Eye[0]-pdbIn->PDB->Coord.x)*(camera->Eye[0]-pdbIn->PDB->Coord.x)
///			+(camera->Eye[1]-pdbIn->PDB->Coord.y)*(camera->Eye[1]-pdbIn->PDB->Coord.y)
///			+(camera->Eye[2]-pdbIn->PDB->Coord.z)*(camera->Eye[2]-pdbIn->PDB->Coord.z));
///		course=sqrt((camera->Centre[0]-pdbIn->PDB->Coord.x)*(camera->Centre[0]-pdbIn->PDB->Coord.x)
///			+(camera->Centre[1]-pdbIn->PDB->Coord.y)*(camera->Centre[1]-pdbIn->PDB->Coord.y)
///			+(camera->Centre[2]-pdbIn->PDB->Coord.z)*(camera->Centre[2]-pdbIn->PDB->Coord.z));
///		break;
///	}
///	else{
///		pdbIn->PDB=pdbIn->PDB->next;
///	}
///}

	distance=sqrt((camera->Eye[0]-target_x)*(camera->Eye[0]-target_x)
		+(camera->Eye[1]-target_y)*(camera->Eye[1]-target_y)
		+(camera->Eye[2]-target_z)*(camera->Eye[2]-target_z));

	shift_Centre_x=camera->Centre[0]-camera->Eye[0];
	shift_Centre_y=camera->Centre[1]-camera->Eye[1];
	shift_Centre_z=camera->Centre[2]-camera->Eye[2];
	shift_target_x=target_x-camera->Eye[0];
	shift_target_y=target_y-camera->Eye[1];
	shift_target_z=target_z-camera->Eye[2];

	innerProduct=(shift_Centre_x*shift_target_x)+(shift_Centre_y*shift_target_y)+(shift_Centre_z*shift_target_z);
	length_p=sqrt((shift_Centre_x*shift_Centre_x)+(shift_Centre_y*shift_Centre_y)+(shift_Centre_z*shift_Centre_z));
	length_v=sqrt((shift_target_x*shift_target_x)+(shift_target_y*shift_target_y)+(shift_target_z*shift_target_z));

	costheta=innerProduct/(length_p*length_v);

	if(distance<118){
		amplitude=128.0-distance;
	}
	else{
		amplitude=10.0;
	}

//	if(course<392){
//		Hz=784.0-(course*2);
//	}
//	else{
//		Hz=0;
//	}

	Hz=784.0*(costheta+1.0)/2.0;

	fprintf(stdout, "%f, %f\n", amplitude, Hz);

	monoSound(amplitude, Hz);
}
*/
void setTarget(GLdouble x, GLdouble y, GLdouble z)
{
	target_x=x;
	target_y=y;
	target_z=z;
}


