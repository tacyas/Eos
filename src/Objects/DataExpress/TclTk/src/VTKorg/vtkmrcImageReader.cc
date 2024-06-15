/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% vtkmrcImageReader.cc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : vtkmrcImageReader.cc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%vtkmrcImageReader.cc ver%I%; Date:%D% %Z%";
#include <stdlib.h>
/*
#include "vtkTclUtil.h"
*/
//#include "vtkScalars.h"
#include "vtkFloatArray.h"
#include "vtkSetGet.h"
#include "vtkObjectFactory.h"
#include "vtkTransform.h"
#include "vtkStructuredPointsReader.h"
#include "vtkVolumeReader.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "./vtkmrcImageReader.hh"
/*
	vtkmrcImageReaderNewCommand
*/
/*
vtkmrcImageReader*
vtkmrcImageReader::New()
{
	// First try to create the object from the vtkObjectFactory
	vtkObject* ret = vtkObjectFactory::CreateInstance("vtkmrcImageReader");
	if(ret) {
		return (vtkmrcImageReader*)ret;
	}
	return new vtkmrcImageReader;
}
*/
vtkStandardNewMacro(vtkmrcImageReader);

vtkmrcImageReader::vtkmrcImageReader()
{
  this->FilePrefix = NULL;
  this->Filename   = NULL;
  this->ImageRange[0] = this->ImageRange[1] = -1;
  this->DataOrigin[0] = this->DataOrigin[1] = this->DataOrigin[2] = 0.0;
  this->DataSpacing[0] = this->DataSpacing[1] = this->DataSpacing[2] = 1.0;
}

vtkmrcImageReader::~vtkmrcImageReader()
{
}

void vtkmrcImageReader::ExecuteInformation()
{
	int dim[3];
	vtkImageData *output=this->GetOutput();

	// fprintf(stderr, "in ExecuteInformation");
    dim[0] = this->mrc.HeaderN.x;
    dim[1] = this->mrc.HeaderN.y;
    dim[2] = this->mrc.HeaderN.z;
	output->SetWholeExtent(0, dim[0]-1, 0, dim[1]-1, 0, dim[2]-1);
	output->SetScalarType(VTK_FLOAT);
	output->SetNumberOfScalarComponents(1);
	output->SetSpacing(this->DataSpacing);
	output->SetOrigin(this->DataOrigin);
}

void vtkmrcImageReader::ExecuteData(vtkDataObject* outp)
{
  vtkImageData *output = this->AllocateOutputData(outp);
  vtkFloatArray *newScalars = vtkFloatArray::SafeDownCast(output->GetPointData()->GetScalars());

  int dim[3];
  float Spacing[3];
  float origin[3];

  // fprintf(stderr, "in Execute");
  if(this->Filename == NULL) {
    vtkErrorMacro(<<"Please specify a filename!");
    return;
  }

  ReadVolume(newScalars);

  dim[0] = this->mrc.HeaderN.x;
  dim[1] = this->mrc.HeaderN.y;
  dim[2] = this->mrc.HeaderN.z;
  Spacing[0] = this->mrc.HeaderLength.x;
  Spacing[1] = this->mrc.HeaderLength.y;
  Spacing[2] = this->mrc.HeaderLength.z;
  origin[0]  = this->mrc.HeaderLength.x*this->mrc.HeaderStartN.x;
  origin[1]  = this->mrc.HeaderLength.y*this->mrc.HeaderStartN.y;
  origin[2]  = this->mrc.HeaderLength.z*this->mrc.HeaderStartN.z;

  output->SetDimensions(dim);
  output->SetOrigin(origin);
  output->SetSpacing(Spacing);
}

vtkImageData *vtkmrcImageReader::GetImage(int ImageNum)
{
  vtkFloatArray *newScalars=NULL;
  vtkImageData *result;
  int dim[3];
  float Spacing[3];
  float origin[3];

  // fprintf(stderr, "in Get Image");
  result = vtkImageData::New();
  if ( this->Filename == NULL ) {
    vtkErrorMacro(<<"Please specify a filename!");
    return NULL;
  }

  this->ReadVolume(newScalars);

  dim[0] = this->mrc.HeaderN.x;
  dim[1] = this->mrc.HeaderN.y;
  dim[2] = this->mrc.HeaderN.z;
  Spacing[0] = this->mrc.HeaderLength.x;
  Spacing[1] = this->mrc.HeaderLength.y;
  Spacing[2] = this->mrc.HeaderLength.z;
  origin[0]  = this->mrc.HeaderLength.x*this->mrc.HeaderStartN.x;
  origin[1]  = this->mrc.HeaderLength.y*this->mrc.HeaderStartN.y;
  origin[2]  = this->mrc.HeaderLength.z*this->mrc.HeaderStartN.z;

  result->SetDimensions(dim);
  result->SetOrigin(origin);
  result->SetSpacing(Spacing);
  if(newScalars) {
    result->GetPointData()->SetScalars(newScalars);
    newScalars->Delete();
  }
  return result;
}

void
vtkmrcImageReader::ReadVolume(vtkFloatArray *scalars)
{
  float*           pixel;
  char             filename[1024];
  int              status;
  int              num; 

  sprintf(filename, "%s", this->Filename);
  mrcFileRead(&this->mrc, filename, "in vtkmrcImageReader::ReadVoluem\n", 0);

  // Create the floart scalars

  // Get a pointer to the data 
  pixel = scalars->WritePointer(0, this->mrc.PixelPerImage);

  if(pixel==NULL) {
  	fprintf(stderr, "Not allocated\n");
	exit(EXIT_FAILURE);
  }

  // Read the image data
  status = ReadFloatImage(pixel, &(this->mrc));

  return;
}

int vtkmrcImageReader::ReadFloatImage(float* pixel, mrcImage* mrc)
{
  long i;
  double data;
  mrcImageParaTypeReal x, y, z;
  int status;

  i = 0;
  if(IsImage(mrc, "in ReadFloatImage", 0)) {
	for(z=0; z<mrc->HeaderN.z; z++) {
	  for(y=0; y<mrc->HeaderN.y; y++) {
	    for(x=0; x<mrc->HeaderN.x; x++) {
		  mrcPixelDataGet(mrc, x, y, z, &data, this->DataType, this->DataHow); 
		  pixel[i] = (float)data;
		  i++;
		}
	  }
	}
	status = 1;
  } else if(IsFT(mrc, "in ReadFloatImage", 0)) {
	for(z=-mrc->HeaderN.z/2.0; z<mrc->HeaderN.z/2.0; z++) {
	  for(y=-mrc->HeaderN.y/2.0; y<mrc->HeaderN.y/2.0; y++) {
	    for(x=-mrc->HeaderN.x/2.0; x<mrc->HeaderN.x/2.0; x++) {
		  mrcPixelDataGet(mrc, x, y, z, &data, this->DataType, this->DataHow); 
		  if(x<1 && y < 1) {
		  	fprintf(stderr, "%f %lf\n", z, data);
		}
		  pixel[i] = (float)data;
		  i++;
		}
	  }
	}
	status = 1;
  } else {
	status = 0;
  }
  return status;
}

void vtkmrcImageReader::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkVolumeReader::PrintSelf(os,indent);

  os << indent << "Filename: " 
     << (this->Filename ? this->Filename : "(none)") << "\n";
}

