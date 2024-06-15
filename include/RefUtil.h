/* type definition */

typedef struct {
  int ip;
  int iw;
  int ia;
  int dp;
  int dw;
  int da;
  int wp;
  int ww;
  int wa;
} mrcRefHeader;

const int mrcRefHeaderNumber = 9;


/* prototype */

/* in mrcRefUtil.c */

/* For Projection */
void lmrcRefFilamentProjction(mrcImage* out, mrcImage* in, float phi ,float omega ,float alpha ,int sizex ,int sizey );
void lvec3mul(double* out ,double x ,double* in );
void lvec3add(double* out ,double* in1 ,double* in2);
void lvec3sub(double* out ,double* in1 ,double* in2);
void lmrcPixelLiGet(mrcImage* mrc,
		    mrcImageParaTypeReal x,
		    mrcImageParaTypeReal y,
		    mrcImageParaTypeReal z,
		    double* data,
		    mrcPixelDataType mode,
		    mrcPixelDataHowToGet how);
void lestimateradian(float* lradian);

/* For Reference file Operattion */
void lmrc3DZ1Clear(mrcImage* in ,int z);
void lmrcRefHeaderSet(mrcImage* out ,mrcRefHeader* in);
