KARCH_DEFINE = -DKARCH_PARISC
KOPSYS_DEFINE = -DKOPSYS_HPUX
EOS_PATH = /users/Eos
EOS_LIBDIR = /usr/local/khoros210/lib
EOS_BINDIR = /usr/local/khoros210/bin
BOOTSTRAP_PATH = /users/khoros/bootstrap
BOOTSTRAP_LIBDIR = /usr/local/khoros210/lib
BOOTSTRAP_BINDIR = /usr/local/khoros210/bin
DATASERV_PATH = /users/khoros/dataserv
DATASERV_LIBDIR = /usr/local/khoros210/lib
DATASERV_BINDIR = /usr/local/khoros210/bin
DESIGN_PATH = /users/khoros/design
DESIGN_LIBDIR = /usr/local/khoros210/lib
DESIGN_BINDIR = /usr/local/khoros210/bin
TB_NAME = $(EOS_PATH)
TOOLBOX_PATH = /users/Eos
SHELL = /bin/sh
ARCH = Architecture
MAKE = make
MV = mv -f
SED = sed
YACC = yacc
YFLAGS = -d
LEX = lex
LFLAGS = -n
LINT = lint
INSTALL = $(SCRIPTSRC)/bsdinst.sh
LIBLD = ld
RM = rm -f
TAGS = ctags
KGENMAKE = kgenmake
DEPEND = kgendepend
KGENIMAKE = kgenimake
BASENAME = /bin/basename
SCRIPTSRC = $(BOOTSTRAP_PATH)/repos/config/scripts
FORTRANSCRIPT = $(SCRIPTSRC)/fortran.sh
GHOSTWRITER = ghostwriter
CONDUCTOR = conductor
KGENSTRUCT = kgenstruct
KLINT = klint
PROTOIZEFLAGS = -fstrength-reduce -fpcc-struct-return -fwritable-strings -ansi
KLD_RUN_PATH = $(EOS_LIBDIR):$(DESIGN_LIBDIR):$(DATASERV_LIBDIR):$(BOOTSTRAP_LIBDIR):$${LD_RUN_PATH+$$LD_RUN_PATH}
OBJECTINCLUDE = $(TOOLBOX_INCLUDE)
OBJECTLIBDIR = $(TOOLBOX_LIBDIR)
OBJECTDEFINES = $(TOOLBOX_DEFINES)
ALLINCLUDES = $(OBJECTINCLUDE) $(EXTRA_INCLUDES) $(STD_INCLUDES)
ALLDEFINES = $(ALLINCLUDES) $(KARCH_DEFINE) $(KOPSYS_DEFINE) $(OBJECTDEFINES) $(LOCALDEFINES) $(DEFINES)
LINTFLAGS = $(ALLDEFINES) $(ALLINCLUDES)
RM_CMD = $(RM) *.o core *.a tags ,* *~ *.i *.u *.B *.G *.T *.s .emacs_* tags TAGS .pure
MAKEFILE_CMD = $(KGENMAKE) $(IMAKE_DEFINES)
SYS_LIBRARIES = -lBSD -lmalloc -lm -ll -lcl
X_LIBRARIES = -lXaw -lXmu -lXt -lXext -lX11
ALLLIBDIRS = $(EXTRALIBDIR)
OBJS = $(YOBJS) $(LOBJS) $(COBJS) $(FOBJS) $(C++OBJS)
SRCS = $(YSRCS) $(LSRCS) $(CSRCS) $(FSRCS) $(C++SRCS)
TOOLBOX_INCLUDE = -I$(EOS_PATH)/include \
 		-I$(DESIGN_PATH)/include \
 		-I$(DATASERV_PATH)/include \
 		-I$(BOOTSTRAP_PATH)/include
TOOLBOX_LIBDIR = -L$(EOS_LIBDIR) \
 		-L$(DESIGN_LIBDIR) \
 		-L$(DATASERV_LIBDIR) \
 		-L$(BOOTSTRAP_LIBDIR)
