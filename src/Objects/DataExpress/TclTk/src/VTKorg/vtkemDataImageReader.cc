/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% vtkemDataReader.cc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : vtkemDataReader.cc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%vtkemDataReader.cc ver%I%; Date:%D% %Z%";
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
#include "./vtkemDataImageReader.hh"
/*
	vtkemDataReaderNewCommand
*/
/*
vtkemDataReader*
vtkemDataReader::New()
{
	// First try to create the object from the vtkObjectFactory
	vtkObject* ret = vtkObjectFactory::CreateInstance("vtkemDataReader");
	if(ret) {
		return (vtkemDataReader*)ret;
	}
	return new vtkemDataReader;
}
*/
vtkStandardNewMacro(vtkemDataReader);

vtkemDataReader::vtkemDataReader()
{
  this->FilePrefix = NULL;
  this->Filename   = NULL;
  this->ImageRange[0] = this->ImageRange[1] = -1;
  this->DataOrigin[0] = this->DataOrigin[1] = this->DataOrigin[2] = 0.0;
  this->DataSpacing[0] = this->DataSpacing[1] = this->DataSpacing[2] = 1.0;
}

vtkemDataReader::~vtkemDataReader()
{
}

void vtkemDataReader::ExecuteInformation()
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

void vtkemDataReader::ExecuteData(vtkDataObject* outp)
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

vtkImageData *vtkemDataReader::GetImage(int ImageNum)
{
  vtkFloatArray *newScalars;
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
vtkemDataReader::ReadVolume(vtkFloatArray *scalars)
{
  float*           pixel;
  char             filename[1024];
  int              status;
  int              num; 

  sprintf(filename, "%s", this->Filename);
  mrcFileRead(&this->mrc, filename, "in vtkemDataReader::ReadVoluem\n", 0);

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

int vtkemDataReader::ReadFloatImage(float* pixel, emData* em)
{
  	long i;
  	double data;
  	emDataParaTypeReal x, y, z;
 	 int status;

  	i=0
	for(z=0; z<em->Header.Cont.Nz; z++) {
	  for(y=0; y<em->Header.Cont.Ny; y++) {
	    for(x=0; x<em->Header.Cont.Nx; x++) {
		  emDataPixelDataGet(em, x, y, z, &data, this->DataType, this->DataHow); 
		  pixel[i] = (float)data;
		  i++;
		}
	  }
	}
	status = 1;
  	return status;
}

void vtkemDataReader::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkVolumeReader::PrintSelf(os,indent);

  os << indent << "Filename: " 
     << (this->Filename ? this->Filename : "(none)") << "\n";
}

