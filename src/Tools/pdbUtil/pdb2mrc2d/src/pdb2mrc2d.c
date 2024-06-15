/*
# pdb2mrc2d.c  1.5
# The latest update : 11/02/96 at 23:15:49
#
#@(#) pdb2mrc2d ver 1.5
#@(#) Created by 
#@(#)
#@(#) Usage : pdb2mrc2d
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)pdb2mrc2d ver1.5; Date:96/11/02 @(#)";

/*

      y
      |
      |
      |
      |
      |____________ x 
     /
    /
   /
 z

	Projection : x-y plane along z-axis

	RotationRule    : YOYS 
	First Rotation  : y-axis : Y: Y
	Second Rotation : x-axis : O: Odd 
	Last Rotation   : z-axis : Y: Same
	v1 = A v0                : S: Staic 
		
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#undef DEBUG
#include "mrcImage.h"       
#include "../inc/config.h"
#include "pdbFile.h"
#include "lpdb2mrcInfo.h"
#include "genUtil.h"
#include "Matrix3D.h"
#include "Map2D.h"

#ifdef CUDA
#include "eosCuda.h"
#endif

#define HowToCreateImageBit (0x1)
#define HowToDrawMapBit     (0x2)

int
main(int argc, char* argv[])
{
    pdb2mrc2dInfo info;
    lpdb2mrc2dInfo linfo;
    pdbFile pdb;
    mrcImage mrc;
    mrcImage out;
    mrcImage out3D;
	mrcImageParaTypeRealCoord to;
	mrcImageParaTypeReal ix, iy;
	pdbFileParaTypeReal rotx, roty, rotz, droty;
	Map2DParaTypeInteger nrotx, nroty;
	mrcImageParaTypeReal zsection;
	
    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

#ifdef CUDA
	if(info.flagcudaDeviceID) {
		eosCudaInit(info.cudaDeviceID);
	}
#endif

	linfo.dx = info.dx; linfo.dy = info.dy;
	linfo.nx = info.nx; linfo.ny = info.ny;

	if(info.flagsx && info.flagsy ) {
		linfo.sx = info.sx; linfo.sy = info.sy;
	} else {
		linfo.sx = -1.0*info.dx*info.nx/2.0 ;
		linfo.sy = -1.0*info.dy*info.ny/2.0 ;
	}
	linfo.Weight = info.Weight;
	linfo.Sigma = info.Sigma;

	if(!(info.flagOut|info.flagOut3D)) {
		fprintf(stderr, "This program has no work for your request\n");
		fprintf(stderr, "-o or -O option is required.\n");
		usage(argv[0]);
	}

    pdbFileRead(info.fptIn, &pdb);
	if(info.flagsrotx) {
		pdbRotationZXY(&pdb, info.srotx*RADIAN, -info.sroty*RADIAN, info.srotz*RADIAN);
	}
	if(info.flagsRotMode) {
		pdbRotationFollowingEulerAngle(&pdb, info.sRotMode, info.sRot1*RADIAN, -info.sRot2*RADIAN, info.sRot3*RADIAN);
	}
	if(info.flagdRot1 && !info.flagrotnx) {
		info.rotnx = (int)((info.maxRot1 - info.minRot1)/info.dRot1+0.5);
	}	
	if(info.flagdRot2 && !info.flagrotny) {
		info.rotny = (int)((info.maxRot2 - info.minRot2)/info.dRot2+0.5)*2;
	}
	if(info.flagOut) {
		out.HeaderN.x = info.rotnx*info.nx; 
		out.HeaderN.y = info.rotny*info.ny; 
		out.HeaderN.z = 1.0;
	   	out.HeaderMode = 	mrcFloatImage;
		out.HeaderLength.x = info.dx; 
		out.HeaderLength.y = info.dy; 
		out.HeaderLength.z = 0.0; 
	    mrcInit(&out, (char*)NULL);
	}
	if(info.flagOut3D) {
		out3D.HeaderN.x = info.nx; 
		out3D.HeaderN.y = info.ny; 
		out3D.HeaderN.z = info.rotnx*info.rotny;
	   	out3D.HeaderMode = 	mrcFloatImage;
		out3D.HeaderLength.x = info.dx; 
		out3D.HeaderLength.y = info.dy; 
		out3D.HeaderLength.z = 0.0; 
	    mrcInit(&out3D, NULL);
		out3D.numTailer = out3D.HeaderN.z; 
		mrcTailerInit(&out3D, 0);
	}
	rotz = 0.0;
	nrotx = info.rotny; /* Attention: x - y change */

	zsection = 0.0;
	for(ix=0; ix < nrotx ; ix++) {
		if(nrotx/4 < ix && ix < nrotx/4*3) {
			/* Skip */
		} else {
			if(!info.flagRotMode) {
				rotx = ((double)ix)/nrotx*2.0*M_PI; 
			} else {
				rotx = ((double)ix)/nrotx*2.0*M_PI; 
			}
			map2DParallelInfo(&nroty, &droty,
							  rotx, info.rotnx, 
							  (info.mode&HowToCreateImageBit));
			for(iy=0; iy < info.rotny; iy+= droty) {
				DEBUGPRINT2("%g %g\n", ix, iy);

#ifdef DEBUG
				{
					pdbFileTop(&pdb);
					pdbFileNextAtom(&pdb);
					DEBUGPRINT3("(x, y, z)=(%g, %g %g)\n", pdb.PDB->Coord.x, pdb.PDB->Coord.y, pdb.PDB->Coord.z);
				}
#endif

				if(!info.flagRotMode) {
					roty = ((double)iy)/info.rotny*2.0*M_PI; 
					pdbRotationZXY(&pdb, rotx, -roty, -rotz); 
				} else {
					roty = ((double)iy)/info.rotny*2.0*M_PI; 
					pdbRotationFollowingEulerAngle(&pdb, info.RotMode, -roty, rotx, -rotz); 
				}

#ifdef DEBUG
				{
					pdbFileTop(&pdb);
					pdbFileNextAtom(&pdb);
					DEBUGPRINT3("(x, y, z)=(%g, %g %g)\n", pdb.PDB->Coord.x, pdb.PDB->Coord.y, pdb.PDB->Coord.z);
				}
#endif

				DEBUGPRINT3("rot: (%g %g %g) \n", rotx*DEGREE, roty*DEGREE, rotz*DEGREE);

	    		lpdb2mrc2d(&mrc, &pdb,  &linfo, 'z', 0);
#ifdef DEBUG
				{
					char s[1024];
	
					sprintf(s, "/tmp/test.mrc.%03d", (int)zsection);
					
					mrcFileWrite(&mrc, s, "tmp", 0);
				}
#endif

				if(!info.flagRotMode) {
					pdbRotationYXZ(&pdb, -rotx, roty, rotz);
				} else {
					pdbRotationFollowingEulerAngleInverse(&pdb, info.RotMode, roty, -rotx, -rotz); 
				}

				DEBUGPRINT3("%g %g %g\n", -roty*DEGREE, rotx*DEGREE, -rotz*DEGREE);
				if(info.flagOut) {
					map2DCoordGet(&(to.x), &(to.y), roty, rotx, info.rotnx, info.rotny, ((info.mode&HowToDrawMapBit)>>1)); 
					to.x = fmod(to.x*info.nx, out.HeaderN.x); 
					to.y = fmod(to.y*info.ny, out.HeaderN.y); 
					DEBUGPRINT2("map %f %f\n", to.x, to.y);
					to.z = 0.0;
					DEBUGPRINT3("to: %f %f %f\n", to.x, to.y, to.z);
					lmrcImageCopy(&out, &mrc, to);
#ifdef DEBUG
				{
					char s[1024];
					sprintf(s, "/tmp/test.2d.%03d", (int)zsection);
					mrcFileWrite(&out, s, "tmp", 0);
				}
#endif
				} 
				if(info.flagOut3D) {
					to.x = 0.0;
					to.y = 0.0;
					to.z = zsection;
					out3D.Tailer[(int)zsection].Cont.Mode = mrcImageTailerMode2DProjection; 
					out3D.Tailer[(int)zsection].Cont.EulerAngleMode[0] = info.RotMode[0]; /* X or Y or Z */
					out3D.Tailer[(int)zsection].Cont.EulerAngleMode[1] = info.RotMode[1]; /* E[ven] or O[dd] */ 
					out3D.Tailer[(int)zsection].Cont.EulerAngleMode[2] = info.RotMode[2]; /* S[ame] or D[iff] */ 
					out3D.Tailer[(int)zsection].Cont.EulerAngleMode[3] = info.RotMode[3]; /* S[tatic] or R[otating] */ 
					out3D.Tailer[(int)zsection].Cont.Rot1 = -roty; 
					out3D.Tailer[(int)zsection].Cont.Rot2 =  rotx; 
					out3D.Tailer[(int)zsection].Cont.Rot3 = -rotz; 
					DEBUGPRINT3("to: %f %f %f\n", to.x, to.y, to.z);
					lmrcImageCopy(&out3D, &mrc, to); 	
					zsection += 1.0;
				}
				mrcImageFree(&mrc, 0);
			}
		}
	}
	if(info.flagOut) {
	   mrcStatDataSet(&out, 0);
 	   mrcFileWrite(&out, info.Out, "in pdb2mrc2d Main Routine", 0);
	}
	if(info.flagOut3D) {
	   out3D.HeaderN.z = zsection;
	   out3D.numTailer = zsection;
	   mrcHiddenDataSet(&out3D, 0);
	   mrcStatDataSet(&out3D, 0);
 	   mrcFileWrite(&out3D, info.Out3D, "in pdb2mrc2d Main Routine", 0);
	}
	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Attention1 -----\n");	
	fprintf(stderr, "If both of -s and -startEA, first -s and second -startEA will be performed\n");	
	fprintf(stderr, "----- Attention2 -----\n");	
	fprintf(stderr, "Bug fixed: rotation around x-axis. + is changed to - \n");
	fprintf(stderr, "----- Mode -----\n");	
	fprintf(stderr, "%d: 0: equal angle 1: equal area\n", HowToCreateImageBit);	
	fprintf(stderr, "%d: 0: Mercatol    1: Morwide \n", HowToDrawMapBit);	
}