C_TOOLBOX_LIBRARIES = -lkapu \
 		-lkaps \
 		-lkdms \
 		-lkdac \
 		-lkfmt \
 		-lkgen \
 		-lkcms \
 		-lkclui \
 		-lkvf \
 		-lkexpr \
 		-lklibdb \
 		-lklm \
 		-lku
C_TOOLBOX_DEP_LIBRARIES = $(DATASERV_LIBDIR)/libkapu.a \
 		$(DATASERV_LIBDIR)/libkaps.a \
 		$(DATASERV_LIBDIR)/libkdms.a \
 		$(DATASERV_LIBDIR)/libkdac.a \
 		$(DATASERV_LIBDIR)/libkfmt.a \
 		$(BOOTSTRAP_LIBDIR)/libkgen.a \
 		$(BOOTSTRAP_LIBDIR)/libkcms.a \
 		$(BOOTSTRAP_LIBDIR)/libkclui.a \
 		$(BOOTSTRAP_LIBDIR)/libkvf.a \
 		$(BOOTSTRAP_LIBDIR)/libkexpr.a \
 		$(BOOTSTRAP_LIBDIR)/libklibdb.a \
 		$(BOOTSTRAP_LIBDIR)/libklm.a \
 		$(BOOTSTRAP_LIBDIR)/libku.a
X_TOOLBOX_LIBRARIES = -lxvl \
 		-lxvf \
 		-lxvu \
 		-lxvs \
 		-lxvg \
 		-lxva \
 		-lxvobj \
 		-lkwid \
 		-lxvw
X_TOOLBOX_DEP_LIBRARIES = $(DESIGN_LIBDIR)/libxvl.a \
 		$(DESIGN_LIBDIR)/libxvf.a \
 		$(DESIGN_LIBDIR)/libxvu.a \
 		$(DESIGN_LIBDIR)/libxvs.a \
 		$(DESIGN_LIBDIR)/libxvg.a \
 		$(DESIGN_LIBDIR)/libxva.a \
 		$(DESIGN_LIBDIR)/libxvobj.a \
 		$(DESIGN_LIBDIR)/libkwid.a \
 		$(DESIGN_LIBDIR)/libxvw.a
