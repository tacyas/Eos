%module molvieRuby

%{
#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "Matrix3D.h"
#include "mrcImage.h"
#include "pdbFile.h"
#include "DisplayListNumber.h"
#include "lmolvieProteinStatus.h"
#include "molvieDefault.h"
#include "molvieDockDefault.h"
#include "molvieFlightDefault.h"
#include "molvieMrcViewerDefault.h"
#include "molvieProjectionDefault.h"
#include "molvieViewerDefault.h"
#include "lmolvie.h"

%}

%include "Matrix3D.h"
%include "mrcImage.h"
%include "pdbFile.h"
%include "lmolvie.h"  
%include "DisplayListNumber.h"
%include "lmolvieProteinStatus.h"
%include "molvieDefault.h"

 
extern FILE* fopen(char* filename, char* mode);
extern void fclose(FILE* fpt);

