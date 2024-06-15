#ifndef __vtkmrcImageReader_h
#define __vtkmrcImageReader_h

#include <stdio.h>
//#include "vtkFloatScalars.h"
#include "vtkStructuredPointsSource.h"
#include "vtkVolumeReader.h"
#include "mrcImage.h"

class vtkmrcImageReader : public vtkVolumeReader
{
public:
  vtkmrcImageReader();
  char *GetClassName() {return "vtkmrcImageReader";};
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  vtkSetStringMacro(Filename);
  vtkGetStringMacro(Filename);

  vtkSetMacro(PixelType, mrcPixelDataType);
  vtkGetMacro(PixelType, mrcPixelDataType);

  vtkSetMacro(HowToGet, mrcPixelDataHowToGet);
  vtkGetMacro(HowToGet, mrcPixelDataHowToGet);

  vtkImageData *GetImage(int ImageNum);

protected:
  void Execute();
  char *Filename;
  mrcPixelDataType     PixelType;
  mrcPixelDataHowToGet HowToGet;

  //vtkFloatScalars *ReadVolume(int dim[3]);
  int ReadFloatImage(float* pixel, mrcImage* mrc, mrcPixelDataType type, mrcPixelDataHowToGet how);  
};

#endif