BINDIR = $(EOS_BINDIR)
LIBDIR = $(EOS_LIBDIR)
OBJECT_TYPE = dir
TOOLBOX_NAME = eos
SUBDIRS = Display2  	Display3  	Eos  	ctfDeterminationFromPhaseComparison  	ctfDeterminationFromThonRing  	ctfDetermine  	ctfEnvelopFunction  	ctfFunction  	ctfFunctionServer  	ctfWeightMapCreation  	ctfZeroPoint  	defocusDeterminationFromThonRing  	dos2unix  	energyTransferModelCheck  	fft2d  	ip2mrc  	khorosFilterGenerate  	largeIPInfo  	ll2ltlg  	llDataAverage  	llDataAxisSearch  	llDataCTFCompensate  	llDataCompare  	llDataContributionCalcDifferentN  	llDataFit  	llDataInfo  	llDataLowPassFiltering  	llDataMultiCTFCompensation  	llDataPrint  	llDataRescaling  	llDataRotation  	llDataSeparate  	llDataWeightSet  	llDatarMaxLimit  	llExtract  	llExtractCtfinfFileCreate  	llExtractCtrlFileCreate  	llExtractWithLayerSeparation  	llExtractWithLayerSeparationCtrlFileCreate  	llExtractWithLayerSeparationCtrlFileCreateMyosin  	llExtractWithLayerSeparationFilamentInfo  	ltlg2mrc  	ltlgDataInfo  	mrc2Dto3D  	mrc2Dto3DforVariation  	mrc2fld  	mrc2gif  	mrc2hdf  	mrc2lattice  	mrc2map  	mrc2tiff  	mrc2viff  	mrc3DExtractZ  	mrcFFTBandPassFilter  	mrcFFTCTFCompensation  	mrcFFTExpression  	mrcFFTFiltering  	mrcFFTInfo  	mrcFFTProjection  	mrcFFTSizeChange  	mrcFFTXFiltering  	mrcFFTplainreduce  	mrcImage1DProjectionfrom2D  	mrcImage1dAverageByCorrelation  	mrcImage1dCutAverage  	mrcImage1dShiftAverageByAnnealing  	mrcImage1dShiftByCorrelation  	mrcImage2DProjection  	mrcImage3DHighResoEmphasis  	mrcImage3DPad  	mrcImageAbnormalValueRemove  	mrcImageAdaptiveBinalization  	mrcImageAdd  	mrcImageAssignedToTFofPDB  	mrcImageAutoCorrelationWithWindowing  	mrcImageAutoFilamentExtract  	mrcImageAutoFilamentExtractResultAnalysis  	mrcImageAutoRotationCorrelation  	mrcImageAutoRotationCorrelationResultPrint  	mrcImageAverage  	mrcImageBandPassFilter  	mrcImageCTFCompensation  	mrcImageCTFDetermination  	mrcImageCTFObservation  	mrcImageCTFSN  	mrcImageCVE  	mrcImageCenterGet  	mrcImageCenterOfMassCalculate  	mrcImageCircumferentialProjection  	mrcImageColoring  	mrcImageCoordinateChange  	mrcImageCorrelation  	mrcImageCorrelationWithCTFCompensation  	mrcImageCrystalCreate  	mrcImageCutAndSetInArray  	mrcImageCylinderSection  	mrcImageDensityInfo  	mrcImageDevideIntoTwoImages  	mrcImageEnhancementWithFuzzySets  	mrcImageFFT  	mrcImageFilteringbyFile  	mrcImageFilteringbyFileForVariance  	mrcImageFourierPowerSpectrum  	mrcImageFourierShellCorrelation  	mrcImageGaussSphere  	mrcImageHeaderChange  	mrcImageHelicalProjection  	mrcImageHighPassFilter  	mrcImageHighlighting  	mrcImageInfo  	mrcImageLowPassFilter  	mrcImageMagnificationChange  	mrcImageMake2DArrayImage  	mrcImageMakeCylinder  	mrcImageMakeDump  	mrcImageMasking  	mrcImageMaskingByImage  	mrcImageMergebyside  	mrcImageModeChange  	mrcImageModelCreate  	mrcImageMultiCTFCompensation  	mrcImageMultiCTFDetermination  	mrcImageMultiplying  	mrcImageNoiseAdd  	mrcImageNoiseCreate  	mrcImageNoiseReductionByRelaxation  	mrcImageNormalizedSubstraction  	mrcImageNormalizing  	mrcImagePad  	mrcImagePolyROI  	mrcImagePrint  	mrcImagePrint3D  	mrcImageProjection  	mrcImagePut3D  	mrcImageROI  	mrcImageRadialDistribution  	mrcImageRectangleGet  	mrcImageRectangleGetByCorrelation  	mrcImageRefConv2D  	mrcImageRefCreate  	mrcImageRefFFTConv2D  	mrcImageRefScaleChangeWithPad  	mrcImageReverse  	mrcImageRotation  	mrcImageSN  	mrcImageSamplingUnitChange  	mrcImageScalarAdd  	mrcImageSectionGet  	mrcImageSetFunction  	mrcImageShift  	mrcImageShrink  	mrcImageSmoothing  	mrcImageSolventFlattening  	mrcImageStandardDeviation  	mrcImageSubstraction  	mrcImageSymmetryFind  	mrcImageTfunction  	mrcImageTransepose  	mrcImageTransformDescartesIntoPolar  	mrcImageTwoImageTest  	mrcImageUnbentROI  	mrcImageUnexpectedMassFromPDB  	mrcImageVolumeCalc  	mrcImageWindowing  	mrcInfo  	mrcInfoSet  	mrcMask  	mrcMeanYlinePos  	mrcMirrorImageCreate  	mrcRefCorEstimate  	mrcRefCorModify  	mrcRefCoreGet  	mrcRefCorrelation  	mrcRefCorrelationConv  	mrcRefEstimate  	mrcRefFFTConvert  	mrcRefHighPassFilter  	mrcRefImagepwzCorEstimate  	mrcRefImagepwzCorModify  	mrcRefImagepwzCorPeakFind  	mrcRefImagepwzCorrelation  	mrcRefImagepwzCorrelationByFFT  	mrcRefImagexaFit  	mrcRefLowPassFilter  	mrcRefNoiseAdd  	mrcRefNormalizing  	mrcRefPhaseImageCreate  	mrcRefSmoothing  	mrcRefz1ImageCorrelation  	muscleSimulation  	pdb2bender  	pdb2mrc  	pdb2mrc2d  	pdb2ucd  	pdbAtomSection  	pdbCAOnly  	pdbChargeFit  	pdbDisplay  	pdbHelix  	pdbInfo  	pdbMatrixCreate  	pdbMove  	pdbOneProteinGet  	pdbProteinIDSet  	pdbRhoFit  	pdbRotation  	pdbTrans  	pdbTwoProteinFit  	psFileMerge  	psFilePageMerge  	randomNormalGet  	randomUniformGet  	tiff2mrc
all::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "making" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE) 'CDEBUGFLAGS=$(CDEBUGFLAGS)' all);     done
tags::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "tagging" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE) TAGS='$(TAGS)' tags);     done
clean::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "cleaning" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE) RM_CMD='$(RM_CMD)' clean);     done
spotless::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "cleaning" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE) RM_CMD='$(RM_CMD)' spotless);     done
install::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "installing" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  install);     done
uninstall::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "removing installed binaries" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  uninstall);     done
depends::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "depending" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  depends);     done
test::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; PWD=$(PWD)/$$i; export PWD;     $(MAKE)  test);     done
Makefiles::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo making Makefiles "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; $(MAKEFILE_CMD);     export PWD; $(MAKE) Makefiles);     done
Imakefiles::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo making Imakefiles "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; $(KGENIMAKE) -tb $(TOOLBOX_NAME);     export PWD; $(MAKE) Imakefiles);     done
GenImakefiles::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo creating Imakefiles "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; $(KGENIMAKE) -tb $(TOOLBOX_NAME) -recreate;     export PWD; $(MAKE) GenImakefiles);     done
gendepend::
	@true
