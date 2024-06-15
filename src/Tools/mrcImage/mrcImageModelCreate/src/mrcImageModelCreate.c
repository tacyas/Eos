/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageModelCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageModelCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageModelCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageModelCreate.h"

int
main(int argc, char* argv[]) 
{
	mrcImageModelCreateInfo info;
	mrcImage out;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	out.HeaderN.x = info.nx;
	out.HeaderN.y = info.ny;
	out.HeaderN.z = info.nz;
	out.HeaderLength.x = info.lx;
	out.HeaderLength.y = info.ly;
	out.HeaderLength.z = info.lz;
	out.HeaderMode = mrcFloatImage;
	mrcInit(&out, NULL);

	switch(info.mode) {
		case 0: {
			_lmrcImageModelCreateMode0(&out, info.r);
			break;
		}
		case 1: {
			_lmrcImageModelCreateMode1Info linfo;

			if(info.flagIn) {
				mrcFileRead(&in, info.In, "in main", 0);
				linfo.in = &in;
				linfo.flagIn = 1;
			} else {
				linfo.flagIn = 0;
			}

			linfo.inMode = info.inMode;

			linfo.radius = info.radius;
			linfo.nHelix = info.nHelix;
			linfo.zPitch = info.zPitch;
			if (info.flagphiAngle) {
				linfo.phiAngle = info.phiAngle*RADIAN;
			} else { 
				linfo.phiAngle = 360.0/info.nHelix * RADIAN;
			}
			linfo.deltaPhi = info.deltaPhi*RADIAN;
			linfo.startZ   = info.startZ;
			linfo.endZ     = info.endZ;
			linfo.startPhi = info.startPhi*RADIAN;
			linfo.fm       = info.fm;
			linfo.units    = info.units;
			_lmrcImageModelCreateMode1(&out, linfo);
			break;
		}
		
		case 2: {
			_lmrcImageModelCreateMode2(&out);
			break;
		}
		case 3: {
			_lmrcImageModelCreateMode3(&out);
			break;
		}
		case 4: {
			_lmrcImageModelCreateMode4(&out);
			break;
		}
		case 5: {
			_lmrcImageModelCreateMode5(&out);
			break;
		}
		case 6: {
			DEBUGPRINT("_lmrcImageModelCreateSheppLogan2D\n");
			_lmrcImageModelCreateSheppLogan2D(&out);
			DEBUGPRINT("END\n");
			break;
		}
		case 7: {
			_lmrcImageModelCreateSheppLogan3D(&out);
			break;
		}
		case 8: {
			_lmrcImageModelCreateCylinder(&out, info.r, info.l);
			break;
		}
		case 9: {
			_lmrcImageModelCreateGradientBarX(&out, info.min, info.max);
			break;
		}
		default: {
					 	fprintf(stderr, "Not supported\n");
		}

	}
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, ">>>> \n");
	fprintf(stderr, "-nx -ny -nz : image size[pixel]\n");
	fprintf(stderr, "-lx -ly -lz : pixel/voxel size[Angstrom]\n");
	fprintf(stderr, ">>>> Mode <<<< (-m)\n");
	fprintf(stderr, "0: Circle(a right cylinder:3D) and Triangle(a trigonal prism:3D) \n");
	fprintf(stderr, "       Optional argument : -nx -ny -nz -r  \n");
	fprintf(stderr, "1: Thick Filaments \n");
	fprintf(stderr, "		Example \n");
	fprintf(stderr, "       Optional argument \n");
	fprintf(stderr, "       -nx -ny -nz Image Size \n");
	fprintf(stderr, "       -lx -ly -lz Pixel Size \n");
	fprintf(stderr, "       -radius filament radius 150[A]\n");
	fprintf(stderr, "       -n  three helix \n");
	fprintf(stderr, "       -dz  pitch 143[A] \n");
	fprintf(stderr, "       -dphi rotation angle 40[degree]\n");
	fprintf(stderr, "       -phi rotation angle in the same level 120[degree]\n");
	fprintf(stderr, "       -sz  start z 0[A]\n");
	fprintf(stderr, "       -ez  end z 800[A]\n");
	fprintf(stderr, "       -sphi start phi 0[degree]\n");
	fprintf(stderr, "       -----------------------\n");
	fprintf(stderr, "       -inMode Centre = 0     \n");
	fprintf(stderr, "       -inMode Origin = 1     \n");
	fprintf(stderr, "       -----------------------\n");
	fprintf(stderr, "       -units 9 \n");
	fprintf(stderr, "       -fm formation of Gauss Sphere (t=1, u=9 and n=3)\n");
	fprintf(stderr, "       	0: normal \n");
	fprintf(stderr, "       	1: 3 sphere on the same z\n");
	fprintf(stderr, "       		Phi 0 , 30 , 60 degree    \n");
	fprintf(stderr, "           2: 3 sphere on the differnt z  and on the differnt radius\n");
	fprintf(stderr, "       		Phi 0 , 30 , 60 degree    \n");
	fprintf(stderr, "       		Z  0 , 30 , 60 A         \n");
	fprintf(stderr, "       		Radius 0 ,1.2 ,1.4 times     \n");
	fprintf(stderr, "           3: 3 sphere on the same z and on the different radius\n");
	fprintf(stderr, "       		Phi 0 , 30 , 60 degree    \n");
	fprintf(stderr, "       		Z  0 ,  0 ,  0 A         \n");
	fprintf(stderr, "       		Radius 0 ,1.2 ,1.4 times     \n");
	fprintf(stderr, "       -----------------------\n");
	fprintf(stderr, "       -units 3 \n");
	fprintf(stderr, "       -fm formation of Gauss Sphere (t=1, u=3 and n=3)\n");
	fprintf(stderr, "       	0: abnormal \n");
	fprintf(stderr, "2: Dot(2D)\n");
	fprintf(stderr, "3: Projection of 2 Sphere and 2 circle for 2D \n");
	fprintf(stderr, "       Optional argument : -nx -ny   \n");
	fprintf(stderr, "4: Another Projection of 2 Sphere and 2 circle for 2D \n");
	fprintf(stderr, "       Optional argument : -nx -ny   \n");
	fprintf(stderr, "5: Another Projection of 2 Sphere for 2D \n");
	fprintf(stderr, "       Optional argument : -nx -ny   \n");
	fprintf(stderr, "6: SheppLogan 2D \n");
	fprintf(stderr, "       Optional argument : -nx -ny   \n");
	fprintf(stderr, "7: SheppLogan 3D \n");
	fprintf(stderr, "       Optional argument : -nx -ny -nz  \n");
	fprintf(stderr, "8: Cylinder 3D \n");
	fprintf(stderr, "       Optional argument : -nx -ny -nz -r -l \n");
	fprintf(stderr, "9: Gradient Bar along x\n");
	fprintf(stderr, "       Optional argument : -nx -ny -nz -l -range\n");
}
