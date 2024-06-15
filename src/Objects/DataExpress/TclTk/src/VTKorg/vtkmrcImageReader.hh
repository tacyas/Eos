#ifndef __vtkmrcImageReader_h
#define __vtkmrcImageReader_h

#include <stdio.h>
#include "vtkTclUtil.h"
#include "vtkTransform.h"
#include "vtkStructuredPointsSource.h"
#include "vtkVolumeReader.h"
#include "vtkFloatArray.h"
#include "vtkObjectFactory.h"
#include "mrcImage.h"

/* struct begin */
class VTK_EXPORT vtkmrcImageReader : public vtkVolumeReader
{
public:
  vtkTypeMacro(vtkmrcImageReader,vtkVolumeReader);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkmrcImageReader *New();


  // Description:
  vtkSetStringMacro(Filename);
  vtkGetStringMacro(Filename);

  vtkSetMacro(DataType,mrcPixelDataType);
  vtkGetMacro(DataType,mrcPixelDataType);

  vtkSetMacro(DataHow,mrcPixelDataHowToGet);
  vtkGetMacro(DataHow,mrcPixelDataHowToGet);

  //
  vtkImageData *GetImage(int ImageNum);

protected:
  vtkmrcImageReader();
  ~vtkmrcImageReader();
  vtkmrcImageReader(const vtkmrcImageReader&) {};
  void operator=(const vtkmrcImageReader&) {};

  virtual void ExecuteData(vtkDataObject*);
  virtual void ExecuteInformation();

  char *Filename;
  mrcImage mrc;
  mrcPixelDataType     DataType;
  mrcPixelDataHowToGet DataHow;

  // Get Volume Data
  void ReadVolume(vtkFloatArray* scalars);
  int ReadFloatImage(float* pixel, mrcImage* mrc);
};
/* struct end */

/* prototype begin */
ClientData vtkmrcImageReaderNewCommand();

int VTKTCL_EXPORT 
vtkmrcImageReaderCommand(
     ClientData cd, Tcl_Interp *interp,
     int argc, char *argv[]);
/* prototype end */

#endif
