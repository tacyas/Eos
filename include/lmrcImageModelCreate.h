#ifndef  LMRC_IMAGE_MODEL_CREATE_H 
#define  LMRC_IMAGE_MODEL_CREATE_H

/* struct begin */
typedef struct _lmrcImageModelCreateMode1Info {
	float radius;
	float nHelix;
	float zPitch;
	float phiAngle;
	float deltaPhi;
	float startZ;
	float endZ;
	float startPhi;
	int     flagIn;
	mrcImage*  in;
	mrcImageDataSetMode inMode;
	int 	fm;
	int 	units;
} _lmrcImageModelCreateMode1Info;
/* struct end */

/* prototype begin */
extern void _lmrcImageModelCreateMode0(mrcImage* out, mrcImageParaTypeReal radius);
extern void _lmrcImageModelCreateMode1(mrcImage* out, _lmrcImageModelCreateMode1Info info);
extern void _lmrcImageModelCreateMode2(mrcImage* out);
extern void _lmrcImageModelCreateMode3(mrcImage* out);
extern void _lmrcImageModelCreateMode4(mrcImage* out);
extern void _lmrcImageModelCreateMode5(mrcImage* out);
extern void _lmrcImageModelCreateSheppLogan2D(mrcImage* out); // Mode: 6
extern void _lmrcImageModelCreateSheppLogan3D(mrcImage* out); // Mode: 7
extern void _lmrcImageModelCreateCylinder(mrcImage* out, mrcImageParaTypeReal radius,  mrcImageParaTypeReal length); // Mode: 8 
extern void _lmrcImageModelCreateGradientBarX(mrcImage* out, float min, float max);

/* prototype end */

#endif





