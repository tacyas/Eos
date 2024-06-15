#ifndef MRC_REFUTIL_H
#define MRC_REFUTIL_H
/* type definition */

/* struct begin */
typedef double mrcRefDegCoordinate; 

typedef struct {
  mrcRefDegCoordinate ip;
  mrcRefDegCoordinate iw;
  mrcRefDegCoordinate ia;
  mrcRefDegCoordinate dp;
  mrcRefDegCoordinate dw;
  mrcRefDegCoordinate da;
  mrcRefDegCoordinate wp;
  mrcRefDegCoordinate ww;
  mrcRefDegCoordinate wa;
} mrcRefHeader;

typedef struct {
  mrcRefDegCoordinate ip;
  mrcRefDegCoordinate iw;
  mrcRefDegCoordinate ia;
  mrcRefDegCoordinate dp;
  mrcRefDegCoordinate dw;
  mrcRefDegCoordinate da;
  mrcRefDegCoordinate wp;
  mrcRefDegCoordinate ww;
  mrcRefDegCoordinate wa;
  int mode;
} mrcRefCorHeader;

#define mrcRefHeaderNumber 9;

typedef struct {
  mrcRefDegCoordinate ip;
  mrcRefDegCoordinate iw;
  mrcRefDegCoordinate ia;
  mrcRefDegCoordinate dp;
  mrcRefDegCoordinate dw;
  mrcRefDegCoordinate da;
  mrcRefDegCoordinate wp;
  mrcRefDegCoordinate ww;
  mrcRefDegCoordinate wa;
  double sy;
  double ey;
  double refsize;
  int inverse;
} mrcpwzCorHeader;

/* struct end */

/* prototype begin */
/* macros */
#define surplus(a,b) (((a)/(b) > 0)?((a)-floor((a)/(b))*(b) ):((a)-floor((a)/(b)+1)*(b)))
#define NormalDegree(p) (((p) > 0)?( ( surplus( ( (p)+180 ) ,360 )) - 180 ):( (surplus(((p)-180),360)) +180 ))
 
/* prototype */

/* in mrcRefUtil.c */

/* For General */
void lRandShuffle(void);

/* For mrcImage Operation */
double lmrcImageZ1Normalization(mrcImage* in ,int z);
double lmrcImageNormalization(mrcImage* in ,int mode);
void lmrcImageRectangleGet(mrcImage* out ,mrcImage* in ,int blx ,int bly ,int trx ,int try );
void llmrcImageAdd(mrcImage* in1 ,mrcImage* in2);
void llmrcImageSub(mrcImage*out ,mrcImage* in1 ,mrcImage* in2);
void lmrcImageMultiplyingbyMrc(mrcImage* out ,mrcImage* in1 ,mrcImage* in2);
void lmrcImageFTSetbyRArray(mrcImage* infft ,double** filterval ,int mode);
double lmrcImageFTDataSetByRArray(double X ,double Y ,double Z ,double** filterval ,int mode);
void lmrcImageMagnificationChange(mrcImage* out, mrcImage* in, double ratio);
void lmrcImageCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,int Nz ,float Cx ,float Cy ,float Cz ,int mode);
void lmrcImageMultiplysingbyFile(mrcImage* in1 ,mrcImage* in2);

/* For mrcImage Statics */
double lmrcImageStandardDeviation(mrcImage* in);

/* For Projection */
void lmrcRefFilamentProjction(mrcImage* out, mrcImage* in, mrcRefDegCoordinate phi ,mrcRefDegCoordinate omega ,mrcRefDegCoordinate alpha ,int sizex ,int sizey );
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
void lestimateradian(mrcRefDegCoordinate* lradian);

/* For Reference file Operation */
void lmrc3DZ1Clear(mrcImage* in ,int z);
void lmrcRefHeaderSet(mrcImage* out ,mrcRefHeader* in);
void lmrcRefHeaderGet(mrcRefHeader* out ,mrcImage* in);
void lmrc3DZ1ImgPut(mrcImage* out ,mrcImage* in ,int z);
void lmrc3DZ1ImgGet(mrcImage* out ,mrcImage* in ,int z); 
void lmrc3DZ1FtPut(mrcImage* out ,mrcImage* in ,int Z);
void lmrc3DZ1FtGet(mrcImage* out ,mrcImage* in ,int Z);
double lmrcRef2DImgCorrelation(mrcImage* in1 ,mrcImage* in2 );
void lmrcRefNormalization(mrcImage* in);
int lmrcRefGetzCordinate(mrcRefDegCoordinate phi ,mrcRefDegCoordinate omega ,mrcRefDegCoordinate alpha ,mrcRefHeader* header);
void lmrcRefGetdegreeCoordinate(mrcRefDegCoordinate* phi ,mrcRefDegCoordinate* omega ,mrcRefDegCoordinate* alpha ,int z ,mrcRefHeader* header);

/* For Reference statics */
double lmrcRefSqrAverageZ1(mrcImage* in ,int z);
double lmrcRefSqrAverage(mrcImage* in);
double lmrcRefStandardDeviation(mrcImage* in);
double lmrcRefVariationZ1(mrcImage* in ,int z);


/* For Reference Correlation File Operation */
void lmrcRefCorHeaderSet(mrcImage* out ,mrcRefCorHeader* in);
void lmrcRefCorHeaderGet(mrcRefCorHeader* out ,mrcImage* in);
double lmrcRefCorrelationGet(mrcImage* in ,mrcRefDegCoordinate p1 ,mrcRefDegCoordinate w1 ,mrcRefDegCoordinate a1 ,mrcRefDegCoordinate p2 ,mrcRefDegCoordinate w2 ,mrcRefDegCoordinate a2 ,mrcRefCorHeader* header);
int lmrcRefCorrelationGetCordinate(mrcRefDegCoordinate phi ,mrcRefDegCoordinate omega ,mrcRefDegCoordinate alpha ,mrcRefCorHeader* header );
void lmrcRefCorrelationGetRefxCordinate(mrcRefDegCoordinate* phi ,mrcRefDegCoordinate* omega ,mrcRefDegCoordinate* alpha ,int x ,mrcImage* in ,mrcRefCorHeader* header);
void lmrcRefCorrelationGetRefyCordinate(mrcRefDegCoordinate* phi ,mrcRefDegCoordinate* omega ,mrcRefDegCoordinate* alpha ,int y ,mrcImage* in ,mrcRefCorHeader* header);

/* For pwz correlation file operation */
void lmrcpwzCorHeaderSet(mrcImage* out ,mrcpwzCorHeader* in);
void lmrcpwzCorHeaderGet(mrcpwzCorHeader* out ,mrcImage* in);


/* in lmrcImageROInotChangeHeaderLength.c */

extern double lbilinearInterpolation(double* image,
                       unsigned long nx, unsigned long ny,
                       double x, double y);

extern double lcubicConvolutionInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y);
extern double lpolyNominalInterpolation(double* image, 
                                unsigned long nx, unsigned long ny, 
                                double x, double y);
extern void lpolyInitMatrix(double matrix[6][6], int m, int n);
extern void lpolyInitVector(double vec[6], int m, int n, double* image, int nx, int ny);
extern int lpolySolveMatrix(double matrix[6][6], double vec[6], double coefficient[6]);


/* in mrcImageUtilityforVariance.c */
void lmrcImageFilteringbyFileForVariance(mrcImage* out ,mrcImage* in ,double** filterval ,int mode);

/* in lmrcImageCorrelationinSpace.c */
double lmrcImageCorrelationinSpace(mrcImage* in,mrcImage* ref,int mode);
/* prototype end */

# endif /* MRC_REFUTIL_H */










