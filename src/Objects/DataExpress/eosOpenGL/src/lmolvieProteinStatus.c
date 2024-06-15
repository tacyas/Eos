/*
# lmolvieProteinStatus : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieProteinStatus 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "../inc/eosOpenGL.h"
#include "./lmolvie.h"
#include "pdbFile.h"
#include "./lmolvieProteinStatus.h"

extern void setMyCamera(pdbCenter pdbCenter, GLfloat h);

static ProteinStatus protein[5];

static GLuint ProteinNumber=0;
static GLuint multiProteinChange=0;

pdbCenter getpdbCenter(int returnID)
{
	return protein[returnID].__pdbCenter;
}

void putpdbCenter(pdbFile* putpdbfile)
{
	GLfloat h;

	putpdbfile->PDB=putpdbfile->top;
	protein[ProteinNumber].__pdbCenter.xMax=putpdbfile->PDB->Coord.x;
	protein[ProteinNumber].__pdbCenter.xMin=putpdbfile->PDB->Coord.x;
	protein[ProteinNumber].__pdbCenter.yMax=putpdbfile->PDB->Coord.y;
	protein[ProteinNumber].__pdbCenter.yMin=putpdbfile->PDB->Coord.y;
	protein[ProteinNumber].__pdbCenter.zMax=putpdbfile->PDB->Coord.z;
	protein[ProteinNumber].__pdbCenter.zMin=putpdbfile->PDB->Coord.z;
	putpdbfile->PDB=putpdbfile->PDB->next;
	while(NULL!=putpdbfile->PDB){
		if(protein[ProteinNumber].__pdbCenter.xMax<putpdbfile->PDB->Coord.x){
			protein[ProteinNumber].__pdbCenter.xMax=putpdbfile->PDB->Coord.x;
		}
		if(protein[ProteinNumber].__pdbCenter.xMin>putpdbfile->PDB->Coord.x){
			protein[ProteinNumber].__pdbCenter.xMin=putpdbfile->PDB->Coord.x;
		}
		if(protein[ProteinNumber].__pdbCenter.yMax<putpdbfile->PDB->Coord.y){
			protein[ProteinNumber].__pdbCenter.yMax=putpdbfile->PDB->Coord.y;
		}
		if(protein[ProteinNumber].__pdbCenter.yMin>putpdbfile->PDB->Coord.y){
			protein[ProteinNumber].__pdbCenter.yMin=putpdbfile->PDB->Coord.y;
		}
		if(protein[ProteinNumber].__pdbCenter.zMax<putpdbfile->PDB->Coord.z){
			protein[ProteinNumber].__pdbCenter.zMax=putpdbfile->PDB->Coord.z;
		}
		if(protein[ProteinNumber].__pdbCenter.zMin>putpdbfile->PDB->Coord.z){
			protein[ProteinNumber].__pdbCenter.zMin=putpdbfile->PDB->Coord.z;
		}
		putpdbfile->PDB=putpdbfile->PDB->next;
	}

	protein[ProteinNumber].__pdbCenter.xWidth = protein[ProteinNumber].__pdbCenter.xMax - protein[ProteinNumber].__pdbCenter.xMin;
	protein[ProteinNumber].__pdbCenter.yWidth = protein[ProteinNumber].__pdbCenter.yMax - protein[ProteinNumber].__pdbCenter.yMin;
	protein[ProteinNumber].__pdbCenter.zWidth = protein[ProteinNumber].__pdbCenter.zMax - protein[ProteinNumber].__pdbCenter.zMin;
	
	protein[ProteinNumber].__pdbCenter.xCenter = (protein[ProteinNumber].__pdbCenter.xMax + protein[ProteinNumber].__pdbCenter.xMin) / 2.0;
	protein[ProteinNumber].__pdbCenter.yCenter = (protein[ProteinNumber].__pdbCenter.yMax + protein[ProteinNumber].__pdbCenter.yMin) / 2.0;
	protein[ProteinNumber].__pdbCenter.zCenter = (protein[ProteinNumber].__pdbCenter.zMax + protein[ProteinNumber].__pdbCenter.zMin) / 2.0;
	
	fprintf(stdout, "pdbcenter: %f, %f, %f, %f, %f, %f\n", protein[ProteinNumber].__pdbCenter.xWidth, protein[ProteinNumber].__pdbCenter.yWidth, protein[ProteinNumber].__pdbCenter.zWidth, protein[ProteinNumber].__pdbCenter.xCenter, protein[ProteinNumber].__pdbCenter.yCenter, protein[ProteinNumber].__pdbCenter.zCenter);

	if(ProteinNumber==0){
		if(protein[ProteinNumber].__pdbCenter.xWidth > protein[ProteinNumber].__pdbCenter.yWidth){
			h = ((protein[ProteinNumber].__pdbCenter.xWidth / 2) * 1.8) + (protein[ProteinNumber].__pdbCenter.zWidth / 1);	/* 1.8 ha rute3 no kinjiti */
		}
		else{
			h = ((protein[ProteinNumber].__pdbCenter.yWidth / 2) * 1.8) + (protein[ProteinNumber].__pdbCenter.zWidth / 1);	/* 1.8 ha rute3 no kinjiti */
		}
		fprintf(stdout, "h = %f\n", h);
		setMyCamera(protein[ProteinNumber].__pdbCenter, h);
	}

	proteinInit();

	ProteinNumber++;
	if(ProteinNumber==5){
		ProteinNumber=4;
	}
}