depend::
	@true
klint::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running klint" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  klint);     done
gw::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running ghostwriter" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  gw);     done
struct::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running kgenstruct" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  struct);     done
clui::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running ghostwriter" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  clui);     done
gui::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running conductor" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  gui);     done
conductor::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running conductor" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  conductor);     done
listincl::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running findincl" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  listincl);     done
proto::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running mkproto" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  proto);     done
sbrowser::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running sbrowser" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  sbrowser);     done
cleanout::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "removing Makefiles" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  cleanout);     done
purecov::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running purecoverage" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  purecov);     done
install-purecov::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "installing purecoverage binary" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  install-purecov);     done
purify::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running purify" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  purify);     done
install-purify::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "installing purify binary" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  install-purify);     done
quantify::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "running quantify" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  quantify);     done
install-quantify::
	@for i in $(SUBDIRS) ;    do     (cd $$i ; echo "installing quantify binary" "in $(PWD)/$$i...";     PWD=$(PWD)/$$i; export PWD; $(MAKE)  install-quantify);     done
clean::
	$(RM_CMD) \#*
Makefile::
	$(MAKEFILE_CMD)
Imakefile::
	$(KGENIMAKE) -tb $(TOOLBOX_NAME)
GenImakefile::
	$(KGENIMAKE) -tb $(TOOLBOX_NAME) -recreate
