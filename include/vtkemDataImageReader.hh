#ifndef __vtkemDataReader_h
#define __vtkemDataReader_h

#include <stdio.h>
/*
#include "vtkTclUtil.h"
*/
#include "vtkTransform.h"
#include "vtkStructuredPointsSource.h"
#include "vtkVolumeReader.h"
#include "vtkFloatArray.h"
#include "vtkObjectFactory.h"
#include "emData.h"

/* struct begin */
class VTK_EXPORT vtkemDataReader : public vtkVolumeReader
{
public:
  vtkTypeMacro(vtkemDataReader,vtkVolumeReader);
  void PrintSelf(ostream& os, vtkIndent indent);

  static vtkemDataReader *New();


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
  vtkemDataReader();
  ~vtkemDataReader();
  vtkemDataReader(const vtkemDataReader&) {};
  void operator=(const vtkemDataReader&) {};

  virtual void ExecuteData(vtkDataObject*);
  virtual void ExecuteInformation();

  char *Filename;
  emData em;
  mrcPixelDataType     DataType;
  mrcPixelDataHowToGet DataHow;

  // Get Volume Data
  void ReadVolume(vtkFloatArray* scalars);
  int ReadFloatImage(float* pixel, emData* mrc);
};
/* struct end */

/* prototype begin */
ClientData 
vtkemDataReaderNewCommand();

int VTKTCL_EXPORT 
vtkemDataReaderCommand(
     ClientData cd, Tcl_Interp *interp,
     int argc, char *argv[]);
/* prototype end */

#endif
