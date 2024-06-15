/*
# lmolvieDisplayListMake : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieDisplayListMake 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../inc/eosOpenGL.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "mrcImage.h"
#include "./DisplayListNumber.h"

static pdbFile* pdbIn;

/*static GLboolean needDisplayListMakingAtom=GL_TRUE;
static GLboolean needDisplayListMakingStick=GL_TRUE;
static GLboolean needDisplayListMakingAtomSerial=GL_TRUE;
static GLboolean needDisplayListMakingResidue=GL_TRUE;
static GLboolean needDisplayListMakingTemp=GL_TRUE;
static GLboolean needDisplayListMakingStickTemp=GL_TRUE;
static GLboolean needDisplayListMakingStickResidue=GL_TRUE;
static GLboolean needDisplayListMakingSurface=GL_TRUE;
static GLboolean needDisplayListMakingDistanceFromTarget=GL_TRUE;
static GLboolean needDisplayListMakingWireFrame=GL_TRUE;
static GLboolean needDisplayListMakingChain=GL_TRUE;*/

GLboolean myDisplayListMakeAtom(void)
{
	DEBUGPRINT("Start myDisplayListMakeAtom\n");
	pdbIn=get_pdb();
	DEBUGPRINT2("PDBFileGet: %x %d\n", pdbIn, pdbIn->nAtom);

	glNewList(drawatomc, GL_COMPILE);
	DrawAtomC(pdbIn);
	glEndList();
	glNewList(drawatomca, GL_COMPILE);
	DrawAtomCA(pdbIn);
	glEndList();
	glNewList(drawatomo, GL_COMPILE);
	DrawAtomO(pdbIn);
	glEndList();
	glNewList(drawatomn, GL_COMPILE);
	DrawAtomN(pdbIn);
	glEndList();
	glNewList(drawatoms, GL_COMPILE);
	DrawAtomS(pdbIn);
	glEndList();
	glNewList(drawatomp, GL_COMPILE);
	DrawAtomP(pdbIn);
	glEndList();
	glNewList(drawatomh, GL_COMPILE);
	DrawAtomH(pdbIn);
	glEndList();
	glNewList(drawatomfe, GL_COMPILE);
	DrawAtomFE(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeStick(void)
{
	glNewList(drawstick, GL_COMPILE);
	DrawStick(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeAtomSerial(void)
{
	glNewList(drawatomserial, GL_COMPILE);
  	DrawAtomSerial(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeResidue(void)
{
	glNewList(drawresidue, GL_COMPILE);
	DrawResidue(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeTemp(void)
{
	glNewList(drawtemp, GL_COMPILE);
	DrawTemp(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeStickTemp(void)
{
	glNewList(drawsticktemp, GL_COMPILE);
	DrawStickTemp(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeStickResidue(void)
{
	glNewList(drawstickresidue, GL_COMPILE);
	DrawStickResidue(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeSurface(void)
{
	mrcImage *mrc;

	glNewList(drawsurface, GL_COMPILE);
	mrc=get_mrc();/*lmolvieMRCread.c*/
	marching_cubes_display(mrc);
	glEndList();
	return GL_FALSE;
}

/*GLboolean myDisplayListMakeDistanceFromTarget(void)
{
	glNewList(drawdistancefromtarget, GL_COMPILE);
	DrawDistanceFromTarget(pdbIn);
	glEndList();
	return GL_FALSE;
}*/

GLboolean myDisplayListMakeWireFrame(void)
{
	glNewList(drawwireframe, GL_COMPILE);
	DrawWireFrame(pdbIn);
	glEndList();
	return GL_FALSE;
}

GLboolean myDisplayListMakeChain(void)
{
	glNewList(drawchain, GL_COMPILE);
	DrawChain(pdbIn);
	glEndList();
	return GL_FALSE;
}