GLuint getProteinNumber(){/*load number*/
	return ProteinNumber;
}

void proteinInit(){
	protein[ProteinNumber].__elementSwitch.elementC=1;
	protein[ProteinNumber].__elementSwitch.elementO=1;
	protein[ProteinNumber].__elementSwitch.elementN=1;
	protein[ProteinNumber].__elementSwitch.elementS=1;
	protein[ProteinNumber].__elementSwitch.elementP=1;
	protein[ProteinNumber].__elementSwitch.elementH=1;
	protein[ProteinNumber].__elementSwitch.elementFE=1;

	protein[ProteinNumber].spin_x=0;
	protein[ProteinNumber].spin_y=0;
	protein[ProteinNumber].move_x=0.0;
	protein[ProteinNumber].move_y=0.0;
}

elementSwitch get_elementSwitch(int ID)
{
	return protein[ID].__elementSwitch;
}

void put_elementSwitch(int ID, char atom)
{
	switch(atom) {
		case 'c': {
			protein[ID].__elementSwitch.elementC+=1;
			if(protein[ID].__elementSwitch.elementC==3){
				protein[ID].__elementSwitch.elementC=0;
			}
			if(protein[ID].__elementSwitch.elementC==1){
				fprintf(stdout, "C switch ON\n");
			}
			else if(protein[ID].__elementSwitch.elementC==2){
				fprintf(stdout, "C switch mainChain\n");
			}
			else{
				fprintf(stdout, "C switch OFF\n");
			}
			break;
		}
		case 'o': {
			protein[ID].__elementSwitch.elementO*=-1;
			if(protein[ID].__elementSwitch.elementO==1){
				fprintf(stdout, "O switch ON\n");
			}
			else{
				fprintf(stdout, "O switch OFF\n");
			}
			break;
		}
		case 'n': {
			protein[ID].__elementSwitch.elementN*=-1;
			if(protein[ID].__elementSwitch.elementN==1){
				fprintf(stdout, "N switch ON\n");
			}
			else{
				fprintf(stdout, "N switch OFF\n");
			}
			break;
		}
		case 's': {
			protein[ID].__elementSwitch.elementS*=-1;
			if(protein[ID].__elementSwitch.elementS==1){
				fprintf(stdout, "S switch ON\n");
			}
			else{
				fprintf(stdout, "S switch OFF\n");
			}
			break;
		}
		case 'p': {
			protein[ID].__elementSwitch.elementP*=-1;
			if(protein[ID].__elementSwitch.elementP==1){
				fprintf(stdout, "P switch ON\n");
			}
			else{
				fprintf(stdout, "P switch OFF\n");
			}
			break;
		}
		case 'h': {
			protein[ID].__elementSwitch.elementH*=-1;
			if(protein[ID].__elementSwitch.elementH==1){
				fprintf(stdout, "H switch ON\n");
			}
			else{
				fprintf(stdout, "H switch OFF\n");
			}
			break;
		}
		case 'f': {
			protein[ID].__elementSwitch.elementFE*=-1;
			if(protein[ID].__elementSwitch.elementFE==1){
				fprintf(stdout, "Fe switch ON\n");
			}
			else{
				fprintf(stdout, "Fe switch OFF\n");
			}
			break;
		}
	}
}

int getSpin_x(int ID)
{
	return protein[ID].spin_x;
}

int getSpin_y(int ID)
{
	return protein[ID].spin_y;
}

int getSpin_z(int ID)
{
	return protein[ID].spin_z;
}

void proteinRotateX(int pan, int ID)
{
	protein[ID].spin_x-=pan;
}

void proteinRotateY(int pan, int ID)
{
	protein[ID].spin_y-=pan;
}

void proteinRotateZ(int pan, int ID)
{
	protein[ID].spin_z-=pan;
}

int getMultiMoveX(int ID)
{
	return protein[ID].move_x;
}

int getMultiMoveY(int ID)
{
	return protein[ID].move_y;
}

void MultiMoveX(GLint move)
{
	protein[multiProteinChange].move_x+=(float)move/10.0;
}

void MultiMoveY(GLint move)
{
	protein[multiProteinChange].move_y-=(float)move/10.0;
}

void set_multiProteinChange(){
	multiProteinChange++;
	if(multiProteinChange==ProteinNumber+1){
		multiProteinChange=0;
	}
	fprintf(stdout, "You operate no.%d protein.\n", multiProteinChange);
}

GLuint get_multiProteinChange(){/*oprating number*/
	return multiProteinChange;
}

/*void saveStatus()
{
	saveproteinStatus(protein[multiProteinChange]);
}

void loadStatus()
{
	loadproteinStatus(&protein[multiProteinChange]);
}*/
