/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% vtkmrcImageWriter.cc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : vtkmrcImageWriter.cc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%vtkmrcImageWriter.cc ver%I%; Date:%D% %Z%";
#include "vtkmrcImageWriter.hh"
#include "mrcImage.h"
/*
vtkmrcImageWriter::vtkmrcImageWriter()
{
  this->Filename = NULL;
}

vtkmrcImageWriter::~vtkmrcImageWriter()
{
  if ( this->Filename ) delete [] this->Filename;
}

// Description:
// Specify the input data or filter.
void vtkmrcImageWriter::SetInput(vtkStructuredPoints *input)
{
  if ( this->Input != input )
    {
    vtkDebugMacro(<<" setting Input to " << (void *)input);
    this->Input = (vtkDataSet *) input;
    this->Modified();
    }
}

// Description:
// Write mrcImage data out.
void vtkmrcImageWriter::WriteData()
{
  FILE *fp;
  vtkColorScalars *newScalars;
  int *dims;
  int numPts;
  vtkStructuredPoints *input=(vtkStructuredPoints *)this->Input;
  vtkPointData *pd = input->GetPointData();
  int bpp, i;
  unsigned char *buffer;
  
  vtkDebugMacro(<< "Writing mrcImage file");

  dims = input->GetDimensions();
  numPts = dims[0]*dims[1]*dims[2];

  if (strcmp(pd->GetScalars()->GetScalarType(),"ColorScalar"))
    {
    vtkWarningMacro(<< "Scalars must be of type ColorScalar.");
    return;
    }

  newScalars = (vtkColorScalars *)pd->GetScalars();

  bpp = newScalars->GetNumberOfValuesPerScalar();

  if (!(bpp % 2))
    {
    vtkWarningMacro(<< "Scalars must have one or three bytes per pixel");
    return;
    }
  
  if ( this->Filename == NULL)
    {
    vtkErrorMacro(<< "Please specify filename to write");
    return;
    }

  fp = fopen(this->Filename,"wb");
  if (!fp) 
    {
    vtkErrorMacro(<< "Couldn't open file: " << this->Filename << endl);
    return;
    }

  buffer = newScalars->GetPtr(0);
  
  if (bpp == 1)
    {
    fprintf(fp,"P5\n");
    fprintf(fp,"# pgm file written by the visualization toolkit\n");
    fprintf(fp,"%i %i\n255\n",dims[0],dims[1]);
    // now write the binary info 
    for (i = dims[1]-1; i >= 0; i--)
      {
      fwrite(buffer + i*dims[0],1,dims[0],fp);
      }
    }
  else
    {
    fprintf(fp,"P6\n");
    fprintf(fp,"# ppm file written by the visualization toolkit\n");
    fprintf(fp,"%i %i\n255\n",dims[0],dims[1]);
    // now write the binary info 
    for (i = dims[1]-1; i >= 0; i--)
      {
      fwrite(buffer + i*dims[0]*3,1,dims[0]*3,fp);
      }
    }
  
  fclose(fp);
}

void vtkmrcImageWriter::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkWriter::PrintSelf(os,indent);

  os << indent << "Filename: " 
     << (this->Filename ? this->Filename : "(none)") << "\n";
}


*/
